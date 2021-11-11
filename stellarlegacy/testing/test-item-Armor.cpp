// $Id: test-item-Armor.cpp,v 1.11 2002/04/27 00:09:22 prolator Exp $
//
// armor and defense type classes testing
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

#define Armor_NAME "Armor"
#define Armor_TECHLEVEL 26
#define Armor_MASS 13
#define Armor_VOLUME 2
#define Armor_SURFACE 3
#define Armor_COST 230
#define Armor_HITPOINTS 45
#define Armor_StanEfficiency1 50
#define Armor_StanEfficiency2 130
#define Armor_Efficiency1 40
#define Armor_Efficiency2 60
#define Armor_Efficiency3 100
#define Armor_Efficiency4 80
#define Armor_Efficiency5 56
#define Armor_Efficiency6 77
#define Armor_Efficiency7 89

cout << "*************************************************************\n";
cout << "*** Now I'm going to test TArmor and TArmorType.\n";
cout << "*** At first I create two TArmorType objects and set their.\n";
cout << "*** efficiencies against different weapons.\n";
cout << "*** Now I create the first TArmorType object (armorType1).\n";
TArmorType* armorType1 = new TArmorType();
cout << "*** Now I check whether armorType1 is empty";
result = true;
for( int2 c = 0; c < 10 ; ++c )
{
  if ( armorType1->getDefenseEfficiency( c ) != 100 )
  {
    cout << "standard efficiency wrong initialized!";
    result = false;
  } // if
} // for
if ( armorType1->getStandardEfficiency() != 100 )
{
  cout << "standard efficiency wrong initialized!";
  result = false;
} // if
test.report( result );

