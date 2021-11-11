// $Id: test-link.cpp,v 1.10 2002/05/10 10:40:42 mkrohn5 Exp $

// Test Link Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#include "common/link.h"
#include "common/datapackage.h"
#include "testing/testing.h"

using namespace std;





//----------------------------------------  Prototypes  ----------------------------------------

class TLinkableTest;
void testObjectIDClassFailed( TTesting& test, const TLink<TLinkableTest>& l1, const TLink<TLinkableTest>& l2 );
bool testFailed();





//----------------------------------------  Definition of a test class  ----------------------------------------

class TLinkableTest : public TLinkable
{
  public:
    TLinkableTest( int i ) : TLinkable()  { fVal = i;  fDLink.setNull(); }
    int getValue() const  { return fVal; }

    TDoubleLink<TLinkableTest> fDLink;

  private:
    int fVal;
};





//----------------------------------------  Functions  ----------------------------------------

void testFailed( TTesting& test, const TLink<TLinkableTest>& l1, const TLink<TLinkableTest>& l2 )
{
  test.report( false );
  cout << "\tlink1: " << l1 << endl;
  cout << "\tlink2: " << l2 << endl;
}



bool testLinkClass()
{
TLinkableTest a(1), b(2), c(3);
TLink<TLinkableTest> la, lb, lc;
TTesting test;

//----------------------------------------  test for null links

  cout << "null link--getDest()";
  if ( la.getDest() != 0 )  testFailed( test, la, lb );
  else                      test.report( true );

  cout << "null link--getDestID()";
  if ( la.getDest() != 0 )  testFailed( test, la, lb );
  else                      test.report( true );

  cout << "null link--isNull()";
  if ( la.isNull() == false )  testFailed( test, la, lb );
  else                         test.report( true );

  cout << "null link--isUpdated()";
  if ( la.isUpdated() == false )  testFailed( test, la, lb );
  else                            test.report( true );

  cout << "null link--isValid()";
  if ( la.isValid() == true )  testFailed( test, la, lb );
  else                         test.report( true );

  cout << "null link--operator=";
  lb.setDest( &b );
  lb = la;
  if ( la.getDest() != lb.getDest() )  testFailed( test, la, lb );
  else                                 test.report( true );

  cout << "null link--operator==";
  if ( !(la == lb) )  testFailed( test, la, lb );
  else                test.report( true );

  cout << "null link--setNull()";
  la.setDest( &a );
  la.setNull();
  if ( la.isNull() == false )  testFailed( test, la, lb );
  else                         test.report( true );

  cout << "null link--setDest(0)";
  la.setDest( &a );
  la.setDest( (TLinkableTest*) 0 );
  if ( la.isNull() == false )  testFailed( test, la, lb );
  else                         test.report( true );

  cout << "load and save for null link";
  la.setNull();
  TDataPackageList* dplist = new TDataPackageList;
  la.save( dplist, "link-test", true );
  lb.load( dplist, "link-test", true );
  if ( la != lb )  {
    dplist->showContent();                                 // write information to the log file
    testFailed( test, la, lb );
  }
  else test.report( true );
  delete dplist;

//---------------------------------------- tests for real links

  cout << "getDest()";
  la.setDest( &a );
  if ( la.getDest() != &a )  testFailed( test, la, lb );
  else                       test.report( true );

  cout << "getDestID()";
  if ( la.getDestID() != a.getID() )  testFailed( test, la, lb );
  else                                test.report( true );

//---------------------------------------- tests for TLinkable / TDoubleLink

  TLinkBaseList l;
  TLinkBaseList::iterator it;
  int found;

  cout << "no link--getLinkedByList()";
  la.setNull();
  lb.setNull();
  lc.setNull();
  l = a.getLinkedByList();
  if ( l.size() > 0 )  testFailed( test, la, lb );
  else                 test.report( true );

  cout << "one link--getLinkedByList()";
  la.setDest( &a );

  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
  }
  if ( found==1 && l.size()==1 )  test.report( true );
  else                            testFailed( test, la, lb );

  cout << "two links--getLinkedByList()";
  lb.setDest( &a );
  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
    if ( *it == &lb )  found += 2;
  }
  if ( found==3 && l.size()==2 )  test.report( true );
  else                            testFailed( test, la, lb );

  cout << "three links--getLinkedByList()";
  lc.setDest( &a );
  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
    if ( *it == &lb )  found += 2;
    if ( *it == &lc )  found += 4;
  }
  if ( found==7 && l.size()==3 )  test.report( true );
  else                            testFailed( test, la, lb );

  cout << "lb-->0 => is link removed from linkedByList?";
  lb.setNull();
  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
    if ( *it == &lb )  found += 2;
    if ( *it == &lc )  found += 4;
  }
  if ( found==5 && l.size()==2 )  test.report( true );
  else                            testFailed( test, la, lb );

  cout << "la-->b => is link removed from linkedByList?";
  la.setDest( &b );
  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
    if ( *it == &lb )  found += 2;
    if ( *it == &lc )  found += 4;
  }
  if ( found==4 && l.size()==1 )  test.report( true );
  else                            testFailed( test, la, lb );

  cout << "lc-->b => is link removed from linkedByList?";
  lc.setDest( &b );                                        // la-->b, lb-->0, lc-->b
  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
    if ( *it == &lb )  found += 2;
    if ( *it == &lc )  found += 4;
  }
  if ( found==0 && l.size()==0 )  test.report( true );
  else                            testFailed( test, la, lb );

  cout << "lc-->b => is link removed from linkedByList?";
  lc.setDest( &b );                                        // la-->b, lb-->0, lc-->b
  l = a.getLinkedByList();
  found = 0;
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( *it == &la )  found += 1;
    if ( *it == &lb )  found += 2;
    if ( *it == &lc )  found += 4;
  }
  if ( found==0 && l.size()==0 )  test.report( true );
  else                            testFailed( test, la, lb );

