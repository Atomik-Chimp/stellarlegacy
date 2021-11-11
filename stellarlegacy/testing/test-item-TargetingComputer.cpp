// $Id: test-item-TargetingComputer.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// targeting computer class testing
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

#define TargetingComputer_NAME "Targeting Computer"
#define TargetingComputer_TECHLEVEL 9
#define TargetingComputer_MASS 13
#define TargetingComputer_VOLUME 14
#define TargetingComputer_SURFACE 0
#define TargetingComputer_COST 8
#define TargetingComputer_AIMINGEFFICIENCY 13

void check_TargetingComputer( TTargetingComputer* TargetingComputer, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the targeting computer is empty";
  result = check_item( *TargetingComputer,
                       TItem::TARGETINGCOMPUTER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);
  if ( result ) 
  {
    if ( TargetingComputer->getAimingEfficiency() != 0 )
    {
      cout << "targeting computer efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  TargetingComputer->setItemName(TargetingComputer_NAME);
  TargetingComputer->setTechLevel(TargetingComputer_TECHLEVEL);
  TargetingComputer->setMass(TargetingComputer_MASS);
  TargetingComputer->setVolume(TargetingComputer_VOLUME);
  TargetingComputer->setSurface(TargetingComputer_SURFACE);
  dummySet.Add( *substance->Create(TargetingComputer_COST) );
  TargetingComputer->setCost( dummySet );
  dummySet.Clear();
  TargetingComputer->setAimingEfficiency(TargetingComputer_AIMINGEFFICIENCY);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(TargetingComputer_COST) );
  result = check_item( *TargetingComputer,
                       TItem::TARGETINGCOMPUTER,
                       TargetingComputer_NAME,
                       TargetingComputer_TECHLEVEL,
                       TargetingComputer_MASS,
                       TargetingComputer_VOLUME,
                       TargetingComputer_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( TargetingComputer->getAimingEfficiency() != TargetingComputer_AIMINGEFFICIENCY )
    {
      cout << "targeting computer efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TTargetingComputer object.\n";
  TTargetingComputer* testComputer = new TTargetingComputer();
  cout << "*** Now I check the operator=";  
  *testComputer = *TargetingComputer;
  dummySet.Add( *substance->Create(TargetingComputer_COST) );
  result = check_item( *testComputer,
                       TItem::TARGETINGCOMPUTER,
                       TargetingComputer_NAME,
                       TargetingComputer_TECHLEVEL,
                       TargetingComputer_MASS,
                       TargetingComputer_VOLUME,
                       TargetingComputer_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( TargetingComputer->getAimingEfficiency() != TargetingComputer_AIMINGEFFICIENCY )
    {
      cout << "targeting computer efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TTargetingComputer object again.\n";
  delete testComputer;
  cout << "*** Now I use the copy constructor.\n";
  testComputer = new TTargetingComputer( *TargetingComputer );
  cout << "*** Now I check whether it worked";  
  *testComputer = *TargetingComputer;
  dummySet.Add( *substance->Create(TargetingComputer_COST) );
  result = check_item( *testComputer,
                       TItem::TARGETINGCOMPUTER,
                       TargetingComputer_NAME,
                       TargetingComputer_TECHLEVEL,
                       TargetingComputer_MASS,
                       TargetingComputer_VOLUME,
                       TargetingComputer_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( TargetingComputer->getAimingEfficiency() != TargetingComputer_AIMINGEFFICIENCY )
    {
      cout << "targeting computer efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testComputer == *TargetingComputer );


  cout << "*** Now I destruct the TTargetingComputer object again.\n";
  delete testComputer;
} // check_TargetingComputer



/*
 * $Log: test-item-TargetingComputer.cpp,v $
 * Revision 1.7  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.6  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.5  2001/07/05 20:34:19  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.4  2001/06/12 14:13:43  prolator
 * added test for operator==
 *
 * Revision 1.3  2001/06/11 14:27:58  prolator
 * added tests for tech level of items
 *
 * Revision 1.2  2001/06/10 23:37:42  prolator
 * corrected mistake in comments
 *
 * Revision 1.1  2001/06/10 22:48:30  prolator
 * tests for item sub classes now in independent files
 *
 */
