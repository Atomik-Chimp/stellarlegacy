// $Id: game-create.h,v 1.2 2002/05/11 23:54:38 mkrohn5 Exp $

// Game Creation Header File
// Written by: Alberto Barsella, <>
//             Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2002 -     , Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __GAME_CREATE_INCLUDED
#define __GAME_CREATE_INCLUDED

#include "admin/game.h"





//----------------------------------------  class TGameCreate  ----------------------------------------

/**
* @class TGameCreate
* @brief Supports the creation of a new game / universe.
* @author Alberto Barsella <>
*         Marco Krohn <marco.krohn@gmx.de>
* @version $Id: game-create.h,v 1.2 2002/05/11 23:54:38 mkrohn5 Exp $
*
* FIXME
*/
class TGameCreate : public TGame
{
  public:
    /**
    * Sets the game name and game dir.
    * You have to explicitly call @ref createGame to create a new game.
    * @param gameDir The path to the game directory.
    * @param gameName The name of the game.
    */
    TGameCreate( const string& gameDir, const string& gameName );

    /**
    * Creates a new game.
    * @return @c true if the game creation was successful, otherwise @c false.
    */
    bool createGame();

  protected:
    /**
    * Creates a demo galaxy.???
    * @deprecated This is for demonstration purposes only!
    *   The real solution is to load a galaxy description file
    *   which will be realized in the TStartUp class.
    */
    virtual void PDBGame( TDataPackageList* block );
};





#endif        // __GAME_CREATE_INCLUDED
