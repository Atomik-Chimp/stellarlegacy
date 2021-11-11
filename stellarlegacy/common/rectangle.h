// $Id: rectangle.h,v 1.3 2002/07/12 10:05:04 mkrohn5 Exp $

// Rectangle Header File
// Written by: Marco Krohn

// Copyright (C) 1999 - 2001, Marco Krohn, marco.krohn@gmx.de
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

#ifndef __RECTANGLE_INCLUDED
#define __RECTANGLE_INCLUDED

#include <iostream>

using namespace std;

class TLine;
class TPoint;
class TRectangle;





//----------------------------------------  Misc. Functions  ----------------------------------------

/**
* Stream function for TRectangle, allowing e.g. cout << rect.
* The output format is: "(x1, y1, x2, x2)"
* @param Stream the current ostream for output.
* @param Rect this rectangle will be written to the output stream.
* @returns the old stream + the coordinates of the rect.
*/
ostream& operator<<( ostream& Stream, const TRectangle& Rect );





//----------------------------------------  class TRectangle  ----------------------------------------

/**
* @class TRectangle
* @brief Describes a rectangle in the plane.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: rectangle.h,v 1.3 2002/07/12 10:05:04 mkrohn5 Exp $
* @see TPoint
*
* The default coordinate system has origin (0,0) in the top left corner,
* the positive direction of the y axis is downwards and the positive x axis
* is from the left to the right. In contary to many other rectangle classes
* TRectangle uses double values for the representation of the rectangle.
*/
class TRectangle
{
  public:
    /**
    * Constructor for a rectangle with the top left corner at (x, y),
    * the width w and the height h.
    * @param x is the x-coordinate of the top left corner.
    * @param y is the y-coordinate of the top left corner.
    * @param w is the width of the rectangle.
    * @param h is the height of the rectangle.
    */
    TRectangle( double x=0, double y=0, double w=0, double h=0 );
    /**
    * Constructs a rectangle with topLeft as the top left corner and size as
    * the rectangle size.
    * @param TopLeft is the top left corner.
    * @param Size is the size of the rectangle.
    */
    TRectangle( const TPoint& TopLeft, const TPoint& Size );

    // default: operator=, copy constructor

