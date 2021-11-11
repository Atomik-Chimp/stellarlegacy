// $Id: sl.cpp,v 1.45 2002/07/12 10:08:02 mkrohn5 Exp $

// Main File
// Written by: Marco Krohn

// Copyright (C) 1999 - 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#include <iostream>
#include <string>

#include "common/defs.h"
#include "admin/game.h"
#include "admin/game-client.h"
#include "admin/game-create.h"
#include "admin/game-server.h"
#include "admin/player.h"
#include "common/random.h"
#include "gamelogic/galaxy.h"
#include "gamelogic/stobj.h"
#include "gamelogic/fleet.h"
#include "gamelogic/stolist.h"
#include "gamelogic/universe.h"

#include "gamelogic/fleetaction.h"

using namespace std;





//----------------------------------------  Prototypes  ----------------------------------------

int parseArguments( int argc, char* argv[] );
void printUsageDescription();
bool runTestScripts();
void startLocalServer();





//----------------------------------------  Main Function  ----------------------------------------

int main( int argc, char* argv[] )
{
int iReturn;

  cout << "This is Stellar Legacy - Version " << VERSION << endl << endl;

  if ( argc == 1 )  {
    printUsageDescription();
    exit( 0 );
  }

  #ifdef LOG_ENABLED
    LOG("-", "main(int, char*[])") << "This is Stellar Legacy - Version " << VERSION << endl
      << endl
      << "The log system is enabled. The log file is called log.out" << endl;
    cout << "The log system is enabled. The log file is called log.out" << endl;
  #else
    cout << "The log system is disabled." << endl
      << "Note: this simply means that SL will not produce a log file." << endl;
  #endif

  TRandom::initialize();
  LOG("-", "main(int, char*[])") << "Random number init: " << TRandom::getInitNumber() << endl;

  iReturn = parseArguments( argc, argv );

  LOG("-", "main(int, char*[])") << "Main function return value: " << iReturn << endl
    << "---------------------------------------" << endl
    << "Destructor calls from global objects:" << endl;

  return iReturn;
}



int parseArguments( int argc, char* argv[] )
{
int i, iReturn = 0;
string sParameter, sPort, sHost;

  i = 1;
  sParameter = argv[i];
  if ( sParameter=="--testing" || sParameter=="-t" )  {
    if ( runTestScripts() == false )  return 1;
    i++;
    if ( i < argc )  sParameter = argv[i];
  }

  if ( i < argc )  {
    if ( sParameter=="--server" || sParameter=="-s" )  {
      i++;
      if ( i < argc )  sPort = argv[i];
      // Interface to Piers server program
      // ...
    }
    else if ( sParameter=="--client" || sParameter=="-c" )  {
      i++;
      if ( i < argc )  sHost = argv[i];
      i++;
      if ( i < argc )  sPort = argv[i];
      cerr << "Sorry, there is no client at the moment" << endl;
    }
    else if ( sParameter=="--localserver" || sParameter=="-l" )  {
      startLocalServer();
    }
    else  {
      cerr << endl << "unknown parameter: \"" << sParameter << "\""<< endl << endl;
      printUsageDescription();
    }
  }

  return iReturn;
}



void printUsageDescription()
{
  cerr << "usage:" << endl;
  cerr << endl;
  cerr << "sl --testing" << endl;
  cerr << "sl [--testing] --server [port]" << endl;
  cerr << "sl [--testing] --client [host] [port]" << endl;
  cerr << "sl [--testing] --localserver" << endl;
  cerr << endl;
  cerr << "Abbreviations: -c = --client" << endl;
  cerr << "               -l = --localserver" << endl;
  cerr << "               -s = --server" << endl;
  cerr << "               -t = --testing" << endl;
}



