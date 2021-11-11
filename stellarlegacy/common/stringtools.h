// $Id: stringtools.h,v 1.2 2002/06/23 15:50:48 ishark Exp $

// String Tools Header File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

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

#ifndef __STRINGTOOLS_INCLUDED
#define __STRINGTOOLS_INCLUDED

#include "common/defs.h"


using namespace std;



//----------------------------------------  class TStringTools  ----------------------------------------

/**
* @class TStringTools
* @brief Some useful tools for manipulating strings.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: stringtools.h,v 1.2 2002/06/23 15:50:48 ishark Exp $
*
* Various methods for manipulating strings.
*/
class TStringTools
{
  public:
    /**
    * "cleans" a string in the sense that it is o.k. to use it as a filename.
    * @param src The source string.
    * @return The "cleaned" string.
    */
    static string convertToFileName( const string& src );
    /**
    * "Cleans" a string in the sense that it is possible to use the string
    * as a path name. Especially this method ensures that the directory
    * ends with "/".
    * @param src The source string.
    * @return The "cleaned" string.
    */
    static string convertToDirectory( const string& src );
};





#endif        // __STRINGTOOLS_INCLUDED
