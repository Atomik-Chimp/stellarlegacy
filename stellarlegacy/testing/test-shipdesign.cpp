// $Id: test-shipdesign.cpp,v 1.31 2002/05/10 10:40:43 mkrohn5 Exp $
//
// ship design class testing
// Written by: Ralf Laue, <ralf.laue@gmx.de>
//
// Copyright (C) 2001 Ralf Laue, <ralf.laue@gmx.de>
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

#include "gamelogic/shipdesign.h"
#include "gamelogic/modules/subfleet_basic.h"
#include <fstream>
#include "testing/testing.h"


static bool check_design( const TShipDesign& DesignToCheck,
                          const int2 subfleets,
                          const bool changeable,
                          const bool canLand,
                          const double factor,
                          const string name,
                          const int4 hullmass,
                          const int4 totalmass,
                          const int2 hullvolume,
                          const int2 freevolume,
                          const int2 hullsurface,
                          const int2 freesurface,
                          const int2 hitpoints,
                          const TSubstanceSet& hullcost,
                          const TSubstanceSet& designcost )
{
  bool itemOK = true;
  TSubstanceSet dummySubstanceSet;

  // check all fields inherited from TShipDesign

  if ( DesignToCheck.getType() != TType::SHIPDESIGN )
  {
    cout << "type (TType) wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getTypeName() != "TShipDesign")
  {
    cout << "type name (TType) wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getUsageNumber() != subfleets)
  {
    cout << "subfleets wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.isChangeable() != changeable)
  {
    cout << "isChangeable wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.isAtmospheric() != canLand)
  {
    cout << "isAtmospheric is  wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getAtmosphericFactor() != factor)
  {
    cout << "Atmosphericfactor is wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getDesignName() != name)
  {
    cout << "DesignName wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getHullMass() != hullmass)
  {
    cout << "hull mass wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getTotalMass() != totalmass)
  {
    cout << DesignToCheck.getTotalMass() << "total mass wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getHullVolume() != hullvolume)
  {
    cout << "hull volume wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getFreeVolume() != freevolume)
  {
    cout <<  DesignToCheck.getFreeVolume() << "free volume wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getHullSurface() != hullsurface)
  {
    cout << "hull surface wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getFreeSurface() != freesurface)
  {
    cout << DesignToCheck.getFreeSurface()  << "free surface wrong!\n";
    itemOK = false;
  } // if
  if ( DesignToCheck.getMaxHullHP() != hitpoints)
  {
    cout << "hull hp wrong!\n";
    itemOK = false;
  } // if
  DesignToCheck.getHullCost( &dummySubstanceSet );
  if ( dummySubstanceSet != hullcost)
  {
    cout << "hull cost wrong!\n";
    itemOK = false;
  } // if
  DesignToCheck.getDesignCost( &dummySubstanceSet );
  if ( dummySubstanceSet != designcost )
  {
    cout << "design cost wrong!\n";
    itemOK = false;
  } // if

  return itemOK;                       // if one failed, return false, else true
} // check_design

static bool check_item( const TItem& ItemToCheck,
                        const TItem::tItemType type,
                        const string name,
                        const int2 techLevel,
                        const int2 mass,
                        const int2 volume,
                        const int2 surface,
                        const TSubstanceSet& cost)
{
  bool itemOK = true;
  TSubstanceSet dummySubstanceSet;

  // check all fields inherited from TItem

  if ( ItemToCheck.getType() != TType::ITEM )
  {
    cout << "type (TType) wrong!\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getTypeName() != "TItem" )
  {
    cout << "type name (TType) wrong!\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getItemType() != type)
  {
    cout << "item type wrong!\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getItemName() != name)
  {
    cout << "item name wrong!\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getTechLevel() != techLevel)
  {
    cout << "tech level wrong\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getMass() != mass)
  {
    cout << "item mass wrong\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getVolume() != volume)
  {
    cout << "item volume wrong\n";
    itemOK = false;
  } // if
  if ( ItemToCheck.getSurface() != surface)
  {
    cout << "item surface wrong!\n";
    itemOK = false;
  } // if
  ItemToCheck.getCost( &dummySubstanceSet );
  if ( dummySubstanceSet != cost )
  {
    cout << "item cost wrong!\n";
    itemOK = false;
  } // if

  return itemOK;                       // if one failed, return false, else true
} // check_item


#include "test-item-STLEngine.cpp"
#include "test-item-FTLEngine.cpp"
#include "test-item-FuelTank.cpp"
#include "test-item-FuelScoop.cpp"
#include "test-item-CargoBay.cpp"
#include "test-item-Colonizer.cpp"
#include "test-item-RepairBot.cpp"
#include "test-item-KWeapon.cpp"
#include "test-item-EWeapon.cpp"
#include "test-item-TargetingComputer.cpp"
#include "test-item-ScannerNormalActive.cpp"
#include "test-item-ScannerNormalPassive.cpp"
#include "test-item-ScannerAntiDisguiseActive.cpp"
#include "test-item-ScannerAntiDisguisePassive.cpp"
#include "test-item-ScannerAntiCloakActive.cpp"
#include "test-item-ScannerAntiCloakPassive.cpp"
#include "test-item-ScannerPenetrateActive.cpp"
#include "test-item-ScannerPenetratePassive.cpp"
#include "test-item-JammerNormal.cpp"
#include "test-item-JammerDisguise.cpp"
#include "test-item-JammerCloak.cpp"
#include "test-item-JammerAntiPenetrate.cpp"
#include "test-item-MineLayer.cpp"
#include "test-item-MiningBot.cpp"
#include "test-item-FighterLauncher.cpp"
#include "test-item-SPWeaponLauncher.cpp"

bool TestShipDesignClass()
{
  bool result;
  TTesting test;

  cout << "*** During this test I create a test ship design with\n";
  cout << "*** items on it. During and after the building I'll\n";
  cout << "*** check, whether the values are correct\n";
  cout << "*** \n";
  cout << "*** But before I start, I need to create a substance type.\n";
  TSubstanceType* GSchalen = new TSubstanceType("Gurkenschalen", "GS", 0, 1, 1);
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  // ************** create ship design and check basic functions *****************

  cout << "*** \n";
  cout << "*** At first I create the new ship design.\n";

  TShipDesign* testDesign;
  testDesign = new TShipDesign();

  cout << "*** Then I check whether the design is empty";
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "",
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             TSubstanceSet(),
                             TSubstanceSet()));


  cout << "*** Now I will assign the ship design some basic values.\n";
  testDesign->setDesignName("Battleship");
  testDesign->setHullMass(1000000);
  testDesign->setHullVolume(20000);
  testDesign->setHullSurface(15000);
  testDesign->setMaxHullHP(1200);
  dummySet.Add( *GSchalen->Create(20) );
  testDesign->setHullCost( dummySet );
  dummySet.Clear();

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(20) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1000000,
                             20000,
                             20000,
                             15000,
                             15000,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  // ************************** start building items *****************************

  cout << "*** \n";
  cout << "*** Now I start to create items and to put them onto the\n";
  cout << "*** ship design.\n";

  // build STL engine

  cout << "*************************************************************\n";
  cout << "*** Now I create a new empty TSTLEngine object\n";
  TSTLEngine STLEngine;
  check_STLEngine( &STLEngine, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 2 STL engines onto the design.\n";
  testDesign->AddItem( &STLEngine, 2);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(22) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1000400,
                             20000,
                             19960,
                             15000,
                             14940,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build FTL engine

  cout << "*************************************************************\n";
  cout << "*** Now I create a new empty TSTLEngine object\n";
  TFTLEngine FTLEngine;
  check_FTLEngine( &FTLEngine, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 1 FTL engines onto the design.\n";
  testDesign->AddItem( &FTLEngine, 1);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(25) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1000550,
                             20000,
                             19930,
                             15000,
                             14928,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build fuel tank

  cout << "*************************************************************\n";
  cout << "*** Now I create a new empty fuel tank\n";
  TFuelTank FuelTank;
  check_FuelTank( &FuelTank, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 3 fuel tanks onto the design.\n";
  testDesign->AddItem( &FuelTank, 3);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(37) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1000571,
                             20000,
                             19918,
                             15000,
                             14925,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build fuel scoop

  cout << "*************************************************************\n";
  cout << "*** Now I create a new empty fuel scoop\n";
  TFuelScoop FuelScoop;
  check_FuelScoop( &FuelScoop, GSchalen, test );

  // and check updated ship design
  // IMPORTANT: 0 fuel scoops are added to test what happens
 
  cout << "*** \n";
  cout << "*** Now I put 0 fuel scoops onto the design.\n";
  testDesign->AddItem( &FuelScoop, 0);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(37) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1000571,
                             20000,
                             19918,
                             15000,
                             14925,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build cargo bay

  cout << "*************************************************************\n";
  cout << "*** Now I create a new cargo bay.\n";
  TCargoBay CargoBay;
  check_CargoBay( &CargoBay, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 4 cargo bay modules onto the design.\n";
  testDesign->AddItem( &CargoBay, 4);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(41) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1000575,
                             20000,
                             19910,
                             15000,
                             14925,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build colonization module

  cout << "*************************************************************\n";
  cout << "*** Now I create a colonization module.\n";
  TColonizer Colonizer;
  check_Colonizer( &Colonizer, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 6 colonization modules onto the design.\n";
  testDesign->AddItem( &Colonizer, 6);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(4001) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001175,
                             20000,
                             18410,
                             15000,
                             14565,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  // build repair module

  cout << "*************************************************************\n";
  cout << "*** Now I create a repair module.\n";
  TRepairBot RepairBot;
  check_RepairBot( &RepairBot, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 5 repair modules onto the design.\n";
  testDesign->AddItem( &RepairBot, 5);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(4171) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001200,
                             20000,
                             18300,
                             15000,
                             14550,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build kinectic weapon

  cout << "*************************************************************\n";
  cout << "*** Now I create a kinetic weapon.\n";
  TKWeapon KWeapon;
  check_KWeapon( &KWeapon, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 7 kinetic weapons onto the design.\n";
  testDesign->AddItem( &KWeapon, 7 );
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(4766) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001263,
                             20000,
                             18132,
                             15000,
                             14508,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build energy weapon

  cout << "*************************************************************\n";
  cout << "*** Now I create a energy weapon.\n";
  TEWeapon EWeapon;
  check_EWeapon( &EWeapon, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 8 energy weapons onto the design.\n";
  testDesign->AddItem( &EWeapon, 8 );
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5302) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001511,
                             20000,
                             17724,
                             15000,
                             14404,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build targeting computer

  cout << "*************************************************************\n";
  cout << "*** Now I create a targeting computer.\n";
  TTargetingComputer TargetingComputer;
  check_TargetingComputer( &TargetingComputer, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 9 targeting computer onto the design.\n";
  testDesign->AddItem( &TargetingComputer, 9);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5374) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001628,
                             20000,
                             17598,
                             15000,
                             14404,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build active normal scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a active normal scanner.\n";
  TScannerNormalActive ScannerNormalActive;
  check_ScannerNormalActive( &ScannerNormalActive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 5 active normal scanners onto the design.\n";
  testDesign->AddItem( &ScannerNormalActive, 5);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5459) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001688,
                             20000,
                             17568,
                             15000,
                             14319,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build passive normal scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a passive normal scanner.\n";
  TScannerNormalPassive ScannerNormalPassive;
  check_ScannerNormalPassive( &ScannerNormalPassive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 4 passive normal scanners onto the design.\n";
  testDesign->AddItem( &ScannerNormalPassive, 4);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5471) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1001752,
                             20000,
                             17556,
                             15000,
                             14295,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build active anti disguise scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a active anti disguise scanner.\n";
  TScannerAntiDisguiseActive ScannerAntiDisguiseActive;
  check_ScannerAntiDisguiseActive( &ScannerAntiDisguiseActive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 7 active anti disguise scanners onto the design.\n";
  testDesign->AddItem( &ScannerAntiDisguiseActive, 7);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5632) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002053,
                             20000,
                             17507,
                             15000,
                             14260,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build passive anti disguise scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a passive anti disguise scanner.\n";
  TScannerAntiDisguisePassive ScannerAntiDisguisePassive;
  check_ScannerAntiDisguisePassive( &ScannerAntiDisguisePassive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 3 passive anti disguise scanners onto the design.\n";
  testDesign->AddItem( &ScannerAntiDisguisePassive, 3);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5773) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002092,
                             20000,
                             17489,
                             15000,
                             14248,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build active anti cloak scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a active anti cloak scanner.\n";
  TScannerAntiCloakActive ScannerAntiCloakActive;
  check_ScannerAntiCloakActive( &ScannerAntiCloakActive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 2 active anti cloak scanners onto the design.\n";
  testDesign->AddItem( &ScannerAntiCloakActive, 2);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(5871) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002122,
                             20000,
                             17479,
                             15000,
                             14244,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build passive anti cloak scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a passive anti cloak scanner.\n";
  TScannerAntiCloakPassive ScannerAntiCloakPassive;
  check_ScannerAntiCloakPassive( &ScannerAntiCloakPassive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 6 passive anti cloak scanners onto the design.\n";
  testDesign->AddItem( &ScannerAntiCloakPassive, 6);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6093) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002164,
                             20000,
                             17455,
                             15000,
                             14214,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  // build active penetrate scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a active penetrate scanner.\n";
  TScannerPenetrateActive ScannerPenetrateActive;
  check_ScannerPenetrateActive( &ScannerPenetrateActive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 1 active penetrate scanners onto the design.\n";
  testDesign->AddItem( &ScannerPenetrateActive, 1);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6122) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002209,
                             20000,
                             17451,
                             15000,
                             14205,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build passive penetrate scanner

  cout << "*************************************************************\n";
  cout << "*** Now I create a passive penetrate scanner.\n";
  TScannerPenetratePassive ScannerPenetratePassive;
  check_ScannerPenetratePassive( &ScannerPenetratePassive, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 3 passive penetrate scanners onto the design.\n";
  testDesign->AddItem( &ScannerPenetratePassive, 3);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6215) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002308,
                             20000,
                             17436,
                             15000,
                             14184,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build normal jammer

  cout << "*************************************************************\n";
  cout << "*** Now I create a normal jammer.\n";
  TJammerNormal JammerNormal;
  check_JammerNormal( &JammerNormal, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 11 normal jammers onto the design.\n";
  testDesign->AddItem( &JammerNormal, 11);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6446) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002473,
                             20000,
                             17348,
                             15000,
                             14107,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build disguise jammer

  cout << "*************************************************************\n";
  cout << "*** Now I create a disguise jammer.\n";
  TJammerDisguise JammerDisguise;
  check_JammerDisguise( &JammerDisguise, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 4 disguise jammers onto the design.\n";
  testDesign->AddItem( &JammerDisguise, 4);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6562) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1002613,
                             20000,
                             17328,
                             15000,
                             14095,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build cloak jammer

  cout << "*************************************************************\n";
  cout << "*** Now I create a cloak jammer.\n";
  TJammerCloak JammerCloak;
  check_JammerCloak( &JammerCloak, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 6 cloak jammers onto the design.\n";
  testDesign->AddItem( &JammerCloak, 6);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6748) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1003015,
                             20000,
                             17310,
                             15000,
                             14065,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build anti penetrate jammer

  cout << "*************************************************************\n";
  cout << "*** Now I create a anti penetrate jammer.\n";
  TJammerAntiPenetrate JammerAntiPenetrate;
  check_JammerAntiPenetrate( &JammerAntiPenetrate, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 3 anti penetrate jammers onto the design.\n";
  testDesign->AddItem( &JammerAntiPenetrate, 3);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6877) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1003270,
                             20000,
                             17277,
                             15000,
                             14053,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build mine layer

  cout << "*************************************************************\n";
  cout << "*** Now I create a mine layer.\n";
  TMineLayer MineLayer;
  check_MineLayer( &MineLayer, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 2 mine layers onto the design.\n";
  testDesign->AddItem( &MineLayer, 2);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(6967) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1003360,
                             20000,
                             17253,
                             15000,
                             13999,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build mining bot

  cout << "*************************************************************\n";
  cout << "*** Now I create a mining bot.\n";
  TMiningBot MiningBot;
  check_MiningBot( &MiningBot, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 5 mining bots onto the design.\n";
  testDesign->AddItem( &MiningBot, 5);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(7347) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1003685,
                             20000,
                             16933,
                             15000,
                             13659,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build fighter launcher

  cout << "*************************************************************\n";
  cout << "*** Now I create a fighter launcher\n";
  TFighterLauncher FighterLauncher;
  check_FighterLauncher( &FighterLauncher, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 2 fighter launchers onto the design.\n";
  testDesign->AddItem( &FighterLauncher, 2);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(8917) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1004095,
                             20000,
                             15919,
                             15000,
                             13551,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // build SP weapon launcher

  cout << "*************************************************************\n";
  cout << "*** Now I create a SP weapon launcher\n";
  TSPWeaponLauncher SPWeaponLauncher;
  check_SPWeaponLauncher( &SPWeaponLauncher, GSchalen, test );

  // and check updated ship design

  cout << "*** \n";
  cout << "*** Now I put 4 SPWeapon launchers onto the design.\n";
  testDesign->AddItem( &SPWeaponLauncher, 4);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(10857) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1004635,
                             20000,
                             15095,
                             15000,
                             13343,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  // now testing TArmor & TDefenseType & TShield
  // this is done in an extra file, but not in an extra function for scope reasons
#include "test-item-Armor.cpp"
#include "test-item-Shield.cpp"




  // now testing TShipDesign
  // test RemoveItem (AddItem was used all the time above)
  cout << "*************************************************************\n";
  cout << "*************************************************************\n";
  cout << "*** Now all item tests are done. Now the ship design class\n";
  cout << "*** will be tested.\n";
  cout << "*** First I check RemoveItem. I remove 4 energy weapons.\n";
  int dummyInt = testDesign->RemoveItem ( &EWeapon, 4 );
  cout << "*** Now I check whether exactly 4 weapons were removed";
  test.report( dummyInt == 4 );
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(33399) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1004946,
                             20000,
                             15237,
                             15000,
                             13318,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();



  cout << "*** \n";
  cout << "*** RemoveItem again: I try to remove 9 kinetic weapons.\n";
  dummyInt = testDesign->RemoveItem ( &KWeapon, 9 );
  cout << "*** Now I check whether exactly 7 weapons were removed";
  test.report(dummyInt == 7);
  cout << "*** Now I check whether the design has the correct values";
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(32804) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             false,
                             0,
                             "Battleship",
                             1000000,
                             1004883,
                             20000,
                             15405,
                             15000,
                             13360,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();


  // check getItemList

  cout << "*** Now I check getItemList of TShipDesign\n";
  cout << "*** First I create a TPList<TItemPack> object.\n";
  TPList<TItemPack> ItemList;
  cout << "*** Then I get a list with all weapons from th ship design.\n";
  testDesign->getItemList( &ItemList, TItem::EWEAPON | TItem:: KWEAPON );
  cout << "*** Then I check, whether the list is correct\n";
  result = true;
  if ( ItemList.size() != 1 ) 
  {
    result = false;
    cout << "list size wrong!\n";
  } // if
  if ( (*ItemList.begin())->getItem()->getItemType() != TItem::EWEAPON )
  {
    result = false;
    cout << (*ItemList.begin())->getItem()->getItemType() << "item type wrong!\n";
  } // if
  if ( (*ItemList.begin())->getItemAmount() != 4 )
  {
    result = false;
    cout << "item amount wrong!\n";
  } // if
  test.report( result );

  cout << "*** \n";

  // check whether nothing happened as 0 fuel scoops were added (see above)

  cout << "*** Now I check whether there were fuel scoops.\n";
  testDesign->getItemList( &ItemList, TItem::FUELSCOOP );
  cout << "*** Then I check, whether the list is correct\n";
  result = true;
  if ( !ItemList.empty() ) 
  {
    result = false;
    cout << "list size wrong, should be empty!\n";
  } // if
  test.report( result );

  cout << "*** \n";

  // empty the ItemList
  ItemList.setAutoDeleteMode( true );
  ItemList.deleteAll();


  // check of Atmospheric
  
  cout << "*** \n";
  cout << "*************************************************************\n";
  cout << "*** Now I check Atmospheric. First I set it.\n";
  testDesign->AbleToLand( true );
  cout << "*** Now I check the ship design";  
  dummySet.Add( *GSchalen->Create(20) );
  dummySet2.Add( *GSchalen->Create(32804) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             true,
                             0,
                             "Battleship",
                             1000000,
                             1004883,
                             20000,
                             15405,
                             15000,
                             13360,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  cout << "*************************************************************\n";
  cout << "*** Now I change the Atmospheric factor\n";
  testDesign->setAtmosphericFactor( 0.25 );
  cout << "*** Now I check the ship design";  
  dummySet.Add( *GSchalen->Create(25) );
  dummySet2.Add( *GSchalen->Create(32809) );
  test.report( check_design( *testDesign,
                             0,
                             true,
                             true,
                             0.25,
                             "Battleship",
                             1000000,
                             1004883,
                             20000,
                             15405,
                             15000,
                             13360,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  // check of Changeable

  cout << "*** \n";
  cout << "*************************************************************\n";
  cout << "*** Now I create a subfleet (tested elsewhere) and try to change the values.\n";

  /* FIXME
  TSubFleetBasic* testSubfleet = new TSubFleetBasic(testDesign, 1);
  testDesign->AbleToLand( false );
  testDesign->setAtmosphericFactor( 0.5 );
  testDesign->setDesignName("Battleship II");
  testDesign->setHullMass(100000);
  testDesign->setHullVolume(2000);
  testDesign->setHullSurface(1500);
  testDesign->setMaxHullHP(120);
  dummySet.Add( *GSchalen->Create(40) );
  testDesign->setHullCost( dummySet );
  dummySet.Clear();

  cout << "*** Now I check the ship design";
  dummySet.Add( *GSchalen->Create(25) );
  dummySet2.Add( *GSchalen->Create(32809) );
  test.report( check_design( *testDesign,
                             1,
                         false,
                         true,
                         0.25,
                         "Battleship",
                         1000000,
                         1004883,
                         20000,
                         15405,
                         15000,
                         13360,
                         1200,
                         dummySet,
                         dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  cout << "*** Finally I destruct the subfleet\n";
  delete testSubfleet;
  */
  // check operator=

  cout << "*** \n";
  cout << "*************************************************************\n";
  cout << "*** Now a new TShipDesign object is created.\n";
  TShipDesign* testDesign2 = new TShipDesign();
  cout << "*** Now I check the operator=";  
  *testDesign2 = *testDesign;
  dummySet.Add( *GSchalen->Create(25) );
  dummySet2.Add( *GSchalen->Create(32809) );
  test.report( check_design( *testDesign2,
                             0,
                             true, // FIXME false,
                             true,
                             0.25,
                             "Battleship",
                             1000000,
                             1004883,
                             20000,
                             15405,
                             15000,
                             13360,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();
  cout << "*** Now I destruct the TShipDesign object again.\n";
  delete testDesign2;

  // test copy constructor

  cout << "*** Now I use the copy constructor.\n";
  testDesign2 = new TShipDesign( *testDesign );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *GSchalen->Create(25) );
  dummySet2.Add( *GSchalen->Create(32809) );
  test.report( check_design( *testDesign2,
                             0,
                             true, // FIXME false,
                             true,
                             0.25,
                             "Battleship",
                             1000000,
                             1004883,
                             20000,
                             15405,
                             15000,
                             13360,
                             1200,
                             dummySet,
                             dummySet2));
  dummySet.Clear();
  dummySet2.Clear();

  cout << "*** Now I destruct the TShipDesign object again.\n";
  delete testDesign2;


  // testing Load and Save
  cout << "*************************************************************\n";
  cout << "*** Now testing Load and Save of TShipDesign.\n";
  cout << "*** Creating testDesign2 again\n";
  testDesign2 = new TShipDesign();
  cout << "*** Now creating an TDataPackageList object.\n";
  TDataPackageList* dataList = new TDataPackageList();
  cout << "*** Now I save the old ship design\n";
  testDesign->save( dataList );

  ofstream out( "testfile.txt" );
  dataList->save( out );
  out.close();

// FIXME: uncomment the following lines "===>" if
// Load(...) really works
//===>  cout << "*** Now deleting the datalist" << endl;
//===>  delete dataList;

  cout << "*** Now I load it into the second design\n";
//===>  dataList = new TDataPackageList();
  testDesign2->load( dataList );
  //==>  cout << "*** Now I check whether it worked";


  //  dummySet.Add( *GSchalen->Create(25) );
  //  dummySet2.Add( *GSchalen->Create(32809) );
  //  test.report( check_design( *testDesign2,
  //                         1,
  //                         false,
  //                         true,
  //                         0.25,
  //                         "Battleship",
  //                         1000000,
  //                         1004883,
  //                         20000,
  //                         15405,
  //                         15000,
  //                         13360,
  //                         1200,
  //                         dummySet,
  //                         dummySet2));
  //  dummySet.Clear();
  //  dummySet2.Clear();


  cout << "*** Now deleting the datalist" << endl;
  delete dataList;


  cout << "*** Now I destruct the TShipDesign object again.\n";
  delete testDesign2;

  cout << "*** \n";
  cout << "*** \n";
  cout << "*** \n";
  cout << "*** deleting first TShipDesign object\n";
  delete testDesign;

  cout << "*** Now destruct armorType1 and shieldType1\n";
  delete armorType1;
  delete shieldType1;


  return test.result();
}


/*
 * $Log: test-shipdesign.cpp,v $
 * Revision 1.31  2002/05/10 10:40:43  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.30  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.29  2002/04/25 22:22:33  prolator
 * finally found and killed the bug
 *
 * Revision 1.28  2002/04/02 22:32:28  prolator
 * some Xet to xet
 *
 * Revision 1.27  2002/03/24 13:39:07  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.26  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.25  2001/12/02 14:21:58  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.24  2001/06/29 01:06:38  mkrohn5
 * a few modifications to make the tests work correctly (still a bug left which needs further attention)
 *
 * Revision 1.23  2001/06/23 23:53:33  prolator
 * commented buggy part out
 *
 * Revision 1.22  2001/06/23 09:56:45  prolator
 * added testing for Load/Save
 *
 * Revision 1.21  2001/06/21 21:51:24  prolator
 * adjusted test to new implementation in TShipDesign: TPList<TItemPack>
 *
 * Revision 1.20  2001/06/17 11:10:48  prolator
 * adjusted tests to GetMaxHullHP instead of GetMaxHullDP
 *
 * Revision 1.19  2001/06/16 21:38:03  prolator
 * adjusted to new counter of subfleets in ship design
 *
 * Revision 1.18  2001/06/15 23:25:45  prolator
 * added test for fuel scoop
 *
 * Revision 1.17  2001/06/15 13:55:18  prolator
 * adjusted tests to new classes TArmorType and TShieldType
 *
 * Revision 1.16  2001/06/14 12:01:37  prolator
 * adjusted test to tLinkList in TShipDesign
 *
 * Revision 1.15  2001/06/13 15:47:13  prolator
 * added tests for flags Changeable and Atmospheric
 *
 * Revision 1.14  2001/06/12 21:38:20  prolator
 * coreected tests of costs
 *
 * Revision 1.13  2001/06/12 15:53:09  prolator
 * added tests for shields and methods RemoveItem and GetItemList of TShipDesign
 *
 * Revision 1.12  2001/06/12 13:51:36  prolator
 * change from TArmorType to TDefenseType
 *
 * Revision 1.11  2001/06/12 11:52:19  prolator
 * tests for armor added
 *
 * Revision 1.10  2001/06/11 14:28:40  prolator
 * added test for tech level of items
 *
 * Revision 1.9  2001/06/11 13:15:48  prolator
 * added the rest of the item sub class test (only armor and shield missing
 *
 * Revision 1.8  2001/06/10 23:35:03  prolator
 * added the rest of the tests for the jammer classes
 *
 * Revision 1.7  2001/06/10 22:49:13  prolator
 * added a few more item sub classes tests
 *
 * Revision 1.6  2001/06/10 17:41:03  prolator
 * new version with item sub classes tests in extra files
 *
 * Revision 1.5  2001/06/07 13:59:57  prolator
 * small changes, so it works with the new versions of TItem and its sub classes
 *
 * Revision 1.4  2001/05/21 23:26:54  prolator
 * added tests for operator= and copy constructor
 *
 * Revision 1.3  2001/05/19 19:46:10  prolator
 * added first version of tests for the items - ship design relation
 *
 * Revision 1.2  2001/05/17 14:18:57  prolator
 * Added tests for GetType and GetTypeName (inherited from TType and reimplemented in TShipDesign)
 *
 * Revision 1.1  2001/05/17 12:47:38  prolator
 * File for testing of TShipDesign and TItem
 *
 */
