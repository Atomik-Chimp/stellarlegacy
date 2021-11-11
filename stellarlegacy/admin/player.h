// $Id: player.h,v 1.4 2002/05/11 23:50:45 mkrohn5 Exp $

// Player Header File
// Written by: Alberto Barsella

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

#ifndef __PLAYER_INCLUDED
#define __PLAYER_INCLUDED

#include "common/defs.h"
#include "common/link.h"


class TDataPackageList;



class TPlayer : public TLinkable
{
  public:
    enum {
      ACTIVE = 0,
      INACTIVE = 1,
      DEAD = 2
    };

    /**
    * Sets the status of the player to ACTIVE.
    */
    TPlayer( const string& name="" );
    ~TPlayer();

    /**
    * FIXME
    */
    const string& getName() const;
    int2 getStatus() const;
    virtual bool load( TDataPackageList* in );
    virtual bool save( TDataPackageList* out ) const;
    /**
    * Sets the name of the player.
    * @param name The name of the player.
    */
    void setName( const string& name );
    void setStatus( int2 status );

  private:
    /**
    * Making the copy constructor private prevents copying a player object.
    */
    TPlayer( const TPlayer& );
    /**
    * Making the operator= private prevents copying a player object.
    */
    TPlayer& operator=( const TPlayer& );

    int2 fStatus;
    string fName;
};


#endif // __PLAYER_INCLUDED
