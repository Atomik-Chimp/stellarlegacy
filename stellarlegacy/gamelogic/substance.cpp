// $Id: substance.cpp,v 1.14 2002/06/28 10:12:07 mkrohn5 Exp $

// Substance Code File
// Written by: Alberto Barsella

// Copyright (C) 1999, 2000, Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
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

#include "substance.h"
#include "common/datapackage.h"

typedef TPList<TSubstance>::iterator TSiter;
typedef TPList<TSubstance>::const_iterator CTSiter;
typedef TPList<const TSubstance>::const_iterator CCTSiter;


vector<TSubstanceType*> TSubstanceType::fSubstanceTable;
uint2 TSubstanceType::fCargoClasses = 0;

/*
 * TSubstanceType member functions
 */


TSubstanceType::TSubstanceType(const string& name, const string& abbrev,
			       const uint2 cclass,
			       const int2 usize, const int2 umass,
			       const bool update) :
     fName(name), fAbbrev(abbrev), fCargoClass(cclass),
     fUnitSize(usize), fUnitMass(umass), fUpdatable(update)
  // update = false
{
  fId = fSubstanceTable.size();
  fSubstanceTable.push_back(this);

  if (fCargoClass >= fCargoClasses)
    fCargoClasses = fCargoClass + 1;
}


TSubstanceType::~TSubstanceType(void)
{
  // NOTE: this is not implemented, since we cannot guarantee
  // that no TSubstances of this type exist

  //  ERROR(fatal, "Attempt to destroy an existing substance type");
  exit(-1);
}


const string& TSubstanceType::Name(void) const
{
  return fName;
}


const uint2 TSubstanceType::Id(void) const
{
  return fId;
}


const uint2 TSubstanceType::CargoClass(void) const
{
  return fCargoClass;
}


const int2 TSubstanceType::UnitSize(void) const
{
  return fUnitSize;
}


const int2 TSubstanceType::UnitMass(void) const
{
  return fUnitMass;
}


const bool TSubstanceType::Updatable(void) const
{
  return fUpdatable;
}


TSubstance* TSubstanceType::Create(const TOSVal& iAmount)
  // iAmount = 1
{
  return new TSubstance(this, iAmount);
}


TOSVal TSubstanceType::Update( TSubstance*, const TOSVal& )
{
  return TOSVal(0);
}


// Find a substance type based on its Id (is this really needed?)

TSubstanceType* TSubstanceType::FindById(const SubstanceId Id)
{
  if (Id < fSubstanceTable.size())
    return fSubstanceTable[Id];
  else
    return 0;
}


// Find a substance type based on its name (needed by parser)

TSubstanceType* TSubstanceType::FindByName(const string& Name)
{
  vector<TSubstanceType*>::const_iterator i;

  for (i = fSubstanceTable.begin(); i != fSubstanceTable.end(); ++i)
    if ((*i)->fName == Name)
      return (*i);

  return 0;
}


const uint4 TSubstanceType::NumberSubstances(void)
{
  return fSubstanceTable.size();
}


const uint2 TSubstanceType::NumberCargoClasses(void)
{
  return fCargoClasses;
}


bool TSubstanceType::load( TDataPackageList* in )
{
  bool ReturnBool = true;
  
  ReturnBool &= TLinkable::load( in );// load parent's data and all local fields
  ReturnBool &= in->getAndDelete( "substance_name", &fName, true );
  ReturnBool &= in->getAndDelete( "abbreviation", &fAbbrev, true );
  ReturnBool &= in->getAndDelete( "substance_id", (int2*) &fId, true );
  ReturnBool &= in->getAndDelete( "cargo_class", (int2*) &fCargoClass, true );
  ReturnBool &= in->getAndDelete( "unit_size", &fUnitSize, true );
  ReturnBool &= in->getAndDelete( "unit_mass", &fUnitMass, true );
  ReturnBool &= in->getAndDelete( "updateable", &fUpdatable, true );
  // now update the static variables
  fSubstanceTable.push_back(this);
  if (fCargoClass >= fCargoClasses)
    fCargoClasses = fCargoClass + 1;
  return ReturnBool;                              // return the bool for success
} // load



