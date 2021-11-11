// String Tools Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2002 -     , Marco Krohn, <marco.krohn@gmx.de>
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

#include <cctype>
#include <string>

#include "common/stringtools.h"

using namespace std;





//----------------------------------------  class TStringTools  ----------------------------------------

// static method
string TStringTools :: convertToFileName( const string& src )
{
string dest;
int4 i, len;

  len = src.length();
  for ( i=0; i<len; i++ )  {
    dest += ( (isalnum(src[i]))? src[i] : '_' );
  }

  return dest;
}



// static method
string TStringTools :: convertToDirectory( const string& src )
{
string dest;
int4 i, len;

  len = src.length();
  for ( i=0; i<len; i++ )  {
    if ( src[i]=='/' || isalnum(src[i])!=0 )  dest += src[i];
    else                                      dest += '_';
  }

  // make sure the directory ends with the appropriate termination
  if ( dest[dest.length()-1] != '/')  dest += '/';

  return dest;
}
