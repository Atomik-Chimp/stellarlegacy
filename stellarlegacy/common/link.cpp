// $Id: link.cpp,v 1.37 2002/06/28 10:12:07 mkrohn5 Exp $

// Link Code File
// Written by: Marco Krohn <marco.krohn@gmx.de>

// Copyright (C) 1999 - 2001, Marco Krohn, <marco.krohn@gmx.de>
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

#include <iomanip>
#include <iostream>

#include "common/datapackage.h"
#include "common/link.h"
#include "common/global.h"

using namespace std;





//----------------------------------------  global/static data  ----------------------------------------

TObjectID TLinkBase::NullID;
TObjectID TLinkable::UniqueID;
TLinkUpdate* TLinkUpdate::fInstance = 0;





//----------------------------------------  Misc. Functions  ----------------------------------------

ostream& operator<<( ostream& Stream, const TObjectID& ObjectID )
{
  ObjectID.write(Stream);
  return Stream;
}



ostream& operator<<( ostream& Stream, const TLinkBase& Link )
{
  Link.Write(Stream);
  return Stream;
}





//----------------------------------------  class TObjectID  ----------------------------------------

TObjectID :: TObjectID()
{
  setNull();
  bTemp = false;
}



TObjectID :: TObjectID( const TObjectID& Object )          // copy constructor
{
  *this = Object;
}



// bTemp = false
TObjectID :: TObjectID( const byte* ByteArray, bool bTemp )
{
  setID( ByteArray );
  setTemp( bTemp );
}



// bTemp = false
TObjectID :: TObjectID( const int* IntArray, bool bTemp )
{
  setID( IntArray );
  setTemp( bTemp );
}



bool TObjectID :: isNull() const
{
int i;

  for (i=0; i<ID_SIZE; i++)
  {
    if (ObjectID[i] != 0)  return false;
  }
  return true;
}



bool TObjectID :: isTemp() const
{
  return bTemp;
}



// static method
int TObjectID ::  getIDSize()
{
  return ID_SIZE;
}



// bUnique=true
bool TObjectID :: load( TDataPackageList* in, const string& sIdentifier,
                        bool bUnique )
{
TDataPackage* pPackage;

  if ( bUnique == true )  pPackage = in->SearchAndExtractUnique( sIdentifier );
  else                    pPackage = in->SearchAndExtract( sIdentifier );

  if ( pPackage == 0 )
  {
    WLOG("TObjectID","load") << "missing identifier: " << sIdentifier << endl;
    return false;
  }

  *this = *( (TObjectID*) *pPackage );                     // ID extracted
  delete pPackage;                                         // delete the data package

  return true;
}



TObjectID& TObjectID :: operator=( const TObjectID& Object )
{
int i;

  for (i=0; i<ID_SIZE; i++)  ObjectID[i] = Object.ObjectID[i];
  bTemp = Object.bTemp;
  return *this;
}



// prefix increment operator
TObjectID TObjectID :: operator++()
{
int i;

  for (i=0; i<ID_SIZE; i++)
  {
    ObjectID[i]++;
    if (ObjectID[i] != 0)  return *this;                   // no overflow
  }

  // overflow!
  Fatal("TObjectID", "operator++()",
    "Could not increment ID. Use more bytes for ID handling!");

  return *this;
}



// postfix increment operator
TObjectID TObjectID :: operator++( int )
{
  TObjectID temp = *this;
  operator++();
  return temp;
}



bool TObjectID :: operator==( const TObjectID& Object ) const
{
int i;

  for (i=0; i<ID_SIZE; i++)
  {
    if (ObjectID[i] != Object.ObjectID[i])  return false;
  }
  if (bTemp != Object.bTemp)  return false;
  return true;
}



bool TObjectID :: operator!=( const TObjectID& Object ) const
{
  return !(*this == Object);
}



bool TObjectID :: operator<( const TObjectID& Object ) const
{
int i;

  if ( bTemp==true &&  Object.bTemp==false )  return true;
  if ( bTemp==false &&  Object.bTemp==true )  return false;

  for (i=ID_SIZE-1; i>=0; i--)  {
    if ( ObjectID[i] < Object.ObjectID[i] )       return true;
    else if ( ObjectID[i] > Object.ObjectID[i] )  return false;
  }
  return false;                                            // both IDs are the same
}



