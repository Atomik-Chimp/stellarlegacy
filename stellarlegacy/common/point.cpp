// $Id: point.cpp,v 1.12 2002/07/12 10:05:03 mkrohn5 Exp $

// Point Header File
// Written by: Marco Krohn

// Copyright (C) 1999, Marco Krohn, krohn@itp.uni-hannover.de
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

#include "common/datapackage.h"
#include "common/point.h"

using namespace std;





const double TPoint::dEps = 0.0000000001;





//----------------------------------------  Misc. Functions  ----------------------------------------

ostream& operator<<( ostream& Stream, const TPoint& point )
{
  return point.write(Stream);
}



TPoint operator*( const double dScale, const TPoint& point )
{
  return point*dScale;
}





//----------------------------------------  TPoint  ----------------------------------------

TPoint :: TPoint( double x, double y, double z )
{
  dX = x;
  dY = y;
  dZ = z;
}


TPoint :: TPoint( const TPoint& point )
{
  dX = point.dX;
  dY = point.dY;
  dZ = point.dZ;
}



double TPoint :: getLength() const
{
  return sqrt( dX*dX + dY*dY + dZ*dZ );
}



double TPoint :: getX() const
{
  return dX;
}



double TPoint :: getY() const
{
  return dY;
}



double TPoint :: getZ() const
{
  return dZ;
}



bool TPoint :: isNull() const
{
  if ( dX==0 && dY==0 && dZ==0 )  return true;
  return false;
}


// FIXME!!!
#include <iostream>

// dAccuracy=dEps
bool TPoint :: linearDependence( const TPoint& two, double dAccuracy ) const
{
double l;

  if ( dX == 0 )
  {
    if ( dY == 0 )
    {
      if ( dZ == 0 )  return true;
      else l = two.getZ() / dZ;
    }
    else l = two.getY() / dY;
  }
  else l = two.getX() / dX;

  cout << "x: " << dX << "  y: " << dY << "  z: " << dZ << endl;
  cout << "x: " << two.getX() << "  y: " << two.getY() << "  z: " << two.getZ() << endl;
  cout << "l: " << l << endl;
  if ( dX != 0 )
  {
    if ( fabs(two.getX() / dX - l) >= dAccuracy )  return false;
  }
  else if ( two.getX() != 0 )  return false;
  if ( dY != 0 )
  {
    if ( fabs(two.getY() / dY - l) >= dAccuracy )  return false;
  }
  else if ( two.getY() != 0 )  return false;
  if ( dZ != 0 )
  {
    if ( fabs(two.getZ() / dZ - l) >= dAccuracy )  return false;
  }
  else if ( two.getZ() != 0 )  return false;
  return true;
}



// bUnique=true
bool TPoint :: load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
TDataPackage* pPackage;

  if ( bUnique == true )  pPackage = in->SearchAndExtractUnique( sIdentifier );
  else                    pPackage = in->SearchAndExtract( sIdentifier );

  if ( pPackage == 0 )
  {
    WLOG("TPoint","Load") << "missing identifier: " << sIdentifier << endl;
    return false;
  }

  *this = *( (TPoint*) *pPackage );                        // all information copied
  delete pPackage;                                         // delete the package

  return true;
}



double TPoint :: magnitude() const
{
  return getLength();
}



TPoint& TPoint :: normalize()
{
double dScale;

  dScale = magnitude();
  if ( dScale == 0 )  return *this;                         // not possible to normalize
  *this *= 1/dScale;
  return *this;
}



bool TPoint :: operator==( const TPoint& point ) const
{
  return (dX == point.dX && dY == point.dY && dZ == point.dZ);
}



TPoint& TPoint :: operator+=( const TPoint& point )
{
  dX += point.dX;
  dY += point.dY;
  dZ += point.dZ;
  return *this;
}



TPoint& TPoint :: operator-=( const TPoint& point )
{
  dX -= point.dX;
  dY -= point.dY;
  dZ -= point.dZ;
  return *this;
}



TPoint TPoint :: operator+( const TPoint& point ) const
{
static TPoint calc;                                        // static to prevent multiple generations of this object

  calc = *this;
  calc += point;                                           // using the operator += to ensure consistency
  return calc;
}



