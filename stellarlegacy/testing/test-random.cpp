// $Id: test-random.cpp,v 1.5 2002/03/24 13:53:31 mkrohn5 Exp $

// Test Random Code File
// Written by: Marco Krohn

// Copyright (C) 2001, Marco Krohn, marco.krohn@gmx.de
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
#include <cmath>

#include "common/random.h"
#include "testing/testing.h"

using namespace std;





//----------------------------------------  Prototypes  ---------------------------------------

bool testDistribution( int4 nballs, int4 nbags);
bool testRandomClass();





//----------------------------------------  Functions  ----------------------------------------

// distribute a number of balls on a number of bags
// and check if the distribution is o.k.
bool testDistribution( int4 nballs, int4 nbags)
{
int4 i, rand;

  TRandom::initialize();
  int4* bag = new int4[nbags];                             // create some bags
  for ( i=0; i<nbags+1; i++ )  bag[i] = 0;                 // all bags contain 0 balls

  double average = (double) nballs / nbags;
  // FIXME: is that correct? I do not know much about probability calculations (Marco)
  double delta = sqrt( (double) nballs / nbags );
  double bound_upper = (double) average + 5*delta;
  double bound_lower = (double) average - 5*delta;

  for ( i=0; i<nballs; i++ )  {                            // now distribute the balls among the bags
    rand = TRandom::getInteger( nbags );
    if ( rand<0 || rand>=nbags )  return false;            // random number out of range
    bag[rand]++;
  }

  for ( i=0; i<nbags; i++ )  {
    if ( bag[i]>bound_upper || bag[i]<bound_lower )  return false;
  }

  delete[] bag;                                            // free memory

  return( true );
}



bool testRandomClass()
{
int i, max;
int field1[100], field2[100], field3[100];
bool result;
TTesting test;

  max = TRandom::getMaxRandomNumber();
  TRandom::initialize( 1234 );
  for ( i=0; i<100; i++ )  field1[i] = TRandom::getInteger( max );
  TRandom::initialize( 888 );
  for ( i=0; i<100; i++ )  field2[i] = TRandom::getInteger( max );
  TRandom::initialize( 1234 );
  for ( i=0; i<100; i++ )  field3[i] = TRandom::getInteger( max );

  cout << "different init numbers should generate different random numbers";
  for ( i=0; i<100; i++ )  {
    if ( field1[i] != field2[i] )  break;
  }
  if ( i>= 100 )  test.report( false );
  else            test.report( true );

  cout << "identical init numbers should generate identical random numbers";
  for ( i=0; i<100; i++ )  {
    if ( field1[i] != field3[i] )  break;
  }
  if ( i<100 )  test.report( false );
  else test.report( true );

  cout << "check distribution of numbers: 10000 balls, 2 bags";
  result = testDistribution( 10000, 2 );
  test.report( result );

  cout << "check distribution of numbers: 10000 balls, 10 bags";
  result = testDistribution( 10000, 10 );
  test.report( result );

  cout << "check distribution of numbers: 10000 balls, 50 bags";
  result = testDistribution( 10000, 50 );
  test.report( result );

  cout << "check distribution of numbers: 10000 balls, 100 bags";
  result = testDistribution( 10000, 100 );
  test.report( result );

  cout << "passed " << test.getSuccess() << " out of " << test.getChecksDone() << " tests." << endl;
  return test.result();
}
