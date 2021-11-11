// $Id: datapackage.cpp,v 1.29 2002/07/03 18:01:32 mkrohn5 Exp $

// Data Package Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>
//             Alberto Barsella, <Alberto.Barsella@univ-lille1.fr>

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#include <algorithm>

#include "common/datapackage.h"
#include "common/link.h"
#include "common/point.h"

#include <iomanip>

using namespace std;





//----------------------------------------  static member definition  ----------------------------------------

#ifdef SECURE_MODE
  TLeakChecker TDataPackage::lc;
  TLeakChecker TDataPackageList::lc;
#endif // SECURE_MODE





//----------------------------------------  Comparison Predicate  ----------------------------------------

class CompareToIdentifier : public unary_function<TDataPackage*,bool> {
  const string ident;
public:
  explicit CompareToIdentifier(const string& id) : ident(id) { }
  bool operator()(const TDataPackage* test) const
    { return ( test->GetIdentifier() == ident ); }
};





//----------------------------------------  class TDataPackage  ----------------------------------------

TDataPackage :: TDataPackage()
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
}



TDataPackage :: TDataPackage( const string& sIdentifier, const bool* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();

  SetData( sIdentifier, pData );
}



TDataPackage :: TDataPackage( const string& sIdentifier, const double* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();

  SetData( sIdentifier, pData );
}



TDataPackage :: TDataPackage( const string& sIdentifier, const int2* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
  SetData( sIdentifier, pData );
}



TDataPackage :: TDataPackage( const string& sIdentifier, const int4* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
  SetData( sIdentifier, pData );
}


TDataPackage :: TDataPackage( const string& sIdentifier, const string* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
  SetData( sIdentifier, pData );
}



TDataPackage :: TDataPackage( const string& sIdentifier, const TDataPackageList* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
  SetData( sIdentifier, pData );
}



TDataPackage :: TDataPackage( const string& sIdentifier, const TObjectID* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
  SetData( sIdentifier, pData );
}



TDataPackage :: TDataPackage( const string& sIdentifier, const TPoint* pData )
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackage","TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  Reset();
  SetData( sIdentifier, pData );
}



TDataPackage :: ~TDataPackage()
{
  #ifdef SECURE_MODE
    lc--;
    LOG("TDataPackage","~TDataPackage") << "#TDataPackage: " << lc.Get() << endl;
  #endif // SECURE_MODE
  CheckAutoDelete();
}



bool TDataPackage :: GetAutoDeleteMode() const
{
  return bAutoDelete;
}



const string& TDataPackage :: GetIdentifier() const
{
  return sIdentifier;
}



const TDataPackage::tType TDataPackage :: GetType() const
{
  return type;
}



TDataPackage :: operator bool*() const
{
  if ( type != BOOL )
  {
    ELOG( "TDataPackage", "operator bool*()" )
      << "type mismatch when requesting parameter " + sIdentifier << endl
      << "type received: " << type << endl;
    Fatal( "TDataPackage", "operator bool*()", "failed conversion", -1 );
  }
  return (bool*) pData;
}



TDataPackage :: operator double*() const
{
  if ( type != DOUBLE )
  {
    string sMsg = "Type mismatch when requesting parameter " + sIdentifier
                  + "\nType received: ";
    sMsg += type;
    Fatal( "TDataPackage", "operator double*()", sMsg, -1 );
  }
  return (double*) pData;
}



TDataPackage :: operator int2*() const
{
  if ( type != INTEGER_2 )
  {
    Fatal( "TDataPackage", "operator int2*()",
      "Type mismatch when requesting parameter " + sIdentifier, -1 );
  }
  return (int2*) pData;
}



TDataPackage :: operator int4*() const
{
  if ( type != INTEGER_4 )
  {
    Fatal( "TDataPackage", "operator int4*()",
      "Type mismatch when requesting parameter " + sIdentifier, -1 );
  }
  return (int4*) pData;
}



TDataPackage :: operator string*() const
{
  if ( type != STRING )
  {
    Fatal( "TDataPackage", "operator string*()",
      "Type mismatch when requesting parameter " + sIdentifier, -1 );
  }
  return (string*) pData;
}



