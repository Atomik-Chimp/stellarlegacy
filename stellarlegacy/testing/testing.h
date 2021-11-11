// $Id: testing.h,v 1.1 2002/03/24 13:53:58 mkrohn5 Exp $

// Testing Header File
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

#ifndef __TESTING_INCLUDED
#define __TESTING_INCLUDED

#include "common/defs.h"





//----------------------------------------  class TTesting  ----------------------------------------

/**
* @class TTesting
* @brief Counts overall and successful tests.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: testing.h,v 1.1 2002/03/24 13:53:58 mkrohn5 Exp $
*/
class TTesting
{
  public:
    TTesting();

    int4 getChecksDone() const;
    int4 getSuccess() const ;
    void report( bool check );
    void reset();
    bool result() const;

  private:
    int4 fChecksDone;
    int4 fSuccess;
};





#endif        // __TESTING_INCLUDED
