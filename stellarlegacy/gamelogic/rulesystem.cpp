// $Id: rulesystem.cpp,v 1.1 2002/07/12 10:10:35 mkrohn5 Exp $

// Rule System Code File
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

#include <fstream>

#include "common/datapackage.h"

#include "gamelogic/fleet.h"
#include "gamelogic/rulesystem.h"
#include "gamelogic/item.h"
#include "gamelogic/race.h"
#include "gamelogic/ruleatom.h"
#include "gamelogic/galaxy.h"
#include "gamelogic/system.h"

#include "gamelogic/modules/fleet_basic.h"
#include "gamelogic/modules/race_basic.h"
#include "gamelogic/modules/race_sl.h"
#include "gamelogic/modules/system_basic.h"

using namespace std;





//----------------------------------------  class TRuleSystem  ----------------------------------------

bool TRuleSystem :: checkDependencies()
{
map<string, string>::const_iterator it;

  LOG("TRuleSystem","checkDependencies") << "now checking rule dependencies..." << endl;
  if ( fVerified == true )  return true;

  fErrorList.clear();                                      // reset the old list of errors
  fVerified = true;

  // check if all modules have reasonable values
  for ( it=fModules.begin(); it!=fModules.end(); it++ )  {
    if ( it->second == "" )  {
      fVerified = false;
      fErrorList.push_back( tError("",it->first) );
    }
  }

  // check if all rule atoms have reasonable values
  for ( it=fRules.begin(); it!=fRules.end(); it++ )  {
    if ( it->second == "" )  {
      fVerified = false;
      fErrorList.push_back( tError(it->first,"") );
    }
  }

  // it makes no sense to check the dependencies
  if ( fVerified == false )  {
    LOG("TRuleSystem","checkDependencies") << "failed! not all modules exist!" << endl;
    return 0;
  }

  // now check if the rules have any real dependencies
  for ( it=fRules.begin(); it!=fRules.end(); it++ )  {
    TRuleAtom* ra = getRuleAtom( it->first );
    LOG("TRuleSystem","checkDependencies") << "checking: " << it->first << endl;

    if ( ra != 0 )  {
      if ( ra->checkDependencies(&fErrorList) == false )  {
        LOG("TRuleSystem","checkDependencies")  << "failed!" << endl;
        fVerified = false;
      }
    }
    else  {
      LOG("TRuleSystem","checkDependencies")  << "rule atom: "
        << it->first << " does not exist." << endl;
      fVerified = false;
    }
    delete ra;
  }

  if ( fVerified == true )  {
    LOG("TRuleSystem","checkDependencies") << "all dependecies fulfilled!" << endl;
  }

  return fVerified;
}



TFleet* TRuleSystem :: createFleet() const
{
TFleet* fleet;

  LOG("TRuleSystem","createFleet") << "will create a new fleet" << endl;
  if ( fVerified == false )  return 0;

  string rule = getModule( "fleet" );
  if ( rule == "basic" )       fleet = new TFleetBasic();

  return fleet;
}



TItem* TRuleSystem :: createItem( int2 type ) const
{
TItem* ret = 0;

  if ( fVerified == false )   return 0;
  if ( type == TItem::STL_ENGINE )  ret = new TSTLEngine();
  if ( type == TItem::FTL_ENGINE )  ret = new TFTLEngine();
  if ( type == TItem::FUELTANK )  ret = new TFuelTank();

  return ret;
}



TRace* TRuleSystem :: createRace() const
{
TRace* race;

  LOG("TRuleSystem","createRace") << "will create a new race" << endl;
  if ( fVerified == false )   return 0;

  string rule = getModule( "race" );
  if ( rule == "basic" )                race = new TRaceBasic();
  else if ( rule == "stellarlegacy" )   race = new TRaceSL();

  return race;
}



TSystem* TRuleSystem :: createSystem() const
{
TSystem* system;

  LOG("TRuleSystem","createSystem") << "will create a new system" << endl;
  if ( fVerified == false )   return 0;

  string rule = getModule( "system" );
  if ( rule == "basic" )                system = new TSystemBasic();

  return system;
}



TRuleAtom* TRuleSystem :: getRuleAtom( const string& ruleName ) const
{
map<string, string>::const_iterator it;

  if ( fVerified == false )   return 0;

  it = fRules.find( ruleName );
  if ( it == fRules.end() )  {
    WLOG("TRuleSystem","fetchRule") << "the demanded rule: " << ruleName
      << " does not exist." << endl;
    return 0;
  }

  tRuleAtomKey key( ruleName, it->second );
  TRuleAtom* ra = TPMRuleAtom::instance().create( key );

  return ra;
}



const list<TRuleSystem::tError>* TRuleSystem :: getErrorList() const
{
  return &fErrorList;
}



string TRuleSystem :: getModule( const string& module ) const
{
  map<string,string>::const_iterator it = fModules.find( module );
  if ( it == fModules.end() )  return "";
  return it->second;
}



bool TRuleSystem :: getStatus() const
{
  return fVerified;
}



// static method
TRuleSystem& TRuleSystem :: instance()
{
static TRuleSystem theInstance;

  return theInstance;
}