    /**
    * Checks whether or not this rectangle contains the point (x, y).
    * If the rectangle is not valid (see IsValid()) the result is always false.
    * @param x is the x-coordinate of the point.
    * @param y is the y-coordinate of the point.
    * @param proper If proper is true, this function returns true only if p is
    *   inside (not on the edge).
    * @return true in case the point is inside or on the edge of the rectangle.
    *   Otherwise returns false.
    * @see TRectangle#Intersects
    */
    bool contains( double x, double y, bool proper=false ) const;
    /**
    * Checks whether or not this Rectangle contains the point (x, y).
    * If the rectangle is not valid (see IsValid) the result is always false.
    * @param Point contains the coordinates of the point.
    * @param proper If proper is true, this function returns true only if p is
    *   inside (not on the edge).
    * @return true in case the point is inside or on the edge of the rectangle.
    *   Otherwise returns false.
    * @see TRectangle#Intersects
    */
    bool contains( const TPoint& Point, bool proper=false ) const;
    /**
    * @return Returns the right coordinate.
    * @see TRectangle#getTop
    */
    double getBottom() const;
    /**
    * @return Returns the center point of the rectangle,
    *   that is (x1+x2)/2, (y1+y2)/2.
    */
    TPoint getCenter() const;
    /**
    * @return Returns the height of the rectangle. Note that a non valid rectangle
    *   has negative height.
    * @see TRectangle#getWidth, TRectangle#IsValid
    */
    double getHeight() const;
    /**
    * FIXME
    * Note: does only work for valid rectangles.
    */
    int getIntersectionPoints( const TLine& line, TPoint* one, TPoint* two ) const;
    /**
    * @return Returns the left coordinate. Identical to getX().
    * @see TRectangle#getRight, TRectangle#getX
    */
    double getLeft() const;
    /**
    * @return Returns the right coordinate.
    * @see TRectangle#getLeft
    */
    double getRight() const;
    /**
    * @return The size of the rectangle.
    * @see TRectangle#getWidth, TRectangle#getHeight
    */
    TPoint getSize() const;
    /**
    * @return Returns the top coordinate. Identical to getY().
    * @see TRectangle#getBottom, TRectangle#getY
    */
    double getTop() const;
    /**
    * @return Returns the width of the rectangle. Note that a non valid rectangle
    *   has negative width.
    * @see TRectangle#getHeight, TRectangle#IsValid
    */
    double getWidth() const;
    /**
    * @return Returns the left coordinate. Identical to getLeft().
    */
    double getX() const;
    /**
    * @return Returns the top coordinate. Identical to getTop().
    */
    double getY() const;
    /**
    * @param r is the second rectangle.
    * @returns Returns true if this rectangle intersects with r (that means
    * if there is at least one point which belongs to both rectangles).
    */
    bool intersects( const TRectangle& r ) const;
    /**
    * A valid rectangle has a left() <= right() and top() <= bottom().
    * @returns true if the rectangle is valid, or false if it is invalid.
    */
    bool isValid() const;
    /**
    * Moves the rectangle dx along the X axis and dy along the Y axis, relative
    * to the current position (Positive values moves the rectangle rightwards
    * and/or downwards). The size of the rectangle does not change.
    * @param dx is the relative movement in x direction.
    * @param dy is the relative movement in y direction.
    * @see TRectangle#MoveByX, TRectangle#MoveByY, TRectangle#MoveTo
    */
    void moveBy( double dx, double dy );
    /**
    * Moves the rectangle dx along the X axis, relative
    * to the current position. The size of the rectangle does not change.
    * @param dx is the relative movement in x direction.
    * @see TRectangle#MoveBy, TRectangle#MoveByY, TRectangle#MoveToX
    */
    void moveByX( double dx );
    /**
    * Moves the rectangle dy along the Y axis, relative
    * to the current position. The size of the rectangle does not change.
    * @param dy is the relative movement in y direction.
    * @see TRectangle#MoveBy, TRectangle#MoveByX, TRectangle#MoveToY
    */
    void moveByY( double dy );
    /**
    * Moves the rectangle (or more precise the top left corner) to the
    * absolute position (x, y) without changing the size of the rectangle.
    * @param x is the new x position (left coordinate).
    * @param y is the new y position (bottom coordinate).
    * @see TRectangle#MoveBy, TRectangle#MoveToX, TRectangle#MoveToY
    */
    void moveTo( double x, double y );
    /**
    * Moves the rectangle (or more precise the top left corner) to the
    * absolute position x without changing the size of the rectangle.
    * @param x is the new x position (left coordinate).
    * @see TRectangle#MoveByX, TRectangle#MoveTo, TRectangle#MoveToY
    */
    void moveToX( double x );
    /**
    * Moves the rectangle (or more precise the top left corner) to the
    * absolute position y without changing the size of the rectangle.
    * @param y is the new y position (left coordinate).
    * @see TRectangle#MoveByY, TRectangle#MoveTo, TRectangle#MoveToX
    */
    void moveToY( double y );
    /**
    * @return A normalized rectangle, i.e. one that has a non-negative width
    *   and height. It swaps left and right if getLeft() > getRight(), and swaps top
    *   and bottom if getTop() > getBottom().
    * @see TRectangle#isValid
    */
    TRectangle normalize() const;
    /**
    * Sets the bottom edge of the rectangle. May change the height, but will
    * never change the top edge of the rectangle.
    * @param b is the new bottom position.
    * @see TRectangle#getBottom, TRectangle#SetTop, TRectangle#SetHeight
    */
    void setBottom( double b );
    /**
    * Sets the height of the rectangle to h. The top edge is not moved,
    * but the bottom edge may be moved.
    * @see TRectangle#getHeight, TRectangle#SetTop, TRectangle#SetBottom, TRectangle#SetSize
    */
    void setHeight( double h );
    /**
    * Sets the left edge of the rectangle. May change the width, but will
    * never change the right edge of the rectangle. Identical to SetX().
    * @param l the new value for the left edge.
    * @see TRectangle#getLeft, TRectangle#SetTop, TRectangle#SetWidth
    */
    void setLeft( double l );
    /**
    * Sets the coordinates of the rectangle's top left corner to (x,y),
    * and its size to (w,h).
    */
    void setRect( double x, double y, double w, double h );
    /**
    * Sets the right edge of the rectangle. May change the width,
    * but will never change the left edge of the rectangle.
    * @see TRectangle#getRight, TRectangle#SetLeft, TRectangle#SetWidth
    */
    void setRight( double r );
    /**
    * Sets the size of the rectangle to (w, h). The top left corner is not moved.
    * @param w is the width.
    * @param h is the height.
    * @see TRectangle#getSize, TRectangle#SetWidth, TRectangle#SetHeight
    */
    void setSize( double w, double h );
    /**
    * Sets the size of the rectangle to (Size.getX(), Size.getY()).
    * The top left corner is not moved.
    * @param Size which determines the size of the rectangle.
    * @see TRectangle#getSize, TRectangle#SetWidth, TRectangle#SetHeight
    */
    void setSize( const TPoint& Size );
    /**
    * Sets the top edge of the rectangle. May change the height, but will
    * never change the bottom edge of the rectangle.
    * @param t the new value for the left edge.
    */
    void setTop( double t );
    /**
    * Sets the width of the rectangle to w.
    * The right edge is changed, but not the left edge.
    * @param w the new width.
    */
    void setWidth( double w );
    /**
    * Sets the x position of the rectangle (its left end). May change the width,
    * but will never change the right edge of the rectangle.
    * Identical to SetLeft().
    * @see TRectangle#getX, TRectangle#SetY
    */
    void setX( double x );
    /**
    * Sets the y position of the rectangle (its top). May change the height,
    * but will never change the bottom edge of the rectangle.
    * Identical to SetTop().
    * @see TRectangle#getX, TRectangle#SetY
    */
    void setY( double y );
    /**
    * Writes the current rectangle to a stream, using the following
    * output format: (x1, y1, x2, y2).
    * @param Stream is the output stream.
    * @return a reference to the new stream.
    */
    ostream& write( ostream& Stream ) const;

  protected:
    double x1;
    double y1;
    double x2;
    double y2;
};





#endif        // __RECTANGLE_INCLUDED
