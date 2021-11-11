// $Id: property.h,v 1.3 2001/12/03 01:40:15 mkrohn5 Exp $

// Property Header File
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

#ifndef __PROPERTY_INCLUDED
#define __PROPERTY_INCLUDED

#include "common/link.h"

class TRace;





//----------------------------------------  class TProperty  ----------------------------------------

/**
* @class TProperty
* @brief Base class for all kind of properties.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: property.h,v 1.3 2001/12/03 01:40:15 mkrohn5 Exp $
*
* Basically the TProperty class provides two links to @ref TRace called @e creator
* and @e owner. The creator link points to the race which created the object,
* while the owner link points to the race which owns the stellar object.
* The owner of a stellar object is the only one which may give orders to the
* object. The creator is responsible for modificators such as cheap engines.
* Having an owner and creator allows for example giving a fleet to another
* race while all properties of the fleet are determined by the creator.
*/
class TProperty : public TLinkable
{
  public:
    /**
    * Initializes @a Creator and @a Owner.
    */
    TProperty( TRace* Creator=0, TRace* Owner=0 );

    /**
    * @return The creator of the object.
    * @see SetCreator, GetOwner
    */
    TRace* getCreator() const;
    /**
    * @return The owner of the object.
    * @see SetOwner, GetCreator
    */
    TRace* getOwner() const;
    /**
    * Loads a TProperty object. Note that classes that are derived from
    * this class @e must call TProperty::Load explicitly to load the data
    * correctly.
    * @param in The list of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves TProperty by adding the data packages to the list. Note that
    * classes that are derived from this class @e must call TProperty::Save
    * explicitly to save the data correctly.
    * @param out The output stream of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Sets the creator of the object. (Note that the creator
    * of a object normaly never changes during game play.)
    * @param The race which creates the object.
    * @see GetCreator, SetOwner
    */
    void setCreator( TRace* creator );
    /**
    * Sets the owner of the object.
    * @param The race which owns the object.
    * @see GetOwner, SetCreator
    */
    void setOwner( TRace* owner );

  private:
    /**
    * The creator of the object.
    */
    TLink<TRace> fCreator;
    /**
    * The owner of the object.
    */
    TLink<TRace> fOwner;
};





#endif        // __PROPRERTY_INCLUDED
