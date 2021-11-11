// $Id: shipdesign.cpp,v 1.26 2002/06/28 10:12:07 mkrohn5 Exp $
//
// Ship Design Code File
// Written by: Ralf Laue, <ralf.laue@gmx.de>
//
// Copyright (C) 2001, Ralf Laue, <ralf.laue@gmx.de>
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


#include "shipdesign.h"
#include "common/datapackage.h"
#include "common/plist.h"



/***************************** class TShipDesign *******************************/

TShipDesign::TShipDesign()
  : TLinkable(),
    fDesignName(""),
    fHullCost(),
    fEquipment()
{
//  fSubfleets = 0;       // reset the number of existing subfleets if this design
  fAtmospheric = false;                  // normally ships can't land on planets
  fAtmosphericFactor = 0;              // initialized with no no extra hull cost
  fHullMass = 0;                                   // for fDesignName, fHullCost
  fHullVolume = 0;                             // and fEquipment it's done above
  fHullSurface = 0;
  fMaxHullHP = 0;
} // Constructor



TShipDesign::TShipDesign( const TShipDesign& OldDesign )
  : TLinkable()
{
  *this = OldDesign;              // assign all fields/properties with operator=
} // Constructor



TShipDesign::~TShipDesign()
{
  fEquipment.setAutoDeleteMode( true );                  // set auto delete mode
  fEquipment.deleteAll();                               // delete equipment list
} // Deconstructor



int2 TShipDesign::getType() const
{
  return TType::SHIPDESIGN;
} // getType



const string& TShipDesign::getTypeName() const
{
  static const string typeName = "TShipDesign"; // make string & keep it(static)
  return typeName;                         // return the name of the object type
} // getTypeName



int4 TShipDesign::getUsageNumber() const
{
int4 number;

  TLinkBaseList list = getLinkedByList();
  TLinkBaseList::const_iterator it;

  number = 0;
  for ( it=list.begin(); it!=list.end(); it++ )  {
    if ( (*it)->getDestType() == TType::SUBFLEET )  number++;
  }

  return number;
}



bool TShipDesign::isChangeable() const
{
  if ( getUsageNumber() == 0 )  return true;
  return false;                                            // some subfleets still use this design
}



void TShipDesign::AbleToLand( bool CanLand )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fAtmospheric = CanLand;                     // set new value @c fAtmospheric
} // AbleToLand



bool TShipDesign::isAtmospheric() const
{
  return fAtmospheric;               // return value of the flag @c fAtmospheric
} // isAtmospheric



void  TShipDesign::setAtmosphericFactor( double Factor )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fAtmosphericFactor = Factor;           // set new value for hull cost factor
} //  setAtmosphericFactor



double TShipDesign::getAtmosphericFactor() const
{
  return fAtmosphericFactor;                          // return hull cost factor
} //  getAtmosphericFactor



void TShipDesign::setDesignName( const string& Name )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fDesignName = Name;                  // set the new name for the ship design
} // setName



const string& TShipDesign::getDesignName() const
{
  return fDesignName;                      // return the name of the ship design
} // getName



void TShipDesign::setHullMass( const int4 Mass )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fHullMass = Mass;                        // set new mass for the ship design
} // setHullMass



int4 TShipDesign::getHullMass() const
{
  return fHullMass;                        // return teh mass of the ship design
} // getHullMass



int4 TShipDesign::getTotalMass() const
{
  TPList<TItemPack>::const_iterator iter;// const iterator through the equipment
  int4 massDummy = fHullMass;                  // variable to calculate the mass

  for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
  {                                 // iterate through the whole fEquipment list
                          // and add each item's mass to the already summed mass
    massDummy += (*iter)->getItemAmount() * (*iter)->getItem()->getMass();
  } // for
  
  return massDummy;                      // return total mass of the ship design
} // getTotalMass



void TShipDesign::setHullVolume( const int2 Volume )
{
if ( getUsageNumber() == 0 )             // if no ship of this design exists
    fHullVolume = Volume;                  // set new volume for the ship design
} // setVolume



