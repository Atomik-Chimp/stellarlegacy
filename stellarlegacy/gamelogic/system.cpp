// $Id: system.cpp,v 1.12 2002/06/28 10:12:07 mkrohn5 Exp $

// System Code File
// Written by: Marco Krohn

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

#include "gamelogic/system.h"





//----------------------------------------  class TSystem  ----------------------------------------

// Pos=0
TSystem :: TSystem( const TPoint& Pos )
  : TStellarObject( Pos )
{
  fPlanets.setAutoDeleteMode( true );                      // will also remove the planets
}



// virtual method
TSystem :: ~TSystem()
{
  // nothing to do here, since the fPlanets is of type TPList
  // and auto delete of this list is set to "true"
  // See TPList::SetAutoDelete for more information

  LOG("TSystem","~TSystem")
    << "system destructor called => will delete "
    << fPlanets.size()
    << " planet(s)" << endl;
}



// virtual method
int2 TSystem :: getType() const
{
  return TType::SYSTEM;
}



// virtual method
const string& TSystem :: getTypeName() const
{
static const string sTypeName = "TSystem";

  return sTypeName;
}



// virtual method
bool TSystem :: load( TDataPackageList* in )
{
  return TStellarObject::load( in );
}



// virtual method
bool TSystem :: save( TDataPackageList* out ) const
{
bool bReturn = true;
static const string sBlockType = "system";

  // additional information to write a block (this data will not be
  // read by the load method)
  bReturn &= out->add( "blocktype", &sBlockType, true, false );

  bReturn &= TStellarObject::save( out );                  // call the parent

  return bReturn;
}





/**
* $Log: system.cpp,v $
* Revision 1.12  2002/06/28 10:12:07  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.11  2002/05/15 08:30:55  ishark
* actionsequencer now uses lists + cosmetic fixes
*
* Revision 1.10  2001/12/05 00:40:47  mkrohn5
* - some conversions XXX -> xXX
* - implemented the basic rule "fleet movement"
*
* Revision 1.9  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.8  2001/06/24 16:53:03  mkrohn5
* minor changes due to changed stobj framework
*
*/
