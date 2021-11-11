
// $Id: subfleet.cpp,v 1.14 2002/06/28 10:12:07 mkrohn5 Exp $
//
// subfleet Code File
// Written by: Marco Krohn
//             Ralf Laue
//
// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
//                        Ralf Laue <ralf.laue@gmx.de>
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

#include "gamelogic/fleet.h"
#include "gamelogic/subfleet.h"
#include "gamelogic/shipdesign.h"



/****************************** class TSubFleet ********************************/



TSubFleet:: TSubFleet( TShipDesign* ShipDesign, int2 NumberOfShips )
  : TActionObject(),
    fFleet(),
    fShipDesign(),
    fUpgradeDesign()
{
  LOG("TSubFleet","TSubFleet") << "subfleet created." << endl;
  fShipDesign.setDest( ShipDesign );              // set link to new ship design
  if ( fShipDesign.isNull() )         // if ShipDesign pointed to NULL --> error
    Fatal( "TSubFleet", "Constructor", "Couldn't set link to ship design!");
  fNumberOfShips = NumberOfShips;                 // set initial number of ships
  if ( fNumberOfShips <= 0 )                       // if 0 or negative --> error
    Fatal( "TSubFleet", "Constructor", "Number of ships can't become <= 0!" );
  fExperience = 0;                                           // reset experience
  fAutoRetire = false;      // reset auto retire (subfleet shall not be retired)
} // constructor



TSubFleet::TSubFleet( TSubFleet& OldSubFleet )
  : TActionObject(),
    fFleet(),
    fShipDesign()
{
  *this = OldSubFleet;            // assign all fields/properties with operator=
} // copy constructor



// virtual destructor
TSubFleet :: ~TSubFleet()
{
  LOG("TSubFleet","~TSubFleet") << "destructing a subfleet" << endl;
}



int2 TSubFleet::getType() const
{
  return TType::SUBFLEET;
} // getType



const string& TSubFleet::getTypeName() const
{
  static const string typeName = "TSubFleet";   // make string & keep it(static)
  return typeName;                         // return the name of the object type
} // getTypeName



const TFleet* TSubFleet::getFleet() const
{
  return fFleet.getPointerToDest();     // return fleet the sub fleet belongs to
} // getFleet


       
const TShipDesign* TSubFleet::getShipDesign() const
{
  return fShipDesign.getPointerToDest();   // return ship design of the subfleet
} // getShipDesign



// virtual
void TSubFleet::AddShips( int4 NumberOfShips )
{
  fNumberOfShips += NumberOfShips;                  // add ships to the subfleet
} //AddShips



// virtual
void TSubFleet::SubstractShips( int4 NumberOfShips )
{
  if (NumberOfShips >= fNumberOfShips)     // if number of ships in the subfleet
  {                                      // would become 0 or negative --> error
    Fatal( "TSubFleet", "SubstractShips", "Number of ships can't become <= 0!" );
  }
  else                                                                   // else
    fNumberOfShips += NumberOfShips;        // substract ships from the subfleet
} // SubstractShips



int4 TSubFleet::getNumberOfShips() const
{
  return fNumberOfShips;           // return the number of ships in the subfleet
} // getShipAmount



void TSubFleet::setAutoUpgrade( TShipDesign* UpgradeDesign )
{
  fUpgradeDesign.setDest( UpgradeDesign );     // set link to new upgrade design
  if ( fUpgradeDesign.isNull() )   // if UpgradeDesign pointed to NULL --> error
    Fatal( "TSubFleet", "SetAutoUpgrade", "Couldn't set link to upgrade design!");
} // setAutoUpgrade



TShipDesign* TSubFleet::getUpgradeDesign() const
{
  return fUpgradeDesign.getPointerToDest();  // return pointer to upgrade design
} // getUpgradeDesign



void TSubFleet::CancelAutoUpgrade()
{
  fUpgradeDesign.setNull();                  // delete pointer to upgrade design
} // CancelAutoUpgrade



bool TSubFleet::CommitAutoUpgrade()
{
  if ( fUpgradeDesign.isValid() )                       // if upgrade is planned
  {
    fShipDesign.setDest(fUpgradeDesign.getPointerToDest());    // set new design

    //  HERE: calculate all needed values new

    fUpgradeDesign.setNull();                // delete pointer to upgrade design
    return true;                               // upgrade committed: return true
  } else
    return false;                          // no upgrade committed: return false
} // CommitAutoUpgrade



void TSubFleet::setAutoRetire()
{
  fAutoRetire = true;                 // set flag: the subfleet is to be retired
} // setAutoRetire