int2 TShipDesign::getHullVolume() const
{
  return fHullVolume;                        // return volume of the ship design
} // getHullVolume



int2 TShipDesign::getFreeVolume() const
{
  TPList<TItemPack>::const_iterator iter;// const iterator through the equipment
  int2 volumeDummy = fHullVolume;        // variable to caculate the free volume

  for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
  {                                 // iterate through the whole fEquipment list
             // and substract each item's volume need from the still free volume
    volumeDummy -= (*iter)->getItemAmount() * (*iter)->getItem()->getVolume();
  } // for
  
  return volumeDummy;                                      // return free volume
} // getFreeVolume



void TShipDesign::setHullSurface( const int2 Surface )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fHullSurface = Surface;          // set new surface area for the ship design
} // setSurface



int2 TShipDesign::getHullSurface() const
{
  return fHullSurface;                //  return surface area of the ship design
} // getHullSurface



int2 TShipDesign::getFreeSurface() const
{
  TPList<TItemPack>::const_iterator iter;// const iterator through the equipment
  int2 surfaceDummy = fHullSurface;     // variable to caculate the free surface

  for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
  {                                 // iterate through the whole fEquipment list
           // and substract each item's surface need from the still free surface
    surfaceDummy -= (*iter)->getItemAmount() * (*iter)->getItem()->getSurface();
  } // for
  
  return surfaceDummy;                                    // return free surface
} // getFreeSurface



void TShipDesign::setHullCost( const TSubstanceSet& HullCost )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fHullCost = HullCost;         // set the new cost for the hull of the design
} // setHullCost


void TShipDesign::getHullCost( TSubstanceSet* ReturnCost ) const
{
  int2 numerator = 1000;          // reset numerator (same value as denominator)

  ReturnCost->Clear();                                 // empty the return value
  if ( fAtmospheric )                             // if ship can land on planets
    numerator += ((int2) (fAtmosphericFactor * 1000));// add factor to numerator

  ReturnCost->Add( fHullCost, numerator, 1000 );  // assign cost to return value
} // getHullCost



void TShipDesign::getDesignCost( TSubstanceSet* ReturnCost ) const
{
  TPList<TItemPack>::const_iterator iter;// const iterator through the equipment
  TSubstanceSet dummySubstanceSet;

  getHullCost( ReturnCost );                           // get cost of empty hull
  for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
  {                             // iterate through the whole fEquipment list and
    (*iter)->getItem()->getCost( &dummySubstanceSet ); // sum up costs for items
    ReturnCost->Add( dummySubstanceSet, (*iter)->getItemAmount() );
  } // for
} // getDesignCost



void TShipDesign::setMaxHullHP( const int2 HitPoints )
{
  if ( getUsageNumber() == 0 )              // if no ship of this design exists
    fMaxHullHP = HitPoints;         // set new amount of hit points for the hull
} // setMaxHullHP



int2 TShipDesign::getMaxHullHP() const
{
  return fMaxHullHP;                   //  return maximum hit points of the hull
} // getMaxHullHP



