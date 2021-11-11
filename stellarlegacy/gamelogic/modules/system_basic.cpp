// $Id: system_basic.cpp,v 1.2 2001/12/02 14:22:00 mkrohn5 Exp $

// System Basic Code File
// Written by: Marco Krohn

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

#include "gamelogic/modules/system_basic.h"





//----------------------------------------  class TSystemBasic  ----------------------------------------

// Pos=0
TSystemBasic :: TSystemBasic( const TPoint& Pos )
  : TSystem( Pos )
{
}



// virtual method
TSystemBasic :: ~TSystemBasic()
{
}



// virtual method
bool TSystemBasic :: load( TDataPackageList* in )
{
  return TSystem::load( in );
}



// virtual method
bool TSystemBasic :: save( TDataPackageList* out ) const
{
  return TSystem::save( out );
}





/*
* $Log: system_basic.cpp,v $
* Revision 1.2  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.1  2001/12/01 17:09:58  mkrohn5
* added new directory "modules"
*
* Revision 1.5  2001/06/24 16:53:03  mkrohn5
* minor changes due to changed stobj framework
*
*/

