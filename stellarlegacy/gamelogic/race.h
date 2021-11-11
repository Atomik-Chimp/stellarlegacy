// $Id: race.h,v 1.8 2002/05/11 23:51:03 mkrohn5 Exp $

// Race Header File
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

#ifndef __RACE_INCLUDED
#define __RACE_INCLUDED

#include "common/link.h"

class TFleet;
class TPlayer;





//----------------------------------------  class TRace  ----------------------------------------

/**
* @class TRace
* @brief Base class for race specific data.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: race.h,v 1.8 2002/05/11 23:51:03 mkrohn5 Exp $
* @see TLinkable
*/
class TRace : public TLinkable
{
  public:
    /**
    * FIXME
    */
    TRace( const string& name="" );
    virtual ~TRace();

    /**
     * Fetch the player who's controlling this race
     * @return a pointer to the player object.
     */
    TPlayer* getController(void) const;
    /**
    * @return The base value for fleet engine failure.
    */
    virtual double getFleetEngineFailure() const = 0;
    /**
     * Fetch the name of the race.
     * @return a reference to the string containing the race name.
     */
    const string& getName() const;
    /**
    * Loads a TRace object from the data packages in the data package list.
    * @param in the list of data packages
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a TRace by adding the data packages to the data package list.
    * @param out the output stream of data packages
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Sets the name of the race.
    * @param name The new name of the race.
    */
    void setName( const string& name );

  private:
    /** The player which controls this race */
    TLink<TPlayer> fController;
    /** Name of the race */
    string fName;
};



#endif        // __RACE_INCLUDED
