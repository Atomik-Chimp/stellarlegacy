// $Id: bitmap.cpp,v 1.3 2001/10/31 20:08:55 mkrohn5 Exp $

// Bitmap File
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

// Description:
// A simple and (at the moment) incomplete class, managing a bitmap
// <PENDING> Right now only special bitmaps can be loaded: 256 colors
// and only Windows BMP?! Don't know ... this is not the final version!!!

#include <iostream>
#include <fstream>
#include <string>

#include "common/bitmap.h"

using namespace std;



TBitmap :: TBitmap()
{
  Reset();
}



TBitmap :: TBitmap(string sFileName)
{
  Reset();
  Load(sFileName);
}



TBitmap :: ~TBitmap()
{
  Clear();
}



void TBitmap :: Clear()
{
  DeleteBitmap();
  Reset();
}



void TBitmap :: ConvertToGrayScale()
{
uint2 x, y;
uint2 uSum, uGray;

  LOG("TBitmap", "ConvertToGrayScale()") << "Converting bitmpap to gray scale." << endl;

  if (Empty() == true)  return;

  for (x=0; x<uWidth; x++)
  {
    for (y=0; y<uHeight; y++)
    {
      uSum = Bitmap[x][y].green + Bitmap[x][y].red + Bitmap[x][y].blue;
      uGray = Round((double) uSum / 3.0);
      Bitmap[x][y].red   = uGray;
      Bitmap[x][y].green = uGray;
      Bitmap[x][y].blue  = uGray;
    }
  }
}



bool TBitmap :: Empty() const
{
  if (Bitmap == 0)  return true;
  return false;
}



uint2 TBitmap :: GetHeight() const
{
  return uHeight;
}



TBitmap::tRGBColor TBitmap :: GetPixel(int2 x, int2 y) const
{
tRGBColor Color = {0, 0, 0};

  if (x<0 || x>=uWidth)   return Color;
  if (y<0 || y>=uHeight)  return Color;

  return Bitmap[x][y];
}



uint2 TBitmap :: GetWidth() const
{
  return uWidth;
}



void TBitmap :: Invert()
{
uint2 x, y;

  LOG("TBitmap", "Invert()") << "Invert bitmap." << endl;

  for (x=0; x<uWidth; x++)
  {
    for (y=0; y<uHeight; y++)
    {
      Bitmap[x][y].red   = 255 - Bitmap[x][y].red;
      Bitmap[x][y].green = 255 - Bitmap[x][y].green;
      Bitmap[x][y].blue  = 255 - Bitmap[x][y].blue;
    }
  }
}



bool TBitmap :: Load(string sFileName)
{
  if (Empty() == false)  Clear();

  // <PENDING> method should automatically find out what kind
  // of graphic format has been used.
  return LoadBMP(sFileName);
}



bool TBitmap :: LoadBMP(string sFileName)
{
ifstream in;
tRGBColor Palette[256];
byte uDummy, uIn;
int x, y;
tBMPHeader Header;

  in.open(sFileName.data(), ios::in);
  if (!in)
  {
    LOG("TBitmap", "LoadBMP(string sFileName)")
      << "Unable to open file: " << sFileName << "." << endl;
    return false;
  }
  LOG("TBitmap", "Load(string sFileName)") << "Loading bitmap: " << sFileName << "." << endl;

  // read file header
  in.read((char*) &Header, sizeof Header);

  // is the file really a bmp?
  if (Header.File.iType != 0x4d42)  return false;

  // dummy data
  for (int i=0; i<14; i++)  { in.read((char*) &uDummy, sizeof uDummy); }

  // load palette
  for (int j=0; j<256; j++)
  {
    in.read((char*) &Palette[j], sizeof Palette[j]);
    in.read((char*) &uDummy, sizeof uDummy);
  }

  // bitmap size
  uWidth = Header.Info.uWidth;
  uHeight = Header.Info.uHeight;
  AllocateMemoryForBitmap();

  // reading the bitmap
  for (y=0; y<uHeight; y++)
  {
    for (x=0; x<uWidth; x++)
    {
      in.read((char*) &uIn, sizeof uIn);
      Bitmap[x][y].red = Palette[uIn].red;
      Bitmap[x][y].green = Palette[uIn].green;
      Bitmap[x][y].blue = Palette[uIn].blue;
    }
  }

  in.close();      // close input stream

  LOG_BEGIN_INDENT();
  WriteBMPHeaderToLog(Header);
  LOG_END_INDENT();

  return true;
}



