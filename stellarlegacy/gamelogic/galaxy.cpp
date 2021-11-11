// $Id: galaxy.cpp,v 1.30 2002/07/12 10:06:48 mkrohn5 Exp $

// Galaxy Code File
// Written by: Marco Krohn, Simon Stich

// Copyright (C) 1999 - 2001, Marco Krohn, <marco.krohn@gmx.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <math.h>

#include "common/datapackage.h"
#include "common/defs.h"
#include "gamelogic/galaxy.h"
#include "common/link.h"
#include "gamelogic/rulesystem.h"
#include "gamelogic/stobj.h"
#include "gamelogic/stolist.h"
#include "gamelogic/universe.h"





//----------------------------------------  class TGalaxy  ----------------------------------------

// name="", size=0, wrapX=false, wrapY=false, wrapZ=false
TGalaxy :: TGalaxy( const string& name, const TPoint& size, bool wrapX, bool wrapY, bool wrapZ )
{
  LOG("TGalaxy", "TGalaxy") << "TGalaxy object created." << endl;

  fName = name;
  fSize = size;
  fWrapX = wrapX;
  fWrapY = wrapY;
  fWrapZ = wrapZ;
}



TGalaxy :: ~TGalaxy()
{
  LOG("TGalaxy", "~TGalaxy()") << "TGalaxy::~TGalaxy() called." << endl;

  removeAll();
}



bool TGalaxy :: addStellarObject( TStellarObject* obj )
{
  if ( obj == 0 )  return false;
  fStObj.push_back( obj );                       // add the obj to the list
  obj->setParent( this );                        // inform the stobj about the new parent

  return true;
}



int2 TGalaxy :: getDimension() const
{
  if ( fSize.getZ() == 0 )  return 2;
  return 3;
}



double TGalaxy :: getDistance( const TPoint& one, const TPoint& two ) const
{
  TPoint Vector = getDistanceVector( one, two );
  return Vector.getLength();
}



double TGalaxy :: getDistance( const TStellarObject* one,
                               const TStellarObject* two ) const
{
  return getDistance( one->getPos(), two->getPos() );
}



TPoint TGalaxy :: getDistanceVector( const TPoint& from, const TPoint& to ) const
{
double xFrom, yFrom, zFrom;
double xTo, yTo, zTo;
double dWay1, dWay2;
TPoint Shortest;

  xFrom = from.getX();
  yFrom = from.getY();
  zFrom = from.getZ();
  xTo = to.getX();
  yTo = to.getY();
  zTo = to.getZ();

  dWay1 = xTo - xFrom;
  if ( fWrapX == true )                                    // there might be a better solution
  {                                                        // using the wrap.
    dWay2 = fSize.getX() - fabs( xTo-xFrom );
    if ( fabs(dWay1) < fabs(dWay2) )
    {
      if ( xFrom < xTo )  Shortest.setX( -dWay1 );
      else Shortest.setX( dWay1 );
    }
    else Shortest.setX( dWay2 );
  }
  else Shortest.setX( dWay1 );

  dWay1 = yTo - yFrom;
  if ( fWrapY == true )
  {
    dWay2 = fSize.getY() - fabs( yTo-yFrom );
    if ( fabs(dWay1) < fabs(dWay2) )
    {
      if ( yFrom < yTo )  Shortest.setY( -dWay1 );
      else Shortest.setY( dWay1 );
    }
    else Shortest.setY( dWay2 );
  }
  else Shortest.setY( dWay1 );

  dWay1 = zTo - zFrom;
  if (fWrapZ == true)
  {
    dWay2 = fSize.getZ() - fabs( zTo-zFrom );
    if ( fabs(dWay1) < fabs(dWay2) )
    {
      if ( zFrom < zTo ) Shortest.setZ( -dWay1 );
      else Shortest.setZ( dWay1 );
    }
    else Shortest.setZ( dWay2 );
  }
  else Shortest.setZ( dWay1 );

  return Shortest;
}



TPoint TGalaxy :: getDistanceVector( const TStellarObject* from,
                                     const TStellarObject* to ) const
{
  return getDistanceVector( from->getPos(), to->getPos() );
}