// bUnique=true, bAutoDelete=false
bool TObjectID :: save( TDataPackageList* out, const string& sIdentifier,
                        bool bUnique, bool bAutoDelete ) const
{
TDataPackage* data;

  if ( bUnique == true && out->Search(sIdentifier) != 0 )  {
    WLOG("TObjectID","save") << "already used identifier: " << sIdentifier << endl;
    return false;
  }

  data = new TDataPackage( sIdentifier, this );
  data->SetAutoDeleteMode( bAutoDelete );
  out->push_back( data );

  return true;
}



// bTemp=false
void TObjectID :: setID( const byte* ByteArray, bool bTemp )
{
int i;
int IntArray[ID_SIZE];

  for (i=0; i<ID_SIZE; i++)  {
    IntArray[i] = (int) ByteArray[i];
  }
  setID( IntArray );
  setTemp( bTemp );
}



// bTemp=false
void TObjectID :: setID( const int* IntArray, bool bTemp )
{
int i;

  for ( i=0; i<ID_SIZE; i++ )  {
    if ( IntArray[i]>=0 && IntArray[i]<=255 )  {
      ObjectID[i] = IntArray[i];
    }
    else  {
      WLOG("TObjectID", "TObjectID(int* IntArray)")
        << "One entry of the integer array is out of range (0-255): " << IntArray[i] << endl;

      if ( IntArray[i] < 0 )         ObjectID[i] = 0;
      else if ( IntArray[i] > 255 )  ObjectID[i] = 255;
    }
  }
  setTemp( bTemp );
}



void TObjectID :: setNull()
{
int i;

  for (i=0; i<ID_SIZE; i++)  ObjectID[i]=0;
}



void TObjectID :: setTemp( bool bTemp )
{
  this->bTemp = bTemp;
}



void TObjectID :: write( ostream& out ) const
{
int i;

  // for debugging reasons:
  // do *not* change the following line to: if (bTemp == true) ...
  if (bTemp != false)  out << "temp";
  out << "[";
  for (i=0; i<ID_SIZE; i++)  {
    out << hex << (int) ObjectID[i];
    if (i != ID_SIZE-1)  out << ",";
  }
  out << dec << "]";
}





//----------------------------------------  class TLinkBase  ----------------------------------------

TLinkBase :: TLinkBase()
{
  reset();
}



TLinkBase :: TLinkBase( TLinkable* p )
{
  reset();
  setDest( p );
}



TLinkBase :: TLinkBase( const TObjectID& DestID )
{
  reset();
  setDest( DestID );
}



TLinkBase :: TLinkBase( const TLinkBase& link )
{
  // using operator= for the copy-constructor is safe, since we don't have
  // to deallocate any local data
  *this = link;
}



TLinkBase :: ~TLinkBase()
{
  LOG("TLinkBase", "~TLinkBase()") << "Delete link object pointing to: " << DestID << endl;
  // LinkUpdate can remove this entry from the list
  removeUpdateRequest();
  // Inform the TLinkable object that this link does not point to it any more
  if ( pDest != 0 )  pDest->removeInverseLink( this );
}



TLinkable* TLinkBase :: getDest() const
{
  return pDest;
}



const TObjectID& TLinkBase :: getDestID() const
{
  if ( bNeedUpdate == true )  return NullID;
  return DestID;
}



int2 TLinkBase :: getDestType() const
{
  if ( bNeedUpdate == true )  return TType::UNKNOWN;
  return pDest->getType();
}



// virtual method
int2 TLinkBase :: getType() const
{
  return TLinkBase::LINK_BASE;
}



const string& TLinkBase :: getDestTypeName() const
{
static string sTypeName = "unknown";

  if ( bNeedUpdate == true )  return sTypeName;
  return pDest->getTypeName();
}



bool TLinkBase :: isNull() const
{
  if ( pDest==0 && DestID.isNull()==true )  return true;
  return false;
}



bool TLinkBase :: isUpdated() const
{
  if ( bNeedUpdate == true )  return false;
  return true;
}



bool TLinkBase :: isValid() const
{
  if ( pDest != 0 )  return true;
  return false;
}



// bUnique=true
bool TLinkBase :: load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
TObjectID ID;

  if ( ID.load(in,sIdentifier,bUnique) == true )  {
    setDest( ID );
    return true;
  }
  return false;
}



