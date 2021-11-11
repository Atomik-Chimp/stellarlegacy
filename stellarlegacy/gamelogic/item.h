// $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
//
// Item Header File
// Written by: Marco Krohn <marco.krohn@gmx.de>
//             Ralf Laue <ralf.laue@gmx.de>,
//
// Copyright (C) 1999 - 2001, Marco Krohn <marco.krohn@gmx.de>
//                            Ralf Laue <ralf.laue@gmx.de>,
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

#ifndef __ITEM_INCLUDED
#define __ITEM_INCLUDED

#include "common/defs.h"
#include "common/link.h"
#include "common/plist.h"
#include "gamelogic/substance.h"
#include <vector>

/********************************* class TItem *********************************/


/** @class TItem
 *  @brief TItem represents an basic item you can put onto a ship.
 *  @author Ralf Laue
 *  @author Marco Krohn, <marco.krohn@gmx.de>
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TItem represents an basic item you can put on a ship design:
 *  name, type, mass, volume, surface area and cost (amount of substances needed to
 *  build this item). In general this class will be used to derive "real" items
 *  like scanners, armors etc. Since all these items are unique, this base
 *  class is derived form @ref TLinkable and provides thus an unique ID and can
 *  be linked as known.
 *
 *  <h2>General concept of TItem and derived classes</h2>
 *  There is one base list which belongs to TUniverse. All items which are
 *  accessible within the game are stored in this list. Also each race has
 *  its own list of pointers to items which are accessible for this race.
 *  When a race develops a new item a pointer to this item is added to
 *  the list of items for this race.
 *
 *  Note that TItem is a pure virtual class, so making instances of this class
 *  is not possible. TItem just provides the general interface for all items.
 *  Derived from this class are the interfaces for the different item types,
 *  for example a TSTLEngine. These classes also provide only the interface
 *  for this item type, the real implementation is done in different classes
 *  which have an additional suffix, e.g. TSTLEngineBasic, TSTLEngineStars
 *  etc.                                                                       */
class TItem : public TLinkable
{
  public:
    /** Each from TItem derived class (i.e. @ref TSTLEngine) will return one
     *  of these constants, if it shall indentify itself. This is especially
     *  important in connection with @ref TShipDesign                          */
    typedef enum
    {
      STL_ENGINE         = 0x00000001,
      FTL_ENGINE         = 0x00000002,
      FUELTANK           = 0x00000004,
      FUELSCOOP          = 0x00000008,
      CARGOBAY           = 0x00000010,
      COLONIZER          = 0x00000020,
      REPAIRBOT          = 0x00000040,
      ARMOR              = 0x00000080,
      SHIELD             = 0x00000100,
      KWEAPON            = 0x00000200,
      EWEAPON            = 0x00000400,
      TARGETINGCOMPUTER  = 0x00000800,
      SCANNER            = 0x00001000,
      JAMMER             = 0x00002000,
      MINELAYER          = 0x00004000,
      MININGBOT          = 0x00008000,
      FIGHTERLAUNCHER    = 0x00010000,
      SPWEAPONLAUNCHER   = 0x00020000
    } tItemType;
    /** This is the variable type for the weapon type. In future it could be
     *  necessary to change it into a class of its own or even two classes,
     *  one for kinetic weapons and one for energy weapons. It is defined here
     *  because this is the only place in the hierarchy above the classes were
     *  it is needed. As long as it is only an integer, the rule set/game
     *  start up class is responsible that there is no energy weapon with the
     *  same number a kinetic weapon already has.                              */
    typedef int2 tWeaponType;
    /** This constructor doesn't work, because TItem is a pure virtual class.
     *  It's only implemented to be used by the sub classes of TItems.         */
    TItem();
    /** This constructor doesn't work either and is implemented to provide
     *  a copy constructor for the sub classes.                                                
     *  @param OldItem the item which shall be copied.                         */
    TItem( const TItem& OldItem );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff. Doesn't work, because TItem is a pure
     *  virtual class and you wont be able to construct an object.             */
    virtual ~TItem();
    /** This method is inherited from TType and reimplemented here. I returns
     *  TType::ITEM.
     *  @return the type of the class, here: TType::ITEM
     *  @see TType                                                             */
    virtual int2 getType() const;
    /** This method is inherited from TType and reimplemented here. I returns
     *  "TItem".
     *  @return the name of the class, here "TItem"
     *  @see TType                                                             */
    virtual const string& getTypeName() const;
    /** The method Load loads a TItem object from the data packages in the
     *  list. All sub classes of TItem have to reimplement the Load method and
     *  they @e must call TItem::Load explicitly in their Load method to load
     *  the data correctly. For more information look in the documentation of
     *  the ancestors of TItem from where this method is inherited.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TItem by adding the data packages to the list.
     *  All sub classes of TItem have to reimplement the Save method and they
     *  @e must call TItem::Save explicitly in their Save method to save the
     *  data correctly. For more information look in the documentation of the
     *  ancestors of TItem, because the method Save is inherited from there.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getItemType you can get the type of the item, that
     *  means whether it is armor, engine or something else. This method
     *  has to be reimplemented in all the derived classes.
     *  @return nothing                                                        */
    virtual TItem::tItemType getItemType() const = 0;
    /** With the method setItemName you can give the item its name.
     *  @param Name the new name for the item                                  */
    virtual void setItemName( const string& Name );
    /** With the method getItemName you can read out the name of the item.
     *  @return the name of the item                                           */
    virtual const string& getItemName() const;
    /** With the method setTechLevel you can set the tech level the item has.
     *  @param TechLevel the new tech level for the item                       */
    virtual void setTechLevel( const int2 TechLevel );
    /** With the method getTechLevel you can get the tech level the item has.
     *  This will be important i.e. if you want to sort items after tech
     *  level.
     *  @return the tech level of the item                                     */
    virtual int2 getTechLevel() const;
    /** With the method setMass you can set the mass of the item.
     *  @paramter Mass the new mass of the item                                */
    virtual void setMass( const int2 Mass );
    /** With the method getMass you can get the mass of the item.
     *  @return the mass of the item                                           */
    virtual int2 getMass() const;
    /** With the method setVolume you can set the volume the item needs.
     *  @param Volume the new volume the item needs                            */
    virtual void setVolume( const int2 Volume );
    /** With the method getVolume you can get the volume the item needs.
     *  @return the volume the item needs                                      */
    virtual int2 getVolume() const;
    /** With the method setSurface you can set the surface area the item needs.
     *  @param Surface the new surface area the item needs                     */
    virtual void setSurface( const int2 Surface);
    /** With the method getSurface you can get the surface area the item needs.
     *  @return the surface area the item needs                                */
    virtual int2 getSurface() const;
    /** With the method setCost you can set the cost (from type TSubstanceSet)
     *  for the item.
     *  @param Cost the new cost for the item                                  */
    virtual void setCost( const TSubstanceSet& Cost );
    /** With the method getCost you can get the cost (from type TSubstanceSet)
     *  for the item. 
     *  @return the cost of the item                                           */
    virtual void getCost( TSubstanceSet* Cost ) const;
    /** This is the compare operator for TItem. It is only used in the sub
     *  classes of TItem to compare the fields of TItem, because TItem is
     *  abstract.
     *  @param Item the item which shall be compared with "*this"
     *  @return @c true if items are equal, @c false if not                    */
    virtual bool operator==( const TItem& Item ) const;
  protected:
    /** This is the assignment operator for TItem.                             */
    virtual TItem& operator=( const TItem& Item );
    /** the name of the item.                                                  */
    string fItemName;
    /** the tech level of the item                                             */
    int2 fTechLevel;
    /** the mass if the item                                                   */
    int2 fItemMass;
    /** the volume the item needs                                              */
    int2 fItemVolume;
    /** the surface area the item needs on the outside of the hull             */
    int2 fItemSurface;
    /** the cost (from type TSubstanceSet) for this item                       */
    TSubstanceSet fItemCost;
};



/****************************** class TSTLEngine *******************************/



/** @class TSTLEngine
 *  @brief TSTLEngine represents the STL engine for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TSTLEngine is derived from TItem and can therefore be put on a
 *  ship design. It represents a STL engine and has - additionally to the
 *  properties of an item - a value for its power for STL flight (STL means
 *  "slower than light"). What this value exactly means is up to the rule
 *  set/battle engine and of no direct concern of th the class TSTLEngine as
 *  it is only a class to keep the data.                                       */
class TSTLEngine : public TItem
{
  public:
    /** This constructor generates a new STL engine with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TSTLEngine();
    /** This constructor creates also a new STL engine, but the attributes are
     *  copied from the STL engine given in OldSTLEngine. Mostly implemented
     *  to provide a copy constructor.                                                
     *  @param OldSTLEngine the STL engine which shall be copied               */
    TSTLEngine( const TSTLEngine& OldSTLEngine );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TSTLEngine();
    /** The method Load loads a TSTLEngine object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TSTLEngine object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::STLENGINE for STL engine.
     *  @return TItem::STLENGINE                                               */
    virtual TItem::tItemType getItemType() const;
    /** The method setSTLPower sets the power for STL flight of the STL engine.
     *  @param STLPower the engine's new power for STL flight                  */
    virtual void setSTLPower( const int2 STLPower );
    /** With the method getSTLPower you can get the power for STL flight of
     *  the STL engine.
     *  @return the engine's power for STL flight                              */
    virtual int2 getSTLPower() const;
    /** With the method operator== you can compare two TSTLEngine objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param STLEngine the STL engine which shall be compared with "*this"
     *  @return @c true if then STL engines are equal, @c false if not         */
    virtual bool operator==( const TSTLEngine& STLEngine ) const;
    /** This is the assignment operator for TSTLEngine.                        */
    virtual TSTLEngine& operator=( const TSTLEngine& STLEngine );
  protected:
    /** the power for STL flight of the engine                                 */
    int2 fSTLEnginePower;
};



/****************************** class TFTLEngine *******************************/



/** @class TFTLEngine
 *  @brief TFTLEngine represents the FTL engine for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TFTLEngine is derived from TItem and can therefore be put on a
 *  ship design. It represents a FTL engine and has - additionally to the
 *  properties of an item - a value for its power for FTL flight (FTL means
 *  "faster than light"). What this value exactly means is up to the rule
 *  set/battle engine and of no direct concern of th the class TSTLEngine as
 *  it is only a class to hold the data.                                       */
class TFTLEngine : public TItem
{
  public:
    /** This constructor generates a new FTL engine with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TFTLEngine();
    /** This constructor creates also a new FTL engine, but the attributes are
     *  copied from the FTL engine given in OldFTLEngine. Mostly implemented
     *  to provide a copy constructor.                                                
     *  @param OldFTLEngine the FTL engine which shall be copied               */
    TFTLEngine( const TFTLEngine& OldFTLEngine );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TFTLEngine();
    /** The method Load loads a TFTLEngine object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TFTLEngine object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::FTLENGINE for FTL engine.
     *  @return TItem::FTLENGINE                                               */
    virtual TItem::tItemType getItemType() const;
    /** The method setFTLPower sets the power for FTL flight of the FTL engine.
     *  @param FTLPower the engine's new power for FTL flight                  */
    virtual void setFTLPower( const int2 FTLPower );
    /** With the method getFTLPower you can get the power for FTL flight of
     *  the FTL engine.
     *  @return the engine's power for FTL flight                              */
    virtual int2 getFTLPower() const;
    /** With the method operator== you can compare two TFTLEngine objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param FTLEngine the FTL engine which shall be compared with "*this"
     *  @return @c true if then FTL engines are equal, @c false if not         */
    virtual bool operator==( const TFTLEngine& FTLEngine ) const;
    /** This is the assignment operator for TFTLEngine.                        */
    virtual TFTLEngine& operator=( const TFTLEngine& FTLEngine );
  protected:
    /** the power for FTL flight of the engine                                 */
    int2 fFTLEnginePower;
};



/****************************** class TFuelTank ********************************/



