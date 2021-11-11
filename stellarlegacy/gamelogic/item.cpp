// $Id: item.cpp,v 1.39 2002/06/28 10:12:07 mkrohn5 Exp $
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

#include "item.h"
#include "common/datapackage.h"

/********************************* class TItem *********************************/



TItem::TItem()
  : TLinkable(),
    fItemName(""),
    fItemCost()
{
  fTechLevel = 0;                     // reset all fields/properties of the item
  fItemMass = 0;                  // for fItemName and fItemCost it's done above
  fItemVolume = 0;
  fItemSurface = 0;
} // Constructor



TItem::TItem( const TItem& OldItem )
  : TLinkable()
{
  *this = OldItem;
} // copy constructor



TItem::~TItem()
{
                                                      // nothing else to do here
} // Destructor



int2 TItem::getType() const
{
  return TType::ITEM;                               // return type of the object 
} // getType



bool TItem::load( TDataPackageList* in )
{
bool ret = true;
TDataPackageList* subList = new TDataPackageList();

  // read the object => sub list
  ret &= in->getAndDelete( "item_base", subList, true );

  // read the real data from the sub list
  ret &= TLinkable::load( subList );                       // load parent's data
  ret &= subList->getAndDelete( "item_name", &fItemName, true );
  ret &= subList->getAndDelete( "item_techlevel", &fTechLevel, true );
  ret &= subList->getAndDelete( "item_mass", &fItemMass, true );
  ret &= subList->getAndDelete( "item_volume", &fItemVolume, true );
  ret &= subList->getAndDelete( "item_surface", &fItemSurface, true );
  //  ret &= fItemCost.load( subList, "item_cost", true ); FIXME

  delete subList;                                          // clean up

 return ret;
}



bool TItem::save( TDataPackageList* out ) const
{
  bool ret = true;

  TDataPackageList* subList = new TDataPackageList();     // create a new datapackage list
  // autoDelete=true so that pSubList is deleted sometime later
  ret &= out->add( "item_base", subList, true, true );

  // add the data packages to the new list
  ret &= TLinkable::save( subList );               // save parent's data
  ret &= subList->add( "item_name", &fItemName, true, false );
  ret &= subList->add( "item_techlevel", &fTechLevel, true, false );
  ret &= subList->add( "item_mass", &fItemMass, true, false );
  ret &= subList->add( "item_volume", &fItemVolume, true, false );
  ret &= subList->add( "item_surface", &fItemSurface, true, false );
  //  ReturnBool &= fItemCost.save( subList, "item_cost", true, false ); FIXME

  return ret;
} // save



const string& TItem::getTypeName() const
{
  static const string typeName = "TItem";
  return typeName;                         // return the name of the object type
} // getTypeName



void TItem::setItemName( const string& Name )
{
  fItemName = Name;                             // set the new name for the item
} // setName



const string& TItem::getItemName() const
{
  return fItemName;                                    // return the item's name
} // getName



void TItem::setTechLevel( const int2 TechLevel )
{
  fTechLevel = TechLevel;                 // set the new tech level for the item
} // setTechLevel



int2 TItem::getTechLevel() const
{
  return fTechLevel;                             // return the item's tech level
} // getTechLevel



void TItem::setMass( const int2 Mass )
{
  fItemMass = Mass;                                 // set new mass for the item
} // setMass



int2 TItem::getMass() const
{
  return fItemMass;                                    // return the item's mass
} // getMass



void TItem::setVolume( const int2 Volume )
{
  fItemVolume = Volume;                         // set new volume the item needs
} // setVolume



int2 TItem::getVolume() const
{
  return fItemVolume;                        // return the volume the item needs
} // getVolume



void TItem::setSurface( const int2 Surface)
{
  fItemSurface = Surface;             // set the new surface area the item needs
} // setSurface



int2 TItem::getSurface() const
{
  return fItemSurface;                 // return the surface area the item needs
} // getSurface



void TItem::setCost( const TSubstanceSet& Cost )
{
  fItemCost = Cost;                              // set the new cost of the item
} // setCost



void TItem::getCost( TSubstanceSet* Cost ) const
{
  Cost->Clear();                         // reset/clear substance set for return
  Cost->Add( fItemCost);                                     // add  item's cost
} // getCost



bool TItem::operator==( const TItem& Item ) const
{
  return (Item.fItemName == fItemName) &&                // are item names equal 
    (Item.fItemMass == fItemMass) &&                     // AND are masses equal
    (Item.fItemVolume == fItemVolume) &&                // AND are volumes equal
    (Item.fItemSurface == fItemSurface) &&             // AND are surfaces equal
    (Item.fItemCost == fItemCost);                        // AND are costs equal
}