TDataPackage :: operator TDataPackageList*() const
{
  if ( type != DATA_PACKAGE_LIST )
  {
    Fatal( "TDataPackage", "operator TDataPackageList*()",
      "Type mismatch when requesting parameter " + sIdentifier, -1 );
  }
  return (TDataPackageList*) pData;
}



TDataPackage :: operator TObjectID*() const
{
  if ( type != ID )
  {
    Fatal( "TDataPackage", "operator TObjectID*()",
      "Type mismatch when requesting parameter " + sIdentifier, -1 );
  }
  return (TObjectID*) pData;
}



TDataPackage :: operator TPoint*() const
{
  if ( type != POINT )
  {
    Fatal( "TDataPackage", "operator TPoint*()",
      "Type mismatch when requesting parameter " + sIdentifier, -1 );
  }
  return (TPoint*) pData;
}



void TDataPackage :: SetAutoDeleteMode( bool bAutoDelete )
{
  this->bAutoDelete = bAutoDelete;
}



void TDataPackage :: SetData( const string& sIdentifier, const bool* pData )
{
  CheckAutoDelete();
  this->type = BOOL;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const double* pData )
{
  CheckAutoDelete();
  this->type = DOUBLE;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const int2* pData )
{
  CheckAutoDelete();
  this->type = INTEGER_2;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const int4* pData )
{
  CheckAutoDelete();
  this->type = INTEGER_4;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const TDataPackageList* pData )
{
  CheckAutoDelete();
  this->type = DATA_PACKAGE_LIST;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const TObjectID* pData )
{
  CheckAutoDelete();
  this->type = ID;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const TPoint* pData )
{
  CheckAutoDelete();
  this->type = POINT;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}



void TDataPackage :: SetData( const string& sIdentifier, const string* pData )
{
  CheckAutoDelete();
  this->type = STRING;
  this->sIdentifier = sIdentifier;
  this->pData = (void*) pData;
}





//----------------------------------------  Private  ----------------------------------------

void TDataPackage :: CheckAutoDelete()
{
  if ( bAutoDelete==true && pData != 0 )
  {
    switch( type )
    {
      case BOOL:               delete (bool*) pData;              break;
      case DATA_PACKAGE_LIST:  delete (TDataPackageList*) pData;  break;
      case DOUBLE:             delete (double*) pData;            break;
      case ID:                 delete (TObjectID*) pData;         break;
      case INTEGER_2:          delete (int2*) pData;              break;
      case INTEGER_4:          delete (int4*) pData;              break;
      case POINT:              delete (TPoint*) pData;            break;
      case STRING:             delete (string*) pData;            break;
      default:
        WLOG("TDataPackage","CheckAutoDelete")
          << "unknown data type: " << type << endl
          << "object not deleted" << endl;
        break;
    }
    pData = 0;
  }
}



void TDataPackage :: Reset()
{
  // do not even think of adding a CheckAutoDelete() call here,
  // since the values might not be initialized at all
  pData = 0;
  bAutoDelete = false;
}





//----------------------------------------  class TDataPackageList  ----------------------------------------

TDataPackageList :: TDataPackageList() : deque<TDataPackage*>()
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TDataPackageList","TDataPackageList")
       << "#TDataPackageList: " << lc.Get() << endl;
  #endif // SECURE_MODE
}



TDataPackageList :: ~TDataPackageList()
{
  #ifdef SECURE_MODE
    lc--;
    LOG("TDataPackageList","~TDataPackageList")
       << "#TDataPackageList: " << lc.Get() << endl;
  #endif // SECURE_MODE
  DeleteAll();
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const bool* pData,
                              bool bUnique, bool bAutoDelete )
{
TDataPackage* data;

  if ( bUnique == true && Search(sIdentifier) != 0 )
  {
    LOG("TDataPackageList","add") << "identifier " << sIdentifier
      << " is already used!" << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, pData );
  data->SetAutoDeleteMode( bAutoDelete );
  push_back( data );

  return true;
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const double* pData,
                              bool bUnique, bool bAutoDelete )
{
TDataPackage* data;

  if ( bUnique == true && Search(sIdentifier) != 0 )
  {
    LOG("TDataPackageList","add") << "identifier " << sIdentifier
      << " is already used!" << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, pData );
  data->SetAutoDeleteMode( bAutoDelete );
  push_back( data );

  return true;
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const int2* pData,
                              bool bUnique, bool bAutoDelete )
{
TDataPackage* data;

  if ( bUnique == true && Search(sIdentifier) != 0 )
  {
    LOG("TDataPackageList","add") << "identifier " << sIdentifier
      << " is already used!" << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, pData );
  data->SetAutoDeleteMode( bAutoDelete );
  push_back( data );

  return true;
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const int4* pData,
                              bool bUnique, bool bAutoDelete )
{
TDataPackage* data;

  if ( bUnique == true && Search(sIdentifier) != 0 )
  {
    LOG("TDataPackageList","add") << "identifier " << sIdentifier
      << " is already used!" << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, pData );
  data->SetAutoDeleteMode( bAutoDelete );
  push_back( data );

  return true;
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const string* pData,
                              bool bUnique, bool bAutoDelete )
{
TDataPackage* data;

  if ( bUnique == true && Search(sIdentifier) != 0 )
  {
    LOG("TDataPackageList","add") << "identifier " << sIdentifier
      << " is already used!" << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, pData );
  data->SetAutoDeleteMode( bAutoDelete );
  push_back( data );

  return true;
}