// default value for AddAmount = 1
int2 TShipDesign::AddItem( TItem* Item, const int2 AddAmount )
{
  if ( (getUsageNumber() == 0) && (AddAmount != 0) ) // if no ship of design exists
  {                                // AND AddAmount > 0 --> try to add the items
    TPList<TItemPack>::iterator iter;          // iterator through the equipment
                             // calculate how many items still fit on the design
    int2 mountCount = AddAmount;            // assume all items can be installed
    if (( Item->getSurface() == 0) && ( Item->getVolume() != 0 ))
    {                                           // if item needs no surface area
      if ( getFreeVolume() / Item->getVolume() < AddAmount )
      {              // check whether the volume is limiting the number of items
        mountCount = getFreeVolume() / Item->getVolume();
      } // if
    } else
      if (( Item->getSurface() != 0) && ( Item->getVolume() == 0 ))
      {                                               // if item needs no volume
        if ( getFreeVolume() / Item->getVolume() < AddAmount )
        {      // check whether the surface area is limiting the number of items
          mountCount = getFreeSurface() / Item->getSurface();
        } // if
      } else
        if  (( Item->getSurface() != 0) && ( Item->getVolume() == 0 ))
        {                               // if item needs both volume and surface
          if ( getFreeSurface() / Item->getSurface() < mountCount)        // set
            mountCount = getFreeSurface() / Item->getSurface();    // mountCount
          if ( getFreeVolume() / Item->getVolume() < mountCount)  // to smallest
            mountCount = getFreeVolume() / Item->getVolume(); // number possible
        } // if
          
    for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
    {                               // iterate through the whole fEquipment list
      if ( (*iter)->getItem() == Item )                // if you find equal item
      {                                              // add mountCount to design
        (*iter)->setItemAmount( (*iter)->getItemAmount() + mountCount);
        return mountCount;             // and return the number of mounted items
      } // if
    } // for
                                      // if no items of this type were installed
    TItemPack* dummyPack = new TItemPack();              // create new TItemPack 
    dummyPack->setItem( Item );         // save its item type (link to the item)
    dummyPack->setItemAmount( AddAmount );                    // save its amount 
    fEquipment.add( dummyPack );          // put it into the equipment container
    return mountCount;                 // and return the number of mounted items
  } else {
    return 0;    // if ships of this design exist OR AddAmount = 0 THEN return 0
  } // if ( (fSubfleets == 0) && (AddAmount != 0) )
} // AddItem



// default value for RemoveAmount = 1
int2 TShipDesign::RemoveItem( TItem *Item, const int2 RemoveAmount)
{
  if ( (getUsageNumber() == 0) && (RemoveAmount != 0) ) // if no ship of design exists
  {                      // AND amount to remove > 0 --> try to remove the items
    TPList<TItemPack>::iterator iter;          // iterator through the equipment
    
    for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
    {                               // iterate through the whole fEquipment list
      if ( (*iter)->getItem() == Item )        // if you find an equal item type
      {
        int2 mountedAmount = (*iter)->getItemAmount(); // get the mounted amount
        if ( mountedAmount > RemoveAmount )      // check whether more items are
        {         // mounted than should be removed: if yes, remove asked amount
          (*iter)->setItemAmount( mountedAmount -= RemoveAmount );
          return RemoveAmount;             // and return amount of removed items
        } else {                                                       // if not
          fEquipment.setAutoDeleteMode( true );          // set auto delete mode
          fEquipment.remove( *iter );                // remove the pack complete
          return mountedAmount;            // and return amount of removed items
        } // if
      } // if
    } // for
  } // if (fSubfleets == 0) && (RemoveAmount != 0)
      // if item not found OR ships of this design exist OR amount to remove = 0
  return 0;                              //  return number of removed items (=0)
} // RemoveItem



// default value for ItemType = -1 (= 0xFFFF)
void TShipDesign::getItemList( TPList<TItemPack>* ReturnList, const int2 ItemType ) const
{
  TPList<TItemPack>::const_iterator iter;// const iterator through the equipment

  ReturnList->setAutoDeleteMode( true );           // empty return list variable
  ReturnList->deleteAll();
  for ( iter = fEquipment.begin() ; iter != fEquipment.end(); ++iter )
  {                                 // iterate through the whole fEquipment list
    if ( ((*iter)->getItem()->getItemType() & ItemType) != 0 )// if item has the
    {                                                            // desired type
      TItemPack* dummyPack = new TItemPack( *(*iter) ); // create a copy of pack
      ReturnList->add( dummyPack );                     // add it to return list
    } // if
  } // for
} // getItemList



