// $Id: test-item-ScannerAntiCloakActive.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
//
// active anti cloak scanner class testing
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

#define ScannerAntiCloakActive_NAME "Active anti Cloak Scanner"
#define ScannerAntiCloakActive_TECHLEVEL 14
#define ScannerAntiCloakActive_MASS 15
#define ScannerAntiCloakActive_VOLUME 5
#define ScannerAntiCloakActive_SURFACE 2
#define ScannerAntiCloakActive_COST 49
#define ScannerAntiCloakActive_EFFICIENCY 54
#define ScannerAntiCloakActive_SHORTRANGE 300000
#define ScannerAntiCloakActive_LONGRANGE 2

void check_ScannerAntiCloakActive( TScannerAntiCloakActive* ScannerAntiCloakActive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Check whether the active anti cloak scanner is empty";
  result = check_item( *ScannerAntiCloakActive,
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
    if ( ScannerAntiCloakActive->getScannerType() != TScanner::ANTICLOAK_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getScanEfficiency() != 0 )
    {
      cout << "active anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getShortRange() != 0 )
    {
      cout << "active anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getLongRange() != 0 )
    {
      cout << "active anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if
  test.report( result );

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerAntiCloakActive->setItemName(ScannerAntiCloakActive_NAME);
  ScannerAntiCloakActive->setTechLevel(ScannerAntiCloakActive_TECHLEVEL);
  ScannerAntiCloakActive->setMass(ScannerAntiCloakActive_MASS);
  ScannerAntiCloakActive->setVolume(ScannerAntiCloakActive_VOLUME);
  ScannerAntiCloakActive->setSurface(ScannerAntiCloakActive_SURFACE);
  dummySet.Add( *substance->Create(ScannerAntiCloakActive_COST) );
  ScannerAntiCloakActive->setCost( dummySet );
  dummySet.Clear();
  ScannerAntiCloakActive->setScanEfficiency(ScannerAntiCloakActive_EFFICIENCY);
  ScannerAntiCloakActive->setShortRange(ScannerAntiCloakActive_SHORTRANGE);
  ScannerAntiCloakActive->setLongRange(ScannerAntiCloakActive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerAntiCloakActive_COST) );
  result = check_item( *ScannerAntiCloakActive,
                       TItem::SCANNER,
                       ScannerAntiCloakActive_NAME,
                       ScannerAntiCloakActive_TECHLEVEL,
                       ScannerAntiCloakActive_MASS,
                       ScannerAntiCloakActive_VOLUME,
                       ScannerAntiCloakActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakActive->getScannerType() != TScanner::ANTICLOAK_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getScanEfficiency() != ScannerAntiCloakActive_EFFICIENCY )
    {
      cout << "active anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getShortRange() != ScannerAntiCloakActive_SHORTRANGE )
    {
      cout << "active anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getLongRange() != ScannerAntiCloakActive_LONGRANGE )
    {
      cout << "active anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerAntiCloakActive object.\n";
  TScannerAntiCloakActive* testScanner = new TScannerAntiCloakActive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerAntiCloakActive;
  dummySet.Add( *substance->Create(ScannerAntiCloakActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiCloakActive_NAME,
                       ScannerAntiCloakActive_TECHLEVEL,
                       ScannerAntiCloakActive_MASS,
                       ScannerAntiCloakActive_VOLUME,
                       ScannerAntiCloakActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakActive->getScannerType() != TScanner::ANTICLOAK_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getScanEfficiency() != ScannerAntiCloakActive_EFFICIENCY )
    {
      cout << "active anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getShortRange() != ScannerAntiCloakActive_SHORTRANGE )
    {
      cout << "active anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getLongRange() != ScannerAntiCloakActive_LONGRANGE )
    {
      cout << "active anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerAntiCloakActive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerAntiCloakActive( *ScannerAntiCloakActive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerAntiCloakActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiCloakActive_NAME,
                       ScannerAntiCloakActive_TECHLEVEL,
                       ScannerAntiCloakActive_MASS,
                       ScannerAntiCloakActive_VOLUME,
                       ScannerAntiCloakActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiCloakActive->getScannerType() != TScanner::ANTICLOAK_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getScanEfficiency() != ScannerAntiCloakActive_EFFICIENCY )
    {
      cout << "active anti cloak scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getShortRange() != ScannerAntiCloakActive_SHORTRANGE )
    {
      cout << "active anti cloak short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiCloakActive->getLongRange() != ScannerAntiCloakActive_LONGRANGE )
    {
      cout << "active anti cloak long scan range wrong!\n";
      result = false;
    } // if
  } // if


  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerAntiCloakActive );


  cout << "*** Now I destruct the TScannerAntiCloakActive object again.\n";
  delete testScanner;
} // check_ScannerAntiCloakActive



/*
 * $Log: test-item-ScannerAntiCloakActive.cpp,v $
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
