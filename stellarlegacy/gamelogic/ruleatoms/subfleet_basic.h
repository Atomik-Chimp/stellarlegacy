// $Id: subfleet_basic.h,v 1.4 2002/04/11 21:35:50 prolator Exp $
//
// subfleet basic rules implementation Header File
// Written by: Ralf Laue
//
// Copyright (C) 2001 - , Ralf Laue <ralf.laue@gmx.de>
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

#ifndef __SUBFLEET_BASIC_INCLUDED
#define __SUBFLEET_BASIC_INCLUDED

#include "common/defs.h"
#include "gamelogic/subfleet.h"

class TFleet;
class TShipDesign;

/**************************** class TSubFleetBasic *****************************/


/** @class TSubFleetBasic
 *  @brief The basic rule implemenation for subfleets.
 *  @author Ralf Laue <ralf.laue@gmx.de>
 *  @version $Id: subfleet_basic.h,v 1.4 2002/04/11 21:35:50 prolator Exp $
 *  @see TFleet, TShipDesign
 *
 *  This is the basic rules implemenation for the pure virtual class TSubFleet.
 *  It implements the rule depending methods for a subfleet according to the
 *  basic rules (see RFC file for rules).                                      */
class TSubFleetBasic : public TSubFleet
{
  public:
    /** This constructor creates and initializes a new subfleet. The ship
     *  design the subfleet is of, is given in the parameter. The number of
     *  ships the subfleet should have initailly, is given in the second
     *  parameter.
     *  @param ShipDesign the ship design the subfleet is of
     *  @param NumberOfShips the number of ships the subfleet has initially    */
    TSubFleetBasic( TShipDesign* ShipDesign, int2 NumberOfShips );
    /** This constructor also creates a new subfleet. It is initialized with
     *  the values of the subfleet given in the parameter. This is the copy
     *  constructor. All values ecxept the fleet are copied. The caller is
     *  responsible to inform the fleet about its new subfleet. This fleet
     *  will then inform the subfleet about its new parent. FIXME, at the
     *  moment the fields of TActioObject are NOT copied.
     *  @param OldSubFleet the subfleet the values are copied from             */
    TSubFleetBasic( TSubFleetBasic& OldSubFleet );
    /** This destructor destrcucts the object. It has nothing to do, because
     *  the destructor of its parent takes care of everything and it is called
     *  automatically.                                                         */
    virtual ~TSubFleetBasic();
    /** With the method getUpgradeCosts you can get the costs the planned
     *  upgrade will cost. The costs are returned in the paremeter
     *  UpgradeCosts. The costs will be 150% of the cost difference between
     *  the two designs. If the old design costs more, then the costs will be
     *  zero, but you don't get any refund. FIXME, this implementation does
     *  not yet look at singel substances, only at the whole set. That means,
     *  if the old design is in only one substance more expensive than the new,
     *  there will be no costs. Furthermore the method returns, whether there
     *  is an upgrade planned.
     *  @parameter UpgradeCosts in this substance set the costs for the
     *                          upgrade are returned, it will be overwritten
     *                          in any case, even if now upgrade was planned
     *  @return @c true if there is an upgrade planned, if not @c false        */
    virtual bool getUpgradeCosts( TSubstanceSet* UpgradeCosts ) const;
    /** With the method getRepairCost you can get the cost for a repair of all
     *  damages on hull, armor and other equipment. The cost for new fighters,
     *  SP weapons and ammuntion will not be included. The cost vlaue will be
     *  returned in the parameter RepairCost.
     *  @param RepairCost return variable for the repair cost; it will deleted
     *                    in any case                                          */
    virtual void getRepairCost( TSubstanceSet* RepairCost ) const;
    /** With the method RepairSubfleet you can order the subfleet to repair
     *  damages to hull, armor and other equipment. But the stocks of fighters,
     *  SP weapons and ammuntion will not be filled up.                        */
    virtual void RepairSubfleet();
    /** With the method getActualHullHP you can get the amount if hit points
     *  the subfleet still has. You don't get any information how they are
     *  distributed over different ships.
     *  @return the amount of hit points the subfleet still has                */
    virtual int4 getActualHullHP() const;
    /** With the method getFuelConsumption you can get the amount of fuel a
     *  subfleet needs for a given distance with a give speed. The method
     *  expacts speed and distance as parameters. The distance can be omitted;
     *  then the default value of 1 is chosen.
     *  @param Speed the speed of the subfleet wants to travel with
     *  @param Distance the distance the subfleet wants to travel
     *  @return the fuel needed for that distance at that speed                */
    virtual int4 getFTLFuelConsumption( double Speed, double Distance=1 ) const;
    /** With the method getMaxSpeed you can get the maximum speed the sublfeet
     *  is able to travel with.
     *  @return the maximum speed of the subfleet                              */
    virtual double getFTLMaxSpeed() const;
    /** With the method getMovementDistance you can get the distance the
     *  subfleet can travel within one turn with the given speed.
     *  @param Speed the speed the subfleet should travel with
     *  @return the distance the subfleet can move with the given speed within
     *          one turn                                                       */
    virtual double getFTLMovementDistance( double Speed ) const;
    /** With the method getBreakDownProbability you can get the probability of
     *  an engine failure for traveling with a certain speed. FIXME, do we
     *  differ between STL and FTL travel?
     *  @param Speed the speed of the subfleet
     *  @return the probability for an engine failure of subfleet at the given
     *           speed                                                    .    */
    virtual double getFTLBreakDownProbability( double Speed ) const;
    /** With the method getLongScannerRange you can get the maximu scanning
     *  range of the long range scanner. That means the range the scanners can
     *  scan on the star map, not on the battlefield. The range is return in
     *  lightyears.
     *  @return the maximum scn range of the long range scanners in LYs        */
    virtual double getLongScannerRange( TScanner::tScannerType ScannerType ) const;
    /** With the method IsColonizer you can get the information whether the
     *  ship design of the subfleet contains at least on colonization module.
     *  What you do with this information is up to the code, which handles the
     *  actual colonization. For example, it could get this information and if
     *  positive it decreases the number of ships by one and colonizes the
     *  planet.
     *  @return @c true if colonization module in the design, if not @c false  */
    virtual bool IsColonizer() const;
    /** FIXME */
    virtual void setFuel( int4 Fuel );
    /** With the method getFuel you can get the amount of fuel the subfleet
     *  has still left.
     *  @return the amount of fuel the subfleet has still left                 */
    virtual int4 getFuel() const;
    /** The method Load loads a TSubFleet object from the data packages in
     *  the list. Additionally it informs the parent fleet about its new
     *  subfleet. For more information look in the documentation of the
     *  ancestors of TShipDesign from where this method is inherited.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TSubFleet by adding the data packages to the
     *  list. For more information look in the documentation of the ancestors
     *  of TShipDesign, because the method Save is inherited from there.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** This is the assignment operator for TSubFleetBasic. It copies all
     *  values of the subfleet except the fleet. The caller is responsible to
     *  inform the fleet about its new subfleet. This fleet will then inform
     *  the subfleet about its new parent. FIXME, at the moment the fields of
     *  TActioObject are NOT copied.                                           */
    virtual TSubFleetBasic& operator=( const TSubFleetBasic& SubFleet );
  private:
    int2 fFuel;
};





#endif        // __SUB_FLEET_INCLUDED
