// $Id: system_basic.h,v 1.2 2001/12/02 14:22:00 mkrohn5 Exp $

// System Basic Header File
// Written by: Marco Krohn

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

#ifndef __SYSTEM_BASIC_INCLUDED
#define __SYSTEM_BASIC_INCLUDED

#include "gamelogic/system.h"

class TDataPackageList;





//----------------------------------------  class TSystemBasic  ----------------------------------------

class TSystemBasic : public TSystem
{
  public:
    TSystemBasic( const TPoint& Pos=0 );
    virtual ~TSystemBasic();

    int2 GetNumberOfPlanets();
    /**
    * Loads a system (rulesystem: basic) from a list of data package.
    * @param in The input "stream" of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a system to (rulesystem: basic) a list of data package.
    * @param in The output "stream" of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;
};





#endif        // __SYSTEM_BASIC_INCLUDED