/** @class TFuelTank
 *  @brief TFuelTank represents the fuel tank for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign  
 *
 *  The class TFuelTank is derived from TItem and can therefore be put on a
 *  ship design. TFuelTank represents the fuel tank of a ship. As all other
 *  items it has mass, volume and surface area. Additionally it can hold an
 *  amount of anti matter (that's the fuel). With increasing tech level the
 *  containment technology gets better and more antimatter can be stored per
 *  ton of fuel tank. How this is exactly handled and what one unit of fuel is
 *  worth, is up to rule set/battle engine and of no direct concern of
 *  TFuleTank                                                                  */
class TFuelTank : public TItem
{
  public:
    /** This constructor generates a new TFuelTank object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TFuelTank();
    /** This constructor creates also a new fuel tank, but the attributes are
     *  copied from the fuel tank given in OldFuelTank. Mostly implemented to
     *  provide a copy constructor.                                                
     *  @param OldFuelTank the fuel tank which shall be copied                 */
    TFuelTank( const TFuelTank& OldFuelTank );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TFuelTank();
    /** The method Load loads a TFuelTank object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TFuelTank object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::FUELTANK for fuel tank.
     *  @return TItem::FUELTANK                                                */
    virtual TItem::tItemType getItemType() const;
    /** The method setTankCapacity sets the size/storage capacity for the fuel
     *  tank.
     *  @param Capacity the fuel tank's storage capacity for anti matter       */
    virtual void setTankCapacity( const int2 Capacity );
    /** With the method getTankCapacity you can get the size/storage capacity
     *  for the fuel tank.
     *  @return the fuel tank's storage capacity for anti matter               */
    virtual int2 getTankCapacity() const;
    /** With the method operator== you can compare two TFuelTank objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param FuelTank the fuel tank object which shall be compared with
     *                  "*this"
     *  @return @c true if the fuel tank objects are equal, @c false if not    */
    virtual bool operator==( const TFuelTank& FuelTank ) const;
    /** This is the assignment operator for TFuelTank.                         */
    virtual TFuelTank& operator=( const TFuelTank& FuelTank );
  protected:
    /** the capacity of the fuel tank object                                   */
    int2 fTankCapacity;
};



/****************************** class TFuelScoop *******************************/



/** @class TFuelScoop
 *  @brief TFuelScoop represents the fuel scoop for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign  
 *
 *  The class TFuelScoop is derived from TItem and can therefore be put on a
 *  ship design. TFuelScoop represents the fuel scoop of a ship. As all other
 *  items it has mass, volume and surface area. Additionally it has value for
 *  its ability to collect fuel during flight. With increasing tech level this
 *  ability should increase. How this is exactly handled and how much fuel it
 *  can collect is up to rule set/battle engine and of no direct concern of
 *  TFuleScoop                                                                 */
class TFuelScoop : public TItem
{
  public:
    /** This constructor generates a new TFuelScoop object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TFuelScoop();
    /** This constructor creates also a new fuel scoop, but the attributes are
     *  copied from the fuel scoop given in OldFuelScoop. Mostly implemented to
     *  provide a copy constructor.                                                
     *  @param OldFuelScoop the fuel scoop which shall be copied               */
    TFuelScoop( const TFuelScoop& OldFuelScoop );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TFuelScoop();
    /** The method Load loads a TFuelScoop object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TFuelScoop object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::FUELSCOOP for fuel scoop.
     *  @return TItem::FUELSCOOP                                               */
    virtual TItem::tItemType getItemType() const;
    /** The method setScoopCapacity sets the capacity of the scoop to collect
     *  fuel.
     *  @param Capacity the fuel scoop's collecting capacity                   */
    virtual void setScoopCapacity( const int2 Capacity );
    /** With the method getScoopCapacity you can the capacity of the scoop to
     *  collect fuel.
     *  @return the fuel scoop's capacity collecting capacity                  */
    virtual int2 getScoopCapacity() const;
    /** With the method operator== you can compare two TFuelScoop objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param FuelScoop the fuel scoop object to be compared with "*this"
     *  @return @c true if the fuel scoop objects are equal, @c false if not   */
    virtual bool operator==( const TFuelScoop& FuelScoop ) const;
    /** This is the assignment operator for TFuelScoop.                        */
    virtual TFuelScoop& operator=( const TFuelScoop& FuelScoop );
  protected:
    /** the capacity of the fuel scoop object                                  */
    int2 fScoopCapacity;
};



/****************************** class TCargoBay ********************************/



/** @class TCargoBay
 *  @brief TCargoBay represents the cargo bay for a ship design.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TCargoBay is derived from TItem and can therefore be put on a
 *  ship design. TCargoBay represents the cargo bay of a ship design. As all
 *  other items it has mass, volume and surface area. One cargo bay item
 *  represents 1 m³ cargo space. All cargo can be transported in cargo bay
 *  items, as long it provides enough space. For example, colonists are also
 *  simple cargo, but take a certain amount of space (i.e. 5 m³) per colonist. */
class TCargoBay : public TItem
{
  public:
    /** This constructor generates a new TCargoBay object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TCargoBay();
    /** This constructor creates also a new TCargoBay object, but the
     *  attributes are copied from the cargo bay item given in OldCargoBay.
     *  Mostly implemented to provide a copy constructor.
     *  @param OldCargoBay the cargo bay item which shall be copied            */
    TCargoBay( const TCargoBay& OldCargoBay );
    /** The method Load loads a TCargoBay object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TCargoBay object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TCargoBay();
    /** The method getItemType returns the type of the item, in this case
     *  TItem::CARGOBAY for cargo bay.
     *  @return TItem::CARGOBAY                                                */
    virtual TItem::tItemType getItemType() const;
    /** With the method operator== you can compare two TCargoBay objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param CargoBay the cargo bay which shall be compared with "*this"
     *  @return @c true if the cargo bay objects are equal, @c false if not    */
    virtual bool operator==( const TCargoBay& CargoBay ) const;
    /** This is the assignment operator for TCargoBay.                         */
    virtual TCargoBay& operator=( const TCargoBay& CargoBay );
};



/****************************** class TColonizer *******************************/



/** @class TColonizer
 *  @brief TColonizer represents the colonization module, which can be put on
 *         a ship design.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TColonizer is derived from TItem and can therefore be put on a
 *  ship design. TColonizer represents a colonization maodule, which can be
 *  put on a ship. As all other items it has mass, volume and surface area. A
 *  colonization module has no extra fields. It just enables the ship to
 *  colonize a planet. How and whether more colonization modules do a better
 *  job than one alone, depends on the rule set and is of no concern for the
 *  TColonizer item class.                                                     */
class TColonizer : public TItem
{
  public:
    /** This constructor generates a new TColonizer object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TColonizer();
    /** This constructor creates also a new TColonizer object, but the
     *  attributes are copied from the TColonizer object given in OldColonizer.
     *  Mostly implemented to provide a copy constructor.
     *  @param OldColonizer the TColonizer object which shall be copied        */
    TColonizer( const TColonizer& OldColonizer );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TColonizer();
    /** The method Load loads a TColonizer object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TColonizer object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::COLONIZER for colonization module.
     *  @return TItem::COLONIZER                                               */
    virtual TItem::tItemType getItemType() const;
    /** With the method operator== you can compare two TColonizer objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param Colonizer the TColonizer object which shall be compared with
     *                   "*this"
     *  @return @c true if TColonizer objects are equal, @c false if not       */
    virtual bool operator==( const TColonizer& Colonizer ) const;
    /** This is the assignment operator for TColonizer.                        */
    virtual TColonizer& operator=( const TColonizer& Colonizer );
};



/****************************** class TRepairBot *******************************/



/** @class TRepairBot
 *  @brief TRepairBot represents a repair module for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TRepairBot is derived from TItem and can therefore be put on a
 *  ship design. TRepairBot represents the repair module of a ship. As all
 *  other items it has mass, volume and surface area. A repair module provides
 *  the possibility to the ship, to repair itself. The efficiency of the
 *  repair module is saved in the field fRepairSpeed. When and how a ship can
 *  repair itself is layed down by the rule set and of no direct concern to
 *  the TRepairBot item class.                                                 */
class TRepairBot : public TItem
{
  public:
    /** This constructor generates a new TRepairBot object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TRepairBot();
    /** This constructor creates also a new repair module, but the attributes
     *  are copied from the reapir module given in OldRepairBot. Mostly
     *  implemented to provide a copy constructor.                                                
     *  @param OldRepairBot the TRepairBot object which shall be copied        */
    TRepairBot( const TRepairBot& OldRepairBot );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TRepairBot();
    /** The method Load loads a TRepairBot object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TRepairBot object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::REPAIRBOT for repair module.
     *  @return TItem::REPAIRBOT                                               */
    virtual TItem::tItemType getItemType() const;
    /** The method setRepairSpeed sets the efficiency of the repair module.
     *  @param RepairSpeed the repair module's efficiency                      */
    virtual void setRepairSpeed( const int2 RepairSpeed );
    /** With the method getRepairSpeed you can get the efficiency of the
     *  repair module.
     *  @return the repair module's efficiency                                 */
    virtual int2 getRepairSpeed() const;
    /** With the method operator== you can compare two TRepairBot objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param RepairBot the TRepairBot object which shall be compared with
     *                  "*this"
     *  @return @c true if TRepairBot objects are equal, @c false if not       */
    virtual bool operator==( const TRepairBot& RepairBot ) const;
    /** This is the assignment operator for TRepairBot.                        */
    virtual TRepairBot& operator=( const TRepairBot& RepairBot );
  protected:
    /** the efficiency of the repair module                                    */
    int2 fRepairSpeed;
};



/*******************************************************************************/
/************************** A R M O R  &  S H I E L D S ************************/
/*******************************************************************************/



/******************************** TEfficiencyToken *****************************/



/** @class TEfficiencyToken
 *  @brief TEfficiencyToken contains the efficiency againts one weapon type.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TDefenseType
 *
 *  The class TEfficiencyToken contains the efficiency of a TDefenseType
 *  object against one  certain weapon type. Every defense type (that includes
 *  armor and shield type) has a list with elements of this class. It has only
 *  fields for one weapon type and the efficiency against it. Furthermore it
 *  provides operator=, operator== and Load and Save.                          */
class TEfficiencyToken
{
  public:
    /** This constructor generates a new TEfficiencyToken object with all
     *  properties resetted. That means the value for the efficiency and the
     *  weapon type is set to 0. You have to assign meaningful values with the
     *  appropriate set???? and get???? methods.                                 */
    TEfficiencyToken();
    /** This constructor also generates a new TEfficiencyToken object, but it
     *  copies from the parameter OldToken. This is the copy constructor.        */
    TEfficiencyToken( TEfficiencyToken& OldToken );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    ~TEfficiencyToken();
    /** With the method setWeaponType you can set the weapon type this object
     *  should contain the efficiency against.
     *  @param WeaponType the new weapon type this object should contain the
     *                    efficiency against                                     */
    void setWeaponType( TItem::tWeaponType WeaponType );
    /** With the method getWeaponType you can get the weapon type this object
     *  contains the efficiency against.
     *  @return the weapon type this object contains the efficiency against      */
    TItem::tWeaponType getWeaponType() const;
    /** With the method setEfficiency you can set the efficiency against the
     *  weapon type.
     *  @param Efficiency the new efficiency against the weapon type             */
    void setEfficiency( int2 Efficiency );
    /** With the method getEfficiency you can get the efficiency against the
     *  weapon type.
     *  @return the efficiency against the weapon type                           */
    int2 getEfficiency() const;
    /** With the method operator== you can compare two TEfficiencyToken objects.
     *  This is of course the expected behaviour of "operator==".
     *  @param Token the TEfficiencyToken object which to be compared with *this
     *  @return @c true if the TItemPack objects are equal, @c false if not      */
    bool operator==( const TEfficiencyToken& Token ) const;
    /** This is the assignment operator for TEfficiencyToken.                    */
    TEfficiencyToken& operator=( const TEfficiencyToken& Token );
    /** With the method Load you can load a TEfficiencyToken object from the
     *  data packages in the list. For more information look in the
     *  documentation of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this token is saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /** With the method Save you can save a TEfficiencyToken object from the
     *  data packages in the list. For more information look in the
     *  documentation of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this token is to be saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool save( TDataPackageList* out, const string& sIdentifier, bool bUnique=true ) const;
  protected:
    /** the weapon type                                                        */
    TItem::tWeaponType fWeaponType;
    /** the efficiency against the weapon type                                 */
    int2 fEfficiency;   
}; // class TEfficiencyToken