// virtual method; operator= is protected
TItem& TItem::operator=( const TItem& Item )
{
  if ( this != &Item )                         // if both items are not the same
  {
    fItemName = Item.fItemName;                                   // copy values
    fTechLevel = Item.fTechLevel;
    fItemMass = Item.fItemMass;
    fItemVolume = Item.fItemVolume;
    fItemSurface = Item.fItemSurface;
    fItemCost = Item.fItemCost;
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TSTLEngine *******************************/



TSTLEngine::TSTLEngine()
  : TItem()
{
  fSTLEnginePower = 0;                                 // reset the engine power
} // Constructor



TSTLEngine::TSTLEngine( const TSTLEngine& OldSTLEngine )
  : TItem( OldSTLEngine )
{
  *this = OldSTLEngine;           // assign all fields/properties with operator=
} // copy constructor



TSTLEngine::~TSTLEngine()
{
                                                      // nothing else to do here
} // Destructor



bool  TSTLEngine::load( TDataPackageList* in )
{
  bool ret = true;

  // load all data
  ret &= TItem::load( in );                                // load parent's data
  ret &= in->getAndDelete( "stl_engine_power", &fSTLEnginePower, true );

  return ret;
}



bool  TSTLEngine::save( TDataPackageList* out ) const
{
  static const string blockType = "item";
  bool ret = true;

  // additional information to write a block (this data will not be
  // read by the load method)
  ret &= out->add( "blocktype", &blockType, true, false );

  // save all data
  ret &= TItem::save( out );                               // save parent's data
  ret &= out->add( "stl_engine_power", &fSTLEnginePower, true, false );

  return ret;
}



TItem::tItemType TSTLEngine::getItemType() const
{
  return TItem::STL_ENGINE;                       // return the type of the item
} // getItemType



void TSTLEngine::setSTLPower( const int2 STLPower )
{
  fSTLEnginePower = STLPower;                        // set the new engine power
} // setSTLPower



int2 TSTLEngine::getSTLPower() const
{
  return fSTLEnginePower;                             // return the engine power
} // getSTLPower



bool TSTLEngine::operator==( const TSTLEngine& STLEngine ) const
{
  return TItem::operator==( STLEngine ) &&            // are TItem fields equal?
    fSTLEnginePower == STLEngine.fSTLEnginePower;     // AND is STL power equal?
} // operator==



TSTLEngine& TSTLEngine::operator=(const TSTLEngine& STLEngine)
{
  if ( this != &STLEngine )                    // if both items are not the same
  {
    TItem::operator=( STLEngine );           // copy fields inherited from TItem
    fSTLEnginePower = STLEngine.fSTLEnginePower;         // copy STL power value
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TFTLEngine *******************************/



TFTLEngine::TFTLEngine()
  : TItem()
{
  fFTLEnginePower = 0;                                 // reset the engine power
} // Constructor



TFTLEngine::TFTLEngine( const TFTLEngine& OldFTLEngine )
  : TItem( OldFTLEngine )
{
  *this = OldFTLEngine;           // assign all fields/properties with operator=
} // copy constructor



TFTLEngine::~TFTLEngine()
{
                                                      // nothing else to do here
} // Destructor



bool  TFTLEngine::load( TDataPackageList* in )
{
bool ret = true;

  // load all data
  ret &= TItem::load( in );                                // load parent's data
  ret &= in->getAndDelete( "ftl_engine_power", &fFTLEnginePower, true );

  return ret;
}



bool  TFTLEngine::save( TDataPackageList* out ) const
{
  static const string blockType = "item";
  bool ret = true;;

  // additional information to write a block (this data will not be
  // read by the load method)
  ret &= out->add( "blocktype", &blockType, true, false );

  // save all data
  ret &= TItem::save( out );                               // save parent's data
  ret &= out->add( "ftl_engine_power", &fFTLEnginePower, true, false );

  return ret;
}



TItem::tItemType TFTLEngine::getItemType() const
{
  return TItem::FTL_ENGINE;                       // return the type of the item
} // getItemType



void TFTLEngine::setFTLPower( const int2 FTLPower )
{
  fFTLEnginePower = FTLPower;                        // set the new engine power
} // setFTLPower


int2 TFTLEngine::getFTLPower() const
{
  return fFTLEnginePower;                             // return the engine power
} // getFTLPower



bool TFTLEngine::operator==( const TFTLEngine& FTLEngine ) const
{
  return TItem::operator==( FTLEngine ) &&            // are TItem fields equal?
    fFTLEnginePower == FTLEngine.fFTLEnginePower;     // AND is FTL power equal?
} // operator==



TFTLEngine& TFTLEngine::operator=(const TFTLEngine& FTLEngine)
{
  if ( this != &FTLEngine )                    // if both items are not the same
  {
    TItem::operator=( FTLEngine );           // copy fields inherited from TItem
    fFTLEnginePower = FTLEngine.fFTLEnginePower;         // copy FTL power value
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TFuelTank ********************************/



TFuelTank::TFuelTank()
  : TItem()
{
  fTankCapacity = 0;                                  // reset the tank capacity
} // Constructor



TFuelTank::TFuelTank( const TFuelTank& OldFuelTank )
  : TItem( OldFuelTank )
{
  *this = OldFuelTank;            // assign all fields/properties with operator=
} // copy constructor



TFuelTank::~TFuelTank()
{
                                                      // nothing else to do here
} // Destructor



bool TFuelTank::load( TDataPackageList* in )
{
bool ret = true;

  // load all data
  ret &= TItem::load( in );                                // load parent's data
  ret &= in->getAndDelete( "tank_capacity", &fTankCapacity, true );

  return ret;
}



bool  TFuelTank::save( TDataPackageList* out ) const
{
  static const string blockType = "item";
  bool ret = true;

  // additional information to write a block (this data will not be
  // read by the load method)
  ret &= out->add( "blocktype", &blockType, true, false );

  // save all data
  ret &= TItem::save( out );                               // save parent's data
  ret &= out->add( "tank_capacity", &fTankCapacity, true, false );

  return ret;
}



TItem::tItemType TFuelTank::getItemType() const
{
  return TItem::FUELTANK;                         // return the type of the item
} // getItemType



void TFuelTank::setTankCapacity( const int2 Capacity )
{
  fTankCapacity = Capacity;                         // set the new tank capacity
} // setTankCapacity



int2 TFuelTank::getTankCapacity() const
{
  return fTankCapacity;                              // return the tank capacity
} // getTankCapacity



bool TFuelTank::operator==( const TFuelTank& FuelTank ) const
{
  return TItem::operator==( FuelTank ) &&             // are TItem fields equal?
    fTankCapacity == FuelTank.fTankCapacity;      // AND is tank capacity equal?
} // operator==



TFuelTank& TFuelTank::operator=(const TFuelTank& FuelTank)
{
  if ( this != &FuelTank )                     // if both items are not the same
  {
    TItem::operator=( FuelTank );            // copy fields inherited from TItem
    fTankCapacity = FuelTank.fTankCapacity;                // copy tank capacity
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TFuelScoop *******************************/



TFuelScoop::TFuelScoop()
  : TItem()
{
  fScoopCapacity = 0;                                // reset the scoop capacity
} // Constructor



TFuelScoop::TFuelScoop( const TFuelScoop& OldFuelScoop )
  : TItem( OldFuelScoop )
{
  *this = OldFuelScoop;           // assign all fields/properties with operator=
} // copy constructor



TFuelScoop::~TFuelScoop()
{
                                                      // nothing else to do here
} // Destructor



bool  TFuelScoop::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );               // load parent's data and scoop
  ReturnBool &= in->getAndDelete( "scoop_capacity", &fScoopCapacity, true );  // capacity
  return ReturnBool;                                  // return success (or not)
} // load



bool  TFuelScoop::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );     // save parent's data and scoop capacity
  ReturnBool &= out->add( "scoop_capacity", &fScoopCapacity, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TFuelScoop::getItemType() const
{
  return TItem::FUELSCOOP;                        // return the type of the item
} // getItemType



void TFuelScoop::setScoopCapacity( const int2 Capacity )
{
  fScoopCapacity = Capacity;                       // set the new scoop capacity
} // setScoopCapacity



int2 TFuelScoop::getScoopCapacity() const
{
  return fScoopCapacity;                            // return the scoop capacity
} // getScoopCapacity



bool TFuelScoop::operator==( const TFuelScoop& FuelScoop ) const
{
  return TItem::operator==( FuelScoop ) &&            // are TItem fields equal?
    fScoopCapacity == FuelScoop.fScoopCapacity;  // AND is scoop capacity equal?
} // operator==



TFuelScoop& TFuelScoop::operator=(const TFuelScoop& FuelScoop)
{
  if ( this != &FuelScoop )                    // if both items are not the same
  {
    TItem::operator=( FuelScoop );           // copy fields inherited from TItem
    fScoopCapacity = FuelScoop.fScoopCapacity;            // copy scoop capacity
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TCargoBay ********************************/



TCargoBay::TCargoBay()
  : TItem()
{
                                                      // no fields to initialize
} // Constructor



TCargoBay::TCargoBay( const TCargoBay& OldCargoBay )
  : TItem( OldCargoBay )
{
  *this = OldCargoBay;            // assign all fields/properties with operator=
} // copy constructor



TCargoBay::~TCargoBay()
{
                                                      // nothing else to do here
} // Destructor



bool  TCargoBay::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                         // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TCargoBay::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );                        // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TCargoBay::getItemType() const
{
  return TItem::CARGOBAY;                         // return the type of the item
} // getItemType



bool TCargoBay::operator==( const TCargoBay& CargoBay ) const
{
  return TItem::operator==( CargoBay );            // only TItem fields to check
} // operator==



TCargoBay& TCargoBay::operator=(const TCargoBay& CargoBay)
{
  if ( this != &CargoBay )                     // if both items are not the same
  {
    TItem::operator=( CargoBay );            // copy fields inherited from TItem
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TColonizer *******************************/



TColonizer::TColonizer()
  : TItem()
{
                                                      // no fields to initialize
} // Constructor



TColonizer::TColonizer( const TColonizer& OldColonizer )
  : TItem( OldColonizer )
{
  *this = OldColonizer;           // assign all fields/properties with operator=
} // copy constructor



TColonizer::~TColonizer()
{
                                                      // nothing else to do here
} // Destructor



bool  TColonizer::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                         // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TColonizer::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );                        // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TColonizer::getItemType() const
{
  return TItem::COLONIZER;                        // return the type of the item
} // getItemType



bool TColonizer::operator==( const TColonizer& Colonizer ) const
{
  return TItem::operator==( Colonizer );           // only TItem fields to check
} // operator==



TColonizer& TColonizer::operator=(const TColonizer& Colonizer)
{
  if ( this != &Colonizer )                    // if both items are not the same
  {
    TItem::operator=( Colonizer );           // copy fields inherited from TItem
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TRepairBot *******************************/



TRepairBot::TRepairBot()
  : TItem()
{
  fRepairSpeed = 0;                      // reset the repair module's efficiency
} // Constructor



TRepairBot::TRepairBot( const TRepairBot& OldRepairBot )
  : TItem( OldRepairBot )
{
  *this = OldRepairBot;           // assign all fields/properties with operator=
} // copy constructor



TRepairBot::~TRepairBot()
{
                                                      // nothing else to do here
} // Destructor



bool  TRepairBot::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );              // load parent's data and repair
  ReturnBool &= in->getAndDelete( "repair_speed", &fRepairSpeed, true );         // speed
  return ReturnBool;                                  // return success (or not)
} // load



bool  TRepairBot::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );             // save parent's data and repair
  ReturnBool &= out->add( "repair_speed", &fRepairSpeed, true, false ); // speed
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TRepairBot::getItemType() const
{
  return TItem::REPAIRBOT;                        // return the type of the item
} // getItemType



void TRepairBot::setRepairSpeed( const int2 RepairSpeed )
{
  fRepairSpeed = RepairSpeed;          // set the new repair module's efficiency
} // setRepairSpeed



int2 TRepairBot::getRepairSpeed() const
{
  return fRepairSpeed;                  // return the repair module's efficiency
} // getRepairSpeed



bool TRepairBot::operator==( const TRepairBot& RepairBot ) const
{
  return TItem::operator==( RepairBot ) &&            // are TItem fields equal?
    fRepairSpeed == RepairBot.fRepairSpeed;          // AND is efficiency equal?
} // operator==



TRepairBot& TRepairBot::operator=(const TRepairBot& RepairBot)
{
  if ( this != &RepairBot )                    // if both items are not the same
  {
    TItem::operator=( RepairBot );           // copy fields inherited from TItem
    fRepairSpeed = RepairBot.fRepairSpeed;                    // copy efficiency
  } // if
  return *this;                                                 // return object
} // operator=



/*******************************************************************************/
/************************** A R M O R  &  S H I E L D S ************************/
/*******************************************************************************/



/******************************** TEfficiencyToken *****************************/



TEfficiencyToken::TEfficiencyToken()
{
  fWeaponType = 0;                                // reset the fields/properties
  fEfficiency = 0;
} // constructor



TEfficiencyToken::TEfficiencyToken( TEfficiencyToken& OldToken )
{
  *this = OldToken;               // assign all fields/properties with operator=
} // copy constructor



TEfficiencyToken::~TEfficiencyToken()
{
                                                      // nothing else to do here
} // destructor



void TEfficiencyToken::setWeaponType( TItem::tWeaponType WeaponType )
{
  fWeaponType = WeaponType;                               // set new weapon type
} // setWeaponType



TItem::tWeaponType TEfficiencyToken::getWeaponType() const
{
  return fWeaponType;                                      // return weapon type
} // getWeaponType



void TEfficiencyToken::setEfficiency( int2 Efficiency )
{
  fEfficiency = Efficiency;                                // set new efficiency
} // setEfficiency



int2 TEfficiencyToken::getEfficiency() const
{
  return fEfficiency;                                       // return efficiency
} // getEfficiency



bool TEfficiencyToken::operator==( const TEfficiencyToken& Token ) const
{
  return ( fWeaponType == Token.fWeaponType ) &&         // are weapon types AND
    ( fEfficiency == Token.fEfficiency );                  // efficiencies equal
} // operator==



TEfficiencyToken& TEfficiencyToken::operator=( const TEfficiencyToken& Token )
{
  if ( this != &Token )                        // if both items are not the same
  {
    fWeaponType = Token.fWeaponType;                         // copy weapon type
    fEfficiency = Token.fEfficiency;                          // copy efficiency
  } // if
  return *this;                                                 // return object
} // operator=



bool TEfficiencyToken::load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                     // read the object into the local data list
  ReturnBool &=in->getAndDelete( sIdentifier, dataList, bUnique );
                        // load weapon type and efficiency out of the local list
  ReturnBool &= dataList->getAndDelete( "weapon_type", &fWeaponType, true );
  ReturnBool &= dataList->getAndDelete( "efficiency", &fEfficiency, true );
  delete dataList;                                  // dispose of the local list
  return ReturnBool;                              // return the bool for success
} // load



bool TEfficiencyToken::save( TDataPackageList* out, const string& sIdentifier, bool bUnique ) const
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                            // save weapon type and efficiency in the local list
  ReturnBool &= dataList->add( "weapon_type", &fWeaponType, true, false );
  ReturnBool &= dataList->add( "efficiency", &fEfficiency, true, false );
                                // put local data list into "parent's" data list
  ReturnBool &= out->add( sIdentifier, dataList, bUnique, true );
  return ReturnBool;                              // return the bool for success
                   // the global data list will take care of freeing the memeory
} // save



/********************************** TDefenseType *******************************/



TDefenseType::TDefenseType()
  : TLinkable(),
    fEfficiencies()
{
  fStandardEfficiency = 100;                 // set standard efficiency of armor
} // Constructor



TDefenseType::TDefenseType( const int2 StandardEfficiency )
  : TLinkable(),
    fEfficiencies()
{
  fStandardEfficiency = StandardEfficiency;       // set new standard efficiency
} // Constructor



TDefenseType::TDefenseType( const TDefenseType& OldDefenseType )
  : TLinkable() 
{
  *this = OldDefenseType;         // assign all fields/properties with operator=
} // copy constructor



TDefenseType::~TDefenseType()
{
  fEfficiencies.setAutoDeleteMode( true );               // set auto delete mode
  fEfficiencies.deleteAll();                         // delete efficiencies list
} //  Destructor


bool  TDefenseType::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TLinkable::load( in ); // load parent's data & stand. efficiency
  ReturnBool &= in->getAndDelete( "standard_efficiency", &fStandardEfficiency, true );
  ReturnBool &= fEfficiencies.load( in, "efficiencies", true );// & efficiencies
  return ReturnBool;                                  // return success (or not)
} // load



bool  TDefenseType::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TLinkable::save( out );// save parent's data & stand. efficiency
  ReturnBool &= out->add( "standard_efficiency", &fStandardEfficiency, true, false );
  ReturnBool &= fEfficiencies.save( out, "efficiencies", true );//& efficiencies
  // save efficiencies here FIXME
  return ReturnBool;                                  // return success (or not)
} // save



void TDefenseType::setStandardEfficiency( const int2 StandardEfficiency )
{
  fStandardEfficiency = StandardEfficiency;       // set new standard efficiency
} // setStandardEfficiency



int2 TDefenseType::getStandardEfficiency() const
{
  return fStandardEfficiency;             // just return the standard efficiency
} // getStandardEfficiency



void TDefenseType::setDefenseEfficiency( const TItem::tWeaponType WeaponType, const int2 Efficiency )
{
  tEfficienciesIterator iter;                  // iterator for efficiencies list

  for ( iter = fEfficiencies.begin() ; iter != fEfficiencies.end(); ++iter )
  {                                              // check all known weapon types
    if ( (*iter)->getWeaponType() == WeaponType )  // if weapon type which shall
    {                                             // be changed is already known
      (*iter)->setEfficiency( Efficiency );                    // then change it
      return;                                        // and return to the caller
    } // if
  }// for                                                                // else
  TEfficiencyToken* dummyToken = new TEfficiencyToken();     // create new token
  dummyToken->setWeaponType( WeaponType );             // assign its weapon type
  dummyToken->setEfficiency( Efficiency );              // assign its efficiency
  fEfficiencies.add( dummyToken );        // put into the efficiencies container
  return;                                            // and return to the caller
} // setDefenseEfficiency



int2 TDefenseType::getDefenseEfficiency( const TItem::tWeaponType WeaponType ) const
{
  tEfficienciesIteratorConst iter;       // const iterator for efficiencies list

  for ( iter = fEfficiencies.begin() ; iter != fEfficiencies.end(); ++iter )
  {                                              // check all known weapon types
    if ( (*iter)->getWeaponType() == WeaponType )        // if asked weapon type 
    {                                                        // is already known
      return (*iter)->getEfficiency();          // return efficieny fo this type
    } // if
  } // for                                      // else (if weapon type unknown)
  return fStandardEfficiency;                      // return standard efficiency
} // getDefenseEfficiency



bool TDefenseType::operator==( const TDefenseType& DefenseType ) const
{                                                           
  tEfficienciesIteratorConst iter;            // const iterator for list of this
  bool EfficienciesEqual = true;     // boolean to remember unequal efficiencies
  
     // FIRST: compare all efficiencies of "this" with the ones of the parameter
  for ( iter = fEfficiencies.begin(); iter != fEfficiencies.end(); ++iter )
  {                                      // check all known weapon types of this
    if ( (*iter)->getEfficiency() != DefenseType.getDefenseEfficiency((*iter)->getWeaponType()) )
    {                        // if efficiencies for this weapon type are unequal
      EfficienciesEqual = false;              // remember that they were unequal
    } // if
  } // for
    // SECOND: compare all efficiencies of the parameter with the ones of "this"
  for ( iter = DefenseType.fEfficiencies.begin(); iter != DefenseType.fEfficiencies.end(); ++iter )
  {                             // check all known weapon types of the parameter
    if ( (*iter)->getEfficiency() != getDefenseEfficiency( (*iter)->getWeaponType() ) )
    {                        // if efficiencies for this weapon type are unequal
      EfficienciesEqual = false;              // remember that they were unequal
    } // if
  } // for

                      // THIRD: return boolean = are standard efficiencies equal 
  return fStandardEfficiency == DefenseType.fStandardEfficiency &&
    EfficienciesEqual;                  // AND are all other efficiencies equal?
} // operator==



TDefenseType& TDefenseType::operator=( const TDefenseType& DefenseType )
{
  if ( this != &DefenseType )                  // if both items are not the same
  { 
    tEfficienciesIteratorConst iter;    // const iterator for efficiencies array

    fEfficiencies.setAutoDeleteMode( true );         // clear efficiencies array
    fEfficiencies.deleteAll();
    for ( iter = DefenseType.fEfficiencies.begin(); iter != DefenseType.fEfficiencies.end(); ++iter )
    {   // go through all known weapon types of DefenseType and set efficiencies
      setDefenseEfficiency( (*iter)->getWeaponType(), (*iter)->getEfficiency() );
    } // for                                              // of this accordingly
    fStandardEfficiency = DefenseType.fStandardEfficiency;    // copy efficiency
  } // if
  return *this;                                                 // return object
} // operator=



/*********************************** TArmorType ********************************/



TArmorType::TArmorType()
  : TDefenseType()
{
                                           // nothing else to do here, no fields
} // Constructor



TArmorType::TArmorType( const int2 StandardEfficiency )
  : TDefenseType( StandardEfficiency )
{
                                           // nothing else to do here, no fields
} // Constructor



TArmorType::TArmorType( const TArmorType& OldArmorType )
  : TDefenseType( OldArmorType )
{
  *this = OldArmorType;           // assign all fields/properties with operator=
} // copy constructor



TArmorType::~TArmorType()
{
                    // nothing to do here, the ancestor takes care of everything
} //  Destructor


bool  TArmorType::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TDefenseType::load( in );                  // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TArmorType::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TDefenseType::save( out );                 // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



bool TArmorType::operator==( const TArmorType& ArmorType ) const
{                                                           
  return TDefenseType::operator==( ArmorType );// are TDefenseType fields equal?
} // operator==



TArmorType& TArmorType::operator=( const TArmorType& ArmorType )
{
  if ( this != &ArmorType )                    // if both items are not the same
  {
    TDefenseType::operator=( ArmorType );       // copy fields from TDefenseType
  } // if
  return *this;                                                 // return object
} // operator=



/********************************** TShieldType ********************************/



TShieldType::TShieldType()
  : TDefenseType()
{
  fRegenerationRate = 0;                          // reset the regeneration rate
} // Constructor



TShieldType::TShieldType( const int2 StandardEfficiency )
  : TDefenseType( StandardEfficiency )
{
  fRegenerationRate = 0;                          // reset the regeneration rate
} // Constructor



TShieldType::TShieldType( const TShieldType& OldShieldType )
  : TDefenseType( OldShieldType )
{
  *this = OldShieldType;          // assign all fields/properties with operator=
} // copy constructor



TShieldType::~TShieldType()
{
                    // nothing to do here, the ancestor takes care of everything
} //  Destructor



bool  TShieldType::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TDefenseType::load( in );    // load parent's data & regen. rate
  ReturnBool &= in->getAndDelete( "regeneration_rate", &fRegenerationRate, true );
  return ReturnBool;                                  // return success (or not)
} // load



bool  TShieldType::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TDefenseType::save( out );   // save parent's data & regen. rate
  ReturnBool &= out->add( "regeneration_rate", &fRegenerationRate, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



void TShieldType::setRegenerationRate( int2 RegenerationRate )
{
  fRegenerationRate = RegenerationRate; // set new regeneration rate of the type
} // setRegenerationRate



int2 TShieldType::getRegenerationRate() const
{
  return fRegenerationRate;      // get the regeneration rate of the shield type
} //getRegenerationRate



bool TShieldType::operator==( const TShieldType& ShieldType ) const
{                                                           
  return TDefenseType::operator==( ShieldType )&&  // TDefenseType fields equal?
    fRegenerationRate == ShieldType.fRegenerationRate; // AND regen. rate equal?
} // operator==



TShieldType& TShieldType::operator=( const TShieldType& ShieldType )
{
  if ( this != &ShieldType )                   // if both items are not the same
  {
    TDefenseType::operator=( ShieldType );      // copy fields from TDefenseType
    fRegenerationRate = ShieldType.fRegenerationRate;        // copy regen. rate
  } // if
  return *this;                                                 // return object
} // operator=



/************************************ TArmor ***********************************/



TArmor::TArmor()
  : TItem(),
    fArmorType()
{
  fHitPoints = 0;                          // reset the armor's hit points value
} // Constructor



TArmor::TArmor( const TArmor& OldArmor )
  : TItem( OldArmor ),
    fArmorType()
{
  *this = OldArmor;               // assign all fields/properties with operator=
} // copy constructor



TArmor::~TArmor()
{
                                                      // nothing else to do here
} // Destructor



bool  TArmor::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                     // load parent's data and
  ReturnBool &= in->getAndDelete( "hit_points", &fHitPoints, true );        // hit points
  ReturnBool &= fArmorType.load( in, "armor_type", true );    // load armor type
  return ReturnBool;                                  // return success (or not)
} // load



bool  TArmor::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );                    // save parent's data and
  ReturnBool &= out->add( "hit_points", &fHitPoints, true, false );// hit points
  ReturnBool &= fArmorType.save( out, "armor_type", true );   // save armor type
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TArmor::getItemType() const
{
  return TItem::ARMOR;                            // return the type of the item
} // getItemType



void TArmor::setHitPoints( const int2 HitPoints )
{
  fHitPoints = HitPoints;       // set the new amount of hit point for the armor
} // setHitPoints



int2 TArmor::getHitPoints() const
{
  return fHitPoints;                 // return the hit point value for the armor
} // getHitPoints



void TArmor::setArmorType( TArmorType* ArmorType )
{
  fArmorType.setDest( ArmorType );         // set the link to the new armor type
  if ( fArmorType.isNull() )          // if ShipDesign pointed to NULL --> error
    Fatal( "TArmor", "SetArmorType", "Couldn't set link to armor type!");
} // setArmorType



const TArmorType* TArmor::getArmorType() const
{
  return fArmorType.getPointerToDest();      // return pointer to the armor type
} // getArmorType



int2 TArmor::getArmorEfficiency( const TItem::tWeaponType WeaponType ) const
{
  if ( fArmorType.isValid() )                    // if link does point somewhere
    return fArmorType->getDefenseEfficiency( WeaponType );  // return efficiency
  else                                     // else (if it points to NULL): error
    Fatal( "TArmor", "getArmorEfficiency", "Link to ArmorType not vaild!");

  return 0; // NOT REACHED
} // getArmorEfficiency



bool TArmor::operator==( const TArmor& Armor ) const
{
  return TItem::operator==( Armor ) &&                // are TItem fields equal?
    fHitPoints == Armor.fHitPoints &&               // AND are hit points equal?
                                                     // AND is armor type equal?
    *(fArmorType.getPointerToDest()) == *(Armor.fArmorType.getPointerToDest());
} // operator==



TArmor& TArmor::operator=(const TArmor& Armor)
{
  if ( this != &Armor )                        // if both items are not the same
  {
    TItem::operator=( Armor );               // copy fields inherited from TItem
    fHitPoints = Armor.fHitPoints;                            // copy hit points
    fArmorType = Armor.fArmorType;                            // copy armor type
  } // if
  return *this;                                                 // return object
} // operator=



/************************************ TShield **********************************/



TShield::TShield()
  : TItem(),
    fShieldType()
{
  fHitPoints = 0;                         // reset the shield's hit points value
} // Constructor



TShield::TShield( const TShield& OldShield )
  : TItem( OldShield ),
    fShieldType()
{
  *this = OldShield;              // assign all fields/properties with operator=
} // copy constructor



TShield::~TShield()
{
                                                      // nothing else to do here
} // Destructor



bool  TShield::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                     // load parent's data and
  ReturnBool &= in->getAndDelete( "hit_points", &fHitPoints, true );        // hit points
  ReturnBool &= fShieldType.load( in, "shield_type", true ); // load shield type
  return ReturnBool;                                  // return success (or not)
} // load



bool  TShield::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );                    // save parent's data and
  ReturnBool &= out->add( "hit_points", &fHitPoints, true, false );// hit points
  ReturnBool &= fShieldType.save( out, "shield_type", true );// save shield type
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TShield::getItemType() const
{
  return TItem::SHIELD;                           // return the type of the item
} // getItemType



void TShield::setHitPoints( const int2 HitPoints )
{
  fHitPoints = HitPoints;          // set the new hit point value for the shield
} // setHitPoints



int2 TShield::getHitPoints() const
{
  return fHitPoints;                // return the hit point value for the shield
} // getHitPoints



void TShield::setShieldType( TShieldType* ShieldType )
{
  fShieldType.setDest( ShieldType );      // set the link to the new shield type
  if ( fShieldType.isNull() )         // if ShipDesign pointed to NULL --> error
    Fatal( "TShield", "SetShieldType", "Couldn't set link to shield type!");
} // setShieldType



const TShieldType* TShield::getShieldType() const
{
  return fShieldType.getPointerToDest();               // return the shield type
} // getShieldType



int2 TShield::getShieldEfficiency( const TItem::tWeaponType WeaponType ) const
{
  if ( fShieldType.isValid() )                   // if link does point somewhere
    return fShieldType->getDefenseEfficiency( WeaponType ); // return efficiency
  else                                     // else (if it points to NULL): error
    Fatal( "TShield", "getShieldEfficiency","Link to ShieldType not vaild!");

  return 0; // NOT REACHED
} // getShieldEfficiency



bool TShield::operator==( const TShield& Shield ) const
{
  return TItem::operator==( Shield ) &&               // are TItem fields equal?
    fHitPoints == Shield.fHitPoints &&              // AND are hit points equal?
                                                    // AND is shield type equal?
    *(fShieldType.getPointerToDest()) == *(Shield.fShieldType.getPointerToDest());

} // operator==



TShield& TShield::operator=(const TShield& Shield)
{
  if ( this != &Shield )                       // if both items are not the same
  {
    TItem::operator=( Shield );              // copy fields inherited from TItem
    fHitPoints = Shield.fHitPoints;                           // copy hit points
    fShieldType = Shield.fShieldType;                        // copy shield type
  } // if
  return *this;                                                 // return object
} // operator=



/************************** class TTargetingComputer ***************************/



TTargetingComputer::TTargetingComputer()
  : TItem()
{
  fAimingEfficiency = 0;            // reset the targeting computer's efficiency
} // Constructor



TTargetingComputer::TTargetingComputer( const TTargetingComputer& OldTargetingComputer )
  : TItem( OldTargetingComputer )
{
  *this = OldTargetingComputer;   // assign all fields/properties with operator=
} // copy constructor



TTargetingComputer::~TTargetingComputer()
{
                                                      // nothing else to do here
} // Destructor



bool  TTargetingComputer::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );   // load parent's data and aiming efficiency
  ReturnBool &= in->getAndDelete( "aiming_efficiency", &fAimingEfficiency, true );
  return ReturnBool;                                  // return success (or not)
} // load