// armorType1: check efficiency changes
cout << "*** Now I change some efficiencies of armorType1.\n";
armorType1->setDefenseEfficiency( 1, Armor_Efficiency1 );
armorType1->setDefenseEfficiency( 3, Armor_Efficiency2 );
armorType1->setDefenseEfficiency( 4, Armor_Efficiency3 );
armorType1->setDefenseEfficiency( 7, Armor_Efficiency4 );
cout << "*** Now I check whether armorType1 is correct";
result = true;
if ( armorType1->getDefenseEfficiency( 0 ) != 100 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 1 ) != Armor_Efficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 2 ) != 100 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 3 ) != Armor_Efficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 4 ) != 100 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 5 ) != 100 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 6 ) != 100 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 7 ) != Armor_Efficiency4 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 8 ) != 100 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( armorType1->getStandardEfficiency() != 100 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// armorType1: check standard efficiency
cout << "*** Now I change the standard efficiency of armorType1.\n";
armorType1->setStandardEfficiency( Armor_StanEfficiency1 );
cout << "*** Now I check again whether armorType1 is correct";
result = true;
if ( armorType1->getDefenseEfficiency( 0 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 1 ) != Armor_Efficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 2 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 3 ) != Armor_Efficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 4 ) != Armor_Efficiency3 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 5 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 6 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 7 ) != Armor_Efficiency4 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( armorType1->getDefenseEfficiency( 8 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( armorType1->getStandardEfficiency() != Armor_StanEfficiency1 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// armorType2: creation and check of initialization
cout << "*** Now I create the second TArmorType object (armorType2).\n";
TArmorType* armorType2 = new TArmorType(Armor_StanEfficiency2);
cout << "*** Now I check whether armorType2 is empty";
result = true;
for( int2 c = 0; c < 10 ; ++c )
{
  if ( armorType2->getDefenseEfficiency( c ) != Armor_StanEfficiency2 )
  {
    cout << "standard efficiency wrong initialized!";
    result = false;
  } // if
} // for
  if ( armorType2->getStandardEfficiency() != Armor_StanEfficiency2 )
{
  cout << "standard efficiency wrong initialized!";
  result = false;
} // if
test.report( result );

// armorType2: check efficiency changes
cout << "*** Now I change some efficiencies of armorType2.\n";
armorType2->setDefenseEfficiency( 2, Armor_Efficiency5 );
armorType2->setDefenseEfficiency( 4, Armor_Efficiency6 );
armorType2->setDefenseEfficiency( 6, Armor_Efficiency7 );
cout << "*** Now I check whether armorType2 is correct";
result = true;
if ( armorType2->getDefenseEfficiency( 0 ) != Armor_StanEfficiency2 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 1 ) != Armor_StanEfficiency2 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 2 ) != Armor_Efficiency5 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 3 ) != Armor_StanEfficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 4 ) != Armor_Efficiency6 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 5 ) != Armor_StanEfficiency2 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 6 ) != Armor_Efficiency7 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 7 ) != Armor_StanEfficiency2 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 8 ) != Armor_StanEfficiency2 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( armorType2->getStandardEfficiency() != Armor_StanEfficiency2 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// test of operator= of TArmorType
cout << "*** Now I check the operator= of TArmorType";  
*armorType2 = *armorType1;
result = true;
if ( armorType2->getDefenseEfficiency( 0 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 1 ) != Armor_Efficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 2 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 3 ) != Armor_Efficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 4 ) != Armor_Efficiency3 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 5 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 6 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 7 ) != Armor_Efficiency4 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 8 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( armorType2->getStandardEfficiency() != Armor_StanEfficiency1 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

// destruct armorType2
cout << "*** Now destruct armorType2\n";
delete armorType2;

// check copy constructor
cout << "*** Now I use the copy constructor of TArmorType.\n";
armorType2 = new TArmorType( *armorType1 );
cout << "*** Now I check whether it worked";  
result = true;
if ( armorType2->getDefenseEfficiency( 0 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 1 ) != Armor_Efficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 2 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 3 ) != Armor_Efficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 4 ) != Armor_Efficiency3 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 5 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 6 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 7 ) != Armor_Efficiency4 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( armorType2->getDefenseEfficiency( 8 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
  if ( armorType2->getStandardEfficiency() != Armor_StanEfficiency1 )
{
  cout << "standard efficiency wrong initialized!\n";
  result = false;
} // if
test.report( result );

cout << "*** Now testing the operator== of TArmorType";
result = ( *armorType2 == *armorType1);
test.report( result );

// destruct armorType2
cout << "*** Now destruct armorType2 again.\n";
delete armorType2;


// test for TArmor
cout << "*************************************************************\n";
cout << "*** Now I'll create an TArmor object.\n";
TArmor testArmor;
cout << "*** Now I check whether the armor is empty";
result = check_item( testArmor,
                     TItem::ARMOR,
                     "",
                     0,
                     0,
                     0,
                     0,
                     TSubstanceSet());
if ( result ) 
{
  if ( testArmor.getHitPoints() != 0 )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testArmor.getArmorType() != 0 )
  {
    cout << "armor type wrong!\n";
    result = false;
  } // if
} // if
test.report(result);

cout << "*** Now I will assign the item some basic values.\n";
testArmor.setItemName( Armor_NAME );
testArmor.setTechLevel( Armor_TECHLEVEL );
testArmor.setMass( Armor_MASS );
testArmor.setVolume( Armor_VOLUME );
testArmor.setSurface( Armor_SURFACE );
dummySet.Add( *GSchalen->Create( Armor_COST ) );
testArmor.setCost( dummySet );
dummySet.Clear();
testArmor.setHitPoints( Armor_HITPOINTS);
testArmor.setArmorType( armorType1 );

cout << "*** Now I check whether the basic values are saved";
dummySet.Add( *GSchalen->Create( Armor_COST ) );
result = check_item( testArmor,
                     TItem::ARMOR,
                     Armor_NAME,
                     Armor_TECHLEVEL,
                     Armor_MASS,
                     Armor_VOLUME,
                     Armor_SURFACE,
                     dummySet);
dummySet.Clear();
if ( result ) 
{
  if ( testArmor.getHitPoints() != Armor_HITPOINTS )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testArmor.getArmorType() != armorType1 )
  {
    cout << "armor type wrong!\n";
    result = false;
  } // if
} // if
test.report(result);

cout << "*** Now I create a new TArmor object.\n";
TArmor* testArmor2 = new TArmor();
cout << "*** Now I check the operator=";  
*testArmor2 = testArmor;
dummySet.Add( *GSchalen->Create( Armor_COST ) );
result = check_item( testArmor,
                     TItem::ARMOR,
                     Armor_NAME,
                     Armor_TECHLEVEL,
                     Armor_MASS,
                     Armor_VOLUME,
                     Armor_SURFACE,
                     dummySet);