//  cout << "does the inverse link + double link work? (empty list)";







  a.fDLink.setDest( &b );
  a.fDLink.setInverse( &a );                               // a.fDLink-->b,  lb-->b


  l = b.getLinkedByList();
  for ( it=l.begin(); it!=l.end(); it++ )  {
    if ( (*it)->getType() == TLinkBase::DOUBLE_LINK )  {
      TDoubleLink<TLinkableTest>* d = dynamic_cast< TDoubleLink<TLinkableTest>* >( (*it) );
      if ( d->getDest() != &b || d->getInverse() == &a )  {

      }
    }
  }


/*
TLinkableTest *a, *b, *c;
TLink<TLinkableTest> *la, *lb, *lc;
ifstream in;
ofstream out;

  a = new TLinkableTest( 1 );
  b = new TLinkableTest( 2 );
  c = new TLinkableTest( 3 );

  la = new TLink<TLinkableTest>( a );
  lb = new TLink<TLinkableTest>();
  lb->SetLink( b );
  lc = new TLink<TLinkableTest>( *la );

  //----------  TEST 1  ----------
  // la->a, lb->b, lc->a
  LOG("-","TestLinkClass") << "Test1: " << flush;
  if ( *la == *lb )
  {
    LOG("-","TestLinkClass") << "failed!" << endl;
    ELOG("-","TestLinkClass") << "Links should not be equal but they are!" << endl
      << "Link1: " << *la << "   TLink2: " << *lb << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  //----------  TEST 2  ----------
  LOG("-","TestLinkClass") << "Test2: " << flush;
  if ( *lb == *lc )
  {
    LOG("-","TestLinkClass") << "failed!" << endl;
    ELOG("-","TestLinkClass") << "Links should not be equal but they are!" << endl
      << "Link1: " << *lb << "   TLink2: " << *lc << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  //----------  TEST 3  ----------
  LOG("-","TestLinkClass") << "Test3: " << flush;
  if ( *la != *lc )
  {
    LOG("-","TestLinkClass") << "failed!" << endl;
    ELOG("-","TestLinkClass") << "Links should be equal but they are not!" << endl
      << "Link1: " << *la << "   TLink2: " << *lc << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  lc->SetLink( c );

  // la->a, lb->b, lc->c, now test load&save routines
  out.open( "test_link_class.tmp", ios::out );
  la->Save( out );
  lb->Save( out );
  a->Save( out );
  b->Save( out );
  c->Save( out );
  lc->Save( out );
  out.close();

  delete a;  delete b;  delete c;
  delete la; delete lb; delete lc;
  a = new TLinkableTest( 1 );                              // a has a new ID now!
  la = new TLink<TLinkableTest>();                         // la points to 0
  b = new TLinkableTest( 2 );                              // b has a new ID now!
  lb = new TLink<TLinkableTest>();                         // lb points to 0
  c = new TLinkableTest( 3 );                              // c has a new ID now!
  lc = new TLink<TLinkableTest>();                         // lc points to 0


  in.open("test_link_class.tmp", ios::in);
  la->Load( in );
  lb->Load( in );
  a->Load( in );
  b->Load( in );
  c->Load( in );
  lc->Load( in );
  in.close();


  //----------  TEST 4  ----------
  // After loading the stuff from disk the IDs may changed but
  // the links should point to the same object
  LOG("-","TestLinkClass") << "Test4: " << flush;
  if ( a->GetValue()!=1 || b->GetValue()!=2 || c->GetValue()!=3 )
  {
    LOG("-","TestLinkClass") << "failed!" << endl;
    ELOG("-","TestLinkClass") << "Load & Save test failed!" << endl
      << "Link1: " << *la << "   TLink2: " << *lb << "   TLink3: " << *lc << endl
      << "Obj1 : " << a->GetID()  << "   Obj2:   " << b->GetID()  << "   Obj3:   "
      << c->GetID() << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  delete la; delete lb; delete lc;

  la = new TLink<TLinkableTest>();                         // null link
  lb = new TLink<TLinkableTest>( b );                      // real link
  lc = new TLink<TLinkableTest>();                         // null link at the moment
//  in.open("test_link_class.tmp", ios::in);
//  lc->Load( in );
//  in.close();

  //----------  TEST 5  ----------
  // la=null link, lb=real link, lc=link that needs an update
  LOG("-","TestLinkClass") << "Test5: " << flush;
  if ( la->IsNull() == false )
  {
    LOG("-","TestLinkClass") << "failed!" << endl;
    ELOG("-","TestLinkClass") << "Link should be a null link: " << la->GetPointerToDest()
      << "   " << la->GetDestID() << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  //----------  TEST 6  ----------
  LOG("-","TestLinkClass") << "Test6: " << flush;
  if ( la->IsValid() == true )
  {
    LOG("-","TestLinkClass") << "failed!" << endl;
    ELOG("-","TestLinkClass") << "Link should not be valid: "
      << la->GetPointerToDest() << "   " << la->GetDestID() << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  //----------  TEST 7  ----------
  LOG("-","TestLinkClass") << "Test7: " << flush;
  if ( la->IsUpdated() == false )
  {
    ELOG("-","TestLinkClass") << "Link should not need an update: "
      << la->GetPointerToDest() << "   " << la->GetDestID() << endl;
    bReturn = false;
  }
  else
    LOG("-","TestLinkClass") << "o.k." << endl;

  delete a;  delete b;  delete c;
  delete la;  delete lb;  delete lc;

  */

  cout << "passed " << test.getSuccess() << " out of " << test.getChecksDone() << " tests." << endl;
  return test.result();
}

