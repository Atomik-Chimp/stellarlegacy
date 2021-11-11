// $Id: line.cpp,v 1.3 2002/07/12 10:05:03 mkrohn5 Exp $

// Line Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001 -     , Marco Krohn, marco.krohn@gmx.de
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

#include "common/line.h"
#include "common/point.h"











//----------------------------------------  class TLine  ----------------------------------------

TLine :: TLine()
{
  fOffset = TPoint( 0, 0, 0 );
  fDir = TPoint( 1, 0, 0 );
}



TLine :: TLine( const TPoint& offset, const TPoint& dir )
{
  setLine( offset, dir );
}



const TPoint& TLine :: getDir() const
{
  return fDir;
}

// FIXME
#include <iostream>

int TLine :: getIntersectionPoint( const TLine& line, TPoint* point ) const
{
  cout << "line1: " << fOffset << "   dir: " << fDir << endl;
  cout << "line2: " << line.fOffset << "   dir: " << line.fDir << endl;

  if ( fDir.linearDependence(line.getDir()) == true )
  {
    if ( fDir.linearDependence(line.getOffset()-fOffset) == true )             // both lines are identical
    {
      *point = fOffset;
      return 2;
    }
    else
    {
      return 0;                                            // parallel but not identical
    }
  }

  // Definitions:
  // x1,y1 = coordinates of the offset (this line)
  // x2,y2 = coordinates of the offset+dir (this line)
  // sx1,sy1 = coordinates of the offset (from the given second line)
  // sx2,sy2 = ...
  double x1, y1, x2, y2, z1, z2;
  double sx1, sy1, sx2, sy2, sz1, sz2;
  double lambda;

  x1 = fOffset.getX();
  y1 = fOffset.getY();
  z1 = fOffset.getZ();
  x2 = (fOffset + fDir).getX();
  y2 = (fOffset + fDir).getY();
  z2 = (fOffset + fDir).getZ();
  sx1 = line.getOffset().getX();
  sy1 = line.getOffset().getY();
  sz1 = line.getOffset().getZ();
  sx2 = (line.getOffset() + line.getDir()).getX();
  sy2 = (line.getOffset() + line.getDir()).getY();
  sz2 = (line.getOffset() + line.getDir()).getZ();

  // lambda is the parameter for the line descibed by x1,x2,y1,y2,...
  // (x1,y1,z1) + lamda*(fDir.x,fDir.y,fDir.z)
  // now we calculate the value for lambda which should be the potential
  // intersection point p
  lambda = ((sx1-x1)*(y2-y1) - (sy1-y1)*(x1-x2)) / ((sx1-sx2)*(y2-y1) - (sy2-sy1)*(x1-x2));

  // p is element of line 1, but so far we don't know if it also belongs to line 2
  TPoint p( sx1+lambda*(sx2-sx1), sy1+lambda*(sy2-sy1), sz1+lambda*(sz2-sz1) );
  cout << "lambda: " << lambda << "   p: " << p << endl;

  if ( (line.getDir()).linearDependence(p-line.getOffset()) == false )  return 0;
  *point = p;                                              // intersection point found!

  return 1;
}



const TPoint& TLine :: getOffset() const
{
  return fOffset;
}



void TLine :: setDir( const TPoint& dir )
{
  if ( dir.isNull() == true )  return;
  fDir = dir;
}



void TLine :: setLine( const TPoint& offset, const TPoint& dir )
{
  setOffset( offset );
  setDir( dir );
}



void TLine :: setOffset( const TPoint& offset )
{
  fOffset = offset;
}





/**
* $Log: line.cpp,v $
* Revision 1.3  2002/07/12 10:05:03  mkrohn5
* lots of upper->lower fixes
*
* Revision 1.2  2002/04/01 19:09:28  mkrohn5
* docu fixes + upper-lower fixes
*
* Revision 1.1  2001/11/02 00:15:26  mkrohn5
* these files are needed by the client but are general enough to put them in the common directory
*
*/