bool TDataPackageList :: add( const string& sIdentifier, const TDataPackageList* pData,
                              bool bUnique, bool bAutoDelete )
{
  if ( pData == this )  {                                  // something strange is going on
    WLOG("TDataPackageList","add")
      << "You can not add TDataPackageList to itself!" << endl;
  }

  if ( bUnique == true && Search(sIdentifier) != 0 )  {
    LOG("TDataPackageList","add") << "identifier " << sIdentifier
      << " is already used!" << endl;
    return false;
  }

  TDataPackage* data = new TDataPackage( sIdentifier, pData );
  data->SetAutoDeleteMode( bAutoDelete );
  push_back( data );

  return true;
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const TObjectID* pData,
                              bool bUnique, bool bAutoDelete )
{
  // this case is somewhat special, since the TObjectID offers a save method
  // which is everything we need here
  return pData->save( this, sIdentifier, bUnique, bAutoDelete );
}



// bUnique=true, bAutoDelete=false
bool TDataPackageList :: add( const string& sIdentifier, const TPoint* pData,
                              bool bUnique, bool bAutoDelete )
{
  // this case is somewhat special, since the TObjectID offers a save method
  // which is everything we need here
  return pData->save( this, sIdentifier, bUnique, bAutoDelete );
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const bool& data, bool unique )
{
  bool* temp = new bool;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );            
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const double& data, bool unique )
{
  double* temp = new double;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const int2& data, bool unique )
{
  int2* temp = new int2;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const int4& data, bool unique )
{
  int4* temp = new int4;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const string& data, bool unique )
{
  string* temp = new string;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const TObjectID& data, bool unique )
{
  TObjectID* temp = new TObjectID;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );
}



// unique=true
bool TDataPackageList::addCopy( const string& identifier, const TPoint& data, bool unique )
{
  TPoint* temp = new TPoint;
  *temp = data;
  // setting autodelete to true (the data will be deleted automatically)
  return add( identifier, temp, unique, true );
}