bool TSubstanceType::save( TDataPackageList* out ) const
{
  bool ReturnBool = true;
  
  ReturnBool &= TLinkable::save( out );   // save parent's data and local fields
  ReturnBool &= out->add( "substance_name", &fName, true, false );
  ReturnBool &= out->add( "abbreviation", &fAbbrev, true, false );
  ReturnBool &= out->add( "substance_id", (int2*) &fId, true, false );
  ReturnBool &= out->add( "cargo_class", (int2*) &fCargoClass, true, false );
  ReturnBool &= out->add( "unit_size", &fUnitSize, true, false );
  ReturnBool &= out->add( "unit_mass", &fUnitMass, true, false );
  ReturnBool &= out->add( "updateable", &fUpdatable, true, false );
       // the static fields don't have to be saved, they will be created in Load
  return ReturnBool;                              // return the bool for success
} // save




/*
 * TSubstance member functions
 */

TSubstance::TSubstance(TSubstanceType* type, const TOSVal& iAmount) :
  // iAmount = 1
     fType(type), fAmount(iAmount)
{
}


TSubstance::~TSubstance(void)
{
}


TSubstance& TSubstance::operator=(const TSubstance& Subst2)
{
  fType.setDest( Subst2.fType.getPointerToDest() );
  fAmount = Subst2.fAmount;

  return *this;
}


TSubstance* TSubstance::Clone(void) const
{
  return new TSubstance(fType.getPointerToDest() , fAmount);
}


TSubstanceType* TSubstance::Type(void) const
{
  return fType.getPointerToDest();
}


TOSVal& TSubstance::Amount(void)
{
  return fAmount;
}


const TOSVal& TSubstance::Amount(void) const
{
  return fAmount;
}


// Total cargo size taken by the substance

const TOSVal TSubstance::Size(void) const
{
  return fAmount.Scale(fType->UnitSize(), 1);
}


TOSVal TSubstance::Update(const TOSVal& available_space)
{
  return fType->Update(this, available_space);
}


ostream& operator<<(ostream& os, const TSubstance& Subst)
{
  os << Subst.Type()->Name() << "/" << Subst.Amount();

  return os;
}



// default for bUnique = true
bool TSubstance::load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                     // read the object into the local data list
  ReturnBool &=in->getAndDelete( sIdentifier, dataList, bUnique );
                              // load item amount and type out of the local list
  ReturnBool &= fAmount.load( dataList, "substance_amount", true );
  ReturnBool &= fType.load( dataList, "substance_type", true );
  delete dataList;                                  // dispose of the local list
  return ReturnBool;                              // return the bool for success

} // load



// default for bUnique = true
bool TSubstance::save( TDataPackageList* out, const string& sIdentifier, bool bUnique ) const
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                  // save amount and type in the local data list
  ReturnBool &= fAmount.save( dataList, "substance_amount", true );
  ReturnBool &= fType.save( dataList, "substance_type", true );
                                // put local data list into "parent's" data list
  ReturnBool &= out->add( sIdentifier, dataList, bUnique, true );
  return ReturnBool;                              // return the bool for success
                   // the global data list will take care of freeing the memeory
} // save




/*
 * TSubstanceSet member functions
 *
 * The substances are stored in the vector in random order, which
 * forces a linear search. Should this prove to be a bottleneck the
 * search can become binary by sorting on fType (which, being an
 * address is an unique key).
 * (NOTE: this slows down a lot the set operations - don't panic if
 * they crawl - with the sorted lists it'll be much faster)
 */

TSubstanceSet::TSubstanceSet(void)
  : fContains()
{
}


TSubstanceSet::~TSubstanceSet(void)
{
  Clear();
}

TSubstanceSet::TSubstanceSet(const TSubstanceSet& Set2)
{
  *this = Set2;
} // Constructor



