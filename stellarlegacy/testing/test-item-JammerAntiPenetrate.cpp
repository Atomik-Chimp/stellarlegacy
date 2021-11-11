// $Id: test-item-JammerAntiPenetrate.cpp,v 1.7 2002/04/27 00:09:22 prolator Exp $
//
// AntiPenetrate jammer class testing
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

#define JammerAntiPenetrate_NAME "Anti Penetrate Jammer"
#define JammerAntiPenetrate_TECHLEVEL 21
#define JammerAntiPenetrate_MASS 85
#define JammerAntiPenetrate_VOLUME 11
#define JammerAntiPenetrate_SURFACE 4
#define JammerAntiPenetrate_COST 43
#define JammerAntiPenetrate_EFFICIENCY 74

void check_JammerAntiPenetrate( TJammerAntiPenetrate* JammerAntiPenetrate, TSubstanceType* substance, TTesting& test )
{
  bool result;
  TSubstanceSet dummySet;
  TSubstanceSet dummySet2;

  cout << "*** Now I check whether the anti penetrate jammer is empty";
  result = check_item( *JammerAntiPenetrate,
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
    if ( JammerAntiPenetrate->getJammerType() != TJammer::ANTIPENETRATE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerAntiPenetrate->getJamEfficiency() != 0 )
    {
      cout << "anti penetrate jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I will assign the item some basic values.\n";
  JammerAntiPenetrate->setItemName(JammerAntiPenetrate_NAME);
  JammerAntiPenetrate->setTechLevel(JammerAntiPenetrate_TECHLEVEL);
  JammerAntiPenetrate->setMass(JammerAntiPenetrate_MASS);
  JammerAntiPenetrate->setVolume(JammerAntiPenetrate_VOLUME);
  JammerAntiPenetrate->setSurface(JammerAntiPenetrate_SURFACE);
  dummySet.Add( *substance->Create(JammerAntiPenetrate_COST) );
  JammerAntiPenetrate->setCost( dummySet );
  dummySet.Clear();
  JammerAntiPenetrate->setJamEfficiency(JammerAntiPenetrate_EFFICIENCY);

  cout << "*** Now I check whether the basic values are saved";
  dummySet.Add( *substance->Create(JammerAntiPenetrate_COST) );
  result = check_item( *JammerAntiPenetrate,
                       TItem::JAMMER,
                       JammerAntiPenetrate_NAME,
                       JammerAntiPenetrate_TECHLEVEL,
                       JammerAntiPenetrate_MASS,
                       JammerAntiPenetrate_VOLUME,
                       JammerAntiPenetrate_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerAntiPenetrate->getJammerType() != TJammer::ANTIPENETRATE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerAntiPenetrate->getJamEfficiency() != JammerAntiPenetrate_EFFICIENCY )
    {
      cout << "anti penetrate jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I create a new TJammerAntiPenetrate object.\n";
  TJammerAntiPenetrate* testJammer = new TJammerAntiPenetrate();
  cout << "*** Now I check the operator=";  
  *testJammer = *JammerAntiPenetrate;
  dummySet.Add( *substance->Create(JammerAntiPenetrate_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerAntiPenetrate_NAME,
                       JammerAntiPenetrate_TECHLEVEL,
                       JammerAntiPenetrate_MASS,
                       JammerAntiPenetrate_VOLUME,
                       JammerAntiPenetrate_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerAntiPenetrate->getJammerType() != TJammer::ANTIPENETRATE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerAntiPenetrate->getJamEfficiency() != JammerAntiPenetrate_EFFICIENCY )
    {
      cout << "anti penetrate jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now I destruct the TJammerAntiPenetrate object again.\n";
  delete testJammer;
  cout << "*** Now I use the copy constructor.\n";
  testJammer = new TJammerAntiPenetrate( *JammerAntiPenetrate );
  cout << "*** Now I check whether it worked";  
  dummySet.Add( *substance->Create(JammerAntiPenetrate_COST) );
  result = check_item( *testJammer,
                       TItem::JAMMER,
                       JammerAntiPenetrate_NAME,
                       JammerAntiPenetrate_TECHLEVEL,
                       JammerAntiPenetrate_MASS,
                       JammerAntiPenetrate_VOLUME,
                       JammerAntiPenetrate_SURFACE,
                       dummySet);
  dummySet.Clear();
  test.report( result );
  if ( result ) 
  {
    if ( JammerAntiPenetrate->getJammerType() != TJammer::ANTIPENETRATE )
    {
      cout << "jammer type wrong!\n";
      result = false;
    } // if
    if ( JammerAntiPenetrate->getJamEfficiency() != JammerAntiPenetrate_EFFICIENCY )
    {
      cout << "anti penetrate jam efficiency wrong!\n";
      result = false;
    } // if
  } // if

  cout << "*** Now testing operator==";
  test.report( *testJammer == *JammerAntiPenetrate );
  

  cout << "*** Now I destruct the TJammerAntiPenetrate object again.\n";
  delete testJammer;
} // check_JammerAntiPenetrate



/*
 * $Log: test-item-JammerAntiPenetrate.cpp,v $
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
