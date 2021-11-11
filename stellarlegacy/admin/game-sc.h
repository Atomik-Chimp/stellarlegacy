// $Id: game-sc.h,v 1.3 2002/05/13 22:57:25 mkrohn5 Exp $

// Game Server Client Header File
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

#ifndef __GAME_SC_INCLUDED
#define __GAME_SC_INCLUDED

#include "admin/game.h"





//----------------------------------------  class TGameSC  ----------------------------------------

/**
* @class TGameSC
* @brief Class which provides methods which are useful for the client as well
*        as the server.
* @author Alberto Barsella <>
*         Marco Krohn <marco.krohn@gmx.de>
* @version $Id: game-sc.h,v 1.3 2002/05/13 22:57:25 mkrohn5 Exp $
*
* FIXME
*/
class TGameSC : public TGame
{
  public:
    /**
    * @return The currently active player.
    */
    TPlayer* getActivePlayer() const;
    /**
    * Loads the player order file.
    * @param playerName The name of the player which order file is going to be
    *   loaded.
    * @return @c true if the file was loaded successfully, otherwise @c false.
    */
    bool loadPlayerOrderFile( const string& playerName );
    /**
    * Loads the server master file.
    * Note: never try to load a server master file, if a game is still present.
    * The correct way is to delete the old game completely by
    * calling @ref resetAll().
    * @return @c true if the file was loaded successfully, otherwise @c false.
    */
    bool loadServerMasterFile();
    /**
    * Record an action from a player.
    * @param action The action to add to the action sequencer.
    */
    bool recordPlayerAction(TAction* action);

  protected:
    /**
    * Action sequencer used in client mode when recording the player actions
    * or by the server when loading the player orders.
    */
    TActionSequencer fActionSequencer;

    /**
    * Empty constructor.
    * @param actSeq The mode you want to start TActionSequencer with.
    *   see @ref TActionSequencer::RecordMode for details.
    * @param gameDir The path to the game directory.
    * @param gameName The name of the game.
    */
    TGameSC( bool actSeq, const string& gameDir, const string& gameName="" );

    /**
    * Creates an action and asks it to load the data package list.
    * @param block A list of datapackages which contains information about
    *   the action.
    */
    virtual void PDBAction( TDataPackageList* block );
    /**
    * Creates a fleet and asks it to load the data package list.
    * @param block A list of datapackages which contains information about
    *   the fleet.
    */
    virtual void PDBFleet( TDataPackageList* block );
    /**
    * Creates a galaxy and asks it to load the data package list.
    * @param block A list of datapackages which contains information about
    *   the galaxy.
    */
    virtual void PDBGalaxy( TDataPackageList* block );
    /**
    * Loads and sets values such as game name and current turn.
    * @param block A list of datapackages which contains information about
    *   the game.
    */
    virtual void PDBGame( TDataPackageList* block );
    /**
    * Creates a system and asks it to load the data package list.
    * @param block A list of datapackages which contains information about
    *   the system.
    */
    virtual void PDBSystem( TDataPackageList* block );
    /**
    * Sets the active player (see @a fActivePlayer).
    * @param player The new active player.
    */
    void setActivePlayer( TPlayer* player );

  private:
    /**
    * Link to the active player (either the player playing the turn or
    * the player whose order file is being loaded)
    */
    TPlayer* fActivePlayer;
};





#endif        // __GAME_SC_INCLUDED