TLinkBase& TLinkBase :: operator=( const TLinkBase& src )
{
  if ( &src == this )  return *this;                       // source and dest are the same objects

  // Inform TLinkUpdate that an update is not neccessary any more
  if ( bNeedUpdate == true )  removeUpdateRequest();
  // Inform the TLinkable object that this link does not point to it any more
  if ( pDest != 0 )  pDest->removeInverseLink( this );

  DestID = src.DestID;                                     // now copy all entries
  pDest = src.pDest;
  bNeedUpdate = src.bNeedUpdate;

  if ( bNeedUpdate == true )  {
    TLinkUpdate::instance()->requestUpdate( this );        // request update
  }
  if ( isValid() == true )  {
    pDest->addInverseLink( this );                         // inform the dest object that it is linked
  }

  return *this;
}



bool TLinkBase :: operator==( const TLinkBase& Two ) const
{
  if ( bNeedUpdate==false && Two.bNeedUpdate==false && pDest==Two.pDest )  return true;
  return false;
}



// bUnique=true
bool TLinkBase :: save( TDataPackageList* out, const string& sIdentifier,
                        bool bUnique ) const
{
  return DestID.save( out, sIdentifier, bUnique );
}



void TLinkBase :: setNull()
{
  setDest( 0 );
}



// virtual method
void TLinkBase :: setDest( TLinkable* p )
{
  // Inform TLinkUpdate that an update is not neccessary any more
  if ( bNeedUpdate == true )  removeUpdateRequest();
  // Inform the TLinkable object that this link does not point to it any more
  if ( pDest != 0 )  pDest->removeInverseLink( this );

  bNeedUpdate = false;
  pDest = p;
  if ( p != 0 )  {
    DestID = p->getID();
    p->addInverseLink( this );                             // inform the dest object that it is linked
  }
  else  {
    DestID.setNull();                                      // set ID to 0
  }
}



void TLinkBase :: Write( ostream& out ) const
{
  out << "link" << DestID;
  if ( bNeedUpdate == true )  out << " (needs update)";
}





//----------------------------------------  Protected  ----------------------------------------

void TLinkBase :: removeUpdateRequest()
{
  if ( bNeedUpdate == true )                     // If update flag is set ...
  {
    TLinkUpdate::instance()->deleteUpdateRequest( this );       // inform LinkUpdate that an update
    reset();                                     // is no longer necessary
  }
}



void TLinkBase :: requestUpdate()
{
  bNeedUpdate = true;
  TLinkUpdate::instance()->requestUpdate( this );
}



void TLinkBase :: reset()
{
  pDest = 0;
  DestID = TObjectID();
  bNeedUpdate = false;
}



void TLinkBase :: setDest( const TObjectID& DestID )
{
  // Inform TLinkUpdate that an update is not neccessary any more
  if ( bNeedUpdate == true )  removeUpdateRequest();
  // Inform the TLinkable object that this link does not point to it any more
  if ( pDest != 0 )  pDest->removeInverseLink( this );

  this->DestID = DestID;
  pDest = 0;
  if ( DestID.isNull() == false )  requestUpdate();
}





//----------------------------------------  class TLink  ----------------------------------------

// the code for TLink is in the header file





//----------------------------------------  class TType  ----------------------------------------

// virtual method
int2 TType :: getType() const
{
  return TType::UNKNOWN;
}



// virtual method
const string& TType :: getTypeName() const
{
static string sTypeName = "TType";

  return sTypeName;
}





//----------------------------------------  class TLinkable  ----------------------------------------

const TObjectID& TLinkable :: getID() const
{
  return ID;
}



const TLinkBaseList& TLinkable :: getLinkedByList() const
{
  return LinkedBy;
}



int4 TLinkable :: getNumberOfLinks() const
{
  return LinkedBy.size();
}



// virtual method
int2 TLinkable :: getType() const
{
  return TType::LINKABLE;
}



// virtual method
const string& TLinkable :: getTypeName() const
{
static const string sTypeName = "TLinkable";

  return sTypeName;
}