void TDataPackageList :: DeleteAll()
{
deque<TDataPackage*>::iterator it;

  for ( it=begin(); it!=end(); it++ )
  {
    delete *it;                                            // delete the data packages
  }
  clear();                                                 // delete the list itself
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, bool* pData, bool bUnique )
{
  TDataPackage* pPackage = getAndExtractPackage( sIdentifier, bUnique );
  if ( pPackage == 0 )  return false;

  *pData = *( (bool*) *pPackage );                         // cast TDataPackage to bool*
  delete pPackage;                                         // delete the package
  return true;
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, double* pData, bool bUnique )
{
  TDataPackage* pPackage = getAndExtractPackage( sIdentifier, bUnique );
  if ( pPackage == 0 )  return false;


  *pData = *( (double*) *pPackage );                       // cast TDataPackage to double*
  delete pPackage;                                         // delete the package
  return true;
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, int2* pData, bool bUnique )
{
  TDataPackage* pPackage = getAndExtractPackage( sIdentifier, bUnique );
  if ( pPackage == 0 )  return false;

  *pData = *( (int2*) *pPackage );                         // cast TDataPackage to int2*
  delete pPackage;                                         // delete the package
  return true;
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, int4* pData, bool bUnique )
{
  TDataPackage* pPackage = getAndExtractPackage( sIdentifier, bUnique );
  if ( pPackage == 0 )  return false;

  *pData = *( (int4*) *pPackage );                         // cast TDataPackage to int4*
  delete pPackage;                                         // delete the package
  return true;
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, string* pData, bool bUnique )
{
  TDataPackage* pPackage = getAndExtractPackage( sIdentifier, bUnique );
  if ( pPackage == 0 )  return false;

  *pData = *( (string*) *pPackage );                       // cast TDataPackage to string*
  delete pPackage;                                         // delete the package
  return true;
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, TDataPackageList* pData,
                              bool bUnique )
{
  TDataPackage* pPackage = getAndExtractPackage( sIdentifier, bUnique );
  if ( pPackage == 0 )  return false;

  // The following is a bit confusing. It might be helpful to look at the RFC
  // which deals with loading and saving (the section about TPackageDataList).

  // cast TDataPackage to TDataPackageList*
  // note: the operator= will create a duplicate of the list (not of the datapackages)
  *pData = *( (TDataPackageList*) *pPackage );             // data extracted and copied

  // delete old sublist without deleting their packages.
  // (The new list is *pData and this list refers to the same old packages.
  // All information is now stored in pData.)
  ((TDataPackageList*) *pPackage)->clear();
  delete ((TDataPackageList*) *pPackage);                  // old list is now completly deleted
  // delete the old datapackage, but not the content of the datapackage
  // (since we already deleted the old list, see above)
  pPackage->SetAutoDeleteMode( false );
  delete pPackage;

  return true;
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, TObjectID* pData, bool bUnique )
{
  // this case is somewhat special, since the TObjectID offers a load method
  // which is everything we need here
  return pData->load( this, sIdentifier, bUnique );
}



// bUnique=true
bool TDataPackageList :: getAndDelete( const string& sIdentifier, TPoint* pData, bool bUnique )
{
  // this case is somewhat special, since the TPoint offers a load method
  // which is everything we need here
  return pData->load( this, sIdentifier, bUnique );
}



// unique=true, valid=0
bool TDataPackageList :: getBool( const string& identifier, bool unique, bool* valid ) const
{
  TDataPackage* package = getPackage( identifier, unique );

  if ( package == 0 )  {
    if ( valid != 0 )  *valid = false;                     // invalid package
    return false;
  }
  if ( valid != 0 )  *valid = true;                        // valid package

  return *( (bool*) *package );
}



// unique=true, valid=0
double TDataPackageList :: getDouble( const string& identifier, bool unique, bool* valid ) const
{
  TDataPackage* package = getPackage( identifier, unique );

  if ( package == 0 )  {
    if ( valid != 0 )  *valid = false;                     // invalid package
    return 0.0;
  }
  if ( valid != 0 )  *valid = true;                        // valid package

  return *( (double*) *package );
}



// unique=true, valid=0
int2 TDataPackageList :: getInt2( const string& identifier, bool unique, bool* valid ) const
{
  TDataPackage* package = getPackage( identifier, unique );

  if ( package == 0 )  {
    if ( valid != 0 )  *valid = false;                     // invalid package
    return 0;
  }
  if ( valid != 0 )  *valid = true;                        // valid package

  return *( (int2*) *package );
}



// unique=true, valid=0
int4 TDataPackageList :: getInt4( const string& identifier, bool unique, bool* valid ) const
{
  TDataPackage* package = getPackage( identifier, unique );

  if ( package == 0 )  {
    if ( valid != 0 )  *valid = false;                     // invalid package
    return 0;
  }
  if ( valid != 0 )  *valid = true;                        // valid package

  return *( (int4*) *package );
}



// unique=true, valid=0
const string TDataPackageList :: getString( const string& identifier, bool unique, bool* valid ) const
{
  TDataPackage* package = getPackage( identifier, unique );

  if ( package == 0 )  {
    if ( valid != 0 )  *valid = false;                     // invalid package
    return 0;
  }
  if ( valid != 0 )  *valid = true;                        // valid package

  return *( (string*) *package );
}



