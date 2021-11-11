// $Id: test-item-EWeapon.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
//
// energy weapon class testing
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


#define EWeapon_NAME "Energy Weapon"
#define EWeapon_TECHLEVEL 8
#define EWeapon_MASS 31
#define EWeapon_VOLUME 51
#define EWeapon_SURFACE 13
#define EWeapon_COST 67
#define EWeapon_DP 41
#define EWeapon_ROF 25
#define EWeapon_RANGE 300000
#define EWeapon_TYPE 4

void check_EWeapon( TEWeapon* EWeapon, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the energy weapon is empty";
  result = check_item( *EWeapon,
                       TItem::EWEAPON,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( EWeapon->getDamagePoints() != 0 )
    {
      cout << "damage points wrong!\n";
      result = false;
    } // if
    if ( EWeapon->getRateOfFire() != 0 )
    {
      cout << "rate of fire wrong!\n";
      result = false;
    } // if
    if ( EWeapon->getEfficientRange() != 0 )
    {
      cout << "efficient range wrong!\n";
      result = false;
    } // if
    if ( EWeapon->getWeaponType() != 0 )
    {
      cout << "weapon type wrong!\n";
      result = false;
    } // if

  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  EWeapon->setItemName( EWeapon_NAME );
  EWeapon->setTechLevel(EWeapon_TECHLEVEL);
  EWeapon->setMass(EWeapon_MASS);
  EWeapon->setVolume(EWeapon_VOLUME);
  EWeapon->setSurface(EWeapon_SURFACE);
  dummySet.Add( *substance->Create(EWeapon_COST) );
  EWeapon->setCost( dummySet );
  dummySet.Clear();
  EWeapon->setDamagePoints(EWeapon_DP);
  EWeapon->setRateOfFire(EWeapon_ROF);
  EWeapon->setEfficientRange(EWeapon_RANGE);
  EWeapon->setWeaponType(EWeapon_TYPE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(EWeapon_COST) );
  result = check_item( *EWeapon,
                       TItem::EWEAPON,
                       EWeapon_NAME,
                       EWeapon_TECHLEVEL,
                       EWeapon_MASS,
                       EWeapon_VOLUME,
                       EWeapon_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( EWeapon->getDamagePoints() != EWeapon_DP )
    {
      cout << "!\n";
      result = false;
    } // if
    if ( EWeapon->getRateOfFire() != EWeapon_ROF )
    {
      cout << "!\n";
      result = false;
    } // if
    if ( EWeapon->getEfficientRange() != EWeapon_RANGE )
    {
      cout << "efficient range wrong!\n";
      result = false;
    } // if
    if ( EWeapon->getWeaponType() != EWeapon_TYPE )
    {
      cout << "!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TEWeapon object.\n";
  TEWeapon* testWeapon = new TEWeapon();
  cout << "*** Now I check the operator=";  
  *testWeapon = *EWeapon;
  dummySet.Add( *substance->Create(EWeapon_COST) );
  result = check_item( *testWeapon,
                       TItem::EWEAPON,
                       EWeapon_NAME,
                       EWeapon_TECHLEVEL,
                       EWeapon_MASS,
                       EWeapon_VOLUME,
                       EWeapon_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( EWeapon->getDamagePoints() != EWeapon_DP )
    {
      cout << "!\n";
      result = false;
    } // if
    if ( EWeapon->getRateOfFire() != EWeapon_ROF )
    {
      cout << "!\n";
      result = false;
    } // if
    if ( EWeapon->getEfficientRange() != EWeapon_RANGE )
    {
      cout << "efficient range wrong!\n";
      result = false;
    } // if
    if ( EWeapon->getWeaponType() != EWeapon_TYPE )
    {
      cout << "!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TEWeapon object again.\n";
  delete testWeapon;
  cout << "*** Now I use the copy constructor.\n";
  testWeapon = new TEWeapon( *EWeapon );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(EWeapon_COST) );
  result = check_item( *testWeapon,
                       TItem::EWEAPON,
                       EWeapon_NAME,
                       EWeapon_TECHLEVEL,
                       EWeapon_MASS,
                       EWeapon_VOLUME,
                       EWeapon_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( EWeapon->getDamagePoints() != EWeapon_DP )
    {
      cout << "!\n";
      result = false;
    } // if
    if ( EWeapon->getRateOfFire() != EWeapon_ROF )
    {
      cout << "!\n";
      result = false;
    } // if
    if ( EWeapon->getEfficientRange() != EWeapon_RANGE )
    {
      cout << "efficient range wrong!\n";
      result = false;
    } // if
    if ( EWeapon->getWeaponType() != EWeapon_TYPE )
    {
      cout << "!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testWeapon == *EWeapon );


  cout << "*** Now I destruct the TEWeapon object again.\n";
  delete testWeapon;
} // check_EWeapon



/*
 * $Log: test-item-EWeapon.cpp,v $
 * Revision 1.8  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.7  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.6  2001/07/05 20:34:18  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.5  2001/06/12 21:41:33  prolator
 * corrected range value
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
 * Revision 1.1  2001/06/10 21:29:56  prolator
 * tests for item sub classes now in independent files
 *
 */
