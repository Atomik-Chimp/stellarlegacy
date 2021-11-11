// $Id: test-item-ScannerNormalPassive.cpp,v 1.9 2002/04/27 00:09:22 prolator Exp $
//
// passive normal scanner class testing
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

#define ScannerNormalPassive_NAME "Passive Normal Scanner"
#define ScannerNormalPassive_TECHLEVEL 11
#define ScannerNormalPassive_MASS 16
#define ScannerNormalPassive_VOLUME 3
#define ScannerNormalPassive_SURFACE 6
#define ScannerNormalPassive_COST 3
#define ScannerNormalPassive_EFFICIENCY 64
#define ScannerNormalPassive_SHORTRANGE 40000
#define ScannerNormalPassive_LONGRANGE 40

void check_ScannerNormalPassive( TScannerNormalPassive* ScannerNormalPassive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the passive normal scanner is empty";
  result = check_item( *ScannerNormalPassive,
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
    if ( ScannerNormalPassive->getScannerType() != TScanner::NORMAL_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getScanEfficiency() != 0 )
    {
      cout << "passive normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getShortRange() != 0 )
    {
      cout << "passive normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getLongRange() != 0 )
    {
      cout << "passive normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerNormalPassive->setItemName(ScannerNormalPassive_NAME);
  ScannerNormalPassive->setTechLevel(ScannerNormalPassive_TECHLEVEL);
  ScannerNormalPassive->setMass(ScannerNormalPassive_MASS);
  ScannerNormalPassive->setVolume(ScannerNormalPassive_VOLUME);
  ScannerNormalPassive->setSurface(ScannerNormalPassive_SURFACE);
  dummySet.Add( *substance->Create(ScannerNormalPassive_COST) );
  ScannerNormalPassive->setCost( dummySet );
  dummySet.Clear();
  ScannerNormalPassive->setScanEfficiency(ScannerNormalPassive_EFFICIENCY);
  ScannerNormalPassive->setShortRange(ScannerNormalPassive_SHORTRANGE);
  ScannerNormalPassive->setLongRange(ScannerNormalPassive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerNormalPassive_COST) );
  result = check_item( *ScannerNormalPassive,
                       TItem::SCANNER,
                       ScannerNormalPassive_NAME,
                       ScannerNormalPassive_TECHLEVEL,
                       ScannerNormalPassive_MASS,
                       ScannerNormalPassive_VOLUME,
                       ScannerNormalPassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerNormalPassive->getScannerType() != TScanner::NORMAL_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getScanEfficiency() != ScannerNormalPassive_EFFICIENCY )
    {
      cout << "passive normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getShortRange() != ScannerNormalPassive_SHORTRANGE )
    {
      cout << "passive normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getLongRange() != ScannerNormalPassive_LONGRANGE )
    {
      cout << "passive normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerNormalPassive object.\n";
  TScannerNormalPassive* testScanner = new TScannerNormalPassive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerNormalPassive;
  dummySet.Add( *substance->Create(ScannerNormalPassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerNormalPassive_NAME,
                       ScannerNormalPassive_TECHLEVEL,
                       ScannerNormalPassive_MASS,
                       ScannerNormalPassive_VOLUME,
                       ScannerNormalPassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerNormalPassive->getScannerType() != TScanner::NORMAL_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getScanEfficiency() != ScannerNormalPassive_EFFICIENCY )
    {
      cout << "passive normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getShortRange() != ScannerNormalPassive_SHORTRANGE )
    {
      cout << "passive normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getLongRange() != ScannerNormalPassive_LONGRANGE )
    {
      cout << "passive normal long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerNormalPassive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerNormalPassive( *ScannerNormalPassive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerNormalPassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerNormalPassive_NAME,
                       ScannerNormalPassive_TECHLEVEL,
                       ScannerNormalPassive_MASS,
                       ScannerNormalPassive_VOLUME,
                       ScannerNormalPassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerNormalPassive->getScannerType() != TScanner::NORMAL_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getScanEfficiency() != ScannerNormalPassive_EFFICIENCY )
    {
      cout << "passive normal scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getShortRange() != ScannerNormalPassive_SHORTRANGE )
    {
      cout << "passive normal short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerNormalPassive->getLongRange() != ScannerNormalPassive_LONGRANGE )
    {
      cout << "passive normal long scan range wrong!\n";
      result = false;
    } // if
  } // if


  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerNormalPassive );


  cout << "*** Now I destruct the TScannerNormalPassive object again.\n";
  delete testScanner;
} // check_ScannerNormalPassive



/*
 * $Log: test-item-ScannerNormalPassive.cpp,v $
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
