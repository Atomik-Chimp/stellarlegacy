// $Id: property.cpp,v 1.6 2002/06/28 10:12:07 mkrohn5 Exp $

// Property Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

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
#include "gamelogic/property.h"
#include "gamelogic/race.h"





//----------------------------------------  TProperty  ----------------------------------------

// creator=0, owner=0
TProperty :: TProperty( TRace* creator, TRace* owner )
{
  setCreator( creator );
  setOwner( owner );
}



TRace* TProperty :: getCreator() const
{
  return fCreator.getPointerToDest();
}



TRace* TProperty :: getOwner() const
{
  return fOwner.getPointerToDest();
}



// virtual method
bool TProperty :: load( TDataPackageList* in )
{
bool bReturn = true;
TDataPackageList* pSubList = new TDataPackageList();

  // read the object => sub list
  bReturn &= in->getAndDelete( "property", pSubList, true );

  // read the real data from the sub list
  bReturn &= TLinkable::load( pSubList );                  // load parent data
  bReturn &= fCreator.load( pSubList, "creator", true );   // load "real" data
  bReturn &= fOwner.load( pSubList, "owner", true );

  delete pSubList;                                         // clean up

  return bReturn;
}



// virtual method
bool TProperty :: save( TDataPackageList* out ) const
{
bool bReturn = true;

  TDataPackageList* pSubList = new TDataPackageList();          // create a new datapackage list
  // bAutoDelete=true so that pList is deleted sometime
  bReturn &= out->add( "property", pSubList, true, true );

  // add the data packages to the new list
  bReturn &= TLinkable::save( pSubList );                       // save parent data
  bReturn &= fCreator.save( pSubList, "creator", true );        // save "real" data
  bReturn &= fOwner.save( pSubList, "owner", true );

  return bReturn;
}



void TProperty :: setCreator( TRace* creator )
{
  fCreator.setDest( creator );
}



void TProperty :: setOwner( TRace* owner )
{
  fOwner.setDest( owner );
}





/*
 * $Log: property.cpp,v $
 * Revision 1.6  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.5  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.4  2002/03/24 13:36:36  mkrohn5
 * mostly style changes
 *
 * Revision 1.3  2001/12/03 01:40:15  mkrohn5
 * fixes / fixed method coding style
 *
 * Revision 1.2  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.1  2001/07/31 00:29:45  mkrohn5
 * added property class to project
 *
 */