const string& TGalaxy :: getName() const
{
  return fName;
}



const TPoint& TGalaxy :: getSize() const
{
  return fSize;
}



const TStellarObjectList& TGalaxy :: getStellarObjectList() const
{
  return fStObj;
}



int4 TGalaxy :: getTotalNumber() const
{
  return fStObj.size();
}



// virtual method
int2 TGalaxy :: getType() const
{
  return TType::GALAXY;
}



// virtual method
const string& TGalaxy :: getTypeName() const
{
static const string sTypeName = "TGalaxy";

  return sTypeName;
}



// virtual method
bool TGalaxy :: load( TDataPackageList* in )
{
bool ret = true;

  ret &= TLinkable::load( in );                            // call parent Load method

  ret &= in->getAndDelete( "wrap_x", &fWrapX, true );               // unique=true
  ret &= in->getAndDelete( "wrap_y", &fWrapY, true );
  ret &= in->getAndDelete( "wrap_z", &fWrapZ, true );
  ret &= in->getAndDelete( "size", &fSize, true );
  ret &= in->getAndDelete( "name", &fName, true );

  // and now the galaxy adds itself to the universe
  TUniverse::instance()->addGalaxy( this );

  return ret;
}



bool TGalaxy :: remove( TStellarObject* obj )
{
TStellarObjectList::iterator it;

  find( fStObj.begin(), fStObj.end(), obj );
  if ( it == fStObj.end() )  return false;
  delete *it;
  fStObj.erase( it );
  return true;
}



// virtual method
bool TGalaxy :: save( TDataPackageList* out ) const
{
bool bReturn = true;
static const string sBlockType = "galaxy";

  bReturn &= TLinkable::save( out );                       // call parent Save method

  // additional information to write a block (this data will not be
  // read by the load method)
  bReturn &= out->add( "blocktype", &sBlockType, true, false );

  bReturn &= out->add( "wrap_x", &fWrapX, true );          // unique=true, auto_delete=false
  bReturn &= out->add( "wrap_y", &fWrapY, true );
  bReturn &= out->add( "wrap_z", &fWrapZ, true );
  bReturn &= out->add( "size", &fSize, true );
  bReturn &= out->add( "name", &fName, true );

  return bReturn;
}



bool TGalaxy :: transform( TPoint& point ) const
{
bool b, ret = false;
double d;

  d = point.getX();                                        // x-coordinate
  b = transformCoordinate( d, fSize.getX(), fWrapX );
  if ( b == true )
  {
    point.setX( d );
    ret = true;
  }
  d = point.getY();                                        // y-coordinate
  b = transformCoordinate( d, fSize.getY(), fWrapY );
  if ( b == true )
  {
    point.setY( d );
    ret = true;
  }
  d = point.getZ();                                        // z-coordinate
  b = transformCoordinate( d, fSize.getZ(), fWrapZ );
  if ( b == true )
  {
    point.setZ( d );
    ret = true;
  }

	return ret;
}





//----------------------------------------  Private  ----------------------------------------

void TGalaxy :: removeAll()
{
TStellarObjectList::iterator it;

  LOG("TGalaxy", "removeAll()") << "removing all stellar objects from this galaxy:" << endl;
  LOG_BEGIN_INDENT();

  for ( it=fStObj.begin(); it!=fStObj.end(); it++ )  delete *it;     // deleting all elements
  fStObj.clear();                                                    // and finaly clears the list

  LOG_END_INDENT();
}



bool TGalaxy :: transformCoordinate( double& x, double max, bool wrap ) const
{
bool ret;
int i;

  ret = true;
  if ( wrap == true )
  {
    i = (int) floor( x / max );
    x -= i * max;
    if ( i == 0 )  ret = false;
    else           ret = true;
  }
  else
  {
    if ( x < 0 )         x = 0;
    else if ( x > max )  x = max;
    else                 ret = false;
  }

  return ret;
}





