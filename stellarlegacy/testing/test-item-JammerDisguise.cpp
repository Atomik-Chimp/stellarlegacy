// $Id: test-item-JammerDisguise.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// disguise jammer class testing
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

#define JammerDisguise_NAME "Disguise Jammer"
#define JammerDisguise_TECHLEVEL 19
#define JammerDisguise_MASS 35
#define JammerDisguise_VOLUME 5
#define JammerDisguise_SURFACE 3
#define JammerDisguise_COST 29
#define JammerDisguise_EFFICIENCY 57

void check_JammerDisguise( TJammerDisguise* JammerDisguise, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the disguise jammer is empty";
  result = check_item( *JammerDisguise,
                       TItem::JAMMER,
                       "",
                       0,
                       0,
                       0,
                       0,
                       TSubstanceSet());
  test.report( result );
  if ( result ) 
  {
    if ( JammerDisguise->getJammerType() != TJammer::DISGUISE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerDisguise->getJamEfficiency() != 0 )
    {
      cout << "disguise jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  JammerDisguise->setItemName(JammerDisguise_NAME);
  JammerDisguise->setTechLevel(JammerDisguise_TECHLEVEL);
  JammerDisguise->setMass(JammerDisguise_MASS);
  JammerDisguise->setVolume(JammerDisguise_VOLUME);
  JammerDisguise->setSurface(JammerDisguise_SURFACE);
  dummySet.Add( *substance->Create(JammerDisguise_COST) );
  JammerDisguise->setCost( dummySet );
  dummySet.Clear();
  JammerDisguise->setJamEfficiency(JammerDisguise_EFFICIENCY);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(JammerDisguise_COST) );
  result = check_item( *JammerDisguise,
                       TItem::JAMMER,
                       JammerDisguise_NAME,
                       JammerDisguise_TECHLEVEL,
                       JammerDisguise_MASS,
                       JammerDisguise_VOLUME,
                       JammerDisguise_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerDisguise->getJammerType() != TJammer::DISGUISE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerDisguise->getJamEfficiency() != JammerDisguise_EFFICIENCY )
    {
      cout << "disguise jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TJammerDisguise object.\n";
  TJammerDisguise* testJammer = new TJammerDisguise();
  cout << "*** Now I check the operator=";  
  *testJammer = *JammerDisguise;
  dummySet.Add( *substance->Create(JammerDisguise_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerDisguise_NAME,
                       JammerDisguise_TECHLEVEL,
                       JammerDisguise_MASS,
                       JammerDisguise_VOLUME,
                       JammerDisguise_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerDisguise->getJammerType() != TJammer::DISGUISE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerDisguise->getJamEfficiency() != JammerDisguise_EFFICIENCY )
    {
      cout << "disguise jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TJammerDisguise object again.\n";
  delete testJammer;
  cout << "*** Now I use the copy constructor.\n";
  testJammer = new TJammerDisguise( *JammerDisguise );
  cout << "*** Now I check whether it worked ";  
  dummySet.Add( *substance->Create(JammerDisguise_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerDisguise_NAME,
                       JammerDisguise_TECHLEVEL,
                       JammerDisguise_MASS,
                       JammerDisguise_VOLUME,
                       JammerDisguise_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerDisguise->getJammerType() != TJammer::DISGUISE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerDisguise->getJamEfficiency() != JammerDisguise_EFFICIENCY )
    {
      cout << "disguise jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testJammer == *JammerDisguise );


  cout << "*** Now I destruct the TJammerDisguise object again.\n";
  delete testJammer;
} // check_JammerDisguise



/*
 * $Log: test-item-JammerDisguise.cpp,v $
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
 * Revision 1.1  2001/06/11 12:16:52  prolator
 * tests for item sub classes now in independent files
 *
 */
