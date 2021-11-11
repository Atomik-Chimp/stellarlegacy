// $Id: test-subfleet.cpp,v 1.5 2001/12/02 14:21:58 mkrohn5 Exp $
//
// subfleet class testing
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

#include "gamelogic/modules/subfleet_basic.h"
#include "gamelogic/modules/fleet_basic.h"
#include "gamelogic/item.h"
#include "gamelogic/shipdesign.h"
#include "gamelogic/galaxy.h"
#include "common/point.h"
#include "common/datapackage.h"
#include "gamelogic/substance.h"

static int2 success;
static int2 checksdone;


static
void report(const bool check)
{
  cout << " ... " << ((check)? "Success" : "FAILED") << endl;
  checksdone++;
  success += check;
}



bool TestSubFleetClass()
{
  success = 0;
  checksdone = 0;

  /*
  TSubstanceType* Fuel = new TSubstanceType("Fuel", "Fu", 0, 1, 0);
  TSubstanceType* FTank = new TSubstanceType("Fuel Tank", "FT", 0, -1, 0);

  TSubstance* r = Fuel->Create(100); // temp container

  TSubstanceHold hold;

  TSubstance* sub;

  sub = FTank->Create(1000); hold.Add(*sub, r); delete sub;
  sub = Fuel->Create(1000); hold.Add(*sub, r); delete sub;

  cout << "hold: " << hold << endl;
  cout << "r: " << *r << endl;

  */
  /*  
  // create a subfleet for testing
  cout << "*** First create a subfleet (and other needed classes) for testing.\n";
  cout << "*** Create a TPoint object.\n";
  TPoint* testPoint = new TPoint( 1, 2, 3 );
  cout << "*** Create a galaxy.\n";
  TGalaxy* testGalaxy = new TGalaxy( *testPoint, true, true, true );
  cout << "*** Destruct the TPoint object.\n";
  delete testPoint;
  cout << "*** Create a ship design.\n";
  TShipDesign* testDesign = new TShipDesign();
  cout << "*** Create a fleet.\n";
  TFleetBasic* testFleet = new TFleetBasic( testGalaxy );
  cout << "*** Create the subfleet.\n";
  TSubFleetBasic* testSubfleet = new TSubFleetBasic( testFleet, testDesign );


  cout << "testing subfleet -->";
  report(result);

  // Marco: wenn man zuerst Subfleet löscht geht es, um den Bug zu bekommen, einfach
  //        "delete testSubfleet" auskommentieren.
  delete testSubfleet;
  delete testFleet;

  // cleaning up
  cout << "*** Destruct the galaxy (destructs also fleet and subfleet)..\n";
  delete testGalaxy;

  cout << "*** Destruct the ship design.\n";
  delete testDesign;


  */

  /*
  TCargoBay testBay;
  TShipDesign testDesign;
  testDesign.AddItem( &testBay, 20 );

  testSubfleet->SetShipDesign( &testDesign );
  testSubfleet->SetNumberOfShips( 30 );
  
  result = (testSubfleet->GetCargoSpace() == 600 );
  */











  return success == checksdone;
}



/*
 * $Log: test-subfleet.cpp,v $
 * Revision 1.5  2001/12/02 14:21:58  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.4  2001/12/01 17:21:15  mkrohn5
 * fixed a few include pathes
 *
 * Revision 1.3  2001/06/23 23:45:11  prolator
 * changed subfleet constructor call
 *
 */
