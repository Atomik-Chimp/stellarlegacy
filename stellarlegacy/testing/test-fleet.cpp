// $Id: test-fleet.cpp,v 1.8 2002/05/15 08:30:55 ishark Exp $
//
// fleet class testing
// Written by: Ralf Laue
//
// Copyright (C) 2001 - , Ralf Laue <ralf.laue@gmx.de>
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

#include "gamelogic/modules/fleet_basic.h"
#include "gamelogic/modules/subfleet_basic.h"
#include "gamelogic/galaxy.h"
#include "gamelogic/shipdesign.h"
#include "common/point.h"

static int2 success;
static int2 checksdone;


static
void report(const bool check)
{
  cout << ((check)? "Success" : "FAILED") << endl;
  checksdone++;
  success += check;
}


static bool check_fleet( const TFleetBasic* FleetToCheck,
                         const int4 NumberOfShips )
{
  bool fleetOK = true;

  if ( FleetToCheck->getType() != TType::FLEET )
  {
    fleetOK = false;
    cout << "object type wrong!\n";
  }
  if ( FleetToCheck->getTypeName() != "TFleet" )
  {
    fleetOK = false;
    cout << "object type name wrong!\n";
  }
  if ( FleetToCheck->getNumberOfShips() != NumberOfShips )
  {
    fleetOK = false;
    cout << "number of ships wrong! It is " << FleetToCheck->getNumberOfShips() <<"\n";
  }

  return fleetOK;
}


bool TestFleetClass()
{
  bool result = true;
  success = 0;
  checksdone = 0;
  

  // create a subfleet for testing
  cout << "*** First create a fleet (and other needed classes) for testing.\n";
  cout << "*** Create a galaxy.\n";
  TGalaxy* testGalaxy = new TGalaxy( "name", TPoint( 1, 2, 3 ), true, true, true );
  cout << "*** Create a fleet.\n";
  TFleetBasic* testFleet = new TFleetBasic();
  cout << "*** Now I add the fleet to the galaxy.\n";
  testGalaxy->addStellarObject( testFleet ); // FIXME, this is necessary until stobj is changed

  cout << "*************************************************************\n";
  cout << "*** Now I check the created fleet                            --> ";
  result = check_fleet( testFleet,
                        0 );
  report( result );  
  
  cout << "*************************************************************\n";
  cout << "*** Now I create and add two subfleets.\n";
  TShipDesign* testDesign = new TShipDesign();
  TSubFleetBasic* testSubfleet = new TSubFleetBasic( testDesign, 20 );
  TSubFleetBasic* testSubfleet2 = new TSubFleetBasic( testDesign, 10 );
  testFleet->Add( testSubfleet );
  testFleet->Add( testSubfleet2 );
  cout << "*** Now I check the fleet again                             --> ";
  result = check_fleet( testFleet,
                        30 );
  report( result );
  



  cout << "*** \n";
  cout << "*** Now I destruct the galaxy (and its content).\n";
  delete testGalaxy;
  delete testDesign;

  return success == checksdone;
}

/*
 * $Log: test-fleet.cpp,v $
 * Revision 1.8  2002/05/15 08:30:55  ishark
 * actionsequencer now uses lists + cosmetic fixes
 *
 * Revision 1.7  2002/05/10 10:40:42  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.6  2002/01/28 01:12:14  mkrohn5
 * changes because of making TLinkUpdate a singleton
 *
 * Revision 1.5  2001/12/07 00:21:15  mkrohn5
 * - converted galaxy to the new style
 * - galaxy now uses the stellar object list (the code is now a lot more readable :-)
 * - made TStellarObjectList a list instead of a deque (makes list operations a lot faster)
 *
 * Revision 1.4  2001/12/01 17:21:15  mkrohn5
 * fixed a few include pathes
 *
 * Revision 1.3  2001/06/29 01:05:23  mkrohn5
 * uncommented some tests which seem to work--have to investigate further though
 *
 * Revision 1.2  2001/06/24 17:01:30  mkrohn5
 * a small fix due to api changes
 *
 * Revision 1.1  2001/06/23 23:23:29  prolator
 * first version of fleet test
 *
 */
