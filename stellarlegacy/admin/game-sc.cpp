// $Id: game-sc.cpp,v 1.9 2002/07/12 10:00:46 mkrohn5 Exp $

// Game Server Client Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>
//             Alberto Barsella, <>

// Copyright (C) 2002 -     , Marco Krohn, <marco.krohn@gmx.de>
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

#include "gamelogic/fleet.h"
#include "gamelogic/galaxy.h"
#include "admin/game-sc.h"
#include "admin/parser-use.h"
#include "admin/player.h"
#include "gamelogic/rulesystem.h"
#include "gamelogic/system.h"





//----------------------------------------  class TGameSC  ----------------------------------------

TPlayer* TGameSC :: getActivePlayer() const
{
  return fActivePlayer;
}



bool TGameSC :: loadPlayerOrderFile( const string& playerName )
{
  LOG("TGameSC","loadPlayerOrderFile") << "loading player order file for: "
    << playerName << endl;

  // reset...
  resetLoadLevel();
  fTransitions.clear();                                    // actually not neccessary (but let's be paranoid ;-)

  // define the needed transition table for loading the player order file
  // blocktype, current loadlevel, new loadlevel, function to call
  fTransitions.push_back( tTransition("game", 0, 1, &TGame::PDBLoadOrders) );
  fTransitions.push_back( tTransition("action", 1, 1, &TGame::PDBAction) );
  fTransitions.push_back( tTransition("", -1, -1, 0) );

  // finaly invoke the parser which results in call backs to the method
  // "processDataBlock"
  bool result = ReadFile( this, FSpecPlayerOrder(playerName) );

  // cleaning up the transition table
  fTransitions.clear();

  return result;
}



bool TGameSC :: loadServerMasterFile()
{
  // reset...
  resetLoadLevel();
  fTransitions.clear();                                    // actually not neccessary (but let's be paranoid ;-)

  // define the needed transition table for loading the server master file
  // blocktype, current loadlevel, new loadlevel, function to call
  fTransitions.push_back( tTransition("rulesystem", 0, 1, &TGame::PDBRuleSystem) );
  fTransitions.push_back( tTransition("game", 1, 2, &TGame::PDBGame) );
  fTransitions.push_back( tTransition("player", 2, 3, &TGame::PDBPlayer) );
  fTransitions.push_back( tTransition("player", 3, 3, &TGame::PDBPlayer) );
  fTransitions.push_back( tTransition("race", 3, 4, &TGame::PDBRace) );
  fTransitions.push_back( tTransition("race", 4, 4, &TGame::PDBRace) );
  fTransitions.push_back( tTransition("galaxy", 4, 5, &TGame::PDBGalaxy) );
  fTransitions.push_back( tTransition("system", 5, 6, &TGame::PDBSystem ) );
  fTransitions.push_back( tTransition("system", 6, 6, &TGame::PDBSystem ) );
  fTransitions.push_back( tTransition("fleet", 6, 7, &TGame::PDBFleet) );
  fTransitions.push_back( tTransition("fleet", 7, 7, &TGame::PDBFleet) );
  fTransitions.push_back( tTransition("", -1, -1, 0) );

  // finaly invoke the parser which results in call backs to the method
  // "processDataBlock"
  bool result = ReadFile( this, FSpecServerMaster() );

  // cleaning up the transition table
  fTransitions.clear();

  return result;
}




bool TGameSC :: recordPlayerAction( TAction* action )
{
  return fActionSequencer.addAction(action);
}





//----------------------------------------  protected  ----------------------------------------

// set the record mode of the action sequencer to true
// gameName=""
TGameSC :: TGameSC( bool actSeq, const string& gameDir, const string& gameName )
  : TGame( gameDir, gameName ), fActionSequencer(actSeq)
{
}



