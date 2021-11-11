// $Id: shipdesign.h,v 1.20 2002/04/25 22:21:13 prolator Exp $
//
// Ship Design Header File
// Written by: Ralf Laue <ralf.laue@gmx.de>
//
// Copyright (C) 2001 Ralf Laue <ralf.laue@gmx.de>
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

#ifndef __SHIPDESIGN_INCLUDED
#define __SHIPDESIGN_INCLUDED

#include "common/defs.h"
#include "common/link.h"
#include "common/plist.h"
#include "gamelogic/item.h"
#include "gamelogic/substance.h"
#include <string>
#include <map>
class TItemPack;



/***************************** class TShipDesign *******************************/



/** @class TShipDesign
 *  @brief TShipDesign saves the properties of a ship design
 *  @author Ralf Laue
 *  @version $Id: shipdesign.h,v 1.20 2002/04/25 22:21:13 prolator Exp $
 *  @see TItem
 *
 *  The class TShipDesign handles the attributes of a ship design like the
 *  cost, the equipment onboard or the name. Because it is derived from
 *  @ref TLinkable it has its own unique ID. The basic values like mass, free
 *  volume and surface, hit points can be set simply with the "set" methods.
 *  The items (they are sub classes of TItem) are added to the ship design with
 *  @ref addItem. You can also specify the quantity of items of one type. The method
 *  @ref removeItem works similar, but it removes the items instead. If you
 *  want to get all items which are on board of the ship design you can get a
 *  list of all items by using the method @ref getItemList. All "get"
 *  methods (beside for name and hit points) exist in two versions: one only
 *  returns the basic values of the fuselage; the other includes the values of
 *  the items. For example you can get the hull mass with @ref getHullMass and the
 *  total mass of the ship design with @ref getTotalMass.
 *
 *  If at least one subfleet exists you can't change the ship design with the
 *  set???? methods. You can only change the ship design, if no ships/subfleets
 *  exist. Whether you the ship design is changeable (if no ships exits) you can
 *  read out with the method isChangeable as bool value. The number of existing
 *  subfleets can be read out with the method getUsageNumber. Because the ship
 *  design get get the number of subfleets through its TLinkable heritage, you
 *  don't have to worry about setting this values.
 *
 *  With the method AbleToLand you can set a flag which determines whether an
 *  actual ship of the design is able to fly in an atmosphere and to land on a
 *  planet. The flag can be read with the method isAtmospheric. If the design
 *  is able to land on a planet the cost for the hull is inreased by a factor.
 *  This factor can be set and read with setAtmosphericFactor and 
 *  getAtmosphericFactor. It is given as double number and the cost is
 *  increased by this factor (i.e. if the ship shall cost 125% of the normal
 *  prize, the factor has to be 0.25). If the flag is true and you set a new
 *  hull cost, the cost is automatically inreased by n%. For example the
 *  factor 0.25 and you set the cost to 100. Then the cost is automatically
 *  set to 125. If you then change the factor to 0.35, the cost is set to 135.
 *  Of course, if isChangeable is  @c true, then neither the factor nor the
 *  flag for landing can be changed. FIXME, perhaps it is wished to make the
 *  changes mor eflexible (i.e. the rule set can decide whether cost or volume
 *  are concerned. Then it has to be changed here.                             */
