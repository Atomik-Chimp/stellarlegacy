// $Id: subfleet.h,v 1.10 2002/04/02 22:33:45 prolator Exp $
//
// subfleet Header File
// Written by: Marco Krohn
//             Ralf Laue
//
// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
//                        Ralf Laue <ralf.laue@gmx.de>
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

#ifndef __SUBFLEET_INCLUDED
#define __SUBFLEET_INCLUDED

#include "gamelogic/action.h"
#include "common/defs.h"
#include "gamelogic/item.h"
#include "common/osval.h"

class TFleet;
class TShipDesign;

/****************************** class TSubFleet ********************************/


/** @class TSubFleet
 *  @brief A subfleet consists of a number of ships of the same type.
 *  @author Marco Krohn <marco.krohn@gmx.de>
 *  @author Ralf Laue <ralf.laue@gmx.de>
 *  @version $Id: subfleet.h,v 1.10 2002/04/02 22:33:45 prolator Exp $
 *  @see TFleet, TShipDesign, TSubFleetBasic
 *
 *  In contrary to a fleet the subfleet consists only of ships of the same type.
 *  TSubFleet is a pure virtual class, the implementation is given in the rule
 *  system related classes TSubFleetBasic, TSubFleetStars, TSubFleetSL.
 *  Basically TSubFleet has a link to the ship design, damage distribution
 *  information and an integer with the number of ships in this subfleet.
 *  Note that the method descriptions sometimes uses the term "fleet" instead
 *  of subfleet.                                                               */
class TSubFleet : public TActionObject
{
  public:
    /** This constructor creates and initializes a new subfleet. The ship
     *  design the subfleet is of, is given in the parameter. The number of
     *  ships the subfleet should have initailly, is given in the second
     *  parameter.
     *  @param ShipDesign the ship design the subfleet is of
     *  @param NumberOfShips the number of ships the subfleet has initially    */
    TSubFleet( TShipDesign* ShipDesign, int2 NumberOfShips );
    /** This constructor also creates a new subfleet. It is initialized with
     *  the values of the subfleet given in the parameter. This is the copy
     *  constructor. All values ecxept the fleet are copied. The caller is
     *  responsible to inform the fleet about its new subfleet. This fleet
     *  will then inform the subfleet about its new parent. FIXME, at the
     *  moment the fields of TActioObject are NOT copied.
     *  @param OldSubFleet the subfleet the values are copied from             */
    TSubFleet( TSubFleet& OldSubFleet );
    /**
    * The destructor is doing nothing special at the moment.
    */
    virtual ~TSubFleet();