/********************************** TDefenseType *******************************/



/** @class TDefenseType
 *  @brief TDefenseType contains the efficiencies against different weapons.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TArmor
 *  @see TShield
 *
 *  The class TDefenseType provides an ancestor for the type for armor and
 *  shields or rather the information about their efficiencies against
 *  different weapon types. It is derived from TLinkable and has therefor an
 *  unique ID and can be linked (see also @ref TLinkable). An defense type
 *  contains a list/array with types of weapons and the related efficiencies
 *  of the armor (or shields) against them. The hit point value for armors or
 *  shields is provided by TArmor or TShield respectively. If a weapon type
 *  is not yet known a standard efficiency against all weapons is returned.
 *  This value can be changed with setStandardEfficiency and it can be read
 *  with getStandardEfficiency. The value of the standard efficiency is
 *  initialized with 100 if you use the constructor without parameters or to
 *  the value you want, if you use the constructor with StandardEfficiency as
 *  parameter. The 100 are chosen in expectation, that the values are
 *  percental values. If that's not correct, the implementation should perhaps
 *  be changed in fufture.<br>
 *  This class is pure virtual and ancestor to TArmorType an TShieldType. It
 *  is written to have the code which is necessary in both sub classes only
 *  one time.                                                                  */
class TDefenseType : public TLinkable
{
  public:
    /** This constructor generates a new TDefenseType object with all
     *  properties resetted. This means the value for the standard efficiency
     *  is 100 and the defense type doesn't know any weapons types. These you
     *  have to make known with setDefenseEfficiency.                          */
    TDefenseType();
    /** This constructor generates a also new TDefenseType object, but only
     *  with the defense efficiencies resetted. The standard efficiency is set
     *  to the value given as parameter. The efficiencies against weapon types
     *  have to be set with setDefenseEfficiency.                              */
    TDefenseType( const int2 StandardEfficiency );
    /** This constructor creates also a new defense type, but the attributes
     *  are copied from the defense type given in OldDefenseType. Mostly
     *  implemented to provide a copy constructor.                                                
     *  @param OldDefenseType the TDefenseType object which shall be copied    */
    TDefenseType( const TDefenseType& OldDefenseType );
    /** Destructs the object. It has to be called for destruction of the
     *  object, because it releases the memory used for the efficiencies list.   */
    virtual ~TDefenseType() = 0;
    /** The method Load loads a TDefenseType object from the data packages in
     *  the list. All sub classes of TDefenseType have to reimplement the Load
     *  method and they @e must call TDefenseType::Load explicitly in their
     *  Load method to load the data correctly.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TDefenseType by adding the data packages to
     *  the list. All sub classes of TDefenseType have to reimplement the Save
     *  method and they @e must call TDefenseType::Save explicitly in their
     *  Save method to save the data correctly.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method setStandardEfficiency you can set the standard 
     *  efficiency value against all unknown weapons.
     *  @param StandardEfficiency the new standard efficiency of the defense
     *                            type against unknown weapon types            */
    virtual void setStandardEfficiency( const int2 StandardEfficiency );
    /** With the method getStandardEfficiency you can get the standard 
     *  efficiency value against all unknown weapons.
     *  @return the standard efficiency against unknown weapons                */
    virtual int2 getStandardEfficiency() const;
    /** With the method setDefenseEfficiency you can set the efficiency value
     *  of the defense type against a certain weapon type.
     *  @param WeaponType the weapon type you want to set the efficieny against
     *  @param Efficiency the new efficiency the defense type shall have
     *                    against the weapon type                              */
    virtual void setDefenseEfficiency( const TItem::tWeaponType WeaponType, const int2 Efficiency );
    /** With the method getDefenseEfficiency you can get the efficiency value
     *  of the defense type against a certain weapon type.
     *  @param WeaponType the weapon type you want the efficieny against
     *  @return the efficiency against this weapon type                        */
    virtual int2 getDefenseEfficiency( const TItem::tWeaponType WeaponType ) const;
    /** With the method operator== you can compare two TDefenseType objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  The method teste whether both defense types have the same efficiencies
     *  for all possible weapon types at the moment. That means, the number of
     *  known weapon types can be different, but the behavior is still equal
     *  and this method will decide then for equal.
     *  @param DefenseType the TDefenseType object to be compared with *this
     *  @return @c true if the TDefenseType objects are equal, @c false if not */
    virtual bool operator==( const TDefenseType& DefenseType ) const;
  protected:
    /** This is the assignment operator for TDefenseType.                      */
    virtual TDefenseType& operator=( const TDefenseType& DefenseType );
    /** This is the type definition for the const iterator through the
     *  efficiencies array.                                                    */
    typedef TPEList<TEfficiencyToken>::const_iterator tEfficienciesIteratorConst;
    /** This is the type definition for the iterator through the efficiencies
     *  array.                                                                 */
    typedef TPEList<TEfficiencyToken>::iterator tEfficienciesIterator;
    /** the standard defense efficiency against all weapons                    */
    int2 fStandardEfficiency;
    /** the list of efficiencies of the defense type against different weapon
     *  types                                                                  */
    TPEList<TEfficiencyToken> fEfficiencies;
};



/*********************************** TArmorType ********************************/



/** @class TArmorType
 *  @brief TArmorType contains armor efficiencies against different weapons.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TArmorType
 *  @see TArmor
 *
 *  The class TArmorType provides the type for armor or rather the information
 *  about their efficiencies against different weapon types. It is derived
 *  from TDefenseType and has therefor an unique ID and can be linked (see
 *  also @ref TLinkable). An armor type contains a list/array with types of
 *  weapons and the related efficiencies of the armor (or shields) against
 *  them. The hit point value for armors is provided by TArmor. If a weapon
 *  type is not yet known a standard efficiency against all weapons is
 *  returned. This value can be changed with setStandardEfficiency and it can
 *  be read with getStandardEfficiency. The value of the standard efficiency
 *  is initialized with 100 if you use the constructor without parameters or
 *  to the value you want, if you use the constructor with StandardEfficiency
 *  as parameter. The 100 are chosen in expectation, that the values are
 *  percental values. If that's not correct, the implementation should perhaps
 *  be changed in fufture.                                                     */
class TArmorType : public TDefenseType
{
  public:
    /** This constructor generates a new TArmorType object with all
     *  properties resetted. This means the value for the standard efficiency
     *  is 100 and the defense type doesn't know any weapons types. These you
     *  have to make known with setDefenseEfficiency.                          */
    TArmorType();
    /** This constructor generates a also new TArmorType object, but only
     *  with the defense efficiencies resetted. The standard efficiency is set
     *  to the value given as parameter. The efficiencies against weapon types
     *  have to be set with setArmorEfficiency.                                */
    TArmorType( const int2 StandardEfficiency );
    /** This constructor creates also a new defense type, but the attributes
     *  are copied from the defense type given in OldArmorType. Mostly
     *  implemented to provide a copy constructor.                                                
     *  @param OldArmorType the TArmorType object which shall be copied        */
    TArmorType( const TArmorType& OldArmorType );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TArmorType();
    /** The method Load loads a TArmorType object from the data packages in
     *  the list. All sub classes of TArmorType have to reimplement the Load
     *  method and they @e must call TArmorType::Load explicitly in their Load
     *  method to load the data correctly.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TArmorType by adding the data packages to
     *  the list. All sub classes of TArmorType have to reimplement the Save
     *  method and they @e must call TArmorType::Save explicitly in their Save
     *  method to save the data correctly.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method operator== you can compare two TArmorType objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param ArmorType the TArmorType object to be compared with *this
     *  @return @c true if the TArmorType objects are equal, @c false if not   */
    virtual bool operator==( const TArmorType& ArmorType ) const;
    /** This is the assignment operator for TArmorType.                        */
    virtual TArmorType& operator=( const TArmorType& ArmorType );
};



/*********************************** TShieldType ********************************/



/** @class TShieldType
 *  @brief TShieldType contains shield efficiencies against different weapons.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TDefenseType
 *  @see TShield
 *
 *  The class TShieldType provides the type for shields or rather the
 *  information about their efficiencies against different weapon types. It is
 *  derived from TDefenseType and has therefor an unique ID and can be linked
 *  (see also @ref TLinkable). An shield type contains a list/array with types
 *  of weapons and the related efficiencies of the shield (or shields) against
 *  them. The hit point value for shields is provided by TShield. If a weapon
 *  type is not yet known a standard efficiency against all weapons is
 *  returned. This value can be changed with setStandardEfficiency and it can
 *  be read with getStandardEfficiency. The value of the standard efficiency
 *  is initialized with 100 if you use the constructor without parameters or
 *  to the value you want, if you use the constructor with StandardEfficiency
 *  as parameter. The 100 are chosen in expectation, that the values are
 *  percental values. If that's not correct, the implementation should perhaps
 *  be changed in fufture.<br>
 *  Besides the values inherited from TDefenseType TShieldType has a field for
 *  the regeneration rate of the shield. It is initialized with 0, but can be
 *  set with the method setRegenerationRate and can be read out with the
 *  method getRegenerationRate.                                                */
class TShieldType : public TDefenseType
{
  public:
    /** This constructor generates a new TShieldType object with all
     *  properties resetted. This means the value for the standard efficiency
     *  is 100 and the shield type doesn't know any weapons types. These you
     *  have to make known with setDefenseEfficiency.                          */
    TShieldType();
    /** This constructor generates a also new TShieldType object, but only
     *  with the defense efficiencies resetted. The standard efficiency is set
     *  to the value given as parameter. The efficiencies against weapon types
     *  have to be set with setShieldEfficiency.                               */
    TShieldType( const int2 StandardEfficiency );
    /** This constructor creates also a new defense type, but the attributes
     *  are copied from the defense type given in OldShieldType. Mostly
     *  implemented to provide a copy constructor.                                                
     *  @param OldShieldType the TShieldType object which shall be copied      */
    TShieldType( const TShieldType& OldShieldType );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TShieldType();
    /** The method Load loads a TShieldType object from the data packages in
     *  the list. All sub classes of TShieldType have to reimplement the Load
     *  method and they @e must call TShieldType::Load explicitly in their
     *  Load method to load the data correctly.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TShieldType by adding the data packages to
     *  the list. All sub classes of TShieldType have to reimplement the Save
     *  method and they @e must call TShieldType::Save explicitly in their
     *  Save method to save the data correctly.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method setRegenerationRate you can set the regeneration rate
     *  of shields of this shield type.
     *  @param RegenerationRate the new regeneration rate of the shield type   */
    virtual void setRegenerationRate( int2 RegenerationRate );
    /** With the method getRegenerationRate you can get the regeneration rate
     *  of shields of this shield type.
     *  @return the regeneration rate of the shield type                       */
    virtual int2 getRegenerationRate() const;
    /** With the method operator== you can compare two TShieldType objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param ShieldType the TShieldType object to be compared with *this
     *  @return @c true if the TShieldType objects are equal, @c false if not  */
    virtual bool operator==( const TShieldType& ShieldType ) const;
    /** This is the assignment operator for TShieldType.                       */
    virtual TShieldType& operator=( const TShieldType& ShieldType );
  protected:
    /** the regeneration rate of this shield type                              */
    int2 fRegenerationRate;
};



/********************************* class TArmor ********************************/