// virtual method
bool TLinkable :: load( TDataPackageList* in )
{
bool bReturn = true;
TDataPackageList* pSubList = new TDataPackageList();
TObjectID OldID;

  // server: read the old ID from disk and use it as the new ID
  // for the object (we can always trust the server master file).
  // After reading the old ID we compare the UniqueID with
  // client: do the same
  reset();

  //---------- Load the data
  // read the object => new sub list
  bReturn &=in->getAndDelete( "linkable", pSubList, true );

  // read the "real" data from the sub list
  bReturn &= OldID.load( pSubList, "id", true );

  // clean up
  delete pSubList;

  //---------- Process the data
  ID = OldID;                                              // change the ID of this object
  TLinkUpdate::instance()->commitUpdate( this, OldID );    // inform TLinkUpdate about the new object

  // to guarantee that UniqueID will be unique we have to change
  // the current UniqueID
  if ( UniqueID < OldID )
  {
    UniqueID = OldID;
    UniqueID++;                                            // UniqueID is now unique again
  }

  return bReturn;
}



// virtual method
bool TLinkable :: save( TDataPackageList* out ) const
{
bool bReturn = true;

  TDataPackageList* pSubList = new TDataPackageList();     // create a new datapackage list
  // bAutoDelete=true so that pSubList is deleted sometime later
  bReturn &= out->add( "linkable", pSubList, true, true );

  // write the linkable data to the new list
  bReturn &= ID.save( pSubList, "id", true );

  return bReturn;
}





//----------------------------------------  Protected  ----------------------------------------

TLinkable :: TLinkable()
{
  // UniqueID is set to null. Make sure that _no_ object has ID zero
  // since zero is reserved for the same thing as the 0 pointer.
  if ( UniqueID.isNull() == true )  UniqueID++;            // ID is now > 0

  ID = TLinkable::UniqueID;
  LOG("TLinkable", "TLinkable()") << "Object ID: " << ID << endl;
  TLinkable::UniqueID++;                                   // UniqueID is now unique again
}



TLinkable :: ~TLinkable()
{
  LOG("TLinkable","~TLinkable") << "destruct TLinkable object" << endl;
  reset();
  LOG("TLinkable", "~TLinkable") << "removed all links to object and the object itself: ID=" << ID << endl;
}



// virtual method
void TLinkable :: reset()
{
TLinkBaseList::iterator it;

  LOG("TLinkable","Reset") << "remove "
    << LinkedBy.size() << " links pointing to this object: " << endl;

  for ( it=LinkedBy.begin(); it!=LinkedBy.end(); it++ )
  {
    // now reset the link (note: a call to RemoveUpdateRequest is not neccessary
    // because only updated links can link an object).
    LOG("TLinkable","Reset") << "reset Link: " << *it << "  "
      << (*it)->getDestID() << endl;
    (*it)->reset();
  }
  LinkedBy.clear();
}





//----------------------------------------  Private  ----------------------------------------

void TLinkable :: addInverseLink( TLinkBase* p )
{

  if ( p != 0 )  {
    LOG("TLinkable","addInverseLink") << "added inverse link." << endl;
    LinkedBy.push_back( p );                  // adds a link to the LinkedBy list
  }
}



void TLinkable :: removeInverseLink( TLinkBase* p )
{
TLinkBaseList::iterator it;

  it = LinkedBy.begin();
  for ( it=LinkedBy.begin(); it!=LinkedBy.end(); it++ )  {
    if ( *it == p )  {
      LinkedBy.erase( it );
      LOG("TLinkable","removeInverseLink") << "removing inverse link..." << endl
        << "now the number of inverse links is: " << LinkedBy.size() << endl;
      break;
    }
  }
}





//----------------------------------------  class TLinkUpdate  ----------------------------------------

TLinkUpdate :: ~TLinkUpdate()
{
  LOG("TLinkUpdate","~TLinkUpdate") << "destructor of TLinkUpdate called." << endl;
  checkConsistency();
}



bool TLinkUpdate :: checkConsistency()
{
TLinkBaseList::iterator p;

  if ( fUpdateList.empty() == false )
  {
    ELOG("TLinkUpdate", "CheckConsistency()")
      << "TLinkUpdate was not able to update all links!" << endl
      << "The follwing links had no update: " << endl;
    for ( p=fUpdateList.begin(); p!=fUpdateList.end(); p++ )
    {
      ELOG("TLinkUpdate", "CheckConsistency()") << "link to: " << (*p)->DestID << endl;
    }
    return false;
  }
  else
  {
    LOG("TLinkUpdate", "checkConsistency()")
      << "There are no links left which need an update!" << endl;
  }

  return true;
}



