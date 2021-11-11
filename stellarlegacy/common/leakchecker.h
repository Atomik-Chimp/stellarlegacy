// $Id: leakchecker.h,v 1.2 2001/07/05 20:34:18 ishark Exp $

// Leak Checker Header File
// Written by: Marco Krohn <marco.krohn@gmx.de>

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#ifndef __LEAK_CHECKER_INCLUDED
#define __LEAK_CHECKER_INCLUDED

#ifdef SECURE_MODE

#include <iostream>





//----------------------------------------  class TLeakChecker  ----------------------------------------

/**
* @class TLeakChecker
* @brief A very simple class to check for memory leaks.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: leakchecker.h,v 1.2 2001/07/05 20:34:18 ishark Exp $
*
* This simply counts the number of objects of a certain type.
* An example implementation is given in TDataPackage.
*/
class TLeakChecker
{
  public:
    TLeakChecker() : iCounter(0) {};
    ~TLeakChecker()  { }

    int Get() const { return iCounter; }
    void operator++(int)  { iCounter++; }
    void operator--(int)  { iCounter--; }
    void Print() const  { std::cout << iCounter; }

  private:
    int iCounter;
};





#endif  // SECURE_MODE

#endif  // __LEAK_CHECKER_INCLUDED