bool  TTargetingComputer::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );   // save parent's data and aimingefficiency
  ReturnBool &= out->add( "aiming_efficiency", &fAimingEfficiency, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TTargetingComputer::getItemType() const
{
  return TItem::TARGETINGCOMPUTER;                // return the type of the item
} // getItemType



void TTargetingComputer::setAimingEfficiency( const int2 AimingEfficiency )
{
  fAimingEfficiency = AimingEfficiency;                // set the new efficiency
} // setAimingEfficiency



int2 TTargetingComputer::getAimingEfficiency() const
{
  return fAimingEfficiency;        // return the targeting computer's efficiency
} // getAimingEfficiency



bool TTargetingComputer::operator==( const TTargetingComputer& TargetingComputer ) const
{
                  // are the TItem fields equal AND the aiming efficiency equal?
  return TItem::operator==( TargetingComputer ) &&
    fAimingEfficiency == TargetingComputer.fAimingEfficiency;
} // operator==



TTargetingComputer& TTargetingComputer::operator=(const TTargetingComputer& TargetingComputer)
{
  if ( this != &TargetingComputer )            // if both items are not the same
  {
    TItem::operator=( TargetingComputer );   // copy fields inherited from TItem
    fAimingEfficiency = TargetingComputer.fAimingEfficiency;      // copy aiming
  } // if
  return *this;                                                 // return object
} // operator=



/*******************************************************************************/
/******************************** W E A P O N S ********************************/
/*******************************************************************************/


/******************************** class TWeapon ********************************/



TWeapon::TWeapon()
  : TItem()
{
  fDamagePoints = 0;        // reset the damage points the kinetic weapon causes
  fRateOfFire = 0;              // reset the rate of fire for the kinetic weapon
  fWeaponType = 0;                       // reset the type of the kinetic weapon
} // Constructor



TWeapon::TWeapon( const TWeapon& OldWeapon )
  : TItem( OldWeapon )
{
  *this = OldWeapon;              // assign all fields/properties with operator=
} // copy constructor



TWeapon::~TWeapon()
{
                                                      // nothing else to do here
} // Destructor



bool  TWeapon::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                         // load parent's data
  ReturnBool &= in->getAndDelete( "damage_points", &fDamagePoints, true );     // load dp
  ReturnBool &= in->getAndDelete( "rate_of_fire", &fRateOfFire, true );       // load RoF
  ReturnBool &= in->getAndDelete( "weapon_type", &fWeaponType, true );// load weapon type
  return ReturnBool;                                  // return success (or not)
} // load



