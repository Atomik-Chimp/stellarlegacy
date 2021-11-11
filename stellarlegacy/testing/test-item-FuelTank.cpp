// $Id: test-item-FuelTank.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// fuel tank class testing
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

#define FuelTank_TECHLEVEL 3

void check_FuelTank( TFuelTank* FuelTank, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the fuel tank is empty";
  result = check_item( *FuelTank,
                       TItem::FUELTANK,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);
  if ( result ) 
  {
    if ( FuelTank->getTankCapacity() != 0 )
    {
      cout << "fuel tank capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  FuelTank->setItemName("Fuel Tank");
  FuelTank->setTechLevel(FuelTank_TECHLEVEL);
  FuelTank->setMass(7);
  FuelTank->setVolume(4);
  FuelTank->setSurface(1);
  dummySet.Add( *substance->Create(4) );
  FuelTank->setCost( dummySet );
  dummySet.Clear();
  FuelTank->setTankCapacity(14);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(4) );
  result = check_item( *FuelTank,
                       TItem::FUELTANK,
                       "Fuel Tank",
                       FuelTank_TECHLEVEL,
                       7,
                       4,
                       1,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FuelTank->getTankCapacity() != 14 )
    {
      cout << "fuel tank capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TFuelTank object.\n";
  TFuelTank* testTank = new TFuelTank();
  cout << "*** Now I check the operator=";  
  *testTank = *FuelTank;
  dummySet.Add( *substance->Create(4) );
  result = check_item( *testTank,
                       TItem::FUELTANK,
                       "Fuel Tank",
                       FuelTank_TECHLEVEL,
                       7,
                       4,
                       1,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FuelTank->getTankCapacity() != 14 )
    {
      cout << "fuel tank capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TFuelTank object again.\n";
  delete testTank;
  cout << "*** Now I use the copy constructor.\n";
  testTank = new TFuelTank( *FuelTank );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(4) );
  result = check_item( *testTank,
                       TItem::FUELTANK,
                       "Fuel Tank",
                       FuelTank_TECHLEVEL,
                       7,
                       4,
                       1,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FuelTank->getTankCapacity() != 14 )
    {
      cout << "fuel tank capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==.";
  test.report( *testTank == *FuelTank );


  cout << "*** Now I destruct the TFuelTank object again.\n";
  delete testTank;
} // check_FuelTank



/*
 * $Log: test-item-FuelTank.cpp,v $
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
 * Revision 1.1  2001/06/10 17:39:53  prolator
 * tests for item sub classes now in independent files
 *
 */