bool TShipDesign::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TLinkable::load( in );// load parent's data and all local fields
  ReturnBool &= in->getAndDelete( "design_name", &fDesignName, true );
  ReturnBool &= in->getAndDelete( "atmospheric_flag", &fAtmospheric, true );
  ReturnBool &= in->getAndDelete( "atmospheric_factor", &fAtmosphericFactor, true );
  ReturnBool &= in->getAndDelete( "hull_mass", &fHullMass, true );
  ReturnBool &= in->getAndDelete( "hull_volume", &fHullVolume, true );
  ReturnBool &= in->getAndDelete( "hull_surface", &fHullSurface, true );
  // load cost FIXME
  ReturnBool &= in->getAndDelete( "max_hull_hp", &fMaxHullHP, true );
  ReturnBool &= fEquipment.load( in, "equipment", true );
  return ReturnBool;                              // return the bool for success
} // load



bool TShipDesign::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  static const string sBlockType = "shipdesign";

  // additional information to write a block (this data will not be
  // read by the load method)
  ReturnBool &= out->add( "blocktype", &sBlockType, true, false );

  
  ReturnBool &= TLinkable::save( out );   // save parent's data and local fields
  ReturnBool &= out->add( "design_name", &fDesignName, true, false );
  ReturnBool &= out->add( "atmospheric_flag", &fAtmospheric, true, false );
  ReturnBool &= out->add( "atmospheric_factor", &fAtmosphericFactor, true, false );
  ReturnBool &= out->add( "hull_mass", &fHullMass, true, false );
  ReturnBool &= out->add( "hull_volume", &fHullVolume, true, false );
  ReturnBool &= out->add( "hull_surface", &fHullSurface, true, false );
  // save cost FIXME
  ReturnBool &= out->add( "max_hull_hp", &fMaxHullHP, true, false );
  ReturnBool &= fEquipment.save( out, "equipment", true );
  return ReturnBool;                              // return the bool for success
} // Save



TShipDesign& TShipDesign::operator=( const TShipDesign& Design )
{
  if ( this != &Design )                // if both ship designs are not the same
  {
    fAtmospheric = Design.fAtmospheric;
    fAtmosphericFactor = Design.fAtmosphericFactor;
    fDesignName = Design.fDesignName;
    fHullMass = Design.fHullMass;
    fHullVolume = Design.fHullVolume;
    fHullSurface = Design.fHullSurface;
    fHullCost = Design.fHullCost;
    fMaxHullHP = Design.fMaxHullHP;
    Design.getItemList( &fEquipment );                         // copy all items
  } // if
  return *this;                                            // return this object
} // operator=



/****************************** class TItemPack ********************************/



TItemPack::TItemPack()
  : fItemLink()
{
  fItemAmount = 0;                                    // reset attributes/values
} // constructor



TItemPack::TItemPack( const TItemPack& OldItemPack )
{
  *this = OldItemPack;            // assign all fields/properties with operator=
} // copy constructor



TItemPack::~TItemPack()
{
                                                      // nothing else to do here
} // deconstructor



void TItemPack::setItem( TItem* Item )
{
  fItemLink.setDest( Item );                        // set link to new item type
} // setItemType



TItem* TItemPack::getItem() const
{
  return fItemLink.getPointerToDest();               // return link to item type
} // getItemType



void TItemPack::setItemAmount( int2 ItemAmount )
{
  fItemAmount = ItemAmount;          // set new amount of items in the item pack
} // setItemAmount



int2 TItemPack::getItemAmount() const
{
  return fItemAmount;                 // return amount of items in the item pack
} // getItemAmount



bool TItemPack::operator==( const TItemPack& ItemPack ) const
{
  return ( fItemAmount == ItemPack.fItemAmount ) && // are amount AND type equal
    ( fItemLink.getPointerToDest() == ItemPack.fItemLink.getPointerToDest() );
} // operator==



TItemPack& TItemPack::operator=( const TItemPack& ItemPack )
{
  if ( this != &ItemPack )                     // if both items are not the same
  {
    fItemAmount = ItemPack.fItemAmount;                         // assign amount
    fItemLink.setDest( ItemPack.fItemLink.getPointerToDest() );   // assign type
  } // if
  return *this;                                                 // return object
} // operator=



