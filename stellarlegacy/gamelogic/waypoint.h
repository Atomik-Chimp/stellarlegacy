// $Id: waypoint.h,v 1.9 2002/06/07 00:39:20 mkrohn5 Exp $

// Waypoint Header File
// Written by: Marco Krohn <marco.krohn@gmx.de>

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

#ifndef __WAYPOINT_INCLUDED
#define __WAYPOINT_INCLUDED

#include "common/link.h"
#include "common/plist.h"
#include "common/point.h"

class TDataPackageList;
class TPoint;
class TStellarObject;





//----------------------------------------  class TWaypoint  ----------------------------------------

/**
* @class TWaypoint
* @brief Stores waypoints.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: waypoint.h,v 1.9 2002/06/07 00:39:20 mkrohn5 Exp $
* @see TPoint, TStellarObject
*
* A waypoint is either a point in space or a stellar object plus the
* information about the wanted speed to approach the point. If the
* waypoint was initialized as a point in space the waypoint will
* always stay the same. In contrary to a waypoint which was set to a
* stellar object. These waypoints will always return the position of the
* stellar object so the @ref getPos return value depends on the position
* of the stellar object.
*/
class TWaypoint
{
  public:
    /**
    * Initializes the data with 0.
    */
    TWaypoint();
    /**
    * Copy constructor.
    */
    TWaypoint( const TWaypoint& wp );
    /**
    * Calls @ref setStellarObject to initialize the waypoint.
    */
    TWaypoint( TStellarObject* stellarObject, double speed=0 );
    /**
    * Calls @ref setPos and @ref setWantedSpeed to initialize the waypoint.
    * @param pos A point in space.
    * @param speed The speed in units of the light speed.
    */
    TWaypoint( const TPoint& pos, double speed=0 );

    /**
    * @return The position of the waypoint in space. If the waypoint
    *   was initialized with a stellar object the return value is the
    *   position of the stellar object.
    */
    const TPoint& getPos() const;
    /**
    * @return The pointer to the stellar object or 0 if @ref isStellarObject
    *   returns @c false.
    */
    TStellarObject* getStellarObject() const;
    /**
    * @return The wanted speed of the stellar object.
    */
    double getWantedSpeed() const;
    /**
    * @return @c true if the waypoint was initialized with a stellar object,
    *   otherwise @c false.
    */
    bool isStellarObject() const;
    /**
    * Loads a TWaypoint object from a list of data packages.
    * Note that a successful load will delete the datapackage from the data
    * package list as well as the datapackage itself.
    * @param in The input stream of data packages.
    * @param identifier The identifier to look for.
    * @param unique Loads the data only if the identifier is unique.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    bool load( TDataPackageList* in, const string& identifier,
               bool unique=true );
    /**
    * Assignment operator is simply doing an element by element copy.
    * @param wp The waypoint to assign from.
    * @return The new object.
    */
    TWaypoint& operator=( const TWaypoint& wp );
    /**
    * Compares waypoints.
    * @param src Waypoint to compare with.
    * @return @c true if objects settings are identical otherwise @c false.
    */
    bool operator==( const TWaypoint& src ) const;
    /**
    * Sets @a fPos and @a fLinkStObj to null.
    */
    void reset();
    /**
    * Creates the data packages of a TWaypoint object and adds them to
    * the data package list.
    * @param out The list of data packages.
    * @param identifier The identifier which is used to store and find the data.
    * @param unique If set to @c true the method will check if the identifier was
    *   already used in the data package list.
    * @return @c true if everything worked fine, otherwise @c false (e.g. if
    *   the identifier was already used in the data package list).
    */
    bool save( TDataPackageList* out, const string& identifier,
               bool unique=true ) const;
    /**
    * Initializes the waypoint with an ordinary point in space.
    * @param pos A point in space.
    */
    void setPos( const TPoint& pos );
    /**
    * Initializes the waypoint with an stellar object.
    * @param stellarObject The stellar object the waypoint is set to.
    */
    void setStellarObject( TStellarObject* stellarObject );
    /**
    * Sets the wanted speed to approach a destination.
    * @param speed The wanted speed in units of the light speed.
    */
    void setWantedSpeed( double speed );

  private:
    /**
    * The position is determined by a stellar object if and only
    * if fLinkStObj is @e not set to null.
    */
    TLink<TStellarObject> fLinkStObj;
    /**
    * The position of the object. This value is only valid if
    * @a fLinkStObj is set to null.
    */
    TPoint fPos;
    /**
    * The wanted speed to approach the destination.
    */
    double fWantedSpeed;
};





//----------------------------------------  class TWaypointList  ----------------------------------------

/**
* @class TWaypointList
* @brief Stores a list of waypoints.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: waypoint.h,v 1.9 2002/06/07 00:39:20 mkrohn5 Exp $
* @see TWaypoint
*
* This class stores and manages a list of TWaypoint objects.
*/
class TWaypointList : public TPEList<TWaypoint>
{
};





#endif // __WAYPOINT_INCLUDED
