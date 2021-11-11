// $Id: game.cpp,v 1.29 2002/07/12 10:00:46 mkrohn5 Exp $

// Game Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>
//             Alberto Barsella, <>

// Copyright (C) 2000 - 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#include <fstream>

#include "common/datapackage.h"
#include "admin/game.h"
#include "common/os_specific.h"
#include "admin/player.h"
#include "gamelogic/race.h"
#include "gamelogic/rulesystem.h"
#include "gamelogic/stobj.h"
#include "common/stringtools.h"
#include "gamelogic/universe.h"

using namespace std;





//----------------------------------------  class TGame  ----------------------------------------

void TGame :: addPlayer( TPlayer* player )
{
  fPlayers.add( player );
}



void TGame :: addRace( TRace* race )
{
  fRaces.add( race );
}



const string& TGame :: getGameDirectory() const
{
  return fGameDirectory;
}



const string& TGame :: getGameName() const
{
  return fGameName;
}



const list<TPlayer*>& TGame :: getPlayers() const
{
  return fPlayers;
}



const list<TRace*>& TGame :: getRaces() const
{
  return fRaces;
}



int4 TGame :: getTurn() const
{
  return fCurrentTurn;
}



// virtual method
void TGame :: resetAll()
{
  TUniverse::instance()->reset();
  TLinkUpdate::instance()->reset();
  TRuleSystem::instance().reset();

  // now reset everything TGame related
  fTransitions.clear();
  fGameDirectory = "";
  fGameName = "";
  fCurrentTurn = -1;
  fRaces.deleteAll();
  fPlayers.deleteAll();
}