void TBitmap :: SetAllPixels(tRGBColor Color)
{
uint2 x, y;

  for (x=0; x<uWidth; x++)
  {
    for (y=0; y<uHeight; y++)
    {
      Bitmap[x][y].red   = Color.red;
      Bitmap[x][y].green = Color.green;
      Bitmap[x][y].blue  = Color.blue;
    }
  }
}



// uGray=0
void TBitmap :: SetAllPixels(uint2 uGray)
{
tRGBColor Color;

  if (uGray > 255)  uGray=255;
  Color.red = uGray;
  Color.green = uGray;
  Color.blue = uGray;

  SetAllPixels(Color);
}


//----------------------------------------  P R I V A T E   M E T H O D S  ----------------------------------------





bool TBitmap :: AllocateMemoryForBitmap()
{
int i;
uint2 uWidthTemp;

  if (Bitmap != 0)  DeleteBitmap();

  uWidthTemp=uWidth;
  uWidth=0;   // 0 is correct here!

  Bitmap = new tRGBColor*[uWidthTemp];
  if (Bitmap == 0)  return false;

  for (i=0; i<uWidthTemp; i++)
  {
    Bitmap[i] = new tRGBColor[uHeight];
    uWidth++;

    if (Bitmap[i] == 0)
    {
      uWidth--;
      DeleteBitmap();
      return false;
    }
  }

  return true;
}



void TBitmap :: DeleteBitmap()
{
uint2 x;

  if (Bitmap == 0)  return;

  for (x=0; x<uWidth; x++)  delete[] Bitmap[x];
  delete[] Bitmap;

  Bitmap=0;
}



// call only when assured that no memory must be freed before
void TBitmap :: Reset()
{
  Bitmap = 0;      // no picture is loaded right now
  uWidth = uHeight = 0;
}



void TBitmap :: WriteBMPHeaderToLog(const tBMPHeader Header) const
{
  if (Empty() == true)
  {
    LOG("TBitmap", "WriteBMPHeaderToLog(const tBMPHeader Header)")
      << "No bitmap loaded." << endl;
    return;
  }
  LOG("TBitmap", "WriteBMPHeaderToLog(const tBMPHeader Header)")
    << "type:        " << Header.File.iType << endl
    << "size:        " << Header.File.uSize << endl
    << "reserved1:   " << Header.File.iReserved1 << endl
    << "reserved2:   " << Header.File.iReserved2 << endl
    << "offbits:     " << Header.File.uOffbits << endl
    << "size:        " << Header.Info.uSize << endl
    << "width:       " << uWidth << endl
    << "height:      " << uHeight << endl
    << "planes:      " << Header.Info.iPlanes << endl
    << "bitcount:    " << Header.Info.iBitCount << endl
    << "compression: " << Header.Info.uCompression << endl
    << "image size:  " << Header.Info.uImageSize << endl
    << "pixel-x:     " << Header.Info.iXpelspermeter << endl
    << "pixel-y:     " << Header.Info.iYpelspermeter << endl
    << "colors used: " << (int) Header.Info.uColorsUsed << endl
    << "colors imp.: " << (int) Header.Info.uColorsImportant << endl;
}





/*
*
* $Log: bitmap.cpp,v $
* Revision 1.3  2001/10/31 20:08:55  mkrohn5
* removed #include "common/log.h"
*
* Revision 1.2  2001/03/09 02:27:32  mkrohn5
* documentation updates, smaller fixes and cleanups and changed the Log calls.
*
* Revision 1.1  2001/03/06 00:30:31  mkrohn5
* project import
*
* Revision 1.5  2000/08/10 00:05:33  mkrohn5
* *** empty log message ***
*
* Revision 1.4  2000/06/15 09:50:47  mkrohn5
* *** empty log message ***
*
* Revision 1.2  2000/05/28 22:16:09  mkrohn5
* small changes
*
* Revision 1.1  2000/04/02 23:46:04  mkrohn5
* no message
*
* Revision 1.4  2000/01/31 00:19:59  krohn
* tiny changes
*
* Revision 1.3  2000/01/23 01:05:05  krohn
* removed some bugs
*
* Revision 1.2  2000/01/20 07:50:53  krohn
* some major changes on bitmap, new methods, redesign, ...
*
* Revision 1.1  2000/01/19 00:29:50  krohn
* new class for loading bitmaps
*
*
*/
