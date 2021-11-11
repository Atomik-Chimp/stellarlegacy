// $Id: test-item-ScannerAntiCloakPassive.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
//
// passive anti cloak scanner class testing
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

#define ScannerAntiCloakPassive_NAME "Passive anti Cloak Scanner"
#define ScannerAntiCloakPassive_TECHLEVEL 15
#define ScannerAntiCloakPassive_MASS 7
#define ScannerAntiCloakPassive_VOLUME 4
#define ScannerAntiCloakPassive_SURFACE 5
#define ScannerAntiCloakPassive_COST 37
#define ScannerAntiCloakPassive_EFFICIENCY 97
#define ScannerAntiCloakPassive_SHORTRANGE 600000
#define ScannerAntiCloakPassive_LONGRANGE 5

void check_ScannerAntiCloakPassive( TScannerAntiCloakPassive* ScannerAntiCloakPassive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Check whether the passive anti cloak scanner is empty";
  result = check_item( *ScannerAntiCloakPassive,
                       TItem::SCANNER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakPassive->getScannerType() != TScanner::ANTICLOAK_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getScanEfficiency() != 0 )
    {
      cout << "passive anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getShortRange() != 0 )
    {
      cout << "passive anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getLongRange() != 0 )
    {
      cout << "passive anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerAntiCloakPassive->setItemName(ScannerAntiCloakPassive_NAME);
  ScannerAntiCloakPassive->setTechLevel(ScannerAntiCloakPassive_TECHLEVEL);
  ScannerAntiCloakPassive->setMass(ScannerAntiCloakPassive_MASS);
  ScannerAntiCloakPassive->setVolume(ScannerAntiCloakPassive_VOLUME);
  ScannerAntiCloakPassive->setSurface(ScannerAntiCloakPassive_SURFACE);
  dummySet.Add( *substance->Create(ScannerAntiCloakPassive_COST) );
  ScannerAntiCloakPassive->setCost( dummySet );
  dummySet.Clear();
  ScannerAntiCloakPassive->setScanEfficiency(ScannerAntiCloakPassive_EFFICIENCY);
  ScannerAntiCloakPassive->setShortRange(ScannerAntiCloakPassive_SHORTRANGE);
  ScannerAntiCloakPassive->setLongRange(ScannerAntiCloakPassive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerAntiCloakPassive_COST) );
  result = check_item( *ScannerAntiCloakPassive,
                       TItem::SCANNER,
                       ScannerAntiCloakPassive_NAME,
                       ScannerAntiCloakPassive_TECHLEVEL,
                       ScannerAntiCloakPassive_MASS,
                       ScannerAntiCloakPassive_VOLUME,
                       ScannerAntiCloakPassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakPassive->getScannerType() != TScanner::ANTICLOAK_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getScanEfficiency() != ScannerAntiCloakPassive_EFFICIENCY )
    {
      cout << "passive anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getShortRange() != ScannerAntiCloakPassive_SHORTRANGE )
    {
      cout << "passive anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getLongRange() != ScannerAntiCloakPassive_LONGRANGE )
    {
      cout << "passive anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerAntiCloakPassive object.\n";
  TScannerAntiCloakPassive* testScanner = new TScannerAntiCloakPassive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerAntiCloakPassive;
  dummySet.Add( *substance->Create(ScannerAntiCloakPassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiCloakPassive_NAME,
                       ScannerAntiCloakPassive_TECHLEVEL,
                       ScannerAntiCloakPassive_MASS,
                       ScannerAntiCloakPassive_VOLUME,
                       ScannerAntiCloakPassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakPassive->getScannerType() != TScanner::ANTICLOAK_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getScanEfficiency() != ScannerAntiCloakPassive_EFFICIENCY )
    {
      cout << "passive anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getShortRange() != ScannerAntiCloakPassive_SHORTRANGE )
    {
      cout << "passive anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getLongRange() != ScannerAntiCloakPassive_LONGRANGE )
    {
      cout << "passive anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerAntiCloakPassive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerAntiCloakPassive( *ScannerAntiCloakPassive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerAntiCloakPassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiCloakPassive_NAME,
                       ScannerAntiCloakPassive_TECHLEVEL,
                       ScannerAntiCloakPassive_MASS,
                       ScannerAntiCloakPassive_VOLUME,
                       ScannerAntiCloakPassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakPassive->getScannerType() != TScanner::ANTICLOAK_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getScanEfficiency() != ScannerAntiCloakPassive_EFFICIENCY )
    {
      cout << "passive anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getShortRange() != ScannerAntiCloakPassive_SHORTRANGE )
    {
      cout << "passive anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakPassive->getLongRange() != ScannerAntiCloakPassive_LONGRANGE )
    {
      cout << "passive anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerAntiCloakPassive );


  cout << "*** Now I destruct the TScannerAntiCloakPassive object again.\n";
  delete testScanner;
} // check_ScannerAntiCloakPassive



/*
 * $Log: test-item-ScannerAntiCloakPassive.cpp,v $
 * Revision 1.8  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.7  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.6  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.5  2001/06/24 14:59:46  prolator
 * added tests for range
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
 * Revision 1.1  2001/06/11 11:42:17  prolator
 * tests for item sub classes now in independent files
 *
 */
