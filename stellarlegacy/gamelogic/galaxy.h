// $Id: galaxy.h,v 1.17 2002/05/15 08:30:55 ishark Exp $

// Galaxy Header File
// Written by: Marco Krohn, Simon Stich

// Copyright (C) 1999 - 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __GALAXY_INCLUDED
#define __GALAXY_INCLUDED

#include <iostream>
#include <string>
#include <vector>

#include "common/defs.h"
#include "common/link.h"
#include "common/point.h"
#include "gamelogic/stolist.h"

class TDataPackageList;
class TObjectID;
class TStellarObject;





//----------------------------------------  class TGalaxy  ----------------------------------------

/**
* @class TGalaxy
* @brief Management of all stellar objects for a galaxy.
* @author Marco Krohn <marco.krohn@gmx.de>
* @author Simon Stich <>
* @version $Id: galaxy.h,v 1.17 2002/05/15 08:30:55 ishark Exp $
* @see TStellarObject, TLinkable
*
* This class manages the stellar objects of a whole galaxy.
* Methods for adding, removing and searching are implemented.
* Note that a galaxy (parent) will delete all its children
* (the stellar objects).
*
* Also the galaxy contains the information about the
* "metric" of the space, that means calculating distances
* between two points in space is done by the galaxy.
* Distances will especially depend on the settings for
* wrapping ("wrapping" is just another word for gluing
* the borders of a galaxy together).
*/
class TGalaxy : public TLinkable
{
  public:
    /**
    * Initializes the galaxy object.
    * @param name The name of this galaxy.
    * @param size Size of the galaxy.
    * @param wrapX @c true enables wrapping for the x axis, @c false
    *   disables wrapping.
    * @param wrapY @c true enables wrapping for the y axis, @c false
    *   disables wrapping.
    * @param wrapZ @c true enables wrapping for the z axis, @c false
    *   disables wrapping.
    */
    TGalaxy( const string& name="", const TPoint& Size=0,
      bool wrapX=false, bool wrapY=false, bool wrapZ =false);
    /**
    * Removes all stellar objects from the array (and deletes the stellar objects)
    */
    ~TGalaxy();

    /**
    * Adds a stellar object to the galaxy. Note: after adding a stellar object
    * to a galaxy the galaxy will take care of deleting the object.
    * Note also that this method will not check for duplicate entries, thus
    * you are responsible that this does not happen.
    * @param obj The new stellar object.
    * @return @c true if the object was added succesfuly, otherwise @c false.
    */
    bool addStellarObject( TStellarObject* obj );
    /**
    * @returns The dimension of the galaxy (2 or 3).
    */
    int2 getDimension() const;
    /**
    * Calculates the shortest distance between two points. The distance
    * is not only a function of the two points but also of the galaxy
    * settings (e.g. wrap).
    * @param one Point number one.
    * @param two Point number two.
    * @returns The shortest distance between the given points.
    */
    double getDistance( const TPoint& one,
                        const TPoint& two ) const;
    /**
    * Calculates the shortest distance between two stellar objects.
    * The distance is not only a function of the two stellar objects but also
    * of the galaxy settings (e.g. wrap).
    * @param one Stellar object number one.
    * @param two Stellar object number two.
    * @returns The shortest distance between the given stellar objects.
    */
    double getDistance( const TStellarObject* one,
                        const TStellarObject* two ) const;
    /**
    * Calculates the shortest vector between two points, taking
    * into account the wrap settings for this galaxy.
    * @param from Start point.
    * @param to Emd point.
    * @returns The shortest vector between these points pointing from 'From' to 'To'.
    */
    TPoint getDistanceVector( const TPoint& from,
                              const TPoint& to ) const;
    /**
    * Calculates the shortest vector between two stellar objects, taking
    * into account the wrap settings for this galaxy. The result is a vector
    * pointing from 'pFrom' to 'pTo'.
    * @param from Stellar object number one.
    * @param to Stellar object number two.
    * @returns The shortest vector between these points pointing
    *   from @e pFrom to @e pTo.
    */
    TPoint getDistanceVector( const TStellarObject* from,
                              const TStellarObject* to ) const;
    /**
    * @return The name of this galaxy.
    */
    const string& getName() const;
    /**
    * @return The size of the galaxy.
    */
    const TPoint& getSize() const;
    /**
    * Access the list of the stellar objects present in the galaxy.
    * @return a const reference to the Stellar Objects list.
    */
    const TStellarObjectList& getStellarObjectList() const;
    /**
    * @return The total number of stellar objects within this galaxy.
    */
    int4 getTotalNumber() const;
    /**
    * @returns TType::GALAXY.
    * @see TType
    */
    virtual int2 getType() const;
    /**
    * Returns the name of this class: "TGalaxy".
    * @returns The string "TGalaxy".
    * @see TType
    */
    virtual const string& getTypeName() const;
    /**
    * Loads a TGalaxy object. Note that this method will not load any stellar
    * objects. The galaxy will add itself automatically to the universe.
    * @param in The list of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Removes a stellar object from the galaxy. The method does not only
    * remove the pointer to the object but also deletes the stellar object.
    * @param obj The object which will be removed.
    * @return @c true if object was removed, otherwise @c false.
    */
    bool remove( TStellarObject* obj );
    /**
    * Saves a TGalaxy object by adding the data packages to the list. Note that
    * this method will @e not save the stellar objects.
    * @param out The output stream of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Transforms the coordinates so that the point is within the galaxy.
    * In case the wrapping for a axis is on, the method will perform a "modulo"
    * operation. If for example the @e x size of the galaxy is 3.0 (wrap active)
    * and the x-component of the argument is 4.7 the method will change this
    * to 1.7. If the wrapping is swichted off the result for this component
    * would be 3.0 which is in the box.
    * @param point is the point which will be transformed.
    * @return @c true in case a transformation was necessary, otherwise @c false.
    * @see TGalaxy#transformCoordinate
    */
    bool transform( TPoint& point ) const;

  private:
    /** Name of this galaxy. */
    string fName;
    /** The size of the galaxy. */
    TPoint fSize;
    /** A list of stellar objects in this galaxy */
    TStellarObjectList fStObj;
    /** Wrap setting for the x-axis. */
    bool fWrapX;
    /** Wrap setting for the y-axis. */
    bool fWrapY;
    /** Wrap setting for the z-axis. */
    bool fWrapZ;

    /**
    * Removes all stellar objects from the galaxy.
    */
    void removeAll();
    /**
    * The same as @ref transformPoint just for a single coordinate.
    * @param x is the coordinate.
    * @param max is the max. value for this argument (0 is the min value).
    * @param wrap @c true = wrap is on, @c false = wrap is off.
    * @see TGalaxy#transformPoint
    */
    bool transformCoordinate( double& x, double max, bool wrap ) const;
};





#endif        // __GALAXY_INCLUDED
