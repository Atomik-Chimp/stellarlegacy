// $Id: defs.h,v 1.16 2002/06/26 19:16:07 ishark Exp $

// Definitions Header File

// Copyright (C) 1999 - 2001, Marco Krohn, marco.krohn@gmx.de
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 1, or (at your option)
// any later version.
//
// This program is distrqibuted in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef __DEFS_INCLUDED
#define __DEFS_INCLUDED





//----------------------------------------  Defines  ----------------------------------------

#ifdef HAVE_CONFIG_H                                       // for unix systems only
  #include "../config.h"
  #define OS_UNIX
#else                                                      // windows
  #define VERSION "0.2pre"
  #define PACKAGE "stellarlegacy"
  #define OS_WINDOWS
#endif

// This will enable additional checks which make the application slower
// but severe bugs are easier to find. For example this will enable a check
// which checks if an element is added twice to a list by accident.
// Another check that is activated is the "leakchecker" class.
#define SECURE_MODE

#define LOG_ENABLED                                        // comment if you don't want to have a log file





//----------------------------------------  Constants  ----------------------------------------

const int FAILED = -1;





//----------------------------------------  Type Definitions  ----------------------------------------

typedef unsigned char byte;
/**
* A two byte integer. It should be guaranteed that this is independet from
* the machine type: Range: -32768 - 32767.
*/
typedef short int int2;
typedef long int int4;
typedef unsigned short int uint2;
typedef unsigned long int uint4;





//----------------------------------------  class TLog  ----------------------------------------

#ifdef LOG_ENABLED                                         // switch on the log system
#include <fstream>

  class TLog
  {
    public:
      /**
      * Decreases the indentation.
      */
      void decreaseIndent()
      {
        if ( fIndent > 0 )  fIndent--;
      }
      /**
      * @return The current indentation.
      */
      int2 getIndent() const
      {
        return fIndent;
      }
      /**
      * @return The logout stream one can write to.
      */
      std::ofstream& out() const
      {
        return *fLogout;
      }
      /**
      * Increases the indentation.
      */
      void increaseIndent()
      {
        fIndent++;
      }
      /**
      * @return The unique instance of TLog.
      */
      static TLog& instance()
      {
        static TLog theInstance;
        return theInstance;
      }

    protected:
      /**
      * The constructor is protected to ensure that there is @e exactly one
      * instance of this class available.
      * @see instance
      */
      TLog()
      {
        fLogout = new std::ofstream("log.out");
        fIndent = 0;
      }

    private:
      /**
      * The log stream one can write to.
      */
      std::ofstream* fLogout;
      /**
      * The current indentation (always >= 0).
      */
      int2 fIndent;
  };

  // see global.cpp
  extern int iIndentNumber;
  extern std::ofstream* logout;                            // the output stream

  #define LOG(x,y)             TLog::instance().out() << ":::" << x << ", " << y << ", normal, " << TLog::instance().getIndent() << ", "
  #define WLOG(x,y)            TLog::instance().out() << ":::" << x << ", " << y << ", warning, " << TLog::instance().getIndent() << ", "
  #define ELOG(x,y)            TLog::instance().out() << ":::" << x << ", " << y << ", error, " << TLog::instance().getIndent() << ", "
  #define LOG_BEGIN_INDENT();  TLog::instance().increaseIndent();
  #define LOG_END_INDENT();    TLog::instance().decreaseIndent();
#else                                                      // all log output to stderr
  #define LOG(x,y)             cerr << x << ", " << y << ", normal, "
  #define LOG_BEGIN_INDENT();  ;
  #define LOG_END_INDENT();    ;
  #define WLOG(x,y)            cerr << x << ", " << y << ", warning, "
  #define ELOG(x,y)            cerr << x << ", " << y << ", error, "
#endif





#endif        // __DEFS_INCLUDED
