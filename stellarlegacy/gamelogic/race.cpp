// $Id: race.cpp,v 1.12 2002/06/28 10:12:07 mkrohn5 Exp $

// Race Header File
// Written by: Alberto Barsella

// Copyright (C) 1999-2001, Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
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

#include "gamelogic/race.h"
#include "common/point.h"
#include "common/datapackage.h"
#include "admin/player.h"





//----------------------------------------  class TRace  ----------------------------------------

// name=""
TRace :: TRace( const string& name )
{
  LOG("TRace", "TRace") << "TRace object created." << endl;
  setName( name );
}



TRace :: ~TRace()
{
  LOG("TRace", "~TRace()") << "TRace destructor called." << endl;
}



TPlayer* TRace :: getController() const
{
  return fController;
}



const string& TRace :: getName() const
{
  return fName;
}



// virtual method
bool TRace :: load( TDataPackageList* in )
{
bool ret = true;
TDataPackageList* subList = new TDataPackageList();

  // read the object => sub list
  ret &= in->getAndDelete( "race_base", subList, true );

  // read the real data from the sub list
  ret &= TLinkable::load( subList );                       // load parent data
  ret &= fController.load( subList, "controller_link", true );
  ret &= subList->getAndDelete( "name", &fName, true );             // unique=true

  delete subList;                                          // clean up

  return ret;
}



// virtual method
bool TRace :: save( TDataPackageList* out ) const
{
bool bReturn = true;

  TDataPackageList* subList = new TDataPackageList();     // create a new datapackage list
  // bAutoDelete=true so that pSubList is deleted sometime later
  bReturn &= out->add( "race_base", subList, true, true );

  // add the data packages to the new list
  bReturn &= TLinkable::save( subList );                   // save parent data
  bReturn &= fController.save( subList, "controller_link", true );   // unique=true, auto_delete=false
  bReturn &= subList->add( "name", &fName, true, false );

  return bReturn;                                 // return the bool for success
}



void TRace :: setName( const string& name )
{
  fName = name;
}





/*
 * $Log: race.cpp,v $
 * Revision 1.12  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.11  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.10  2002/05/11 23:51:03  mkrohn5
 * added method, minor changes
 *
 * Revision 1.9  2002/02/03 23:17:33  mkrohn5
 * removed debug info
 *
 * Revision 1.8  2001/12/16 11:37:24  ishark
 * TLink now uses dynamic_cast<>, lots of TAction-related fixes
 *
 * Revision 1.7  2001/12/03 01:40:54  mkrohn5
 * removed LOG output
 *
 * Revision 1.6  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.5  2001/12/01 17:15:32  mkrohn5
 * various changes (also updated the interface)
 *
 * Revision 1.4  2001/11/08 21:13:55  ishark
 * action uses new method names, additions in sl/race/game
 *
 * Revision 1.3  2001/07/31 00:31:19  mkrohn5
 * inserted a space
 *
 * Revision 1.2  2001/07/28 15:23:11  ishark
 * added filters in stolist, more client code in sl.cpp
 *
 * Revision 1.1  2001/07/10 17:57:32  ishark
 * rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
 *
 */