bool generateNewGame( const string& gameDir )
{
  bool ret = true;

  cout << "Generating new game...." << endl;
  TGameCreate* create = new TGameCreate( gameDir, "no-one" );

  if ( create->createGame() == true )  {
    cout << "game successfully created!" << endl;
    cout << "saving server master file ..." << endl;
    ret &= create->saveServerMasterFile();
    delete create;                                         // cleaning up

    cout << "and now starting the game server ... " << endl;
    TGameServer* server = new TGameServer( gameDir, "no-one" );
    cout << "load the server master file ... " << endl;
    ret &= server->loadServerMasterFile();
    cout << "creating player data files ..." << endl;
    ret &= server->savePlayerDataFiles();
    delete server;
  }
  else  {
    delete create;
    ret = false;
  }

  return ret;
}



bool playTurnFleetMenu( TGameClient* client )
{
TStellarObjectList SOList;
TStellarObjectList::iterator it;
int4 num, selected;
char cInput;
TAction* action;

  cout << "AVAILABLE FLEETS:" << endl;

  // get list of fleets owned by the player
  // we simply use the first galaxy here (note that an universe can consist of more than one galaxy)
  TGalaxy* galaxy = *(TUniverse::instance()->getGalaxies()).begin();

  if ( galaxy->getStellarObjectList().Filter(&SOList, TSOLFilterAND(TSOLFilterType(TType::FLEET), TSOLFilterController(*client->getActivePlayer()))) )
  {
    // show list of fleets to player and ask for the fleet #
    for (num = 0, it = SOList.begin(); it != SOList.end(); ++it, num++)
      cout << num << ". " << (*it)->getName() << "  id=" << (*it)->getID() << endl;

    if (num == 1)
      selected = 1;
    else
      do {
        cout << "Fleet #";
        cin >> selected;
      } while (selected < 0 || selected > num);

    // fetch pointer
    for (it = SOList.begin(); selected; ++it, selected--);
    TFleet& myfleet = *((TFleet*) *it);

    do {
      // show info about fleet
      cout << endl << "SELECTED FLEET: " << myfleet.getName()
           << " at position " << myfleet.getPos() << endl;

      // ask for action to be performed
      cout << endl << "<l>ist waypoints, <s>et waypoint (q)uit" << endl << "> ";
      cin >> cInput;

      // only action: set waypoint, ask for destination
      action = 0;
      switch(cInput) {
        case 'l':
          // fetch the waypoints and print them
          if (myfleet.hasWaypoint()) {
            const TWaypointList* wl = myfleet.getWaypointList();
            TWaypointList::const_iterator wi;

            for (wi = wl->begin(); wi != wl->end(); ++wi) {
              if ((*wi)->isStellarObject())
                cout << "Go to: " << (*wi)->getStellarObject()->getName() << endl;
              else
                cout << "Go to position " << (*wi)->getPos() << endl;
            }
          } else
            cout << myfleet.getName() << ": empty waypoint list" << endl;
          break;

        case 's':
          if ( !(action = PMAction.create("ADD_WAYPOINT")) )
            Fatal("-Client-", "PlayTurnFleetMenu", "unable to create a 'add waypoint' action", -1);

          double dx, dy;
          int2 warp;
          cout << "Enter destination as x y (NO COMMA)" << endl << "> ";
          cin >> dx >> dy;
          // check range blah blah

          cout << "Enter warp speed" << endl << "> ";
          cin >> warp;                                    
          // check range blah blah

          // generate the action
          TActionAddWaypoint* actionWP = dynamic_cast<TActionAddWaypoint*>(action);
          actionWP->setCreator( myfleet.getOwner() );
          actionWP->setActor( &myfleet );
          actionWP->setWaypoint( TWaypoint(TPoint(dx,dy),warp) );

          break;
      }

      if (action) {
        // add action to Game's action sequencer
        // (which implies execute action)
        if ( client->recordPlayerAction(action) == false )
          cout << "ERROR executing the action!!!! (try again?)" << endl;
        else
          cout << "Ok, action was executed just fine." << endl;
      }
    } while (cInput != 'q');

  }
  else  {
    cout << client->getActivePlayer()->getName() << ", you don't have any fleets!" << endl;
  }

  return true;
}



