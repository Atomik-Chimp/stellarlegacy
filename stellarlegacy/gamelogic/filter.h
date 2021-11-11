// $Id: filter.h,v 1.2 2001/11/27 00:16:42 prolator Exp $
//
// Filter class Header File
// Written by: Ralf Laue <ralf.laue@gmx.de>
//
// Copyright (C) 2001 Ralf Laue <ralf.laue@gmx.de>
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

#ifndef __FILTER_INCLUDED
#define __FILTER_INCLUDED

/******************************** class TFilter ********************************/


/** @class TFilter
 *  @brief TFilter represents the amout of information a stellar object is able
 *         to percept of an other stellar object.
 *  @author Ralf Laue
 *  @version $Id: filter.h,v 1.2 2001/11/27 00:16:42 prolator Exp $
 *
 *  The class TFilter represents the amout of information a stellar object is
 *  able to percept of an other stellar object. At the moment the value for the
 *  amount is an integer value. The value can be between -1 and 100. The value
 *  0 means no information at all, 100 means the observer gets absolutely
 *  correct informations and all value between mean the observer gets values
 *  which are not exact, but can differ by (100 - filter value)% from the real
 *  value. The value -1 represents completely random values and the observer
 *  is not aware that these values are completly random. Furthermore the
 *  contains a dtring with a description of the object which is percepted. For
 *  example it could be "population" if the filter is conected with the
 *  population of a planet.                                                    */
class TFilter
{
  public:
    /** Type definition for the filter value, so it's easier to change the
     *  type if needed.                                                        */
    typedef tFilterValueType int2;
    /** This constructor creates a new Filter object. The filter will be
     *  initialized with zero perception and an empty filter description.      */
    TFilter();
    /** This constructor creates a new Filter object. You can specify the
     *  value of the filter and its description as parameters.
     *  @param FilterDescription the description of the percepted object
     *  @param FilterValue the value of the filter                             */
    TFilter( string& FilterDescription, tFilterValueType filterValue );
    /** The copy constructor creates a new Filter object using the values of
     *  filter given as parameter as initialization values.
     *  @param OtherFilter the filter from which the values are copied         */
    TFilter( const TFilter& otherFilter );
    /** The destructor frees the used memeory (at the moment it's nothing).    */
    virtual ~TFilter();
    /** With the method setFilterValue you can set the value of the filter.
     *  Values can be integers between -1 and 100, where 100 is correct
     *  perception, -1 is complete random values and numbers between 0 and 99
     *  stand for probability range. That means, the percepted values can
     *  differ by (100 - filter value)%.
     *  @param FilterValue the new value of the filter                         */
    virtual void setFilterValue( tFilterVauleType filterValue );
    /** With the method getFilterValue you can get the value of the filter.
     *  For further information about the meaning of the filter values look in
     *  the description of the class or the method \ref setFilterValue.
     *  @return the current value of the filter                                */
    virtual tFilterType getFilterValue();
    /** The method setFilterDescription sets the filter description (that is
     *  the description of the object which is observed) to the value given as
     *  parameter.
     *  @param FilterDescription the new filter description                    */
    virtual void setFilterDescription( string& filterDescription );
    /** The method getFilterDescription returns the filter description (that's
     *  the description of the object which is observed).
     *  @return the current filter description                                 */
    virtual string& getFilterDescription() const;
    /** This method implements the operator+ method. It returns a filter
     *  object, which has the value set to the addition/combination of the
     *  filter values of both filters. For now that is simply the greater one
     *  of both values. Neither of the filters is changed. The filter
     *  descriptions HAVE to be equal. If they are different, they cannot be
     *  connected to the same perceived object and they cannot be added. Thus,
     *  if they ae different, a fatal error is reported and the program is
     *  exits.
     *  @param FilterToAdd the filter to be "added" to this filter
     *  @return a filter which is a combination/addition of both filters       */
    virtual TFilter& operator+( const TFilter& filterToAdd ) const;
    /** This method implements the operator= method. It just assigns the new
     *  value to the filter.
     *  @param OtherFilter the filter which is to be assigned to this filter
     *  @return this filter with the new values assigned to it                 */
    virtual TFilter& operator=( const TFilter& otherFilter );
    /** This method implements the operator== method. It returns @c true if
     *  both filter values are equal and @c false if not.
     *  @param OtherFilter the filter which is to be compared ro this filter
     *  @return @true if both filters have the same values and @false if not   */
    virtual bool operator==( const TFilter& otherFilter ) const;
  protected:
    /** the internal variable for the filter value; for further information
     *  about the meaning of the filter values look in the description of the
     *  class or the method \ref setFilterValue.                               */
    FilterValueType fFilterValue;
    /** the internal variable to save the description of the object, which is
     *  observed and to which the filter is linked to                          */
    string fFilterDescription;
} // class TFilter


#endif                                                      // __FILTER_INCLUDED

