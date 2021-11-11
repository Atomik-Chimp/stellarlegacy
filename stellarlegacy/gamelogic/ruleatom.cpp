// $Id: ruleatom.cpp,v 1.9 2002/07/08 06:14:57 mkrohn5 Exp $

// Rule System Code File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2001 - , Marco Krohn, <marco.krohn@gmx.de>
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
#include "common/prototype.h"
#include "gamelogic/ruleatom.h"

using namespace std;





//----------------------------------------  static member definition  ----------------------------------------

#ifdef SECURE_MODE
  TLeakChecker TRuleAtom::lc;
#endif // SECURE_MODE





//----------------------------------------  misc. Functions  ----------------------------------------

ostream& operator<<( ostream& stream, const tRuleAtomKey& key )
{
  return key.write( stream );
}





//----------------------------------------  class TRuleAtom  ----------------------------------------

// virtual method
TRuleAtom :: ~TRuleAtom()
{
  #ifdef SECURE_MODE
    lc--;
    LOG("TRuleAtom","~TRuleAtom") << "#TRuleAtom: " << lc.Get() << endl;
  #endif // SECURE_MODE

  // cleaning up
  delete fInfo;
  delete fResults;
}



void TRuleAtom :: addInfo( const string& identifier, TLinkable* obj )
{
  LOG("TRuleAtom","addInfo") << "received info: " << identifier << endl;

  // this is just used to reserve the name and to avoid name conflicts
  fInfo->set( identifier, true );
  fInfoObj[identifier] = obj;
}



void TRuleAtom :: addInfo( const string& identifier, int2 data )
{
  fInfo->set( identifier, data );
}



void TRuleAtom :: addInfo( const string& identifier, double data )
{
  fInfo->set( identifier, data );
}



// virtual method
bool TRuleAtom :: checkDependencies( list<TRuleSystem::tError>* ) const
{
  return false;
}



double TRuleAtom :: getInfoDouble( const string& identifier ) const
{
  return fInfo->getDouble( identifier );
}



int2 TRuleAtom :: getInfoInt2( const string& identifier ) const
{
  return fInfo->getInt2( identifier );
}



TLinkable* TRuleAtom :: getInfoObject( const string& identifier ) const
{
  map<string,TLinkable*>::const_iterator it = fInfoObj.find( identifier );
  if ( it == fInfoObj.end() )  return 0;

  return it->second;
}



const TDataPackageList* TRuleAtom :: getResults() const
{
  return fResults;
}




//----------------------------------------  protected  ----------------------------------------

TRuleAtom :: TRuleAtom() : TCanBePrototype()
{
  #ifdef SECURE_MODE
    lc++;
    LOG("TRuleAtom","TRuleAtom") << "#TRuleAtom: " << lc.Get() << endl;
  #endif // SECURE_MODE

  fInfo = new TDataPackageList;
  fResults = new TDataPackageList;
}



void TRuleAtom :: validateInfo( const string& identifier ) const
{
  if ( fInfo->Search(identifier) == 0 )  {
    ELOG("TRuleAtom","validateInfo")
      << "there is no data package: " << identifier << endl
      << "called from rule atom: " << getPrototypeName() << endl;
    Fatal("TRuleAtom","validateInfo","missing info for rule atom");
  }
}





/*
* $Log: ruleatom.cpp,v $
* Revision 1.9  2002/07/08 06:14:57  mkrohn5
* added docu
*
* Revision 1.8  2002/07/02 23:18:48  mkrohn5
* added operator<< for tRuleAtomKey
*
* Revision 1.7  2002/07/01 00:09:20  mkrohn5
* "grammer" changer due to changes structure in action.cpp/.h
*
* Revision 1.6  2002/06/22 18:22:53  mkrohn5
* - introduced base class for rule atoms => DeclareRuleAtomBase
* - some doc updates (still work in progress)
*
* Revision 1.5  2002/06/07 00:36:42  mkrohn5
* extended rule atom info
*
* Revision 1.4  2002/06/05 00:33:28  mkrohn5
* removed unneccessary parameter
*
* Revision 1.3  2002/06/04 09:25:02  mkrohn5
* - macro for writing rule atoms
* - some internal changes
*
* Revision 1.2  2001/12/03 01:41:41  mkrohn5
* - changed the system for returning information
* - added lots of documentation
*
* Revision 1.1  2001/12/01 17:19:15  mkrohn5
* moved the interface "ruleatom.*" back to gamelogic/
*
* Revision 1.1  2001/11/25 22:11:57  mkrohn5
* created new subdir for rule atoms
*
*/