bool playTurn(const string& gameDir, const string& playerName )
{  
bool ret = false;
bool finished = false;
char cInput;


  cout << "Loading turn file...." << endl;
  TGameClient* client = new TGameClient( gameDir, playerName );

  if ( client->loadServerMasterFile() == true)  {
    if ( client->initializePlayerOrders(playerName) == true )  {
      ret = true;
      cout << "Playing turn...." << endl;

      while (!finished) {
        cout << "(f)leet orders ..... (s)ave and quit or just (q)uit" << endl
             << "> ";
        cin >> cInput;

        switch(cInput) {
          case 'f':
            playTurnFleetMenu( client );
            break;
          case 's':
            cout << "Saving orders....." << endl;
            client->savePlayerOrderFile();
            finished = true;
            break;
          case 'q':
            finished = true;
            break;
        }
      }
    }
    else {                                                 // could not initializePlayerOrders
      cout << "could not init player, please check if " << playerName
        << " is really a player in this game" << endl;
    }
  }

  delete client;
  return ret;
}



bool generateTurn( const string& gameDir )
{
bool ret = false;

  TGameServer* server = new TGameServer( gameDir, "server" );

  if ( server->loadServerMasterFile() == true )  {
    cout << "loading player orders file ... " << endl;
    server->loadPlayerOrderFiles();                        // loads all order files
    cout << "backup of the game files ... " << endl;
    server->backupGameFiles();                             // create a backup copy of the files

    server->incrementTurn();
    cout << "executing the actions ... " << endl;
    server->executeActions();

    cout << "saving the server master file ... " << endl;
    server->saveServerMasterFile();
    cout << "saving the player data files ... " << endl;
    server->savePlayerDataFiles();

    ret = true;
  }

  delete server;

  return ret;
}



void startLocalServer()
{
  char cInput;
  string sGameDir;
  string sPlayerName;
  bool finished = false;

  cout << endl << "Enter your player name [default = Marco]" << endl << "> ";
  getline(cin, sPlayerName, '\n');
  if (!sPlayerName.length())  sPlayerName = "Marco";
//    sPlayerName = "Test Player";


  cout << endl << "Enter game identificator/directory [default = testgame]" << endl << "> ";
  getline(cin, sGameDir, '\n');
  if (!sGameDir.length())
    sGameDir = "testgame";

  while (!finished) {
    cout << endl << "GAME DIRECTORY: " << sGameDir << endl 
         << "PLAYER: " << sPlayerName << endl;
    cout << "(l)oad server master file and generate turn   (server)" << endl
         << "(p)lay turn                                   (client)" << endl
         << "(c)reate game                                 (create)" << endl
         << "(q)uit" << endl << "> ";
    cin >> cInput;

    switch(cInput) {
      case 'l':
        if ( generateTurn(sGameDir) == true )
          cout << "Turn successfully generated!" << endl;
        else
          cout << "ERROR generating turn!" << endl;
        break;

      case 'p':
        if ( playTurn(sGameDir, sPlayerName) == true )
          cout << "Turn successfully played!" << endl;
        else
          cout << "ERROR playing turn! (make sure your player name is in the game)" << endl;
        break;

      case 'c':
        if ( generateNewGame(sGameDir) )
          cout << "Game successfully generated!" << endl;
        else
          cout << "ERROR generating game! (make sure that GAME DIR/universe-definition.sl exists)" << endl;
          break;

      case 'q':
        finished = true;
    }
  }
}





