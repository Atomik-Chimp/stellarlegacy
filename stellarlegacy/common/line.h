// $Id: line.h,v 1.2 2002/07/12 10:05:03 mkrohn5 Exp $

// Line Header File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001 -     , Marco Krohn, marco.krohn@gmx.de
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

#ifndef __LINE_INCLUDED
#define __LINE_INCLUDED

#include "common/point.h"





//----------------------------------------  class TLine  ----------------------------------------

/**
* @class TLine
* @brief Describes a line in 3D Space.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: line.h,v 1.2 2002/07/12 10:05:03 mkrohn5 Exp $
* @see TPoint
*
* FIXME
*/
class TLine
{
  public:
    TLine();
    TLine( const TPoint& offset, const TPoint& dir );

    const TPoint& getDir() const;
    /**
    * @param point The intersection point.
    * @return The number of intersection points (0, 1, 2=infinity which means that
    *   the lines are indentical).
    */
    int getIntersectionPoint( const TLine& line, TPoint* point ) const;
    const TPoint& getOffset() const;
    void setDir( const TPoint& dir );
    void setLine( const TPoint& offset, const TPoint& dir );
    void setOffset( const TPoint& offset );

  private:
    TPoint fDir;
    TPoint fOffset;

};





#endif        // __LINE_INCLUDED
