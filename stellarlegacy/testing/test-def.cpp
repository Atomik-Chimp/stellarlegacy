// $Id: test-def.cpp,v 1.1 2002/03/24 13:47:43 mkrohn5 Exp $

// Test Def Code File
// Written by: Marco Krohn

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

#include <iostream>

#include "common/defs.h"
#include "testing/testing.h"

using namespace std;





//----------------------------------------  Functions  ----------------------------------------

/**
* A quick test to ensure that all data types have the correct size.
*/
bool testDataTypes()
{
TTesting test;

  cout << "byte size should be 1--is " << sizeof(byte);
  if ( sizeof(byte) != 1 )  test.report( false );
  test.report( true );

  cout << "int2 size should be 2--is " << sizeof(int2);
  if ( sizeof(int2) != 2 )  test.report( false );
  test.report( true );

  cout << "int4 size should be 4--is " << sizeof(int4);
  if ( sizeof(int4) != 4 )  test.report( false );
  test.report( true );

  cout << "uint2 size should be 2--is " << sizeof(uint2);
  if ( sizeof(uint2) != 2 )  test.report( false );
  test.report( true );

  cout << "uint4 size should be 4--is " << sizeof(uint4);
  if ( sizeof(uint4) != 4 )  test.report( false );
  test.report( true );

  cout << "passed " << test.getSuccess() << " out of " << test.getChecksDone() << " tests." << endl;
  return test.result();
}
