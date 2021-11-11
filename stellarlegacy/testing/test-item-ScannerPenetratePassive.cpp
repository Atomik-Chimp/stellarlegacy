// $Id: test-item-ScannerPenetratePassive.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
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

#define ScannerPenetratePassive_NAME "Passive Penetrate Scanner"
#define ScannerPenetratePassive_TECHLEVEL 17
#define ScannerPenetratePassive_MASS 33
#define ScannerPenetratePassive_VOLUME 5
#define ScannerPenetratePassive_SURFACE 7
#define ScannerPenetratePassive_COST 31
#define ScannerPenetratePassive_EFFICIENCY 57
#define ScannerPenetratePassive_SHORTRANGE 50000
#define ScannerPenetratePassive_LONGRANGE 9

void check_ScannerPenetratePassive( TScannerPenetratePassive* ScannerPenetratePassive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Check whether the passive penetrate scanner is empty";
  result = check_item( *ScannerPenetratePassive,
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
    if ( ScannerPenetratePassive->getScannerType() != TScanner::PENETRATE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getScanEfficiency() != 0 )
    {
      cout << "passive penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getShortRange() != 0 )
    {
      cout << "passive penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getLongRange() != 0 )
    {
      cout << "passive penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerPenetratePassive->setItemName(ScannerPenetratePassive_NAME);
  ScannerPenetratePassive->setTechLevel(ScannerPenetratePassive_TECHLEVEL);
  ScannerPenetratePassive->setMass(ScannerPenetratePassive_MASS);
  ScannerPenetratePassive->setVolume(ScannerPenetratePassive_VOLUME);
  ScannerPenetratePassive->setSurface(ScannerPenetratePassive_SURFACE);
  dummySet.Add( *substance->Create(ScannerPenetratePassive_COST) );
  ScannerPenetratePassive->setCost( dummySet );
  dummySet.Clear();
  ScannerPenetratePassive->setScanEfficiency(ScannerPenetratePassive_EFFICIENCY);
  ScannerPenetratePassive->setShortRange(ScannerPenetratePassive_SHORTRANGE);
  ScannerPenetratePassive->setLongRange(ScannerPenetratePassive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerPenetratePassive_COST) );
  result = check_item( *ScannerPenetratePassive,
                       TItem::SCANNER,
                       ScannerPenetratePassive_NAME,
                       ScannerPenetratePassive_TECHLEVEL,
                       ScannerPenetratePassive_MASS,
                       ScannerPenetratePassive_VOLUME,
                       ScannerPenetratePassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerPenetratePassive->getScannerType() != TScanner::PENETRATE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getScanEfficiency() != ScannerPenetratePassive_EFFICIENCY )
    {
      cout << "passive penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getShortRange() != ScannerPenetratePassive_SHORTRANGE )
    {
      cout << "passive penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getLongRange() != ScannerPenetratePassive_LONGRANGE )
    {
      cout << "passive penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerPenetratePassive object.\n";
  TScannerPenetratePassive* testScanner = new TScannerPenetratePassive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerPenetratePassive;
  dummySet.Add( *substance->Create(ScannerPenetratePassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerPenetratePassive_NAME,
                       ScannerPenetratePassive_TECHLEVEL,
                       ScannerPenetratePassive_MASS,
                       ScannerPenetratePassive_VOLUME,
                       ScannerPenetratePassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerPenetratePassive->getScannerType() != TScanner::PENETRATE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getScanEfficiency() != ScannerPenetratePassive_EFFICIENCY )
    {
      cout << "passive penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getShortRange() != ScannerPenetratePassive_SHORTRANGE )
    {
      cout << "passive penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getLongRange() != ScannerPenetratePassive_LONGRANGE )
    {
      cout << "passive penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerPenetratePassive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerPenetratePassive( *ScannerPenetratePassive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerPenetratePassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerPenetratePassive_NAME,
                       ScannerPenetratePassive_TECHLEVEL,
                       ScannerPenetratePassive_MASS,
                       ScannerPenetratePassive_VOLUME,
                       ScannerPenetratePassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerPenetratePassive->getScannerType() != TScanner::PENETRATE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getScanEfficiency() != ScannerPenetratePassive_EFFICIENCY )
    {
      cout << "passive penetrate scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getShortRange() != ScannerPenetratePassive_SHORTRANGE )
    {
      cout << "passive penetrate short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerPenetratePassive->getLongRange() != ScannerPenetratePassive_LONGRANGE )
    {
      cout << "passive penetrate long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerPenetratePassive );


  cout << "*** Now I destruct the TScannerPenetratePassive object again.\n";
  delete testScanner;
} // check_ScannerPenetratePassive



/*
 * $Log: test-item-ScannerPenetratePassive.cpp,v $
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
 * Revision 1.4  2001/06/12 14:13:43  prolator
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
