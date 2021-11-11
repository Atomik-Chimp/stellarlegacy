// $Id: stobj.h,v 1.28 2002/06/07 00:39:55 mkrohn5 Exp $

// Stellar Object Header File
// Written by: Jai Shaw,
//             Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 1996 - 1999, Jai Shaw, <Jai@towersoft.com.au>
//               2000 - 2002, Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __STOBJ_INCLUDED
#define __STOBJ_INCLUDED

#include "gamelogic/action.h"
#include "gamelogic/galaxy.h"
#include "common/global.h"
#include "common/link.h"
#include "common/point.h"
#include "gamelogic/waypoint.h"

#include <string>

class TDataPackageList;
class TGalaxy;
class TStellarObject;
class TWaypoint;





//----------------------------------------  Misc. Functions  ----------------------------------------

/**
* Stream function for TStellarObject, allowing cout << stobj.
* The output shows the name, ID and position of the object.
* @param Stream the current ostream for output.
* @param StellarObject this one will be written to the output stream.
* @return The old stream plus the new output.
*/
ostream& operator<<( ostream& Stream, const TStellarObject& StellarObject );





//----------------------------------------  class TStellarObject  ----------------------------------------

/**
* @class TStellarObject
* @brief Base class for all stellar objects.
* @author Jai Shaw <Jai@towersoft.com.au>, Marco Krohn <marco.krohn@gmx.de>
* @version $Id: stobj.h,v 1.28 2002/06/07 00:39:55 mkrohn5 Exp $
* @see TStellarObjectList, TActionObject
*
* TStellarObject is a base class for all kinds of stellar objects,
* such as fleets, planets and minefields. All stellar objects
* have a name, a position in space and belong to a galaxy. A stellar
* object is derived from TActionObject and therefore can execute
* actions.
*/
class TStellarObject : public TActionObject
{
  friend class TGalaxy;

  public:
    TStellarObject();
    TStellarObject( const TPoint& Point );
    /**
    * At the moment this method sends only a message to the log file.
    */
    virtual ~TStellarObject();