class TShipDesign : public TLinkable
{
  public:
    /** An iterator for the TPList which contains the equipment                */
    typedef TPList<TItemPack>::iterator tEquipmentIterator;
    /** A const iterator for the TPList which contains the equipment           */
    typedef TPList<TItemPack>::const_iterator tEquipmentConstIterator;
    /** This constructor creates a new ship prototype with all the attributes
     *  reseted. That means all attributes like name, cost and so on have to
     *  be set afterwards. This will be used when the parser reads a new
     *  ship type out of the script files or a new ship type is created (not
     *  by the player) because of a new tech level.                            */
    TShipDesign();
    /** This constructor creates also a new ship prototype, but the attributes
     *  are copied from the TShipDesign given in OldDesign. This will be used
     *  when the player generates a new prototype derived from an earlier
     *  prototype
     *  @param OldDesign the design which shall be copied                      */
    TShipDesign( const TShipDesign& OldDesign );
    /** Destructs the object. It has to be called for destruction of the
     *  object, because it releases the memory used for the equipment list.    */
    virtual ~TShipDesign();
    /** This method is inherited from TType and reimplemented here. I returns
     *  TType::SHIPDESIGN.
     *  @return the type of the class, here: TType::SHIPDESIGN
     *  @see TType                                                             */
    virtual int2 getType() const;
    /** This method is inherited from TType and reimplemented here. I returns
     *  "TShipDesign".
     *  @return the name of the class, here "TShipDesign"
     *  @see TType                                                             */
    virtual const string& getTypeName() const;
    /** With the method setDesignName you can set the name of the ship design
     *  if the flag @c fChangeable is @c true. If the flag @c fChangeable is
     *  @c false this method has no effect.
     *  @param Name The new name for the ship design.                          */
    virtual void setDesignName( const string& Name );
    /** With the method getShipDesign you can get the name of the ship design.
     *  @return the name of the ship design                                    */
    virtual const string& getDesignName() const;
    /** With the method getUsageNumber you can get the number of existing
     *  subfleets of this ship design. If there is at least one subfleet, you
     *  can't change the ship design; the set???? methods will have no effect.
     *  @return the number of existing subfleets of this ship design.
     *  @see isChangeable                                                      */
    int4 getUsageNumber() const;
    /** With the method isChangeable you can read out whether the design can
     *  be changed or not.
     *  @return Returns @c true is the design can be changed and @c false if
     *          the design can't be changed. In the latter case no methods
     *          of TShipDesign will alter the ship design.
     *  @see getUsageNumber                                                    */
    virtual bool isChangeable() const;
    /** With the method AbleToLand you can set a flag which determines whether
     *  ships of this design are able to fly through an atmosphere and to land
     *  on a planet. If the flag is changed, the hull cost is changed by an
     *  factor which can be set with the method setAtmosphericFactor and can
     *  be read with the method getAtmosphericFactorfactor. If changed from
     *  @c true to @c false the hull cost is decreased by n% and if changed
     *  from @c false to @c true, it is increased by n%.
     *  @param CanLand value that determines whether ships of this desgin can
     *                 fly through an atmosphere and land on planets           */
    virtual void AbleToLand( bool CanLand );
    /** With the method isAtmospheric you can read out the flag which
     *  determines whether ships of this design can fly through an atmosphere
     *  and land on planets.
     *  @return @c true if it can land on planets, @c false if not             */
    virtual bool isAtmospheric() const;
    /** With the method setAtmosphericFactor you can set the factor the hull
     *  cost is increased, if ships of this design can fly through atmospheres
     *  and land on planets. The cost is increased by the factor, that means
     *  if oyu want to cost the design 125% of the normal cost, the factor has
     *  to be 0.25. If the design is already able to land on planets, the cost
     *  is adjusted to the new factor.
     *  @param Factor the new factor the cost shall be increased by            */
    virtual void setAtmosphericFactor( double Factor );
    /** With the method getAtmosphericFactor you can read out the factor the
     *  hull cost is increased, if ships of this design can fly through
     *  atmospheres and land on planets.
     *  @return the factor the cost shall be increased by                      */
    virtual double getAtmosphericFactor() const;
    /** With the method setHullMass you can set the mass of the empty hull,
     *  if the flag @c fChangeable is @c true. If the flag @c fChangeable is
     *  @c false this method has no effect. 
     *  @paramter Mass the new mass of the empty hull.                         */
    virtual void setHullMass( const int4 Mass );
    /** With the method getHullMass you can get the mass of the empty hull.
     *  The mass of already installed equipment is not accounted for.
     *  @return the mass of the empty hull.                                    */
    virtual int4 getHullMass() const;
    /** With the method getTotalMass you can get the summarized mass of the
     *  hull and all the components. This method will be used, if you want to 
     *  calcilate the acceleration accroding to engine power and ship mass.
     *  @return the mass of the ship.                                          */
    virtual int4 getTotalMass() const;
    /** With the method setVolume you can set the volume which is free for
     *  equipment in an empty hull, if the flag @c fChangeable is @c true. If
     *  the flag @c fChangeable is @c false this method has no effect. 
     *  @param Volume the new free volume in the empty hull                    */
    virtual void setHullVolume( const int2 Volume );
    /** With the method getHullVolume you can get the volume which is free
     *  for equipment in an empty hull. Volume of already installed eqipment
     *  is not accounted for.
     *  @return the free volume in the empty hull                              */
    virtual int2 getHullVolume() const;
    /** With the method getFreeVolume you can get the volume which is still
     *  free for additional equipment in the ship design. The method will be
     *  used to check whether there still is space free for more equipment.
     *  @return the free volume in the ship design                             */
    virtual int2 getFreeVolume() const;
    /** With the method setSurface you can set the surface area which is free
     *  for equipment on the outside of an empty hull, if the flag
     *  @c fChangeable is @c true. If the flag @c fChangeable is @c false this
     *  method has no effect. 
     *  @param Surface the new free surface on the empty hull                  */
    virtual void setHullSurface( const int2 Surface );
    /** With the method getHullSurface you can get the surface area which is
     *  free for equipment on the outside of an empty hull. The Surface area
     *  which is used by already installed equipment is not acounted for.
     *  @return the free surface on the empty hull                             */
    int2 getHullSurface() const;
    /** With the method getFreeSurface you can get the surface area which is
     *  still free for additional equipment on the outside of the ship design.
     *  The method will be used to check whether there still is surface area
     *  free for more equipment.
     *  @return the free surface on the ship design                            */
    virtual int2 getFreeSurface() const;
    /** With the method setHullCost you can set the cost for the empty hull of
     *  the ship design, if the flag @c fChangeable is @c true. If the flag
     *  @c fChangeable is @c false this method has no effect. 
     *  @param HullCost the new cost for the hull                              */
    virtual void setHullCost( const TSubstanceSet& HullCost );
    /** With the method getHullCost you can get the cost for the empty hull of
     *  the ship design. The costs for components are not included. The
     *  interface of this method is made this way to make it similar to
     *  @ref getDesignCost.
     *  @param ReturnCost In this variable the hull cost is returned, any
     *                    old value is deleted.                                */
    virtual void getHullCost( TSubstanceSet* ReturnCost ) const;
    /** With the method getDesignCost you can get the cost for the complete
     *  ship design. The costs for components are included. This method will
     *  be used, when you want to know how much the whole design will cost.
     *  @param ReturnCost In this variable the hull cost is returned, any
     *                    old value is deleted.                                */
    virtual void getDesignCost( TSubstanceSet* ReturnCost ) const;
    /** With the method setMaxHullHP you can set the maximum amount of hit
     *  points the hull can take, before it is destroyed, if the flag
     *  @c fChangeable is @c true. If the flag @c fChangeable is @c false this
     *  method has no effect.
     *  @param HitPoints the amount of hit points for the hull                 */
    virtual void setMaxHullHP( const int2 HitPoints );
    /** With the method getMaxHullHP you can get the aximum amount of hit
     *  points the hull can take before being destroyed.
     *  @return the maximu hit points of the hull                              */
    virtual int2 getMaxHullHP() const;
    /** The method AddItem adds a number of items to the ship design and
     *  returns the number of added items, if the flag @c fChangeable is
     *  @c true. If the ship design has not enough volume or surface to add
     *  all requested items, the method will add as many items as fit on the
     *  ship design and return this number. This can also mean that 0 is
     *  returned if there is not enough volume or surface free to add one item.
     *  If the items coludn't be added, because this type of items is not
     *  allowed -1 is returned. If the flag @c fChangeable is @c false the
     *  method doesn't alter the design and returns 0.
     *  FIXME: Until now, there are no constraints which equipment can be put
     *  on which ship/hull. If in future such constraints are planned, they
     *  could be implemented here.
     *  @param Item the Item which should be mounted in the slot
     *  @param iNewAmount the number of items to be added; the parameter has
     *                    a default of 1, so if it is omitted, only one item
     *                    is added
     *  @return the number of items that were successfully added or -1 if the
     *          item was of the wrong type                                     */
    virtual int2 AddItem( TItem* Item, const int2 AddAmount = 1 );
    /** The method RemoveItem tries to remove RemoveAmount items from the ship
     *  design, if the flag @c fChangeable is @c true. If there are less item
     *  in the slot than should be removed, it removes all items of this type
     *  from the ship design. The number of removed items is returned by the
     *  method. If no item of this type was on the ship design the method does
     *  nothing and returns 0. If the flag @c fChangeable is @c false the
     *  method doesn't alter the design and returns 0.<br>
     *  @param RemoveAmount the number of items to be removed
     *  @return the number of successfully removed items                       */
    virtual int2 RemoveItem( TItem *Item, const int2 RemoveAmount);
    /** The method getItemList returns a list with the types and amounts of
     *  items. This list is of type @ref TItemList and contains structs of
     *  type @ref tItemPack. The list is returned in the paramter ReturnList.
     *  Any existing content in the ReturnList is deleted before returning it.
     *  The second paramter ItemType determines which items are returned. If
     *  the second parameter is omitted, a list with all items is returned.
     *  If not only items with the chosen type are returned. The type has to
     *  be given as values TItem::STLENGINE and similar (see @ref TItem). You
     *  can also get two (or more) different item types if you use two (or
     *  more) constants combine with OR.
     *  @b IMPORTANT: The caller is responsible to delete the TItemPack
     *  objects the list has stored pointers to. This can for example be done
     *  with the method deleteAll from TPList.
     *  @param ReturnList In this list the items are returend and any old
     *                    values are deleted.
     *  @param ItemType the type of items in the list; it has the default
     *                  value of 0xFFFFFFFF, si if this parameter is ommited,
     *                  all items will be returend in the list.                */
    virtual void getItemList( TPList<TItemPack>* ReturnList, const int2 ItemType = -1) const;
    /** The method "load" loads a TShipDesign object from the data packages in
     *  the list. For more information look in the documentation of the
     *  ancestors of TShipDesign from where this method is inherited.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method "save" saves a TShipDesign by adding the data packages to the
     *  list. For more information look in the documentation of the ancestors
     *  of TShipDesign, because the method Save is inherited from there.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** This is the assignment operator for TShipDesign                        */
    virtual TShipDesign& operator=( const TShipDesign& Design );