bool TSubstanceSet::operator==(const TSubstanceSet& Set2) const
{
  TSubstance* dummySubstance;
  CTSiter iter;       // iterator through the substance set
  
  // FIRST: check whether both sets have the same amount of substances
  if ( fContains.size() != Set2.fContains.size() )
    return false;               // unequal amounts => sets can't be equal

  // SECOND: check whether all substances in the set have the same amount
  for ( iter = fContains.begin(); iter != fContains.end(); ++iter )
  {
    dummySubstance = Set2.FindSubstance( (*iter)->Type() );
    // check whether the substance is also in Set2
    if ( dummySubstance != NULL )
    {
      // if yes: check whether amounts of substnaces are unequal
      if ( (*iter)->Amount() != dummySubstance->Amount() )
      {
        return false;
      }
    } else {
      return false;   // sets cannot be equal --> return false
    }
  }
  return true;  // if method was not left earlier, then sets must be equal
} //  operator==



bool TSubstanceSet::operator!=(const TSubstanceSet& Set2) const
{
  return !operator==(Set2);
}


TSubstanceSet& TSubstanceSet::operator=(const TSubstanceSet& Set2)
{
  Clear();
  Add(Set2);
  return *this;
} // operator=



void TSubstanceSet::Clear(void)
{
  while (fContains.size())
  {
    delete fContains.back();
    fContains.pop_back();
  }
}


/*
 * Internal function used to
 * - locate if an element of specified type already exists
 * - eliminate an unused (=0) amount
 */
TSubstance* TSubstanceSet::FindSubstance(const TSubstanceType* type) const
{
  CTSiter s;

  for (s = fContains.begin(); s != fContains.end(); ++s)
    if ((*s)->Type() == type)
      return (*s);

  return 0;
}


void TSubstanceSet::DeleteSubstance(TSubstance* Subst)
{
  TSiter s;

  for (s = fContains.begin(); s != fContains.end(); ++s)
    if ((*s) == Subst) {
      delete Subst;
      fContains.erase(s);
      return;
    }

  //  ERROR(fatal, "Attempt to delete a non-existing substance object");
  exit(-1);
}


/*
 * Cargo space functions
 * These function are more meaningful for holds than for sets,
 * but they can be practical to estimate the size eaten in a hold by a set
 */

/*
 * Compute the total cargo space for a specified class
 * uCClass: the cargo class
 *
 * RETURNS: the amount of space (a POSITIVE number)
 */
TOSVal TSubstanceSet::TotalSpace(uint2 uCClass) const
{
  CTSiter s;
  TOSVal total;

  for (s = fContains.begin(); s != fContains.end(); ++s)
    if ((*s)->Type()->CargoClass() == uCClass &&
	(*s)->Type()->UnitSize() < 0)
      total -= (*s)->Size();

  return total;
}


/*
 * Compute the available (empty) cargo space for a specified class
 * uCClass: the cargo class
 *
 * RETURNS: the amount of space (a POSITIVE number)
 */
TOSVal TSubstanceSet::AvailableSpace(const uint2 uCClass) const
{
  CTSiter s;
  TOSVal total;

  for (s = fContains.begin(); s != fContains.end(); ++s)
    if ((*s)->Type()->CargoClass() == uCClass)
      total -= (*s)->Size();

  return total;
}


/*
 * Compute the used (full) cargo space for a specified class
 * uCClass: the cargo class
 *
 * RETURNS: the amount of substances (a POSITIVE number)
 */
TOSVal TSubstanceSet::UsedSpace(uint2 uCClass) const
{
  CTSiter s;
  TOSVal total;

  for (s = fContains.begin(); s != fContains.end(); ++s)
    if ((*s)->Type()->CargoClass() == uCClass &&
	(*s)->Type()->UnitSize() > 0)
      total += (*s)->Size();

  return total;
}


/*
 * Determine if the set has enough substances.
 * Set2: the set of substances that we plan to remove in the near future
 * iNum/iDenom: scaling factors (numerator/denominator)
 *
 * RETURNS: true if the set has the requested amount
 */
bool TSubstanceSet::HasEnough(const TSubstanceSet& Set2,
			      const int4 iNum, const int4 iDenom) const
  // iNum = 1
  // iDenom = 1
{
  CTSiter s;

  for (s = Set2.fContains.begin(); s != Set2.fContains.end(); ++s)
    if (!HasEnough(**s, iNum, iDenom))
      return false;

  return true;
}


