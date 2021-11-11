// $Id: bitmap.h,v 1.3 2001/03/09 02:27:32 mkrohn5 Exp $

// Bitmap Header File
// Written by: Marco Krohn

// Copyright (C) 1999, 2000
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

#ifndef __BITMAP_INCLUDED
#define __BITMAP_INCLUDED

#include <string>

#include "common/global.h"

using namespace std;





//----------  Declarations for BMP handling
typedef struct tBMPFileHeader
{
  int2 iType;
  uint4 uSize;
  int2  iReserved1;
  int2  iReserved2;
  uint2 uOffbits;
};

typedef struct tBMPInfo
{
  uint2 uSize;
  int2 uWidth;
  int2 iPlanes;
  int2 uHeight;
  int2 iBitCount;
  uint2 uCompression;
  uint2 uImageSize;
  int2  iXpelspermeter;
  int2  iYpelspermeter;
  int2 uColorsUsed;
  int2 uColorsImportant;
};

struct tBMPHeader
{
  tBMPFileHeader File;
  tBMPInfo       Info;
};




/**
* WARNING: this class need to be completly rewritten!
* Use a byte matrix and add the needed methods
* Don't offer a method for loading bitmaps, this is part of the UI
*
* Description:
* A simple and (at the moment) incomplete class, managing a bitmap
* <PENDING> Right now only special bitmaps can be loaded: 256 colors
* and only Windows BMP?! Don't know ... this is not the final version!!!
*/
class TBitmap
{
  public:
    struct tRGBColor
    {
      byte red;
      byte green;
      byte blue;
    };

    TBitmap();
    TBitmap( string sFileName );
    ~TBitmap();

//  PENDING: operator= must be defined as well as a copy constructor

    void Clear();
    void ConvertToGrayScale();
    bool Empty() const;
    uint2 GetHeight() const;
    tRGBColor GetPixel(int2 x, int2 y) const;
    uint2 GetWidth() const;
    void Invert();
    bool Load(string sFileName);
    bool LoadBMP(string sFileName);
    void SetAllPixels(tRGBColor Color);
    void SetAllPixels(uint2 uGray=0);

  private:
    tRGBColor** Bitmap;
    uint2 uWidth, uHeight;

    bool AllocateMemoryForBitmap();
    void DeleteBitmap();
    void Reset();
    void WriteBMPHeaderToLog(const tBMPHeader Header) const;
};





#endif        // __BITMAP_INCLUDED





