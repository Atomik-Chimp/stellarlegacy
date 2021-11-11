// $Id: game-client.cpp,v 1.7 2002/06/28 10:12:06 mkrohn5 Exp $

// Game Client Code File
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

#include "admin/game-client.h"
#include "admin/player.h"





//----------------------------------------  class TGameClient  ----------------------------------------

TGameClient :: TGameClient( const string& gameDir, const string& gameName )
  : TGameSC( true, gameDir, gameName )
{
}



bool TGameClient :: initializePlayerOrders( const string& playerName )
{
  LOG("TGameClient","initializePlayerOrders") << "now init the player orders of "
    << playerName << endl;

  // make sure that the player is in the game
  list<TPlayer*>::const_iterator plit;
  for (plit = getPlayers().begin(); plit != getPlayers().end(); plit++)  {
    if ( (*plit)->getName() == playerName)  break;
  }

  if (plit == getPlayers().end())  return false;

  setActivePlayer( *plit );

  // loads the player orders and does two things:
  // 1. store the action (sending it to the action sequencer)
  // 2. execute the action immediately (this is caused by execution mode=true)
  loadPlayerOrderFile( playerName );

  return true;
}



bool TGameClient :: savePlayerOrderFile() const
{
static const string sBlockType = "game";

  // open the file
  ofstream out( FSpecPlayerOrder( getActivePlayer()->getName() ).c_str() );
  TDataPackageList DataGroup;
  bool bReturn = true;

  string gameName = getGameName();
  int4 turn = getTurn();

  // create a game section with the game id and turn
  bReturn &= DataGroup.add( "blocktype", &sBlockType, true, false );
  bReturn &= DataGroup.add( "name", &gameName, true, false );   // unique=true, auto_delete=false
  bReturn &= DataGroup.add( "turn", &turn, true, false );       // unique=true, auto_delete=false
  bReturn &= DataGroup.save( out );
  out << endl;
  DataGroup.DeleteAll();

  // write out all the actions
  bReturn &= fActionSequencer.saveLists( out );

  // close the output file
  out.close();

  return bReturn;
}





//----------------------------------------  protected  ----------------------------------------

// virtual method
void TGameClient :: PDBLoadOrders( TDataPackageList* block )
{
int4 turn;
string gameName;
bool bCheck = true;

  LOG("TGameSC","PDBLoadOrders") << "load player actions!" << endl;
  LOG_BEGIN_INDENT();

  bCheck &= block->getAndDelete( "name", &gameName, true );              // unique=true
  setGameName( gameName );
  bCheck &= block->getAndDelete( "turn", &turn, true );                  // unique=true
  if ( !bCheck )
    Fatal("TGameSC", "PDBLoadOrders", "Missing parameters for game initialization", -1);

  /* we must make sure that the actions correspond to the turn being
   * played: if not they must be silently ignored (maybe by aborting
   * the parser (how to do this? a flag to yylex to return EOF?)
   */
  if ( turn < getTurn() )  {
    // it's the old order file, ignore it
    // ignore_actions = true blah blah
  }
  else if ( turn > getTurn() )  {
    // this is more serious, fatal for the moment
    // TODO: return cleaner errors - could be someone replaying an older turn
    Fatal("TGameSC", "PDBLoadOrders", "Order file is from the future?!?!", -1);
  }

  LOG_END_INDENT();
}





/*
* $Log: game-client.cpp,v $
* Revision 1.7  2002/06/28 10:12:06  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.6  2002/06/21 08:31:57  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.5  2002/05/15 08:30:55  ishark
* actionsequencer now uses lists + cosmetic fixes
*
* Revision 1.4  2002/05/13 22:56:23  mkrohn5
* removed unnecessary reInit
* changed the constructor
*
* Revision 1.3  2002/05/12 01:22:25  mkrohn5
* removed unneccessary cout
*
* Revision 1.2  2002/05/12 01:17:24  mkrohn5
* - moved some methods around
* - the client now is able to load the old actions
*
* Revision 1.1  2002/05/10 10:27:41  mkrohn5
* split TGame in several new classes (see ChangeLog)
*
*/
