// $Id: rectangle.cpp,v 1.4 2002/07/12 10:05:04 mkrohn5 Exp $

// Rectangle Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 1999 - 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#include "common/global.h"
#include "common/line.h"
#include "common/point.h"
#include "common/rectangle.h"





//----------------------------------------  Misc. Functions  ----------------------------------------

ostream& operator<<(ostream& Stream, const TRectangle& Rect)
{
  return Rect.write(Stream);
}





//----------------------------------------  class TRectangle  ----------------------------------------

// x=0, y=0, w=0, h=0
TRectangle :: TRectangle(double x, double y, double w, double h)
{
  setRect(x, y, w, h);
}



TRectangle :: TRectangle(const TPoint& TopLeft, const TPoint& Size)
{
  setRect( TopLeft.getX(), TopLeft.getY(), Size.getX(), Size.getY() );
}



// proper=false
bool TRectangle :: contains(double x, double y, bool proper) const
{
// OPTIMIZE: it might be useful to inline at least this method since
// this one is very important for the UI (e.g. bounding boxes).

  if ( proper == true )
    return (x>x1 && x<x2 && y>y1 && y<y2);
  else
    return (x>=x1 && x<=x2 && y>=y1 && y<=y2);
}



// proper=false
bool TRectangle :: contains( const TPoint& Point, bool proper ) const
{
  return contains(Point.getX(), Point.getY(), proper);
}



double TRectangle :: getBottom() const
{
  return y2;
}



TPoint TRectangle :: getCenter() const
{
TPoint p;

  p.setX( (x1+x2)/2 );
  p.setY( (y1+y2)/2 );
  return p;
}



double TRectangle :: getHeight() const
{
  return y2-y1;
}


#include <iostream>
int TRectangle :: getIntersectionPoints( const TLine& line, TPoint* one, TPoint* two ) const
{
int i, iNumber;
double w, h;
TLine l;
TPoint p;

  iNumber = 0;
  w = getWidth();
  h = getHeight();

  l.setLine( TPoint(x1,y1,0), TPoint(w,0,0) );
  i = line.getIntersectionPoint( l, &p );
  if ( i == 1 )
  {
    if ( contains(p.getX(),p.getY()) == true )
    {
      iNumber++;
      if ( iNumber == 1 )  *one = p;
      else                 *two = p;
    }
    else  cout << "strange" << endl;
  }
  else if ( i == 2 )  return 3;

/*
  l.setLine( TPoint(x1,y1,0), TPoint(0,h,0) );
  i = line.getIntersectionPoint( l, &p );
  if ( i == 1 )
  {
    if ( Contains(p.getX(),p.getY()) == true )
    {
      iNumber++;
      if ( iNumber == 1 )  *one = p;
      else                 *two = p;
    }
  }
  else if ( i == 2 )  return 3;

  l.setLine( TPoint(x2,y1,0), TPoint(0,h,0) );
  i = line.getIntersectionPoint( l, &p );
  if ( i == 1 )
  {
    if ( Contains(p.getX(),p.getY()) == true )
    {
      iNumber++;
      if ( iNumber == 1 )  *one = p;
      else                 *two = p;
    }
  }
  else if ( i == 2 )  return 3;

  l.setLine( TPoint(x1,y2,0), TPoint(w,0,0) );
  i = line.getIntersectionPoint( l, &p );
  if ( i == 1 )
  {
    if ( Contains(p.getX(),p.getY()) == true )
    {
      iNumber++;
      if ( iNumber == 1 )  *one = p;
      else                 *two = p;
    }
  }
  else if ( i == 2 )  return 3;
*/
  // FIXME: check if one and two are identical
  return iNumber;
}



double TRectangle :: getLeft() const
{
  return x1;
}



double TRectangle :: getRight() const
{
  return x2;
}



TPoint TRectangle :: getSize() const
{
  return TPoint(x2-x1, y2-y1);
}



double TRectangle :: getTop() const
{
  return x2;
}



double TRectangle :: getWidth() const
{
  return x2-x1;
}