bool  TWeapon::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );           // save parent's data, dp, RoF and
  ReturnBool &= out->add( "damage_points", &fDamagePoints, true, false );// wea-
  ReturnBool &= out->add( "rate_of_fire", &fRateOfFire, true, false );    // pon
  ReturnBool &= out->add( "weapon_type", &fWeaponType, true, false );    // type
  return ReturnBool;                                  // return success (or not)
} // save



void TWeapon::setDamagePoints( const int2  DamagePoints)
{
  fDamagePoints = DamagePoints;       // set the new damage points of the weapon
} // setDamagePoints



int2 TWeapon::getDamagePoints() const
{
  return fDamagePoints;            // return the damage points the weapon causes
} // getDamagePoints



void TWeapon::setRateOfFire( const int2 RateOfFire )
{
  fRateOfFire = RateOfFire;            // set the new rate of fire of the weapon
} // setRateOfFire



int2 TWeapon::getRateOfFire() const
{
  return fRateOfFire;                   // return the rate of fire of the weapon
} // setRateOfFire



void TWeapon::setWeaponType( const TItem::tWeaponType WeaponType )
{
  fWeaponType = WeaponType;                           // set the new weapon type
} // 



TItem::tWeaponType TWeapon::getWeaponType() const
{
  return fWeaponType;                                  // return the weapon type
} // 



