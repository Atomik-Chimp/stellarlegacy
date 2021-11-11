// $Id: game-server.cpp,v 1.17 2002/07/12 10:00:46 mkrohn5 Exp $

// Game Server Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>
//             Alberto Barsella, <>

// Copyright (C) 2000 - 2002, Marco Krohn, <marco.krohn@gmx.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 1, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <list>

#include <stdio.h>

#include "gamelogic/galaxy.h"
#include "admin/game.h"
#include "admin/game-server.h"
#include "common/global.h"
#include "common/os_specific.h"
#include "admin/player.h"
#include "gamelogic/rulesystem.h"
#include "gamelogic/stobj.h"
#include "gamelogic/stolist.h"
#include "gamelogic/universe.h"

using namespace std;





//----------------------------------------  class TGameServer  ----------------------------------------

TGameServer :: TGameServer( const string& gameDir, const string& gameName )
  : TGameSC( false, gameDir, gameName )
{
}



TGameServer :: ~TGameServer()
{
}



bool TGameServer :: backupGameFiles() const
{
// TODO: use sstream (Alberto: I don't have it in the C++ lib) FIXME
char newfname[256]; // buffer exploit!! :))

  // create subdir
  sprintf( newfname, "%sbackup-turn-%ld/", getGameDirectory().c_str(), getTurn() );
  osSpecificMkdir( newfname, 0700 );                       // owner-only readable
  // FIXME: actually we should check if the operation succeeded

  // backup server database
  sprintf( newfname, "%sbackup-turn-%ld/%s", getGameDirectory().c_str(),
           getTurn(), FNameServerMaster().c_str() );
  rename( FSpecServerMaster().c_str(), newfname );

  // backup all player files
  list<TPlayer*>::const_iterator plit;
  for (plit = getPlayers().begin(); plit != getPlayers().end(); plit++) {

    // backup player data file ...
    sprintf(newfname, "%sbackup-turn-%ld/%s", getGameDirectory().c_str(),
            getTurn(), FNamePlayerData((*plit)->getName()).c_str());
    rename(FSpecPlayerData((*plit)->getName()).c_str(), newfname);

    // backup player order file ...
    sprintf(newfname, "%sbackup-turn-%ld/%s", getGameDirectory().c_str(),
            getTurn(), FNamePlayerOrder((*plit)->getName()).c_str());
    rename(FSpecPlayerOrder((*plit)->getName()).c_str(), newfname);
  }

  return true;                                             // optimism is good for you
}



void TGameServer :: executeActions()
{
  fActionSequencer.runSequence();

  fActionSequencer.clear();
  addStandardActions();
  fActionSequencer.runSequence();
}



void TGameServer :: incrementTurn()
{
  setTurn( getTurn() + 1 );
}



bool TGameServer :: loadPlayerOrderFiles()
{
list<TPlayer*>::const_iterator it;

  for ( it=getPlayers().begin(); it!=getPlayers().end(); it++ )  {
    LOG("TGameServer","loadPlayerOrderFiles") << "loading the player order file for player "
      << (*it)->getName() << endl;
    setActivePlayer( *it );
    loadPlayerOrderFile( (*it)->getName() );
  }
  return false;
}



bool TGameServer :: savePlayerDataFiles() const
{
bool ret = true;
TDataPackageList DataGroup;

  // iterate over all players and generate the files
  list<TPlayer*>::const_iterator plit;
  for (plit = getPlayers().begin(); plit != getPlayers().end(); plit++) {
    ofstream out( FSpecPlayerData( (*plit)->getName() ).c_str() );

    // TODO: only save the stuff visible by the player, for the moment
    // it's just (with little exceptions since not all variables are accessible "here")
    // a cut'n'paste of saveFullDatabase

    // level 1: write the game rules to disk
    TRuleSystem::instance().save( &DataGroup );
    ret &= DataGroup.save( out );
    out << endl;                                                  // an extra empty line to make the result look nicer
    DataGroup.DeleteAll();

    // level 2: create a game definition block
    // (this comes later since its contents may be rule-dependent)
    static const string sBlockType = "game";
    ret &= DataGroup.add( "blocktype", &sBlockType, true, false );

    ret &= DataGroup.add( "name", &getGameName(), true );  // unique=true
    int4 turn = getTurn();
    ret &= DataGroup.add( "turn", &turn, true);            // unique=true
    ret &= DataGroup.save( out );
    out << endl;
    DataGroup.DeleteAll();

    // level 3: write the players/races to disk
    list<TPlayer*>::const_iterator plit;
    const list<TPlayer*>& players = getPlayers();
    for (plit = players.begin(); plit != players.end(); plit++) {
      (*plit)->save(&DataGroup);
      ret &= DataGroup.save( out );
      out << endl;
      DataGroup.DeleteAll();
    }

    list<TRace*>::const_iterator rcit;
    const list<TRace*>& races = getRaces();
    for (rcit = races.begin(); rcit != races.end(); rcit++) {
      (*rcit)->save(&DataGroup);
      ret &= DataGroup.save( out );
      out << endl;
      DataGroup.DeleteAll();
    }

    // level 4: save the galaxies
    list<TGalaxy*>::const_iterator galit;
    const list<TGalaxy*>& galaxies = TUniverse::instance()->getGalaxies();
    for ( galit=galaxies.begin(); galit!=galaxies.end(); galit++ )  {
      (*galit)->save( &DataGroup );
      ret &= DataGroup.save( out );
      out << endl;
      DataGroup.DeleteAll();
    }

    // level 5: write all stellar objects to disk
    TStellarObjectList::const_iterator it;
    for ( galit=galaxies.begin(); galit!=galaxies.end(); galit++ )  {
      const TStellarObjectList& stolist( (*galit)->getStellarObjectList() );
      for ( it=stolist.begin(); it!=stolist.end(); it++ )
      {
        (*it)->save( &DataGroup );                         // saves the stellar object to a data package list
        ret &= DataGroup.save( out );                      // save the data package list to disk
        out << endl;                                       // an extra empty line to make the result look nicer
        DataGroup.DeleteAll();
      }
    }

    // And finaly close the output file
    out.close();

    // if an error was encountered, drop out of the save process
    if ( ret == false )  break;
  }

  return ret;
}





