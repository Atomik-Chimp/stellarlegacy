// $Id: fleet.cpp,v 1.30 2002/07/02 23:16:09 mkrohn5 Exp $

// Fleet Code File
// Written by: Marco Krohn <marco.krohn@gmx.de>,
//             Ralf Laue <>

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
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

#include <algorithm>

#include "common/datapackage.h"
#include "gamelogic/fleet.h"
#include "gamelogic/subfleet.h"
#include "gamelogic/fleetaction.h"




//----------------------------------------  class TFleet  ----------------------------------------

// Pos=0
TFleet :: TFleet( const TPoint& Pos )
  : TStellarObject( Pos )
{
  fSubFleets.setAutoDeleteMode( true );                    // subfleets will be deleted automaticaly
}



// virtual method
TFleet :: ~TFleet()
{
  // nothing to do here, since the fSubFleets is of type TPList
  // and auto delete of this list is set to "true"
  // See TPList::SetAutoDelete for more information

  LOG("TFleet","~TFleet")
    << "fleet destructor called => will delete "
    << fSubFleets.size()
    << " subfleet(s)" << endl;
}



// virtual method
void TFleet :: Add( TSubFleet* pSubFleet )
{
  pSubFleet->setFleet( this );         // tell the subfleet about its new parent
  #ifdef SECURE_MODE
    if ( find(fSubFleets.begin(), fSubFleets.end(), pSubFleet) != fSubFleets.end() )
    {
      ELOG("TFleet","Add") << "A sub fleet was added twice!" << endl;
    }
  #endif
  fSubFleets.push_back( pSubFleet );
}



// virtual method
bool TFleet::canBeObjectInAction( const TAction& action )
{
  if ( TStellarObject::canBeObjectInAction(action) == true )  return true;

  return false;
}



// virtual method
bool TFleet :: canPerformAction( const TAction& action )
{
  if ( TStellarObject::canPerformAction(action) == true )  return true;

  if ( PMAction.isType(&action,"MOVE_FLEET") == true )  return true;

  return false;
}



// virtual method
TOSVal TFleet :: getNumberOfShips() const
{
TOSVal sum = 0;
TPList<TSubFleet>::const_iterator it;

  for ( it=fSubFleets.begin(); it!=fSubFleets.end(); it++ )  {
    sum += (*it)->getNumberOfShips();
  }

  return sum;
}



double TFleet :: getSpeed() const
{
  return fSpeed;
}



// virtual method
int2 TFleet :: getType() const
{
  return TType::FLEET;
}



// virtual method
const string& TFleet :: getTypeName() const
{
static const string sTypeName = "TFleet";

  return sTypeName;
}



// virtual method
bool TFleet :: load( TDataPackageList* in )
{
  bool bReturn = true;
  
  bReturn &= TStellarObject::load( in );                      // call the parent
  return bReturn;                                 // return the bool for success
} // Load



// virtual method
bool TFleet :: Remove( TSubFleet* pSubFleet )
{                      // auto deletion mode = true --> subfleet will be deleted
  return fSubFleets.remove( pSubFleet );
}



// virtual method
bool TFleet :: save( TDataPackageList* out ) const
{
bool bReturn = true;
static const string sBlockType = "fleet";

  // additional information to write a block (this data will not be
  // read by the load method)
  bReturn &= out->add( "blocktype", &sBlockType, true, false );

  bReturn &= TStellarObject::save( out );                     // call the parent
  return bReturn;                                 // return the bool for success
}



void TFleet :: setSpeed( double speed )
{
  // FIXME: check via rulesystem for the max speed
  fSpeed = speed;
}



// virtual method
bool TFleet :: TransferSubFleet( TSubFleet* pSubFleet, TFleet* pNewFleet )
{                                              // set auto deletion mode off -->
  fSubFleets.setAutoDeleteMode( false );     // only link to subfleet is removed
  if ( fSubFleets.remove(pSubFleet) )                  // try to remove subfleet
  {                                                             // if successful
    fSubFleets.setAutoDeleteMode( true );           // set auto delete mode back
    if ( pNewFleet != 0 )           // check whether pNewFleet points to a fleet
    {                                                                  // if yes
      pNewFleet->Add( pSubFleet );      // tell new fleet about its new subfleet
      pSubFleet->setFleet( pNewFleet );  // inform subfleet about its new parent
      return true;                    // fleet change successful --> return true
    }
    else                                                      // if no --> error
    {
      Fatal( "TSubFleet", "MoveSubFleets", "Pointer to new fleet is 0!" );
      return false;                           // this line will never be reached
    }
  }

  // removal not successful
  fSubFleets.setAutoDeleteMode( true );              // set auto dlete mode back
  return false;                  // fleet change not successful --> return false
} // MoveSubFleet





/*
* $Log: fleet.cpp,v $
* Revision 1.30  2002/07/02 23:16:09  mkrohn5
* lower -> upper for actions
*
* Revision 1.29  2002/07/01 00:09:20  mkrohn5
* "grammer" changer due to changes structure in action.cpp/.h
*
* Revision 1.28  2002/06/28 10:12:07  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.27  2002/06/25 23:07:54  mkrohn5
* changes to make it compile again
*
* Revision 1.26  2002/06/07 10:03:55  mkrohn5
* fixed the constant speed bug
*
* Revision 1.25  2002/06/07 00:35:11  mkrohn5
* added setSpeed method
*
* Revision 1.24  2002/06/05 11:24:12  mkrohn5
* calling the ruleatom for fleetmovement and give the fleet some (artifical) initial speed
*
* Revision 1.23  2002/06/05 10:16:11  mkrohn5
* extended the number of performable actions for stobj, fleet
*
* Revision 1.22  2002/05/15 08:30:55  ishark
* actionsequencer now uses lists + cosmetic fixes
*
* Revision 1.21  2002/05/11 23:51:26  mkrohn5
* reverted Get->get changes
*
* Revision 1.20  2002/04/02 22:33:45  prolator
* some Xet to xet
*
* Revision 1.19  2002/04/01 19:14:08  mkrohn5
* removed some unneccessary code
*
* Revision 1.18  2002/01/28 00:57:09  mkrohn5
* minor changes
*
* Revision 1.17  2001/12/16 11:37:24  ishark
* TLink now uses dynamic_cast<>, lots of TAction-related fixes
*
* Revision 1.16  2001/12/05 00:40:47  mkrohn5
* - some conversions XXX -> xXX
* - implemented the basic rule "fleet movement"
*
* Revision 1.15  2001/12/03 01:35:10  mkrohn5
* cleaned up the fleet interface
*
* Revision 1.14  2001/12/02 14:21:59  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.13  2001/10/31 20:15:09  mkrohn5
* removed #include "common/log.h"
*
* Revision 1.12  2001/07/10 17:57:32  ishark
* rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
*
* Revision 1.11  2001/06/24 16:46:45  mkrohn5
* - changed the order of some methods
* - changed the destructor
* - updated to new stellar object API
*
* Revision 1.10  2001/06/24 14:13:47  prolator
* fixed write mistakes
*
* Revision 1.9  2001/06/24 13:58:36  mkrohn5
* resolved conflict
*
* Revision 1.8  2001/06/23 23:29:10  prolator
* moved GetNumberOfShips to TFleet
*
* Revision 1.7  2001/06/23 19:55:21  prolator
* added Load and Save
*
* Revision 1.6  2001/06/21 11:26:16  mkrohn5
* implemented save method (using blocktype)
*
* Revision 1.5  2001/05/10 23:19:40  mkrohn5
* basic framework for subfleets
*
*/

