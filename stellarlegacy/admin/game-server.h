// $Id: game-server.h,v 1.3 2002/05/13 22:57:54 mkrohn5 Exp $

// Game Server Header File
// Written by: Alberto Barsella, <>
//             Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2002 - , Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __GAME_SERVER_INCLUDED
#define __GAME_SERVER_INCLUDED

#include "admin/game-sc.h"





//----------------------------------------  class TGameServer  ----------------------------------------

/**
* @class TGameServer
* @brief Making turn generation easy.
* @author Alberto Barsella <>,
*         Marco Krohn <marco.krohn@gmx.de>
* @version $Id: game-server.h,v 1.3 2002/05/13 22:57:54 mkrohn5 Exp $
*
* FIXME
*/
class TGameServer : public TGameSC
{
  public:
    /**
    * Sets the directory and the name of the game.
    * Also this starts the action sequencer (@ref TGameSC::fActionSequencer)
    * in non-executing mode.
    * @param gameDir The path to the game directory.
    * @param gameName The name of the game.
    */
    TGameServer( const string& gameDir, const string& gameName );
    /**
    * Does nothing at the moment.
    * FIXME: perhaps it should reset TUniverse & TRuleSystem???
    */
    virtual ~TGameServer();

    /**
    * Generates a backup copy of all important files.
    * @return @c true always (FIXME).
    */
    bool backupGameFiles() const;
    /**
    * This will generate additional actions (e.g. for fleet movement etc.)
    * and will then start executing all actions.
    */
    void executeActions();
    /**
    * Increments the turn number by one.
    */
    void incrementTurn();
    /**
    * Loads the order files from all players.
    * @return @c true if all files were loaded correctly, @c false otherwise
    *   (if there are missing or broken files etc.)
    */
    bool loadPlayerOrderFiles();
    /**
    * Saves the player data files to disk.
    * @return @c true if the data was saved successfully, otherwise @c false.
    */
    bool savePlayerDataFiles() const;

  protected:
    /**
    * Loads the game name and the turn number and checks for consistency
    * with the currently loaded game.
    * @param block A list of datapackages which contains information about
    *   the game.
    */
    virtual void PDBLoadOrders( TDataPackageList* block );

  private:
    void addStandardActions();
};





#endif        // __GAME_SERVER_INCLUDED

