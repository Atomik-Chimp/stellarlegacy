// $Id: universe.h,v 1.5 2002/05/10 10:39:49 mkrohn5 Exp $

// Universe Header File
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

#ifndef __UNIVERSE_INCLUDED
#define __UNIVERSE_INCLUDED

#include <map>
#include <string>

#include "common/defs.h"
#include "gamelogic/item.h"
#include "common/link.h"
#include "common/plist.h"

class TDataPackageList;
class TGalaxy;
class TObjectID;
class TStellarObject;
class TStellarObjectList;





//----------------------------------------  class TUniverse  ----------------------------------------

/**
* @class TUniverse
* @brief Contains a list of all galaxies, item lists and other global objects.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: universe.h,v 1.5 2002/05/10 10:39:49 mkrohn5 Exp $
* @see TGalaxy, TItem
*
* Note that this class is a singelton meaning that there is always @e exactly
* one instance of this class (see @ref instance).
*
* The universe object contains a list of all galaxies existing in this game.
* Also it offers a list of items which are available in this universe. All
* parts e.g. in ship designs (TShipDesign) refer to this list of items.
*/
class TUniverse : public TLinkable
{
  public:
    /**
    * Deletes all children (galaxies, items etc.).
    * @see reset
    */
    virtual ~TUniverse();

    /**
    * Adds a galaxy to the universe. This method checks if the galaxy does
    * already belong to the universe (and will ignore the command in this case).
    * Note that TUniverse takes over control of the object
    * in the sense that is responsible for deleting the memory.
    * @param galaxy The galaxy to add to the universe (only values !=0 are accepted).
    * @return @c true if the galaxy was added successfully, otherwise @c false.
    */
    bool addGalaxy( TGalaxy* galaxy );
    /**
    * Adds an item to the list of available items. Note that there is no
    * check against adding an item twice. Also note that TUniverse takes
    * over control of the object in the sense that is responsible for deleting
    * the memory.
    * @param item The new item (only values !=0 are accpeted).
    * @return @c true if the item was added successfully, otherwise @c false.
    */
    bool addItem( TItem* item );
    /**
    * @return List of all galaxies.
    */
    const list<TGalaxy*>& getGalaxies() const;
    /**
    * @return The list of items which are accessible in this universe.
    */
    const list<TItem*>& getItems() const;
    /**
    * @return The unique instance of TUniverse.
    */
    static TUniverse* instance();
    /**
    * This will reset the whole universe and delete all galaxies
    * and everything else which belongs to the universe
    * (e.g. the list of items). Use with care!!!
    */
    virtual void reset();

  protected:
    /**
    * Constructor made protected to ensure that the users of this
    * class can only create exactly one instance.
    * @see instance
    */
    TUniverse();

  private:
    /** The global (and unique) instance of TUniverse */
    static TUniverse* fInstance;

    /** all galaxies in this universe */
    list<TGalaxy*> fGalaxies;
    /** list of allowed items in this universe */
    list<TItem*> fItemList;
};





#endif        //  __UNIVERSE_INCLUDED