/** @class TArmor
 *  @brief TArmor represents a armor for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TArmor is derived from TItem and can therefore be put on a ship
 *  design. TArmor represents an armor for a ship design. As all other items
 *  it has tech level mass, volume and surface area. Besides that the armor
 *  has a number of hit points for the damage it can take and a type (as link
 *  to an object of type @ref TDefenseType). You can set and get these value
 *  with the respective set???? and get???? methods. Furthermore you can get
 *  (only get) the efficiencies of this armor against different weapon types
 *  with the method getArmorEfficiency. How the different efficiencies are
 *  interpreted exactly is up to the rule set/battle engine and of no direct
 *  concern of TArmor.                                                         */
class TArmor : public TItem
{
  public:
    /** This constructor generates a new TArmor object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TArmor();
    /** This constructor creates also a new armor, but the attributes are
     *  copied from the armor given in OldArmor. Mostly implemented to provide
     *  a copy constructor.                                                
     *  @param OldArmor the TArmor object which shall be copied                */
    TArmor( const TArmor& OldArmor );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TArmor();
     /** The method Load loads a TArmor object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TArmor object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
   /** The method getItemType returns the type of the item, in this case
     *  TItem::ARMOR for armor.          
     *  @return TItem::ARMOR                                                   */
    virtual TItem::tItemType getItemType() const;
    /** The method setHitPoints sets the amount of hit points the armor has.
     *  @param HitPoints the new amount of hit points for the armor            */
    virtual void setHitPoints( const int2 HitPoints );
    /** With the method getHitPoints you can get the amount of hit points the
     *  armor has.
     *  @return the hit points the armor has                                   */
    virtual int2 getHitPoints() const;
    /** With the method setArmorType you can set the type of the armor. The
     *  type is expected as object of type @ref TDefenseType.
     *  @param ArmorType the new type of the armor                             */
    virtual void setArmorType( TArmorType* ArmorType );
    /** With the method getArmotType you can get the type of the armor. The
     *  type is returned as object of type @ref TDefenseType.
     *  @param the type of the armor                                           */
    virtual const TArmorType* getArmorType() const;
    /** With the method getArmorEfficiency you can get the efficiency value of
     *  the armor against a certain weapon type.
     *  @param WeaponType the weapon type you want the efficieny against
     *  @return the efficiency against this weapon type                        */
    virtual int2 getArmorEfficiency( const TItem::tWeaponType WeaponType ) const;
    /** With the method operator== you can compare two TArmor objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param Armor the TArmor object which shall be compared with "*this"
     *  @return @c true if the TArmor objects are equal, @c false if not       */
    virtual bool operator==( const TArmor& Armor ) const;
    /** This is the assignment operator for TArmor.                            */
    virtual TArmor& operator=( const TArmor& Armor );
  protected:
    /** the hit points the armor has                                           */
    int2 fHitPoints;
    /** the type of the armor (see @ref TDefenseType)                          */
    TLink<TArmorType> fArmorType;
};




/******************************** class TShield ********************************/



/** @class TShield
 *  @brief TShield represents a shield for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TShield is derived from TItem and can therefore be put on a ship
 *  design. TShield represents a shield for a ship design. As all other items
 *  it has tech level mass, volume and surface area. Besides that the armor
 *  has a number of hit points it can take and a type (as link to an object of
 *  type @ref TDefenseType). You can set and get these value with the
 *  respective set???? and get???? methods. Furthermore you can get (only get)
 *  the efficiencies of this shield against different weapon types with the
 *  method getShieldEfficiency. How the different efficiencies are interpreted
 *  exactly is up to the rule set/battle engine and of no direct concern of
 *  TShield.                                                                   */
class TShield : public TItem
{
  public:
    /** This constructor generates a new TShield object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TShield();
    /** This constructor creates also a new shield, but the attributes are
     *  copied from the shield given in OldShield. Mostly implemented to
     *  provide a copy constructor.                                                
     *  @param OldShield the TShield object which shall be copied              */
    TShield( const TShield& OldShield );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TShield();
     /** The method Load loads a TShield object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TShield object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
   /** The method getItemType returns the type of the item, in this case
     *  TItem::SHIELD for shield.          
     *  @return TItem::SHIELD                                                  */
    virtual TItem::tItemType getItemType() const;
    /** The method setHitPoints sets the amount of hit points the shield has.
     *  @param HitPoints the new amount of hit points for the shield           */
    virtual void setHitPoints( const int2 HitPoints );
    /** With the method getHitPoints you can get amount of hit points the
     *  shield has.
     *  @return the amount of hit points the shield has                        */
    virtual int2 getHitPoints() const;
    /** With the method setShieldType you can set the type of the shield. The
     *  type is expected as object of type @ref TDefenseType.
     *  @param ShieldType the new type of the shield                           */
    virtual void setShieldType( TShieldType* ShieldType );
    /** With the method getArmotType you can get the type of the shield. The
     *  type is returned as object of type @ref TDefenseType.
     *  @param the type of the shield                                          */
    virtual const TShieldType* getShieldType() const;
    /** With the method getShieldEfficiency you can get the efficiency value of
     *  the shield against a certain weapon type.
     *  @param WeaponType the weapon type you want the efficieny against
     *  @return the efficiency against this weapon type                        */
    virtual int2 getShieldEfficiency( const TItem::tWeaponType WeaponType ) const;
    /** With the method operator== you can compare two TShield objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param Shield the TShield object which shall be compared with "*this"
     *  @return @c true if the TShield objects are equal, @c false if not      */
    virtual bool operator==( const TShield& Shield ) const;
    /** This is the assignment operator for TShield.                           */
    virtual TShield& operator=( const TShield& Shield );
  protected:
    /** the amount of hit points the shield has                                */
    int2 fHitPoints;
    /** the type of the shield (see @ref TDefenseType)                         */
    TLink<TShieldType> fShieldType;
};



/*******************************************************************************/
/******************************** W E A P O N S ********************************/
/*******************************************************************************/

/******************************** class TWeapon ********************************/



/** @class TWeapon
 *  @brief TWeapon represents an abstract weapon for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TWeapon is derived from TItem and it is (like TItem) a pure
 *  virtual class. The actual weapons will be derived from this class. At
 *  this level the properties damage points, rate of fire and weapon type are
 *  implemented. If in future weapon type gets an own class (until now it's
 *  an integer and different types are neede for kinetic weapons, energy
 *  weapons and perhaps other weapons, these types have to be derived from
 *  a type TWeaponType.                                                        */
class TWeapon : public TItem
{
  public:
    /** This constructor doesn't work, because TWeapon is a pure virtual
     *  class. It's only implemented to be used by the sub classes of TWeapon. */
    TWeapon();
    /** This constructor doesn't work either and is only implemented to
     *  provide a copy constructor for the sub classes.
     *  @param OldWeapon the TWeapon object which shall be copied              */
    TWeapon( const TWeapon& OldWeapon );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff. Doesn't work, because TWeapon is a pure
     *  virtual class and you wont be able to construct an object.             */
    virtual ~TWeapon();
    /** The method Load loads a TWeapon object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TWeapon object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, , but in this
     *  class it's pure virtual. Therefor it has be reimplemented in all
     *  derived classes.
     *  @return nothing                                                        */
    virtual TItem::tItemType getItemType() const = 0;
    /** The method setDamage sets the damage points the weapon causes per shot.
     *  @param DamagePoints the new amount of damage points the weapon causes  */
    virtual void setDamagePoints( const int2 DamagePoints );
    /** With the method getDamagePoints you can get the damage points the
     *  weapon causes per shot.
     *  @return the damage points the weapon causes                            */
    virtual int2 getDamagePoints() const;
    /** The method setRateOfFire sets the rate of fire of the weapon, that is
     *  how many shots it can fire in a certain time.
     *  @param RateOfFire the new rate of fire for the weapon                  */
    virtual void setRateOfFire( const int2 RateOfFire );
    /** With the method getRateOfFire you can get the rate of fire of the
     *  weapon, that is how many shots it can fire in a certain time.
     *  @return the rate of fire for the weapon                                */
    virtual int2 getRateOfFire() const;
    /** The method setWeaponType sets the type of the weapon.
     *  @param WeaponType the new type of the weapon                           */
    virtual void setWeaponType( const TItem::tWeaponType WeaponType );
    /** With the method getWeaponType you can get the type of the weapon.
     *  @return the type of the weapon                                         */
    virtual TItem::tWeaponType getWeaponType() const;
    /** With the method operator== you can compare two TWeapon objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param Weapon the TWeapon object which shall be compared with *this
     *  @return @c true if TWeapon objects are equal, @c false if not          */
    virtual bool operator==( const TWeapon& Weapon ) const;
  protected:
     /** The assignment operator for TWeapon                                   */
    virtual TWeapon& operator=( const TWeapon& Weapon );
   /** the damage points the weapon causes                                     */
    int2 fDamagePoints;
    /** the rate of fire for the weapon                                        */
    int2 fRateOfFire;
    /** the type of the weapon                                                 */
    TItem::tWeaponType fWeaponType;
};



/******************************* class TKWeapon ********************************/



/** @class TKWeapon
 *  @brief TKWeapon represents a kinetic energy weapon for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TKWeapon is derived from TWeapon (and that is derived from TItem)
 *  and can therefore be put on a ship design. TKWeapon represents a kinetic
 *  energy weapon for a ship. As all other items it has mass, volume and
 *  surface area. A kinetic energy weapon has additionally all value inherited
 *  from TWeapon like values for damage points (dp) of caused damage, rate of
 *  fire and weapon type. Besides that it has values for velocity of the
 *  projectile and the size of the ammunition. The meaning of this values and
 *  which different types exist and what they do is  up to the rule set/battle
 *  engine and of no direct concern to the TKWeapon item class.
 *  FIXME, until now, the type of the weapon is an integer. This could change
 *  in future.                                                                 */
class TKWeapon : public TWeapon
{
  public:
    /** This constructor generates a new TKWeapon object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TKWeapon();
    /** This constructor creates also a new kinetic energy weapon, but the
     *  attributes are copied from the kinetic energy weapon given in
     *  OldKWeapon. Mostly implemented to provide a copy constructor.
     *  @param OldKWeapon the TKWeapon object which shall be copied            */
    TKWeapon( const TKWeapon& OldKWeapon );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TKWeapon();
    /** The method Load loads a TKWeapon object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TKWeapon object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::KWEAPON for kinetic weapon.
     *  @return TItem::KWEAPON                                                 */
    virtual TItem::tItemType getItemType() const;
    /** The method setVelocity sets the velocity of the projectile of the
     *  kinetic weapon.
     *  @param Velocity the new velocity of the projectile of the weapon       */
    virtual void setVelocity( const int4 Velocity );
    /** With the method getVelocity you can get the velocity of the projectile
     *  of the kinetic weapon.
     *  @return the velocity of the projectile of the weapon                   */
    virtual int4 getVelocity() const;
    /** The method setAmmunitionSize sets the size of the ammunition of this
     *  kinetic weapon. This is important, if you want to know, how much
     *  ammunition you can store in a given cargo space.
     *  @param AmmunitionSize the new ammunition size of the weapon            */
    virtual void setAmmunitionSize( const int2 AmmunitionSize );
    /** With the method getAmmunitionSize you can get the ammunition size of
     *  this kinetic weapon. This is important, if you want to know, how much
     *  ammunition you can store in a given cargo space.
     *  @return the ammunition size of the kinetic weapon                      */
    virtual int2 getAmmunitionSize() const;
    /** With the method operator== you can compare two TKWeapon objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param KWeapon the TKWeapon object which shall be compared with *this
     *  @return @c true if TKWeapon objects are equal, @c false if not         */
    virtual bool operator==( const TKWeapon& KWeapon ) const;
    /** This is the assignment operator for TKWeapon.                          */
    virtual TKWeapon& operator=( const TKWeapon& KWeapon );
  protected:
    /** the velocity of the projectile of the kinetic weapon                   */
    int4 fVelocity;
    /** the ammunition size of the kinetic weapon                              */
    int2 fAmmunitionSize;
};



/******************************* class TEWeapon ********************************/