/*
 * Add two sets of substances
 * Set2: the set of substances that we add
 *
 * RETURNS: always true
 * default value for iNum = 1
 * default value for iDenom = 1
 */
bool TSubstanceSet::Add(const TSubstanceSet& Set2,
                        const int4 iNum, const int4 iDenom)
{
  CTSiter s;

  for (s = Set2.fContains.begin(); s != Set2.fContains.end(); ++s)    // add all
    Add( **s, iNum, iDenom );// substances of Set2 iNum/iDenom times in this set

  return true;
}


/*
 * Remove substances from a set
 * Set2: the set of substances that we want to remove
 * iNum/iDenom: scaling factors (numerator/denominator)
 *
 * RETURNS: true if the set has the requested amount/the substances are removed
 *          false if not enough - the set is left untouched
 */
bool TSubstanceSet::Remove(const TSubstanceSet& Set2,
			   const int4 iNum, const int4 iDenom)
  // iNum = 1
  // iDenom = 1
{
  // do we have enough?
  if (!HasEnough(Set2, iNum, iDenom))
    return false;

  CTSiter s;

  for (s = Set2.fContains.begin(); s != Set2.fContains.end(); ++s)
    Remove(**s, iNum, iDenom);

  return true;
}


/*
 * Add a single substance: makes sure not to duplicate types
 * Subst: the substance that we want to add
 *
 * RETURNS: always true
 * default value for iNum =1
 * default value for iDenom
 */
bool TSubstanceSet::Add(const TSubstance& Subst,
                        const int4 iNum, const int4 iDenom)
{
  TSubstance* s = FindSubstance(Subst.Type());

  if (s)                                          // if substance already in set
                                              // add substance iNum/iDenom times
      s->Amount() += Subst.Amount().Scale(iNum, iDenom); 
  else                                        // if substance not yet in the set
  {
    s = Subst.Clone();                 // create new substance, adjust amount of
    s->Amount() = Subst.Amount().Scale(iNum, iDenom);  // substance: iNum/iDenom
    fContains.push_back( s );                         // and add it into the set
  }
  return true;
}


/*
 * Determine if the set has enough of a specified substance.
 * Subst: the substance that we plan to remove in the near future
 * iNum/iDenom: scaling factors (numerator/denominator)
 *
 * RETURNS: true if the set has the requested amount
 */
bool TSubstanceSet::HasEnough(const TSubstance& Subs,
			      const int4 iNum, const int4 iDenom) const
  // iNum = 1
  // iDenom = 1
{
  TSubstance* s = FindSubstance(Subs.Type());

  if (s && s->Amount() >= Subs.Amount().Scale(iNum, iDenom))
      return true;

  return false;
}


/*
 * Remove a specified substance from the set.
 * Subst: the substance that we plan to remove in the near future
 * iNum/iDenom: scaling factors (numerator/denominator)
 *
 * RETURNS: true if the set has the requested amount/the substance is removed
 *          false if not enough - the set is left untouched
 */
bool TSubstanceSet::Remove(const TSubstance& Subst,
			   const int4 iNum, const int4 iDenom)
  // iNum = 1
  // iDenom = 1
{
  TSubstance* s = FindSubstance(Subst.Type());
  TOSVal Amount = Subst.Amount().Scale(iNum, iDenom);

  if (s && s->Amount() >= Amount)
  {
    s->Amount() -= Amount;

    if (s->Amount().Zero())
      DeleteSubstance(s);
    return true;
  }

  return false;
}


/*
 * Set accessor
 * Type: type of the substance we want to investigate
 *
 * RETURNS: NULL if the substance is not in the set
 *          a pointer to the substance object if it is
 */
const TSubstance* TSubstanceSet::operator[](const TSubstanceType* Type) const
{
  TSubstance* s = FindSubstance(Type);

  if (s)
    return s;
  else
    return 0;
}


/*
 * Set accessor
 *
 * RETURNS: a const reference to the fContains vector
 */
// SHOULD BE const vector<const TSubstance*>& TSubstanceSet::Content(void) const
const TPEList<TSubstance>& TSubstanceSet::Content(void) const
{
  return fContains;
}


