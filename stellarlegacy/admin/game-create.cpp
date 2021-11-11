// $Id: game-create.cpp,v 1.9 2002/07/12 10:00:46 mkrohn5 Exp $

// Game Create Code File
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
#include "admin/game-create.h"
#include "admin/parser-use.h"
#include "common/point.h"
#include "gamelogic/race.h"
#include "common/random.h"
#include "gamelogic/rulesystem.h"
#include "gamelogic/system.h"
#include "gamelogic/universe.h"





//----------------------------------------  class TGameCreate  ----------------------------------------

TGameCreate :: TGameCreate( const string& gameDir, const string& gameName )
  : TGame( gameDir, gameName )
{
}



bool TGameCreate :: createGame()
{
  // reset...
  resetLoadLevel();
  fTransitions.clear();                                    // actually not neccessary (but let's be paranoid ;-)

  // define the needed transition table for loading the universe definition file
  // blocktype, current loadlevel, new loadlevel, function to call
  fTransitions.push_back( tTransition("rulesystem", 0, 2, &TGame::PDBRuleSystem) );
  fTransitions.push_back( tTransition("player", 2, 3, &TGame::PDBPlayer) );
  fTransitions.push_back( tTransition("player", 3, 3, &TGame::PDBPlayer) );
  fTransitions.push_back( tTransition("race", 3, 4, &TGame::PDBRace) );
  fTransitions.push_back( tTransition("race", 4, 4, &TGame::PDBRace) );
  fTransitions.push_back( tTransition("item", 4, 5, &TGame::PDBItem) );
  fTransitions.push_back( tTransition("item", 5, 5, &TGame::PDBItem) );
  fTransitions.push_back( tTransition("game", 5, 6, &TGame::PDBGame) );
  fTransitions.push_back( tTransition("", -1, -1, 0) );

  // finaly invoke the parser which results in call backs to the method
  // "processDataBlock"
  bool result = ReadFile( this, FSpecUniverseDefinition() );

  // cleaning up the transition table
  fTransitions.clear();

  return result;
}





//----------------------------------------  protected  ----------------------------------------

