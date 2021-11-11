// $Id: stobj.cpp,v 1.42 2002/07/02 23:19:06 mkrohn5 Exp $

// Stellar Object Code File
// Written by: Jai Shaw, Marco Krohn

// Copyright (C) 1996 - 1999, Jai Shaw, <Jai@towersoft.com.au>
//               2000 - 2002, Marco Krohn, <marco.krohn@gmx.de>
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

#include "common/datapackage.h"
#include "gamelogic/galaxy.h"
#include "gamelogic/race.h"
#include "gamelogic/stobj.h"
#include "gamelogic/fleetaction.h"





//----------------------------------------  stream functions  ----------------------------------------

ostream& operator<<( ostream& Stream, const TStellarObject& StellarObject )
{
  return StellarObject.Write(Stream);
}





//----------------------------------------  TStellarObject  ----------------------------------------

TStellarObject :: TStellarObject() : TActionObject()
{
  LOG("TStellarObject", "TStellarObject")
    << "stellar object created." << endl;

  Galaxy.setNull();
  setPos( TPoint() );
  fWaypointList.setAutoDeleteMode( true );
}



TStellarObject :: TStellarObject( const TPoint& Pos )  : TActionObject()
{
  LOG("TStellarObject", "TStellarObject(const TPoint& Pos)")
    << "stellar object created at: " << Pos << endl;

  Galaxy.setNull();
  setPos( Pos );
  fWaypointList.setAutoDeleteMode( true );
}



TStellarObject :: ~TStellarObject()
{
  // FIXME: inform TGalaxy!

  // Note: we do not have to delete the waypoints of fWaypointList
  //       since we setAutoDeleteMode( true ) for this list.

  LOG("TStellarObject", "~TStellarObject")
    << "Removing stellar object. Name: \"" << getName() << "\", "
    << "Pos: " << getPos() << endl;
}



void TStellarObject :: addWaypoint( const TWaypoint& waypoint )
{
  LOG("TStellarObject","addWaypoint") << "adding waypoint to waypoint list." << endl;
  TWaypoint* pNew = new TWaypoint( waypoint );             // copy the waypoint
  fWaypointList.add( pNew );
}



void TStellarObject :: Attach( TStellarObject* pDest )
{
  WP.setStellarObject( pDest );
}



// virtual method
bool TStellarObject :: canPerformAction( const TAction& action )
{
  
  if ( PMAction.isType(&action,"ADD_WAYPOINT") == true )  return true;
  if ( PMAction.isType(&action,"INSERT_WAYPOINT") == true )  return true;
  if ( PMAction.isType(&action,"REMOVE_WAYPOINT") == true )  return true;
  if ( PMAction.isType(&action,"REPLACE_WAYPOINT") == true )  return true;

  return false;
}



// virtual method
bool TStellarObject :: canBeObjectInAction( const TAction& action )
{
  if ( PMAction.isType(&action,"MOVE_FLEET") == true )  return true;

  return false;
}



void TStellarObject :: Detach()
{
  if ( WP.isStellarObject() == false )  return;

  // the following line might look a bit confusing but is completly correct
  // WP.getPos() returns the position of the stellar object this object is
  // attached too. WP.SetPos( TPoint ) will then set the current position to
  // a point in space.
  WP.setPos( WP.getPos() );
}



TGalaxy* TStellarObject :: getGalaxy() const
{
  return Galaxy.getPointerToDest();
}



const string& TStellarObject :: getName() const
{
  return sName;
}



const TPoint& TStellarObject :: getPos() const
{
  return WP.getPos();
}



// virtual method
int2 TStellarObject :: getType() const
{
  return TType::UNKNOWN;                                   // should be overwritten by other classes
}



// virtual method
const string& TStellarObject :: getTypeName() const
{
static const string sTypeName = "TStellarObject";

  return sTypeName;
}



const TWaypointList* TStellarObject :: getWaypointList() const
{
  return &fWaypointList;
}



bool TStellarObject :: hasWaypoint() const
{
  if ( fWaypointList.empty() == true )  return false;
  return true;
}



bool TStellarObject :: insertWaypoint( const TWaypoint& waypoint, int2 insertPosition )
{
  TWaypointList::iterator iter;
  TWaypoint* pNew = new TWaypoint( waypoint );
  int2 actPos;

  iter = fWaypointList.begin();
  for( actPos = 0; (actPos <= insertPosition) && (iter != fWaypointList.end()); ++actPos )
    ++iter;                                                // iterate through waypoint list
  if ( actPos == insertPosition )  {                       // if posistion could be reached
       // the possibility, that the posistion is reached AND the end of the list
       // is reached, is also in this case (the waypoint is inserted as tail)
    fWaypointList.insert( iter, pNew );
    return true;
  }
  else  {                                                  // insert posistion couldn't be reached
    return false;                                          // nothing insereted
  }
}



