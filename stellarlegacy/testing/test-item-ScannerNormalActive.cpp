// $Id: test-item-ScannerNormalActive.cpp,v 1.9 2002/04/27 00:09:22 prolator Exp $
//
// active normal scanner class testing
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

#define ScannerNormalActive_NAME "Active Normal Scanner"
#define ScannerNormalActive_TECHLEVEL 10
#define ScannerNormalActive_MASS 12
#define ScannerNormalActive_VOLUME 6
#define ScannerNormalActive_SURFACE 17
#define ScannerNormalActive_COST 17
#define ScannerNormalActive_EFFICIENCY 78
#define ScannerNormalActive_SHORTRANGE 20000
#define ScannerNormalActive_LONGRANGE 20

void check_ScannerNormalActive( TScannerNormalActive* ScannerNormalActive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the active normal scanner is empty";
  result = check_item( *ScannerNormalActive,
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
    if ( ScannerNormalActive->getScannerType() != TScanner::NORMAL_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getScanEfficiency() != 0 )
    {
      cout << "active normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getShortRange() != 0 )
    {
      cout << "active normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getLongRange() != 0 )
    {
      cout << "active normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerNormalActive->setItemName(ScannerNormalActive_NAME);
  ScannerNormalActive->setTechLevel(ScannerNormalActive_TECHLEVEL);
  ScannerNormalActive->setMass(ScannerNormalActive_MASS);
  ScannerNormalActive->setVolume(ScannerNormalActive_VOLUME);
  ScannerNormalActive->setSurface(ScannerNormalActive_SURFACE);
  dummySet.Add( *substance->Create(ScannerNormalActive_COST) );
  ScannerNormalActive->setCost( dummySet );
  dummySet.Clear();
  ScannerNormalActive->setScanEfficiency(ScannerNormalActive_EFFICIENCY);
  ScannerNormalActive->setShortRange(ScannerNormalActive_SHORTRANGE);
  ScannerNormalActive->setLongRange(ScannerNormalActive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerNormalActive_COST) );
  result = check_item( *ScannerNormalActive,
                       TItem::SCANNER,
                       ScannerNormalActive_NAME,
                       ScannerNormalActive_TECHLEVEL,
                       ScannerNormalActive_MASS,
                       ScannerNormalActive_VOLUME,
                       ScannerNormalActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerNormalActive->getScannerType() != TScanner::NORMAL_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getScanEfficiency() != ScannerNormalActive_EFFICIENCY )
    {
      cout << "active normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getShortRange() != ScannerNormalActive_SHORTRANGE )
    {
      cout << "active normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getLongRange() != ScannerNormalActive_LONGRANGE )
    {
      cout << "active normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerNormalActive object.\n";
  TScannerNormalActive* testScanner = new TScannerNormalActive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerNormalActive;
  dummySet.Add( *substance->Create(ScannerNormalActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerNormalActive_NAME,
                       ScannerNormalActive_TECHLEVEL,
                       ScannerNormalActive_MASS,
                       ScannerNormalActive_VOLUME,
                       ScannerNormalActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerNormalActive->getScannerType() != TScanner::NORMAL_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getScanEfficiency() != ScannerNormalActive_EFFICIENCY )
    {
      cout << "active normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getShortRange() != ScannerNormalActive_SHORTRANGE )
    {
      cout << "active normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getLongRange() != ScannerNormalActive_LONGRANGE )
    {
      cout << "active normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerNormalActive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerNormalActive( *ScannerNormalActive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerNormalActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerNormalActive_NAME,
                       ScannerNormalActive_TECHLEVEL,
                       ScannerNormalActive_MASS,
                       ScannerNormalActive_VOLUME,
                       ScannerNormalActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerNormalActive->getScannerType() != TScanner::NORMAL_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getScanEfficiency() != ScannerNormalActive_EFFICIENCY )
    {
      cout << "active normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getShortRange() != ScannerNormalActive_SHORTRANGE )
    {
      cout << "active normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalActive->getLongRange() != ScannerNormalActive_LONGRANGE )
    {
      cout << "active normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerNormalActive );


  cout << "*** Now I destruct the TScannerNormalActive object again.\n";
  delete testScanner;
} // check_ScannerNormalActive



/*
 * $Log: test-item-ScannerNormalActive.cpp,v $
 * Revision 1.9  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.8  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.7  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.6  2001/06/24 14:59:46  prolator
 * added tests for range
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
 * Revision 1.1  2001/06/10 22:48:30  prolator
 * tests for item sub classes now in independent files
 *
 */