  private:
    /** the name of the ship design                                            */
    string fDesignName;
    /** the flag which determines whether ship of this design can land on
     *  planets or fly through atmospheres                                     */
    bool fAtmospheric;
    /** the factor the hull cost are increased if it can on planets            */
    double fAtmosphericFactor;
    /** the mass of the empty hull                                             */
    int4 fHullMass;
    /** the free volume in an empty hull                                       */
    int4 fHullVolume;
    /** the free surface area on the outside of an empty hull                  */
    int4 fHullSurface;
    /** the cost (from type TSubstanceSet) of an empty hull                    */
    TSubstanceSet fHullCost;
    /** the amount of hit point the hull can take before being destroyed       */
    int4 fMaxHullHP;
    /** the container with the installed equipment                             */
    TPEList<TItemPack> fEquipment;
};





/****************************** class TItemPack ********************************/

/** @class TItemPack
 *  @brief TItemPack saves the type of an item and the amount.
 *  @author Ralf Laue
 *  @version $Id: shipdesign.h,v 1.20 2002/04/25 22:21:13 prolator Exp $
 *  @see TItem
 *
 *  The class TItemPack saves the type and the amount of an item on a ship
 *  design. The list of TShipDesign which saves all the equipment, consists of
 *  elements of TItemPack. TItemPack has only a link to the type of the item,
 *  an integer variable for the amount and the basic methods. The is mainly
 *  for communicating the item lists on a ship
 *  (method TShipDesign::getItemList)                                          */
