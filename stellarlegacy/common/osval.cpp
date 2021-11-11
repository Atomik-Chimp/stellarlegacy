// $Id: osval.cpp,v 1.8 2002/06/28 10:12:07 mkrohn5 Exp $

// Overflow-Safe Value Code File
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

#include "common/osval.h"
#include "common/datapackage.h"

const int4 TOSVal::iInfinity =  2147483647;  // 2^31-1
const int4 TOSVal::iMaximum  =  2000000000;





/*
 * TOSVal member functions
 */

TOSVal::TOSVal(void) : iValue(0)
{
}


TOSVal::TOSVal(const int4 iVal)
{
  *this = iVal;
}


int4 TOSVal::Value() const
{
  return iValue;
}


bool TOSVal::Infinite() const
{
  return (iValue == iInfinity || iValue == -iInfinity);
}


bool TOSVal::Maximum() const
{
  return (iValue == iMaximum || iValue == -iMaximum);
}


bool TOSVal::Zero() const
{
  return iValue == 0;
}


bool TOSVal::Negative() const
{
  return iValue < 0;
}


bool TOSVal::Positive() const
{
  return iValue > 0;
}


TOSVal& TOSVal::operator=(const int4 iVal)
{
  if (iVal == iInfinity || iVal == -iInfinity ||
      (iVal >= -iMaximum && iVal <= iMaximum) )
    iValue = iVal;

  else
    iValue = iMaximum * sign(iValue);

  return *this;
}


const TOSVal TOSVal::operator-(void) const
{
  return TOSVal(-iValue);
}


const TOSVal TOSVal::operator+(const TOSVal& v2) const
{
  TOSVal r(*this);
  r += v2;
  return r;
}


const TOSVal TOSVal::operator-(const TOSVal& v2) const
{
  TOSVal r(*this);
  r += -v2;
  return r;
}


TOSVal& TOSVal::operator+=(const TOSVal& v2)
{
  if (iValue == iInfinity)
  {
    if (v2.iValue == -iInfinity)
      iValue = 0;
  }
  else if (iValue == -iInfinity)
  {
    if (v2.iValue == iInfinity)
      iValue = 0;
  }
  else
  {
    if (v2.iValue == iInfinity)
      iValue = iInfinity;
    else if (v2.iValue == -iInfinity)
      iValue = -iInfinity;
    else
    {
      if (v2.iValue >= 0)
      {
        if (iMaximum - v2.iValue <= iValue)
          iValue = iMaximum;
        else
          iValue += v2.iValue;
      }
      else
      {
        if (-iMaximum - v2.iValue >= iValue)
          iValue = -iMaximum;
        else
          iValue += v2.iValue;
      }
    }
  }

  return *this;
}


TOSVal& TOSVal::operator-=(const TOSVal& v2)
{
  *this += -v2;
  return *this;
}


TOSVal TOSVal::Scale(const int4 iNum, const int4 iDenom) const
{
  TOSVal r(*this);

  // first: handle infinite values
  if (r.iValue == iInfinity || r.iValue == -iInfinity)
  {
    if (iNum != 0)
      r.iValue *= sign(iNum);
    if (iDenom != 0)
      r.iValue *= sign(iDenom);
  }
  // second: handle 0 numerator
  else if (iNum == 0)
    r.iValue = 0;

  // third: handle 0 denominator
  else if (iDenom == 0)
  {
    if (r.iValue != 0)
      r.iValue = iInfinity * sign(iNum) * sign(r.iValue);
    else
      r.iValue = iInfinity * sign(iNum);
  }
  // fourth: check for maximum values
  else if (r.iValue == iMaximum || r.iValue == -iMaximum && iNum >= iDenom)
  {
    r.iValue = iMaximum * sign(iNum) * sign(iDenom);
  }
  // fifth: check for overflow
  else if (abs(r.iValue) / abs(iDenom) >= iMaximum / abs(iNum))
  {
    r.iValue = iMaximum * sign(r.iValue) * sign(iNum) * sign(iDenom);
  }
  // sixth: check for possible overflow
  else if (iMaximum / abs(iNum) <= abs(r.iValue))
  {
    // FIXME: perform approximated calculation
    // (this method sucks, any better idea?)
    // COMMENT: without looking exactly at the code:
    // do all the calculations with double numbers?! (marco)
    r.iValue = (max(iNum, r.iValue) / iDenom) * min(iNum, r.iValue);
  }
  else
  {
    // perform exact calculation
    r.iValue = (r.iValue * iNum) / iDenom;
  }

  return r;
}


