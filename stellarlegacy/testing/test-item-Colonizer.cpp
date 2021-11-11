// $Id: test-item-Colonizer.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// Colonizer class testing
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

#define Colonizer_TECHLEVEL 5

void check_Colonizer( TColonizer* Colonizer, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the fuel tank is empty";
  result = check_item( *Colonizer,
                       TItem::COLONIZER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);

  cout << "*** Now I will assign the item some basic values.\n";
  Colonizer->setItemName("Colonization Module");
  Colonizer->setTechLevel(Colonizer_TECHLEVEL);
  Colonizer->setMass(100);
  Colonizer->setVolume(250);
  Colonizer->setSurface(60);
  dummySet.Add( *substance->Create(660) );
  Colonizer->setCost( dummySet );
  dummySet.Clear();

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(660) );
  result = check_item( *Colonizer,
                       TItem::COLONIZER,
                       "Colonization Module",
                       Colonizer_TECHLEVEL,
                       100,
                       250,
                       60,
                       dummySet);
  dummySet.Clear();
  test.report(result);

  cout << "*** Now I create a new TColonizer object.\n";
  TColonizer* testColonizer = new TColonizer();
  cout << "*** Now I check the operator=";  
  *testColonizer = *Colonizer;
  dummySet.Add( *substance->Create(660) );
  result = check_item( *testColonizer,
                       TItem::COLONIZER,
                       "Colonization Module",
                       Colonizer_TECHLEVEL,
                       100,
                       250,
                       60,
                       dummySet);
  dummySet.Clear();
  test.report(result);

  cout << "*** Now I destruct the TColonizer object again.\n";
  delete testColonizer;
  cout << "*** Now I use the copy constructor.\n";
  testColonizer = new TColonizer( *Colonizer );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(660) );
  result = check_item( *testColonizer,
                       TItem::COLONIZER,
                       "Colonization Module",
                       Colonizer_TECHLEVEL,
                       100,
                       250,
                       60,
                       dummySet);
  dummySet.Clear();
  test.report(result);

  cout << "*** Now testing operator==";
  test.report( *testColonizer == *Colonizer );


  cout << "*** Now I destruct the TColonizer object again.\n";
  delete testColonizer;
} // check_Colonizer



/*
 * $Log: test-item-Colonizer.cpp,v $
 * Revision 1.7  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.6  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.5  2001/07/05 20:34:18  ishark
 * added return true in test-item, fixed parser, added action Load/Save
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
 * Revision 1.1  2001/06/10 17:39:53  prolator
 * tests for item sub classes now in independent files
 *
 */