// unique=true, valid=0
const TPoint TDataPackageList :: getPoint( const string& identifier, bool unique, bool* valid ) const
{
  TDataPackage* package = getPackage( identifier, unique );

  if ( package == 0 )  {
    if ( valid != 0 )  *valid = false;                     // invalid package
    return TPoint(0);
  }
  if ( valid != 0 )  *valid = true;                        // valid package

  return *( (TPoint*) *package );
}



TDataPackageList& TDataPackageList :: operator=( const TDataPackageList& src )
{
  if ( this == &src )  return *this;                       // src and dest are the same

  DeleteAll();                                             // delete everything in the dest list
  // the list is now empty
  // call base-class version of operator=() => base-class assignment
  deque<TDataPackage*>::operator=( src );
  return *this;
}



bool TDataPackageList :: save( ofstream& out )
{
bool bReturn = true;
string sBlockType;
TDataPackage* p;
deque<TDataPackage*>::const_iterator it;

  p = SearchUnique( "blocktype" );
  if ( p == 0 )
  {
    LOG("TDataPackageList","save") << "No data package \"blocktype\" found or not unique." << endl;
    return false;
  }

  sBlockType = *( (string*) *p );
  out << sBlockType << " {" << endl;
  for ( it=begin(); it!=end(); it++ )
  {
    if ( (*it)->GetIdentifier() == "blocktype" )  continue;     // do not write the blocktype again
    bReturn &= WriteDataPackage( out, *(*it), 2 );
  }
  out << "}" << endl;

  return bReturn;
}



TDataPackage* TDataPackageList :: Search( const string& sIdentifier ) const
{
deque<TDataPackage*>::const_iterator obj;

  obj = find_if( begin(), end(), CompareToIdentifier(sIdentifier) );

  if ( obj != end() )
  {
    TDataPackage* save = (*obj);
    return save;
  }

  return ( 0 );
}



TDataPackage* TDataPackageList :: SearchUnique( const string& sIdentifier ) const
{
deque<TDataPackage*>::const_iterator obj;

  obj = find_if( begin(), end(), CompareToIdentifier(sIdentifier) );

  if ( obj != end() )
  {
    // ensure it's unique
    if ( find_if( obj+1, this->end(), CompareToIdentifier(sIdentifier)) != this->end() )
    {
      LOG("TDataPackageList", "SearchUnique")
        << "duplicate identifier " << sIdentifier << " when requesting unique." << endl;
      return 0;
    }

    TDataPackage* save = (*obj);
    return save;
  }

  return ( 0 );
}



TDataPackage* TDataPackageList :: SearchAndExtract( const string& sIdentifier )
{
deque<TDataPackage*>::iterator obj;

  obj = find_if( begin(), end(), CompareToIdentifier(sIdentifier));

  if ( obj != end() )
  {
    TDataPackage* save = (*obj);
    erase( obj );
    return save;
  }

  return ( 0 );
}



TDataPackage* TDataPackageList :: SearchAndExtractUnique( const string& sIdentifier )
{
deque<TDataPackage*>::iterator obj;

  LOG("TDataPackageList","SearchAndExtractUnique") << "looking for: " << sIdentifier << endl;
  obj = find_if( this->begin(), this->end(), CompareToIdentifier(sIdentifier) );

  if ( obj != this->end() )
  {
    LOG("TDataPackageList","SearchAndExtractUnique") << sIdentifier << " found!" << endl;

    // ensure it's unique
    if ( find_if( obj+1, this->end(), CompareToIdentifier(sIdentifier)) !=
      this->end() )
    {
      WLOG("TDataPackageList", "SearchAndExtractUnique")
        << "duplicate identifier " << sIdentifier << " when requesting unique." << endl;
      return 0;
    }
    TDataPackage* save = (*obj);
    this->erase( obj );
    return save;
  }

    LOG("TDataPackageList","SearchAndExtractUnique") << sIdentifier << " not found!" << endl;
  return ( 0 );
}



void TDataPackageList :: set( const string& identifier, bool value )
{
  TDataPackage* dp = SearchUnique( identifier );

  if ( dp == 0 ) {
    bool* temp = new bool;
    add( identifier, temp, true, true );
    *temp = value;
  }
  else {
    *((bool*) *dp) = value;
  }
}



void TDataPackageList :: set( const string& identifier, double value )
{
  TDataPackage* dp = SearchUnique( identifier );

  if ( dp == 0 ) {
    double* temp = new double;
    add( identifier, temp, true, true );
    *temp = value;
  }
  else {
    *((double*) *dp) = value;
  }
}



