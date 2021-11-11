// $Id: subfleet_basic.cpp,v 1.7 2002/06/28 10:12:08 mkrohn5 Exp $
//
// subfleet basic rules implementation  Code File
// Written by: Ralf Laue
//
// Copyright (C) 2001 - , Ralf Laue <ralf.laue@gmx.de>
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
#include "gamelogic/modules/subfleet_basic.h"
#include "gamelogic/shipdesign.h"
#include <math.h>


/**************************** class TSubFleetBasic *****************************/



TSubFleetBasic::TSubFleetBasic( TShipDesign* ShipDesign, int2 NumberOfShips )
  : TSubFleet( ShipDesign, NumberOfShips )
{
  fFuel = 0;                                                       // reset Fuel
} // constructor



TSubFleetBasic::TSubFleetBasic( TSubFleetBasic& OldSubFleet )
  : TSubFleet( OldSubFleet )
{
  *this = OldSubFleet;            // assign all fields/properties with operator=
} // copy constructor



// virtual destructor
TSubFleetBasic::~TSubFleetBasic()
{
  // nothing to do here, the destrcutor of the ancestor takes care of everything
                                             // and it gets called automatically
} // destructor



bool TSubFleetBasic::getUpgradeCosts( TSubstanceSet* UpgradeCosts ) const
{
  UpgradeCosts->Clear();                          // empty costs return variable
  if ( fUpgradeDesign.isValid() )                       // if upgrade is planned
  {
    TSubstanceSet* dummySet = new TSubstanceSet();   // local variable for costs
    fUpgradeDesign->getDesignCost( dummySet );    // get the costs of new design
    UpgradeCosts->Add( *dummySet, fNumberOfShips );    // and put rememeber them
    fShipDesign->getDesignCost( dummySet );       // get the costs of old design
    if ( UpgradeCosts->HasEnough( *dummySet, fNumberOfShips ) ) // if new design
    {                                          // is more expensive than the old
      UpgradeCosts->Remove( *dummySet, fNumberOfShips );       // get difference
      UpgradeCosts->Add( *UpgradeCosts, 1, 2 );        // and multiply it by 1.5
    } // if
    return true;                                 // upgrade planned: return true
  } else
    return false;                            // no upgrade planned: return false
} // getUpgradeCosts





int4 TSubFleetBasic::getFTLFuelConsumption( double Speed, double Distance ) const
{
  double dummy = Speed + Distance + dummy; // <-- to avoid warning while compile
  // FIXME don't know yet  
  return 0;
} // getFuelConsumption



double TSubFleetBasic::getFTLMaxSpeed() const
{
  return 0.0;
} // getFTLMaxSpeed



double TSubFleetBasic::getFTLMovementDistance( double Speed ) const
{
  return Speed - Speed; // <-- to avoid warning while compile
} // getFTLMovementDistance



double TSubFleetBasic::getFTLBreakDownProbability( double Speed ) const
{
  return Speed - Speed; // <-- to avoid warning while compile
} // getFTLBreakDownProbability


double TSubFleetBasic::getLongScannerRange( TScanner::tScannerType ScannerType ) const
{          // rememeber: range = sqrt( sqr(range1)+sqr(range2)+...+sqr(rangeN) )
  double rangeDummy = 0;         // initialize variable to sum up scanner ranges
                                           // item list to get the scanner items 
  TPList<TItemPack>* ScannerList = new TPList<TItemPack>();
  TPList<TItemPack>::const_iterator iter;   // const iterator for the cargo list
  
  fShipDesign->getItemList( ScannerList, TItem::SCANNER );   // get all scanners
  for( iter = ScannerList->begin(); iter != ScannerList->end(); ++ iter )
    if ( ((TScanner*) (*iter)->getItem())->getScannerType() & ScannerType != 0 )
    {                                // if wished scanner sum up sqares of range
      rangeDummy += ( (*iter)->getItemAmount() * (*iter)->getItemAmount() );
    } // if

  ScannerList->setAutoDeleteMode( true );                          // cleaning up
  delete ScannerList;
  return sqrt( rangeDummy );                            // return combined range
} // getLongScannerRange




void TSubFleetBasic::setFuel( int4 Fuel )
{
  fFuel = Fuel;                       // set new amount of fuel the subfleet has
} //setFuel



int4 TSubFleetBasic::getFuel() const
{
  return fFuel;
} // getFuel



void TSubFleetBasic::RepairSubfleet()
{
} // RepairSubfleet


int4 TSubFleetBasic::getActualHullHP() const
{
  return 20;
} // getActualHullHP


void TSubFleetBasic::getRepairCost( TSubstanceSet* RepairCost ) const
{
} // getRepairCost



bool TSubFleetBasic::IsColonizer() const
{
  bool hasColonizer = false;         // initialize bool: design has no colonizer

  TPList<TItemPack>* ColonizerList = new TPList<TItemPack>();  // list for items
   
  fShipDesign->getItemList( ColonizerList, TItem::COLONIZER ); // get colonizers
  if ( !ColonizerList->empty() )           // if there is at least one colonizer
    hasColonizer = true;                                          // remember it

  ColonizerList->setAutoDeleteMode( true );                       // cleaning up
  delete ColonizerList;
  return hasColonizer;                      // return whether it has a colonizer
} // IsColonizer



// virtual method
bool TSubFleetBasic::load( TDataPackageList* in )
{
  bool bReturn = true;

  bReturn &= TSubFleet::load( in );                           // call the parent
  bReturn &= in->getAndDelete( "fuel", &fFuel, true ); 
  return bReturn;                                
} 



// virtual method
bool TSubFleetBasic::save( TDataPackageList* out ) const
{
  bool bReturn = true;

  bReturn &= TSubFleet::save( out );                          // call the parent
  bReturn &= out->add( "fuel", &fFuel, true, false );         
  return bReturn;                                
}



// virtual
TSubFleetBasic& TSubFleetBasic::operator=( const TSubFleetBasic& SubFleet )
{
  if ( this != &SubFleet )                     // if both items are not the same
  {
    TSubFleet::operator=( SubFleet );     // copy fields inherited from SubFleet
    fFuel = SubFleet.fFuel;                             // copy all local fields
  } // if
  return *this;                                                 // return object
} // operator=



/*
 * $Log: subfleet_basic.cpp,v $
 * Revision 1.7  2002/06/28 10:12:08  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.6  2002/04/11 21:35:02  prolator
 * added some dummy code to avoid warnings
 *
 * Revision 1.5  2002/04/02 22:34:08  prolator
 * some Xet to xet
 *
 * Revision 1.4  2002/03/24 13:37:58  mkrohn5
 * mostly style changes
 *
 * Revision 1.3  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.2  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.1  2001/12/01 17:09:58  mkrohn5
 * added new directory "modules"
 *
 * Revision 1.7  2001/07/28 15:23:11  ishark
 * added filters in stolist, more client code in sl.cpp
 *
 * Revision 1.6  2001/06/23 23:27:36  prolator
 * changed way to set the number of ships
 *
 * Revision 1.5  2001/06/23 19:55:21  prolator
 * added Load and Save
 *
 * Revision 1.4  2001/06/22 14:47:08  prolator
 * fixed bug with extra called TSubFleet::~TSubFleet
 *
 * Revision 1.3  2001/06/21 21:50:09  prolator
 * adjusted to TPList<TItemPack> (new implementation in TShipDesign)
 *
 * Revision 1.2  2001/06/17 22:38:43  prolator
 * added more methods
 *
 * Revision 1.1  2001/06/16 21:34:44  prolator
 * first version of TSubFleetBasic
 *
 */