ostream& operator<<(ostream& os, const TSubstanceSet& Set)
{
  CTSiter s;

  os << "(";

  for (s = Set.fContains.begin(); s != Set.fContains.end(); ++s)
  {
    if (s != Set.fContains.begin())
      os << ", ";
    os << *(*s);
  }

  os << ")";

  return os;
}



// default for bUnique = true
bool TSubstanceSet::load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                     // read the object into the local data list
  ReturnBool &=in->getAndDelete( sIdentifier, dataList, bUnique );
                                        // load substances out of the local list
  //  ReturnBool &= fContains.load( dataList, "substances", true );
  delete dataList;                                  // dispose of the local list
  return ReturnBool;                              // return the bool for success

} // load



// default for bUnique = true
bool TSubstanceSet::save( TDataPackageList* out, const string& sIdentifier, bool bUnique ) const
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                       // save substances in the local data list
  ReturnBool &= fContains.save( dataList, "substances", true );
                                // put local data list into "parent's" data list
  ReturnBool &= out->add( sIdentifier, dataList, bUnique, true );
  return ReturnBool;                              // return the bool for success
                   // the global data list will take care of freeing the memeory
} // save




/*
 * TSubstanceHold member functions
 */

TSubstanceHold::TSubstanceHold(void)
{
  fTotalSpace.resize(TSubstanceType::NumberCargoClasses());
  fAvailSpace.resize(TSubstanceType::NumberCargoClasses());
}


TSubstanceHold::~TSubstanceHold(void)
{
}


/*
 * internal functions to add/remove a substance preserving the
 * consistency of TotalSpace and AvailSpace
 *
 * NOTE: the functions ASSUME that the operation can be performed
 */
void TSubstanceHold::In(const TSubstance& s)
{
  TSubstanceSet::Add(s);

  if (s.Size().Negative())
    fTotalSpace[s.Type()->CargoClass()] -= s.Size();

  fAvailSpace[s.Type()->CargoClass()] -= s.Size();
}


void TSubstanceHold::Out(const TSubstance& s, const int4 iNum, const int4 iDenom)
{
  TSubstanceSet::Remove(s, iNum, iDenom);

  if (s.Size().Negative())
    fTotalSpace[s.Type()->CargoClass()] += s.Size().Scale(iNum, iDenom);

  fAvailSpace[s.Type()->CargoClass()] += s.Size().Scale(iNum, iDenom);
}


/*
 * clear the hold, similar to its Set counterpart
 */
void TSubstanceHold::Clear(void)
{
  uint2 i;

  TSubstanceSet::Clear();
  for (i = 0; i < TSubstanceType::NumberCargoClasses(); i++)
  {
    fTotalSpace[i] = 0;
    fAvailSpace[i] = 0;
  }
}


/*
 * empty the hold, removing all zero or positive-sized substances
 * negative-sized ones are considered "cargo space" and kept
 */
void TSubstanceHold::Empty(void)
{
  TSiter s;
  uint2 i;

  for (i = 0; i < TSubstanceType::NumberCargoClasses(); i++)
  {
    fTotalSpace[i] = 0;
    fAvailSpace[i] = 0;
  }

  for (s = fContains.begin(); s != fContains.end(); ++s)
  {
    if ((*s)->Type()->UnitSize() >= 0)
    {
      delete (*s);
      fContains.erase(s);
    }
    else
    {
      fTotalSpace[(*s)->Type()->CargoClass()] -= (*s)->Size();
      fAvailSpace[(*s)->Type()->CargoClass()] -= (*s)->Size();
    }
  }
}


/*
 * Return the total cargo space for a specified class
 * uCClass: the cargo class
 *
 * RETURNS: the amount of space (a POSITIVE number)
 */
TOSVal TSubstanceHold::TotalSpace(uint2 uCClass) const
{
  return fTotalSpace[uCClass];
}


/*
 * Return the available (empty) cargo space for a specified class
 * uCClass: the cargo class
 *
 * RETURNS: the amount of space (a POSITIVE number)
 */
TOSVal TSubstanceHold::AvailableSpace(const uint2 uCClass) const
{
  return fAvailSpace[uCClass];
}


/*
 * Compute the used (full) cargo space for a specified class
 * uCClass: the cargo class
 *
 * RETURNS: the amount of substances (a POSITIVE number)
 */
