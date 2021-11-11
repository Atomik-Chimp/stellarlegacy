// $Id: test-item-JammerNormal.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// normal jammer class testing
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

#define JammerNormal_NAME "Normal Jammer"
#define JammerNormal_TECHLEVEL 18
#define JammerNormal_MASS 15
#define JammerNormal_VOLUME 8
#define JammerNormal_SURFACE 7
#define JammerNormal_COST 21
#define JammerNormal_EFFICIENCY 48

void check_JammerNormal( TJammerNormal* JammerNormal, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the normal jammer is empty";
  result = check_item( *JammerNormal,
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
    if ( JammerNormal->getJammerType() != TJammer::NORMAL )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerNormal->getJamEfficiency() != 0 )
    {
      cout << "normal jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  JammerNormal->setItemName(JammerNormal_NAME);
  JammerNormal->setTechLevel(JammerNormal_TECHLEVEL);
  JammerNormal->setMass(JammerNormal_MASS);
  JammerNormal->setVolume(JammerNormal_VOLUME);
  JammerNormal->setSurface(JammerNormal_SURFACE);
  dummySet.Add( *substance->Create(JammerNormal_COST) );
  JammerNormal->setCost( dummySet );
  dummySet.Clear();
  JammerNormal->setJamEfficiency(JammerNormal_EFFICIENCY);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(JammerNormal_COST) );
  result = check_item( *JammerNormal,
                       TItem::JAMMER,
                       JammerNormal_NAME,
                       JammerNormal_TECHLEVEL,
                       JammerNormal_MASS,
                       JammerNormal_VOLUME,
                       JammerNormal_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerNormal->getJammerType() != TJammer::NORMAL )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerNormal->getJamEfficiency() != JammerNormal_EFFICIENCY )
    {
      cout << "normal jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TJammerNormal object.\n";
  TJammerNormal* testJammer = new TJammerNormal();
  cout << "*** Now I check the operator=";  
  *testJammer = *JammerNormal;
  dummySet.Add( *substance->Create(JammerNormal_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerNormal_NAME,
                       JammerNormal_TECHLEVEL,
                       JammerNormal_MASS,
                       JammerNormal_VOLUME,
                       JammerNormal_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerNormal->getJammerType() != TJammer::NORMAL )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerNormal->getJamEfficiency() != JammerNormal_EFFICIENCY )
    {
      cout << "normal jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TJammerNormal object again.\n";
  delete testJammer;
  cout << "*** Now I use the copy constructor.\n";
  testJammer = new TJammerNormal( *JammerNormal );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(JammerNormal_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerNormal_NAME,
                       JammerNormal_TECHLEVEL,
                       JammerNormal_MASS,
                       JammerNormal_VOLUME,
                       JammerNormal_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerNormal->getJammerType() != TJammer::NORMAL )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerNormal->getJamEfficiency() != JammerNormal_EFFICIENCY )
    {
      cout << "normal jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testJammer == *JammerNormal );


  cout << "*** Now I destruct the TJammerNormal object again.\n";
  delete testJammer;
} // check_JammerNormal



/*
 * $Log: test-item-JammerNormal.cpp,v $
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
