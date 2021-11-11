// $Id: game.h,v 1.10 2002/08/12 20:41:28 mkrohn5 Exp $

// Game Header File
// Written by: Alberto Barsella, <>
//             Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001 - 2002, Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __GAME_INCLUDED
#define __GAME_INCLUDED

#include "common/defs.h"
#include "common/link.h"
#include "common/plist.h"
#include "gamelogic/action.h"

class TDataPackageList;
class TRuleSystem;
class TPlayer;
class TRace;





//----------------------------------------  class TGame  ----------------------------------------

/**
* @class TGame
* @brief Class for game administration.
* @author Alberto Barsella <>
*         Marco Krohn <marco.krohn@gmx.de>
* @version $Id: game.h,v 1.10 2002/08/12 20:41:28 mkrohn5 Exp $
*
* This class handles all administration specific things blabla
* FIXME
*/
class TGame
{
  /**
  * This function invokes the @ref ProcessDataBlock calls.
  */
  friend int yyparse();

  public:
    /**
    * Adds a player to the game. Note that the player is now under control of
    * TGame in the sense that TGame will take care of deleting the object.
    * @param player The player which is added to the game.
    */
    void addPlayer( TPlayer* player );
    /**
    * Adds a race to the game. Note that the race is now under control of
    * TGame in the sense that TGame will take care of deleting the object.
    * @param player The rac which is added to the game.
    */
    void addRace( TRace* race );
    /**
    * @return The directory the game data is stored in.
    */
    const string& getGameDirectory() const;
    /**
    * @return The name of the game.
    */
    const string& getGameName() const;
    /**
    * @return The list of players in this game.
    */
    const list<TPlayer*>& getPlayers() const;
    /**
    * @return The list of races in this game.
    */
    const list<TRace*>& getRaces() const;
    /**
    * @return The current turn we are in.
    */
    int4 getTurn() const;
    /**
    * Resets everything the following global objects: TUniverse, TLinkUpdate, TRuleSystem.
    * Use with care!!!
    */
    virtual void resetAll();
    /**
    * Saves the full game database to disk.
    * @return @c true if the data was stored successfully, otherwise @c false.
    */
    bool saveServerMasterFile() const;
    /**
    * Sets the name of the game (@a fGameName).
    * @param name The new name for the game.
    */
    void setGameName( const string& name );
    /**
    * Sets the current turn.
    * @param turn The current turn.
    */
    void setTurn( int4 turn );

  protected:
    /**
    * Type definition to one of the PDBFunctions.
    */
    typedef void (TGame::*tPDBFunc)(TDataPackageList* block);
    /* used by ProcessDataBlock DFA to parse the file */
    struct tTransition {
      tTransition( const string& s, int i1, int i2, tPDBFunc func )  {
        BlockType=s;
        CurrLevel=i1;
        NewLevel=i2;
        Function = func;
      }
      string BlockType;
      int CurrLevel;
      int NewLevel;
      tPDBFunc Function;
    };
    /**
    * ProcessDataBlock DFA state transition table. This contains some information
    * about the structure of the file which is going to be loaded.
    */
    list<tTransition> fTransitions;
    /**
    * The creator and owner of almost everything (planets, systems, ...).
    */
    TLink<TRace> fIluvatar;

    /**
    * Initializes the member variables (e.g. sets @a fRaces, @a fPlayers
    * to the autodelete mode to @c true).
    * @param gameDir The path to the game directory.
    * @param gameName The name of the game.
    */
    TGame( const string& gameDir, const string& gameName="" );
    /**
    * Calls @ref removeAll.
    */
    virtual ~TGame();

    /**
    * @param playerName The name of a player.
    * @return The filename of the player data file for a specific player.
    */
    string FNamePlayerData(const string& PlayerName) const;
    /**
    * @param playerName The name of a player.
    * @return The filename of the player order file for a specific player.
    */
    string FNamePlayerOrder(const string& PlayerName) const;
    /**
    * @return The filename of the server master file.
    */
    string FNameServerMaster() const;
    /**
    * @return The base filename of the universe definition file.
    */
    string FNameUniverseDefinition() const;
    /*
    * @param playerName The name of the player.
    * @return the complete path (gamedirectory + filename) to
    *   the player data file.
    */
    string FSpecPlayerData( const string& playerName ) const;
    /*
    * @param playerName The name of the player.
    * @return the complete path (gamedirectory + filename) to
    *   the player order file.
    */
    string FSpecPlayerOrder( const string& playerName ) const;
    /**
    * @return The complete path (gamedirectory + filename) to
    *   the server master file.
    */
    string FSpecServerMaster() const;
    /**
    * @return The complete path (gamedirectory + filename) to
    *   the universe definition file.
    */
    string FSpecUniverseDefinition() const;
    /**
    * @return Reads and returns the blocktype of the data package list.
    *   Note that the data package is extracted during the process.
    *   The method will return an empty string if no blocktype was found.
    */
    string getBlockType( TDataPackageList* list ) const;
    /**
    * Only needed as an interface. This method is implemented in
    * TGameCreate.
    */
    virtual void PDBAction( TDataPackageList* )  {};
    /**
    * Only needed as an interface. This method is implemented in
    * TGameCS.
    */
    virtual void PDBFleet( TDataPackageList* )  {};
    /**
    * Only needed as an interface. This method is implemented in
    * TGameCS.
    */
    virtual void PDBGalaxy( TDataPackageList* )  {};
    /**
    * Only needed as an interface. This method is implemented in
    * TGameCS and TGameCreate.
    */
    virtual void PDBGame( TDataPackageList* )  {} ;
    /**
    * FIXME
    */
    void PDBItem( TDataPackageList* block );
    /**
    * Only needed as an interface. This method is implemented in
    * TGameCS.
    */
    virtual void PDBLoadOrders( TDataPackageList* )  {};
    /**
    * FIXME
    */
    void PDBPlayer( TDataPackageList* block );
    /**
    * FIXME
    */
    void PDBRace( TDataPackageList* block );
    /**
    * FIXME
    */
    void PDBRuleSystem( TDataPackageList* block );
    /**
    * Only needed as an interface. This method is implemented in
    * TGameCS.
    */
    virtual void PDBSystem( TDataPackageList* )  {};
    /**
    * Processes a list of data packages. This method is called by the parser
    * and the main task of this method is to change the load level and call
    * the right method out of the PDB_XXX set.
    * @param block A block of game data (for more information
    *   consult the load-save RFC)
    */
    void processDataBlock( TDataPackageList* block );
    /**
    * Resets the variable @a fLoadLevel to 0.
    */
    void resetLoadLevel();

  private:
    /**
    * This counter is needed to force a certain order during the load
    * process. For instance in the server mode the first thing to read
    * is the rule system.
    */
    int2 fLoadLevel;
    /**
    * Game directory: all game files reside in this directory
    * and filenames are built with standard names based from this path
    */
    string fGameDirectory;
    /**
    * The Name of the game.
    */
    string fGameName;
    /**
    * Current turn being played.
    */
    int4 fCurrentTurn;
    /**
    * Races in the game. This list is a TPList with autodelete set to @c true
    * (see @ref TPList::setAutoDeleteMode).
    */
    TPList<TRace> fRaces;
    /**
    * Players in the game (may be less than Races - one player may
    * control multiple races). This list is a TPList with autodelete
    * set to @c true (see @ref TPList::setAutoDeleteMode).
    */
    TPList<TPlayer> fPlayers;
};





#endif        // __GAME_INCLUDED
