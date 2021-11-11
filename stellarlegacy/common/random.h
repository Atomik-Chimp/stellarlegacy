// $Id: random.h,v 1.4 2002/03/24 13:24:10 mkrohn5 Exp $

// Random Header File

// Copyright (C) 1999, 2000, Marco Krohn, krohn@itp.uni-hannover.de
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

#ifndef __RANDOM_INCLUDED
#define __RANDOM_INCLUDED





//----------------------------------------  class TRandom  ----------------------------------------

/**
* @class TRandom
* @brief A wrapper class for random number generation.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: random.h,v 1.4 2002/03/24 13:24:10 mkrohn5 Exp $
*
* A wrapper class for random number generations using the standard
* C routines.
*/
class TRandom
{
  public:
    /**
    * @return Returns the next double value. The returned values
    *   are elements of the closed interval [0, 1] (this means
    *   that 0 and 1 are possible values).
    */
    static double getDouble();
    /**
    * @return The initialization number for the random number generation.
    */
    static int getInitNumber();
    /**
    * FIXME: test if the distribution is o.k., I am not sure
    * @param max The highest possible value _plus_ one.
    * @return Returns an integer of the (closed) interval [0, @e max -1].
    */
    static int getInteger( int max );
    /**
    * @return The max. possible random number (simply returns the constant
    *   @c RAND_MAX which is defined in stdlib.h)
    */
    static int getMaxRandomNumber();
    /**
    * Initializes the random number generator using the current time.
    */
    static void initialize();
    /**
    * Initializes the random number generator.
    * @param init The parameter which is used for initialization of the
    *   random number generator.
    */
    static void initialize( int init );

  private:
    static int fRandInit;
};



#endif        // __RANDOM_INCLUDED
