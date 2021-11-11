// $Id: player.cpp,v 1.6 2002/06/28 10:12:06 mkrohn5 Exp $

// Player Code File
// Written by: Alberto Barsella
//             Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001, Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
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


#include "player.h"
#include "common/datapackage.h"



// name=""
TPlayer :: TPlayer( const string& name )
{
  LOG("TPlayer", "TPlayer") << "TPlayer object created." << endl;

  setStatus( TPlayer::ACTIVE );
  setName( name );
}



TPlayer::~TPlayer()
{
  LOG("TPlayer", "~TPlayer()") << "TPlayer::~TPlayer() called." << endl;
}



const string& TPlayer :: getName() const
{
  return fName;
}



int2 TPlayer :: getStatus() const
{
  return fStatus;
}



// virtual method
bool TPlayer::load(TDataPackageList* in)
{
bool bReturn = true;

  bReturn &= TLinkable::load( in );                        // call parent Load method

  bReturn &= in->getAndDelete( "name", &fName, true );     // unique=true

  return bReturn;
}



// virtual method
bool TPlayer::save(TDataPackageList* out) const
{
bool bReturn = true;
static const string sBlockType = "player";

  bReturn &= TLinkable::save( out );                       // call parent Save method

  // additional information to write a block (this data will not be
  // read by the load method)
  bReturn &= out->add( "blocktype", &sBlockType, true, false );

  bReturn &= out->add( "name", &fName, true, false );   // unique=true, auto_delete=false

  return bReturn;
}



void TPlayer :: setName( const string& name )
{
  fName = name;
}



void TPlayer :: setStatus( int2 status )
{
  fStatus = status;
}





/*
 * $Log: player.cpp,v $
 * Revision 1.6  2002/06/28 10:12:06  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.5  2002/06/21 08:31:57  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.4  2002/05/11 23:50:45  mkrohn5
 * added method, minor changes
 *
 * Revision 1.3  2002/05/10 10:28:55  mkrohn5
 * added status methods and some style fixes
 *
 * Revision 1.2  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.1  2001/11/04 01:33:01  mkrohn5
 * moved some files around
 *
 * Revision 1.2  2001/07/25 19:12:31  ishark
 * major additions in game/sl.cpp - skeleton of localserver
 *
 * Revision 1.1  2001/07/10 17:57:32  ishark
 * rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
 *
 */
