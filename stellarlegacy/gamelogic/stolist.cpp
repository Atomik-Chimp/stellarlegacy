// $Id: stolist.cpp,v 1.15 2002/06/07 00:38:37 mkrohn5 Exp $

// Stellar Object List Code File
// Written by: Jai Shaw, Marco Krohn

// Copyright (C) 1996 - 1999, Jai Shaw, <Jai@towersoft.com.au>
//               2000 - 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#include "gamelogic/galaxy.h"
#include "gamelogic/stobj.h"
#include "gamelogic/stolist.h"
#include "gamelogic/race.h"

using namespace std;





//----------------------------------------  Comparison Functions & Classes ----------------------------------------

bool CompareByID( const TStellarObject* x, const TStellarObject* y )
{
  return x->getID() < y->getID();
}



bool CompareByName( const TStellarObject* x, const TStellarObject* y )
{
  return x->getName() < y->getName();
}



class TCompareByDistance
{
  public:
    TCompareByDistance( TStellarObjectList& m_ref ) : ref( m_ref )
    {
    }

    bool operator()( TStellarObject* x, TStellarObject* y )
    {
      return ref.CompareByDistance( x, y );
    }

  private:
    TStellarObjectList& ref;
};





//----------------------------------------  TStellarObjectList  ----------------------------------------

TStellarObjectList :: TStellarObjectList()
{
}



TStellarObjectList :: TStellarObjectList( const TStellarObjectList& List )
{
  *this = List;                                            // calls method operator=
}



TStellarObjectList& TStellarObjectList :: Add( TStellarObject* pObject )
{
  push_back( pObject );
  return *this;
}



TStellarObjectList& TStellarObjectList :: Add( const TStellarObjectList& List )
{
TStellarObjectList::const_iterator StoStart, StoEnd, Iter;

  StoStart = List.begin();
  StoEnd = List.end();
  for ( Iter=StoStart; Iter!=StoEnd; Iter++ )
  {
    push_back( *Iter );
  }

  return *this;
}



// dEpsilon=0.001
double TStellarObjectList :: ApplyFilterMinDistance( const TPoint& Point, double dEpsilon )
{
double dMin, dDist;
TStellarObjectList::iterator Iter;
TStellarObjectList TempList;

  dMin = -1;

  // FIXME: The dEpsilon feature is missing!
  for (Iter=begin(); Iter!=end(); Iter++)
  {
    dDist = (*Iter)->getGalaxy()->getDistance( (*Iter)->getPos(), Point );
    if ( dDist<dMin || dMin==-1 )
    {
      dMin = dDist;
      // FIXME: now check which of the temp list objects are within
      // a distance of: obj_dist < dMin + dEpsilon => keep these objects
      TempList.clear();
      TempList.push_back((*Iter));
    }
    else if ( dDist < dMin+dEpsilon )
    {
      TempList.push_back( (*Iter) );
    }
  }

  clear();                                                 // deletes the whole list
  *this = TempList;

  return dMin;
}



// clear = false
int TStellarObjectList :: Filter( TStellarObjectList* newlist,
                                  const TSOLFilter& f,
                                  const bool clear ) const
{
  int4 filter_in = 0;
  TStellarObjectList::const_iterator it;

  if (clear)
    newlist->clear();

  for (it = begin(); it != end(); ++it)  {
    if ( f(**it) ) {
      filter_in++;
      newlist->push_back( (*it) );
    }
  }

  return filter_in;
}



TStellarObjectList& TStellarObjectList :: operator=( TStellarObject* pObject )
{
  clear();                                                 // deletes the whole list
  *this += pObject;
  return *this;
}



TStellarObjectList& TStellarObjectList :: operator=( const TStellarObjectList& List )
{
  clear();                                                 // deletes the whole list
  *this += List;
  return *this;
}



TStellarObjectList TStellarObjectList :: operator+( TStellarObject* pObject ) const
{
TStellarObjectList Temp;

  Temp = *this;
  Temp += pObject;
  return Temp;
}




TStellarObjectList TStellarObjectList :: operator+( const TStellarObjectList& List ) const
{
TStellarObjectList Temp;

  Temp = *this;
  Temp += List;
  return Temp;
}



TStellarObjectList& TStellarObjectList :: operator+=( TStellarObject* pObject )
{
  return Add( pObject );
}



TStellarObjectList& TStellarObjectList :: operator+=( const TStellarObjectList& List )
{
  return Add( List );
}



void TStellarObjectList :: showContent() const
{
TStellarObjectList::const_iterator it;

  LOG("TStellarObjectList","showContent") << "total: " << size() << endl;

  for ( it=begin(); it!=end(); it++ )  {
    LOG("TStellarObjectList","showContent")
      << "type: " << (*it)->getTypeName()
      << ", name: " << (*it)->getName()
      << ", owner: " << (*it)->getOwner()->getName()
      << ", creator: " << (*it)->getCreator()->getName()
      << ", pos: " << (*it)->getPos() << endl;
  }
}



void TStellarObjectList :: SortByDistance( const TPoint& Pos )
{
  fReferencePos = Pos;
  sort( TCompareByDistance(*this) );
}



void TStellarObjectList :: SortByID()
{
  sort( CompareByID );
}