void TSubFleet::CancelAutoRetire()
{
  fAutoRetire = false;         // delete flag: the subfleet is not to be retired
} // CancelAutoRetire



bool TSubFleet::IsAutoRetire() const
{                 // return the flag which determines whether the subfleet is to
  return fAutoRetire;                      // be retired at the next opportunity
} // IsAutoRetire



void TSubFleet::setExperience( int4 Experience )
{
  fExperience = Experience;                  // set the new amount of experience
} // setExperience



int4 TSubFleet::getExperience() const
{
  return fExperience;                         // return the amount of experience
} // getExperience



int4 TSubFleet::getMaxHullHP() const
{                                       // return maximum hit points of subfleet
  return ( fShipDesign->getMaxHullHP() * fNumberOfShips );
} // getMaxHullHP



int4 TSubFleet::getMaxArmorHP() const
{
  int2 ArmorHP = 0;        // initialize variable to sum up the armor hit points
  TPList<TItemPack>* ArmorList = new TPList<TItemPack>();// list for armor items 
  TPList<TItemPack>::const_iterator iter;   // const iterator for the armor list

  fShipDesign->getItemList( ArmorList, TItem::ARMOR );    // get all armor items
  for( iter = ArmorList->begin(); iter != ArmorList->end(); ++ iter )
  {   // with all armor items do: multiply amount of hit points with item amount
    ArmorHP += ((TArmor*) (*iter)->getItem())->getHitPoints()
      * (*iter)->getItemAmount();                               // and sum it up
  } // for
  ArmorHP *= fNumberOfShips;            // finally multiply with number of ships

  ArmorList->setAutoDeleteMode( true );                           // cleaning up
  delete ArmorList;
  return ArmorHP;                                       // and return this value
} // getMaxArmorHP



int4 TSubFleet::getMaxShieldHP() const
{
  int2 ShieldHP = 0;      // initialize variable to sum up the shield hit points
  TPList<TItemPack>* ShieldList = new TPList<TItemPack>();   // list for shields
  TPList<TItemPack>::const_iterator iter;  // const iterator for the shield list

  fShipDesign->getItemList( ShieldList, TItem::SHIELD ); // get all shield items
  for( iter = ShieldList->begin(); iter != ShieldList->end(); ++ iter )
  {  // with all shield items do: multiply amount of hit points with item amount
    ShieldHP += ((TShield*) ((*iter)->getItem()))->getHitPoints()
      * (*iter)->getItemAmount();                               // and sum it up
    } // for
  ShieldHP *= fNumberOfShips;           // finally multiply with number of ships

  ShieldList->setAutoDeleteMode( true );                          // cleaning up
  delete ShieldList;
  return ShieldHP;                                      // and return this value
} // getMaxShieldHP



int4 TSubFleet::getCargoSpace() const
{                            // remember 1 cargo bay item == 1 m³ of cargo space
  int2 CargoSpace = 0;              // initialize variable to sum up cargo space
  TPList<TItemPack>* CargoList = new TPList<TItemPack>;//list for the cargo bays
  TPList<TItemPack>::const_iterator iter;   // const iterator for the cargo list
    
  fShipDesign->getItemList( CargoList, TItem::CARGOBAY ); // get all cargo items
  for( iter = CargoList->begin(); iter != CargoList->end(); ++ iter )
    CargoSpace += (*iter)->getItemAmount();  // sum up amount of cargo bay items
  CargoSpace *= fNumberOfShips;     // subfleet cargo space: mulitply with ships

  CargoList->setAutoDeleteMode( true );                           // cleaning up
  delete CargoList;
  return CargoSpace;                            // return sum of cargo bay space
} // getCargoSpace



int2 TSubFleet::getMiningRate() const
{
  int2 MiningRate = 0;              // initialize variable to sum up mining rate
  TPList<TItemPack>* MiningList = new TPList<TItemPack>; // list for mining bots
  TPList<TItemPack>::const_iterator iter;  // const iterator for the mining list

  fShipDesign->getItemList( MiningList, TItem::MININGBOT );  
  for( iter = MiningList->begin(); iter != MiningList->end(); ++ iter )
  {       // with all mining bots: sum up mining rates of different mining items
    MiningRate += ((TMiningBot*) ((*iter)->getItem()))->getMiningRate()
      * (*iter)->getItemAmount();   // multiply mining rate with number of items
  } // for
  MiningRate *= fNumberOfShips; // multiply mining rate with the number of ships

  MiningList->setAutoDeleteMode( true );                          // cleaning up
  delete MiningList;
  return MiningRate;                        // return the calculated mining rate
} // getMiningRate



