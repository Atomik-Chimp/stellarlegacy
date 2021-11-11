// $Id: game-client.h,v 1.3 2002/05/13 22:56:23 mkrohn5 Exp $

// Game Client Header File
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

#ifndef __GAME_CLIENT_INCLUDED
#define __GAME_CLIENT_INCLUDED

#include "admin/game-sc.h"





//----------------------------------------  class TGameClient  ----------------------------------------

/**
* @class TGameClient
* @brief Class which provides methods which are useful for the client.
* @author Alberto Barsella <>
*         Marco Krohn <marco.krohn@gmx.de>
* @version $Id: game-client.h,v 1.3 2002/05/13 22:56:23 mkrohn5 Exp $
*
* FIXME
*/
class TGameClient : public TGameSC
{
  public:
    /**
    * Sets the game directory and the game name.
    * Also this starts the action sequencer (@ref TGameSC::fActionSequencer)
    * in executing mode.
    * @param gameDir The path to the game directory.
    * @param gameName The name of the game.
    */
    TGameClient( const string& gameDir, const string& gameName );

    /**
    * Prepares to store actions (passed by @ref recordPlayerAction).
    * If an order file already exists it is loaded and subsequent actions will
    * be appended to this file.
    * @param playerName the name of the player giving the orders.
    * @return @c true if the ActionSequencer was initialized correctly,
    *   otherwise @c false.
    */
    bool initializePlayerOrders( const string& playerName );
    /**
    * Save a recording of the player actions into the player order file.
    * @return @c true if the data was saved successfully, otherwise @c false.
    */
    bool savePlayerOrderFile() const;

  protected:
    /**
    * Loads the game name and the turn number and checks for consistency
    * with the currently loaded game.
    * @param block A list of datapackages which contains information about
    *   the game.
    */
    virtual void PDBLoadOrders( TDataPackageList* block );
};





#endif        // __GAME_CLIENT_INCLUDED

