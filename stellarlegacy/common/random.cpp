// $Id: random.cpp,v 1.3 2001/12/03 01:33:24 mkrohn5 Exp $

// Random Code File
// Written by: Marco Krohn

// Copyright (C) 1999, 2000, Marco Krohn, krohn@itp.uni-hannover.de
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

#include <time.h>
#include <stdlib.h>

#include "common/global.h"
#include "common/random.h"





int TRandom::fRandInit = -1;





//----------------------------------------  class TRandom  ----------------------------------------

// static method
double TRandom :: getDouble()
{
  return (double) rand() / RAND_MAX;
}



// static method
int TRandom :: getInitNumber()
{
  return fRandInit;
}



// static method
int TRandom :: getInteger( int max )
{
int iReturn;

  if ( max > RAND_MAX )  max = RAND_MAX;
  iReturn = (int) ((double) rand() / ((double) RAND_MAX+1) * max);
  return iReturn;
}



// static method
int TRandom :: getMaxRandomNumber()
{
  return RAND_MAX;
}



// static method
void TRandom :: initialize()
{
time_t ltime;

  srand( time(&ltime) );
  initialize( rand() );
}



// static method
void TRandom :: initialize( int init )
{
  srand( init );
  fRandInit = init;
}



