// $Id: test-item-RepairBot.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
//
// repair module class testing
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

#define RepairBot_TECHLEVEL 6

void check_RepairBot( TRepairBot* RepairBot, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the repair module is empty";
  result = check_item( *RepairBot,
                       TItem::REPAIRBOT,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());

  if ( result ) 
  {
    if ( RepairBot->getRepairSpeed() != 0 )
    {
      cout << "repair module capacity wrong!\n";
      result = false;
    } // if
  } // if
  test.report(result);

  cout << "*** Now I will assign the item some basic values.\n";
  RepairBot->setItemName("Repair Module");
  RepairBot->setTechLevel(RepairBot_TECHLEVEL);
  RepairBot->setMass(5);
  RepairBot->setVolume(22);
  RepairBot->setSurface(3);
  dummySet.Add( *substance->Create(34) );
  RepairBot->setCost( dummySet );
  dummySet.Clear();
  RepairBot->setRepairSpeed(375);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(34) );
  result = check_item( *RepairBot,
                       TItem::REPAIRBOT,
                       "Repair Module",
                       RepairBot_TECHLEVEL,
                       5,
                       22,
                       3,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( RepairBot->getRepairSpeed() != 375 )
    {
      cout << "repair module capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TRepairBot object.\n";
  TRepairBot* testBot = new TRepairBot();
  cout << "*** Now I check the operator=";  
  *testBot = *RepairBot;
  dummySet.Add( *substance->Create(34) );
  result = check_item( *testBot,
                       TItem::REPAIRBOT,
                       "Repair Module",
                       RepairBot_TECHLEVEL,
                       5,
                       22,
                       3,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( RepairBot->getRepairSpeed() != 375 )
    {
      cout << "repair module capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TRepairBot object again.\n";
  delete testBot;
  cout << "*** Now I use the copy constructor.\n";
  testBot = new TRepairBot( *RepairBot );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(34) );
  result = check_item( *testBot,
                       TItem::REPAIRBOT,
                       "Repair Module",
                       RepairBot_TECHLEVEL,
                       5,
                       22,
                       3,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( RepairBot->getRepairSpeed() != 375 )
    {
      cout << "repair module capacity wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testBot == *RepairBot );


  cout << "*** Now I destruct the TRepairBot object again.\n";
  delete testBot;
} // check_RepairBot



/*
 * $Log: test-item-RepairBot.cpp,v $
 * Revision 1.8  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.7  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.6  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.5  2001/06/12 14:13:42  prolator
 * added test for operator==
 *
 * Revision 1.4  2001/06/11 15:00:21  prolator
 * fixed a bug (one assignment too much after copy constructor)
 *
 * Revision 1.3  2001/06/11 14:27:58  prolator
 * added tests for tech level of items
 *
 * Revision 1.2  2001/06/11 12:19:07  prolator
 * corrected mistake in comments
 *
 * Revision 1.1  2001/06/10 21:29:56  prolator
 * tests for item sub classes now in independent files
 *
 */