/** @class TEWeapon
 *  @brief TEWeapon represents a standard energy weapon for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TEWeapon is derived from TItem (and that is derived from TItem)
 *  and can therefore be put on a ship design. TEWeapon represents a standard
 *  energy weapon for a ship. As all other items it has mass, volume and
 *  surface area. A standard energy weapon has additionally all value inherited
 *  from TWeapon like values for damage points (dp) of caused damage, rate of
 *  fire and weapon type. Besides taht it has a value for efficient range. The
 *  meaning of this values and which different types exist and what they do is
 *  up to the rule set/battle engine and of no direct concern to the TEWeapon
 *  item class.
 *  FIXME, until now, the type of the weapon is an integer. This could change
 *  in future.                                                                 */
class TEWeapon : public TWeapon
{
  public:
    /** This constructor generates a new TEWeapon object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TEWeapon();
    /** This constructor creates also a new standard energy weapon, but the
     *  attributes are copied from the standard energy weapon given in
     *  OldEWeapon. Mostly implemented to provide a copy constructor.
     *  @param OldEWeapon the TEWeapon object which shall be copied            */
    TEWeapon( const TEWeapon& OldEWeapon );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TEWeapon();
    /** The method Load loads a TEWeapon object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TEWeapon object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::EWEAPON for energy weapon.
     *  @return TItem::EWEAPON                                                 */
    virtual TItem::tItemType getItemType() const;
    /** The method setEfficientRange sets the efficient range in which a shot
     *  still causes significant damage.
     *  @param EfficientRange the new efficient range of the weapon            */
    virtual void setEfficientRange( const int4 EfficientRange );
    /** With the method getEfficientRange you can get the efficient range in
     *  which a shot still causes significant damage.
     *  @return the efficient range of the weapon                              */
    virtual int4 getEfficientRange() const;
    /** With the method operator== you can compare two TEWeapon objects. 
     *  This is of course the behaviour one would expect from "operator==".
     *  @param EWeapon the TEWeapon object which shall be compared with *this
     *  @return @c true if TEWeapon objects are equal, @c false if not         */
    virtual bool operator==( const TEWeapon& EWeapon ) const;
    /** This is the assignment operator for TEWeapon.                          */
    virtual TEWeapon& operator=( const TEWeapon& EWeapon );
  protected:
    /** the efficient range of the standard energy weapon                      */
    int4 fEfficientRange;
};



/************************** class TTargetingComputer ***************************/



/** @class TTargetingComputer
 *  @brief TTargetingComputer represents a targeting computer for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TTargetingComputer is derived from TItem and can therefore be put
 *  on a ship design. TTargetingComputer represents a targeting computer for a
 *  ship. As all other items it has mass, volume and surface area. A targeting
 *  computer improves the aiming capabilities of the ships kinetic and energy
 *  weapons. Which effects this has exactly is decided by the rule set and of
 *  no direct concern to the TTargetingComputer item class.                    */
class TTargetingComputer : public TItem
{
  public:
    /** This constructor generates a new TTargetingComputer object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective set<something>
     *  methods.                                                               */
    TTargetingComputer();
    /** This constructor creates also a new targeting computer, but its
     *  attributes are copied from the targeting computer given in
     *  OldTargetingComputer. This method is mostly implemented to provide a
     *  copy constructor.
     *  @param OldTargetingComputer the TTargetingComputer object which shall
     *                              be copied                                  */
    TTargetingComputer( const TTargetingComputer& OldTargetingComputer );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TTargetingComputer();
    /** The method Load loads a TTargetingComputer object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TTargetingComputer object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::TARGETINGCOMPUTER for targeting computer.
     *  @return TItem::TARGETINGCOMPUTER                                       */
    virtual TItem::tItemType getItemType() const;
    /** The method setAimingEfficiency sets the aiming efficiency of the
     *  targeting computer.
     *  @param AimingEfficiency the targeting computer's efficiency            */
    virtual void setAimingEfficiency( const int2 AimingEfficiency );
    /** With the method getAimingEfficiency you can get the aiming
     *  efficiency of the targeting computer.
     *  @return the targeting computer's aiming efficiency                     */
    virtual int2 getAimingEfficiency() const;
    /** With the method operator== you can compare two TTargetingComputer
     *  objects. This is of course the behaviour one would expect from
     *  "operator==".
     *  @param TargetingComputer the TTargetingComputer object which shall be
     *                           compared with "*this"
     *  @return @c true if the TTargetingComputer objects are euqal and
     *          @c false if not                                                */
    virtual bool operator==( const TTargetingComputer& TargetingComputer ) const;
    /** This is the assignment operator for TTargetingComputer.                */
    virtual TTargetingComputer& operator=( const TTargetingComputer& TargetingComputer );
  protected:
    /** the aiming efficiency of the targeting computer                     */
    int2 fAimingEfficiency;
};



/******************************* class TScanner ********************************/



/** @class TScanner
 *  @brief TScanner represents a scanner for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TScanner is derived from TItem and it is (like TItem) a pure
 *  virtual class. The actual scanners will be derived from this class. But
 *  already at this level the value ScanEfficiency is implemented because all
 *  sub classes need it. Only the method getScannerType() is pure virtual and
 *  is implemented in each of the sub classes. The scanner type which is
 *  returned is of type tScannerType, an enum in this class. Which effects the
 *  value ScanEfficiency exactly has is decided by the rule set/battle engine
 *  and of no direct concern to TScanner or its sub classes. Because it is
 *  a pure virtual class there is also no operator=.                           */
class TScanner : public TItem
{
  public:
    /** Each from TScanner derived class (i.e. @ref TScannerNormalActive) will
     *  return one of these constants to indentify itself. This is especially
     *  important in connection with the battle engine.                        */
    typedef enum
    {
      NORMAL_ACTIVE        = 0x0001,
      NORMAL_PASSIVE       = 0x0002,
      ANTIDISGUISE_ACTIVE  = 0x0004,
      ANTIDISGUISE_PASSIVE = 0x0008,
      ANTICLOAK_ACTIVE     = 0x0010,
      ANTICLOAK_PASSIVE    = 0x0020,
      PENETRATE_ACTIVE     = 0x0040,
      PENETRATE_PASSIVE    = 0x0080
    } tScannerType;
    /** This constructor doesn't work, because TScanner is a pure virtual
     *  class. It's only implemented to be used by the sub classes of TScanner.*/
    TScanner();
    /** This constructor doesn't work either and is implemented to provide
     *  a copy constructor for the sub classes.
     *  @param OldScanner the scanner which shall be copied.                   */
    TScanner( const TScanner& OldScanner );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff. Doesn't work, because TScanner is a pure
     *  virtual class and you wont be able to construct an object.             */
    virtual ~TScanner();
    /** The method Load loads a TScanner object from the data packages in
     *  the list. All sub classes of TScanner have to reimplement the Load
     *  method and they @e must call TScanner::Load explicitly in their Load
     *  method to load the data correctly.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScanner object by adding the data packages
     *  to the list. All sub classes of TScanner have to reimplement the Save
     *  method and they @e must call TScanner::Save explicitly in their Save
     *  method to save the data correctly.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::SCANNER for targeting computer.
     *  @return TItem::SCANNER                                                 */
    virtual TItem::tItemType getItemType() const;
    /** With the method getScannerType you can get the type of the scanner,
     *  that means whether it is a normal active scanner or something else.
     *  This method has to be reimplemented in all the derived classes.
     *  @return nothing                                                        */
    virtual TScanner::tScannerType getScannerType() const = 0;
    /** The method setScanEfficiency sets the efficiency of the scanner. An
     *  actual object will be of one of the sub classes, but because they will
     *  not change anything at this method, it will not have to be
     *  reimplemented in the sub classes.
     *  @param ScanEfficiency the scanner's efficiency                         */
    virtual void setScanEfficiency( const int2 ScanEfficiency );
    /** With the method getScanEfficiency you can get the scanner's efficiency
     *  An actual object will be of one of the sub classes, but because they
     *  will not change anything at this method, it will not have to be
     *  reimplemented in the sub classes.
     *  @return the scanner's efficiency                                       */
    virtual int2 getScanEfficiency() const;
    /** With the method setShortRange you can set the range of the short range
     *  scan ability of the scanner. This is the range the scanner has on the
     *  battle field.
     *  @param Range the new range for the short range scan abilities          */
    virtual void setShortRange( int4 Range );
    /** With the method getShortRange you can get the range of the short range
     *  scan ability of the scanner. This is the range the scanner has on the
     *  battle field.
     *  @param the range of the short range scan abilities                     */
    virtual int4 getShortRange();
    /** With the method setLongRange you can set the range of the long range
     *  scan ability of the scanner. This is the range the scanner has on the
     *  star map.       
     *  @param Range the new range for the long range scan abilities           */
    virtual void setLongRange( int2 Range );
    /** With the method getLongRange you can get the range of the long range
     *  scan ability of the scanner. This is the range the scanner has on the
     *  astar map.          
     *  @param the range of the long range scan abilities                      */
    virtual int2 getLongRange();
    /** With the method operator== you can compare two TScanner objects. This
     *  is of course the behaviour one would expect from "operator==".
     *  @param Scanner the TScanner object which shall be compared with "*this"
     *  @return @c true if TScanner objects are euqal, @c false if not     */
    virtual bool operator==( const TScanner& Scanner ) const;
  protected:
     /** The assignment operator for TScanner                                  */
    virtual TScanner& operator=( const TScanner& Scanner );
    /** the scanner's efficiency                                               */
    int2 fScanEfficiency;
    /** the range of the short range scan abilities (battle field)             */
    int4 fShortRange;
    /** the range of the long range scan abilities (star map)                  */
    int2 fLongRange;
};



/* TScanner sub classes */



/** @class TScannerNormalActive
 *  @brief TScannerNormalActive represents a active normal scanner for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerNormalActive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A active normal scanner is a
 *  scanner which tries to locate the exact position of the enemy ship.
 *  Because it is active it should be more effective than the passive version.
 *  On the down side, because it's active nature it also increases the risk of
 *  being dectected. But the exact efficiency value and which effects it
 *  exactly has is decided by the rule set/battle engine and of no direct
 *  concern to the class TScannerNormalActive.                                 */
class TScannerNormalActive : public TScanner
{
  public:
    /** This constructor generates a new TScannerNormalActive object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerNormalActive();
    /** This constructor creates also a new active normal scanner, but its
     *  attributes are copied from the TScannerNormalActive object given in
     *  OldScannerNormalActive. This method is mostly implemented to provide
     *  a copy constructor.
     *  @param OldScannerNormalActive the normal active scanner which shall be
     *                                copied                                   */
    TScannerNormalActive( const TScannerNormalActive& OldScannerNormalActive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerNormalActive();
    /** The method Load loads a TScannerNormalActive object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerNormalActive object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::NORMAL_ACTIVE.
     *  @return TScanner::NORMAL_ACTIVE                                        */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerNormalActive.
     *  @param ScannerNormalActive the TScannerNormalActive object which shall
     *                             be compared with "*this"
     *  @return @c true if the TScannerNormalActive objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TScannerNormalActive& ScannerNormalActive ) const;
    /** This is the assignment operator for TScannerNormalActive.              */
    virtual TScannerNormalActive& operator=(const TScannerNormalActive& ScannerNormalActive);
};



/** @class TScannerNormalPassive
 *  @brief TScannerNormalPassive represents a passive normal scanner for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerNormalPassive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A passive normal scanner is a
 *  scanner which tries to locate the exact position of the enemy ship.
 *  Because it is passive it should be less effective than the active version.
 *  On the plus side, because of its passive nature, there is no increased
 *  risk of being detected. But the exact efficiency value and which effects
 *  it exactly has is decided by the rule set/battle engine and of no direct
 *  concern to the class TScannerNormalPassive.                                */
