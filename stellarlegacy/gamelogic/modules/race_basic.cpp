// $Id: race_basic.cpp,v 1.4 2002/06/28 10:12:07 mkrohn5 Exp $

// Race Basic Code File
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
#include "gamelogic/modules/race_basic.h"





//----------------------------------------  class TRaceBasic  ----------------------------------------

double TRaceBasic :: getFleetEngineFailure() const
{
  return 0;
}



// virtual method
bool TRaceBasic :: load( TDataPackageList* in )
{
bool ret = true;

  ret &= TRace::load( in );                                // call the parent

  return ret;
}



// virtual method
bool TRaceBasic :: save( TDataPackageList* out ) const
{
static const string blockType = "race";
bool ret;

  // additional information to write a block (this data will not be
  // read by the load method)
  ret &= out->add( "blocktype", &blockType, true, false );

  ret &= TRace::save( out );                               // save parent data

  return ret;
}





/**
* $Log: race_basic.cpp,v $
* Revision 1.4  2002/06/28 10:12:07  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.3  2001/12/03 01:36:42  mkrohn5
* minor changes
*
* Revision 1.2  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.1  2001/12/01 17:09:58  mkrohn5
* added new directory "modules"
*
* Revision 1.2  2001/07/11 00:12:49  mkrohn5
* added load and save method for TRaceBasic
*
*/
