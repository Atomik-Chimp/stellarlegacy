// $Id: osval.h,v 1.6 2002/06/23 15:50:48 ishark Exp $

// Overflow-Safe Value Header File
// Written by: Alberto Barsella

// Copyright (C) 1999, 2000, Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
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

#ifndef __TOSVAL_INCLUDED
#define __TOSVAL_INCLUDED

#include <iostream>

#include "common/global.h"

class TDataPackageList;
using namespace std;



/* FIXME: should be removed or moved to global.cpp - Marco */
inline int4 sign(const int4 i) {
  return (i > 0)? 1 : ((i == 0)? 0 : -1);
}

inline int4 iabs(const int4 i) {
  return (i > 0)? i : ((i == 0)? 0 : -i);
}

inline int4 min(const int4 a, const int4 b) {
  return (a < b)? a : b;
}

inline int4 max(const int4 a, const int4 b) {
  return (a > b)? a : b;
}





//----------------------------------------  class TOSVal  ----------------------------------------

/**
 * @class TOSVal
 * @brief Wrapper for an integer number (int4) to prevent overflow errors.
 * @author Alberto Barsella, <Alberto.Barsella@univ-lille1.fr>
 * @version $Id: osval.h,v 1.6 2002/06/23 15:50:48 ishark Exp $
 *
 * TOSVal, Overflow-secure Value
 *
 * This class is a wrapper for an integer number (int4)
 * to prevent overflow errors from wrapping and/or messing
 * things up.
 *
 * Two "special" values are added:
 *
 * <ul>
 *   <li><strong>Infinity</strong> represents an infinite value</li>
 *   <li><strong>Maximum</strong> represent the maximum (finite) value</li>
 * </ul>
 *
 *
 * <h2>Properties</h2>
 *
 * Properties of the new values:
 *
 * <ul>
 *  <li>Infinity + anything = Infinity</li>
 *  <li>Infinity - anything but Infinity = Infinity</li>
 *  <li>Infinity - Infinity              = 0</li>
 *  <li>Maximum  + anything but Infinity = Maximum</li>
 *  <li>Maximum  - anything but Infinity = Maximum-anything</li>
 * </ul>
 *
 * <h2>Multiplicatio Properties (Scale function)</h2>
 *
 * Given: value * numerator/denominator
 *
 * <ul>
 *  <li>Infinity * anything/anything  = Infinity</li>
 *  <li>anything * 0/anything         = 0</li>
 *  <li>anything * anything/0         = Infinity</li>
 * </ul>
 *
 * if ( value*numerator/denominator >= Maximum ) = Maximum
 *
 * if (value*numerator > Maximum BUT value*numerator/denominator < Maximum)
 *
 *   the function will try to approximate the result by preventing
 *   a multipliction overflow. The result is NOT guaranteed to be
 *   the exact value.
 */
class TOSVal
{
  public:
    TOSVal();
    TOSVal(const int4 iVal);
    // default destructor
    // default copy constructor
    // default operator=

    // special values for quantities
    // - infinity means an infinite amount
    // - maximum  is the maximum possible value: any attempt to
    //            go beyond this just does nothing
    //            it's used to prevent overflows
    static const int4 iInfinity;  // 2^31-1
    static const int4 iMaximum;   // 2*10^9       see osval.cpp

    // accessors
    int4 Value() const;
    bool Infinite() const;
    bool Maximum() const;
    bool Zero() const;
    bool Positive() const;
    bool Negative() const;
    TOSVal& operator=(const int4 iVal);

    // mathematical operators
    const TOSVal operator-(void) const;
    const TOSVal operator+(const TOSVal& v2) const;
    const TOSVal operator-(const TOSVal& v2) const;
    TOSVal& operator+=(const TOSVal& v2);
    TOSVal& operator-=(const TOSVal& v2);

    // rescale (= multiply by fraction)
    TOSVal Scale(const int4 iNum, const int4 iDenom) const;

    // comparison operators
    bool operator==(const TOSVal v2) const;
    bool operator!=(const TOSVal v2) const;
    bool operator>=(const TOSVal v2) const;
    bool operator<=(const TOSVal v2) const;
    bool operator>(const TOSVal v2) const;
    bool operator<(const TOSVal v2) const;

    bool operator==( int4 v2 ) const;
    bool operator!=( int4 v2 ) const;

    // output operator
    friend ostream& operator<<(ostream& os, const TOSVal& v);

    // load and save
    /** With the method Load you can load a TOSVal object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /** With the method Save you can save a TOSVal object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool save( TDataPackageList* out, const string& sIdentifier, bool bUnique=true ) const;

  private:
    int4 iValue;
};





#endif        // TOSVal