class TScannerNormalPassive : public TScanner
{
  public:
    /** This constructor generates a new TScannerNormalPassive object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective set<something>
     *  methods.                                                               */
    TScannerNormalPassive();
    /** This constructor creates also a new passive normal scanner, but its
     *  attributes are copied from the TScannerNormalPassive object given in
     *  OldScannerNormalPassive. This method is mostly implemented to provide
     *  a copy constructor.
     *  @param OldScannerNormalPassive the normal passive scanner which shall
     *                                 be copied                               */
    TScannerNormalPassive( const TScannerNormalPassive& OldScannerNormalPassive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerNormalPassive();
    /** The method Load loads a TScannerNormalPassive object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerNormalPassive object by adding the
     *  data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::NORMAL_PASSIVE.
     *  @return TScanner::NORMAL_PASSIVE                                       */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerNormalPassive.
     *  @param ScannerNormalPassive the TScannerNormalPassive object which shall
     *                              be compared with "*this"
     *  @return @c true if the TScannerNormalPassive objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TScannerNormalPassive& ScannerNormalPassive ) const;
    /** This is the assignment operator for TScannerNormalPassive.              */
    virtual TScannerNormalPassive& operator=(const TScannerNormalPassive& ScannerNormalPassive);
};



/** @class TScannerAntiDisguiseActive
 *  @brief TScannerAntiDisguise represents a active anti disguise scanner.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerAntiDisguiseActive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A active anti disguise scanner
 *  is a scanner which tries to indentify the true type/shape of an enemy ship,
 *  to prevent that a small ship is perceived as a huge battleship (or vice
 *  versa). Because it is active it should be more effective than the passive
 *  version. On the down side, because it's active nature it also increases
 *  the risk of being dectected. But the exact efficiency value and which
 *  effects it exactly has is decided by the rule set/battle engine and of no
 *  direct concern to the class TScannerAntiDisguiseActive.                    */