/*
* $Log: sl.cpp,v $
* Revision 1.45  2002/07/12 10:08:02  mkrohn5
* *** empty log message ***
*
* Revision 1.44  2002/07/08 06:28:58  mkrohn5
* TAction_XXX -> TActionXXX
*
* Revision 1.43  2002/07/03 11:59:39  mkrohn5
* - ActionAddWa.. -> Action_AddWa...
* - change in makefile.am: testing is compiled last
*
* Revision 1.42  2002/07/02 23:19:25  mkrohn5
* compile fix
*
* Revision 1.41  2002/07/01 20:52:23  ishark
* fixes in act-to-cpp and related stuff
*
* Revision 1.40  2002/07/01 00:09:53  mkrohn5
* "grammer" changes due to changed structure in action.cpp/.h
*
* Revision 1.39  2002/06/28 10:12:02  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.38  2002/06/22 23:15:37  mkrohn5
* bug fix - fleet selection did not work correctly
*
* Revision 1.37  2002/06/21 08:31:52  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.36  2002/05/13 23:03:30  mkrohn5
* removed debug output
* activated server
*
* Revision 1.35  2002/05/12 01:17:24  mkrohn5
* - moved some methods around
* - the client now is able to load the old actions
*
* Revision 1.34  2002/05/11 23:59:58  mkrohn5
* minor modifications
*
* Revision 1.33  2002/05/11 10:40:42  mkrohn5
* more bugfixes
*
* Revision 1.32  2002/05/10 23:46:08  mkrohn5
* edited some strings
*
* Revision 1.31  2002/05/10 10:41:22  mkrohn5
* number of changes due to changed TGame class
*
* Revision 1.30  2002/04/01 21:43:30  mkrohn5
* bugfix which prevented a call to saveAttributes
*
* Revision 1.29  2002/04/01 19:20:10  mkrohn5
* made it a lot easier to add data to an action
*
* Revision 1.28  2002/03/24 18:06:51  mkrohn5
* uppercase -> lowercase fixes
*
* Revision 1.27  2001/12/16 11:37:22  ishark
* TLink now uses dynamic_cast<>, lots of TAction-related fixes
*
* Revision 1.26  2001/12/09 13:25:41  ishark
* minor fixes in game.cpp and sl.cpp
*
* Revision 1.25  2001/12/07 00:21:15  mkrohn5
* - converted galaxy to the new style
* - galaxy now uses the stellar object list (the code is now a lot more readable :-)
* - made TStellarObjectList a list instead of a deque (makes list operations a lot faster)
*
* Revision 1.24  2001/12/05 00:40:47  mkrohn5
* - some conversions XXX -> xXX
* - implemented the basic rule "fleet movement"
*
* Revision 1.23  2001/12/04 00:37:50  mkrohn5
* ooops, that actually should go in yesterday :-(
*
* Revision 1.22  2001/12/02 14:33:45  mkrohn5
* NULL -> 0
*
* Revision 1.21  2001/11/08 21:13:54  ishark
* action uses new method names, additions in sl/race/game
*
* Revision 1.20  2001/11/06 18:14:18  mkrohn5
* removed unnecessary include
*
* Revision 1.19  2001/11/04 02:18:31  mkrohn5
* moved some files around
*
* Revision 1.18  2001/11/02 02:12:07  mkrohn5
* fixed possible crash (see global.cpp, logout for details)
*
* Revision 1.17  2001/10/31 20:23:52  mkrohn5
* some smaller corrections due to Log
*
* Revision 1.16  2001/08/03 19:42:06  ishark
* fixed function/file names to reflect RFCLoadSave
*
* Revision 1.15  2001/07/31 00:32:50  mkrohn5
* replaced tabs by spaces
*
* Revision 1.14  2001/07/28 15:23:11  ishark
* added filters in stolist, more client code in sl.cpp
*
* Revision 1.13  2001/07/25 19:12:31  ishark
* major additions in game/sl.cpp - skeleton of localserver
*
* Revision 1.12  2001/07/10 17:57:32  ishark
* rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
*
* Revision 1.11  2001/07/03 01:03:49  mkrohn5
* added log section at eof
*
*/