/*
* $Log: galaxy.cpp,v $
* Revision 1.30  2002/07/12 10:06:48  mkrohn5
* include path fix
* many upper->lower fixes
*
* Revision 1.29  2002/06/28 10:12:07  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.28  2002/06/21 08:31:56  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.27  2002/06/07 00:38:37  mkrohn5
* GetLength -> getLength
*
* Revision 1.26  2002/05/15 08:30:55  ishark
* actionsequencer now uses lists + cosmetic fixes
*
* Revision 1.25  2002/05/11 23:59:58  mkrohn5
* minor modifications
*
* Revision 1.24  2002/05/10 10:39:49  mkrohn5
* all kind of changes (my cvs frontend is f#%$§ up so I can not see a detailed list of changes). Have a look at the ChangeLog file to see the changes.
*
* Revision 1.23  2002/01/28 00:58:23  mkrohn5
* added getName method
*
* Revision 1.22  2001/12/07 00:21:15  mkrohn5
* - converted galaxy to the new style
* - galaxy now uses the stellar object list (the code is now a lot more readable :-)
* - made TStellarObjectList a list instead of a deque (makes list operations a lot faster)
*
* Revision 1.21  2001/12/05 00:40:47  mkrohn5
* - some conversions XXX -> xXX
* - implemented the basic rule "fleet movement"
*
* Revision 1.20  2001/12/03 01:40:15  mkrohn5
* fixes / fixed method coding style
*
* Revision 1.19  2001/12/02 14:21:59  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.18  2001/10/31 20:15:35  mkrohn5
* removed #include "common/log.h"
*
* Revision 1.17  2001/07/28 15:23:11  ishark
* added filters in stolist, more client code in sl.cpp
*
* Revision 1.16  2001/07/25 19:12:31  ishark
* major additions in game/sl.cpp - skeleton of localserver
*
* Revision 1.15  2001/07/05 20:34:18  ishark
* added return true in test-item, fixed parser, added action Load/Save
*
* Revision 1.14  2001/07/03 01:06:13  mkrohn5
* a minor change in the galaxy constructor
*
* Revision 1.13  2001/06/24 16:55:12  mkrohn5
* - added documentation
* - redesigned the remove / add part (as discussed with Ralf)
* - made "Transform" public
*
* Revision 1.12  2001/06/21 11:33:04  mkrohn5
* implemented save method (using blocktype)
*
* Revision 1.11  2001/06/13 20:27:50  prolator
* fixed copy'n'paste mistake in constructor (3 times this->bWrapX = bWrapX;)
*
* Revision 1.10  2001/06/13 00:16:28  mkrohn5
* changed return value of GetSize
*
* Revision 1.9  2001/06/12 10:13:28  mkrohn5
* fixed a bug in the load routine
*
* Revision 1.8  2001/06/10 23:26:43  mkrohn5
* * Load & Save do now use the TDataPackageList "stream"
* * small changes to GetStellarObjectList
*
* Revision 1.7  2001/05/10 23:12:21  mkrohn5
* commented load method
*
* Revision 1.6  2001/04/27 01:18:38  mkrohn5
* added "const" to a string
*
* Revision 1.5  2001/04/26 00:05:06  mkrohn5
* changes a return value from "string" to "const string&"
*
* Revision 1.4  2001/04/18 00:35:24  mkrohn5
* load & save does now work
*
* Revision 1.3  2001/04/17 18:56:05  mkrohn5
* start working on load & save methods
*
* Revision 1.2  2001/03/24 00:52:24  mkrohn5
* added documentation and cleaned up the code
*
* Revision 1.1  2001/03/22 02:29:21  mkrohn5
* addition of galaxy and stolist files and cleanup of the interface (galaxy and stolist need some more work though)
*
* Revision 1.1  2000/08/10 00:11:33  mkrohn5
* *** empty log message ***
*
* Revision 1.6  2000/07/04 09:17:34  mkrohn5
* tiny  changes
*
* Revision 1.5  2000/06/27 23:19:43  mkrohn5
* looked trough the whole code and added two new methods. Almost all class members are now documented.
*
* Revision 1.4  2000/06/15 09:57:04  mkrohn5
* *** empty log message ***
*
* Revision 1.3  2000/05/28 22:24:48  mkrohn5
* small changes
*
* Revision 1.2  2000/05/05 20:12:20  mkrohn5
* no message
*
* Revision 1.1  2000/04/02 23:53:02  mkrohn5
* no message
*/