TOSVal TSubstanceHold::UsedSpace(uint2 uCClass) const
{
  return fTotalSpace[uCClass] - fAvailSpace[uCClass];
}


bool TSubstanceHold::CanAdd(const TSubstanceSet& Set) const
{
  uint2 i;

  for (i = 0; i < TSubstanceType::NumberCargoClasses(); i++)
    if (-Set.AvailableSpace(i) > AvailableSpace(i))
      return false;

  return true;
}


bool TSubstanceHold::Add(const TSubstanceSet& Set, TSubstanceSet* Added)
{
  CTSiter i;
  bool result = true;

  // we add all substances one by one
  // we start with negative and zero-sized substances,
  // which may expand the cargo space (they can be added without check)

  for (i = Set.Content().begin(); i != Set.Content().end(); ++i)
  {
    if ((*i)->Type()->UnitSize() <= 0)
    {
      TSubstance* s = (*i)->Clone();

      Add(**i, s);
      Added->Add(**i);
    }
  }

  // now handle the positive-sized substances

  for (i = Set.Content().begin(); i != Set.Content().end(); ++i)
  {
    if ((*i)->Type()->UnitSize() > 0)
    {
      TSubstance* s = (*i)->Clone();

      // try to add substance
      if (Add(**i, s))
      {
	Added->Add(**i);
      }
      else
      {
	// failed: addition was partial
	result = false;

	if (!s->Amount().Zero())
	  Added->Add(*s);
      }

      delete s;
    }
  }

  return result;
}


bool TSubstanceHold::CanRemove(const TSubstanceSet& Set,
			       const int4 iNum, const int4 iDenom) const
  // iNum = 1
  // iDenom = 1
{
  uint2 i;

  // make sure we do have the substances
  if (!HasEnough(Set, iNum, iDenom))
    return false;

  // ensure consistency with cargo space
  for (i = 0; i < TSubstanceType::NumberCargoClasses(); i++)
    if (Set.AvailableSpace(i) > AvailableSpace(i))
      return false;

  return true;
}


bool TSubstanceHold::Remove(const TSubstanceSet& Set, TSubstanceSet* Removed,
			    const int4 iNum, const int4 iDenom)
  // iNum = 1
  // iDenom = 1
{
  CTSiter i;
  bool result = true;

  // we remove all substances one by one
  // as in add, we start with zero or positive-sized substances, which
  // take up space - contrary to add, we need to check during this stage
  // as well, since there may not be enough substance
  for (i = Set.Content().begin(); i != Set.Content().end(); ++i)
  {
    if ((*i)->Type()->UnitSize() > 0)
    {
      TSubstance* s = (*i)->Clone();

      // try to remove substance
      if (Remove(**i, s, iNum, iDenom))
      {
	Removed->Add(**i);
      }
      else
      {
	// failed: partial removal
	result = false;

	if (!s->Amount().Zero())
	  Removed->Add(*s);
      }

      delete s;
    }
  }

  // same as above for negative-sized substances
  for (i = Set.Content().begin(); i != Set.Content().end(); ++i)
  {
    if ((*i)->Type()->UnitSize() > 0)
    {
      TSubstance* s = (*i)->Clone();

      // try to remove substance
      if (Remove(**i, s, iNum, iDenom))
      {
	Removed->Add(**i);
      }
      else
      {
	// failed: partial removal
	result = false;

	if (!s->Amount().Zero())
	  Removed->Add(*s);
      }

      delete s;
    }
  }

  return result;
}


bool TSubstanceHold::GetAllFrom(TSubstanceHold* Hold2)
{
  // we just use Add(Set), giving a temp "added",
  // which will then be removed from Hold2
  TSubstanceSet Added;
  bool result;

  result = Add(*Hold2, &Added);
  Hold2->TSubstanceSet::Remove(Added);

  return result;
}


bool TSubstanceHold::GetFrom(TSubstanceHold* Hold2,
                             const TSubstanceSet& MaxAbsolute,
                             const TSubstanceSet& MaxRelative)
{
  // this function only operates on non-negative sized substances

  return false;
}


