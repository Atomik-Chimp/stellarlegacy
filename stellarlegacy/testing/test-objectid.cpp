// $Id: test-objectid.cpp,v 1.2 2002/03/24 18:08:03 mkrohn5 Exp $

// Test ObjectID Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001 - 2002, Marco Krohn, <marco.krohn@gmx.de>
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

#include "common/link.h"
#include "common/datapackage.h"
#include "testing/testing.h"

using namespace std;





//----------------------------------------  Prototypes  ----------------------------------------

void testFailed( TTesting& test, const TObjectID& id1, const TObjectID& id2 );
bool testObjectIDClass();





//----------------------------------------  Functions  ----------------------------------------

void testFailed( TTesting& test, const TObjectID& id1, const TObjectID& id2 )
{
  test.report( false );
  cout << "\tid1: " << id1 << endl;
  cout << "\tid2: " << id2 << endl;
}



bool testObjectIDClass()
{
int array[] = { 255, 0, 0, 12, 24, 48, 26, 19, 14, 12 };   // test works for all ID sizes <= 10
int ovfl[] = { 0, 1, 0, 12, 24, 48, 26, 19, 14, 12 };
int array2[] = { 255, 255, 255, 1, 0, 0, 0, 0, 0, 0 };
int ovfl2[] = { 0, 0, 0, 2, 0, 0, 0, 0, 0, 0 };
TDataPackageList* dplist;
TTesting test;

  cout << "ID size should be >=4: is " << TObjectID::getIDSize();
  if ( TObjectID::getIDSize() <= 3 )  test.report( false );
  else                                test.report( true );

  cout << "ID Size should be <= 10: is " << TObjectID::getIDSize();
  if ( TObjectID::getIDSize() >= 11 )  test.report( false );
  else                                 test.report( true );

  cout << "operator==, constructor and copy constructor";
  TObjectID ID1( array, false );
  TObjectID ID2( ID1 );
  if ( !(ID1 == ID2) )  testFailed( test, ID1, ID2 );
  else                  test.report( true );

  cout << "setID method";
  ID2.setID( array, true );
  if ( ID1 == ID2 )  testFailed( test, ID1, ID2 );
  else               test.report( true );

  cout << "setTemp and operator== (temp IDs)";
  ID2.setTemp( false );
  if ( !(ID1 == ID2) )  testFailed( test, ID1, ID2 );
  else                  test.report( true );

  cout << "operator=";
  ID2 = ID1;
  if ( !(ID1 == ID2) )  testFailed( test, ID1, ID2 );
  else                  test.report( true );

  cout << "operator!=";
  if ( ID1 != ID2 )  testFailed( test, ID1, ID2 );
  else               test.report( true );

  cout << "operator++ (postfix)";
  ID2 = ID1;
  if ( ID1 != ID2++ )  testFailed( test, ID1, ID2 );
  else                 test.report( true );

  cout << "operator++ (prefix)";
  ID2 = ID1;
  if ( ID1 == ++ID2 )  testFailed( test, ID1, ID2 );
  else                 test.report( true );

  cout << "operator== with null IDs";
  ID1.setNull();
  ID1.setTemp( false );
  ID2.setNull();
  ID2.setTemp( false );
  if ( ID1 != ID2 )  testFailed( test, ID1, ID2 );
  else               test.report( true );

  cout << "operator== with null IDs and diffent temp settings";
  ID1.setNull();
  ID1.setTemp( false );
  ID2.setNull();
  ID2.setTemp( true );
  if ( ID1 == ID2 )  testFailed( test, ID1, ID2 );
  else               test.report( true );

  cout << "operator< with null IDs";
  ID1.setNull();
  ID1.setTemp( false );
  ID2.setNull();
  ID2.setTemp( false );
  if ( ID1 < ID2 )  testFailed( test, ID1, ID2 );
  else              test.report( true );

  cout << "operator< with id1=temp(0), id2=0";
  ID1.setNull();
  ID1.setTemp( true );
  ID2.setNull();
  ID2.setTemp( false );
  if ( !(ID1 < ID2) )  testFailed( test, ID1, ID2 );    // tempIDs should always be smaller!
  else                 test.report( true );

  cout << "operator< with id1=temp(1), id2=0";
  ID1++;
  if ( !(ID1 < ID2) )  testFailed( test, ID1, ID2 );
  else                 test.report( true );

  cout << "operator< with id1=temp(1), id2=1";
  ID2++;
  if ( !(ID1 < ID2) )  testFailed( test, ID1, ID2 );
  else                 test.report( true );

  cout << "operator< with id1=0, id2=0";
  ID1.setNull();
  ID1.setTemp( false );
  ID2.setNull();
  ID2.setTemp( false );
  if ( ID1 < ID2 )  testFailed( test, ID1, ID2 );    // tempIDs should always be smaller!
  else              test.report( true );

  cout << "operator< with id1=1, id2=0";
  ID1++;
  if ( ID1 < ID2 )  testFailed( test, ID1, ID2 );
  else              test.report( true );

  cout << "operator< with id1=1, id2=1";
  ID2++;
  if ( ID1 < ID2 )  testFailed( test, ID1, ID2 );
  else              test.report( true );

  cout << "operator< with id1=1, id2=2";
  ID2++;
  if ( !(ID1 < ID2) )  testFailed( test, ID1, ID2 );
  else                 test.report( true );

  cout << "operator< with id1=temp(1), id2=temp(2)";
  ID1.setTemp( true );
  ID2.setTemp( true );                                     // ID1=temp(1), ID2=temp(2)
  if ( !(ID1 < ID2) )  testFailed( test, ID1, ID2 );
  else                 test.report( true );

  cout << "isNull() for null IDs";
  ID1.setNull();
  ID1.setTemp( true );
  ID2.setNull();
  ID2.setTemp( false );
  if ( ID1.isNull()==false || ID2.isNull()==false )  testFailed( test, ID1, ID2 );
  else                                               test.report( true );

  cout << "isNull() for non-null IDs";
  ID1++;
  ID2++;
  if ( ID1.isNull()==true || ID2.isNull()==true )  testFailed( test, ID1, ID2 );
  else                                             test.report( true );

  cout << "isTemp() for temp IDs";
  ID1.setNull();
  ID1.setTemp( true );
  ID2.setNull();
  ID2++;
  ID2.setTemp( true );
  if ( ID1.isTemp()==false || ID2.isTemp()==false )  testFailed( test, ID1, ID2 );
  else                                               test.report( true );

  cout << "isTemp() for non-temp IDs";
  ID1.setTemp( false );
  ID2.setTemp( false );
  if ( ID1.isTemp()==true || ID2.isTemp()==true )  testFailed( test, ID1, ID2 );
  else                                             test.report( true );

  cout << "load and save for non-temp ID";
  ID1.setID( array );
  ID1.setTemp( false );
  dplist = new TDataPackageList;
  ID1.save( dplist, "id-test", true );
  ID2.load( dplist, "id-test", true );
  if ( ID1 != ID2 )  {
    dplist->showContent();                                 // write information to the log file
    testFailed( test, ID1, ID2 );
  }
  else test.report( true );
  delete dplist;

  cout << "load and save for temp ID";
  ID1.setID( array );
  ID1.setTemp( true );
  dplist = new TDataPackageList;
  ID1.save( dplist, "id-test", true );
  ID2.load( dplist, "id-test", true );
  if ( ID1 != ID2 )  {
    dplist->showContent();                                 // write information to the log file
    testFailed( test, ID1, ID2 );
  }
  else test.report( true );
  delete dplist;

  cout << "one byte overflow";
  ID1.setID( array );
  ID1++;
  ID2.setID( ovfl );
  if ( ID1 != ID2 )  testFailed( test, ID1, ID2 );
  else               test.report( true );

  cout << "multiple byte overflow";
  ID1.setID( array2 );
  ID1++;
  ID2.setID( ovfl2 );
  if ( ID1 != ID2 )  testFailed( test, ID1, ID2 );
  else               test.report( true );

  cout << "passed " << test.getSuccess() << " out of " << test.getChecksDone() << " tests." << endl;
  return test.result();
}