TPoint TPoint :: operator-( const TPoint& point ) const
{
static TPoint calc;                                        // static to prevent multiple generations of this object

  calc = *this;
  calc -= point;                                           // using the operator -= to ensure consistency
  return calc;
}



TPoint& TPoint :: operator*=( const double dScale )
{
  dX *= dScale;
  dY *= dScale;
  dZ *= dScale;
  return *this;
}



TPoint TPoint :: operator*( const double dScale ) const
{
static TPoint calc;                                        // static to prevent multiple generations of this object

  calc = *this;
  calc *= dScale;                                          // using the operator *= to ensure consistency
  return calc;
}



double TPoint :: operator*( const TPoint& point ) const
{
  return dX*point.dX + dY*point.dY + dZ*point.dZ;
}



void TPoint :: rescale( double dScale )
{
  *this *= dScale;
}



// bUnique=true, bAutoDelete=false
bool TPoint :: save( TDataPackageList* out, const string& sIdentifier,
                     bool bUnique, bool bAutoDelete ) const
{
TDataPackage* data;

  if ( bUnique == true && out->Search(sIdentifier) != 0 )
  {
    WLOG("TPoint","save") << "already used identifier: " << sIdentifier << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, this );
  data->SetAutoDeleteMode( bAutoDelete );
  out->push_back( data );

  return true;
}



void TPoint :: setNull()
{
  dX = dY = dZ = 0;
}



// x=0, y=0, z=0
void TPoint :: setPoint( double x, double y, double z )
{
  dX = x;
  dY = y;
  dZ = z;
}



void TPoint :: setX( double x )
{
  dX = x;
}



void TPoint :: setY( double y )
{
  dY = y;
}



void TPoint :: setZ( double z )
{
  dZ = z;
}



ostream& TPoint :: write( ostream& stream ) const
{
  return stream << '(' << dX << ", " << dY << ", " << dZ << ')';
}





/*
* $Log: point.cpp,v $
* Revision 1.12  2002/07/12 10:05:03  mkrohn5
* lots of upper->lower fixes
*
* Revision 1.11  2002/06/07 00:33:00  mkrohn5
* upper->lower conversion
*
* Revision 1.10  2002/06/05 11:39:06  mkrohn5
* bugfix
*
* Revision 1.9  2002/06/05 11:32:04  mkrohn5
* changed the behaviour of normalize method
*
* Revision 1.8  2002/04/01 19:09:29  mkrohn5
* docu fixes + upper-lower fixes
*
* Revision 1.7  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.6  2001/10/31 19:51:01  mkrohn5
* added a few methods needed by the client
*
* Revision 1.5  2001/07/28 15:23:11  ishark
* added filters in stolist, more client code in sl.cpp
*
* Revision 1.4  2001/06/10 23:14:01  mkrohn5
* Load & Save do now use the TDataPackageList "stream"
* Added the SetNull method
*
* Revision 1.3  2001/05/10 22:52:12  mkrohn5
* changed Load method (now using TDataPackageList as input)
*
* Revision 1.2  2001/04/11 22:58:05  mkrohn5
* layout changes + update of the load&save methods
*
* Revision 1.1  2001/03/06 00:30:31  mkrohn5
* project import
*
* Revision 1.4  2000/06/15 09:50:47  mkrohn5
* *** empty log message ***
*
* Revision 1.3  2000/05/28 22:16:09  mkrohn5
* small changes
*
* Revision 1.2  2000/04/02 23:46:04  mkrohn5
* no message
*
* Revision 1.6  2000/03/08 23:34:41  krohn
* began writing the documentation using KDoc
*
* Revision 1.11  2000/01/31 00:22:20  krohn
* minor changes
*
* Revision 1.10  2000/01/20 04:24:57  jai
* Moved some inline functions into the header
*
* Revision 1.9  2000/01/17 17:25:52  krohn
* don't know but should be minor changes
*
* Revision 1.8  2000/01/13 22:28:50  krohn
* some minor modifications / improvements
* the log system seems to have a smaller bug which I will fix next time
*
* Revision 1.7  1999/10/23 16:10:15  alberto
* first version (semi-complete) of the TSubstance-related classes
*
* Revision 1.6  1999/09/28 07:10:22  krohn
* minor layout changes
*
* Revision 1.5  1999/09/15 23:10:10  krohn
* added cvs info
*
*
*/
