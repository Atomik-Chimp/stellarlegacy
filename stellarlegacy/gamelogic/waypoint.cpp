// $Id: waypoint.cpp,v 1.10 2002/06/28 10:12:07 mkrohn5 Exp $

// Waypoint Code File
// Written by: Marco Krohn <marco.krohn@gmx.de>

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
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

#include "common/datapackage.h"
#include "gamelogic/stobj.h"
#include "gamelogic/waypoint.h"

using namespace std;





//----------------------------------------  class TWaypoint  ----------------------------------------

TWaypoint :: TWaypoint()
{
  reset();
}



TWaypoint :: TWaypoint( const TWaypoint& wp )
{
  // it should be safe to use the assignment operator here
  *this = wp;
}



// speed=0
TWaypoint :: TWaypoint( TStellarObject* stellarObject, double speed )
{
  setStellarObject( stellarObject );
  setWantedSpeed( speed );
}



// speed=0
TWaypoint :: TWaypoint( const TPoint& pos, double speed )
{
  setPos( pos );
  setWantedSpeed( speed );
}



const TPoint& TWaypoint :: getPos() const
{
  if ( isStellarObject() == true )  return fLinkStObj->getPos();
  return fPos;
}



TStellarObject* TWaypoint :: getStellarObject() const
{
  if ( isStellarObject() == true )  return fLinkStObj.getPointerToDest();
  return 0;
}



double TWaypoint :: getWantedSpeed() const
{
  return fWantedSpeed;
}



bool TWaypoint :: isStellarObject() const
{
  if ( fLinkStObj.isNull() == true )  return false;
  return true;
}



// unique=true
bool TWaypoint :: load( TDataPackageList* in, const string& identifier,
                        bool unique )
{
bool ret = true;

  TDataPackageList* list = new TDataPackageList();

  // read the object => sub list
  ret &=in->getAndDelete( identifier, list, unique );

  // read the real data from the sub list
  ret &= fLinkStObj.load( list, "link", true );
  ret &= fPos.load( list, "pos", true );
  ret &= list->getAndDelete( "wanted_speed", &fWantedSpeed, true );

  // delete the temp list
  delete list;

  return ret;
}



TWaypoint& TWaypoint :: operator=( const TWaypoint& wp )
{
  if ( this != &wp )  {                                    // ensure that the object are not identical
    fLinkStObj = wp.fLinkStObj;
    fPos = wp.fPos;
    fWantedSpeed = wp.fWantedSpeed;
  }
  return *this;
}



bool TWaypoint :: operator==( const TWaypoint& src ) const
{
  if ( src.fLinkStObj == fLinkStObj && src.fPos == fPos &&
       src.fWantedSpeed == fWantedSpeed )  return true;
  return false;
}



void TWaypoint :: reset()
{
  fWantedSpeed = 0.0;
  fPos.setNull();
  fLinkStObj.setNull();
}



// bUnique=true
bool TWaypoint :: save( TDataPackageList* out, const string& identifier,
                        bool unique ) const
{
bool ret = true;

  TDataPackageList* list = new TDataPackageList();        // create a new datapackage list

  // bAutoDelete=true so that pList is deleted sometime
  ret &= out->add( identifier, list, unique, true );

  // add the data packages to the new list
  ret &= fLinkStObj.save( list, "link", true );
  ret &= fPos.save( list, "pos", true );
  ret &= list->add( "wanted_speed", &fWantedSpeed, true );

  return ret;
}



void TWaypoint :: setPos( const TPoint& pos )
{
  fPos = pos;
  fLinkStObj.setNull();
}



void TWaypoint :: setStellarObject( TStellarObject* stellarObject )
{
  fPos.setNull();
  fLinkStObj.setDest( stellarObject );
}



void TWaypoint :: setWantedSpeed( double speed )
{
  fWantedSpeed = speed;
}





/*
 * $Log: waypoint.cpp,v $
 * Revision 1.10  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.9  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.8  2002/06/07 00:39:20  mkrohn5
 * implemented getWantedSpeed
 *
 * Revision 1.7  2002/05/11 00:24:53  mkrohn5
 * bug fix + added some log messages
 *
 * Revision 1.6  2002/05/10 10:39:49  mkrohn5
 * all kind of changes (my cvs frontend is f#%$§ up so I can not see a detailed list of changes). Have a look at the ChangeLog file to see the changes.
 *
 * Revision 1.5  2002/04/01 19:15:16  mkrohn5
 * added "wanted speed" to a waypoint
 *
 * Revision 1.4  2002/03/24 13:36:37  mkrohn5
 * mostly style changes
 *
 * Revision 1.3  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.2  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.1  2001/08/07 20:57:45  mkrohn5
 * recommit waypoint files
 *
 * Revision 1.8  2001/06/29 01:00:46  mkrohn5
 * fixed memory leak in save method
 *
 * Revision 1.7  2001/06/25 21:07:11  ishark
 * modified parser (still bad) + removed minor warnings in waypoint
 *
 * Revision 1.6  2001/06/24 16:51:47  mkrohn5
 * renamed the "Set" methods
 *
 * Revision 1.5  2001/06/22 00:46:36  mkrohn5
 * fixed a few memory leaks
 *
 * Revision 1.4  2001/06/21 23:46:28  mkrohn5
 * fixed a couple of bugs in the load & save method
 *
 * Revision 1.3  2001/06/21 11:23:47  mkrohn5
 * * implemented the new load and save method
 * * using TPList for TWaypoint List now
 *
*/