    /** This method is inherited from TType and reimplemented here. I returns
     *  TType::SUBFLEET.
     *  @return the type of the class, here: TType::SUBFLEET
     *  @see TType                                                             */
    virtual int2 getType() const;
    /** This method is inherited from TType and reimplemented here. I returns
     *  "TSubFleet".
     *  @return the name of the class, here "TSubFleet"
     *  @see TType                                                             */
    virtual const string& getTypeName() const;
    /** With the method getFleet you can get the "parent" fleet, the subfleet
     *  is belonging to.
     *  @return the TFleet object this subfleet belongs to                     */
    virtual const TFleet* getFleet() const;
    /** With the method getShipDesign you can get the ship design the ships in
     *  the subfleet are from.
     *  @return link to the ship design the ships in the subfleet are from     */
    virtual const TShipDesign* getShipDesign() const;
    /** With the method AddShips you can add ships to the subfleet. The method
     *  doesn't complain about, if the number of new ships is 0.
     *  @param NumberOfShips the number of ships to be added to the subfleet   */
    virtual void AddShips( int4 NumberOfShips );
    /** With the method SubstractShips you can substract ships from the
     *  subfleet. The method doesn't complain about, if the number of ships to
     *  be substracted is 0. If the number of ships would be become 0 or
     *  negative, the method gives a fatal error.
     *  @param NumberOfShips number to be substracted from the subfleet        */
    virtual void SubstractShips( int4 NumberOfShips );
    /**
     *  @return The total number of ships in the subfleet.                     */
    virtual int4 getNumberOfShips() const;
    /** With the method setAutoUpgrade you can give the subfleet the ship
     *  design it should become upgraded to at the next opportunity. This
     *  opportunity is signed the subfleet with the method CommitAutoUpgrade.
     *  If there is already one auto upgrade planned, it will be overwritten
     *  with the new one.
     *  @param UpgradeDesign the design the subfleet shall be upgraded to      */ 
    virtual void setAutoUpgrade( TShipDesign* UpgradeDesign );
    /** With the method getUpgradeDesign you can get the pointer to the ship
     *  design, the subfleet shall be upgraded to. If there is no such design,
     *  because no auto upgrade si planned, the method will return the
     *  NULL-pointer.
     *  @return pointer to upgrade design or NULL                              */
    virtual TShipDesign* getUpgradeDesign() const;
    /** With the method CancelAutoUpgrade you can cancel an ordered auto
     *  upgrade. Also the link to the upgrade design will be deleted, so that
     *  if you want to set up a new auto upgrade, you have to give the wished
     *  design again.                                                          */
    virtual void CancelAutoUpgrade();
    /** With the method getUpgradeCosts you can get the costs the planned
     *  upgrade will cost. The costs are returned in the paremeter
     *  UpgradeCosts. Furthermore the method returns, whether there is an
     *  upgrade planned.
     *  @parameter UpgradeCosts in this substance set the costs for the
     *                          upgrade are returned, it will be overwritten
     *                          in any case, even if now upgrade was planned
     *  @return @c true if there is an upgrade planned, if not @c false        */
    virtual bool getUpgradeCosts( TSubstanceSet* UpgradeCosts ) const = 0;
    /** With the method CommitAutoUpgrade you can commit an ordered auto
     *  upgrade. Also the link to the upgrade design will be deleted (it is no
     *  longer needed) so that if you want to set up a new auto upgrade, you
     *  have to give the wished design again. The method will return a bool
     *  value, whether an upgrade was planned and commited (if one was planned
     *  it is commited after this method). Because this method doesn't care,
     *  whether you are able to pay the costs or not, make sure only to call
     *  it, when you already have payed the costs.
     *  @return @c true if a upgrade was planned an committed, @c false if not */
    virtual bool CommitAutoUpgrade();
    /** With the method setAutoRetire you can set a flag, which determines
     *  whether the subfleet is to be retired at the next opportunity. The
     *  flag can be read out with the method IsAutoRetire. The classes which
     *  are responsible for the actions of the subfleet has to check at every
     *  opportunity (i.e. planet) whether the subfleet is to be retired and if
     *  yes, destruct it with the destructor.                                  */
    virtual void setAutoRetire();
    /** With the method CancelAutoRetire you can delete the flag, which
     *  determines whether the subfleet is to be retired at the next
     *  opportunity. That means, the auto reiterment is canceld.
     *  @see setAutoRetire, CancelRetire                                       */
    virtual void CancelAutoRetire();
    /** With the method IsAutoRetire you can get the value of the flag that
     *  determines whether the subfleet shoulf be retired at the next
     *  opportunity.
     *  @return @c true is the subfleet should be retired, @c false if not
     *  @see setAutoRetire, CancelRetire                                       */
    virtual bool IsAutoRetire() const;
    /** With the method getRepairCost you can get the cost for a repair of all
     *  damages on hull, armor and other equipment. The cost for new fighters,
     *  SP weapons and ammuntion will not be included. The cost value will be
     *  returned in the parameter RepairCost.
     *  @param RepairCost return variable for the repair cost; it will deleted
     *                    in any case                                          */
    virtual void getRepairCost( TSubstanceSet* RepairCost ) const = 0;
    /** With the method RepairSubfleet you can order the subfleet to repair
     *  damages to hull, armor and other equipment. But the stocks of fighters,
     *  SP weapons and ammuntion will not be filled up.                        */
    virtual void RepairSubfleet() = 0;
    /** With the method setExperience you can set the amount of experience the
     *  subfleet or rather its crew has. With growing experience the battle
     *  performance of the crew increaes.
     *  @param Experience the new amount of experience of the subfleet         */
    virtual void setExperience( int4 Experience );
    /** With the method getExperience you can get the amount of experience the
     *  subfleet or rather its crew has.
     *  @return the amount of experience the crew of the subfleet has          */
    virtual int4 getExperience() const;
    /** With this method you can get the maximum amount of hull hit points the
     *  sub fleet has (in undamaged condition).
     *  @return the maximum amount of hull hit points of the subfleet          */
    virtual int4 getMaxHullHP() const;
    /** With this method you can get the maximum amount of armor hit points
     *  the sub fleet has (in undamaged condition). The amount is returned
     *  without taking in calculation different armor types.
     *  @return the maximum amount of armor hit points of the subfleet         */
    virtual int4 getMaxArmorHP() const;
    /** With this method you can get the maximum amount of shield hit points
     *  the sub fleet has (in undamaged condition). The amount is returned
     *  without taking in calculation different shield types.
     *  @return the maximum amount of shield hit points of the subfleet        */
    virtual int4 getMaxShieldHP() const;
    /** With the method getActualHullHP you can get the amount if hit points
     *  the subfleet still has. You don't get any information how they are
     *  distributed over different ships.
     *  @return the amount of hit points the subfleet still has                */
    virtual int4 getActualHullHP() const = 0;
    /** With the method getFuelConsumption you can get the amount of fuel a
     *  subfleet needs for a given distance with a give speed. The method
     *  expacts speed and distance as parameters. The distance can be omitted;
     *  then the default value of 1 is chosen.
     *  @param Speed the speed of the subfleet wants to travel with
     *  @param Distance the distance the subfleet wants to travel
     *  @return the fuel needed for that distance at that speed                */
    virtual int4 getFTLFuelConsumption( double Speed, double Distance=1 ) const = 0;
    /** With the method getMaxSpeed you can get the maximum speed the sublfeet
     *  is able to travel with.
     *  @return the maximum speed of the subfleet                              */
    virtual double getFTLMaxSpeed() const = 0;
    /** With the method getMovementDistance you can get the distance the
     *  subfleet can travel within one turen with the given speed.
     *  @param Speed the speed the subfleet should travel with
     *  @return the distance the subfleet can move with the given speed within
     *          one turn                                                       */
    virtual double getFTLMovementDistance( double dSpeed ) const = 0;
    /** With the method getBreakDownProbability you can get the probability of
     *  an engine failure for traveling with a certain speed. FIXME, do we
     *  differ between STL and FTL travel?
     *  @param Speed the speed of the subfleet
     *  @return the probability for an engine failure of subfleet at the given
     *           speed                                                    .    */
    virtual double getFTLBreakDownProbability( double Speed ) const = 0;
    /** With the method getLongScannerRange you can get the maximu scanning
     *  range of the long range scanner. That means the range the scanners can
     *  scan on the star map, not on the battlefield.
     *  @return the maximum scn range of the long range scanners               */
    virtual double getLongScannerRange( TScanner::tScannerType ScannerType ) const = 0;
    /** With the method setFuel you can get the amount of fuel the subfleet
     *  has still left.
     *  @return the amount of fuel the subfleet has still left                 */
    virtual void setFuel( int4 Fuel ) = 0;
    /** With the method getFuel you can get the amount of fuel the subfleet
     *  has still left.
     *  @return the amount of fuel the subfleet has still left                 */
    virtual int4 getFuel() const = 0;
    /** With the method getCargoSpace you can get the amount of cargo space of
     *  the subfleet (as integer value).
     *  @return the amount of cargo space the subfleet has                     */
    virtual int4 getCargoSpace() const;
    /** With the method IsColonizer you can get the information whether the
     *  ship design of the subfleet contains at least on colonization module.
     *  What you do with this information is up to the code, which handles the
     *  actual colonization. For example, it could get this information and if
     *  positive it decreases the number of ships by one and colonizes the
     *  planet.
     *  @return @c true if colonization module in the design, if not @c false  */
    virtual bool IsColonizer() const = 0;
    /** With the method getMiningRate you can get the mineral mining rate of
     *  the subfleet. It is simply the value of the ship design multiplied
     *  with the number of ships in the subfleet.
     *  @return the mineral mining rate of the subfleet                        */
    virtual int2 getMiningRate() const;
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
    /** This is the assignment operator for TSubFleet. It copies all values of
     *  the subfleet except the fleet. The caller is responsible to inform the
     *  fleet about its new subfleet. This fleet will then inform the subfleet
     *  about its new parent. FIXME, at the moment the fields of TActioObject
     *  are NOT copied.                                                        */
    virtual TSubFleet& operator=( const TSubFleet& SubFleet );

  protected:
    friend class TFleet;
    /** The method setFleet sets the fleet this subfleet belongs to. It
     *  doesn't care about whether the new or old parent fleet are informed
     *  about it. This method should only be called by TFleet, if the subfleet
     *  gets a new parent fleet.
     *  @param NewFleet the new fleet the subfleet should be added to          */
    virtual void setFleet( TFleet* NewFleet );
    /** the link to the "parent" fleet                                         */
    TLink<TFleet> fFleet;
    /** the link to the ship design the ships in the subfleets are of          */
    TLink<TShipDesign> fShipDesign;
    /** the link to the ship design the subfleet shall be get upgraded to      */
    TLink<TShipDesign> fUpgradeDesign;
    /** the number of ships in the subfleet                                    */
    int4 fNumberOfShips;
    /** the amount of experience the crew of the subfleet has                  */
    int4 fExperience;
    /** the flag which determines whether the subfleet is to be auto retired   */
    bool fAutoRetire;
};


#endif        // __SUB_FLEET_INCLUDED
