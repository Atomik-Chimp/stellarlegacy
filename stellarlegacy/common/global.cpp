// $Id: global.cpp,v 1.13 2002/06/24 23:42:07 mkrohn5 Exp $

// Global Code File

// Copyright (C) 1999 - 2001, Marco Krohn, marco.krohn@gmx.de
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

#include "common/global.h"

#include <iostream>

using namespace std;





//----------------------------------------  Misc. Functions  ----------------------------------------

// iExitCode=-1
void Fatal( const string& sClassName, const string& sMethodName,
  const string& sMessage, int iExitCode )
{
  cerr << "The fatal function was called! See log.out for details" << endl;
  ELOG("-","Fatal")
    << "The Fatal function has been called, so there is some serious trouble :-(" << endl
    << "The fatal call was initiated in class: " << sClassName << ", method: " << sMethodName << endl
    << "and the message is: " << endl
    << sMessage << endl;
  exit( iExitCode );
}



int Round(double dValue)
{
  if ( dValue > 0 )  return int( dValue + 0.5 );
  return int( dValue - 0.5 );
}





/*
* $Log: global.cpp,v $
* Revision 1.13  2002/06/24 23:42:07  mkrohn5
* some design improvement concerning log
*
* Revision 1.12  2002/06/23 15:50:48  ishark
* added act-to-cpp tool, fixes in TActionSequencer, gcc3 fixes
*
* Revision 1.11  2002/05/11 23:50:18  mkrohn5
* added cout message to Fatal call
*
* Revision 1.10  2001/11/02 02:10:52  mkrohn5
* added some comments
*
* Revision 1.9  2001/10/31 20:05:20  mkrohn5
* changed LOG_ENABLED behaviour
*
* Revision 1.8  2001/08/07 20:43:26  mkrohn5
* - minor changes due to new log mode
* - moved template funcions Min, Max to header
*
* Revision 1.7  2001/07/23 00:18:05  mkrohn5
* a quick hack to include the "indent" to the log output
*
* Revision 1.6  2001/05/10 22:59:16  mkrohn5
* changed parameter list for function Fatal(...)
*
* Revision 1.5  2001/04/29 21:38:37  ishark
* TAction updated to use TDataPackage/Load
*
* Revision 1.4  2001/04/27 01:15:05  mkrohn5
* added the Fatal function and removed one Min and one Max function
*
* Revision 1.3  2001/03/09 02:27:32  mkrohn5
* documentation updates, smaller fixes and cleanups and changed the Log calls.
*
* Revision 1.2  2001/03/07 00:40:53  mkrohn5
* smaller corrections
*
* Revision 1.1  2001/03/06 00:30:31  mkrohn5
* project import
*
* Revision 1.4  2000/06/15 09:50:47  mkrohn5
* *** empty log message ***
*
* Revision 1.3  2000/05/28 22:16:09  mkrohn5
* small changes
*
* Revision 1.2  2000/04/02 23:46:04  mkrohn5
* no message
*
* Revision 1.30  2000/03/01 19:39:39  stich
* templated Min and Max functions
*
* Revision 1.29  2000/02/29 00:26:42  krohn
* minor mods caused by major changes of the log concept
*
* Revision 1.28  2000/02/24 00:12:28  krohn
* minor changes
*
* Revision 1.27  2000/02/08 20:32:50  krohn
* log ID for planet class added
*
* Revision 1.26  2000/02/02 00:19:29  krohn
* added a log number for TConfig
*
* Revision 1.25  2000/01/27 23:19:10  krohn
* new log file number and removed namespace StellarLegacy
*
* Revision 1.24  2000/01/26 00:07:21  krohn
* a log number for fleet
*
* Revision 1.23  2000/01/21 06:14:16  jai
* oops forgot to save
*
* Revision 1.22  2000/01/21 06:11:09  jai
* Some minor changes including - removing log.h include as it creates nast include loops. Adding an std include before the using namespace std line so it makes sense.
*
* Revision 1.21  2000/01/21 00:49:17  krohn
* minor changes
*
* Revision 1.20  2000/01/20 07:56:26  krohn
* merged global.h file, hope it works?!
*
* Revision 1.19  2000/01/20 04:27:29  jai
* Commented out log.h, remove is possible for this creates some nasty include loops if left in.
*
* Revision 1.18  2000/01/19 00:30:17  krohn
* new type: byte
*
* Revision 1.17  2000/01/16 23:55:33  krohn
* added two minor functions
*
* Revision 1.16  2000/01/13 22:28:50  krohn
* some minor modifications / improvements
* the log system seems to have a smaller bug which I will fix next time
*
* Revision 1.15  1999/11/04 20:07:55  krohn
* minor changes (e.g. removed the translation class)
*
* Revision 1.14  1999/10/16 10:26:21  stich
* Added TNames, THostNames and TCondition classes for name management
*
* Revision 1.13  1999/10/11 16:01:48  alberto
* implemented TOSVal, TSubstance, TSubstanceType, TSubstanceSet methods
* added code/testing directory - added osval-demo and substance-demo
*
* Revision 1.12  1999/10/03 21:08:20  krohn
* removed translation class from namespace
*
* Revision 1.9  1999/09/28 07:08:29  krohn
* added some useful functions, e.g. randomize, random, round
*
* Revision 1.8  1999/09/21 09:56:09  jai
* Added using namespace StellarLegacy here to save code duplication elsewhere
*
* Revision 1.7  1999/09/15 23:08:33  krohn
* added a log const
*
* Revision 1.5  1999/09/10 16:07:41  krohn
* add CVS information
*
*/
