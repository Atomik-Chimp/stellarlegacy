// $Id: test-item-FTLEngine.cpp,v 1.8 2002/04/27 00:09:22 prolator Exp $
//
// FTL engine class testing
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

#define FTLEngine_TECHLEVEL 2

void check_FTLEngine( TFTLEngine* FTLEngine, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the FTL engine is empty";
  result = check_item( *FTLEngine,
                       TItem::FTL_ENGINE,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report(result);
  if ( result ) 
  {
    if ( FTLEngine->getFTLPower() != 0 )
    {
      cout << "FTL Engine power wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  FTLEngine->setItemName("FTL Engine");
  FTLEngine->setTechLevel(FTLEngine_TECHLEVEL);
  FTLEngine->setMass(150);
  FTLEngine->setVolume(30);
  FTLEngine->setSurface(12);
  dummySet.Add( *substance->Create(3) );
  FTLEngine->setCost( dummySet );
  dummySet.Clear();
  FTLEngine->setFTLPower( 16000 );
  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(3) );
  result = check_item( *FTLEngine,
                       TItem::FTL_ENGINE,
                       "FTL Engine",
                       FTLEngine_TECHLEVEL,
                       150,
                       30,
                       12,
                       dummySet);
  dummySet.Clear();
  test. report(result);
  if ( result ) 
  {
    if ( FTLEngine->getFTLPower() != 16000 )
    {
      cout << "FTL Engine power wrong!\n";
      result = false;
    } // if
  } // if
  
  cout << "*** Now I create a new TFTLEngine object.\n";
  TFTLEngine* testEngine = new TFTLEngine();
  cout << "*** Now I check the operator=";  
  *testEngine = *FTLEngine;
  dummySet.Add( *substance->Create(3) );
  result = check_item( *testEngine,
                       TItem::FTL_ENGINE,
                       "FTL Engine",
                       FTLEngine_TECHLEVEL,
                       150,
                       30,
                       12,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FTLEngine->getFTLPower() != 16000 )
    {
      cout << "FTL Engine power wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TFTLEngine object again.\n";
  delete testEngine;
  cout << "*** Now I use the copy constructor.\n";
  testEngine = new TFTLEngine( *FTLEngine );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(3) );
  result = check_item( *testEngine,
                       TItem::FTL_ENGINE,
                       "FTL Engine",
                       FTLEngine_TECHLEVEL,
                       150,
                       30,
                       12,
                       dummySet);
  dummySet.Clear();
  test.report(result);
  if ( result ) 
  {
    if ( FTLEngine->getFTLPower() != 16000 )
    {
      cout << "FTL Engine power wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testEngine == *FTLEngine );


  cout << "*** Now I destruct the TFTLEngine object again.\n";
  delete testEngine;
} // check_FTLEngine



/*
 * $Log: test-item-FTLEngine.cpp,v $
 * Revision 1.8  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.7  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.6  2002/02/03 23:18:26  mkrohn5
 * minor changes due to renaming
 *
 * Revision 1.5  2001/07/05 20:34:18  ishark
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
 * Revision 1.1  2001/06/10 17:39:53  prolator
 * tests for item sub classes now in independent files
 *
 */