bool TWeapon::operator==( const TWeapon& Weapon ) const
{
  return TItem::operator==( Weapon ) &&       // are the TItem fields equal AND
    fDamagePoints == Weapon.fDamagePoints &&     // the damage points equal AND
    fRateOfFire == Weapon.fRateOfFire &&          // the rate of fire equal AND
    fWeaponType == Weapon.fWeaponType;             // AND the weapon type equal
} // operator==



TWeapon& TWeapon::operator=( const TWeapon& Weapon )
{
  if ( this != & Weapon )                      // if both items are not the same
  {
    TItem::operator=( Weapon );          // copy fields inherited from TItem and
    fDamagePoints = Weapon.fDamagePoints;                  // copy damage points
    fRateOfFire = Weapon.fRateOfFire;              // copy weapon's rate of fire
    fWeaponType = Weapon.fWeaponType;                        // copy weapon type
  } // if
  return *this;
} // operator=



/******************************* class TKWeapon ********************************/



TKWeapon::TKWeapon()
  : TWeapon()
{
  fVelocity = 0;   // reset the velocity of the projectile of the kinetic weapon
  fAmmunitionSize = 0;        // reset the ammunition size of the kinetic weapon
} // Constructor



TKWeapon::TKWeapon( const TKWeapon& OldKWeapon )
  : TWeapon( OldKWeapon )
{
  *this = OldKWeapon;             // assign all fields/properties with operator=
} // copy constructor



TKWeapon::~TKWeapon()
{
                                                      // nothing else to do here
} // Destructor



bool  TKWeapon::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TWeapon::load( in );                       // load parent's data
  ReturnBool &= in->getAndDelete( "velocity", &fVelocity, true );        // load velocity
  ReturnBool &= in->getAndDelete( "ammunition_size", &fAmmunitionSize, true );//load size
  return ReturnBool;                                  // return success (or not)
} // load



bool  TKWeapon::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TWeapon::save( out );            // save parent's data, velocity
  ReturnBool &= out->add( "velocity", &fVelocity, true, false );     // and size
  ReturnBool &= out->add( "ammunition_size", &fAmmunitionSize, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TKWeapon::getItemType() const
{
  return TItem::KWEAPON;                          // return the type of the item
} // getItemType



void TKWeapon::setVelocity( const int4 Velocity )
{
  fVelocity = Velocity;                           // set the projectile velocity
} // setVelocity



int4 TKWeapon::getVelocity() const
{
  return fVelocity;              // return the projectile velocity of the weapon
} // getVelocity



void TKWeapon::setAmmunitionSize( const int2 AmmunitionSize )
{
  fAmmunitionSize = AmmunitionSize;               // set the new ammunition size
} // 



int2 TKWeapon::getAmmunitionSize() const
{
  return fAmmunitionSize;           // return the ammunition size for the weapon
} // 



bool TKWeapon::operator==( const TKWeapon& KWeapon ) const
{
  return TWeapon::operator==( KWeapon) && // are the TWeapon fields equal AND
    fVelocity == KWeapon.fVelocity &&           // projectile velocity equal AND
    fAmmunitionSize == KWeapon.fAmmunitionSize;         // ammunition size equal
} // operator==



TKWeapon& TKWeapon::operator=(const TKWeapon& KWeapon)
{
  if ( this != &KWeapon )                      // if both items are not the same
  {
    TWeapon::operator=( KWeapon );     // copy fields inherited from TWeapon and
    fVelocity = KWeapon.fVelocity;                   // copy projectile velocity
    fAmmunitionSize = KWeapon.fAmmunitionSize;           // copy ammunition size
  } // if
  return *this;                                                 // return object
} // operator=



/******************************* class TEWeapon ********************************/



TEWeapon::TEWeapon()
  : TWeapon()
{
  fEfficientRange = 0;         // reset the efficient range of the energy weapon
} // Constructor



TEWeapon::TEWeapon( const TEWeapon& OldEWeapon )
  : TWeapon( OldEWeapon )
{
  *this = OldEWeapon;             // assign all fields/properties with operator=
} // copy constructor



TEWeapon::~TEWeapon()
{
                                                      // nothing else to do here
} // Destructor



bool  TEWeapon::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TWeapon::load( in );         // load parent's data and efficient
  ReturnBool &= in->getAndDelete( "efficient_range", &fEfficientRange, true );   // range
  return ReturnBool;                                  // return success (or not)
} // load



