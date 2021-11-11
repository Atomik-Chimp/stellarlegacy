// $Id: stolist.h,v 1.7 2002/05/11 23:59:58 mkrohn5 Exp $

// Stellar Object List Header File
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

#ifndef __STELLAR_OBJECT_LIST_INCLUDED
#define __STELLAR_OBJECT_LIST_INCLUDED

#include <algorithm>
#include <list>
#include <string>

#include "common/point.h"
#include "gamelogic/race.h"

class TGalaxy;
class TObjectID;
class TStellarObject;
class TSOLFilter;
class TPlayer;




//----------------------------------------  class TStellarObjectList  ----------------------------------------

/**
* @class TStellarObjectList
* @brief A list of stellar objects which can be sorted, merged, filtered etc.
* @author Jai Shaw <Jai@towersoft.com.au>, Marco Krohn <marco.krohn@gmx.de>
* @version $Id: stolist.h,v 1.7 2002/05/11 23:59:58 mkrohn5 Exp $
* @see TStellarObject
*
* FIXME: description of class
*/
class TStellarObjectList : public list<TStellarObject*>
{
  public:
    friend class TCompareByDistance;

    /**
    * Empty constructor.
    */
    TStellarObjectList();
    /**
    * The copy constructor.
    */
    TStellarObjectList( const TStellarObjectList& List );

    /**
    * Adds a stellar object to the list.
    * @param pObject The stellar object to add.
    * @return The new stellar object list.
    */
    TStellarObjectList& Add( TStellarObject* pObject );
    /**
    * Adds a list of stellar objects to the list.
    * @param List The list of stellar object to add.
    * @return The new stellar object list.
    */
    TStellarObjectList& Add( const TStellarObjectList& List );
    /**
    * Calculates for each stellar object the distance to a given
    * point and keeps only the nearest objects in the list. If several
    * objects have the same (min) distance they all stay in the list.
    * @param Point Reference point to which the distance is measured.
    * @param dEpsilon Due to rounding errors it might happen that objects which
    *   actually have the same distance have different distances. This parameter
    *   gives a certain tolerance such that all objects with
    *   @e distance <  @e min_dist + @e dEpsilon stay in the list.
    *   FIXME: this feature is not yet implemented, but it should!
    * @return The distance from the point to the closest object, or if the
    *   list is empty -1.
    */
    double ApplyFilterMinDistance( const TPoint& Point, double dEpsilon=0.001 );
    /**
     * Apply a filter to a list and create a new (filtered) list.
     * @param newlist pointer to the list where the result will be stored.
     * @param f filter to be applied.
     * @param clear whenether to clear or not "newlist" before adding the
     *        filter result.
     * @ return then number of elements which satisfied the filter.
     */
    int Filter( TStellarObjectList* newlist, const TSOLFilter& f, const bool clear = false ) const;

    TStellarObjectList& operator=( TStellarObject* pObject );
    TStellarObjectList& operator=( const TStellarObjectList& List );
    TStellarObjectList operator+( TStellarObject* pObject ) const;
    TStellarObjectList operator+( const TStellarObjectList& List ) const;
    /**
    * Adds a stellar object to the list.
    * The same as @ref #Add.
    * @param pObject The stellar object to add.
    * @return The new stellar object list.
    */
    TStellarObjectList& operator+=( TStellarObject* pObject );
    /**
    * Adds a list of stellar objects to the list.
    * The same as @ref #Add.
    * @param List The list of stellar object to add.
    * @return The new stellar object list.
    */
    TStellarObjectList& operator+=( const TStellarObjectList& List );
    /**
    * For debugging only!
    * Writes the stellar objects to the LOG stream.
    */
    void showContent() const;
    /**
    * Uses the distance to a given point to sort the list by distance.
    * @param Pos The reference position.
    */
    void SortByDistance( const TPoint& Pos );
    /**
    * Sorts the list by ID (FIXME ascending?).
    */
    void SortByID();
    /**
    * Sorts the list by name (FIXME ascending?).
    */
    void SortByName();
    /**
    * Sorts the list by type.
    */
    void SortByType();

  private:
    /** FIXME */
    TPoint fReferencePos;

    /**
    * Calculates the distance of both stellar objects to the
    * reference point @a ReferencePos and returns @c true if
    * @e x is closer to the reference point than @e y, otherwise
    * @c false.
    */
    bool CompareByDistance( TStellarObject* x, TStellarObject* y );
};



class TSOLFilter {
  public:
    virtual ~TSOLFilter() {};
    virtual bool operator()( TStellarObject& obj ) const = 0;
};


class TSOLFilterCreator : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterCreator(const TRace& creator) : fCreator(&creator) {};

  private:
    const TRace* fCreator;
};



class TSOLFilterOwner : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterOwner(const TRace& own) : fOwner(&own) {};

  private:
    const TRace* fOwner;
};


class TSOLFilterController : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterController(const TPlayer& control) : fController(&control) {};

  private:
    const TPlayer* fController;
};


class TSOLFilterPosition : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterPosition(const TPoint& pos, double radius = 0) : 
      fPosition(pos), fRadius(radius) {};

  private:
    TPoint fPosition;
    double fRadius;
};


class TSOLFilterName : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterName(const string& name) : fName(name) {} ;

  private:
    string fName;
};


class TSOLFilterType : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterType(const int2 type) : fType(type) {} ;

  private:
    const int2 fType;
};


class TSOLFilterAND : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterAND(const TSOLFilter& f1, const TSOLFilter& f2) : fF1(f1), fF2(f2) {} ;

  private:
    const TSOLFilter& fF1;
    const TSOLFilter& fF2;
};


class TSOLFilterOR : public TSOLFilter {
  public:
    bool operator()( TStellarObject& obj ) const;
    TSOLFilterOR(const TSOLFilter& f1, const TSOLFilter& f2) : fF1(f1), fF2(f2) {} ;

  private:
    const TSOLFilter& fF1;
    const TSOLFilter& fF2;
};





#endif        // __STELLAR_OBJECT_LIST_INCLUDED
