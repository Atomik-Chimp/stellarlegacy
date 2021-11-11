// $Id: test-item-JammerCloak.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// cloak jammer class testing
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

#define JammerCloak_NAME "Cloak Jammer"
#define JammerCloak_TECHLEVEL 20
#define JammerCloak_MASS 67
#define JammerCloak_VOLUME 3
#define JammerCloak_SURFACE 5
#define JammerCloak_COST 31
#define JammerCloak_EFFICIENCY 77

void check_JammerCloak( TJammerCloak* JammerCloak, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the cloak jammer is empty";
  result = check_item( *JammerCloak,
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
    if ( JammerCloak->getJammerType() != TJammer::CLOAK )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerCloak->getJamEfficiency() != 0 )
    {
      cout << "cloak jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  JammerCloak->setItemName(JammerCloak_NAME);
  JammerCloak->setTechLevel(JammerCloak_TECHLEVEL);
  JammerCloak->setMass(JammerCloak_MASS);
  JammerCloak->setVolume(JammerCloak_VOLUME);
  JammerCloak->setSurface(JammerCloak_SURFACE);
  dummySet.Add( *substance->Create(JammerCloak_COST) );
  JammerCloak->setCost( dummySet );
  dummySet.Clear();
  JammerCloak->setJamEfficiency(JammerCloak_EFFICIENCY);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(JammerCloak_COST) );
  result = check_item( *JammerCloak,
                       TItem::JAMMER,
                       JammerCloak_NAME,
                       JammerCloak_TECHLEVEL,
                       JammerCloak_MASS,
                       JammerCloak_VOLUME,
                       JammerCloak_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerCloak->getJammerType() != TJammer::CLOAK )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerCloak->getJamEfficiency() != JammerCloak_EFFICIENCY )
    {
      cout << "cloak jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TJammerCloak object.\n";
  TJammerCloak* testJammer = new TJammerCloak();
  cout << "*** Now I check the operator=";  
  *testJammer = *JammerCloak;
  dummySet.Add( *substance->Create(JammerCloak_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerCloak_NAME,
                       JammerCloak_TECHLEVEL,
                       JammerCloak_MASS,
                       JammerCloak_VOLUME,
                       JammerCloak_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerCloak->getJammerType() != TJammer::CLOAK )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerCloak->getJamEfficiency() != JammerCloak_EFFICIENCY )
    {
      cout << "cloak jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TJammerCloak object again.\n";
  delete testJammer;
  cout << "*** Now I use the copy constructor.\n";
  testJammer = new TJammerCloak( *JammerCloak );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(JammerCloak_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerCloak_NAME,
                       JammerCloak_TECHLEVEL,
                       JammerCloak_MASS,
                       JammerCloak_VOLUME,
                       JammerCloak_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerCloak->getJammerType() != TJammer::CLOAK )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerCloak->getJamEfficiency() != JammerCloak_EFFICIENCY )
    {
      cout << "cloak jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testJammer == *JammerCloak );


  cout << "*** Now I destruct the TJammerCloak object again.\n";
  delete testJammer;
} // check_JammerCloak



/*
 * $Log: test-item-JammerCloak.cpp,v $
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