// default for bUnique = true
bool TItemPack::load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                     // read the object into the local data list
  ReturnBool &=in->getAndDelete( sIdentifier, dataList, bUnique );
                              // load item amount and type out of the local list
  ReturnBool &= dataList->getAndDelete( "item_amount", (int4*) &fItemAmount, true );
  ReturnBool &= fItemLink.load( dataList, "item_type", true );
  delete dataList;                                  // dispose of the local list
  return ReturnBool;                              // return the bool for success
} // load



// default for bUnique = true
bool TItemPack::save( TDataPackageList* out, const string& sIdentifier, bool bUnique ) const
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                  // save amount and type in the local data list
  ReturnBool &= dataList->add( "item_amount", (int4*) &fItemAmount, true, false );
  ReturnBool &= fItemLink.save( dataList, "item_type", true );
                                // put local data list into "parent's" data list
  ReturnBool &= out->add( sIdentifier, dataList, bUnique, true );
  return ReturnBool;                              // return the bool for success
                   // the global data list will take care of freeing the memeory
} // save



/*
 * $Log: shipdesign.cpp,v $
 * Revision 1.26  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.25  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.24  2002/04/11 21:33:34  prolator
 * removed default values for parameters from .cpp-file
 *
 * Revision 1.23  2002/04/02 22:32:52  prolator
 * some Xet to xet
 *
 * Revision 1.22  2002/03/24 13:33:53  mkrohn5
 * started some work on ship design:
 * major change is that a shipdesign automatically detects if there is a subfleet out there that uses exactly this design (not yet complete)
 *
 * Revision 1.21  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.20  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.19  2001/06/29 01:03:32  mkrohn5
 * Save does now work correctly (blocktype added)
 *
 * Revision 1.18  2001/06/23 00:13:10  prolator
 * added save of equipment in TShipDesign
 *
 * Revision 1.17  2001/06/22 14:55:51  prolator
 * Save and Load use now int2
 *
 * Revision 1.16  2001/06/22 01:07:57  prolator
 * changed implementation in TDefenseType: TPList<TEfficiencyToken>
 *
 * Revision 1.15  2001/06/21 21:38:38  prolator
 * changed the implementation of the equipment lis: now as TPList<TItemPack>
 *
 * Revision 1.14  2001/06/20 15:45:24  prolator
 * first version of method Load and Save added; don't work yet properly!
 *
 * Revision 1.13  2001/06/17 11:09:55  prolator
 * changed interface from damage points (DP) to hit points (HP)
 *
 * Revision 1.12  2001/06/16 21:32:28  prolator
 * changed changeable implementation to counter of subfleets
 *
 * Revision 1.11  2001/06/15 23:30:09  prolator
 * fixed bug, if 0 items were added
 *
 * Revision 1.10  2001/06/14 11:59:08  prolator
 * changed links to items to TLink<TItem> and tItemList to map
 *
 * Revision 1.9  2001/06/13 15:43:04  prolator
 * added flag atmospheric and the related methods
 *
 * Revision 1.8  2001/06/12 21:35:03  prolator
 * cleared a bug in GetDesignCost
 *
 * Revision 1.7  2001/06/12 17:20:41  prolator
 * added comments about default values for AddItem and RemoveItem
 *
 * Revision 1.6  2001/06/11 18:54:43  mkrohn5
 * fixed problems with TLinkable copy constructor
 *
 * Revision 1.5  2001/06/10 17:43:57  prolator
 * mass is now int4 and fixed bug with item volumes or surfaces of 0
 *
 * Revision 1.4  2001/05/21 23:32:06  prolator
 * added code for GetItemList; changed interface for GetHullCost and GetDesignCost; added operator=
 *
 * Revision 1.3  2001/05/19 19:37:43  prolator
 * Added changable flag, changable methods and first version of item list
 *
 * Revision 1.2  2001/05/17 14:23:01  prolator
 * Changed GetType so, that it now returns TType::SHIPDESIGN and not TType::UNKNOWN
 *
 * Revision 1.1  2001/05/17 12:49:53  prolator
 * Code file for TShipDesign
 *
 */


