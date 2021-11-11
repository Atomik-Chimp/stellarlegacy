// $Id: test-item-FighterLauncher.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// fighter launcher class testing
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

#define FighterLauncher_NAME "Fighter Launcher"
#define FighterLauncher_TECHLEVEL 24
#define FighterLauncher_MASS 205
#define FighterLauncher_VOLUME 507
#define FighterLauncher_SURFACE 54
#define FighterLauncher_COST 785
#define FighterLauncher_LAUNCHRATE 47
#define FighterLauncher_LANDINGRATE 84
#define FighterLauncher_REPAIRRATE 53

void check_FighterLauncher( TFighterLauncher* FighterLauncher, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the fighter launcher is empty";
  result = check_item( *FighterLauncher,
                       TItem::FIGHTERLAUNCHER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( FighterLauncher->getLaunchRate() != 0 )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getLandingRate() != 0 )
    {
      cout << "landing rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getRepairRate() != 0 )
    {
      cout << "repair rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  FighterLauncher->setItemName( FighterLauncher_NAME );
  FighterLauncher->setTechLevel(FighterLauncher_TECHLEVEL);
  FighterLauncher->setMass(FighterLauncher_MASS);
  FighterLauncher->setVolume(FighterLauncher_VOLUME);
  FighterLauncher->setSurface(FighterLauncher_SURFACE);
  dummySet.Add( *substance->Create(FighterLauncher_COST) );
  FighterLauncher->setCost( dummySet );
  dummySet.Clear();
  FighterLauncher->setLaunchRate(FighterLauncher_LAUNCHRATE);
  FighterLauncher->setLandingRate(FighterLauncher_LANDINGRATE);
  FighterLauncher->setRepairRate(FighterLauncher_REPAIRRATE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(FighterLauncher_COST) );
  result = check_item( *FighterLauncher,
                       TItem::FIGHTERLAUNCHER,
                       FighterLauncher_NAME,
                       FighterLauncher_TECHLEVEL,
                       FighterLauncher_MASS,
                       FighterLauncher_VOLUME,
                       FighterLauncher_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( FighterLauncher->getLaunchRate() != FighterLauncher_LAUNCHRATE )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getLandingRate() != FighterLauncher_LANDINGRATE )
    {
      cout << "landing rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getRepairRate() != FighterLauncher_REPAIRRATE )
    {
      cout << "repair rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TFighterLauncher object.\n";
  TFighterLauncher* testLauncher = new TFighterLauncher();
  cout << "*** Now I check the operator=";  
  *testLauncher = *FighterLauncher;
  dummySet.Add( *substance->Create(FighterLauncher_COST) );
  result = check_item( *testLauncher,
                       TItem::FIGHTERLAUNCHER,
                       FighterLauncher_NAME,
                       FighterLauncher_TECHLEVEL,
                       FighterLauncher_MASS,
                       FighterLauncher_VOLUME,
                       FighterLauncher_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( FighterLauncher->getLaunchRate() != FighterLauncher_LAUNCHRATE )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getLandingRate() != FighterLauncher_LANDINGRATE )
    {
      cout << "landing rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getRepairRate() != FighterLauncher_REPAIRRATE )
    {
      cout << "repair rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TFighterLauncher object again.\n";
  delete testLauncher;
  cout << "*** Now I use the copy constructor.\n";
  testLauncher = new TFighterLauncher( *FighterLauncher );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(FighterLauncher_COST) );
  result = check_item( *testLauncher,
                       TItem::FIGHTERLAUNCHER,
                       FighterLauncher_NAME,
                       FighterLauncher_TECHLEVEL,
                       FighterLauncher_MASS,
                       FighterLauncher_VOLUME,
                       FighterLauncher_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( FighterLauncher->getLaunchRate() != FighterLauncher_LAUNCHRATE )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getLandingRate() != FighterLauncher_LANDINGRATE )
    {
      cout << "landing rate wrong!\n";
      result = false;
    } // if
    if ( FighterLauncher->getRepairRate() != FighterLauncher_REPAIRRATE )
    {
      cout << "repair rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testLauncher == *FighterLauncher );


  cout << "*** Now I destruct the TFighterLauncher object again.\n";
  delete testLauncher;
} // check_FighterLauncher



/*
 * $Log: test-item-FighterLauncher.cpp,v $
 * Revision 1.7  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.6  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.5  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.4  2001/06/12 14:13:42  prolator
 * added test for operator==
 *
 * Revision 1.3  2001/06/11 15:00:21  prolator
 * fixed a bug (one assignment too much after copy constructor)
 *
 * Revision 1.2  2001/06/11 14:27:58  prolator
 * added tests for tech level of items
 *
 * Revision 1.1  2001/06/11 13:14:56  prolator
 * tests for item sub classes now in independent files
 *
 */