bool TSubstanceHold::SplitOff(TSubstanceHold* Hold2)
{
  // this operation REQUIRES the second set to be empty, otherwise it's
  // not a split-off
  Hold2->Empty();

  // compute the ratio between total spaces in the two holds for every cargo class

  // multiply the contents by the ratio computed above

  // add the result to Hold2, remove it from Hold1

  // problem: how are zero-sized substances treated????
  return false;
}


bool TSubstanceHold::CanAdd(const TSubstance& Subst) const
{
  TOSVal SSize(Subst.Size());

  // Zero and Negative-Sized items are always ok
  if (SSize.Positive())
    return fAvailSpace[Subst.Type()->CargoClass()] >= SSize;

  return true;
}



/*
 * add a given substance to a hold
 * Subst: the substance we want to add
 * Added: an optional pointer to a scratch TSubstance object
 *
 * RETURNS: true  - if the full amount was added, Added is untouched
 *          false - Added contains actual the amount added to the hold
 */
bool TSubstanceHold::Add(const TSubstance& Subst, TSubstance* Added)
{
  // verify that we have enough space
  TOSVal SSize(Subst.Size());

  if (SSize.Positive())
  {
    TOSVal& Space(fAvailSpace[Subst.Type()->CargoClass()]);

    if (SSize <= Space)
      In(Subst);
    else
    {
      *Added = Subst;
      Added->Amount() = Space;
      In(*Added);
    }

    return false;
  }
  else
  {
    // just add the substance and be happy
    In(Subst);
  }

  return true;
}


bool TSubstanceHold::CanRemove(const TSubstance& Subst,
			       const int4 iNum, const int4 iDenom) const
  // iNum = 1
  // iDenom = 1
{
  if (!HasEnough(Subst, iNum, iDenom))
    return false;

  TOSVal SSize(Subst.Size());

  // Zero/Positive sized ones are always ok (we just checked to have enough)
  if (SSize.Negative())
    return fAvailSpace[Subst.Type()->CargoClass()] >= (-SSize);

  return true;
}


/*
 * remove a given substance to a hold
 * Subst: the substance we want to remove
 * Removed: an optional pointer to a scratch TSubstance object
 *
 * RETURNS: <as in Add>
 * (this function is more complex than its Set counterpart since we
 *  must ensure that consistency is mantained when removing cargo space.
 *  Basically it ends up being very similar to Add)
 */
bool TSubstanceHold::Remove(const TSubstance& Subst, TSubstance* Removed,
			    const int4 iNum, const int4 iDenom)
  // iNum = 1
  // iDenom = 1
{
  // we must ensure that we don't remove too much cargo space
  TOSVal Amount = Subst.Amount().Scale(iNum, iDenom);
  TOSVal SSize = Amount.Scale(Subst.Type()->UnitSize(), 1);

  if (SSize.Zero())
    TSubstanceSet::Remove(Subst, iNum, iDenom);

  else if (SSize.Negative())
  {
    // check the limit
    TOSVal Space = AvailableSpace(Subst.Type()->CargoClass());

    if (Space >= -SSize)
      Out(Subst, iNum, iDenom);
    else
    {
      // remove as much cargo space as possible
      if (Removed)
      {
	*Removed = Subst;
	Removed->Amount() = Space;
	Out(*Removed, 1, 1);
      }

      return false;
    }
  }
  else
  {
    // see if we have enough of it and remove as much as possible
    TSubstance* s = FindSubstance(Subst.Type());
    *Removed = Subst;

    if (!s) {
      Removed->Amount() = 0;

      return false;
    }
    else if (s->Amount() >= Amount)
    {
      Out(Subst, iNum, iDenom);
    }
    else
    {
      *Removed = *s;
      Out(*Removed, 1, 1);

      return false;
    }
  }

  return true;
}


ostream& operator<<(ostream& os, const TSubstanceHold& Hold)
{
  uint2 i;

  os << "[";
  operator<<(os, (const TSubstanceSet&)Hold);

  for (i = 0; i < TSubstanceType::NumberCargoClasses(); i++)
    os << " " << Hold.AvailableSpace(i) << "/" << Hold.TotalSpace(i);

  os << "]";

  return os;
}