    /**
    * Adds a waypoint to the waypoint list @a fWaypointList.
    * @param The new waypoint.
    */
    void addWaypoint( const TWaypoint& waypoint );
    /**
    * Attaches the stellar object @c A to another one @c B. This means that
    * @c A will move together with object @c B. To be more precise:
    * stellar object @c B determines the position of the object A.
    * Note: the method will attach the object to @e Dest without looking at
    * the current state of the object (e.g. if it is already attached). Also
    * this means that the object is at once at the same position as @e pDest.
    * @param Dest The stellar object @c B.
    * @see Detach
    */
    void Attach( TStellarObject* pDest );
    /**
    * Overload of TActionObject method to filter action types.
    */
    virtual bool canPerformAction(const TAction& action);
    /**
    * Overload of TActionObject method to filter action types.
    */
    virtual bool canBeObjectInAction(const TAction& action);
    /**
    * Detaches the stellar object from another object.
    * @see Attach
    */
    void Detach();
    /**
    * @return The galaxy the stellar object belongs to.
    */
    TGalaxy* getGalaxy() const;
    /**
    * @return The name of the stellar object.
    */
    const string& getName() const;
    /**
    * @return The position of the stellar object.
    */
    const TPoint& getPos() const;
    /**
    * @return The type of the stellar object--e.g. TType::TFleet.
    * @see TType
    */
    virtual int2 getType() const;
    /**
    * @return The name of the class: "TStellarObject".
    */
    virtual const string& getTypeName() const;
    /** FIXME, do we need a method like TWaypoint& getWaypoint( int2 waypointNumber ) const?
    * @return The waypoint list @a fWaypointList.
    */
    const TWaypointList* getWaypointList() const;
    /**
    * @return @c true if there are waypoints left, @c false if the list of waypoints
    *   (@a fWaypointList) is empty.
    */
    bool hasWaypoint() const;
    /**
    * With the method insertWaypoint you can insert a waypoint in the
    * waypoint list. The posistion in the waypoint list is identified with
    * the number of the waypoint in the list, behind which the new waypoint
    * shall be inserted.
    *
    * Example: A waypoint
    * to be inserted at posistion 0 is always inserted at the head of the
    * list, A waypoint to be inserted at position 1, is inserted after the
    * head of the list, if there is already a head. Else the waypoint isn't
    * inserted. If a list contains 3 waypoints, and you want to add a
    * waypoint at position 3, the waypoint is inserted as tail and the list
    * contains then 4 waypoints.
    *
    * @param waypoint the waypoint to be inserted
    * @param insertPosistion the posistion, after which the waypoint is to be
    *   inserted
    * @return @c true, if the waypoint is inserted successfully, @c false, if
    *   the list is to short to have the wanted posistion
    */
    bool insertWaypoint( const TWaypoint& waypoint, int2 insertPosition );
    /**
    * Loads a TStellarObject. Note that classes that are derived from
    * this class @e must call TStellarObject::Load explicitly to load the data
    * correctly. After loading the stellar object it will automatically inform
    * TGalaxy (so that TGalaxy adds this object to its list).
    * @param in The list of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Compare stellar objects.
    * @param src Stellar Object to compare against.
    * @return @c true if object ID match otherwise @c false.
    */
    bool operator==( const TStellarObject& Src ) const;
    /**
    * To compare values for sorting.
    * @param src Stellar Object to compare against.
    * @return @c true if object ID is less than source objectID otherwise @c false.
    */
    bool operator<( const TStellarObject& Src ) const;
    /**
    * With removeWaypoint you can remove a waypoint from the waypoint list of
    * the stellar object. The waypoint is identified with its number in the
    * list. The first waypoint has the number 0. If the there is no waypoint
    * with this number, the method returns @c false, else it returns @c true
    * after removing the waypoint from the list.
    * @param waypointNumber the number of the waypoint to be removed
    * @returns @true, if the waypoint was removed successfully, @c false, if
    *   there wasn't any waypoint with this number
    */
    bool removeWaypoint( int2 waypointNumber );
    /**
    * With replaceWaypoint you can replace a waypoint in the waypoint list of
    * the stellar object with another waypoint. The waypoint to be replaced
    * is identified with its number in the list. The first waypoint has the
    * number 0. If the there is no waypoint with this number, the method
    * returns @c false, else it returns @c true after replacing the waypoint
    * in the list withe one given as parameter.
    * @param waypoint the waypoint to be inserted
    * @param waypointNumber the number of the waypoint to be repaced
    * @returns @c true, if the waypoint was replaced successfully, @c false, if
    *   there wasn't any waypoint with this number
    */
    bool replaceWaypoint( const TWaypoint& Waypoint, int2 waypointNumber );
    /**
    * Saves a TStellarObject by adding the data packages to the list. Note that
    * classes that are derived from this class @e must call TStellarObject::Save
    * explicitly to save the data correctly.
    * @param out The output stream of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Sets the name of the stellar object.
    * @param sName The new name of the object.
    */
    void setName( const string& sName );
    /**
    * Sets the position of the stellar object in space.
    * Note: the method calls @ref TGalaxy#Transform to ensure that
    * the position is within the galaxy.
    * @param Pos The position in space.
    */
    void setPos( const TPoint& Pos );
    /**
    * Writes the class @e TStellarObject to a stream using the following format:
    * "ID, Name, Pos".
    * @param Stream The (old) output stream.
    * @return The (new) stream.
    */
    ostream& Write( ostream& Stream ) const;       // output

  private:
    /**
    * All stellar objects must belong to a galaxy. This link points to
    * the current galaxy. Only jumps between galaxies may change this link.
    */
    TLink<TGalaxy> Galaxy;
    /**
    * The current "waypoint" of the fleet (this may be another stellar object).
    */
    TWaypoint WP;
    /**
    * The list of waypoints. The auto delete mode is set to @c true
    * in the constructor.
    */
    TWaypointList fWaypointList;
    /**
    * The speed of the stellar object.
    */
    double dSpeed;
    /**
    * The name of the stellar object
    */
    string sName;

    /**
    * Sets the @a Galaxy variable and transforms the point so that it is
    * guranteed that the point is within the boundaries of the new galaxy.
    * Note that this method will @e not (apart from the above)
    * trigger any further actions in TGalaxy for example this will @e not
    * inform the old galaxy that the parent changed.
    * This method is called by @ref TGalaxy#Add.
    * @param pGalaxy The new parent of this object.
    * @see TGalaxy#Transform
    */
    void setParent( TGalaxy* pGalaxy );
};





#endif      // __STOBJ_INCLUDED