void TStellarObjectList :: SortByName()
{
  sort( CompareByName );
}





//----------------------------------------  Private  ----------------------------------------

bool TStellarObjectList :: CompareByDistance( TStellarObject* x, TStellarObject* y )
{
  double dx = x->getGalaxy()->getDistance( x->getPos(), fReferencePos );
  double dy = y->getGalaxy()->getDistance( y->getPos(), fReferencePos );
  if ( dx < dy )  return true;
  return false;
}



//----------------------------------------  FILTERS  ----------------------------------------

bool TSOLFilterCreator :: operator()( TStellarObject& obj ) const
{
  return (obj.getCreator() == fCreator);
}



bool TSOLFilterOwner :: operator()( TStellarObject& obj ) const
{
  return (obj.getOwner() == fOwner);
}



bool TSOLFilterController :: operator()( TStellarObject& obj ) const
{
  return (obj.getOwner() &&
	  obj.getOwner()->getController() == fController);
}



bool TSOLFilterPosition :: operator()( TStellarObject& obj ) const
{
  if (fRadius == 0.0)
    return obj.getPos() == fPosition;
  else
    return ((obj.getPos() - fPosition).getLength() < fRadius);
}



bool TSOLFilterName ::  operator()( TStellarObject& obj ) const
{
  return obj.getName() == fName;
}



bool TSOLFilterType :: operator()( TStellarObject& obj ) const
{
  return obj.getType() == fType;
}



bool TSOLFilterAND :: operator()( TStellarObject& obj ) const
{
  return (fF1(obj) && fF2(obj));
}



bool TSOLFilterOR :: operator()( TStellarObject& obj ) const
{
  return (fF1(obj) || fF2(obj));
}





/*
 * $Log: stolist.cpp,v $
 * Revision 1.15  2002/06/07 00:38:37  mkrohn5
 * GetLength -> getLength
 *
 * Revision 1.14  2002/05/15 08:30:55  ishark
 * actionsequencer now uses lists + cosmetic fixes
 *
 * Revision 1.13  2002/05/13 23:01:56  mkrohn5
 * cosmetic mods
 *
 * Revision 1.12  2002/05/11 23:59:58  mkrohn5
 * minor modifications
 *
 * Revision 1.11  2002/03/24 18:02:38  mkrohn5
 * uppercase -> lowercase fixes
 *
 * Revision 1.10  2001/12/07 00:21:15  mkrohn5
 * - converted galaxy to the new style
 * - galaxy now uses the stellar object list (the code is now a lot more readable :-)
 * - made TStellarObjectList a list instead of a deque (makes list operations a lot faster)
 *
 * Revision 1.9  2001/12/05 00:40:47  mkrohn5
 * - some conversions XXX -> xXX
 * - implemented the basic rule "fleet movement"
 *
 * Revision 1.8  2001/12/03 01:42:08  mkrohn5
 * fixes / fixed method coding style
 *
 * Revision 1.7  2001/12/01 17:19:55  mkrohn5
 * fix due to changes in race*
 *
 * Revision 1.6  2001/10/31 20:21:03  mkrohn5
 * removed #include "common/log.h"
 *
 * Revision 1.5  2001/07/31 00:31:38  mkrohn5
 * added creator filter
 *
 * Revision 1.4  2001/07/28 15:23:11  ishark
 * added filters in stolist, more client code in sl.cpp
 *
 * Revision 1.3  2001/03/31 01:05:37  mkrohn5
 * removed test method and not needed variable
 *
 * Revision 1.2  2001/03/24 00:57:53  mkrohn5
 * added methods and changed interface
 *
 * Revision 1.1  2001/03/22 02:29:21  mkrohn5
 * addition of galaxy and stolist files and cleanup of the interface (galaxy and stolist need some more work though)
 *
 * Revision 1.1  2000/08/10 00:05:33  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.6  2000/07/04 09:18:46  mkrohn5
 * minor changes
 *
 * Revision 1.5  2000/06/26 23:43:57  mkrohn5
 * changed some methods and began changing pointers to links
 *
 * Revision 1.4  2000/06/26 23:27:42  mkrohn5
 * *** empty log message ***
 *
 * Revision 1.3  2000/05/28 22:24:48  mkrohn5
 * small changes
 *
 * Revision 1.2  2000/05/05 20:23:54  mkrohn5
 * no message
 *
 * Revision 1.1  2000/04/03 00:07:23  mkrohn5
 * no message
 *
 * Revision 1.9  2000/02/07 22:36:26  krohn
 * minor changes
 *
 * Revision 1.8  2000/01/31 00:26:36  krohn
 * changed the data type (is now a list of pointers)
 * also added several functions
 *
 * Revision 1.7  2000/01/27 23:22:24  krohn
 * added and changed some log information / changed the return value of ReleaseRef
 *
 * Revision 1.6  2000/01/19 08:19:49  jai
 * Got ref stuff working for stellar object and got stellar object list working and sorting.
 *
 * Revision 1.5  2000/01/19 04:03:37  jai
 * Added playerID and got stolist compiling
 *
 * Revision 1.4  2000/01/11 01:10:25  jai
 * ???
 *
 */
