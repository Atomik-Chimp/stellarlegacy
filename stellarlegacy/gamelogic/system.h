// $Id: system.h,v 1.9 2002/05/15 08:30:55 ishark Exp $

// System Header File
// Written by: Marco Krohn

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __SYSTEM_INCLUDED
#define __SYSTEM_INCLUDED

#include "gamelogic/planet.h"
#include "common/plist.h"
#include "gamelogic/stobj.h"

class TDataPackageList;
class TPlanet;





//----------------------------------------  class TSystem  ----------------------------------------

/**
* @class TSystem
* @brief The general interface for systems.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: system.h,v 1.9 2002/05/15 08:30:55 ishark Exp $
* @see TStellarObject, TSystemBasic
*
* FIXME
*/
class TSystem : public TStellarObject
{
  public:
    TSystem( const TPoint& Pos=0 );
    virtual ~TSystem();

    /**
    * @return The type of the stellar object, here: TType::SYSTEM.
    * @see TType
    */
    virtual int2 getType() const;
    /**
    * @return The name of the class: "TSystem".
    */
    virtual const string& getTypeName() const;
    /**
    * Loads a system from a list of data package.
    * @param in The input "stream" of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a system to a list of data package.
    * @param in The output "stream" of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;

  protected:
    TPList<TPlanet> fPlanets;
};





#endif        // __SYSTEM_INCLUDED