// virtual method
void TGameSC :: PDBAction( TDataPackageList* block )
{
  // fetch action sub-type
  string actiontype;

  if (!block->getAndDelete("subblocktype", &actiontype, true) )
    Fatal("TGame", "PDBAction", "unspecified action type", -1);

  LOG("TGame","PDBAction") << "create new action: " << actiontype << endl;

  TAction* pAction = PMAction.create( actiontype );

  if (!pAction)
    Fatal("TGame", "PDBAction", "invalid action type", -1);

  if (!pAction->isPlayerAction())
    Fatal("TGame", "PDBAction", "invalid (not player!) action type", -1);

  LOG("TGame","PDBAction") << "loading action... " << endl;
  LOG_BEGIN_INDENT();
  if ( !pAction->load( block ) )
    Fatal("TGame", "PDBAction", "LOAD ERROR in Action object", -1);

  // make sure that the current active player controls the race
  if (pAction->getCreator()->getController() != fActivePlayer)  {
    Fatal("TGame", "PDBAction", "The action does NOT come from a race controlled by the player", -1);
  }

  // finaly store the action
  recordPlayerAction( pAction );

  LOG_END_INDENT();
}



// virtual method
void TGameSC :: PDBFleet( TDataPackageList* block )
{
  LOG("TGame","PDBFleet") << "create new fleet" << endl;
  TFleet* pFleet = TRuleSystem::instance().createFleet();

  LOG("TGame","PDBFleet") << "loading fleet... " << endl;
  LOG_BEGIN_INDENT();

  // note: the fleet will automatically add itself to the right galaxy
  bool res = pFleet->load( block );
  if ( res == false ) {
    Fatal("TGame", "PDBFleet", "LOAD ERROR in Fleet object", -1);
  }

  LOG_END_INDENT();
}



// virtual method
void TGameSC :: PDBGalaxy( TDataPackageList* block )
{
  LOG("TGame","PDBGalaxy") << "create new galaxy" << endl;
  TGalaxy* pGalaxy = new TGalaxy();

  LOG("TGame","PDBGalaxy") << "loading the galaxy... " << endl;
  LOG_BEGIN_INDENT();

  // note: the galaxy will automatically add itself to the universe
  bool res = pGalaxy->load( block );
  if ( res == false ) {
    Fatal("TGame", "PDBGalaxy", "LOAD ERROR in Galaxy object", -1);
  }

  LOG_END_INDENT();
}



// virtual method
void TGameSC :: PDBGame( TDataPackageList* block )
{
  bool bCheck = true;
  string gameName;
  int4 currentTurn;

  LOG("TGameSC","PDBGame") << "load existing game!" << endl;
  LOG_BEGIN_INDENT();

  bCheck &= block->getAndDelete( "name", &gameName, true );         // unique=true
  bCheck &= block->getAndDelete( "turn", &currentTurn, true );      // unique=true
  bCheck &= fIluvatar.load( block, "iluvatar", true );

  // "apply" the loaded data to the game
  setGameName( gameName );
  setTurn( currentTurn );

  if ( !bCheck )
    Fatal("TGame", "PDBLoadGame", "Missing parameters for game initialization", -1);
  LOG_END_INDENT();
}



// virtual method
void TGameSC :: PDBSystem( TDataPackageList* block )
{
  LOG("TGame","PDBSystem") << "create new system" << endl;
  TSystem* pSystem = TRuleSystem::instance().createSystem();

  LOG("TGame","PDBSystem") << "loading system... " << endl;
  LOG_BEGIN_INDENT();

  // note: the system will automatically add itself to the right galaxy
  bool res = pSystem->load( block );
  if ( res == false ) {
    Fatal("TGame", "PDBSystem", "LOAD ERROR in System object", -1);
  }

  LOG_END_INDENT();
}



void TGameSC :: setActivePlayer( TPlayer* player )
{
  fActivePlayer = player;
}





/*
* $Log: game-sc.cpp,v $
* Revision 1.9  2002/07/12 10:00:46  mkrohn5
* include path + upper->lower fixes
*
* Revision 1.8  2002/07/01 00:05:56  mkrohn5
* prototype pattern used in action.cpp/.h
*
* Revision 1.7  2002/06/21 08:31:57  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.6  2002/06/05 00:30:16  mkrohn5
* changed TRuleSystem::instance
*
* Revision 1.5  2002/05/13 22:57:25  mkrohn5
* constructor changes
*
* Revision 1.4  2002/05/12 01:17:24  mkrohn5
* - moved some methods around
* - the client now is able to load the old actions
*
* Revision 1.3  2002/05/11 23:57:33  mkrohn5
* smaller changes due to new "super"-race
*
* Revision 1.2  2002/05/11 10:40:44  mkrohn5
* more bugfixes
*
* Revision 1.1  2002/05/10 10:27:41  mkrohn5
* split TGame in several new classes (see ChangeLog)
*
*/