// virtual method
bool TSubFleet::load( TDataPackageList* in )
{
  bool bReturn = true;

  bReturn &= TActionObject::load( in );                       // call the parent
  bReturn &= fFleet.load( in, "parent_fleet", true );   // load the parent fleet
  fFleet->Add( this );                         // tell parent about new subfleet
  bReturn &= fShipDesign.load( in, "ship_design", true );     // load the design
  bReturn &= fUpgradeDesign.load( in, "upgrade_ design", true ); // load upgrade
  bReturn &= in->getAndDelete( "number_of_ships", &fNumberOfShips ); 
  bReturn &= in->getAndDelete( "experience", &fExperience, true );  
  bReturn &= in->getAndDelete( "autoretire", &fAutoRetire, true );  
  return bReturn;                                
} // load



// virtual method
bool TSubFleet::save( TDataPackageList* out ) const
{
bool bReturn = true;
static const string sBlockType = "subfleet";

  // additional information to write a block (this data will not be
  // read by the load method)
  bReturn &= out->add( "blocktype", &sBlockType, true, false );

  bReturn &= TActionObject::save( out );                      // call the parent
  bReturn &= fFleet.save( out, "parent_fleet", true );  // save the parent fleet
  bReturn &= fShipDesign.save( out, "ship_design", true );    // save the design
  bReturn &= fUpgradeDesign.save( out, "upgrade_ design", true );// save upgrade
  bReturn &= out->add( "number_of_ships", &fNumberOfShips, true, false ); // and
  bReturn &= out->add( "experience", &fExperience, true, false );     // rest of 
  bReturn &= out->add( "autoretire", &fAutoRetire, true, false );      // fields
  return bReturn;                                 // return the bool for success
}



// protected
void TSubFleet::setFleet( TFleet* NewFleet )
{
  fFleet.setDest( NewFleet );          // set the fleet the sub fleet belongs to
  if ( !fFleet.isValid() )         // if pointer to new parent fleet is no valid
    Fatal( "TSubFleet", "SetFleet", "Couldn't set link to parent fleet!");
} // setFleet



// virtual
TSubFleet& TSubFleet::operator=( const TSubFleet& SubFleet )
{
  if ( this != &SubFleet )                     // if both items are not the same
  {
    if ( fFleet.isValid() )               // if link to fleet is valid --> error
      Fatal( "TSubFleet", "operator=", "Tried to remove subfleet without telling parent fleet!");
    //    TActionObject::operator=( SubFleet );  // copy fields inherited from TActObj
    fFleet.setNull();// set fleet to 0
    fShipDesign = SubFleet.fShipDesign;                 // copy all local fields
    fUpgradeDesign = SubFleet.fUpgradeDesign;
    fNumberOfShips = SubFleet.fNumberOfShips;
    fExperience = SubFleet.fExperience;
    fAutoRetire = SubFleet.fAutoRetire;
  } // if
  return *this;                                                 // return object
} // operator=



/*
 * $Log: subfleet.cpp,v $
 * Revision 1.14  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.13  2002/04/02 22:33:45  prolator
 * some Xet to xet
 *
 * Revision 1.12  2002/03/24 13:33:53  mkrohn5
 * started some work on ship design:
 * major change is that a shipdesign automatically detects if there is a subfleet out there that uses exactly this design (not yet complete)
 *
 * Revision 1.11  2002/01/28 01:07:46  mkrohn5
 * fix of method name (lowercase) and bugfix in load method
 *
 * Revision 1.10  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.9  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.8  2001/06/23 23:27:36  prolator
 * changed way to set the number of ships
 *
 * Revision 1.7  2001/06/23 19:55:21  prolator
 * added Load and Save
 *
 * Revision 1.6  2001/06/21 21:50:21  prolator
 * adjusted to TPList<TItemPack> (new implementation in TShipDesign)
 *
 * Revision 1.5  2001/06/21 11:27:50  mkrohn5
 * added debug output
 *
 * Revision 1.4  2001/06/17 22:38:43  prolator
 * added more methods
 *
 * Revision 1.3  2001/06/16 21:37:09  prolator
 * added getCargo and getLongScannerRange; adjusted to counter of subfleets in ship design
 *
 * Revision 1.2  2001/06/14 14:14:41  prolator
 * added experience, link to ship design and implmented number of ships
 *
 * Revision 1.1  2001/05/10 23:10:53  mkrohn5
 * basic framework for subfleets
 *
 */