// virtual method
bool TStellarObject :: load( TDataPackageList* in )
{
bool bReturn = true;
TDataPackageList* pList = new TDataPackageList();

  // read the object => sub list
  bReturn &= in->getAndDelete( "stellarobject", pList, true );

  // read the real data from the sub list
  bReturn &= TActionObject::load( pList );                  // load parent data
  bReturn &= Galaxy.load( pList, "galaxy_link", true );
  bReturn &= WP.load( pList, "pos", true );                 // load TWaypoint
  bReturn &= fWaypointList.load( pList, "waypoint", true );  // load TWaypointList
  bReturn &= pList->getAndDelete( "speed", &dSpeed, true );
  bReturn &= pList->getAndDelete( "name", &sName, true );            // load string

  delete pList;                                            // clean up

  // now inform TGalaxy (the stellar object registers itself)
  if ( Galaxy.isValid() == true )  {
    // this will register the object and TGalaxy::addStellarObject will also
    // call TStellarObject::setParent (which in fact does nothing).
    Galaxy->addStellarObject( this );
  }
  else  {
    // we assume that the galaxy is always loaded before its stellar objects.
    // If this is not the case we have a problem :-(
    ELOG("TStellarObject","load")
      << "galaxy object is not in place, but it should :-(" << endl;
  }

  return bReturn;
}



bool TStellarObject :: operator==( const TStellarObject& src ) const
{
  if ( getID() == src.getID() )  return true;
  return false;
}



bool TStellarObject :: operator<( const TStellarObject& src ) const
{
  if ( getID() < src.getID() )  return true;
  return false;
}



bool TStellarObject :: removeWaypoint( int2 waypointNumber )
{
  TWaypointList::iterator iter;
  int2 number;

  iter = fWaypointList.begin();
  for( number = 0; (number <= waypointNumber) && (iter != fWaypointList.end()); ++number )
    ++iter;                                     // iterate through waypoint list
  if ( number == waypointNumber )  {            // if the waypoint with the chosen number was found
    return fWaypointList.remove( *iter );       // remove the waypoint
  }
  else  {                                       // if the waypoint with this number doesn't exist
    return false;                               // nothing removed
  }
}



bool TStellarObject :: replaceWaypoint( const TWaypoint& Waypoint, int2 waypointNumber )
{
  bool removed = removeWaypoint( waypointNumber );
  if ( removed == false )  {                               // if the waypoint couldn't be removed
    return false;
  }
  else  {
    return insertWaypoint( Waypoint, waypointNumber );     // should always succeed
  }
}



// virtual method
bool TStellarObject :: save( TDataPackageList* out ) const
{
bool bReturn = true;

  TDataPackageList* pList = new TDataPackageList();             // create a new datapackage list
  // bAutoDelete=true so that pList is deleted sometime
  bReturn &= out->add( "stellarobject", pList, true, true );

  // add the data packages to the new list
  bReturn &= TActionObject::save( pList );                      // save parent data
  bReturn &= Galaxy.save( pList, "galaxy_link", true );         // save links
  bReturn &= WP.save( pList, "pos", true );                     // save TWaypoint
  bReturn &= fWaypointList.save( pList, "waypoint", true );      // save TWaypointList
  bReturn &= pList->add( "speed", &dSpeed, true, false );       // bAutoDelete=false
  bReturn &= pList->add( "name", &sName, true, false );         // save string

  return bReturn;
}



void TStellarObject :: setName( const string& sName )
{
  this->sName = sName;
}



void TStellarObject :: setPos( const TPoint& Pos )
{
  // It is not that bad if the galaxy is not yet linked. In the
  // Set parent method there is another call of Galaxy->Transform.
  if ( Galaxy.isValid() == true )
  {
    TPoint Temp = Pos;
    Galaxy->transform( Temp );                             // transforms the point
    WP.setPos( Temp );
  }
  else
  {
    WP.setPos( Pos );
  }
}



ostream& TStellarObject :: Write( ostream& Stream ) const
{
  return Stream << getID() << ", " << getName() << ", " << getPos();
}





//----------------------------------------  private  ----------------------------------------

void TStellarObject :: setParent( TGalaxy* pGalaxy )
{
  // Note that the stellar object is totaly passive and will _not_
  // request any actions by its former owner.
  Galaxy.setDest( pGalaxy );
  // Since the galaxy might have changed or set for the first time
  // we want that our point is within the galaxy.
  TPoint Pos = getPos();
  Galaxy->transform( Pos );
  setPos( Pos );
}