void TLinkUpdate :: commitUpdate( TLinkable* pNew, const TObjectID& OldID )
{
TLinkBaseList::iterator p;
TObjectID NewID;

  fMap[OldID] = pNew;                                       // add information to map
  NewID = pNew->ID;                                        // get new ID

  LOG("TLinkUpdate", "CommitUpdate(TLinkable* pNew, const TObjectID& OldID)")
    << "Update message received: real object ID: " << pNew->getID()
    << ", old (received) ID: " << OldID << endl
    << "(the information has been added to the map)" << endl;
  LOG_BEGIN_INDENT();

  for ( p=fUpdateList.begin(); p!=fUpdateList.end(); p++ )      // now checking the whole list for updates
  {
    if ( (*p)->DestID == OldID )                           // if link in update list refers to old ID
    {
      LOG("TLinkUpdate", "CommitUpdate(TLinkable* pNew, const TObjectID& OldID)")
          << "link to (old) ID: " << OldID << " changed to (new) ID: " << NewID << endl;

      (*p)->DestID = NewID;                                // ID update
      (*p)->pDest = pNew;                                  // pointer update
      (*p)->bNeedUpdate = false;                           // does not need an update any more
      pNew->addInverseLink( *p );                          // informs object that it is linked
      (*p)=0;                                              // mark for remove
    }
  }
  fUpdateList.remove( 0 );                                 // remove all links which do not need an update anymore

  LOG_END_INDENT();
}



void TLinkUpdate :: deleteUpdateRequest( const TLinkBase* pLink )
{
TLinkBaseList::iterator p;

  for ( p=fUpdateList.begin(); p!=fUpdateList.end(); p++ )  {
    if ( (*p) == pLink )  {                                // link found
      fUpdateList.erase(p);
      break;
    }
  }
}



// static method
TLinkUpdate* TLinkUpdate :: instance()
{
  if ( fInstance == 0 ) {
    fInstance = new TLinkUpdate;
  }
  return fInstance;
}



void TLinkUpdate :: requestUpdate( TLinkBase* pLink )
{
map<TObjectID, TLinkable*>::iterator p;

  LOG("TLinkUpdate", "requestUpdate")
    << "Received update request for link: " << pLink
    << "  DestID: " << pLink->DestID
    << "  temp: " << pLink->DestID.bTemp << endl;

  p = fMap.find( pLink->DestID );

  if ( p == fMap.end() ) {                                 // ID not found => no update possible at the moment
    fUpdateList.push_back(pLink);                          // add the link to the list
    LOG("TLinkUpdate", "requestUpdate")
      << "Link has been added to the update list" << endl;
  }
  else {                                                   // entry found => update the link
    pLink->DestID = p->second->ID;                         // ID update
    pLink->pDest = p->second;                              // pointer update
    pLink->bNeedUpdate = false;                            // need no update
    p->second->addInverseLink( pLink );                    // informs object that it is linked

    LOG("TLinkUpdate", "requestUpdate")
      << "Link has been updated, now pointing to: " << pLink->DestID << endl;
  }
}



void TLinkUpdate :: reset()
{
  fMap.clear();
  fUpdateList.clear();
}





//----------------------------------------  protected  ----------------------------------------

TLinkUpdate :: TLinkUpdate()
{
  LOG("TLinkUpdate", "TLinkUpdate") << "TLinkUpdate created" << endl;
}



//----------------------------------------  private  ----------------------------------------

void TLinkUpdate :: showMap()
{
map<TObjectID, TLinkable*>::iterator p;

  LOG("TLinkUpdate", "ShowMap") << "Show link map." << endl;

  LOG_BEGIN_INDENT();
  LOG("TLinkUpdate", "ShowMap") << "Mapping: old ID -> new ID" << endl;
  for ( p=fMap.begin(); p!=fMap.end(); p++ )  {
    LOG("TLinkUpdate", "ShowMap") << p->first << " -> " << p->second->ID << endl;
  }
  LOG_END_INDENT();
}



