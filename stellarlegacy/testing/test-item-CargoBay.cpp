// $Id: test-item-CargoBay.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// cargo bay class testing
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

#define CargoBay_TECHLEVEL 4

void check_CargoBay( TCargoBay* CargoBay, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the fuel tank is empty";
  result = check_item( *CargoBay,
                       TItem::CARGOBAY,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);

  cout << "*** Now I will assign the item some basic values.\n";
  CargoBay->setItemName("Cargo Bay");
  CargoBay->setTechLevel(CargoBay_TECHLEVEL);
  CargoBay->setMass(1);
  CargoBay->setVolume(2);
  CargoBay->setSurface(0);
  dummySet.Add( *substance->Create(1) );
  CargoBay->setCost( dummySet );
  dummySet.Clear();

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(1) );
  result = check_item( *CargoBay,
                       TItem::CARGOBAY,
                       "Cargo Bay",
                       CargoBay_TECHLEVEL,
                       1,
                       2,
                       0,
                       dummySet);
  dummySet.Clear();
  test.report(result);

  cout << "*** Now I create a new TCargoBay object.\n";
  TCargoBay* testBay = new TCargoBay();
  cout << "*** Now I check the operator=";  
  *testBay = *CargoBay;
  dummySet.Add( *substance->Create(1) );
  result = check_item( *testBay,
                       TItem::CARGOBAY,
                       "Cargo Bay",
                       CargoBay_TECHLEVEL,
                       1,
                       2,
                       0,
                       dummySet);
  dummySet.Clear();
  test.report(result);

  cout << "*** Now I destruct the TCargoBay object again.\n";
  delete testBay;
  cout << "*** Now I use the copy constructor.\n";
  testBay = new TCargoBay( *CargoBay );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(1) );
  result = check_item( *testBay,
                       TItem::CARGOBAY,
                       "Cargo Bay",
                       CargoBay_TECHLEVEL,
                       1,
                       2,
                       0,
                       dummySet);
  dummySet.Clear();
  test.report(result);

  cout << "*** Now testing operator==";
  test.report( *testBay == *CargoBay );


  cout << "*** Now I destruct the TCargoBay object again.\n";
  delete testBay;
} // check_CargoBay



/*
 * $Log: test-item-CargoBay.cpp,v $
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
