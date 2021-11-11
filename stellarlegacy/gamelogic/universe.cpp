// $Id: universe.cpp,v 1.7 2002/05/11 23:59:58 mkrohn5 Exp $

// Galaxy Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

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

#include <string>

#include "common/datapackage.h"
#include "common/defs.h"
#include "gamelogic/galaxy.h"
#include "common/link.h"
#include "gamelogic/universe.h"

using namespace std;





//----------------------------------------  member data  ----------------------------------------

TUniverse* TUniverse::fInstance = 0;





//----------------------------------------  class TUniverse  ----------------------------------------

// virtual method
TUniverse :: ~TUniverse()
{
  reset();
}



bool TUniverse :: addGalaxy( TGalaxy* galaxy )
{
  if ( galaxy == 0 )  return false;

  string name = galaxy->getName();
  list<TGalaxy*>::iterator it = find( fGalaxies.begin(), fGalaxies.end(), galaxy );
  if ( it != fGalaxies.end() )  {
    WLOG("TUniverse","addGalaxy")
      << "galaxy " << galaxy->getName()
      << " is already an element of the universe." << endl;
    return false;
  }
  else  {
    fGalaxies.push_back( galaxy );
    LOG("TUniverse","addGalaxy") << "adding " << galaxy->getName()
      << " to the universe." << endl;
  }

  return true;
}



bool TUniverse :: addItem( TItem* item )
{
  if ( item == 0 )  return false;
  fItemList.push_back( item );
  return false;
}



const list<TGalaxy*>& TUniverse :: getGalaxies() const
{
  return fGalaxies;
}



const list<TItem*>& TUniverse :: getItems() const
{
  return fItemList;
}



// static method
TUniverse* TUniverse :: instance()
{
  if ( fInstance == 0 ) {
    fInstance = new TUniverse;
  }
  return fInstance;
}



void TUniverse :: reset()
{
list<TGalaxy*>::iterator itGalaxy;
list<TItem*>::iterator itItem;

  // also call the parent method
  TLinkable::reset();

  // and now delete everything: bye
  LOG("TUniverse","reset") << "deleting everything, bye, bye universe ..." << endl;

  LOG_BEGIN_INDENT();
  LOG("TUniverse","reset") << "deleting the galaxies ..." << endl;
  for ( itGalaxy=fGalaxies.begin(); itGalaxy!=fGalaxies.end(); itGalaxy++ ) {
    delete *itGalaxy;
  }
  fGalaxies.clear();

  LOG("TUniverse","reset") << "deleting the items ..." << endl;
  for ( itItem=fItemList.begin(); itItem!=fItemList.end(); itItem++ ) {
    delete *itItem;
  }
  fItemList.clear();
  LOG_END_INDENT();

  fInstance = 0;
}





//----------------------------------------  protected  ----------------------------------------

TUniverse :: TUniverse()
{
}





/**
* $Log: universe.cpp,v $
* Revision 1.7  2002/05/11 23:59:58  mkrohn5
* minor modifications
*
* Revision 1.6  2002/05/11 00:24:53  mkrohn5
* bug fix + added some log messages
*
* Revision 1.5  2002/05/10 10:39:49  mkrohn5
* all kind of changes (my cvs frontend is f#%$§ up so I can not see a detailed list of changes). Have a look at the ChangeLog file to see the changes.
*
* Revision 1.4  2002/03/24 13:34:31  mkrohn5
* removed unneccessary load & save methods
*
* Revision 1.3  2002/02/05 00:50:33  mkrohn5
* - added some methods concerning item handling
* - few other changes
*
* Revision 1.2  2002/02/03 23:17:51  mkrohn5
* minor changes
*
* Revision 1.1  2002/01/28 01:13:37  mkrohn5
* the universe class
*
*/