bool TOSVal::operator==(const TOSVal v2) const
{
  return iValue == v2.iValue;
}


bool TOSVal::operator!=(const TOSVal v2) const
{
  return iValue != v2.iValue;
}


bool TOSVal::operator>=(const TOSVal v2) const
{
  return iValue >= v2.iValue;
}


bool TOSVal::operator<=(const TOSVal v2) const
{
  return iValue <= v2.iValue;
}


bool TOSVal::operator<(const TOSVal v2) const
{
  return iValue < v2.iValue;
}


bool TOSVal::operator>(const TOSVal v2) const
{
  return iValue > v2.iValue;
}



bool TOSVal::operator==( int4 v2 ) const
{
  return iValue == v2;
}



bool TOSVal::operator!=( int4 v2 ) const
{
  return iValue != v2;
}



ostream& operator<<(ostream& os, const TOSVal& v)
{
  if (v.Infinite())
  {
    if (!v.Positive())
      os << "-";
    os << "Infinity";
  }
  else if (v.Maximum())
  {
    if (!v.Positive())
      os << "-";
    os << "Maximum";
  }
  else
    os << v.iValue;

  return os;
}



// default bUnique=true
bool TOSVal::load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
  bool ReturnBool = true;
  
  ReturnBool &= in->getAndDelete( sIdentifier, &iValue, bUnique);           // load value
  return ReturnBool;                              // return the bool for success
} // load



// default bUnique=true
bool TOSVal::save( TDataPackageList* out, const string& sIdentifier, bool bUnique ) const
{
  bool ReturnBool = true;

  ReturnBool &= out->add( sIdentifier, &iValue, bUnique, false ); // save value
  return ReturnBool;                              // return the bool for success
} // save





/*
 * $Log: osval.cpp,v $
 * Revision 1.8  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.7  2002/06/23 15:50:48  ishark
 * added act-to-cpp tool, fixes in TActionSequencer, gcc3 fixes
 *
 * Revision 1.6  2002/06/21 08:31:57  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.5  2002/01/28 00:34:39  mkrohn5
 * reformated the docu and added two comparison methods
 *
 * Revision 1.4  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.3  2001/06/20 15:43:54  prolator
 * added methods Load and Save
 *
 * Revision 1.2  2001/04/13 21:56:54  ishark
 * fixed osval/substance tests, added preliminary version of action
 *
 * Revision 1.1  2001/03/06 00:30:31  mkrohn5
 * project import
 *
 * Revision 1.5  2000/09/21 21:12:35  mkrohn5
 * smaller updates
 *
 * Revision 1.4  2000/06/29 10:59:56  ishark
 * added action/lex/parser, addeed license to headers
 *
 * Revision 1.3  2000/05/28 22:16:09  mkrohn5
 * small changes
 *
 * Revision 1.2  2000/04/02 23:46:04  mkrohn5
 * no message
 *
 * Revision 1.6  2000/01/26 00:07:51  krohn
 * corrected some lines to avoid problems with my compiler
 *
 * Revision 1.5  1999/10/23 16:10:15  alberto
 * first version (semi-complete) of the TSubstance-related classes
 *
 * Revision 1.4  1999/10/17 17:32:47  alberto
 * corrections in OSVal and Substance/Set, partial implement of Hold
 *
 * Revision 1.3  1999/10/11 16:01:48  alberto
 * implemented TOSVal, TSubstance, TSubstanceType, TSubstanceSet methods
 * added code/testing directory - added osval-demo and substance-demo
 *
 *
 */
