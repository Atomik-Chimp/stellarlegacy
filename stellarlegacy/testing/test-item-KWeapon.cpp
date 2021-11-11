// $Id: test-item-KWeapon.cpp,v 1.9 2002/04/27 00:09:22 prolator Exp $
//
// kinetic weapon class testing
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

#define KWeapon_NAME "Kinetic Weapon"
#define KWeapon_TECHLEVEL 7
#define KWeapon_MASS 9
#define KWeapon_VOLUME 24
#define KWeapon_SURFACE 6
#define KWeapon_COST 85
#define KWeapon_DP 56
#define KWeapon_ROF 10
#define KWeapon_VELOCITY 50000
#define KWeapon_SIZE 91
#define KWeapon_TYPE 7

void check_KWeapon( TKWeapon* KWeapon, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the kinetic weapon is empty";
  result = check_item( *KWeapon,
                       TItem::KWEAPON,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);
  if ( result ) 
  {
    if ( KWeapon->getDamagePoints() != 0 )
    {
      cout << "damage points wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getRateOfFire() != 0 )
    {
      cout << "rate of fire wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getVelocity() != 0 )
    {
      cout << "velocity wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getAmmunitionSize() != 0 )
    {
      cout << "ammunition size wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getWeaponType() != 0 )
    {
      cout << "weapon type wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  KWeapon->setItemName( KWeapon_NAME );
  KWeapon->setTechLevel(KWeapon_TECHLEVEL);
  KWeapon->setMass(KWeapon_MASS);
  KWeapon->setVolume(KWeapon_VOLUME);
  KWeapon->setSurface(KWeapon_SURFACE);
  dummySet.Add( *substance->Create(KWeapon_COST) );
  KWeapon->setCost( dummySet );
  dummySet.Clear();
  KWeapon->setDamagePoints(KWeapon_DP);
  KWeapon->setRateOfFire(KWeapon_ROF);
  KWeapon->setVelocity(KWeapon_VELOCITY);
  KWeapon->setAmmunitionSize(KWeapon_SIZE);
  KWeapon->setWeaponType(KWeapon_TYPE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(KWeapon_COST) );
  result = check_item( *KWeapon,
                       TItem::KWEAPON,
                       KWeapon_NAME,
                       KWeapon_TECHLEVEL,
                       KWeapon_MASS,
                       KWeapon_VOLUME,
                       KWeapon_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( KWeapon->getDamagePoints() != KWeapon_DP )
    {
      cout << "damage points wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getRateOfFire() != KWeapon_ROF )
    {
      cout << "rate of fire wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getVelocity() != KWeapon_VELOCITY )
    {
      cout << "velocity wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getAmmunitionSize() != KWeapon_SIZE )
    {
      cout << "ammunition size wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getWeaponType() != KWeapon_TYPE )
    {
      cout << "weapon type wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TKWeapon object.\n";
  TKWeapon* testWeapon = new TKWeapon();
  cout << "*** Now I check the operator=";  
  *testWeapon = *KWeapon;
  dummySet.Add( *substance->Create(KWeapon_COST) );
  result = check_item( *testWeapon,
                       TItem::KWEAPON,
                       KWeapon_NAME,
                       KWeapon_TECHLEVEL,
                       KWeapon_MASS,
                       KWeapon_VOLUME,
                       KWeapon_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( KWeapon->getDamagePoints() != KWeapon_DP )
    {
      cout << "damage points wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getRateOfFire() != KWeapon_ROF )
    {
      cout << "rate of fire wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getVelocity() != KWeapon_VELOCITY )
    {
      cout << "velocity wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getAmmunitionSize() != KWeapon_SIZE )
    {
      cout << "ammunition size wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getWeaponType() != KWeapon_TYPE )
    {
      cout << "weapon type wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TKWeapon object again.\n";
  delete testWeapon;
  cout << "*** Now I use the copy constructor.\n";
  testWeapon = new TKWeapon( *KWeapon );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(KWeapon_COST) );
  result = check_item( *testWeapon,
                       TItem::KWEAPON,
                       KWeapon_NAME,
                       KWeapon_TECHLEVEL,
                       KWeapon_MASS,
                       KWeapon_VOLUME,
                       KWeapon_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( KWeapon->getDamagePoints() != KWeapon_DP )
    {
      cout << "damage points wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getRateOfFire() != KWeapon_ROF )
    {
      cout << "rate of fire wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getVelocity() != KWeapon_VELOCITY )
    {
      cout << "velocity wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getAmmunitionSize() != KWeapon_SIZE )
    {
      cout << "ammunition size wrong!\n";
      result = false;
    } // if
    if ( KWeapon->getWeaponType() != KWeapon_TYPE )
    {
      cout << "weapon type wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testWeapon == *KWeapon );


  cout << "*** Now I destruct the TKWeapon object again.\n";
  delete testWeapon;
} // check_KWeapon



/*
 * $Log: test-item-KWeapon.cpp,v $
 * Revision 1.9  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.8  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.7  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.6  2001/06/12 21:41:18  prolator
 * corrected velocity value
 *
 * Revision 1.5  2001/06/12 14:13:42  prolator
 * added test for operator==
 *
 * Revision 1.4  2001/06/11 15:00:21  prolator
 * fixed a bug (one assignment too much after copy constructor)
 *
 * Revision 1.3  2001/06/11 14:27:58  prolator
 * added tests for tech level of items
 *
 * Revision 1.2  2001/06/10 23:37:42  prolator
 * corrected mistake in comments
 *
 * Revision 1.1  2001/06/10 21:29:56  prolator
 * tests for item sub classes now in independent files
 *
 */
