// $Id: race_sl.h,v 1.1 2001/12/01 17:09:58 mkrohn5 Exp $

// Race SL Header File
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

#ifndef __RACE_SL_INCLUDED
#define __RACE_SL_INCLUDED

#include "gamelogic/race.h"





//----------------------------------------  class TRaceSL  ----------------------------------------

class TRaceSL : public TRace
{
  public:
    static const int NONE = -1;

    /** Please keep MAX_PRT up to date! */
    enum                                                   // primary racial traits
    {
      AR = 0,                                              // alternate reality
      CA,                                                  // claim adjuster
      HE,                                                  // hyper expansion
      IS,                                                  // inner strength
      IT,                                                  // interstellar traveller
      JOAT,                                                // jack of all trades
      PP,                                                  // packet physics
      SD,                                                  // space demolition
      SS,                                                  // super stealth
      WM                                                   // war monger
    };
    /** The number of different PRTs. */
    static const int MAX_PRT = 10;
    /** Please keep MAX_LRT up to date! */
    enum
    {
      ARM = 0,                                             // advanced remote mining
      CE,                                                  // cheap engines
      IFE                                                  // improved fuel efficiency
    };
    /** The number of different LRTs. */
    static const int MAX_LRT = 3;

    /**
    * Sets the data members to default values.
    */
    TRaceSL();

    /**
    * @return The base value for fleet engine failure.
    */
    virtual double getFleetEngineFailure() const;
    /**
    * @return Returns the PRT of the race.
    */
    int2 getPRT() const;
    /**
    * @param A LRT e.g. TRaceSL::IFE.
    * @return Wheter the race has the LRT or not.
    */
    bool hasLRT( int2 lrt ) const;
    /**
    * Loads a TRaceSL object from the data packages in the data package list.
    * @param in the list of data packages
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a TRaceSL by adding the data packages to the data package list.
    * @param out the output stream of data packages
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Sets the PRT for this race. Note that it is only one time possible
    * to set the PRT, after that changes are impossible!
    * @param prt The primary racial trait for the race, e.g. TRaceSL::JOAT.
    * @return @c true = the prt was accepted, otherwise @c false (for example
    *   if a prt was already set).
    */
    bool setPRT( int prt );

  private:
    /** primary racial trait */
    int2 fPRT;
    /** the different lesser racial traits */
    bool fLRT[MAX_LRT];
};





#endif        // __RACE_SL_INCLUDED
