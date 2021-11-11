// $Id: test-item-SPWeaponLauncher.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// SP weapon launcher class testing
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

#define SPWeaponLauncher_NAME "SP Weapon Launcher"
#define SPWeaponLauncher_TECHLEVEL 25
#define SPWeaponLauncher_MASS 135
#define SPWeaponLauncher_VOLUME 206
#define SPWeaponLauncher_SURFACE 52
#define SPWeaponLauncher_COST 485
#define SPWeaponLauncher_LAUNCHRATE 59

void check_SPWeaponLauncher( TSPWeaponLauncher* SPWeaponLauncher, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the SP weapon launcher is empty      --> ";
  result = check_item( *SPWeaponLauncher,
                       TItem::SPWEAPONLAUNCHER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( SPWeaponLauncher->getLaunchRate() != 0 )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  SPWeaponLauncher->setItemName( SPWeaponLauncher_NAME );
  SPWeaponLauncher->setTechLevel(SPWeaponLauncher_TECHLEVEL);
  SPWeaponLauncher->setMass(SPWeaponLauncher_MASS);
  SPWeaponLauncher->setVolume(SPWeaponLauncher_VOLUME);
  SPWeaponLauncher->setSurface(SPWeaponLauncher_SURFACE);
  dummySet.Add( *substance->Create(SPWeaponLauncher_COST) );
  SPWeaponLauncher->setCost( dummySet );
  dummySet.Clear();
  SPWeaponLauncher->setLaunchRate(SPWeaponLauncher_LAUNCHRATE);

  cout << "*** Now I check whether the basic values are saved           --> ";
  dummySet.Add( *substance->Create(SPWeaponLauncher_COST) );
  result = check_item( *SPWeaponLauncher,
                       TItem::SPWEAPONLAUNCHER,
                       SPWeaponLauncher_NAME,
                       SPWeaponLauncher_TECHLEVEL,
                       SPWeaponLauncher_MASS,
                       SPWeaponLauncher_VOLUME,
                       SPWeaponLauncher_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( SPWeaponLauncher->getLaunchRate() != SPWeaponLauncher_LAUNCHRATE )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TSPWeaponLauncher object.\n";
  TSPWeaponLauncher* testLauncher = new TSPWeaponLauncher();
  cout << "*** Now I check the operator=                                --> ";  
  *testLauncher = *SPWeaponLauncher;
  dummySet.Add( *substance->Create(SPWeaponLauncher_COST) );
  result = check_item( *testLauncher,
                       TItem::SPWEAPONLAUNCHER,
                       SPWeaponLauncher_NAME,
                       SPWeaponLauncher_TECHLEVEL,
                       SPWeaponLauncher_MASS,
                       SPWeaponLauncher_VOLUME,
                       SPWeaponLauncher_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( SPWeaponLauncher->getLaunchRate() != SPWeaponLauncher_LAUNCHRATE )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TSPWeaponLauncher object again.\n";
  delete testLauncher;
  cout << "*** Now I use the copy constructor.\n";
  testLauncher = new TSPWeaponLauncher( *SPWeaponLauncher );
  cout << "*** Now I check whether it worked                            --> ";  
  dummySet.Add( *substance->Create(SPWeaponLauncher_COST) );
  result = check_item( *testLauncher,
                       TItem::SPWEAPONLAUNCHER,
                       SPWeaponLauncher_NAME,
                       SPWeaponLauncher_TECHLEVEL,
                       SPWeaponLauncher_MASS,
                       SPWeaponLauncher_VOLUME,
                       SPWeaponLauncher_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( SPWeaponLauncher->getLaunchRate() != SPWeaponLauncher_LAUNCHRATE )
    {
      cout << "launch rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==.                                  --> ";
  test.report( *testLauncher == *SPWeaponLauncher );


  cout << "*** Now I destruct the TSPWeaponLauncher object again.\n";
  delete testLauncher;
} // check_SPWeaponLauncher



/*
 * $Log: test-item-SPWeaponLauncher.cpp,v $
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
