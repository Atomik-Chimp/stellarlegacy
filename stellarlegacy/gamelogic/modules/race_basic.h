// $Id: race_basic.h,v 1.1 2001/12/01 17:09:58 mkrohn5 Exp $

// Race Basic Header File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __RACE_BASIC_INCLUDED
#define __RACE_BASIC_INCLUDED

#include "gamelogic/race.h"





//----------------------------------------  class TRaceBasic  ----------------------------------------

class TRaceBasic : public TRace
{
  public:
    /**
    * @return The base value for fleet engine failure.
    */
    virtual double getFleetEngineFailure() const;
    /**
    * Loads a TRaceBasic object from the data packages in the data package list.
    * @param in the list of data packages
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a TRaceBasic by adding the data packages to the data package list.
    * @param out the output stream of data packages
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;

};





#endif        // __RACE_BASIC_INCLUDED
