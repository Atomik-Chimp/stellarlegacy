// $Id: test-item-ScannerPenetrateActive.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
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

#define ScannerPenetrateActive_NAME "Active Penetrate Scanner"
#define ScannerPenetrateActive_TECHLEVEL 16
#define ScannerPenetrateActive_MASS 45
#define ScannerPenetrateActive_VOLUME 4
#define ScannerPenetrateActive_SURFACE 9
#define ScannerPenetrateActive_COST 29
#define ScannerPenetrateActive_EFFICIENCY 56
#define ScannerPenetrateActive_SHORTRANGE 10000
#define ScannerPenetrateActive_LONGRANGE 6

void check_ScannerPenetrateActive( TScannerPenetrateActive* ScannerPenetrateActive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Check whether the active penetrate scanner is empty";
  result = check_item( *ScannerPenetrateActive,
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
    if ( ScannerPenetrateActive->getScannerType() != TScanner::PENETRATE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getScanEfficiency() != 0 )
    {
      cout << "active penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getShortRange() != 0 )
    {
      cout << "active penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getLongRange() != 0 )
    {
      cout << "active penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerPenetrateActive->setItemName(ScannerPenetrateActive_NAME);
  ScannerPenetrateActive->setTechLevel(ScannerPenetrateActive_TECHLEVEL);
  ScannerPenetrateActive->setMass(ScannerPenetrateActive_MASS);
  ScannerPenetrateActive->setVolume(ScannerPenetrateActive_VOLUME);
  ScannerPenetrateActive->setSurface(ScannerPenetrateActive_SURFACE);
  dummySet.Add( *substance->Create(ScannerPenetrateActive_COST) );
  ScannerPenetrateActive->setCost( dummySet );
  dummySet.Clear();
  ScannerPenetrateActive->setScanEfficiency(ScannerPenetrateActive_EFFICIENCY);
  ScannerPenetrateActive->setShortRange(ScannerPenetrateActive_SHORTRANGE);
  ScannerPenetrateActive->setLongRange(ScannerPenetrateActive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerPenetrateActive_COST) );
  result = check_item( *ScannerPenetrateActive,
                       TItem::SCANNER,
                       ScannerPenetrateActive_NAME,
                       ScannerPenetrateActive_TECHLEVEL,
                       ScannerPenetrateActive_MASS,
                       ScannerPenetrateActive_VOLUME,
                       ScannerPenetrateActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerPenetrateActive->getScannerType() != TScanner::PENETRATE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getScanEfficiency() != ScannerPenetrateActive_EFFICIENCY )
    {
      cout << "active penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getShortRange() != ScannerPenetrateActive_SHORTRANGE )
    {
      cout << "active penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getLongRange() != ScannerPenetrateActive_LONGRANGE )
    {
      cout << "active penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerPenetrateActive object.\n";
  TScannerPenetrateActive* testScanner = new TScannerPenetrateActive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerPenetrateActive;
  dummySet.Add( *substance->Create(ScannerPenetrateActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerPenetrateActive_NAME,
                       ScannerPenetrateActive_TECHLEVEL,
                       ScannerPenetrateActive_MASS,
                       ScannerPenetrateActive_VOLUME,
                       ScannerPenetrateActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerPenetrateActive->getScannerType() != TScanner::PENETRATE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getScanEfficiency() != ScannerPenetrateActive_EFFICIENCY )
    {
      cout << "active penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getShortRange() != ScannerPenetrateActive_SHORTRANGE )
    {
      cout << "active penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getLongRange() != ScannerPenetrateActive_LONGRANGE )
    {
      cout << "active penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerPenetrateActive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerPenetrateActive( *ScannerPenetrateActive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerPenetrateActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerPenetrateActive_NAME,
                       ScannerPenetrateActive_TECHLEVEL,
                       ScannerPenetrateActive_MASS,
                       ScannerPenetrateActive_VOLUME,
                       ScannerPenetrateActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerPenetrateActive->getScannerType() != TScanner::PENETRATE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getScanEfficiency() != ScannerPenetrateActive_EFFICIENCY )
    {
      cout << "active penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getShortRange() != ScannerPenetrateActive_SHORTRANGE )
    {
      cout << "active penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetrateActive->getLongRange() != ScannerPenetrateActive_LONGRANGE )
    {
      cout << "active penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerPenetrateActive );


  cout << "*** Now I destruct the TScannerPenetrateActive object again.\n";
  delete testScanner;
} // check_ScannerPenetrateActive



/*
 * $Log: test-item-ScannerPenetrateActive.cpp,v $
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
 * Revision 1.1  2001/06/10 23:34:03  prolator
 * tests for item sub classes now in independent files
 *
 */
