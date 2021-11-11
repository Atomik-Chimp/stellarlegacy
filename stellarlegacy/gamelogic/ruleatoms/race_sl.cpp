// $Id: race_sl.cpp,v 1.5 2002/06/28 10:12:08 mkrohn5 Exp $

// Race SL Code File
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
#include "gamelogic/modules/race_sl.h"





//----------------------------------------  class TRaceSL  ----------------------------------------

TRaceSL :: TRaceSL() : TRace()
{
int2 i;

  fPRT = NONE;
  for ( i=0; i<MAX_LRT; i++ )  fLRT[i] = false;
}



double TRaceSL :: getFleetEngineFailure() const
{
  if ( hasLRT(CE) == true )  return 0.1;
  return 0.0;
}



bool TRaceSL :: hasLRT( int2 lrt ) const
{
  if ( lrt<0 || lrt>=MAX_LRT)  return false;
  return fLRT[lrt];
}



// virtual method
bool TRaceSL :: load( TDataPackageList* in )
{
bool ret = true;
int i;

  ret &= TRace::load( in );                                // call the parent
  ret &= in->getAndDelete( "prt", &fPRT, true );           // unique=true
  for ( i=0; i<MAX_LRT; i++ )
  {
    ret &= in->getAndDelete( "lrt", &fLRT[i], false );     // unique=false
  }


  return ret;
}



// virtual method
bool TRaceSL :: save( TDataPackageList* out ) const
{
static const string blockType = "race";
bool ret;
int2 i;

  // additional information to write a block (this data will not be
  // read by the load method)
  ret &= out->add( "blocktype", &blockType, true, false );

  ret &= TRace::save( out );                               // save parent data
  ret &= out->add( "prt", &fPRT, true, false );            // autoDelete=false
  for ( i=0; i<MAX_LRT; i++ )
  {
    ret &= out->add( "lrt", &fLRT[i], false, false );      // unique=false, autoDelete=false
  }

  return ret;
}



bool TRaceSL :: setPRT( int prt )
{
  if ( fPRT != NONE )  return false;
  if ( prt<0 || prt>=MAX_PRT)  return false;
  fPRT = prt;
  return true;
}





/**
* $Log: race_sl.cpp,v $
* Revision 1.5  2002/06/28 10:12:08  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.4  2002/06/21 08:31:56  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.3  2002/06/04 09:27:04  mkrohn5
* added parent constructor call
*
* Revision 1.2  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.1  2001/12/01 17:09:58  mkrohn5
* added new directory "modules"
*
*/