void TDataPackageList :: set( const string& identifier, int2 value )
{
  TDataPackage* dp = SearchUnique( identifier );

  if ( dp == 0 ) {
    int2* temp = new int2;
    add( identifier, temp, true, true );
    *temp = value;
  }
  else {
    *((int2*) *dp) = value;
  }
}



void TDataPackageList :: set( const string& identifier, int4 value )
{
  TDataPackage* dp = SearchUnique( identifier );

  if ( dp == 0 ) {
    int4* temp = new int4;
    add( identifier, temp, true, true );
    *temp = value;
  }
  else {
    *((int4*) *dp) = value;
  }
}



void TDataPackageList :: set( const string& identifier, const string& value )
{
  TDataPackage* dp = SearchUnique( identifier );

  if ( dp == 0 ) {
    string* temp = new string;
    add( identifier, temp, true, true );
    *temp = value;
  }
  else {
    *((string*) *dp) = value;
  }
}



void TDataPackageList :: set( const string& identifier, const char* value )
{
  set( identifier, (string) value );
}



void TDataPackageList :: set( const string& identifier, const TPoint& value )
{
  TDataPackage* dp = SearchUnique( identifier );

  if ( dp == 0 ) {
    TPoint* temp = new TPoint;
    add( identifier, temp, true, true );
    *temp = value;
  }
  else {
    *((TPoint*) *dp) = value;
  }
}



// indent=0
void TDataPackageList :: showContent( int indent ) const
{
int i;
string s;
deque<TDataPackage*>::const_iterator it;

  if ( indent == 0 )  {                                    // show #packages only one time
    LOG("TDataPackageList","showContent")
      << "currently there is(are) " << this->size()
      << " package(s) in this datapackage list:" << endl;
  }

  for ( it=begin(); it!=end(); it++ )  {
    s = "";
    for ( i=0; i<indent; i++ )  s+="    ";
    LOG("TDataPackageList","showContent")
      << s << (*it)->GetIdentifier() << ", " << (*it)->GetAutoDeleteMode() << endl;
    if ( (*it)->GetType() == TDataPackage::DATA_PACKAGE_LIST )
    {
      ((TDataPackageList*) *(*it))->showContent( indent+1 );
    }
  }
}





//----------------------------------------  Private  ----------------------------------------

TDataPackage* TDataPackageList :: getAndExtractPackage( const string& identifier, bool unique )
{
TDataPackage* package;

  if ( unique == true )  package = SearchAndExtractUnique( identifier );
  else                   package = SearchAndExtract( identifier );

  if ( package == 0 ) {
    LOG("TDataPackageList","getAndExtractPackage")
      << "missing identifier or not unique: " << endl
      << "identifier: " << identifier << ", unique: " << unique << endl;
  }
  return package;
}



TDataPackage* TDataPackageList :: getPackage( const string& identifier, bool unique ) const
{
TDataPackage* package;

  if ( unique == true )  package = SearchUnique( identifier );
  else                   package = Search( identifier );

  if ( package == 0 ) {
    LOG("TDataPackageList","getPackage") << "missing identifier or not unique: " << endl
      << "identifier: " << identifier << ", unique: " << unique << endl;
  }

  return package;
}



void TDataPackageList :: Indent( ofstream& out, int2 iIndent ) const
{
int i;

  for ( i=0; i<iIndent; i++ )  out << " ";                 // write a number of spaces
}



