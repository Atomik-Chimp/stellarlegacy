// $Id: fleet.h,v 1.17 2002/06/07 00:35:11 mkrohn5 Exp $

// Fleet Header File
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

#ifndef __FLEET_INCLUDED
#define __FLEET_INCLUDED

#include <deque>

#include "common/osval.h"
#include "gamelogic/stobj.h"

class TDataPackageList;
class TSubFleet;





//----------------------------------------  class TFleet  ----------------------------------------

/**
* @class TFleet
* @brief A fleet is the composition of different ships.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: fleet.h,v 1.17 2002/06/07 00:35:11 mkrohn5 Exp $
* @see TStellarObject, TSubFleet, TFleetBasic
*
* A fleet is basically a list of TSubFleet objects. Similarily
* to the other classes TPlanet, TSystem etc. this class is pure
* virtual meaning that it just defines the general interface for
* fleets in general.
*/
class TFleet : public TStellarObject
{
  public:
    /**
    * Initializes the fleet with a position in space and sets the current
    * speed to 0.
    * @param Pos Position in space.
    */
    TFleet( const TPoint& Pos=0 );
    /**
    * Deletes all subfleets.
    */
    virtual ~TFleet();

    /**
    * Adds a subfleet to the fleet. Note: TFleet is now responsible for
    * the subfleet in the sense that it will delete the TSubFleet
    * object when the desturtor is called. Also note that @e no check
    * is performed to prevent that a sub fleet is added twice.
    */
    virtual void Add( TSubFleet* pSubFleet );
    /**
    * Overload of TActionObject method to filter action types.
    */
    virtual bool canPerformAction(const TAction& action);
    /**
    * Overload of TActionObject method to filter action types.
    */
    virtual bool canBeObjectInAction(const TAction& action);
    /**
    * @return The total number of ships calculated by summing up the number of
    *   ships of the subfleets.
    * @see TSubFleet#getNumberOfShips
    */
    TOSVal getNumberOfShips() const;
    /**
    * @return The current speed of the fleet.
    */
    double getSpeed() const;
    /**
    * @return The type of the stellar object, here: TType::FLEET.
    * @see TType
    */
    virtual int2 getType() const;
    /**
    * @return The name of the class: "TFleet".
    */
    virtual const string& getTypeName() const;
    /**
    * The method Load loads a TFleet object from the data packages in
    * the list.
    * @param in the list of data packages
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    * @see TLinkable
    */
    virtual bool load( TDataPackageList* in );
    /**
    * This method removes a subfleet from the fleet. It will also delete the
    * subfleet.
    * @param pSubFleet The subfleet which will be removed.
    * @return @c true = successfuly removed the subfleet from the list,
    *   otherwise @c false (means that the object is not an element of the list).
    */
    virtual bool Remove( TSubFleet* pSubFleet );
    /**
    * The method Save saves a TFleet by adding the data packages to the
    * list.
    * @param out the output stream of data packages
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    * @see TLinkable
    */
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Sets the current speed of the fleet. The value is only stored during
    * fleet movement. Actually the fleet tries to move with the speed given
    * by the waypoint list, but under some circumstances (e.g. mine fields)
    * the current speed can be different of the wanted speed.
    * @param speed The new current speed.
    */
    void setSpeed( double speed );
    /**
    * This method moves the subfleet given as parameter from this fleet to
    * the fleet given as second parameter. The method will return @c false,
    * if the subfleet was not part of this fleet and the move couldn't be
    * done.
    * @param pSubFleet the subfleet which will be moved
    * @param pNewFleet the new fleet the subfleet will be moved to
    * @return @c true = successfuly removed the subfleet from the list,
    *   otherwise @c false (means that the object is not an element of the list).
    */
    virtual bool TransferSubFleet( TSubFleet* pSubFleet, TFleet* pNewFleet );

  protected:
    /** Current speed of the fleet */
    double fSpeed;
    /** List of all subfleets. */
    TPList<TSubFleet> fSubFleets;
};





#endif        // __FLEET_INCLUDED