/*
 * $Log: stobj.cpp,v $
 * Revision 1.42  2002/07/02 23:19:06  mkrohn5
 * lower -> upper for actions
 *
 * Revision 1.41  2002/07/01 19:00:27  mkrohn5
 * stobj can occur as actions in "move_fleet"
 *
 * Revision 1.40  2002/07/01 00:09:20  mkrohn5
 * "grammer" changer due to changes structure in action.cpp/.h
 *
 * Revision 1.39  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.38  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.37  2002/06/07 00:39:55  mkrohn5
 * bug fix
 *
 * Revision 1.36  2002/06/05 10:16:12  mkrohn5
 * extended the number of performable actions for stobj, fleet
 *
 * Revision 1.35  2002/05/15 08:30:55  ishark
 * actionsequencer now uses lists + cosmetic fixes
 *
 * Revision 1.34  2002/05/11 00:24:53  mkrohn5
 * bug fix + added some log messages
 *
 * Revision 1.33  2002/05/10 10:39:49  mkrohn5
 * all kind of changes (my cvs frontend is f#%$§ up so I can not see a detailed list of changes). Have a look at the ChangeLog file to see the changes.
 *
 * Revision 1.32  2002/04/11 22:15:46  prolator
 * added replaceWaypoint
 *
 * Revision 1.31  2002/04/10 15:49:53  prolator
 * deleted second reoveWaypoint method
 *
 * Revision 1.30  2002/04/03 23:03:24  prolator
 * added first version of insert and remove waypoints
 *
 * Revision 1.29  2002/04/01 19:18:20  mkrohn5
 * mostly style fixes
 *
 * Revision 1.28  2002/03/24 18:02:38  mkrohn5
 * uppercase -> lowercase fixes
 *
 * Revision 1.27  2002/03/24 13:36:36  mkrohn5
 * mostly style changes
 *
 * Revision 1.26  2002/01/28 01:05:13  mkrohn5
 * some smaller comment changes
 *
 * Revision 1.25  2001/12/16 11:37:24  ishark
 * TLink now uses dynamic_cast<>, lots of TAction-related fixes
 *
 * Revision 1.24  2001/12/07 00:21:15  mkrohn5
 * - converted galaxy to the new style
 * - galaxy now uses the stellar object list (the code is now a lot more readable :-)
 * - made TStellarObjectList a list instead of a deque (makes list operations a lot faster)
 *
 * Revision 1.23  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.22  2001/12/03 01:42:08  mkrohn5
 * fixes / fixed method coding style
 *
 * Revision 1.21  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.20  2001/10/31 20:16:51  mkrohn5
 * removed #include "common/log.h"
 * and added method GetWaypointList
 *
 * Revision 1.19  2001/07/31 00:32:01  mkrohn5
 * moved owner, creator to TProperty
 *
 * Revision 1.18  2001/07/10 17:57:32  ishark
 * rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
 *
 * Revision 1.17  2001/06/24 16:58:13  mkrohn5
 * - redesigned some stuff (as discussed with Ralf)
 * - some major changes in the class interface
 *
 * Revision 1.16  2001/06/22 00:46:36  mkrohn5
 * fixed a few memory leaks
 *
 * Revision 1.15  2001/06/22 00:35:27  mkrohn5
 * cleaned some things up
 * added Add method for waypoints
 *
 * Revision 1.14  2001/06/21 23:49:14  mkrohn5
 * fixed bug in load method
 * removed an unneccessary include
 *
 * Revision 1.13  2001/06/21 11:28:58  mkrohn5
 * added new load & save method
 *
 * Revision 1.12  2001/06/13 00:20:27  mkrohn5
 * Started implementation  of "move" method for TStellarObject
 * and also added a list of waypoints.
 *
 * Revision 1.11  2001/06/10 23:32:41  mkrohn5
 * Load & Save do now use the TDataPackageList "stream"
 *
 * Revision 1.10  2001/05/10 23:16:15  mkrohn5
 * changed Load method (now using TDataPackageList as input)
 *
 * Revision 1.9  2001/04/27 01:18:38  mkrohn5
 * added "const" to a string
 *
 * Revision 1.8  2001/04/26 00:05:07  mkrohn5
 * changes a return value from "string" to "const string&"
 *
 * Revision 1.7  2001/04/17 18:59:36  mkrohn5
 * added owner & creator race
 *
 * Revision 1.6  2001/04/11 22:59:19  mkrohn5
 * added working load & save methods
 *
 * Revision 1.5  2001/04/04 00:40:09  mkrohn5
 * fixed a minor bug (constructor of TLinkable was not called)
 *
 * Revision 1.4  2001/03/31 01:04:25  mkrohn5
 * minor changes to layout
 *
 * Revision 1.3  2001/03/24 00:55:17  mkrohn5
 * small changes of log messages and change to api
 *
 * Revision 1.2  2001/03/22 02:29:21  mkrohn5
 * addition of galaxy and stolist files and cleanup of the interface (galaxy and stolist need some more work though)
 *
 * Revision 1.1  2001/03/09 02:30:38  mkrohn5
 * stobj classes added to the repository again
 *
 * Revision 1.2  2000/09/21 21:19:51  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.1  2000/08/10 00:05:33  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.8  2000/07/04 09:18:46  mkrohn5
 * minor changes
 *
 * Revision 1.7  2000/06/27 23:21:46  mkrohn5
 * changes some methods - and moved the enum { FLEET, SYSTEM, ... } to the TType class in link.h
 *
 * Revision 1.6  2000/06/26 23:27:42  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.5  2000/06/15 09:59:42  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.4  2000/05/28 22:24:48  mkrohn5
 * small changes
 *
 * Revision 1.3  2000/05/05 20:23:54  mkrohn5
 * no message
 *
 * Revision 1.2  2000/04/07 12:35:17  sfstich
 * made it compile and link with egcs 2.95 and 2.91 (also without libstdc++)
 *
 * Revision 1.1  2000/04/03 00:07:23  mkrohn5
 * no message
 */