double TRectangle :: getX() const
{
  return x1;
}



double TRectangle :: getY() const
{
  return y1;
}



bool TRectangle :: intersects(const TRectangle& r) const
{
  return ( Max( x1, r.x1 ) <= Min( x2, r.x2 ) &&
           Max( y1, r.y1 ) <= Min( y2, r.y2 ) );
}



bool TRectangle :: isValid() const
{
  return ( x1<=x2 && y1<=y2 );
}



void TRectangle :: moveBy(double dx, double dy)
{
  x1 += dx;
  x2 += dx;
  y1 += dy;
  y2 += dy;
}



void TRectangle :: moveByX(double dx)
{
  x1 += dx;
  x2 += dx;
}



void TRectangle :: moveByY(double dy)
{
  y1 += dy;
  y2 += dy;
}



void TRectangle :: moveTo(double x, double y)
{
  x2 += x - x1;
  x1 = x;
  y2 += y - y1;
  y1 = y;
}



void TRectangle :: moveToX(double x)
{
  x2 += x - x1;
  x1 = x;
}



void TRectangle :: moveToY(double y)
{
  y2 += y - y1;
  y1 = y;
}



TRectangle TRectangle :: normalize() const
{
TRectangle r;

  if ( x2 < x1 )                                 // swap bad x values
  {
    r.x1 = x2;
    r.x2 = x1;
  }
  else
  {
    r.x1 = x1;
    r.x2 = x2;
  }
  if ( y2 < y1 )                                 // swap bad y values
  {
    r.y1 = y2;
    r.y2 = y1;
  }
  else
  {
    r.y1 = y1;
    r.y2 = y2;
  }
  return r;
}



void TRectangle :: setBottom(double b)
{
  y2 = b;
}



void TRectangle :: setHeight(double h)
{
  y2 = y1 + h;
}



void TRectangle :: setLeft(double l)
{
  x1 = l;
}



void TRectangle :: setRect(double x, double y, double w, double h)
{
  x1 = x;
  y1 = y;
  x2 = x + w;
  y2 = y + h;
}



void TRectangle :: setRight(double r)
{
  x2 = r;
}



void TRectangle :: setSize(double w, double h)
{
  x2 = x1 + w;
  y2 = y1 + h;
}



void TRectangle :: setSize(const TPoint& Size)
{
  x2 = x1 + Size.getX();
  y2 = y1 + Size.getY();
}



void TRectangle :: setTop(double t)
{
  y1 = t;
}



void TRectangle :: setWidth(double w)
{
  x2 = x1 + w;
}



void TRectangle :: setX(double x)
{
  x1 = x;
}



void TRectangle :: setY(double y)
{
  y1 = y;
}



ostream& TRectangle :: write(ostream& Stream) const
{
  return Stream << "(" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << ")";
}





/*
* $Log: rectangle.cpp,v $
* Revision 1.4  2002/07/12 10:05:04  mkrohn5
* lots of upper->lower fixes
*
* Revision 1.3  2001/10/31 19:52:12  mkrohn5
* added a few methods needed by the client (needs some more work though)
*
* Revision 1.2  2001/03/07 00:40:53  mkrohn5
* smaller corrections
*
* Revision 1.1  2001/03/06 00:30:31  mkrohn5
* project import
*
* Revision 1.6  2000/09/21 20:49:55  mkrohn5
* added some documentation and finished some methods - should be almost complete now
*
* Revision 1.5  2000/09/03 00:10:31  mkrohn5
* made the interface similar to the qt one
*
* Revision 1.4  2000/08/10 00:05:33  mkrohn5
* *** empty log message ***
*
* Revision 1.3  2000/06/15 09:50:47  mkrohn5
* *** empty log message ***
*
* Revision 1.2  2000/05/28 22:16:09  mkrohn5
* small changes
*
* Revision 1.1  2000/04/02 23:46:04  mkrohn5
* no message
*
* Revision 1.1  2000/01/31 00:22:45  krohn
* a new class for managing a rectangle
*
*
*/
