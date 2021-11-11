// $Id: test-item-ScannerAntiDisguiseActive.cpp,v 1.9 2002/04/27 00:09:22 prolator Exp $
//
// active anti disguise scanner class testing
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

#define ScannerAntiDisguiseActive_NAME "Active anti Disguise Scanner"
#define ScannerAntiDisguiseActive_TECHLEVEL 12
#define ScannerAntiDisguiseActive_MASS 43
#define ScannerAntiDisguiseActive_VOLUME 7
#define ScannerAntiDisguiseActive_SURFACE 5
#define ScannerAntiDisguiseActive_COST 23
#define ScannerAntiDisguiseActive_EFFICIENCY 76
#define ScannerAntiDisguiseActive_SHORTRANGE 70000
#define ScannerAntiDisguiseActive_LONGRANGE 80

void check_ScannerAntiDisguiseActive( TScannerAntiDisguiseActive* ScannerAntiDisguiseActive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Check whether the active anti disguise scanner is empty";
  result = check_item( *ScannerAntiDisguiseActive,
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
    if ( ScannerAntiDisguiseActive->getScannerType() != TScanner::ANTIDISGUISE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getScanEfficiency() != 0 )
    {
      cout << "active anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getShortRange() != 0 )
    {
      cout << "active anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getLongRange() != 0 )
    {
      cout << "active anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerAntiDisguiseActive->setItemName(ScannerAntiDisguiseActive_NAME);
  ScannerAntiDisguiseActive->setTechLevel(ScannerAntiDisguiseActive_TECHLEVEL);
  ScannerAntiDisguiseActive->setMass(ScannerAntiDisguiseActive_MASS);
  ScannerAntiDisguiseActive->setVolume(ScannerAntiDisguiseActive_VOLUME);
  ScannerAntiDisguiseActive->setSurface(ScannerAntiDisguiseActive_SURFACE);
  dummySet.Add( *substance->Create(ScannerAntiDisguiseActive_COST) );
  ScannerAntiDisguiseActive->setCost( dummySet );
  dummySet.Clear();
  ScannerAntiDisguiseActive->setScanEfficiency(ScannerAntiDisguiseActive_EFFICIENCY);
  ScannerAntiDisguiseActive->setShortRange(ScannerAntiDisguiseActive_SHORTRANGE);
  ScannerAntiDisguiseActive->setLongRange(ScannerAntiDisguiseActive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerAntiDisguiseActive_COST) );
  result = check_item( *ScannerAntiDisguiseActive,
                       TItem::SCANNER,
                       ScannerAntiDisguiseActive_NAME,
                       ScannerAntiDisguiseActive_TECHLEVEL,
                       ScannerAntiDisguiseActive_MASS,
                       ScannerAntiDisguiseActive_VOLUME,
                       ScannerAntiDisguiseActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiDisguiseActive->getScannerType() != TScanner::ANTIDISGUISE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getScanEfficiency() != ScannerAntiDisguiseActive_EFFICIENCY )
    {
      cout << "active anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getShortRange() != ScannerAntiDisguiseActive_SHORTRANGE )
    {
      cout << "active anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getLongRange() != ScannerAntiDisguiseActive_LONGRANGE )
    {
      cout << "active anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerAntiDisguiseActive object.\n";
  TScannerAntiDisguiseActive* testScanner = new TScannerAntiDisguiseActive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerAntiDisguiseActive;
  dummySet.Add( *substance->Create(ScannerAntiDisguiseActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiDisguiseActive_NAME,
                       ScannerAntiDisguiseActive_TECHLEVEL,
                       ScannerAntiDisguiseActive_MASS,
                       ScannerAntiDisguiseActive_VOLUME,
                       ScannerAntiDisguiseActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiDisguiseActive->getScannerType() != TScanner::ANTIDISGUISE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getScanEfficiency() != ScannerAntiDisguiseActive_EFFICIENCY )
    {
      cout << "active anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getShortRange() != ScannerAntiDisguiseActive_SHORTRANGE )
    {
      cout << "active anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getLongRange() != ScannerAntiDisguiseActive_LONGRANGE )
    {
      cout << "active anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerAntiDisguiseActive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerAntiDisguiseActive( *ScannerAntiDisguiseActive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerAntiDisguiseActive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiDisguiseActive_NAME,
                       ScannerAntiDisguiseActive_TECHLEVEL,
                       ScannerAntiDisguiseActive_MASS,
                       ScannerAntiDisguiseActive_VOLUME,
                       ScannerAntiDisguiseActive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiDisguiseActive->getScannerType() != TScanner::ANTIDISGUISE_ACTIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getScanEfficiency() != ScannerAntiDisguiseActive_EFFICIENCY )
    {
      cout << "active anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getShortRange() != ScannerAntiDisguiseActive_SHORTRANGE )
    {
      cout << "active anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguiseActive->getLongRange() != ScannerAntiDisguiseActive_LONGRANGE )
    {
      cout << "active anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerAntiDisguiseActive );


  cout << "*** Now I destruct the TScannerAntiDisguiseActive object again.\n";
  delete testScanner;
} // check_ScannerAntiDisguiseActive



/*
 * $Log: test-item-ScannerAntiDisguiseActive.cpp,v $
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
 * Revision 1.2  2001/06/10 23:34:03  prolator
 * tests for item sub classes now in independent files
 *
 * Revision 1.1  2001/06/10 22:48:30  prolator
 * tests for item sub classes now in independent files
 *
 */