dummySet.Clear();
if ( result ) 
{
  if ( testArmor.getHitPoints() != Armor_HITPOINTS )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testArmor.getArmorType() != armorType1 )
  {
    cout << "armor type wrong!\n";
    result = false;
  } // if
} // if
test.report(result);

cout << "*** Now I destruct the TArmor object again.\n";
delete testArmor2;


cout << "*** Now I use the copy constructor.\n";
testArmor2 = new TArmor( testArmor );
cout << "*** Now I check whether it worked";  

dummySet.Add( *GSchalen->Create( Armor_COST ) );
result = check_item( testArmor,
                     TItem::ARMOR,
                     Armor_NAME,
                     Armor_TECHLEVEL,
                     Armor_MASS,
                     Armor_VOLUME,
                     Armor_SURFACE,
                     dummySet);
dummySet.Clear();
if ( result ) 
{
  if ( testArmor.getHitPoints() != Armor_HITPOINTS )
  {
    cout << "hit points wrong!\n";
    result = false;
  } // if
  if ( testArmor.getArmorType() != armorType1 )
  {
    cout << "armor type wrong!\n";
    result = false;
  } // if
} // if
test.report(result);

cout << "*** Now I destruct the TArmor object again.\n";
delete testArmor2;

cout << "*** Now I check method getArmor Efficiencies";
result = true;
if ( testArmor.getArmorEfficiency( 0 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 0 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 1 ) != Armor_Efficiency1 )
{
  cout << "efficiency 1 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 2 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 2 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 3 ) != Armor_Efficiency2 )
{
  cout << "efficiency 3 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 4 ) != Armor_Efficiency3 )
{
  cout << "efficiency 4 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 5 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 5 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 6 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 6 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 7 ) != Armor_Efficiency4 )
{
  cout << "efficiency 7 wrong!\n";
  result = false;
} // if
if ( testArmor.getArmorEfficiency( 8 ) != Armor_StanEfficiency1 )
{
  cout << "efficiency 8 wrong!\n";
  result = false;
} // if
test.report( result );



// now check ship design with armor

cout << "*** \n";
cout << "*** Now I put 7 armors onto the design.\n";
testDesign->AddItem( &testArmor, 7);
cout << "*** Now I check whether the design has the correct values";
dummySet.Add( *GSchalen->Create(20) );
dummySet2.Add( *GSchalen->Create(12467) );
result = check_design( *testDesign,
                       0,
                       true,
                       false,
                       0,
                       "Battleship",
                       1000000,
                       1004726,
                       20000,
                       15081,
                       15000,
                       13322,
                       1200,
                       dummySet,
                       dummySet2);
test.report(result);
dummySet.Clear();
dummySet2.Clear();


/*
 * $Log: test-item-Armor.cpp,v $
 * Revision 1.11  2002/04/27 00:09:22  prolator
 * now using TTesting
 *
 * Revision 1.10  2002/04/02 22:32:03  prolator
 * some Xet to xet
 *
 * Revision 1.9  2001/06/16 21:38:03  prolator
 * adjusted to new counter of subfleets in ship design
 *
 * Revision 1.8  2001/06/15 23:26:51  prolator
 * adjusted tests to interface change: GetDamagePoints to GetHitPoints
 *
 * Revision 1.7  2001/06/15 13:55:18  prolator
 * adjusted tests to new classes TArmorType and TShieldType
 *
 * Revision 1.6  2001/06/14 15:45:47  prolator
 * adjusted test to change of the return type of GetArmorType
 *
 * Revision 1.5  2001/06/13 15:47:13  prolator
 * added tests for flags Changeable and Atmospheric
 *
 * Revision 1.4  2001/06/12 21:39:51  prolator
 * corrected tests of costs
 *
 * Revision 1.3  2001/06/12 15:56:26  prolator
 * fixed mistake in comment
 *
 * Revision 1.2  2001/06/12 13:50:30  prolator
 * added tests for TDefenseType (operator=, operator==, copy constructor) and TArmor
 *
 * Revision 1.1  2001/06/12 11:51:40  prolator
 * first version of tests for TArmor and TArmorType
 *
 */