bool TRuleSystem :: load( TDataPackageList* in )
{
bool bReturn = true;

  reset();

  bReturn &= in->getAndDelete( "module_fleet", &fModules["fleet"], true );      // bUnique=true
  bReturn &= in->getAndDelete( "module_item", &fModules["item"], true );
  bReturn &= in->getAndDelete( "module_race", &fModules["race"], true );
  bReturn &= in->getAndDelete( "module_subfleet", &fModules["subfleet"], true );
  bReturn &= in->getAndDelete( "module_system", &fModules["system"], true );

  map<string, string>::iterator it;
  string temp;
  for ( it=fRules.begin(); it!=fRules.end(); it++ )  {
    bReturn &= in->getAndDelete( it->first, &temp, true );
    fRules[it->first] = temp;
  }

  return bReturn;
}



void TRuleSystem :: reset()
{
  fVerified = false;
  fErrorList.clear();

  fModules["fleet"] = "";
  fModules["item"] = "";
  fModules["race"] = "";
  fModules["subfleet"] = "";
  fModules["system"] = "";

  fRules["fleet_engine_failure"] = "";
  fRules["fleet_movement"] = "";
}



bool TRuleSystem :: save( TDataPackageList* out ) const
{
bool bReturn = true;
string* temp;
static const string sBlockType = "rulesystem";

  // additional information to write a block (this data will not be
  // read by the load method)
  bReturn &= out->add( "blocktype", &sBlockType, true, false );

  // "addCopy" instead of "add" is neccessary!
  bReturn &= out->addCopy( "module_fleet", getModule("fleet"), true );         // unique=true
  bReturn &= out->addCopy( "module_item", getModule("item"), true );
  bReturn &= out->addCopy( "module_race", getModule("race"), true );
  bReturn &= out->addCopy( "module_subfleet", getModule("subfleet"), true );
  bReturn &= out->addCopy( "module_system", getModule("system"), true );

  // Now write the individual rule atom setting to disk
  map<string, string>::const_iterator it;
  for ( it=fRules.begin(); it!=fRules.end(); it++ )  {
    bReturn &= out->add( it->first, &(it->second), true, false );
  }

  return bReturn;
}



bool TRuleSystem :: setModule( const string& module, const string& ruleset )
{
  fModules[module] = ruleset;
  fVerified = false;
  return true;
}



bool TRuleSystem :: setRuleAtom( const string& rule, const string& ruleset )
{
  fRules[rule] = ruleset;
  fVerified = false;
  return true;
}





//----------------------------------------  protected  ----------------------------------------

TRuleSystem :: TRuleSystem()
{
  reset();
}





/*
* $Log: rulesystem.cpp,v $
* Revision 1.1  2002/07/12 10:10:35  mkrohn5
* moved rulesystem.* -> gamelogic/
*
* Revision 1.26  2002/07/08 06:23:50  mkrohn5
* added comment
*
* Revision 1.25  2002/07/03 18:02:02  mkrohn5
* made use of new TDataPackageList methods
*
* Revision 1.24  2002/06/28 10:12:02  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.23  2002/06/22 18:23:14  mkrohn5
* fetchRule --> getRuleAtom
*
* Revision 1.22  2002/06/21 12:38:54  mkrohn5
* doc update + minor style changes
*
* Revision 1.21  2002/06/21 08:31:52  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.20  2002/06/05 09:29:56  mkrohn5
* bug fix in the save method which caused crashes
*
* Revision 1.19  2002/06/05 00:34:18  mkrohn5
* major changes in the rule system: int2 -> string
* also now making use of TPrototypeManager for the rule atoms
*
* Revision 1.18  2002/06/04 09:31:08  mkrohn5
* removed some unneccessary code
*
* Revision 1.17  2002/05/29 18:33:27  mkrohn5
* small bug fix
*
* Revision 1.16  2002/05/11 00:24:52  mkrohn5
* bug fix + added some log messages
*
* Revision 1.15  2002/05/10 10:41:22  mkrohn5
* number of changes due to changed TGame class
*
* Revision 1.14  2002/03/24 13:54:52  mkrohn5
* *** empty log message ***
*
* Revision 1.13  2002/02/05 00:51:26  mkrohn5
* cosmetic modification
*
* Revision 1.12  2002/02/03 23:18:53  mkrohn5
* added a method: createItem
*
* Revision 1.11  2002/01/28 23:40:20  mkrohn5
* started some work on loading items
*
* Revision 1.10  2001/12/03 01:44:52  mkrohn5
* - added module + some rule atoms
* - enhanced dependency check
*
* Revision 1.9  2001/12/01 17:24:13  mkrohn5
* fixed a few include pathes
*
* Revision 1.8  2001/11/27 10:19:06  mkrohn5
* added log messages
* fixed a few bugs
*
* Revision 1.7  2001/11/25 22:46:34  mkrohn5
* some major changes due to the addition of rule atoms
*
* Revision 1.6  2001/07/10 17:57:32  ishark
* rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
*
* Revision 1.5  2001/07/03 01:05:21  mkrohn5
* added some get methods
*
* Revision 1.4  2001/06/24 17:03:44  mkrohn5
* some fixes due to api changes
*
* Revision 1.3  2001/06/21 11:35:29  mkrohn5
* rewrote load and save methods
*
* Revision 1.2  2001/06/12 10:09:59  mkrohn5
* implemented the load & save methods
*
*/

