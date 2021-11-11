// $Id: fleet_basic.cpp,v 1.2 2001/12/03 01:35:10 mkrohn5 Exp $

// Fleet Basic Code File
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

#include <cmath>

#include "gamelogic/fleet.h"
#include "gamelogic/modules/fleet_basic.h"
#include "gamelogic/subfleet.h"





//----------------------------------------  class TFleetBasic  ----------------------------------------

// Pos=0
TFleetBasic :: TFleetBasic( const TPoint& Pos )
  : TFleet( Pos )
{
}


// virtual method
TFleetBasic :: ~TFleetBasic()
{
}





/*
* $Log: fleet_basic.cpp,v $
* Revision 1.2  2001/12/03 01:35:10  mkrohn5
* cleaned up the fleet interface
*
* Revision 1.1  2001/12/01 17:09:58  mkrohn5
* added new directory "modules"
*
* Revision 1.5  2001/06/24 16:53:03  mkrohn5
* minor changes due to changed stobj framework
*
* Revision 1.4  2001/06/23 23:29:10  prolator
* moved GetNumberOfShips to TFleet
*
* Revision 1.3  2001/05/10 23:19:40  mkrohn5
* basic framework for subfleets
*
*/