//----------------------------------------  protected  ----------------------------------------

// virtual method
void TGameServer :: PDBLoadOrders( TDataPackageList* block )
{
int4 turn;
string gameName;
bool bCheck = true;

  LOG("TGameServer","PDBLoadOrders") << "load player actions!" << endl;
  LOG_BEGIN_INDENT();

  bCheck &= block->getAndDelete( "name", &gameName, true );              // unique=true
  setGameName( gameName );
  bCheck &= block->getAndDelete( "turn", &turn, true );                  // unique=true
  if ( !bCheck )  {
    Fatal("TGameServer", "PDBLoadOrders", "Missing parameters for game initialization", -1);
  }
  LOG("TGameServer","PDBLoadOrders") << "turn: " << getTurn()
    << ", order file for turn: " << turn << endl;

  /* we must make sure that the actions correspond to the turn being
  * played: if not they must be silently ignored (maybe by aborting
  * the parser (how to do this? a flag to yylex to return EOF?)
  */

  if ( turn < getTurn() )  {
      // warn about the problem
      WLOG("TGameServer","PDBLoadOrders") << "order file is outdated (and will be ignored)" << endl;
  }
  else if ( turn > getTurn() )  {
    // this is more serious, fatal for the moment
    // TODO: return cleaner errors - could be someone replaying an older turn
    Fatal("TGameServer", "PDBLoadOrders", "Order file is from the future?!?!", -1);
  }

  LOG_END_INDENT();
}





//----------------------------------------  private  ----------------------------------------

#include "gamelogic/stolist.h"
void TGameServer :: addStandardActions()
{
TAction* action;
TStellarObjectList SOList;
TStellarObjectList::iterator it;

  TGalaxy* galaxy = *(TUniverse::instance()->getGalaxies()).begin();
  galaxy->getStellarObjectList().Filter( &SOList, TSOLFilterType(TType::FLEET) );

  // generates actions for all fleets that have waypoints 
  for ( it=SOList.begin(); it!=SOList.end(); it++ )  {
    if ( (*it)->hasWaypoint() == true )  {
      action = PMAction.create( "MOVE_FLEET" );
      if (!action)  {
        Fatal("TGameServer", "addStandardActions","unable to create MOVE_FLEET actions!!");
      }
      action->setCreator( (*it)->getOwner() );
      action->setActor( *it );
      if ( (*it)->getWaypointList()->getFirst()->isStellarObject() == true )  {
        TStellarObject* p = (*it)->getWaypointList()->getFirst()->getStellarObject();
        action->addInvolvedObject( p );                    // the dest is a stellar object
      }

      recordPlayerAction( action );                        // stores the action in the action sequencer
    }
  }
}





/*
* $Log: game-server.cpp,v $
* Revision 1.17  2002/07/12 10:00:46  mkrohn5
* include path + upper->lower fixes
*
* Revision 1.16  2002/07/08 06:22:44  mkrohn5
* bug fix
*
* Revision 1.15  2002/07/02 23:14:22  mkrohn5
* lower -> upper for actions
*
* Revision 1.14  2002/07/01 20:52:23  ishark
* fixes in act-to-cpp and related stuff
*
* Revision 1.13  2002/07/01 00:05:56  mkrohn5
* prototype pattern used in action.cpp/.h
*
* Revision 1.12  2002/06/28 10:12:06  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.11  2002/06/23 12:00:45  mkrohn5
* add the involved objects to the action
*
* Revision 1.10  2002/06/23 11:15:07  mkrohn5
* - added a two more fleets (to test conflict resolution--he,he a play of words :-)
* - enhanced the code for generating fleet movement actions
*
* Revision 1.9  2002/06/21 08:31:57  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.8  2002/06/07 00:31:05  mkrohn5
* name change of action
*
* Revision 1.7  2002/06/05 00:30:16  mkrohn5
* changed TRuleSystem::instance
*
* Revision 1.6  2002/06/04 09:17:09  mkrohn5
* "move" actions are added to all stobj
*
* Revision 1.5  2002/05/15 08:30:55  ishark
* actionsequencer now uses lists + cosmetic fixes
*
* Revision 1.4  2002/05/13 22:57:54  mkrohn5
* started writing the addStandardActions method
*
* Revision 1.3  2002/05/12 01:17:24  mkrohn5
* - moved some methods around
* - the client now is able to load the old actions
*
* Revision 1.2  2002/05/10 23:43:42  mkrohn5
* started implementation of loadPlayerOrderFiles
*
* Revision 1.1  2002/05/10 10:27:41  mkrohn5
* split TGame in several new classes (see ChangeLog)
*
*/
