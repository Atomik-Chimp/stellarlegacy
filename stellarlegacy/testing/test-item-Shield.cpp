// $Id: test-item-Shield.cpp,v 1.10 2002/04/27 00:09:22 prolator Exp $
//
// shield classes testing
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

#define Shield_NAME "Shield"
#define Shield_TECHLEVEL 27
#define Shield_MASS 43
#define Shield_VOLUME 6
#define Shield_SURFACE 7
#define Shield_COST 2650
#define Shield_HITPOINTS 67
#define Shield_StanEfficiency1 87
#define Shield_StanEfficiency2 46
#define Shield_Efficiency1 45
#define Shield_Efficiency2 56
#define Shield_Efficiency3 129
#define Shield_Efficiency4 14
#define Shield_Efficiency5 34
#define Shield_Efficiency6 57


cout << "*************************************************************\n";
cout << "*** Now I'm going to test TShield and TShieldType.\n";
cout << "*** At first I create two TShieldType objects and set their.\n";
cout << "*** efficiencies against different weapons.\n";
cout << "*** Now I create the first TShieldType object (shieldType1).\n";
TShieldType* shieldType1 = new TShieldType();
cout << "*** Now I check whether shieldType1 is empty";
result = true;
for( int2 c = 0; c < 10 ; ++c )
{
  if ( shieldType1->getDefenseEfficiency( c ) != 100 )
  {
    cout << "standard efficiency wrong initialized!";
    result = false;
  } // if
} // for
  if ( shieldType1->getStandardEfficiency() != 100 )
{
  cout << "standard efficiency wrong initialized!";
  result = false;
} // if
test.report( result );

// shieldType1: check efficiency changes
cout << "*** Now I change some efficiencies of shieldType1.\n";
shieldType1->setDefenseEfficiency( 2, Shield_Efficiency1 );
shieldType1->setDefenseEfficiency( 5, Shield_Efficiency2 );
shieldType1->setDefenseEfficiency( 8, Shield_Efficiency3 );
cout << "*** Now I check whether shieldType1 is correct";
result = true;
if ( shieldType1->getDefenseEfficiency( 0 ) != 100 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 1 ) != 100 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 2 ) != Shield_Efficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 3 ) != 100 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 4 ) != 100 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 5 ) != Shield_Efficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 6 ) != 100 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 7 ) != 100 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 8 ) != Shield_Efficiency3 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( shieldType1->getStandardEfficiency() != 100 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// shieldType1: check standard efficiency
cout << "*** Now I change the standard efficiency of shieldType1.\n";
shieldType1->setStandardEfficiency( Shield_StanEfficiency1 );
cout << "*** Now I check again whether shieldType1 is correct";
result = true;
if ( shieldType1->getDefenseEfficiency( 0 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 1 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 2 ) != Shield_Efficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 3 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 4 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 5 ) != Shield_Efficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 6 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 7 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 8 ) != Shield_Efficiency3 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( shieldType1->getStandardEfficiency() != Shield_StanEfficiency1 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// shieldType2: creation and check of initialization
cout << "*** Now I create the second TShieldType object (shieldType2).\n";
TShieldType* shieldType2 = new TShieldType( Shield_StanEfficiency2 );
cout << "*** Now I check whether shieldType2 is empty";
result = true;
for( int2 c = 0; c < 10 ; ++c )
{
  if ( shieldType2->getDefenseEfficiency( c ) != Shield_StanEfficiency2 )
  {
    cout << "standard efficiency wrong initialized!";
    result = false;
  } // if
} // for
  if ( shieldType2->getStandardEfficiency() != Shield_StanEfficiency2 )
{
  cout << "standard efficiency wrong initialized!";
  result = false;
} // if
test.report( result );

// shieldType2: check efficiency changes
cout << "*** Now I change some efficiencies of shieldType2.\n";
shieldType2->setDefenseEfficiency( 2, Shield_Efficiency4 );
shieldType2->setDefenseEfficiency( 4, Shield_Efficiency5 );
shieldType2->setDefenseEfficiency( 6, Shield_Efficiency6 );
cout << "*** Now I check whether shieldType2 is correct";
result = true;
if ( shieldType2->getDefenseEfficiency( 0 ) != Shield_StanEfficiency2 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 1 ) != Shield_StanEfficiency2 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 2 ) != Shield_Efficiency4 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 3 ) != Shield_StanEfficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 4 ) != Shield_Efficiency5 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 5 ) != Shield_StanEfficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 6 ) != Shield_Efficiency6 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 7 ) != Shield_StanEfficiency2 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( shieldType2->getDefenseEfficiency( 8 ) != Shield_StanEfficiency2 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( shieldType2->getStandardEfficiency() != Shield_StanEfficiency2 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// test of operator= of TShieldType
cout << "*** Now I check the operator= of TShieldType";  
*shieldType2 = *shieldType1;
result = true;
if ( shieldType1->getDefenseEfficiency( 0 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 1 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 2 ) != Shield_Efficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 3 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 4 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 5 ) != Shield_Efficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 6 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 7 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 8 ) != Shield_Efficiency3 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( shieldType1->getStandardEfficiency() != Shield_StanEfficiency1 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// destruct shieldType2
cout << "*** Now destruct shieldType2\n";
delete shieldType2;

// check copy constructor
cout << "*** Now I use the copy constructor of TShieldType.\n";
shieldType2 = new TShieldType( *shieldType1 );
cout << "*** Now I check whether it worked";  
result = true;
if ( shieldType1->getDefenseEfficiency( 0 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 1 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 2 ) != Shield_Efficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 3 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 4 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 5 ) != Shield_Efficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 6 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 7 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( shieldType1->getDefenseEfficiency( 8 ) != Shield_Efficiency3 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( shieldType1->getStandardEfficiency() != Shield_StanEfficiency1 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

cout << "*** Now testing the operator== of TShieldType";
result = ( *shieldType2 == *shieldType1);
test.report( result );

// destruct shieldType2
cout << "*** Now destruct shieldType2 again.\n";
delete shieldType2;


// test for TShield
cout << "*************************************************************\n";
cout << "*** Now I'm going to test TShield.\n";
TShield testShield;
cout << "*** Now I check whether the shield is empty";
result = check_item( testShield,
                     TItem::SHIELD,
                     "",
                     0,
                     0,
                     0,
                     0,
                     TSubstanceSet());
if ( result ) 
{
  if ( testShield.getHitPoints() != 0 )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testShield.getShieldType() != 0 )
  {
    cout << "shield type wrong!\n";
    result = false;
  } // if
} // if
test.report( result );

cout << "*** Now I will assign the item some basic values.\n";
testShield.setItemName( Shield_NAME );
testShield.setTechLevel( Shield_TECHLEVEL );
testShield.setMass( Shield_MASS );
testShield.setVolume( Shield_VOLUME );
testShield.setSurface( Shield_SURFACE );
dummySet.Add( *GSchalen->Create( Shield_COST ) );
testShield.setCost( dummySet );
dummySet.Clear();
testShield.setHitPoints( Shield_HITPOINTS);
testShield.setShieldType( shieldType1 );

cout << "*** Now I check whether the basic values are saved";
dummySet.Add( *GSchalen->Create( Shield_COST ) );
result = check_item( testShield,
                     TItem::SHIELD,
                     Shield_NAME,
                     Shield_TECHLEVEL,
                     Shield_MASS,
                     Shield_VOLUME,
                     Shield_SURFACE,
                     dummySet);
dummySet.Clear();
if ( result ) 
{
  if ( testShield.getHitPoints() != Shield_HITPOINTS )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testShield.getShieldType() != shieldType1 )
  {
    cout << "shield type wrong!\n";
    result = false;
  } // if
} // if
test.report( result );

cout << "*** Now I create a new TShield object.\n";
TShield* testShield2 = new TShield();
cout << "*** Now I check the operator=";  
*testShield2 = testShield;
dummySet.Add( *GSchalen->Create( Shield_COST ) );
result = check_item( testShield,
                     TItem::SHIELD,
                     Shield_NAME,
                     Shield_TECHLEVEL,
                     Shield_MASS,
                     Shield_VOLUME,
                     Shield_SURFACE,
                     dummySet);
dummySet.Clear();
if ( result ) 
{
  if ( testShield.getHitPoints() != Shield_HITPOINTS )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testShield.getShieldType() != shieldType1 )
  {
    cout << "shield type wrong!\n";
    result = false;
  } // if
} // if
test.report( result );

cout << "*** Now I destruct the TShield object again.\n";
delete testShield2;


cout << "*** Now I use the copy constructor.\n";
testShield2 = new TShield( testShield );
cout << "*** Now I check whether it worked";  

dummySet.Add( *GSchalen->Create( Shield_COST ) );
result = check_item( testShield,
                     TItem::SHIELD,
                     Shield_NAME,
                     Shield_TECHLEVEL,
                     Shield_MASS,
                     Shield_VOLUME,
                     Shield_SURFACE,
                     dummySet);
dummySet.Clear();
if ( result ) 
{
  if ( testShield.getHitPoints() != Shield_HITPOINTS )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testShield.getShieldType() != shieldType1 )
  {
    cout << "shield type wrong!\n";
    result = false;
  } // if
} // if
test.report( result );

