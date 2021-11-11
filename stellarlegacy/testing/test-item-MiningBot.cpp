// $Id: test-item-MiningBot.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// mining bot class testing
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

#define MiningBot_NAME "Mining Bot"
#define MiningBot_TECHLEVEL 23
#define MiningBot_MASS 65
#define MiningBot_VOLUME 64
#define MiningBot_SURFACE 68
#define MiningBot_COST 76
#define MiningBot_RATE 79

void check_MiningBot( TMiningBot* MiningBot, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the mining bot is empty";
  result = check_item( *MiningBot,
                       TItem::MININGBOT,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( MiningBot->getMiningRate() != 0 )
    {
      cout << "mining rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  MiningBot->setItemName( MiningBot_NAME );
  MiningBot->setTechLevel(MiningBot_TECHLEVEL);
  MiningBot->setMass(MiningBot_MASS);
  MiningBot->setVolume(MiningBot_VOLUME);
  MiningBot->setSurface(MiningBot_SURFACE);
  dummySet.Add( *substance->Create(MiningBot_COST) );
  MiningBot->setCost( dummySet );
  dummySet.Clear();
  MiningBot->setMiningRate(MiningBot_RATE);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(MiningBot_COST) );
  result = check_item( *MiningBot,
                       TItem::MININGBOT,
                       MiningBot_NAME,
                       MiningBot_TECHLEVEL,
                       MiningBot_MASS,
                       MiningBot_VOLUME,
                       MiningBot_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( MiningBot->getMiningRate() != MiningBot_RATE )
    {
      cout << "mining rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TMiningBot object.\n";
  TMiningBot* testBot = new TMiningBot();
  cout << "*** Now I check the operator=";  
  *testBot = *MiningBot;
  dummySet.Add( *substance->Create(MiningBot_COST) );
  result = check_item( *testBot,
                       TItem::MININGBOT,
                       MiningBot_NAME,
                       MiningBot_TECHLEVEL,
                       MiningBot_MASS,
                       MiningBot_VOLUME,
                       MiningBot_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( MiningBot->getMiningRate() != MiningBot_RATE )
    {
      cout << "mining rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TMiningBot object again.\n";
  delete testBot;
  cout << "*** Now I use the copy constructor.\n";
  testBot = new TMiningBot( *MiningBot );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(MiningBot_COST) );
  result = check_item( *testBot,
                       TItem::MININGBOT,
                       MiningBot_NAME,
                       MiningBot_TECHLEVEL,
                       MiningBot_MASS,
                       MiningBot_VOLUME,
                       MiningBot_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( MiningBot->getMiningRate() != MiningBot_RATE )
    {
      cout << "mining rate wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testBot == *MiningBot );


  cout << "*** Now I destruct the TMiningBot object again.\n";
  delete testBot;
} // check_MiningBot



/*
 * $Log: test-item-MiningBot.cpp,v $
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
