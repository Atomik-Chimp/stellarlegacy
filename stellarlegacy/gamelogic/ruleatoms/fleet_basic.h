// $Id: fleet_basic.h,v 1.2 2001/12/03 01:35:10 mkrohn5 Exp $

// Fleet Basic Header File
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

#ifndef __FLEET_BASIC_INCLUDED
#define __FLEET_BASIC_INCLUDED

#include "gamelogic/fleet.h"





//----------------------------------------  class TFleetBasic  ----------------------------------------

/**
* @class TFleetBasic
* @brief Basic rule set for TFleet.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: fleet_basic.h,v 1.2 2001/12/03 01:35:10 mkrohn5 Exp $
* @see TFleet
*
* This class implements a very simple rule set: the basic rules.
* Basically all virtual methods of the TFleet class are filled with
* life. The exact definition of the rules is documented below.
*/
class TFleetBasic : public TFleet
{
  public:
    TFleetBasic( const TPoint& Pos=0 );
    virtual ~TFleetBasic();
};





#endif        // __FLEET_BASIC_INCLUDED