// default for bUnique = true
bool TSubstanceHold::load( TDataPackageList* in, const string& sIdentifier, bool bUnique )
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                     // read the object into the local data list
  ReturnBool &=in->getAndDelete( sIdentifier, dataList, bUnique );
                                        // load substances out of the local list
  //  ReturnBool &= fContains.load( dataList, "substances", true );
  delete dataList;                                  // dispose of the local list
  return ReturnBool;                              // return the bool for success

} // load



// default for bUnique = true
bool TSubstanceHold::save( TDataPackageList* out, const string& sIdentifier, bool bUnique ) const
{
  bool ReturnBool = true;                                    // assume all is OK
  TDataPackageList* dataList = new TDataPackageList(); // create local data list
                                       // save substances in the local data list
  //  ReturnBool &= fContains.save( dataList, "substances", true );
                                // put local data list into "parent's" data list
  ReturnBool &= out->add( sIdentifier, dataList, bUnique, true );
  return ReturnBool;                              // return the bool for success
                   // the global data list will take care of freeing the memeory
} // save





/*
 * $Log: substance.cpp,v $
 * Revision 1.14  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.13  2002/06/23 15:50:49  ishark
 * added act-to-cpp tool, fixes in TActionSequencer, gcc3 fixes
 *
 * Revision 1.12  2002/06/21 08:31:56  mkrohn5
 * changed method name in TDatapackageList:
 * Get -> getAndDelete
 *
 * Revision 1.11  2002/06/03 11:48:29  mkrohn5
 * added operator!= for TSubstanceSet
 *
 * Revision 1.10  2002/03/24 13:36:37  mkrohn5
 * mostly style changes
 *
 * Revision 1.9  2002/01/28 01:10:40  mkrohn5
 * changed TPList -> TPEList
 *
 * Revision 1.8  2001/12/02 14:22:00  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.7  2001/08/07 20:54:45  mkrohn5
 * removed global variable which was never used
 *
 * Revision 1.6  2001/06/23 14:29:17  prolator
 * added Load and Save
 *
 * Revision 1.5  2001/06/23 00:13:38  prolator
 * fixed bug in TSubstanceSet::operator==
 *
 * Revision 1.4  2001/06/14 20:27:39  prolator
 * modified methods Add of TSubstanceSet: now with iNum and iDenom
 *
 * Revision 1.3  2001/06/12 21:36:08  prolator
 * added operator== and added 2nd parameter to both Add methods
 *
 * Revision 1.2  2001/05/17 12:25:47  prolator
 * I inserted the code part for the copy constructor and opertator=.
 *
 * Revision 1.1  2001/03/07 00:47:49  mkrohn5
 * reimport
 *
 * Revision 1.5  2000/10/02 12:33:17  ishark
 * added some more lex/parser stuff related to actions
 *
 * Revision 1.4  2000/06/29 10:59:56  ishark
 * added action/lex/parser, addeed license to headers
 *
 * Revision 1.3  2000/05/28 22:16:09  mkrohn5
 * small changes
 *
 * Revision 1.2  2000/04/02 23:46:04  mkrohn5
 * no message
 *
 * Revision 1.9  2000/03/08 15:47:34  alberto
 *
 * added kdoc comments for TSubstance classes
 * added kdoc html files to web/coding and a code/Makefile to rebuild them
 *
 * Revision 1.8  2000/02/02 12:17:53  krohn
 * make it compile
 *
 * Revision 1.7  2000/02/01 08:44:23  alberto
 * minor fixes in substance, added some crap action stuff
 *
 * Revision 1.5  1999/10/23 16:10:15  alberto
 * first version (semi-complete) of the TSubstance-related classes
 *
 * Revision 1.4  1999/10/17 17:32:47  alberto
 * corrections in OSVal and Substance/Set, partial implement of Hold
 *
 * Revision 1.3  1999/10/11 16:01:49  alberto
 * implemented TOSVal, TSubstance, TSubstanceType, TSubstanceSet methods
 * added code/testing directory - added osval-demo and substance-demo
 *
 * Revision 1.2  1999/10/04 15:33:01  alberto
 * substance classes updated, split set/hold
 *
 */