bool TGame :: saveServerMasterFile() const
{
bool ret = true;
ofstream out( FSpecServerMaster().c_str() );
TDataPackageList DataGroup;

  // level 1: write the game rules to disk
  TRuleSystem::instance().save( &DataGroup );
  ret &= DataGroup.save( out );
  out << endl;                                                  // an extra empty line to make the result look nicer
  DataGroup.DeleteAll();

  // level 2: create a game definition block
  // (this comes later since its contents may be rule-dependent)
  static const string sBlockType = "game";
  ret &= DataGroup.add( "blocktype", &sBlockType, true );
  ret &= DataGroup.add( "name", &fGameName, true );        // unique=true
  ret &= DataGroup.add( "turn", &fCurrentTurn, true );
  ret &= fIluvatar.save( &DataGroup, "iluvatar", true );
  ret &= DataGroup.save( out );
  out << endl;
  DataGroup.DeleteAll();

  // level 3: write the players/races to disk
  list<TPlayer*>::const_iterator plit;
  for (plit = fPlayers.begin(); plit != fPlayers.end(); plit++) {
    (*plit)->save(&DataGroup);
    ret &= DataGroup.save( out );
    out << endl;
    DataGroup.DeleteAll();
  }

  list<TRace*>::const_iterator rcit;
  for (rcit = fRaces.begin(); rcit != fRaces.end(); rcit++) {
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
    const TStellarObjectList& stolist = (*galit)->getStellarObjectList();
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

  return ret;
}



void TGame :: setGameName( const string& name )
{
  fGameName = name;
}



void TGame :: setTurn( int4 turn )
{
  fCurrentTurn = turn;
}





//----------------------------------------  protected  ----------------------------------------

// gameName=""
TGame :: TGame( const string& gameDir, const string& gameName )
{
  fGameDirectory = TStringTools::convertToDirectory( gameDir );
  setGameName( gameName );
  fCurrentTurn = -1;
  fRaces.setAutoDeleteMode( true );
  fPlayers.setAutoDeleteMode( true );
}



// virtual method
TGame :: ~TGame()
{
  resetAll();
}



string TGame :: FNamePlayerData(const string& playerName) const
{
  return TStringTools::convertToFileName(playerName) + "-data.sl";
}



string TGame :: FNamePlayerOrder(const string& playerName) const
{
  return TStringTools::convertToFileName(playerName) + "-order.sl";
}



string TGame :: FNameServerMaster() const
{
  return "server-master.sl";
}



string TGame :: FNameUniverseDefinition() const
{
  return "universe-definition.sl";
}



string TGame :: FSpecPlayerData(const string& playerName) const
{
  string ret = fGameDirectory + FNamePlayerData(playerName);
  return ret;
}



string TGame :: FSpecPlayerOrder(const string& playerName) const
{
  string ret = fGameDirectory + FNamePlayerOrder(playerName);
  return ret;
}



string TGame :: FSpecServerMaster() const
{
  string ret = fGameDirectory + FNameServerMaster();
  return ret;
}



string TGame :: FSpecUniverseDefinition() const
{
  string ret = fGameDirectory + FNameUniverseDefinition();
  return ret;
}



string TGame :: getBlockType( TDataPackageList* list ) const
{
  TDataPackage* package = list->SearchAndExtractUnique( "blocktype" );

  if ( package == 0 )  {
    LOG("TGame","getBlockType") << "no blocktype found!" << endl;
  }

  string blockType = *( (string*) *package );              // all information copied
  delete package;                                          // delete the package

  LOG("TGame","getBlockType") << "blocktype: " << blockType << endl;
  return blockType;
}



void TGame :: PDBItem( TDataPackageList* block )
{
int2 itemtype;

  LOG("TGame","PDBItem") << "now loading an item ..." << endl;
  if ( block->getAndDelete("subblocktype", &itemtype, true) == false ) {
    Fatal( "TGame", "PDBItem", "unspecified item type" );
  }

  LOG("TGame","PDBItem") << "create new item: " << itemtype << endl;
  TItem* item = TRuleSystem::instance().createItem( itemtype );

  if ( item == 0 )  {
    Fatal( "TGame", "PDBItem", "item creation failed" );
  }

  LOG("TGame","PDBItem") << "loading item " << itemtype << " data ... " << endl;
  LOG_BEGIN_INDENT();
  if ( item->load( block ) == false )  {
    Fatal( "TGame", "PDBItem", "LOAD ERROR in Item object" );
  }
  LOG_END_INDENT();

  // add item to universe
  TUniverse::instance()->addItem( item );
}




void TGame :: PDBPlayer( TDataPackageList* block )
{
  LOG("TGame","PDBPlayer") << "create new player" << endl;
  TPlayer* player = new TPlayer();

  LOG("TGame","PDBPlayer") << "loading player... " << endl;
  LOG_BEGIN_INDENT();
  if ( !player->load( block ) )  {
    Fatal("TGame", "PDBPlayer", "LOAD ERROR in Player object", -1);
  }
  LOG_END_INDENT();

  fPlayers.push_back( player );                            // add player to player list
}



void TGame :: PDBRace( TDataPackageList* block )
{
bool ret;

  LOG("TGame","PDBRace") << "create new race" << endl;
  TRace* pRace = TRuleSystem::instance().createRace();

  LOG("TGame","PDBRace") << "loading race... " << endl;

  LOG_BEGIN_INDENT();
  #ifdef SECURE_MODE
    block->showContent();
  #endif // SECURE MODE
  ret = pRace->load( block );
  if ( ret == false )  Fatal("TGame", "PDBRace", "LOAD ERROR in Race object", -1);
  LOG_END_INDENT();

  // add player to player list
  fRaces.push_back( pRace );
}



void TGame :: PDBRuleSystem( TDataPackageList* block )
{
  LOG("TGame","PDBRuleSystem") << "loading rule system... " << endl;
  LOG_BEGIN_INDENT();
  if ( TRuleSystem::instance().load( block ) == false )
    Fatal("TGame", "PDBRuleSystem", "LOAD ERROR in RuleSystem object", -1);
  LOG_END_INDENT();

  LOG("TGame","PDBRuleSystem") << "checking if the rule atoms fit together... " << endl;
  if ( TRuleSystem::instance().checkDependencies() == false ) {
    Fatal("TGame", "PDBRuleSystem", "Dependency errors in RuleSystem object", -1);
  }
  LOG("TGame","PDBRuleSystem") << "all rule atoms and modules are validated!" << endl;
}



void TGame :: processDataBlock( TDataPackageList* block )
{
  string sBlockType;

  LOG("TGame","processDataBlock") << "received data block. start processing ..." << endl;

  sBlockType = getBlockType( block );
  LOG("TGame","processDataBlock") << "found: " << sBlockType << endl;

  // check for a valid block
  list<tTransition>::iterator it;

  for ( it=fTransitions.begin(); it!=fTransitions.end(); it++ )  {
    if ( it->Function == 0 )  break;

    if ( it->CurrLevel == fLoadLevel && it->BlockType == sBlockType ) {
      (this->*(it->Function))(block);                      // call the right method for parsing the data block

      fLoadLevel = it->NewLevel;
      LOG("TGame","processDataBlock") << "switching to load level: " << fLoadLevel << endl;
      break;
    }

  }

  // check if we failed to find a valid transition
  if ( it->Function == 0 )  {
    Fatal("TGame", "processDataBlock", "structure error in file data", -1);
  }
}



void TGame :: resetLoadLevel()
{
  fLoadLevel = 0;
}





/*
* $Log: game.cpp,v $
* Revision 1.29  2002/07/12 10:00:46  mkrohn5
* include path + upper->lower fixes
*
* Revision 1.28  2002/06/28 10:12:06  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.27  2002/06/21 08:31:57  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.26  2002/06/05 00:30:16  mkrohn5
* changed TRuleSystem::instance
*
* Revision 1.25  2002/05/13 22:58:41  mkrohn5
* small fix
*
* Revision 1.24  2002/05/12 01:17:24  mkrohn5
* - moved some methods around
* - the client now is able to load the old actions
*
* Revision 1.23  2002/05/11 23:57:33  mkrohn5
* smaller changes due to new "super"-race
*
* Revision 1.22  2002/05/11 10:40:44  mkrohn5
* more bugfixes
*
* Revision 1.21  2002/05/10 10:27:41  mkrohn5
* split TGame in several new classes (see ChangeLog)
*
* Revision 1.20  2002/04/01 19:08:33  mkrohn5
* fix creator() -> getCreator()
*
* Revision 1.19  2002/03/24 18:02:46  mkrohn5
* uppercase -> lowercase fixes
*
* Revision 1.18  2002/03/24 12:45:26  mkrohn5
* loading another item
*
* Revision 1.17  2002/02/05 00:49:37  mkrohn5
* item is now added to universe
*
* Revision 1.16  2002/02/03 23:16:26  mkrohn5
* now item loading is enabled
*
* Revision 1.15  2002/01/28 23:49:37  mkrohn5
* commented some code that broke the app
*
* Revision 1.14  2002/01/28 23:34:30  mkrohn5
* started some work on loading items
*
* Revision 1.13  2001/12/16 11:37:24  ishark
* TLink now uses dynamic_cast<>, lots of TAction-related fixes
*
* Revision 1.12  2001/12/09 13:25:41  ishark
* minor fixes in game.cpp and sl.cpp
*
* Revision 1.11  2001/12/07 00:21:15  mkrohn5
* - converted galaxy to the new style
* - galaxy now uses the stellar object list (the code is now a lot more readable :-)
* - made TStellarObjectList a list instead of a deque (makes list operations a lot faster)
*
* Revision 1.10  2001/12/05 00:40:47  mkrohn5
* - some conversions XXX -> xXX
* - implemented the basic rule "fleet movement"
*
* Revision 1.9  2001/12/03 01:31:30  mkrohn5
* - bug fix
* - some minor changes due to changed API
*
* Revision 1.8  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.7  2001/12/01 17:01:17  mkrohn5
* some changes due to changes in race.cpp and rulesystem.cpp
*
* Revision 1.6  2001/11/29 11:38:52  maash
* mkdir fixes (sys/stat.h -> os_specific.h; mkdir -> osSpecificMkdir)
*
* Revision 1.5  2001/11/27 10:17:32  mkrohn5
* removed some debug code which I commited accidently
*
* Revision 1.4  2001/11/25 22:04:06  mkrohn5
* - various fixes due to changes in rulesystem
* - added getRuleSystem method
*
* Revision 1.3  2001/11/08 21:13:54  ishark
* action uses new method names, additions in sl/race/game
*
* Revision 1.2  2001/11/04 03:53:59  mkrohn5
* bug fix
*
* Revision 1.1  2001/11/04 01:33:01  mkrohn5
* moved some files around
*
* Revision 1.20  2001/10/31 20:21:54  mkrohn5
* added { } around LOG
*
* Revision 1.19  2001/08/07 21:00:13  mkrohn5
* adjust path for waypoint (common->gamelogic)
*
* Revision 1.18  2001/08/03 19:42:06  ishark
* fixed function/file names to reflect RFCLoadSave
*
* Revision 1.17  2001/07/28 15:23:11  ishark
* added filters in stolist, more client code in sl.cpp
*
* Revision 1.16  2001/07/25 19:12:31  ishark
* major additions in game/sl.cpp - skeleton of localserver
*
* Revision 1.15  2001/07/10 17:57:32  ishark
* rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
*
* Revision 1.14  2001/07/05 20:34:18  ishark
* added return true in test-item, fixed parser, added action Load/Save
*
* Revision 1.13  2001/07/03 01:04:21  mkrohn5
* added some more code for loading the game
*
* Revision 1.12  2001/07/02 00:39:21  mkrohn5
* worked on load game mechanism--loading a rule system seems to work :)
*
* Revision 1.11  2001/06/29 01:08:42  mkrohn5
* added emtpy method ProcessGameData
*
* Revision 1.10  2001/06/28 21:30:39  ishark
* parser can read savefile, TObjectID now uses []
*
* Revision 1.9  2001/06/24 17:05:28  mkrohn5
* - began adding server and client mode to game
* - fixes because of class interface changes in stellarobject
*
* Revision 1.8  2001/06/22 00:37:33  mkrohn5
* added waypoint for fleet to demo game
*
* Revision 1.7  2001/06/21 11:34:46  mkrohn5
* fixed the load & save stuff
*
* Revision 1.6  2001/06/12 10:14:56  mkrohn5
* implented the save function
*
* Revision 1.5  2001/06/10 23:44:48  mkrohn5
* make it compile
*
* Revision 1.4  2001/04/18 00:35:03  mkrohn5
* load & save does now work
*
* Revision 1.3  2001/04/17 18:51:46  mkrohn5
* added the rulesystem and moved the load & save routine to the galaxy class
*
*/