class TItemPack
{
  public:
    /** This constructor creates a new TItemPack object with the link and the
     *  amount reseted. That means the link and the amount have to be set
     *  afterwards.                                                            */
    TItemPack();
    /** This constructor creates also a new TItemPack objet, but the values
     *  are copied from the TItemPack object given as parameter. This is the
     *  copy constructor.
     *  @param OldItemPack the item pack which shall be copied                 */
    TItemPack( const TItemPack& OldItemPack );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    ~TItemPack();
    /** With the method setItem you can set the link to the item type this
     *  item pack should contain an item of.
     *  @param Item a pointer to the new item this pack should be of           */
    void setItem( TItem* Item );
    /** With the method getItem you can get the link to the item type this
     *  item pack contains an item of.
     *  @return a pointer to the item this pack is of                          */
    TItem* getItem() const;
    /** With the method setItemAmount you can set the amount of items
     *  represented through this item pack.
     *  @param ItemAmount the new amount of items in this item pack            */
    void setItemAmount( int2 ItemAmount );
    /** With the method getItemAmount you can get the amount of items in this
     *  item pack.
     *  @return the amount of items in the itme pack                           */
    int2 getItemAmount() const;
    /** With the method operator== you can compare two TItemPack objects. This
     *  is of course the expected behaviour of "operator==".
     *  @param ItemPack the TItemPack object which to be compared with "*this"
     *  @return @c true if the TItemPack objects are equal, @c false if not    */
    bool operator==( const TItemPack& ItemPack ) const;
    /** This is the assignment operator for TItemPack.                         */
    TItemPack& operator=( const TItemPack& ItemPack );
    /** With the method Load you can load a TItemPack object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /** With the method Save you can save a TItemPack object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is to be saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool save( TDataPackageList* out, const string& sIdentifier, bool bUnique=true ) const;
  protected:
    /** the link to the item this item pack contains items of                  */
    TLink<TItem> fItemLink;
    /** the amount of items this item pack contains                            */
    int2 fItemAmount;
}; // class TItemPack



#endif        // __SHIPDESIGN_INCLUDED

