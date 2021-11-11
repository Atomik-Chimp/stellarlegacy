// $Id: global.h,v 1.8 2001/08/07 20:43:26 mkrohn5 Exp $

// Global Header File

// Copyright (C) 1999 - 2001, Marco Krohn, marco.krohn@gmx.de
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 1, or (at your option)
// any later version.
//
// This program is distrqibuted in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef __GLOBAL_INCLUDED
#define __GLOBAL_INCLUDED

#include <string>

#include "common/defs.h"

using namespace std;





//----------------------------------------  Functions  ----------------------------------------

/**
* Fatal error function which performs a "clean" exist instead of just
* doing exit(). For example it should be possible to try to save important
* data etc. After cleaning up the function will call @c exit( @e iExitCode ).
* @param sClassName Name of the class that initiated the @c Fatal() call.
* @param sMethodName Name of the method that initiated the @c Fatal() call.
* @param sMessage The message that contains the reason for calling Fatal.
* @param iExitCode The value @c exit() will called with.
*/
void Fatal( const string& sClassName, const string& sMethodName,
  const string& sMessage, int iExitCode=-1 );
/**
* Returns the greater of two objects.
* @param x the first object.
* @param y the second object.
* @return the greater of the two objects.
*/
template <class T>
T Max (const T x, const T y)
{
  if ( x < y )  return y;
  return x;
}
/**
* Returns the smaller of two objects.
* @param x the first object.
* @param y the second object.
* @return the smaller of the two objects.
*/
template <class T>
T Min (const T x, const T y)
{
  if ( x < y ) return x;
  return y;
}
/**
* Returns the closest int to the argument. Note: I have no idea
* what happens if d > @c MAX_INT or d < @c MIN_INT.
*
* Examples:
* @c round(0.5)  ==  1<br>
* @c round(1)    ==  1<br>
* @c round(-0.5) == -1<br>
* @c round(-1.2) == -1
*
* @param dValue The floating value for which the closest @
* @return the value of the argument rounded to the nearest int value.
*/
int Round( double dValue );





#endif        // __GLOBAL_INCLUDED





