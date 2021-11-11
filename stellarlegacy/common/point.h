// $Id: point.h,v 1.17 2002/07/12 10:05:04 mkrohn5 Exp $

// Point Header File
// Written by: Marco Krohn

// Copyright (C) 1999-2000, Marco Krohn, krohn@itp.uni-hannover.de
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

#ifndef __POINT_INCLUDED
#define __POINT_INCLUDED

#include <fstream>
#include <iostream>

#include "common/global.h"

using namespace std;

class TDataPackageList;
class TPoint;





//----------------------------------------  Misc. Functions  ----------------------------------------

/**
* Stream function for TPoint, allowing cout << point.
* The output looks like: "(0.124, 3.3453, 100.345)".
* @param Stream the current ostream for output.
* @param point this one will be written to the output stream.
* @return The old stream + the coordinates of the point.
*/
ostream& operator<<( ostream& Stream, const TPoint& point );
/**
* Product with a scalar quantity e.g. 3 * (1, -2, 3) = (3, -6, 9).
* (note: this is only the version for the left hand side. The rhs:
* (vector)*(scalar quantity) is defined in TPoint.
* @param dScale the scalar quantity = the scale factor for the point (vector).
* @param point the point itself.
* @return The new scaled point (vector).
*/
TPoint operator*( const double dScale, const TPoint& point );





//----------------------------------------  class TPoint  ----------------------------------------

/**
* @class TPoint
* @brief 3d vector and some standard operations.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: point.h,v 1.17 2002/07/12 10:05:04 mkrohn5 Exp $
* @see TRectangle
*
* A simple class representing a point in a 3 dimensional space.
* Operations like +, - and multiplication with scalar values are available.
*/
class TPoint
{
  public:
    enum
    {
      X_AXIS=1,
      Y_AXIS=2,
      Z_AXIS=3
    };

    /**
    * The standard constructor for defining a 3d point.
    * @param x the x coordinate.
    * @param y the y coordinate.
    * @param z the z coordinate.
    */
    TPoint( double x=0, double y=0, double z=0 );
    /**
    * The TPoint copy constructor.
    * @param point use the coordinates of this point.
    */
    TPoint( const TPoint& point );

    /**
    * Calculates the euclidean length of the distance from the point
    * to (0,0,0).
    * @return The distance to the origin.
    * @see Magnitude
    */
    double getLength() const;
    /**
    * @return The x coordinate of the point.
    */
    double getX() const;
    /**
    * @return The y coordinate of the point.
    */
    double getY() const;
    /**
    * @return The z coordinate of the point.
    */
    double getZ() const;
    /**
    * @return @c true if all coordinates are 0, otherwise false.
    */
    bool isNull() const;
    /**
    * Analyses if two points (or better "vectors") are linear dependent or not.
    * @param two The second "vector".
    * @param dAccuracy See @a dEps.
    * @return @c true if the "vectors" are linear dependent, otherwise @c false.
    */
    bool linearDependence( const TPoint& two, double dAccuracy=dEps ) const;
    /**
    * Loads a TPoint object from a list of data packages.
    * Note that a successful load will delete the datapackage from the data
    * package list as well as the datapackage itself.
    * @param in The input stream of data packages.
    * @param sIdentifier The identifier to look for.
    * @param bUnique Loads the data only if the identifier is unique.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    bool load( TDataPackageList* in, const string& sIdentifier,
               bool bUnique=true );
    /**
    * Calculates the euclidean length of the distance from the point
    * to (0,0,0).
    * @return The distance to the origin.
    * @see getLength
    */
    double magnitude() const;
    /**
    * Sets the length of the vector to 1.
    * Note that the vector (0,0,0) can not be normalized.
    * @return The newly normalized vector (or (0,0,0) for the case mentioned above).
    */
    TPoint& normalize();
    /**
    * Comparison operator.
    * @param point The point to compare to.
    * @return true if the two points are identical.
    */
    bool operator==( const TPoint& point ) const;
   /**
    * Incrementing the point by @e point.
    * @param point The point that is added.
    * @return The modified point.
    */
    TPoint& operator+=( const TPoint& point );
    /**
    * Subtracting @e point from this point.
    * @param point The point that is substracted.
    * @return The modified point.
    */
    TPoint& operator-=( const TPoint& point );
    /**
    * Calculates the sum of two points.
    * @param point The second term of the sum.
    * @return The sum of the two points.
    */
    TPoint operator+( const TPoint& point ) const;
    /**
    * The difference of two points (vectors) = a-b
    * @param point the second term.
    * @return the result of the operation a-b (note: a will not change its value)
    */
    TPoint operator-( const TPoint& point ) const;
    /**
    * Multiplies this point with a scalar quantity.
    * @param dScale The scalar quantity.
    * @return The modified point.
    */
    TPoint& operator*=( const double dScale );
    /**
    * Multiplies the point with a scalar quantity.
    * @param dScale The scalar quantity.
    * @return The scaled point.
    */
    TPoint operator*( const double dScale ) const;
    /**
    * Multiplies two objects with type TPoint, using the "dot product".
    * @param point The second point needed for the product.
    * @return The return value is the dot product, a real number.
    */
    double operator*( const TPoint& point ) const;
    /**
    * Multiplies the point with a scalar quantity.
    * @param dScale The scalar quantity.
    * @return The scaled point.
    * @see operator*=
    */
    void rescale( double dScale );
    /**
    * Creates the data package for a TPoint object and adds it to
    * the data package list.
    * @param out The list of data packages.
    * @param sIdentifier The identifier which is used to store and find the data.
    * @param bUnique If set to @c true the method will check if the identifier was
    *   already used in the data package list.
    * @param bAutoDelete Setting this flag to @c true means that _this_ object
    *   will automatically be deleted by the TDataPackageList.
    * @return @c true if everything worked fine, otherwise @c false (e.g. if
    *   the identifier was already used in the data package list).
    */
    bool save( TDataPackageList* out, const string& sIdentifier,
               bool bUnique=true, bool bAutoDelete=false ) const;
    /**
    * Sets all coordinates to 0.
    */
    void setNull();
    /**
    * Sets all three coordinates of the point.
    */
    void setPoint( double x=0, double y=0, double z=0 );
    /**
    * Sets the x coordinate of the point.
    */
    void setX( double x );
    /**
    * Sets the y coordinate of the point.
    */
    void setY( double y );
    /**
    * Sets the z coordinate of the point.
    */
    void setZ( double z );
    /**
    * Writes the current position to a stream, using the following
    * output format: (x, y, z).
    * @param stream The output stream.
    * @return The output stream after adding the output for the point.
    */
    ostream& write( ostream& stream ) const;

  protected:
    /**
    * Since the double arithmetic is not exact we use this constant
    * and say that two double values are "equal" if their difference
    * is smaller than @e dEps;
    */
    static const double dEps;

    /**
    * The x-component of the point
    */
    double dX;
    /**
    * The y-component of the point
    */
    double dY;
    /**
    * The z-component of the point
    */
    double dZ;
};





#endif        // __POINT_INCLUDED