bool  TEWeapon::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TWeapon::save( out );  // save parent's data and efficient range
  ReturnBool &= out->add( "efficient_range", &fEfficientRange, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TEWeapon::getItemType() const
{
  return TItem::EWEAPON;                          // return the type of the item
} // getItemType



void TEWeapon::setEfficientRange( const int4 EfficientRange )
{
  fEfficientRange = EfficientRange;     // set the efficient range of the weapon
} // setEfficientRange



int4 TEWeapon::getEfficientRange() const
{
  return fEfficientRange;            // return the efficient range of the weapon
} // getEfficientRange



bool TEWeapon::operator==( const TEWeapon& EWeapon ) const
{
  return TWeapon::operator==( EWeapon ) &&   // are the TWeapon fields equal AND
    fEfficientRange == EWeapon.fEfficientRange;        // effic. range equal AND
} // operator==



TEWeapon& TEWeapon::operator=(const TEWeapon& EWeapon)
{
  if ( this != &EWeapon )                      // if both items are not the same
  {
    TWeapon::operator=( EWeapon );     // copy fields inherited from TWeapon and
    fEfficientRange = EWeapon.fEfficientRange;           // copy efficient range
  } // if
  return *this;                                                 // return object
} // operator=



/******************************* class TScanner ********************************/



TScanner::TScanner()
  : TItem()
{
  fScanEfficiency = 0;                         // reset the scanner's efficiency
  fShortRange = 0;                   // reset range for short range scan ability
  fLongRange = 0;                     // reset range for long range scan ability
} // Constructor



TScanner::TScanner( const TScanner& OldScanner )
  : TItem( OldScanner )
{
  *this = OldScanner;             // assign all fields/properties with operator=
} // copy constructor



TScanner::~TScanner()
{
                                                      // nothing else to do here
} // Destructor



bool  TScanner::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );     // load parent's data and scan efficiency
  ReturnBool &= in->getAndDelete( "scan_efficiency", &fScanEfficiency, true );
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScanner::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );    // save parent's data and scan efficiency
  ReturnBool &= out->add( "scan_efficiency", &fScanEfficiency, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TScanner::getItemType() const
{
  return TItem::SCANNER;                          // return the type of the item
} // getItemType



void TScanner::setScanEfficiency( const int2 ScanEfficiency )
{
  fScanEfficiency = ScanEfficiency;          // set the scanner's new efficiency
} // setScanEfficiency



int2 TScanner::getScanEfficiency() const
{
  return fScanEfficiency;                     // return the scanner's efficiency
} // getScanEfficiency



void TScanner::setShortRange( int4 Range )
{
  fShortRange = Range;     // set the new range for the short range scan ability
} // setShortRange



int4 TScanner::getShortRange()
{
  return fShortRange;        // return the range of the short range scan ability
} // getShortRang



void TScanner::setLongRange( int2 Range )
{
  fLongRange = Range;       // set the new range for the long range scan ability
} // setLongRang



int2 TScanner::getLongRange()
{
  return fLongRange;          // return the range of the long range scan ability
} // getLongRang



bool TScanner::operator==( const TScanner& Scanner ) const
{
  return TItem::operator==( Scanner ) &&       // are the TItem fields equal AND
    fScanEfficiency == Scanner.fScanEfficiency;    // the scan efficiency equal?
} // operator==



// virtaul; operator= is protected!!
TScanner& TScanner::operator=( const TScanner& Scanner )
{
  if ( this != &Scanner )                      // if both items are not the same
  {                                                           // copy all fields
    TItem::operator=( Scanner );         // copy fields inherited from TItem and
    fScanEfficiency = Scanner.fScanEfficiency;           // copy scan efficiency
  } // if

  return *this;
} // operator=



/* TScanner sub classes */
/* TScannerNormalActive */



TScannerNormalActive::TScannerNormalActive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerNormalActive::TScannerNormalActive( const TScannerNormalActive& OldScannerNormalActive )
  : TScanner( OldScannerNormalActive )
{
  *this = OldScannerNormalActive; // assign all fields/properties with operator=
} // copy constructor



TScannerNormalActive::~TScannerNormalActive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerNormalActive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerNormalActive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerNormalActive::getScannerType() const
{
  return TScanner::NORMAL_ACTIVE;              // return the type of the scanner
} // getItemType



bool TScannerNormalActive::operator==( const TScannerNormalActive& ScannerNormalActive ) const
{
  return TScanner::operator==( ScannerNormalActive );  // TScanner fields equal?
} // operator==



TScannerNormalActive& TScannerNormalActive::operator=(const TScannerNormalActive& ScannerNormalActive)
{
  if ( this != &ScannerNormalActive )          // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerNormalActive );       // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerNormalPassive */



TScannerNormalPassive::TScannerNormalPassive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerNormalPassive::TScannerNormalPassive( const TScannerNormalPassive& OldScannerNormalPassive )
  : TScanner( OldScannerNormalPassive )
{
  *this = OldScannerNormalPassive;           // assign all fields with operator=
} // copy constructor



TScannerNormalPassive::~TScannerNormalPassive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerNormalPassive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerNormalPassive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerNormalPassive::getScannerType() const
{
  return TScanner::NORMAL_PASSIVE;             // return the type of the scanner
} // getItemType



bool TScannerNormalPassive::operator==( const TScannerNormalPassive& ScannerNormalPassive ) const
{
  return TScanner::operator==( ScannerNormalPassive );  //TScanner fields equal?
} // operator==



TScannerNormalPassive& TScannerNormalPassive::operator=(const TScannerNormalPassive& ScannerNormalPassive)
{
  if ( this != &ScannerNormalPassive )         // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerNormalPassive );      // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerAntiDisguiseActive */



TScannerAntiDisguiseActive::TScannerAntiDisguiseActive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerAntiDisguiseActive::TScannerAntiDisguiseActive( const TScannerAntiDisguiseActive& OldScannerAntiDisguiseActive )
  : TScanner( OldScannerAntiDisguiseActive )
{
  *this = OldScannerAntiDisguiseActive;      // assign all fields with operator=
} // copy constructor



TScannerAntiDisguiseActive::~TScannerAntiDisguiseActive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerAntiDisguiseActive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerAntiDisguiseActive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerAntiDisguiseActive::getScannerType() const
{
  return TScanner::ANTIDISGUISE_ACTIVE;       // return the type of the scanner
} // getItemType



bool TScannerAntiDisguiseActive::operator==( const TScannerAntiDisguiseActive& ScannerAntiDisguiseActive ) const
{
                                               // are the TScanner fields equal?
  return TScanner::operator==( ScannerAntiDisguiseActive );
} // operator==



TScannerAntiDisguiseActive& TScannerAntiDisguiseActive::operator=(const TScannerAntiDisguiseActive& ScannerAntiDisguiseActive)
{
  if ( this != &ScannerAntiDisguiseActive )    // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerAntiDisguiseActive ); // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerAntiDisguisePassive */



TScannerAntiDisguisePassive::TScannerAntiDisguisePassive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerAntiDisguisePassive::TScannerAntiDisguisePassive( const TScannerAntiDisguisePassive& OldScannerAntiDisguisePassive )
  : TScanner( OldScannerAntiDisguisePassive )
{
  *this = OldScannerAntiDisguisePassive;     // assign all fields with operator=
} // copy constructor



TScannerAntiDisguisePassive::~TScannerAntiDisguisePassive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerAntiDisguisePassive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerAntiDisguisePassive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerAntiDisguisePassive::getScannerType() const
{
  return TScanner::ANTIDISGUISE_PASSIVE;       // return the type of the scanner
} // getItemType



bool TScannerAntiDisguisePassive::operator==( const TScannerAntiDisguisePassive& ScannerAntiDisguisePassive ) const
{
                                               // are the TScanner fields equal?
  return TScanner::operator==( ScannerAntiDisguisePassive );
} // operator==



TScannerAntiDisguisePassive& TScannerAntiDisguisePassive::operator=(const TScannerAntiDisguisePassive& ScannerAntiDisguisePassive)
{
  if ( this != &ScannerAntiDisguisePassive )   // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerAntiDisguisePassive );// inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerAntiCloakActive */



TScannerAntiCloakActive::TScannerAntiCloakActive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerAntiCloakActive::TScannerAntiCloakActive( const TScannerAntiCloakActive& OldScannerAntiCloakActive )
  : TScanner( OldScannerAntiCloakActive )
{
  *this = OldScannerAntiCloakActive;         // assign all fields with operator=
} // copy constructor



TScannerAntiCloakActive::~TScannerAntiCloakActive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerAntiCloakActive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerAntiCloakActive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerAntiCloakActive::getScannerType() const
{
  return TScanner::ANTICLOAK_ACTIVE;           // return the type of the scanner
} // getItemType



bool TScannerAntiCloakActive::operator==( const TScannerAntiCloakActive& ScannerAntiCloakActive ) const
{
                                               // are the TScanner fields equal?
  return TScanner::operator==( ScannerAntiCloakActive );
} // operator==



TScannerAntiCloakActive& TScannerAntiCloakActive::operator=(const TScannerAntiCloakActive& ScannerAntiCloakActive)
{
  if ( this != &ScannerAntiCloakActive )       // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerAntiCloakActive );    // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerAntiCloakPassive */



TScannerAntiCloakPassive::TScannerAntiCloakPassive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerAntiCloakPassive::TScannerAntiCloakPassive( const TScannerAntiCloakPassive& OldScannerAntiCloakPassive )
  : TScanner( OldScannerAntiCloakPassive )
{
  *this = OldScannerAntiCloakPassive;        // assign all fields with operator=
} // copy constructor



TScannerAntiCloakPassive::~TScannerAntiCloakPassive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerAntiCloakPassive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerAntiCloakPassive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerAntiCloakPassive::getScannerType() const
{
  return TScanner::ANTICLOAK_PASSIVE;          // return the type of the scanner
} // getItemType



bool TScannerAntiCloakPassive::operator==( const TScannerAntiCloakPassive& ScannerAntiCloakPassive ) const
{
                                               // are the TScanner fields equal?
  return TScanner::operator==( ScannerAntiCloakPassive );
} // operator==



TScannerAntiCloakPassive& TScannerAntiCloakPassive::operator=(const TScannerAntiCloakPassive& ScannerAntiCloakPassive)
{
  if ( this != &ScannerAntiCloakPassive )      // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerAntiCloakPassive );   // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerPenetrateActive */



TScannerPenetrateActive::TScannerPenetrateActive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerPenetrateActive::TScannerPenetrateActive( const TScannerPenetrateActive& OldScannerPenetrateActive )
  : TScanner( OldScannerPenetrateActive )
{
  *this = OldScannerPenetrateActive;         // assign all fields with operator=
} // copy constructor



TScannerPenetrateActive::~TScannerPenetrateActive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerPenetrateActive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerPenetrateActive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerPenetrateActive::getScannerType() const
{
  return TScanner::PENETRATE_ACTIVE;           // return the type of the scanner
} // getItemType



bool TScannerPenetrateActive::operator==( const TScannerPenetrateActive& ScannerPenetrateActive ) const
{
                                               // are the TScanner fields equal?
  return TScanner::operator==( ScannerPenetrateActive );
} // operator==



TScannerPenetrateActive& TScannerPenetrateActive::operator=(const TScannerPenetrateActive& ScannerPenetrateActive)
{
  if ( this != &ScannerPenetrateActive )       // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerPenetrateActive );    // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/* TScannerPenetratePassive */



TScannerPenetratePassive::TScannerPenetratePassive()
  : TScanner()
{
                                                      // no fields to initialize
} // Constructor



TScannerPenetratePassive::TScannerPenetratePassive( const TScannerPenetratePassive& OldScannerPenetratePassive )
  : TScanner( OldScannerPenetratePassive )
{
  *this = OldScannerPenetratePassive;        // assign all fields with operator=
} // copy constructor



TScannerPenetratePassive::~TScannerPenetratePassive()
{
                                                      // nothing else to do here
} // Destructor



bool  TScannerPenetratePassive::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::load( in );                      // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TScannerPenetratePassive::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TScanner::save( out );                     // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TScanner::tScannerType TScannerPenetratePassive::getScannerType() const
{
  return TScanner::PENETRATE_PASSIVE;          // return the type of the scanner
} // getItemType



bool TScannerPenetratePassive::operator==( const TScannerPenetratePassive& ScannerPenetratePassive ) const
{
                                               // are the TScanner fields equal?
  return TScanner::operator==( ScannerPenetratePassive );
} // operator==



TScannerPenetratePassive& TScannerPenetratePassive::operator=(const TScannerPenetratePassive& ScannerPenetratePassive)
{
  if ( this != &ScannerPenetratePassive )      // if both items are not the same
  {                                                           // copy all fields
    TScanner::operator=( ScannerPenetratePassive );   // inherited from TScanner
  } // if
  return *this;                                                 // return object
} // operator=



/******************************* class TJammer *********************************/



TJammer::TJammer()
  : TItem()
{
  fJamEfficiency = 0;                           // reset the jammer's efficiency
} // Constructor



TJammer::TJammer( const TJammer& OldJammer )
  : TItem( OldJammer )
{
  *this = OldJammer;              // assign all fields/properties with operator=
} // copy constructor



TJammer::~TJammer()
{
                                                      // nothing else to do here
} // Destructor



bool  TJammer::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );      // load parent's data and jam efficiency
  ReturnBool &= in->getAndDelete( "jam_efficiency", &fJamEfficiency, true );
  return ReturnBool;                                  // return success (or not)
} // load



bool  TJammer::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );     // save parent's data and jam efficiency
  ReturnBool &= out->add( "jam_efficiency", &fJamEfficiency, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TJammer::getItemType() const
{
  return TItem::JAMMER;                           // return the type of the item
} // getItemType



void TJammer::setJamEfficiency( const int2 JamEfficiency )
{
  fJamEfficiency = JamEfficiency;             // set the jammer's new efficiency
} // setJamEfficiency



int2 TJammer::getJamEfficiency() const
{
  return fJamEfficiency;                       // return the jammer's efficiency
} // getJamEfficiency



bool TJammer::operator==( const TJammer& Jammer ) const
{
  return TItem::operator==( Jammer ) &&        // are the TItem fields equal AND
    fJamEfficiency == Jammer.fJamEfficiency;        // the jam efficiency equal?
} // operator==



// virtual; operator= is protected!!
TJammer& TJammer::operator=( const TJammer& Jammer )
{
    TItem::operator=( Jammer );          // copy fields inherited from TItem and
    fJamEfficiency = Jammer.fJamEfficiency;               // copy jam efficiency

    return *this;
} // operator=



/* TJammer sub classes */
/* TJammerNormal */



TJammerNormal::TJammerNormal()
  : TJammer()
{
                                                      // no fields to initialize
} // Constructor



TJammerNormal::TJammerNormal( const TJammerNormal& OldJammerNormal )
  : TJammer( OldJammerNormal )
{
  *this = OldJammerNormal;        // assign all fields/properties with operator=
} // copy constructor



TJammerNormal::~TJammerNormal()
{
                                                      // nothing else to do here
} // Destructor



bool  TJammerNormal::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::load( in );                       // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TJammerNormal::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::save( out );                      // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TJammer::tJammerType TJammerNormal::getJammerType() const
{
  return TJammer::NORMAL;                       // return the type of the jammer
} // getItemType



bool TJammerNormal::operator==( const TJammerNormal& JammerNormal ) const
{
  return TJammer::operator==( JammerNormal );       // are TJammer fields equal?
} // operator==



TJammerNormal& TJammerNormal::operator=(const TJammerNormal& JammerNormal)
{
  if ( this != &JammerNormal )                 // if both items are not the same
  {                                                           // copy all fields
    TJammer::operator=( JammerNormal );                // inherited from TJammer
  } // if
  return *this;                                                 // return object
} // operator=



/* TJammerDisguise */



TJammerDisguise::TJammerDisguise()
  : TJammer()
{
                                                      // no fields to initialize
} // Constructor



TJammerDisguise::TJammerDisguise( const TJammerDisguise& OldJammerDisguise )
  : TJammer( OldJammerDisguise )
{
  *this = OldJammerDisguise;      // assign all fields/properties with operator=
} // copy constructor



TJammerDisguise::~TJammerDisguise()
{
                                                      // nothing else to do here
} // Destructor



bool  TJammerDisguise::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::load( in );                       // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TJammerDisguise::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::save( out );                      // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TJammer::tJammerType TJammerDisguise::getJammerType() const
{
  return TJammer::DISGUISE;                     // return the type of the jammer
} // getItemType



bool TJammerDisguise::operator==( const TJammerDisguise& JammerDisguise ) const
{
  return TJammer::operator==( JammerDisguise );     // are TJammer fields equal?
} // operator==



TJammerDisguise& TJammerDisguise::operator=(const TJammerDisguise& JammerDisguise)
{
  if ( this != &JammerDisguise )               // if both items are not the same
  {                                                           // copy all fields
    TJammer::operator=( JammerDisguise );              // inherited from TJammer
  } // if
  return *this;                                                 // return object
} // operator=



/* TJammerCloak */



TJammerCloak::TJammerCloak()
  : TJammer()
{
                                                      // no fields to initialize
} // Constructor



TJammerCloak::TJammerCloak( const TJammerCloak& OldJammerCloak )
  : TJammer( OldJammerCloak )
{
  *this = OldJammerCloak;         // assign all fields/properties with operator=
} // copy constructor



TJammerCloak::~TJammerCloak()
{
                                                      // nothing else to do here
} // Destructor



bool  TJammerCloak::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::load( in );                       // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TJammerCloak::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::save( out );                      // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TJammer::tJammerType TJammerCloak::getJammerType() const
{
  return TJammer::CLOAK;                        // return the type of the jammer
} // getItemType



bool TJammerCloak::operator==( const TJammerCloak& JammerCloak ) const
{
  return TJammer::operator==( JammerCloak );        // are TJammer fields equal?
} // operator==



TJammerCloak& TJammerCloak::operator=(const TJammerCloak& JammerCloak)
{
  if ( this != &JammerCloak )                  // if both items are not the same
  {                                                           // copy all fields
    TJammer::operator=( JammerCloak );                 // inherited from TJammer
  } // if
  return *this;                                                 // return object
} // operator=



/* TJammerAntiPenetrate */



TJammerAntiPenetrate::TJammerAntiPenetrate()
  : TJammer()
{
                                                      // no fields to initialize
} // Constructor



TJammerAntiPenetrate::TJammerAntiPenetrate( const TJammerAntiPenetrate& OldJammerAntiPenetrate )
  : TJammer( OldJammerAntiPenetrate )
{
  *this = OldJammerAntiPenetrate; // assign all fields/properties with operator=
} // copy constructor



TJammerAntiPenetrate::~TJammerAntiPenetrate()
{
                                                      // nothing else to do here
} // Destructor



bool  TJammerAntiPenetrate::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::load( in );                       // load parent's data
  return ReturnBool;                                  // return success (or not)
} // load



bool  TJammerAntiPenetrate::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TJammer::save( out );                      // save parent's data
  return ReturnBool;                                  // return success (or not)
} // save



TJammer::tJammerType TJammerAntiPenetrate::getJammerType() const
{
  return TJammer::ANTIPENETRATE;                // return the type of the jammer
} // getItemType



bool TJammerAntiPenetrate::operator==( const TJammerAntiPenetrate& JammerAntiPenetrate ) const
{
  return TJammer::operator==( JammerAntiPenetrate );    // TJammer fields equal?
} // operator==



TJammerAntiPenetrate& TJammerAntiPenetrate::operator=(const TJammerAntiPenetrate& JammerAntiPenetrate)
{
  if ( this != &JammerAntiPenetrate )          // if both items are not the same
  {                                                           // copy all fields
    TJammer::operator=( JammerAntiPenetrate );         // inherited from TJammer
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TMineLayer *******************************/



TMineLayer::TMineLayer()
  : TItem()
{
  fMineLayingRate = 0;      // reset the mine laying facility's mine laying rate
} // Constructor



TMineLayer::TMineLayer( const TMineLayer& OldMineLayer )
  : TItem( OldMineLayer )
{
  *this = OldMineLayer;           // assign all fields/properties with operator=
} // copy constructor



TMineLayer::~TMineLayer()
{
                                                      // nothing else to do here
} // Destructor



bool  TMineLayer::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );         // load parent's data and mine laying
  ReturnBool &= in->getAndDelete( "mine_laying_rate", &fMineLayingRate, true );   // rate
  return ReturnBool;                                  // return success (or not)
} // load



bool  TMineLayer::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );   // save parent's data and mine laying rate
  ReturnBool &= out->add( "mine_laying_rate", &fMineLayingRate, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TMineLayer::getItemType() const
{
  return TItem::MINELAYER;                        // return the type of the item
} // getItemType



void TMineLayer::setMineLayingRate( const int2 MineLayingRate )
{
  fMineLayingRate = MineLayingRate;              // set the new mine laying rate
} // setMineLayingRate



int2 TMineLayer::getMineLayingRate() const
{
  return fMineLayingRate;                         // return the mine laying rate
} // getMineLayingRate



bool TMineLayer::operator==( const TMineLayer& MineLayer ) const
{
  return TItem::operator==( MineLayer ) &&    // are TItem fields equal AND mine
    fMineLayingRate == MineLayer.fMineLayingRate;           // laying rate equal
} // operator==



TMineLayer& TMineLayer::operator=(const TMineLayer& MineLayer)
{
  if ( this != &MineLayer )                    // if both items are not the same
  {
    TItem::operator=( MineLayer );           // copy fields inherited from TItem
    fMineLayingRate = MineLayer.fMineLayingRate;     // and the mine laying rate
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TMiningBot *******************************/



TMiningBot::TMiningBot()
  : TItem()
{
  fMiningRate = 0;            // reset the mining facility's mineral mining rate
} // Constructor



TMiningBot::TMiningBot( const TMiningBot& OldMiningBot )
  : TItem( OldMiningBot )
{
  *this = OldMiningBot;           // assign all fields/properties with operator=
} // copy constructor



TMiningBot::~TMiningBot()
{
                                                      // nothing else to do here
} // Destructor



bool  TMiningBot::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                     // load parent's data and
  ReturnBool &= in->getAndDelete( "mining_rate", &fMiningRate, true );     // mining rate
  return ReturnBool;                                  // return success (or not)
} // load



bool  TMiningBot::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );             // save parent's data and mining
  ReturnBool &= out->add( "mining_rate", &fMiningRate, true, false );    // rate
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TMiningBot::getItemType() const
{
  return TItem::MININGBOT;                        // return the type of the item
} // getItemType


void TMiningBot::setMiningRate( const int2 MiningRate )
{
  fMiningRate = MiningRate;                   // set the new mineral mining rate
} // setMiningRate



int2 TMiningBot::getMiningRate() const
{
  return fMiningRate;        // return the mining facility's mineral mining rate
} // getMiningRate



bool TMiningBot::operator==( const TMiningBot& MiningBot ) const
{
  return TItem::operator==( MiningBot ) &&         // are the TItem fields equal
    fMiningRate == MiningBot.fMiningRate;           // AND the mining rate equal
} // operator==



TMiningBot& TMiningBot::operator=(const TMiningBot& MiningBot)
{
  if ( this != &MiningBot )                    // if both items are not the same
  {
    TItem::operator=( MiningBot );           // copy fields inherited from TItem
    fMiningRate = MiningBot.fMiningRate;          // and the mineral mining rate
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TFighterLauncher *******************************/



TFighterLauncher::TFighterLauncher()
  : TItem()
{
  fLaunchRate = 0;    // reset the fighter launcher bay's fighter launching rate
  fLandingRate = 0;     // reset the fighter launcher bay's fighter landing rate
  fRepairRate = 0;       // reset the fighter launcher bay's fighter repair rate
} // Constructor



TFighterLauncher::TFighterLauncher( const TFighterLauncher& OldFighterLauncher )
  : TItem( OldFighterLauncher )
{
  *this = OldFighterLauncher;     // assign all fields/properties with operator=
} // copy constructor



TFighterLauncher::~TFighterLauncher()
{
                                                      // nothing else to do here
} // Destructor



bool  TFighterLauncher::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                     // load parent's data and
  ReturnBool &= in->getAndDelete( "launch_rate", &fLaunchRate, true );     // launch rate
  ReturnBool &= in->getAndDelete( "landing_rate", &fLandingRate, true );  // landing rate
  ReturnBool &= in->getAndDelete( "repair_rate", &fRepairRate, true );     // repair rate
  return ReturnBool;                                  // return success (or not)
} // load



bool  TFighterLauncher::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );    // save parent's data and launch/landing/
  ReturnBool &= out->add( "launch_rate", &fLaunchRate, true, false );  // repair
  ReturnBool &= out->add( "landing_rate", &fLandingRate, true, false );  // rate
  ReturnBool &= out->add( "repair_rate", &fRepairRate, true, false );
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TFighterLauncher::getItemType() const
{
  return TItem::FIGHTERLAUNCHER;                  // return the type of the item
} // getItemType


void TFighterLauncher::setLaunchRate( const int2 LaunchRate )
{
  fLaunchRate = LaunchRate;  // set the fighter bay's new fighter launching rate
} // setLaunchRate



int2 TFighterLauncher::getLaunchRate() const
{
  return fLaunchRate;         // return the fighter bay's fighter launching rate
} // getLaunchRate



void TFighterLauncher::setLandingRate( const int2 LandingRate )
{
  fLandingRate = LandingRate;  // set the fighter bay's new fighter landing rate
} // setLandingRate



int2 TFighterLauncher::getLandingRate() const
{
  return fLandingRate;          // return the fighter bay's fighter landing rate
} // getLandingRate



void TFighterLauncher::setRepairRate( const int2 RepairRate )
{
  fRepairRate = RepairRate;     // set the fighter bay's new fighter repair rate
} // setRepairRate



int2 TFighterLauncher::getRepairRate() const
{
  return fRepairRate;            // return the fighter bay's fighter repair rate
} // getRepairRate



bool TFighterLauncher::operator==( const TFighterLauncher& FighterLauncher ) const
{
  return TItem::operator==( FighterLauncher ) &&   // are TItem fields equal AND
    fLaunchRate == FighterLauncher.fLaunchRate &&     // the launching rates AND
    fLandingRate == FighterLauncher.fLandingRate &&     // the landing rates AND
    fRepairRate == FighterLauncher.fRepairRate;        // the repair rates equal
} // operator==



TFighterLauncher& TFighterLauncher::operator=(const TFighterLauncher& FighterLauncher)
{
  if ( this != &FighterLauncher )              // if both items are not the same
  {
    TItem::operator=( FighterLauncher );     // copy fields inherited from TItem
    fLaunchRate = FighterLauncher.fLaunchRate;           // copy launching rates
    fLandingRate = FighterLauncher.fLandingRate;           // copy landing rates
    fRepairRate = FighterLauncher.fRepairRate;              // copy repair rates
  } // if
  return *this;                                                 // return object
} // operator=



/****************************** class TSPWeaponLauncher *******************************/



TSPWeaponLauncher::TSPWeaponLauncher()
  : TItem()
{
  fLaunchRate = 0;    // reset the SP weapon launcher's SP weapon launching rate
} // Constructor



TSPWeaponLauncher::TSPWeaponLauncher( const TSPWeaponLauncher& OldSPWeaponLauncher )
  : TItem( OldSPWeaponLauncher )
{
  *this = OldSPWeaponLauncher;    // assign all fields/properties with operator=
} // copy constructor



TSPWeaponLauncher::~TSPWeaponLauncher()
{
                                                      // nothing else to do here
} // Destructor



bool  TSPWeaponLauncher::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::load( in );                     // load parent's data and
  ReturnBool &= in->getAndDelete( "launch_rate", &fLaunchRate, true );     // launch rate
  return ReturnBool;                                  // return success (or not)
} // load



bool  TSPWeaponLauncher::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TItem::save( out );             // save parent's data and launch
  ReturnBool &= out->add( "launch_rate", &fLaunchRate, true, false );    // rate
  return ReturnBool;                                  // return success (or not)
} // save



TItem::tItemType TSPWeaponLauncher::getItemType() const
{
  return TItem::SPWEAPONLAUNCHER;                 // return the type of the item
} // getItemType


void TSPWeaponLauncher::setLaunchRate( const int2 LaunchRate )
{
  fLaunchRate = LaunchRate;   // set the SP weapon launcher's new launching rate
} // setLaunchRate



int2 TSPWeaponLauncher::getLaunchRate() const
{
  return fLaunchRate;          // return the SP weapon launcher's launching rate
} // getLaunchRate


bool TSPWeaponLauncher::operator==( const TSPWeaponLauncher& SPWeaponLauncher ) const
{
  return TItem::operator==( SPWeaponLauncher ) &&  // are TItem fields equal AND
    fLaunchRate == SPWeaponLauncher.fLaunchRate;        // launching rates equal
} // operator==



TSPWeaponLauncher& TSPWeaponLauncher::operator=(const TSPWeaponLauncher& SPWeaponLauncher)
{
  if ( this != &SPWeaponLauncher )             // if both items are not the same
  {
    TItem::operator=( SPWeaponLauncher );    // copy fields inherited from TItem
    fLaunchRate = SPWeaponLauncher.fLaunchRate;          // copy launching rates
  } // if
  return *this;                                                 // return object
} // operator=



/*
 * $Log: item.cpp,v $
 * Revision 1.39  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.38  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.37  2002/04/11 21:33:34  prolator
 * removed default values for parameters from .cpp-file
 *
 * Revision 1.36  2002/04/02 22:33:08  prolator
 * some Xet to xet
 *
 * Revision 1.35  2002/03/24 13:36:35  mkrohn5
 * mostly style changes
 *
 * Revision 1.34  2002/02/03 23:16:55  mkrohn5
 * some changes esp. to the load / save methods
 *
 * Revision 1.33  2001/12/16 11:37:24  ishark
 * TLink now uses dynamic_cast<>, lots of TAction-related fixes
 *
 * Revision 1.32  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.31  2001/12/02 14:21:59  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.30  2001/06/25 21:07:12  ishark
 * modified parser (still bad) + removed minor warnings in waypoint
 *
 * Revision 1.29  2001/06/24 14:59:05  prolator
 * corrected mistake range instead of rang
 *
 * Revision 1.28  2001/06/24 14:35:53  prolator
 * added short and long range for scanners
 *
 * Revision 1.27  2001/06/23 00:12:24  prolator
 * added Save for efficiencies list in TDefenseType
 *
 * Revision 1.26  2001/06/22 14:52:14  prolator
 * changed implementation of TDefenseType: now with TPList<TEfficiencyToken>
 *
 * Revision 1.25  2001/06/21 21:36:40  prolator
 * changed operator== of armor/shield: now it compares the content of defense type
 *
 * Revision 1.24  2001/06/20 15:46:45  prolator
 * added methods Load and Save; for TDefenseType they don't work yet properly!
 *
 * Revision 1.23  2001/06/15 23:28:34  prolator
 * changed interface of TArmor and TShield: GetDamagePoints to GetHitPoints
 *
 * Revision 1.22  2001/06/15 13:53:55  prolator
 * added TArmorType and TShieldType
 *
 * Revision 1.21  2001/06/14 15:44:45  prolator
 * changed return type of GetArmorType and GetShieldType to TLink<TDefenseType>
 *
 * Revision 1.20  2001/06/14 12:00:41  prolator
 * changed TItemList to tItemList (now in TShipDesign
 *
 * Revision 1.19  2001/06/13 15:45:42  prolator
 * changed the implementation of operator= and operator==
 *
 * Revision 1.18  2001/06/12 21:43:07  prolator
 * changed GetCost interface
 *
 * Revision 1.16  2001/06/12 15:55:00  prolator
 * added TShield
 *
 * Revision 1.15  2001/06/12 13:53:09  prolator
 * changed from TArmorType to TDefensType for armor and schields
 *
 * Revision 1.14  2001/06/12 12:40:16  prolator
 * introduced TWeapon as ancestor of TKWeapon and TEWeapon
 *
 * Revision 1.13  2001/06/12 11:49:27  prolator
 * added TArmor and TArmorType
 *
 * Revision 1.12  2001/06/11 18:54:43  mkrohn5
 * fixed problems with TLinkable copy constructor
 *
 * Revision 1.11  2001/06/11 14:27:08  prolator
 * tech level added to TItem and sub classes
 *
 * Revision 1.10  2001/06/10 23:30:44  mkrohn5
 * added operator= method to avoid problems with TLinkable
 *
 * Revision 1.9  2001/06/10 22:52:20  prolator
 * small changes at interface; velocity and range of weapons now int4
 *
 * Revision 1.8  2001/06/09 23:42:04  prolator
 * added first versions of TKWeapon, TEWeapon and TJammer with all sub classes
 *
 * Revision 1.7  2001/06/09 21:59:27  prolator
 * added first versions of TFighterLauncher, TSPWeaponLauncher and TScanner with all sub classes
 *
 * Revision 1.6  2001/06/09 19:05:53  prolator
 * added first versions of TCargoBay, TColonizer, TRepairBot, TTargetingComputer, TMineLayer and TMiningBot
 *
 * Revision 1.5  2001/06/07 13:50:10  prolator
 * added operator==, made TItem abstract and added TFTLEngine and TFuelTank
 *
 * Revision 1.4  2001/05/21 23:28:47  prolator
 * added operator= and copy constructor; improved example class TEngine a little
 *
 * Revision 1.3  2001/05/19 19:40:01  prolator
 * added firts version of TItemList
 *
 * Revision 1.2  2001/05/17 14:21:54  prolator
 * Added method GetItemType (returns whether it is armor, engine or similar)
 *
 * Revision 1.1  2001/05/17 12:49:12  prolator
 * Code file for TItem
 *
 */
