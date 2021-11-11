// $Id: test-item-FuelScoop.cpp,v 1.4 2002/04/27 00:09:22 prolator Exp $
//
// fuel scoop class testing
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

#define FuelScoop_NAME "Fuel Scoop"
#define FuelScoop_TECHLEVEL 28
#define FuelScoop_MASS 46
#define FuelScoop_VOLUME 47
#define FuelScoop_SURFACE 78
#define FuelScoop_COST 34
#define FuelScoop_CAPACITY 842

void check_FuelScoop( TFuelScoop* FuelScoop, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the fuel scoop is empty";
  result = check_item( *FuelScoop,
                       TItem::FUELSCOOP,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);
  if ( result ) 
  {
    if ( FuelScoop->getScoopCapacity() != 0 )
    {
      cout << "fuel scoop capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  FuelScoop->setItemName("Fuel Scoop");
  FuelScoop->setTechLevel(FuelScoop_TECHLEVEL);
  FuelScoop->setMass(FuelScoop_MASS);
  FuelScoop->setVolume(FuelScoop_VOLUME);
  FuelScoop->setSurface(FuelScoop_SURFACE);
  dummySet.Add( *substance->Create(FuelScoop_COST) );
  FuelScoop->setCost( dummySet );
  dummySet.Clear();
  FuelScoop->setScoopCapacity(FuelScoop_CAPACITY);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(FuelScoop_COST) );
  result = check_item( *FuelScoop,
                       TItem::FUELSCOOP,
                       "Fuel Scoop",
                       FuelScoop_TECHLEVEL,
                       FuelScoop_MASS,
                       FuelScoop_VOLUME,
                       FuelScoop_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FuelScoop->getScoopCapacity() != FuelScoop_CAPACITY )
    {
      cout << "fuel scoop capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TFuelScoop object.\n";
  TFuelScoop* testScoop = new TFuelScoop();
  cout << "*** Now I check the operator=";  
  *testScoop = *FuelScoop;
  dummySet.Add( *substance->Create(FuelScoop_COST) );
  result = check_item( *testScoop,
                       TItem::FUELSCOOP,
                       "Fuel Scoop",
                       FuelScoop_TECHLEVEL,
                       FuelScoop_MASS,
                       FuelScoop_VOLUME,
                       FuelScoop_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FuelScoop->getScoopCapacity() != FuelScoop_CAPACITY )
    {
      cout << "fuel scoop capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TFuelScoop object again.\n";
  delete testScoop;
  cout << "*** Now I use the copy constructor.\n";
  testScoop = new TFuelScoop( *FuelScoop );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(FuelScoop_COST) );
  result = check_item( *testScoop,
                       TItem::FUELSCOOP,
                       "Fuel Scoop",
                       FuelScoop_TECHLEVEL,
                       FuelScoop_MASS,
                       FuelScoop_VOLUME,
                       FuelScoop_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FuelScoop->getScoopCapacity() != FuelScoop_CAPACITY )
    {
      cout << "fuel scoop capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScoop == *FuelScoop );


  cout << "*** Now I destruct the TFuelScoop object again.\n";
  delete testScoop;
} // check_FuelScoop



/*
 * $Log: test-item-FuelScoop.cpp,v $
 * Revision 1.4  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.3  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.2  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.1  2001/06/15 23:25:13  prolator
 * test for fuel scoop
 *
 */
