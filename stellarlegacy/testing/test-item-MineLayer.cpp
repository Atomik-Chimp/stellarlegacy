// $Id: test-item-MineLayer.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// mine layer class testing
// Written by: Ralf Laue, <ralf.laue@gmx.de>
//
// Copyright (C) 2001 Ralf Laue, <ralf.laue@gmx.de>
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

#define MineLayer_NAME "Mine Layer"
#define MineLayer_TECHLEVEL 22
#define MineLayer_MASS 45
#define MineLayer_VOLUME 12
#define MineLayer_SURFACE 27
#define MineLayer_COST 45
#define MineLayer_RATE 64

void check_MineLayer( TMineLayer* MineLayer, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the mine layer is empty";
  result = check_item( *MineLayer,
                       TItem::MINELAYER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( MineLayer->getMineLayingRate() != 0 )
    {
      cout << "mine laying rate wrong!\n";
      result = false;
    } // if
  } // if
  
  cout << "*** Now I will assign the item some basic values.\n";
  MineLayer->setItemName( MineLayer_NAME );
  MineLayer->setTechLevel(MineLayer_TECHLEVEL);
  MineLayer->setMass(MineLayer_MASS);
  MineLayer->setVolume(MineLayer_VOLUME);
  MineLayer->setSurface(MineLayer_SURFACE);
  dummySet.Add( *substance->Create(MineLayer_COST) );
  MineLayer->setCost( dummySet );
  dummySet.Clear();
  MineLayer->setMineLayingRate(MineLayer_RATE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(MineLayer_COST) );
  result = check_item( *MineLayer,
                       TItem::MINELAYER,
                       MineLayer_NAME,
                       MineLayer_TECHLEVEL,
                       MineLayer_MASS,
                       MineLayer_VOLUME,
                       MineLayer_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( MineLayer->getMineLayingRate() != MineLayer_RATE )
    {
      cout << "mine laying rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TMineLayer object.\n";
  TMineLayer* testLayer = new TMineLayer();
  cout << "*** Now I check the operator=";  
  *testLayer = *MineLayer;
  dummySet.Add( *substance->Create(MineLayer_COST) );
  result = check_item( *testLayer,
                       TItem::MINELAYER,
                       MineLayer_NAME,
                       MineLayer_TECHLEVEL,
                       MineLayer_MASS,
                       MineLayer_VOLUME,
                       MineLayer_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( MineLayer->getMineLayingRate() != MineLayer_RATE )
    {
      cout << "mine laying rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TMineLayer object again.\n";
  delete testLayer;
  cout << "*** Now I use the copy constructor.\n";
  testLayer = new TMineLayer( *MineLayer );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(MineLayer_COST) );
  result = check_item( *testLayer,
                       TItem::MINELAYER,
                       MineLayer_NAME,
                       MineLayer_TECHLEVEL,
                       MineLayer_MASS,
                       MineLayer_VOLUME,
                       MineLayer_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( MineLayer->getMineLayingRate() != MineLayer_RATE )
    {
      cout << "mine laying rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testLayer == *MineLayer );


  cout << "*** Now I destruct the TMineLayer object again.\n";
  delete testLayer;
} // check_MineLayer



/*
 * $Log: test-item-MineLayer.cpp,v $
 * Revision 1.7  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.6  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.5  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.4  2001/06/12 14:13:42  prolator
 * added test for operator==
 *
 * Revision 1.3  2001/06/11 15:00:21  prolator
 * fixed a bug (one assignment too much after copy constructor)
 *
 * Revision 1.2  2001/06/11 14:27:58  prolator
 * added tests for tech level of items
 *
 * Revision 1.1  2001/06/11 13:14:56  prolator
 * tests for item sub classes now in independent files
 *
 */
