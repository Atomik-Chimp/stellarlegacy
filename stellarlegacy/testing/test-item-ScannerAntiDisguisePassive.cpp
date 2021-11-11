// $Id: test-item-ScannerAntiDisguisePassive.cpp,v 1.9 2002/04/27 00:09:22 prolator Exp $
//
// passive anti disguise scanner class testing
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

#define ScannerAntiDisguisePassive_NAME "Passive anti Disguise Scanner"
#define ScannerAntiDisguisePassive_TECHLEVEL 13
#define ScannerAntiDisguisePassive_MASS 13
#define ScannerAntiDisguisePassive_VOLUME 6
#define ScannerAntiDisguisePassive_SURFACE 4
#define ScannerAntiDisguisePassive_COST 47
#define ScannerAntiDisguisePassive_EFFICIENCY 65
#define ScannerAntiDisguisePassive_SHORTRANGE 60000
#define ScannerAntiDisguisePassive_LONGRANGE 60

void check_ScannerAntiDisguisePassive( TScannerAntiDisguisePassive* ScannerAntiDisguisePassive, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Check whether the passive anti disguise scanner is empty";
  result = check_item( *ScannerAntiDisguisePassive,
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
    if ( ScannerAntiDisguisePassive->getScannerType() != TScanner::ANTIDISGUISE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getScanEfficiency() != 0 )
    {
      cout << "passive anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getShortRange() != 0 )
    {
      cout << "passive anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getLongRange() != 0 )
    {
      cout << "passive anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  ScannerAntiDisguisePassive->setItemName(ScannerAntiDisguisePassive_NAME);
  ScannerAntiDisguisePassive->setTechLevel(ScannerAntiDisguisePassive_TECHLEVEL);
  ScannerAntiDisguisePassive->setMass(ScannerAntiDisguisePassive_MASS);
  ScannerAntiDisguisePassive->setVolume(ScannerAntiDisguisePassive_VOLUME);
  ScannerAntiDisguisePassive->setSurface(ScannerAntiDisguisePassive_SURFACE);
  dummySet.Add( *substance->Create(ScannerAntiDisguisePassive_COST) );
  ScannerAntiDisguisePassive->setCost( dummySet );
  dummySet.Clear();
  ScannerAntiDisguisePassive->setScanEfficiency(ScannerAntiDisguisePassive_EFFICIENCY);
  ScannerAntiDisguisePassive->setShortRange(ScannerAntiDisguisePassive_SHORTRANGE);
  ScannerAntiDisguisePassive->setLongRange(ScannerAntiDisguisePassive_LONGRANGE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(ScannerAntiDisguisePassive_COST) );
  result = check_item( *ScannerAntiDisguisePassive,
                       TItem::SCANNER,
                       ScannerAntiDisguisePassive_NAME,
                       ScannerAntiDisguisePassive_TECHLEVEL,
                       ScannerAntiDisguisePassive_MASS,
                       ScannerAntiDisguisePassive_VOLUME,
                       ScannerAntiDisguisePassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiDisguisePassive->getScannerType() != TScanner::ANTIDISGUISE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getScanEfficiency() != ScannerAntiDisguisePassive_EFFICIENCY )
    {
      cout << "passive anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getShortRange() != ScannerAntiDisguisePassive_SHORTRANGE )
    {
      cout << "passive anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getLongRange() != ScannerAntiDisguisePassive_LONGRANGE )
    {
      cout << "passive anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TScannerAntiDisguisePassive object.\n";
  TScannerAntiDisguisePassive* testScanner = new TScannerAntiDisguisePassive();
  cout << "*** Now I check the operator=";  
  *testScanner = *ScannerAntiDisguisePassive;
  dummySet.Add( *substance->Create(ScannerAntiDisguisePassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiDisguisePassive_NAME,
                       ScannerAntiDisguisePassive_TECHLEVEL,
                       ScannerAntiDisguisePassive_MASS,
                       ScannerAntiDisguisePassive_VOLUME,
                       ScannerAntiDisguisePassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiDisguisePassive->getScannerType() != TScanner::ANTIDISGUISE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getScanEfficiency() != ScannerAntiDisguisePassive_EFFICIENCY )
    {
      cout << "passive anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getShortRange() != ScannerAntiDisguisePassive_SHORTRANGE )
    {
      cout << "passive anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getLongRange() != ScannerAntiDisguisePassive_LONGRANGE )
    {
      cout << "passive anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TScannerAntiDisguisePassive object again.\n";
  delete testScanner;
  cout << "*** Now I use the copy constructor.\n";
  testScanner = new TScannerAntiDisguisePassive( *ScannerAntiDisguisePassive );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(ScannerAntiDisguisePassive_COST) );
  result = check_item( *testScanner,
                       TItem::SCANNER,
                       ScannerAntiDisguisePassive_NAME,
                       ScannerAntiDisguisePassive_TECHLEVEL,
                       ScannerAntiDisguisePassive_MASS,
                       ScannerAntiDisguisePassive_VOLUME,
                       ScannerAntiDisguisePassive_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( ScannerAntiDisguisePassive->getScannerType() != TScanner::ANTIDISGUISE_PASSIVE )
    {
      cout << "scanner type wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getScanEfficiency() != ScannerAntiDisguisePassive_EFFICIENCY )
    {
      cout << "passive anti disguise scan efficiency wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getShortRange() != ScannerAntiDisguisePassive_SHORTRANGE )
    {
      cout << "passive anti disguise short scan range wrong!\n";
      result = false;
    } // if
    if ( ScannerAntiDisguisePassive->getLongRange() != ScannerAntiDisguisePassive_LONGRANGE )
    {
      cout << "passive anti disguise long scan range wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testScanner == *ScannerAntiDisguisePassive );


  cout << "*** Now I destruct the TScannerAntiDisguisePassive object again.\n";
  delete testScanner;
} // check_ScannerAntiDisguisePassive



/*
 * $Log: test-item-ScannerAntiDisguisePassive.cpp,v $
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