// virtual method
void TGameCreate :: PDBGame( TDataPackageList* block )
{
TPoint GalaxySize;
int4 GalaxySystems;
string gameName;
bool bCheck = true;

  LOG("TGameCreate","PDBGame") << "create new GAME!!" << endl;
  LOG_BEGIN_INDENT();

  bCheck &= block->getAndDelete( "name", &gameName, true );                   // unique=true
  bCheck &= block->getAndDelete( "galaxy_size", &GalaxySize, true );          // unique=true
  bCheck &= block->getAndDelete( "galaxy_systems", &GalaxySystems, true );    // unique=true
  if ( !bCheck )
    Fatal("TGameCreate", "PDBGame", "Missing parameters for game initialization", -1);

  // set some data
  setGameName( gameName );
  setTurn( 0 );

  // create the "super"-race
  TRace* race = TRuleSystem::instance().createRace();
  race->setName( "Iluvatar" );
  addRace( race );
  fIluvatar.setDest( race );

  // create galaxy
  TGalaxy* galaxy = new TGalaxy( "milkyway", GalaxySize );
  TUniverse::instance()->addGalaxy( galaxy );                   // and add it to the universe

  // create the systems
  TPoint Pos;
  TSystem* pSystem;
  int4 i;

  for (i = 0; i < GalaxySystems; i++)
  {
    Pos.setX( 100.0*TRandom::getDouble() );
    Pos.setY( 100.0*TRandom::getDouble() );
    pSystem = TRuleSystem::instance().createSystem();
    pSystem->setPos( Pos );
    galaxy->addStellarObject( pSystem );
    pSystem->setCreator( fIluvatar.getPointerToDest() );
    pSystem->setOwner( fIluvatar.getPointerToDest() );

    // DELETE: remove the next few lines (FIXME)
    if ( i == 0 )  pSystem->setName( "Antares" );
    else if ( i == 2 )  pSystem->setName( "Canopus" );
    else if ( i == GalaxySystems-1 )  pSystem->setName( "Zibal" );
    else pSystem->setName( "unnamed" );
  }

  // DELETE: add one fleet (basic ruleset)  FIXME
  TFleet* pFleet = TRuleSystem::instance().createFleet();
  pFleet->setPos( TPoint(20, 20) );
  pFleet->addWaypoint( TWaypoint(pSystem, 35.0) );
  pFleet->addWaypoint( TWaypoint(TPoint(30,30), 15.0) );
  pFleet->addWaypoint( TWaypoint(TPoint(60,30), 15.0) );
  pFleet->addWaypoint( TWaypoint(pSystem, 2.0) );
  pFleet->setName("SL-One");

  // assign the race to the races
  // (note: done manually) is there a reason to have a "search by name"
  // method for races?
  TPList<TRace>::const_iterator ri;

  for ( ri = getRaces().begin(); ri != getRaces().end(); ++ri )  {
    if ( (*ri)->getName() == "Albertians")  break;
  }
  if ( ri == getRaces().end() )  {
    Fatal("TGame", "PDBCreteGame", "Albertians undefined in test game?!?", -1);
  }

  pFleet->setOwner(*ri);
  pFleet->setCreator(*ri);

  galaxy->addStellarObject( pFleet );

  // DELETE: add one fleet (basic ruleset)
  pFleet = TRuleSystem::instance().createFleet();
  pFleet->addWaypoint( TWaypoint(pSystem, 35.0) );
  pFleet->addWaypoint( TWaypoint(TPoint(20,20), 1.0) );
  pFleet->addWaypoint( TWaypoint(TPoint(60,20), 3.0) );
  pFleet->addWaypoint( TWaypoint(pSystem, 5.0) );
  pFleet->setName("SL-Two");

  for (ri = getRaces().begin(); ri != getRaces().end(); ++ri)  {
    if ( (*ri)->getName() == "Marconians")  break;
  }
  if ( ri == getRaces().end() )  {
    Fatal("TGame", "PDBCreteGame", "Marconians undefined in test game?!?", -1);
  }

  pFleet->setOwner(*ri);
  pFleet->setCreator(*ri);

  galaxy->addStellarObject( pFleet );


  // and two more fleets flying towards each other
  TFleet* fleet3 = TRuleSystem::instance().createFleet();
  TFleet* fleet4 = TRuleSystem::instance().createFleet();
  fleet3->setName( "conflict-tester1" );
  fleet4->setName( "conflict-tester2" );
  fleet3->setPos( TPoint(0,0) );
  fleet4->setPos( TPoint(50,50) );
  fleet3->addWaypoint( TWaypoint(fleet4, 10.0) );
  fleet4->addWaypoint( TWaypoint(fleet3, 20.0) );
  fleet3->setOwner(*ri);
  fleet3->setCreator(*ri);
  fleet4->setOwner(*ri);
  fleet4->setCreator(*ri);
  galaxy->addStellarObject( fleet3 );
  galaxy->addStellarObject( fleet4 );

  LOG_END_INDENT();
}





/*
* $Log: game-create.cpp,v $
* Revision 1.9  2002/07/12 10:00:46  mkrohn5
* include path + upper->lower fixes
*
* Revision 1.8  2002/06/23 11:15:07  mkrohn5
* - added a two more fleets (to test conflict resolution--he,he a play of words :-)
* - enhanced the code for generating fleet movement actions
*
* Revision 1.7  2002/06/21 08:31:57  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.6  2002/06/07 00:31:32  mkrohn5
* added wanted speed to the fleet waypoints
*
* Revision 1.5  2002/06/05 11:23:20  mkrohn5
* give the systems a position in space
*
* Revision 1.4  2002/06/05 00:30:16  mkrohn5
* changed TRuleSystem::instance
*
* Revision 1.3  2002/05/11 23:54:38  mkrohn5
* added "super"-race iluvatar, the owner of the galaxies, systems, ...
*
* Revision 1.2  2002/05/10 23:44:07  mkrohn5
* bug fix in the transition table
*
* Revision 1.1  2002/05/10 10:27:41  mkrohn5
* split TGame in several new classes (see ChangeLog)
*
*/