void TLinkUpdate :: showUpdateList()
{
TLinkBaseList::iterator p;

  LOG("TLinkUpdate", "ShowUpdateList") << "Show LinkUpdate list." << endl;
  LOG_BEGIN_INDENT();

  LOG("TLinkUpdate", "ShowUpdateList")
    << "Links which need an update and their current dest ID." << endl;

  for ( p=fUpdateList.begin(); p!=fUpdateList.end(); p++ )  {
    LOG("TLinkUpdate", "ShowUpdateList") << (*p)->DestID << endl;
  }
  if ( fUpdateList.empty() == true)  {
    LOG("TLinkUpdate", "showUpdateList")
      << "There are no links in the UpdateList which need an update." << endl;
  }
  LOG_END_INDENT();
}





/*
* $Log: link.cpp,v $
* Revision 1.37  2002/06/28 10:12:07  mkrohn5
* - Add -> add (TDataPackageList)
* - readded validated cache flag in TAction
*
* Revision 1.36  2002/06/21 08:31:57  mkrohn5
* changed method name in TDatapackageList:
* Get -> getAndDelete
*
* Revision 1.35  2002/05/15 08:30:55  ishark
* actionsequencer now uses lists + cosmetic fixes
*
* Revision 1.34  2002/05/11 23:49:52  mkrohn5
* implemented TLinkUpdate::reset
*
* Revision 1.33  2002/05/10 10:35:19  mkrohn5
* some minor changes
*
* Revision 1.32  2002/03/24 18:05:08  mkrohn5
* bug fix and small API changes
*
* Revision 1.31  2002/03/24 13:26:16  mkrohn5
* - added TDoubleLink class
* - lots of style fixes
*
* Revision 1.30  2002/01/28 00:55:46  mkrohn5
* mostly docu & layout fixes
*
* Revision 1.29  2001/12/02 14:22:00  mkrohn5
* changed Load -> load, Save -> save,
* puuh, more work than expected :-(
*
* Revision 1.28  2001/10/31 19:48:14  mkrohn5
* removed #include "common/log.h"
*
* Revision 1.27  2001/08/07 20:45:37  mkrohn5
* removed some unneccessary log messages
*
* Revision 1.26  2001/07/31 00:23:21  mkrohn5
* - changed ID handling in server mode
* - docu changes
*
* Revision 1.25  2001/07/23 00:20:16  mkrohn5
* fixed bug in TObjectID::operator<
*
* Revision 1.24  2001/07/11 00:10:38  mkrohn5
* fixed a bug in TLinkUpdate
*
* Revision 1.23  2001/06/28 21:30:42  ishark
* parser can read savefile, TObjectID now uses []
*
* Revision 1.22  2001/06/24 16:49:14  mkrohn5
* changed message strings
*
* Revision 1.21  2001/06/22 00:46:36  mkrohn5
* fixed a few memory leaks
*
* Revision 1.20  2001/06/21 11:55:17  prolator
* fixed bug in TLinkable::Load; pList was not initialized
*
* Revision 1.19  2001/06/21 02:29:54  mkrohn5
* fixed nasty bug
*
* Revision 1.18  2001/06/13 00:08:06  mkrohn5
* removed a parameter which is not needed
*
* Revision 1.17  2001/06/12 10:10:36  mkrohn5
* changed some log strings
*
* Revision 1.16  2001/06/10 23:18:04  mkrohn5
* Load & Save do now use the TDataPackageList "stream"
* Renamed: SetZero -> SetNull
* Fixed a bug in TLinkBase
*
* Revision 1.15  2001/05/10 23:02:37  mkrohn5
* Changed Load methods
* Corrected parameters for Fatal calls
* Introduced a Reset method for TLinkable
*
* Revision 1.14  2001/04/29 21:38:37  ishark
* TAction updated to use TDataPackage/Load
*
* Revision 1.13  2001/04/27 01:16:33  mkrohn5
* added "const" to a string
*
* Revision 1.12  2001/04/26 21:52:05  mkrohn5
* moved the template related code back to the header file since it caused some problems :-(
*
* Revision 1.11  2001/04/26 00:02:03  mkrohn5
* bugfix, moved code from the header to the code file, changed api
*
* Revision 1.9  2001/04/18 00:36:18  mkrohn5
* bugfix: a null link does _not_ need an update
*
* Revision 1.8  2001/04/17 00:45:21  mkrohn5
* changed API and improved documentation
*
*/
