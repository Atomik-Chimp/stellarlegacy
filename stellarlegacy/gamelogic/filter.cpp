// $Id: filter.cpp,v 1.2 2001/11/27 00:16:42 prolator Exp $
//
// filter class Code File
// Written by: Ralf Laue, <ralf.laue@gmx.de>
//
// Copyright (C) 2001, Ralf Laue, <ralf.laue@gmx.de>
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

#include "filter.h"

/******************************** class TFilter ********************************/

TFilter::TFilter()
{
  fFilterValue = 0;        // set the filter value to minimum (standard setting)
} // constructor



TFilter::TFilter( const tFilterValueType& filterValue )
{
  fFilterValue = FilterValue;               // set filter value to desired value
} // constructor



TFilter::TFilter( const TFilter& otherFilter )
{
  *this = OtherFilter;                           // use operator= to copy fields
} // copy constructor



// virtual
TFilter::~TFilter()
{
                                                           // nothing to do here
} // destructor



// virtual
void TFilter::setFilterValue( const tFilterVauleType& filterValue )
{
  fFilterValue = FilterValue;                   // set filter value to new value
} // setFilterValue



// virtual
tFilterType TFilter::getFilterValue()
{
  return fFilterValue;                                    // return filter value
} // getFilterValue



void setFilterDescription( string& filterDescription )
{
  fFilterDescription = FilterDescription; // set filter description to new value
} // setFilterDescription



string& getFilterDescription() const
{
  return fFilterDescription;            // return the current filter description
} // getFilterDescription



// virtual
TFilter& TFilter::operator+( const TFilter& filterToAdd ) const
{
  if ( fFilterDescription == FilterToAdd.fFilterDescription)
  {                      // if both filter descriptions are equal (they have to)
    if ( fFilterValue < FilterToAdd.fFilterValue )
    {                     // if the filter object of the other filter is greater
      return TFilter( FilterToAdd.fFilterValue );//return filter with this value
    } else {                                                             // else
      return TFilter( fFilterValue );      // return filter with the other value
    } // if
  } else {     // if the filter descriptions are not the same --> error and exit
    Fatal( "TFilter", "operator+", "The filter descriptions didn't match!" );
  } // if else
} // operator+



// virtual
TFilter& TFilter::operator=( const TFilter& otherFilter )
{
  if ( this != &OtherFilter )                 // if both filter are not the same
  {
    fFilterValue = OtherFilter.fFilterValue;            // copy filter value and 
    fFilterDescription = OtherFilter.fFilterDescription;   // filter description
  } // if
  return *this;                                                 // return object
} // operator=



// virtual
bool TFilter::operator==( const TFilter& otherFilter ) const
{
  return (fFilterValue == OtherFilter.fFilterValue) &&  // are filter values AND
    (fFilterDescription == OtherFilter.fFilterDescription); //description equal?
} // operator==



/*
 * $Log: filter.cpp,v $
 * Revision 1.2  2001/11/27 00:16:42  prolator
 * adjusted parameter to coding conventions
 *
 * Revision 1.1  2001/11/21 18:48:36  prolator
 * first version of the filter class
 *
 */