class TScannerAntiDisguiseActive : public TScanner
{
  public:
    /** This constructor generates a new TScannerAntiDisguiseActive object
     *  with all properties resetted. This means you have to set all
     *  properties like name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerAntiDisguiseActive();
    /** This constructor creates also a new active anti disguise scanner, but
     *  its attributes are copied from the TScannerAntiDisguiseActive object
     *  given in OldScannerAntiDisguiseActive. This method is mostly
     *  implemented to provide a copy constructor.
     *  @param OldScannerAntiDisguiseActive the normal active scanner which
     *                                      shall be copied                    */
    TScannerAntiDisguiseActive( const TScannerAntiDisguiseActive& OldScannerAntiDisguiseActive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerAntiDisguiseActive();
    /** The method Load loads a TScannerAntiDisguiseActive object from the
     *  data packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerAntiDisguiseActive object by adding
     *  the data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::ANTIDISGUISE_ACTIVE.
     *  @return TScanner::ANTIDISGUISE_ACTIVE                                  */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerAntiDisguiseActive.
     *  @param ScannerAntiDisguiseActive the TScannerAntiDisguiseActive object
     *                                   which shall be compared with "*this"
     *  @return @c true if the TScannerAntiDisguiseActive objects are equal
     *          and @c false if not                                            */
    virtual bool operator==( const TScannerAntiDisguiseActive& ScannerAntiDisguiseActive ) const;
    /** This is the assignment operator for TScannerAntiDisguiseActive.        */
    virtual TScannerAntiDisguiseActive& operator=(const TScannerAntiDisguiseActive& ScannerAntiDisguiseActive);
};



/** @class TScannerAntiDisguisePassive
 *  @brief TScannerAntiDisguise represents a passive anti disguise scanner.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerAntiDisguisePassive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A passive anti disguise scanner
 *  is a scanner which tries to indentify the true type/shape of an enemy ship,
 *  to prevent that a small ship is perceived as a huge battleship (or vice
 *  versa). Because it is passive it should be less effective than the active
 *  version. On the plus side, because of its passive nature, there is no
 *  increased risk of being detected. But the exact efficiency value and which
 *  effects it exactly has is decided by the rule set/battle engine and of no
 *  direct concern to the class TScannerAntiDisguisePassive.                   */
class TScannerAntiDisguisePassive : public TScanner
{
  public:
    /** This constructor generates a new TScannerAntiDisguisePassive object
     *  with all properties resetted. This means you have to set all
     *  properties like name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerAntiDisguisePassive();
    /** This constructor creates also a new passive anti disguise scanner, but
     *  its attributes are copied from the TScannerAntiDisguisePassive object
     *  given in OldScannerAntiDisguisePassive. This method is mostly
     *  implemented to provide a copy constructor.
     *  @param OldScannerAntiDisguisePassive the normal passive scanner which
     *                                      shall be copied                    */
    TScannerAntiDisguisePassive( const TScannerAntiDisguisePassive& OldScannerAntiDisguisePassive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerAntiDisguisePassive();
    /** The method Load loads a TScannerAntiDisguisePassive object from the
     *  data packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerAntiDisguisePassive object by adding
     *  the data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::ANTIDISGUISE_PASSIVE.
     *  @return TScanner::ANTIDISGUISE_PASSIVE                                  */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerAntiDisguisePassive.
     *  @param ScannerAntiDisguisePassive the TScannerAntiDisguisePassive object
     *                                   which shall be compared with "*this"
     *  @return @c true if the TScannerAntiDisguisePassive objects are equal
     *          and @c false if not                                            */
    virtual bool operator==( const TScannerAntiDisguisePassive& ScannerAntiDisguisePassive ) const;
    /** This is the assignment operator for TScannerAntiDisguisePassive.        */
    virtual TScannerAntiDisguisePassive& operator=(const TScannerAntiDisguisePassive& ScannerAntiDisguisePassive);
};



/** @class TScannerAntiCloakActive
 *  @brief TScannerAntiCloak represents a active anti cloak scanner.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerAntiCloakActive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A active anti cloak scanner is a
 *  scanner which tries to detect cloaked ships. Because it is active it
 *  should be more effective than the passive version. On the down side,
 *  because it's active nature it also increases the risk of being dectected.
 *  But the exact efficiency value and which effects it exactly has is decided
 *  by the rule set/battle engine and of no direct concern to the class
 *  TScannerAntiCloakActive.                                                   */
class TScannerAntiCloakActive : public TScanner
{
  public:
    /** This constructor generates a new TScannerAntiCloakActive object with
     *  all properties resetted. This means you have to set all properties
     *  like name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerAntiCloakActive();
    /** This constructor creates also a new active anti cloak scanner, but its
     *  attributes are copied from the TScannerAntiCloakActive object given
     *  in OldScannerAntiCloakActive. This method is mostly implemented to
     *  provide a copy constructor.
     *  @param OldScannerAntiCloakActive the normal active scanner which
     *                                   shall be copied                       */
    TScannerAntiCloakActive( const TScannerAntiCloakActive& OldScannerAntiCloakActive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerAntiCloakActive();
    /** The method Load loads a TScannerAntiCloakActive object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerAntiCloakActive object by adding the
     *  data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::ANTICLOAK_ACTIVE.
     *  @return TScanner::ANTICLOAK_ACTIVE                                     */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerAntiCloakActive.
     *  @param ScannerAntiCloakActive the TScannerAntiCloakActive object
     *                                which shall be compared with "*this"
     *  @return @c true if the TScannerAntiCloakActive objects are equal
     *          and @c false if not                                            */
    virtual bool operator==( const TScannerAntiCloakActive& ScannerAntiCloakActive ) const;
    /** This is the assignment operator for TScannerAntiCloakActive.           */
    virtual TScannerAntiCloakActive& operator=(const TScannerAntiCloakActive& ScannerAntiCloakActive);
};



/** @class TScannerAntiCloakPassive
 *  @brief TScannerAntiCloak represents a passive anti cloak scanner.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerAntiCloakPassive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A passive anti cloak scanner
 *  is a scanner which tries to detect cloaked ships. Because it is passive it
 *  should be less effective than the active version. On the plus side,
 *  because of its passive nature, there is no increased risk of being
 *  detected. But the exact efficiency value and which effects it exactly has
 *  is decided by the rule set/battle engine and of no direct concern to the
 *  class TScannerAntiCloakPassive.                                            */
class TScannerAntiCloakPassive : public TScanner
{
  public:
    /** This constructor generates a new TScannerAntiCloakPassive object with
     *  all properties resetted. This means you have to set all properties
     *  like name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerAntiCloakPassive();
    /** This constructor creates also a new passive anti cloak scanner, but
     *  its attributes are copied from the TScannerAntiCloakPassive object
     *  given in OldScannerAntiCloakPassive. This method is mostly implemented
     *  to provide a copy constructor.
     *  @param OldScannerAntiCloakPassive the normal passive scanner which
     *                                    shall be copied                      */
    TScannerAntiCloakPassive( const TScannerAntiCloakPassive& OldScannerAntiCloakPassive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerAntiCloakPassive();
    /** The method Load loads a TScannerAntiCloakPassive object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerAntiCloakPassive object by adding the
     *  data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::ANTICLOAK_PASSIVE.
     *  @return TScanner::ANTICLOAK_PASSIVE                                    */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerAntiCloakPassive.
     *  @param ScannerAntiCloakPassive the TScannerAntiCloakPassive object
     *                                 which shall be compared with "*this"
     *  @return @c true if the TScannerAntiCloakPassive objects are equal
     *          and @c false if not                                            */
    virtual bool operator==( const TScannerAntiCloakPassive& ScannerAntiCloakPassive ) const;
    /** This is the assignment operator for TScannerAntiCloakPassive.          */
    virtual TScannerAntiCloakPassive& operator=(const TScannerAntiCloakPassive& ScannerAntiCloakPassive);
};



/** @class TScannerPenetrateActive
 *  @brief TScannerPenetrateActive represents a active penetrate scanner.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerPenetrateActive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A active penetrate scanner is a
 *  scanner which tries to "see" inside an (enemy) ship. Because it is active
 *  it should be more effective than the passive version. On the down side,
 *  because it's active nature it also increases the risk of being dectected.
 *  But the exact efficiency value and which effects it exactly has is decided
 *  by the rule set/battle engine and of no direct concern to the class
 *  TScannerPenetrateActive.                                                   */
class TScannerPenetrateActive : public TScanner
{
  public:
    /** This constructor generates a new TScannerPenetrateActive object with
     *  all properties resetted. This means you have to set all properties
     *  like name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerPenetrateActive();
    /** This constructor creates also a new active penetrate scanner, but its
     *  attributes are copied from the TScannerPenetrateActive object given in
     *  OldScannerPenetrateActive. This method is mostly implemented to
     *  provide a copy constructor.
     *  @param OldScannerPenetrateActive the penetrate active scanner which
     *                                   shall be copied                       */
    TScannerPenetrateActive( const TScannerPenetrateActive& OldScannerPenetrateActive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerPenetrateActive();
    /** The method Load loads a TScannerPenetrateActive object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerPenetrateActive object by adding the
     *  data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::PENETRATE_ACTIVE.
     *  @return TScanner::PENETRATE_ACTIVE                                     */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerPenetrateActive.
     *  @param ScannerPenetrateActive the TScannerPenetrateActive object which
     *                                shall be compared with "*this"
     *  @return @c true if the TScannerPenetrateActive objects are equal
     *          and @c false if not                                            */
    virtual bool operator==( const TScannerPenetrateActive& ScannerPenetrateActive ) const;
    /** This is the assignment operator for TScannerPenetrateActive.           */
    virtual TScannerPenetrateActive& operator=(const TScannerPenetrateActive& ScannerPenetrateActive);
};



/** @class TScannerPenetratePassive
 *  @brief TScannerPenetratePassive represents a passive penetrate scanner.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TScanner
 *
 *  The class TScannerPenetratePassive is derived from TScanner and and can
 *  therefor be put on a ship. It has a value ScanEfficiency (implemented in
 *  TScanner) and get and set methods for it. A passive penetrate scanner is a
 *  scanner which tries to "see" inside an (enemy) ship. Because it is passive
 *  it should be less effective than the active version. On the plus side,
 *  because of its passive nature, there is no increased risk of being
 *  detected. But the exact efficiency value and which effects it exactly has
 *  is decided by the rule set/battle engine and of no direct concern to the
 *  class TScannerPenetratePassive.                                            */
class TScannerPenetratePassive : public TScanner
{
  public:
    /** This constructor generates a new TScannerPenetratePassive object with
     *  all properties resetted. This means you have to set all properties
     *  like name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TScannerPenetratePassive();
    /** This constructor creates also a new passive penetrate scanner, but its
     *  attributes are copied from the TScannerPenetratePassive object given
     *  in OldScannerPenetratePassive. This method is mostly implemented to
     *  provide a copy constructor.
     *  @param OldScannerPenetratePassive the penetrate passive scanner which
     *                                    shall be copied                      */
    TScannerPenetratePassive( const TScannerPenetratePassive& OldScannerPenetratePassive );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TScannerPenetratePassive();
    /** The method Load loads a TScannerPenetratePassive object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TScannerPenetratePassive object by adding the
     *  data packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getScannerType you can get the type of the scanner, in
     *  this case TScanner::PENETRATE_PASSIVE.
     *  @return TScanner::PENETRATE_PASSIVE                                    */
    virtual TScanner::tScannerType getScannerType() const;
    /** This is the compare operator for TScannerPenetratePassive.
     *  @param ScannerPenetratePassive the TScannerPenetratePassive object
     *                                 which shall be compared with "*this"
     *  @return @c true if the TScannerPenetratePassive objects are equal
     *          and @c false if not                                            */
    virtual bool operator==( const TScannerPenetratePassive& ScannerPenetratePassive ) const;
    /** This is the assignment operator for TScannerPenetratePassive.          */
    virtual TScannerPenetratePassive& operator=(const TScannerPenetratePassive& ScannerPenetratePassive);
};



/******************************** class TJammer ********************************/



/** @class TJammer
 *  @brief TJammer represents a jammer for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TJammer is derived from TItem and it is (like TItem) a pure
 *  virtual class. The actual jammers will be derived from this class. But
 *  already at this level the value JamEfficiency is implemented because all
 *  sub classes need it. Only the method getJammerType() is pure virtual and
 *  is implemented in each of the sub classes. The jammer type which is
 *  returned is of type tJammerType, an enum in this class. Which effects the
 *  value JamEfficiency exactly has is decided by the rule set/battle engine
 *  and of no direct concern to TJammer or its sub classes. Because it is a
 *  pure virtual class there is also no operator=.                             */
class TJammer : public TItem
{
  public:
    /** Each from TJammer derived class (i.e. @ref TJammerNormal) will return
     *  one of these constants to indentify itself. This is especially
     *  important in connection with the battle engine.                        */
    typedef enum
    {
      NORMAL        = 0x0001,
      DISGUISE      = 0x0002,
      CLOAK         = 0x0004,
      ANTIPENETRATE = 0x0008
    } tJammerType;
    /** This constructor doesn't work, because TJammer is a pure virtual
     *  class. It's only implemented to be used by the sub classes of TJammer. */
    TJammer();
    /** This constructor doesn't work either and is implemented to provide
     *  a copy constructor for the sub classes.
     *  @param OldJammer the jammer which shall be copied.                     */
    TJammer( const TJammer& OldJammer );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff. Doesn't work, because TJammer is a pure
     *  virtual class and you wont be able to construct an object.             */
    virtual ~TJammer();
    /** The method Load loads a TJammer object from the data packages in the
     *  list. All sub classes of TJammer have to reimplement the Load method
     *  and they @e must call TJammer::Load explicitly in their Load method to
     *  load the data correctly.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TJammer object by adding the data packages to
     *  the list. All sub classes of TJammer have to reimplement the Save
     *  method and they @e must call TJammer::Save explicitly in their Save
     *  method to save the data correctly.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::JAMMER for targeting computer.
     *  @return TItem::JAMMER                                                  */
    virtual TItem::tItemType getItemType() const;
    /** With the method getJammerType you can get the type of the jammer,
     *  that means whether it is a normal jammer or something else. This
     *  method has to be reimplemented in all the derived classes.
     *  @return nothing                                                        */
    virtual TJammer::tJammerType getJammerType() const = 0;
    /** The method setJamEfficiency sets the efficiency of the jammer. An
     *  actual object will be of one of the sub classes, but because they will
     *  not change anything at this method, it will not have to be
     *  reimplemented in the sub classes.
     *  @param JamEfficiency the jammer's efficiency                           */
    virtual void setJamEfficiency( const int2 JamEfficiency );
    /** With the method getJamEfficiency you can get the jammer's efficiency
     *  An actual object will be of one of the sub classes, but because they
     *  will not change anything at this method, it will not have to be
     *  reimplemented in the sub classes.
     *  @return the jammer's efficiency                                        */
    virtual int2 getJamEfficiency() const;
    /** With the method operator== you can compare two TJammer objects. This
     *  is of course the behaviour one would expect from "operator==".
     *  @param Jammer the TJammer object which shall be compared with "*this"
     *  @return @c true if TJammer objects are equal, @c false if not       */
    virtual bool operator==( const TJammer& Jammer ) const;
  protected:
     /** The assignment operator for TJammer                                   */
    virtual TJammer& operator=( const TJammer& Jammer );
    /** the jammer's efficiency                                                */
    int2 fJamEfficiency;
};



/* TJammer sub classes */



/** @class TJammerNormal
 *  @brief TJammerNormal represents a normal jammer for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TJammer
 *
 *  The class TJammerNormal is derived from TJammer and and can therefor be
 *  put on a ship. It has a value JamEfficiency (implemented in TJammer) and
 *  get and set methods for it. A normal jammer is a jammer which tries to
 *  prevent the real ship location from being detected. But the exact
 *  efficiency value and which effects it exactly has is decided by the rule
 *  set/battle engine and of no direct concern to the class TJammerNormal.     */
class TJammerNormal : public TJammer
{
  public:
    /** This constructor generates a new TJammerNormal object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TJammerNormal();
    /** This constructor creates also a new normal jammer, but its attributes
     *  are copied from the TJammerNormal object given in OldJammerNormal.
     *  This method is mostly implemented to provide a copy constructor.
     *  @param OldJammerNormal the normal jammer which shall be copied         */
    TJammerNormal( const TJammerNormal& OldJammerNormal );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TJammerNormal();
    /** The method Load loads a TJammerNormal object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TJammerNormal object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getJammerType you can get the type of the jammer, in
     *  this case TJammer::NORMAL.
     *  @return TJammer::NORMAL                                                */
    virtual TJammer::tJammerType getJammerType() const;
    /** This is the compare operator for TJammerNormal.
     *  @param JammerNormal the TJammerNormal object which shall be compared
     *                      with "*this"
     *  @return @c true if the TJammerNormal objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TJammerNormal& JammerNormal ) const;
    /** This is the assignment operator for TJammerNormal.                     */
    virtual TJammerNormal& operator=(const TJammerNormal& JammerNormal);
};



/** @class TJammerDisguise
 *  @brief TJammerDisguise represents a disguise jammer for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TJammer
 *
 *  The class TJammerDisguise is derived from TJammer and and can therefor be
 *  put on a ship. It has a value JamEfficiency (implemented in TJammer) and
 *  get and set methods for it. A disguise jammer is a jammer which tries to
 *  disguise the real type/shape of the ship, so that a small ship is
 *  perceived as a huge battleship (or vice versa). But the exact efficiency
 *  value and which effects it exactly has is decided by the rule set/battle
 *  engine and of no direct concern to the class TJammerDisguise.              */
class TJammerDisguise : public TJammer
{
  public:
    /** This constructor generates a new TJammerDisguise object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TJammerDisguise();
    /** This constructor creates also a new disguise jammer, but its
     *  attributes are copied from the TJammerDisguise object given in
     *  OldJammerDisguise. This method is mostly implemented to provide a
     *  copy constructor.
     *  @param OldJammerDisguise the disguise jammer which shall be copied     */
    TJammerDisguise( const TJammerDisguise& OldJammerDisguise );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TJammerDisguise();
    /** The method Load loads a TJammerDisguise object from the data packages
     *  in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TJammerDisguise object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getJammerType you can get the type of the jammer, in
     *  this case TJammer::DISGUISE.
     *  @return TJammer::DISGUISE                                              */
    virtual TJammer::tJammerType getJammerType() const;
    /** This is the compare operator for TJammerDisguise.
     *  @param JammerDisguise the TJammerDisguise object which shall be
     *                        compared with "*this"
     *  @return @c true if the TJammerDisguise objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TJammerDisguise& JammerDisguise ) const;
    /** This is the assignment operator for TJammerDisguise.                   */
    virtual TJammerDisguise& operator=(const TJammerDisguise& JammerDisguise);
};



/** @class TJammerCloak
 *  @brief TJammerCloak represents a cloak jammer for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TJammer
 *
 *  The class TJammerCloak is derived from TJammer and and can therefor be put
 *  on a ship. It has a value JamEfficiency (implemented in TJammer) and get
 *  and set methods for it. A cloak jammer is a jammer which tries to
 *  cloak the ship. But the efficiency value and which effects it exactly has
 *  is decided by the rule set/battle engine and of no direct concern to the
 *  class TJammerCloak.                                                        */
class TJammerCloak : public TJammer
{
  public:
    /** This constructor generates a new TJammerCloak object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TJammerCloak();
    /** This constructor creates also a new cloak jammer, but its
     *  attributes are copied from the TJammerCloak object given in
     *  OldJammerCloak. This method is mostly implemented to provide a
     *  copy constructor.
     *  @param OldJammerCloak the cloak jammer which shall be copied           */
    TJammerCloak( const TJammerCloak& OldJammerCloak );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TJammerCloak();
    /** The method Load loads a TJammerCloak object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TJammerCloak object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getJammerType you can get the type of the jammer, in
     *  this case TJammer::CLOAK.
     *  @return TJammer::CLOAK                                                 */
    virtual TJammer::tJammerType getJammerType() const;
    /** This is the compare operator for TJammerCloak.
     *  @param JammerCloak the TJammerCloak object which shall be
     *                     compared with "*this"
     *  @return @c true if the TJammerCloak objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TJammerCloak& JammerCloak ) const;
    /** This is the assignment operator for TJammerCloak.                      */
    virtual TJammerCloak& operator=(const TJammerCloak& JammerCloak);
};



/** @class TJammerAntiPenetrate
 *  @brief TJammerAntiPenetrate represents an anti penetrate jammer for ships.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TJammer
 *
 *  The class TJammerAntiPenetrate is derived from TJammer and and can
 *  therefor be put on a ship. It has a value JamEfficiency (implemented in
 *  TJammer) and get and set methods for it. An anti penetrate jammer is a
 *  jammer which tries to prevent the enemy from "seeing" inside the ship. But
 *  the efficiency value and which effects it exactly has is decided by the
 *  rule set/battle engine and of no direct concern to the class
 *  TJammerAntiPenetrate.                                                      */
class TJammerAntiPenetrate : public TJammer
{
  public:
    /** This constructor generates a new TJammerAntiPenetrate object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective
     *  set<something> methods.                                                */
    TJammerAntiPenetrate();
    /** This constructor creates also a new anti penetrate jammer, but its
     *  attributes are copied from the TJammerAntiPenetrate object given in
     *  OldJammerAntiPenetrate. This method is mostly implemented to provide
     *  a copy constructor.
     *  @param OldJammerAntiPenetrate the anti penetrate jammer to be copied   */
    TJammerAntiPenetrate( const TJammerAntiPenetrate& OldJammerAntiPenetrate );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TJammerAntiPenetrate();
    /** The method Load loads a TJammerAntiPenetrate object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TJammerAntiPenetrate object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** With the method getJammerType you can get the type of the jammer, in
     *  this case TJammer::ANTIPENETRATE.
     *  @return TJammer::ANTIPENETRATE                                         */
    virtual TJammer::tJammerType getJammerType() const;
    /** This is the compare operator for TJammerAntiPenetrate.
     *  @param JammerAntiPenetrate the TJammerAntiPenetrate object which shall be
     *                             compared with "*this"
     *  @return @c true if the TJammerAntiPenetrate objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TJammerAntiPenetrate& JammerAntiPenetrate ) const;
    /** This is the assignment operator for TJammerAntiPenetrate.              */
    virtual TJammerAntiPenetrate& operator=(const TJammerAntiPenetrate& JammerAntiPenetrate);
};



/****************************** class TMineLayer *******************************/



/** @class TMineLayer
 *  @brief TMineLayer represents a mine laying facility for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TMineLayer is derived from TItem and can therefore be put on a
 *  ship design. TMineLayer represents a mine laying facility for a ship. As
 *  all other items it has mass, volume and surface area. Besides that it knows
 *  its rate of mine laying. How this value is interpreted exactly is up to the
 *  rule set/battle engine and of no direct concern to the TMineLayer item
 *  class.
 *  FIXME, in future it could be decided that the volume/space in which mines
 *  can be layed is also important and that certain mine layer items are
 *  restricted to mines of a certain type. These informations would then have
 *  to be added to this class.                                                 */
class TMineLayer : public TItem
{
  public:
    /** This constructor generates a new TMineLayer object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TMineLayer();
    /** This constructor creates also a new mine laying facility, but its
     *  attributes are copied from the TMineLayer object given in OldMineLayer.
     *  This method is mostly implemented to provide a copy constructor.
     *  @param OldMineLayer the TMineLayer object which shall be copied        */
    TMineLayer( const TMineLayer& OldMineLayer );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TMineLayer();
    /** The method Load loads a TMineLayer object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TMineLayer object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::MINELAYER for mine laying device.
     *  @return TItem::MINELAYER                                               */
    virtual TItem::tItemType getItemType() const;
    /** The method setMineLayingRate sets the rate of mine laying of the mine
     *  laying device.
     *  @param MineLayingRate the device's new mine laying rate                */
    virtual void setMineLayingRate( const int2 MineLayingRate );
    /** With the method getMineLayingRate you can get the mine laying rate of
     *  the mine laying facility.
     *  @return the device's mine laying rate                                  */
    virtual int2 getMineLayingRate() const;
    /** With the method operator== you can compare two TMineLayer objects.
     *  This is of course the behaviour one would expect from "operator==".
     *  @param MineLayer the TMineLayer object which shall be compared with
     *                   "*this"
     *  @return @c true if TMineLayer objects are equal, @c false if not    */
    virtual bool operator==( const TMineLayer& MineLayer ) const;
    /** This is the assignment operator for TMineLayer.                        */
    virtual TMineLayer& operator=( const TMineLayer& MineLayer );
  protected:
    /** the mine laying facility's mine laying rate                            */
    int2 fMineLayingRate;
};



/****************************** class TMiningBot *******************************/



/** @class TMiningBot
 *  @brief TMiningBot represents a mineral mining facility for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TMiningBot is derived from TItem and can therefore be put on a
 *  ship design. TMiningBot represents a mineral mining facility for a ship. As
 *  all other items it has mass, volume and surface area. Besides that it knows
 *  its mineral mining rate. How this value is interpreted exactly is up to the
 *  rule set and of no direct concern to the TMiningBot item class.
 *  FIXME, in future it could be decided that a mining bot has different
 *  efficiencies for different mineral types. These informations would then
 *  have to be added to this class.                                            */
class TMiningBot : public TItem
{
  public:
    /** This constructor generates a new TMiningBot object with all properties
     *  resetted. This means you have to set all properties like name and mass
     *  afterwards with help of the respective set<something> methods.         */
    TMiningBot();
    /** This constructor creates also a mineral mining facility, but its
     *  attributes are copied from the TMiningBot object given in OldMiningBot.
     *  This method is mostly implemented to provide a copy constructor.
     *  @param OldMiningBot the TMiningBot object which shall be copied        */
    TMiningBot( const TMiningBot& OldMiningBot );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TMiningBot();
    /** The method Load loads a TMiningBot object from the data packages in
     *  the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TMiningBot object by adding the data packages
     *  to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::MININGBOT for mineral mining device.
     *  @return TItem::MININGBOT                                               */
    virtual TItem::tItemType getItemType() const;
    /** The method setMiningRate sets the mineral mining rate of the mineral
     *  mining device.
     *  @param MiningRate the mining device's new mineral mining rate          */
    virtual void setMiningRate( const int2 MiningRate );
    /** With the method getMiningRate you can get the mineral mining rate of
     *  the mineral mining facility.
     *  @return the mining device's mineral mining rate                        */
    virtual int2 getMiningRate() const;
    /** With the method operator== you can compare two TMiningBot objects.
     *  This is of course the behaviour one would expect from "operator==".
     *  @param MiningBot the TMiningBot object which shall be compared with
     *                   "*this"
     *  @return @c true if TMiningBot objects are equal, @c false if not       */
    virtual bool operator==( const TMiningBot& MiningBot ) const;
    /** This is the assignment operator for TMiningBot.                        */
    virtual TMiningBot& operator=( const TMiningBot& MiningBot );
  protected:
    /** the mineral mining facility's mineral mining rate                      */
    int2 fMiningRate;
};



/*************************** class TFighterLauncher ****************************/



/** @class TFighterLauncher
 *  @brief TFighterLauncher represents a fighter bay/launcher for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TFighterLauncher is derived from TItem and can therefore be put
 *  on a ship design. TFighterLauncher represents the fighter launcher and
 *  repair bay for a ship. As all other items it has mass, volume and a surface
 *  area. Besides that it has a rate of launching for fighter, a rate of
 *  landing of fighter and a rate of repairing fighters. How these values are
 *  interpreted exactly is up to the rule set/battle engine and of no direct
 *  concern to the TFighterLauncher item class.
 *  FIXME, in future it could be decided that fighter bay/launcher can only
 *  launch fighter of a certain type. This information would then have to be
 *  added to this class.                                                       */
class TFighterLauncher : public TItem
{
  public:
    /** This constructor generates a new TFighterLauncher object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective set<something>
     *  methods.                                                               */
    TFighterLauncher();
    /** This constructor creates also a fighter launcher/bay, but its
     *  attributes are copied from the TFighterLauncher object given in
     *  OldFighterLauncher. This method is mostly implemented to provide a
     *  copy constructor.
     *  @param OldFighterLauncher the TFighterLauncher object to be copied     */
    TFighterLauncher( const TFighterLauncher& OldFighterLauncher );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TFighterLauncher();
    /** The method Load loads a TFighterLauncher object from the data packages
     *  in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TFighterLauncher object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::FIGHTERLAUNCHER for fighter bay/launcher.
     *  @return TItem::FIGHTERLAUNCHER                                         */
    virtual TItem::tItemType getItemType() const;
    /** The method setLaunchRate sets the fighter launching rate of the
     *  fighter bay.
     *  @param LaunchRate the fighter bay's new fighter launching rate         */
    virtual void setLaunchRate( const int2 LaunchRate );
    /** With the method getLaunchRate you can get the fighter launching rate
     *  of the fighter bay.
     *  @return the fighter bay's fighter launching rate                       */
    virtual int2 getLaunchRate() const;
    /** The method setLandingRate sets the fighter landing rate of the
     *  fighter bay.
     *  @param LandingRate the fighter bay's new fighter landing rate          */
    virtual void setLandingRate( const int2 LandingRate );
    /** With the method getLandingRate you can get the fighter landing rate
     *  of the fighter bay.
     *  @return the fighter bay's fighter landing rate                         */
    virtual int2 getLandingRate() const;
    /** The method setRepairRate sets the fighter repair rate of the fighter
     *  bay.
     *  @param RepairRate the fighter bay's new fighter repair rate            */
    virtual void setRepairRate( const int2 RepairRate );
    /** With the method getRepairRate you can get the fighter repair rate of
     *  the fighter bay.
     *  @return the fighter bay's fighter repair rate                          */
    virtual int2 getRepairRate() const;
    /** With the method operator== you can compare two TFighterLauncher
     *  objects. This is of course the expected behaviour of "operator==".
     *  @param FighterLauncher the TFighterLauncher object which shall be
     *                         compared with "*this"
     *  @return @c true if the TFighterLauncher objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TFighterLauncher& FighterLauncher ) const;
    /** This is the assignment operator for TFighterLauncher.                  */
    virtual TFighterLauncher& operator=( const TFighterLauncher& FighterLauncher );
  protected:
    /** the fighter bay's fighter launching rate                               */
    int2 fLaunchRate;
    /** the fighter bay's fighter landing rate                                 */
    int2 fLandingRate;
    /** the fighter bay's fighter repair rate                                  */
    int2 fRepairRate;
};



/*************************** class TSPWeaponLauncher ****************************/



/** @class TSPWeaponLauncher
 *  @brief TSPWeaponLauncher represents a SP weapon launcher for a ship.
 *  @author Ralf Laue
 *  @version $Id: item.h,v 1.34 2002/04/02 22:33:08 prolator Exp $
 *  @see TShipDesign
 *
 *  The class TSPWeaponLauncher is derived from TItem and can therefore be put
 *  on a ship design. TSPWeaponLauncher represents a SP weapon launcher for a
 *  ship. As all other items it has mass, volume and a surface area. Besides
 *  that it has also a rate of launching for SP weapons. How this value is
 *  interpreted exactly is up to the rule set/battle engine and of no direct
 *  concern to the TSPWeaponLauncher item class.
 *  FIXME, in future it could be decided that SP weapon launcher can only
 *  launch SP weapons of a certain type. This information would then have to
 *  be added to this class.                                                    */
class TSPWeaponLauncher : public TItem
{
  public:
    /** This constructor generates a new TSPWeaponLauncher object with all
     *  properties resetted. This means you have to set all properties like
     *  name and mass afterwards with help of the respective set<something>
     *  methods.                                                               */
    TSPWeaponLauncher();
    /** This constructor creates also a SP weapon launcher, but its attributes
     *  are copied from the TSPWeaponLauncher object given in
     *  OldSPWeaponLauncher. This method is mostly implemented to provide a
     *  copy constructor.
     *  @param OldSPWeaponLauncher the TSPWeaponLauncher object to be copied   */
    TSPWeaponLauncher( const TSPWeaponLauncher& OldSPWeaponLauncher );
    /** Destructs the object. Has nothing else to do, because no memory has
     *  to be freed or similar stuff.                                          */
    virtual ~TSPWeaponLauncher();
    /** The method Load loads a TSPWeaponLauncher object from the data
     *  packages in the list.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TSPWeaponLauncher object by adding the data
     *  packages to the list.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;
    /** The method getItemType returns the type of the item, in this case
     *  TItem::SPWEAPONLAUNCHER for SP weapon launcher.
     *  @return TItem::SPWEAPONLAUNCHER                                        */
    virtual TItem::tItemType getItemType() const;
    /** The method setLaunchRate sets the launching rate of the SP weapon
     *  launcher.
     *  @param LaunchRate the SP weapon launcher's new launching rate          */
    virtual void setLaunchRate( const int2 LaunchRate );
    /** With the method getLaunchRate you can get the launching rate if the
     *  SP weapon launcher.
     *  @return the SP weapon launcher's launching rate                        */
    virtual int2 getLaunchRate() const;
    /** With the method operator== you can compare two TSPWeaponLauncher
     *  objects. This is of course the expected behaviour of "operator==".
     *  @param SPWeaponLauncher the TSPWeaponLauncher object which shall be
     *                          compared with "*this"
     *  @return @c true if the TSPWeaponLauncher objects are equal and
     *          @c false if not                                                */
    virtual bool operator==( const TSPWeaponLauncher& SPWeaponLauncher ) const;
    /** This is the assignment operator for TSPWeaponLauncher.                 */
    virtual TSPWeaponLauncher& operator=( const TSPWeaponLauncher& SPWeaponLauncher );
  protected:
    /** the SP weapon launcher's SP weapon launching rate                      */
    int2 fLaunchRate;
};


 

#endif        // __ITEM_INCLUDED