// iIndent=0
bool TDataPackageList :: WriteDataPackage( ofstream& out,
                                           const TDataPackage& package, int2 iIndent ) const
{
bool bReturn = true;
TDataPackageList* pList;
deque<TDataPackage*>::const_iterator it;

  Indent( out, iIndent );                                  // write a number of spaces

  out << package.GetIdentifier() << " = ";
  switch( package.GetType() )
  {
    case TDataPackage::BOOL:
      if ( *(bool*) package == true )  out << "true;";
      else out << "false;";
      break;
    case TDataPackage::DATA_PACKAGE_LIST:                  // writes a complete data block
      out << "{" << endl;
      pList = (TDataPackageList*) package;
      for ( it=pList->begin(); it!=pList->end(); it++ )
        bReturn &= WriteDataPackage( out, *(*it), iIndent+2 );
      Indent( out, iIndent );
      out << "}";
      break;
    case TDataPackage::DOUBLE:
      out << setiosflags(ios::showpoint) << *(double*) package << resetiosflags(ios::showpoint) << ";";
      break;
    case TDataPackage::ID:
      out << *(TObjectID*) package << ";";
      break;
    case TDataPackage::INTEGER_2:
      out << "int2(" << *(int2*) package << ");";
      break;
    case TDataPackage::INTEGER_4:
      out << *(int4*) package << ";";
      break;
    case TDataPackage::POINT:
      out << "vec3d" << *(TPoint*) package << ";";
      break;
    case TDataPackage::STRING:
      out << "\"";
      out << *(string*) package;                            // FIXME: this needs probably more attention to prevent misuse of string
      out << "\";";                                         // at least we should convert the '"' to '\"' to avoid confusion.
      break;

    default:
      ELOG("TDataPackageList","WriteDataPackage") << "unknown data package: " << endl
        << "identifier: " << package.GetIdentifier() << endl
        << "type:       " << package.GetType() << endl;
      return false;
  }
  out << endl;
  return bReturn;
}





/*
* $Log: datapackage.cpp,v $
* Revision 1.29  2002/07/03 18:01:32  mkrohn5
* added methods: addCopy
*
* Revision 1.28  2002/06/28 10:12:07  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.27  2002/06/24 23:12:19  mkrohn5
* some docu reminders and minor changes
*
* Revision 1.26  2002/06/21 20:34:41  mkrohn5
* extended the get"DataType" methods of TDataPackageList
*
* Revision 1.25  2002/06/21 08:31:56  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.24  2002/06/07 00:32:38  mkrohn5
* fixed some tabs, added documentation
*
* Revision 1.23  2002/06/04 09:18:16  mkrohn5
* cosmetic changes
*
* Revision 1.22  2001/12/04 00:31:42  mkrohn5
* lots of new methods + clean up
*
* Revision 1.21  2001/12/03 01:32:13  mkrohn5
* improved LOG output
*
* Revision 1.20  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.19  2001/11/25 22:09:12  mkrohn5
* added ifdef / endif "bracket"
*
* Revision 1.18  2001/11/04 02:13:18  mkrohn5
* added documentation for a critical part
*
* Revision 1.17  2001/10/31 20:06:10  mkrohn5
* removed #include "common/log.h"
*
* Revision 1.16  2001/07/23 00:16:33  mkrohn5
* - fixed nasty memory leak in TDataPackageList
* - changed some log output
*
* Revision 1.15  2001/07/10 17:57:32  ishark
* rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
*
* Revision 1.14  2001/07/05 20:34:18  ishark
* added return true in test-item, fixed parser, added action Load/Save
*
* Revision 1.13  2001/07/03 00:54:24  mkrohn5
* small changes
*
* Revision 1.12  2001/07/02 00:36:42  mkrohn5
* cout -> LOG
*
* Revision 1.11  2001/06/29 00:57:22  mkrohn5
* - important bug fix
* - added leak checking
* - added some methods (for internal usage)
* - some debug output (the "cout" messages are temp)
*
* Revision 1.10  2001/06/22 14:44:07  prolator
* added elementary type int2
*
* Revision 1.9  2001/06/21 11:20:15  mkrohn5
* added TDataPackageList basic data type
* fixed a bug
*
* Revision 1.8  2001/06/13 00:06:15  mkrohn5
* added "double" to the base data types
*
* Revision 1.7  2001/06/12 10:12:10  mkrohn5
* added DeleteAll and the possibility to save a TDataPackageList to an ofstream
*
* Revision 1.6  2001/06/10 23:19:41  mkrohn5
* * added documentation
* * a lot new methods esp. in TDataPackageList
*
* Revision 1.5  2001/05/10 22:55:50  mkrohn5
* corrected parameters for Fatal calls
*
* Revision 1.4  2001/05/01 23:39:37  mkrohn5
* added debug method
*
* Revision 1.3  2001/04/29 21:38:37  ishark
* TAction updated to use TDataPackage/Load
*
* Revision 1.2  2001/04/27 01:17:06  mkrohn5
* merged Albertos and my work on this class
*
*/