cout << "*** Now I destruct the TShield object again.\n";
delete testShield2;

cout << "*** Now I check method getShield Efficiencies";
result = true;
if ( testShield.getShieldEfficiency( 0 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 1 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 2 ) != Shield_Efficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 3 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 4 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 5 ) != Shield_Efficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 6 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 7 ) != Shield_StanEfficiency1 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( testShield.getShieldEfficiency( 8 ) != Shield_Efficiency3 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
test.report( result );



// now check ship design with shield

cout << "*** \n";
cout << "*** Now I put 8 shields onto the design.\n";
testDesign->AddItem( &testShield, 8);
cout << "*** Now I check whether the design has the correct values";
dummySet.Add( *GSchalen->Create(20) );
dummySet2.Add( *GSchalen->Create(33667) );
result = check_design( *testDesign,
                       0,
                       true,
                       false,
                       0,
                       "Battleship",
                       1000000,
                       1005070,
                       20000,
                       15033,
                       15000,
                       13266,
                       1200,
                       dummySet,
                       dummySet2);
test.report( result );
dummySet.Clear();
dummySet2.Clear();


/*
 * $Log: test-item-Shield.cpp,v $
 * Revision 1.10  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.9  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.8  2001/06/16 21:38:03  prolator
 * adjusted to new counter of subfleets in ship design
 *
 * Revision 1.7  2001/06/15 23:26:51  prolator
 * adjusted tests to interface change: GetDamagePoints to GetHitPoints
 *
 * Revision 1.6  2001/06/15 13:55:18  prolator
 * adjusted tests to new classes TArmorType and TShieldType
 *
 * Revision 1.5  2001/06/14 20:59:29  prolator
 * fixed a bug
 *
 * Revision 1.4  2001/06/14 15:46:11  prolator
 * adjusted test to change of the return type of GetShieldType
 *
 * Revision 1.3  2001/06/13 15:47:13  prolator
 * added tests for flags Changeable and Atmospheric
 *
 * Revision 1.2  2001/06/12 21:39:51  prolator
 * corrected tests of costs
 *
 * Revision 1.1  2001/06/12 15:52:09  prolator
 * frist version of tests for shields
 *
 */



