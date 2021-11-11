// $Id: substance.h,v 1.10 2002/06/03 11:48:24 mkrohn5 Exp $
//
// Substance Header File
// Written by: Alberto Barsella
//
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

#ifndef __TSUBSTANCE_INCLUDED
#define __TSUBSTANCE_INCLUDED

#include "common/osval.h"
#include "common/link.h"
#include "common/plist.h"

#include <string>
#include <vector>
class TDataPackageList;

class TSubstance;
class TSubstanceType;
class TSubstanceSet;
class TSubstanceHold;

/**
 * Substance Id type, used to reference substances without resorting
 * to a TSubstanceType pointer.
 */
typedef uint2 SubstanceId;


/**
 * Substance type class.  Instances of this class represent substances
 * with the same set of properties.  Every substance type is
 * automatically assigned an id which can be used in place of the name
 * for faster operation.  Substance parameters such as size, mass,
 * etc. are stored here.  The class can be used as a base class for
 * the introduction of types which require more parameters than the
 * one currently available.
 * 
 *
 * Please check TSubstance for an overview of the substance classes.
 *
 * @short Substance handling classes: substance Type
 * @version $Id: substance.h,v 1.10 2002/06/03 11:48:24 mkrohn5 Exp $
 * @see TSubstance,TSubstanceSet,TSubstanceHold
 */
class TSubstanceType : public TLinkable
{
  public:
    /**
     * The TSubstanceType constructor is used to define a new type of
     * substance to be used. All properties must be specified at
     * creation and are *constant*.
     *
     * @param name Name of the substance (localizable).
     * @param abbrev Abbreviation of the name (fixed, used in files).
     * @param cclass Cargo class used by thie substance.
     * @param usize Size taken by a single unit of substance.
     * @param umass Mass of a single unit of substance.
     * @param update Specifies if the substance needs periodic updates or
     * not (e.g. growing population).
     */
    TSubstanceType(const string& name, const string& abbrev,
		   const uint2 cclass, const int2 usize, const int2 umass,
		   const bool update = false);
    /**
     * Destructor, virtual to allow derivation.
     */
    virtual ~TSubstanceType(void);

    // accessors
    /**
     * Read-accessor to Substance name.
     * @returns name of the substance type.
     */
    const string& Name(void) const;
    /**
     * Read-accessor to Substance abbreviated name.
     * @returns abbreviation of the substance type.
     */
    const string& Abbrev(void) const;
    /**
     * Read-accessor to Substance ID number.
     * @returns ID number of the substance type.
     */
    const uint2   Id(void) const;
    /**
     * Read-accessor to Substance cargo class.
     * @returns cargo class of the substance type.
     */
    const uint2   CargoClass(void) const;
    /**
     * Read-accessor to Substance size / unit.
     * @returns size/unit ration of the substance type.
     */
    const int2    UnitSize(void) const;
    /**
     * Read-accessor to Substance mass / unit.
     * @returns mass/unit ration of the substance type.
     */
    const int2    UnitMass(void) const;
    /**
     * Determine if the Substance Type requires updates of substance
     * objects.
     * @returns true if substance has time evolution, false otherwise.
     */
    const bool    Updatable(void) const;

    /**
     * Class-wide member to return the total number of Substances
     * currently defined.
     * @returns number of defined substance types.
     */
    static const uint4 NumberSubstances(void);
    /**
     * Class-wide member to return the total number of different
     * cargo classes defined.
     * @returns number of defined cargo classes.
     */
    static const uint2 NumberCargoClasses(void);
    /**
     * Class-wide member to obtain a pointer to the SubstanceType
     * corresponding to a specified ID number.
     * @returns pointer to a TSubstanceType.
     * @param Id the id of the requested substance type.
     */
    static TSubstanceType* FindById(const SubstanceId Id);
    /**
     * Class-wide member to obtain a pointer to the SubstanceType
     * corresponding to a specified substance name.
     * @returns pointer to a TSubstanceType.
     * @param Name the name of the requested substance type.
     */
    static TSubstanceType* FindByName(const string& Name);

    /**
     * Substance creator.  This function is used to create a specified
     * amount of the substance.  It replaces the TSubstance class
     * constructor. 
     * @returns allocates and returns a new TSubstance object
     * containing the specified amount. THE CALLER IS IN CHARGE OF
     * DEALLOCATION.
     * @param iAmount the amount of substance to be created.
     */
    virtual TSubstance* Create(const TOSVal& iAmount = 1);

    /**
     * Default update method for the substance.  If a group of 
     * substance types share the same time-evolution properties then
     * one can put the update function here and have all the objects
     * call this function for update (default behaviour).  If the
     * update depends on some weird, substance object-dependent value
     * then one should consider deriving from TSubstance and replacing
     * the Update function down there.
     * @returns the amount of substance that must be added/removed
     * which results from the time evolution.
     * @param substance pointer to the TSubstance object to evolve.
     * @param available_space indication of the available cargo space
     * (note that the return value may be greater than this value, it's
     * up to the caller to ensure it fits).
     */
    virtual TOSVal Update(TSubstance* substance, const TOSVal& available_space);
    /** The method Load loads a TSubstanceType object from the data packages
     *  in the list. For more information look in the documentation of the
     *  ancestors of TSubstanceType from where this method is inherited.
     *  @param in the list of data packages
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool load( TDataPackageList* in );
    /** The method Save saves a TSubstanceType by adding the data packages to
     *  the list. For more information look in the documentation of the
     *  ancestors of TSubstanceType, because the method Save is inherited from
     *  there.
     *  @param out the output stream of data packages
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    virtual bool save( TDataPackageList* out ) const;

  private:
    string fName;        // name of the substance
    string fAbbrev;      // abbreviation of name, language independent,
                         // used in the creation of ASCII files
    SubstanceId fId;     // Id of the substance
    uint2  fCargoClass;  // type of cargo space used by the substance
    int2   fUnitSize;    // size (cargo space) of a unit
    int2   fUnitMass;    // mass (kT) of a unit
    // the above values are stored as int2 as they'll not be big

    // this one is needed to speed things up. Since update needs the
    // available cargo space we compute it ONLY for substances needing updates
    bool   fUpdatable;

    // global list of substances, indexed by Id,
    // and max # for cargo class
    static vector<TSubstanceType*> fSubstanceTable;
    static uint2 fCargoClasses;

    // disallow duplication of object
    TSubstanceType(const TSubstanceType&);
    TSubstanceType& operator=(const TSubstanceType&);
};



/**
 * @class TSubstance
 * @brief Substance handling classes: substance object
 * @author Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
 * @version $Id: substance.h,v 1.10 2002/06/03 11:48:24 mkrohn5 Exp $
 * @see TSubstanceType,TSubstanceSet,TSubstanceHold
 *
 * Substance object class.  Instances of this class represent a given
 * amount of a specific substance. This class can be used as a base
 * class to provide really special substance (e.g. where update is
 * dependent on the specific instance).
 *
 * This class DOES NOT provide a constructor. Creation of instances
 * should pass through @ref TSubstanceType::Create. Copy constructor is
 * not available as well: derivation-safe duplication is obtained via
 * a Clone method.
 *
 * <h3>Purpose</h3>
 *
 * The TSubstanceXXXX classes are used to implement and manipulate
 * substances, such as minerals, colonists, fuel, resources, etc. The
 * aim is to provide a general structure, sufficient to handle the
 * simplest cases (like minerals), which can be expanded via
 * derivation to handle more complex substances (such as growing
 * colonists, for example).
 * 
 * Creation of new substances can be performed at runtime for
 * substances whose properties are already coded. Creation of new
 * substance classes (with different properies, e.g. the growing
 * colonists) will require modification of the code and recompilation.
 *
 * <h3>Class organization</h3>
 * 
 * There are four classes: 
 *
 * <ol>
 * <li>TSubstanceType: instances of this class represent different
 * substances with the same (basic) properties. For example, germanium
 * and ironium are two istances of this class. In the case of growing
 * colonists, two steps are needed: first, a derived class of
 * TSubstanceType is created, providing the needed time-evolution
 * functions, then instances of this new class will represent specific
 * growing colonists.</li>
 *
 * <li>TSubstance: instances of this class (which can be used as a base
 * class) are used to represent a specified amount of a single
 * substance. Basically they have a type (read TSubstanceType*) and an
 * amount field.</li>
 *
 * <li>TSubstanceSet: is a set of substances. It's used to represent item
 * costs and it's used in production calculations.</li>
 *
 * <li>TSubstanceHold: is the same as TSubstanceSet, but with limits
 * imposed on the maximum space available to store substances. They
 * are used for cargo holds.</li>
 * </ol>
 *
 * <h3>Substance properties: cargo classes/space</h3>
 *
 * Every substance type (i.e. every instance of TSubstanceType or its
 * derived classes) is characterized by some properties which specify
 * the behaviour of the substance. Examples are the mass for every
 * unit of substance and the size for every unit. A special property
 * is the cargo class: it specifies which substances are considered
 * identical in the calculation of used space. For example: fuel is
 * stored in fuel tanks, while germanium/ironium/boranium are stored
 * in cargo space. Minerals cannot stay into a fuel tank and fuel
 * cannot stay in cargo space. This is implemented by giving a "fuel"
 * cargo class to fuel and a "generic cargo" cargo class to all
 * minerals. This allows TSubstanceHold to properly handle limited
 * space, using a different maximum for every cargo class.
 *
 * This approach is better shown by looking at how cargo space is
 * specified in a TSubstanceHold (Hold for short). Basically, a Hold
 * is the same as a TSubstanceSet, with one additional restriction:
 * the total size of substances contained in the set which share the
 * same cargo class must be negative. This is obtained by creating
 * substances which have a negative size, 100 units of this substance
 * will take up -100 space of the cargo class of the substance. The
 * presence of this "special substance" allows the addition to 100
 * size of positive-sized substances before the Hold is considered
 * full.
 *
 * For example, in the case of minerals, we create three istances of
 * TSubstanceType, to represent ironium, boranium and germanium. They
 * all have the same cargo class and the size property is "1 unit of
 * substance takes 1 unit of space". We then add another substance,
 * called "Mineral Cargo Space", which has the same cargo class of the
 * three minerals, but which size property is "1 unit of substance
 * takes -1 unit of space".  Holds are then "expanded" by adding to
 * them a specified amount of the "Mineral Cargo Space" substance.  If
 * we want to have a separate "cargo" for fuel (i.e. a tank) we just
 * define a "Fuel" substance of size 1, giving it a new cargo class,
 * together with a "Fuel Tank" substance which has the same cargo
 * class and -1 negative size.
 *
 * This approach should give all the necessary flexibility for
 * subnstance with different sizes, "living space" for carrying
 * colonists separate from minerals, etc. etc.
 *
 * <h3>Problems</h3>
 *
 * I'm not sure that creating whole new substances by deriving from
 * TSubstance will be handled correctly by TSubstanceHold. Actually,
 * I'm quite sure that it WON'T. I'll work on it when we need it
 * :). (new types - derived from TSubstanceType - which use TSubstance
 * work correctly).
 */
class TSubstance
{
  public:
    /**
     * Destructor, virtual to allow derivation.
     */
    virtual ~TSubstance(void);
    /**
     * Assignment operator. This is not derivation-safe so I'll kill it.
     */
    virtual TSubstance& operator=(const TSubstance& Subst2);

    /**
     * Duplicate the substance. As with TSubstanceType.Create, a new
     * instance is allocated and initialized.
     * @returns allocates and returns a new TSubstance object.
     * THE CALLER IS IN CHARGE OF DEALLOCATION.
     */
    TSubstance* Clone(void) const;

    /**
     * Read-accessor to the Type of the TSubstance object. This is not
     * a virtual function, since Type is Type!
     * @returns pointer to the TSubstanceType object of this substance.
     */
    TSubstanceType* Type(void) const;
    /**
     * Read-accessor to the substance amount.
     * @returns a constant value representing the number of substance units.
     */
    virtual const TOSVal& Amount(void) const;
    /**
     * Write-accessor to the substance amount.
     * @returns a reference to the value representing the number of
     *   substance units.
     */
    virtual TOSVal& Amount(void);
    /**
     * Determine the total size taken by the substance object.
     * @returns the amount of cargo space taken by this substance.
     *   It can be a negative number for "space"-type substances.
     */
    virtual const TOSVal Size(void) const;
    /**
     * Time evolution function.  By default it calls Type()->Update().
     * Overloading may be desirable in case of weird operations which are
     * very object-dependent. (will we ever need this?).
     */
    virtual TOSVal Update(const TOSVal& available_space);
    /** With the method Load you can load a TSubstance object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /** With the method Save you can save a TSubstance object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is to be saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool save( TDataPackageList* out, const string& sIdentifier, bool bUnique=true ) const;

  private:
    TLink<TSubstanceType> fType;    // link to the type of the substance
    TOSVal fAmount;               // amount of the specified substance

    // creation occurs through TSubstanceType, constructor is then
    // private and the class is friendly

    // iAmount = 0
    friend TSubstance* TSubstanceType::Create(const TOSVal& iAmount);
    TSubstance(TSubstanceType* type, const TOSVal& iAmount = 1);
    TSubstance(void);
    TSubstance(const TSubstance& Subst2);
};

/**
 * TSubstance output function, provides stream-compatible output for
 * TSubstance objects.  It writes a human-readable string
 * representation of the TSubstance object to the stream
 * @returns the given stream.
 * @param os output stream where string is written
 * @param Subst the TSubstance object
 */
ostream& operator<<(ostream& os, const TSubstance& Subst);



/**
 * Substance set class.  Instances of this class represent groups of
 * substances. Substances of the same type are automatically added, so
 * you can't have two ironoum amounts: they'll be added.
 *
 * Please check TSubstance for an overview of the substance classes.
 *
 * @short Substance handling classes: substance Set
 * @version $Id: substance.h,v 1.10 2002/06/03 11:48:24 mkrohn5 Exp $
 * @see TSubstanceType,TSubstance,TSubstanceHold
 */
class TSubstanceSet
{
  public:
    /**
     * Constructor: builds an empty set.
     */ 
    TSubstanceSet(void);
    /**
     * Non-virtual destructor, TSubstanceSet is not meant for
     * derivation (you can derive it but must not use TSubstanceSet*
     * to point to a derived object).
     */
    ~TSubstanceSet(void);
    /**
     * Copy constructor: duplication of Sets is legal.
     */
    TSubstanceSet(const TSubstanceSet& Set2);
    /**
     * Compare operator
     */
    bool operator==(const TSubstanceSet& Set2) const;
    bool operator!=(const TSubstanceSet& Set2) const;
    /**
     * Assignment operator: duplication of Sets is legal.
     */
    TSubstanceSet& operator=(const TSubstanceSet& Set2);

    /**
     * Clear the set, eliminating all elements it contains. 
     */ 
    void Clear(void);

    /**
     * Determine the size "offered" by negative-sized substances
     * (positive-sized are ignored).
     * @returns the opposite of the total size (i.e. a positive
     * number) of negative-sized substances. 
     * @param uCClass cargo class to be examined.
     */
    TOSVal TotalSpace(const uint2 uCClass) const;
    /**
     * Determine the size offered/taken by all substances (acts like
     * "remaining cargo space").
     * @returns the opposite of the total size (i.e. a positive
     * number) of all substances.
     * @param uCClass cargo class to be examined.
     */ 
    TOSVal AvailableSpace(const uint2 uCClass) const;
    /**
     * Determine the size taken by all positive-sized substances (acts
     * like "how much stuff is stored").
     * @returns the the total size (i.e. a positive number) of all
     * positive-sized substances.
     * @param uCClass cargo class to be examined.
     */ 
    TOSVal UsedSpace(const uint2 uCClass) const;


    /**
     * Check if the Set has enough substances to allow a
     * removal of the amount specified by Set2 * iNum / iDenom. In any
     * case the set is left untouched. 
     * @returns false if there are not enough substances and true if
     * there are enough. 
     * @param Set2 specifies the amount against which to check.
     * @param iNum (default 1) multiplies Set2.
     * @param iDenom (default 1) divides Set2.
     */
    bool HasEnough(const TSubstanceSet& Set2,
		   const int4 iNum = 1, const int4 iDenom = 1) const;
    /**
     * Adds to the Set the amount specifies by Set2. Set2 is left untouched.
     * The new set is added iNum/iDenom times. The default values for
     * both iNum and iDenom are 1.
     * @returns always true.
     * @param Set2 the substances to be added to the Set.
     * @param iNum (default 1) multiplies Set2.
     * @param iDenom (default 1) divides Set2.
     */ 
    bool Add(const TSubstanceSet& Set2,
             const int4 iNum = 1, const int4 iDenom = 1);
    /**
     * Remove is used to subtract sets. If the Set does not contain
     * enough substances to allow the removal of the amount given by
     * Set2 * iNum / iDenom the function returns false and no action
     * is taken. If the Set contains enough substances, then they are
     * removed and the function returns true.
     * @returns true if removal was done, false otherwise.
     * @param Set2 amount of substances to be removed.
     * @param iNum (default 1) multiplies Set2.
     * @param iDenom (default 1) divides Set2.
     */
    bool Remove(const TSubstanceSet& Set,
		const int4 iNum = 1, const int4 iDenom = 1);


    /**
     * Check if the Set has enough of the specified substance. In any
     * case the set is left untouched. 
     * @returns false if there is not enough substance and true if
     * there is enough. 
     * @param Subst specifies the substance type/amount amount against
     * which to check. 
     * @param iNum (default 1) multiplies Subst.
     * @param iDenom (default 1) divides Subst.
     */
    bool HasEnough(const TSubstance& Subst,
		   const int4 iNum = 1, const int4 iDenom = 1) const;
    /**
     * Adds to the Set the given substance set. Set2 is left untouched.
     * The new set is added iNum/iDenom times. The default values for
     * both iNum and iDenom are 1.
     * @returns always true.
     * @param Subst the substance to be added to the Set.
     * @param iNum (default 1) multiplies Subst
     * @param iDenom (default 1) divides Subst
     */ 
    bool Add(const TSubstance& Subst,
             const int4 iNum = 1, const int4 iDenom = 1);
    /**
     * Remove a specified substance from the set. If the Set does not
     * contain enough substances to allow the removal of the amount
     * given by Subst * iNum / iDenom the function returns false and no
     * action is taken. If the Set contains enough substance, then
     * it is  removed and the function returns true.
     * @returns true if removal was done, false otherwise.
     * @param Subst substance to be removed.
     * @param iNum (default 1) multiplies Subst
     * @param iDenom (default 1) divides Subst
     */
    bool Remove(const TSubstance& Subst,
		const int4 iNum = 1, const int4 iDenom = 1);

    // accessor to subs

    /**
     * Access a specified type of substance directly (read mode).
     * @returns a const pointer to the substance if found, NULL if not
     * found.
     * @param Type a pointer to the substance type object.
     */ 
    const TSubstance* operator[](const TSubstanceType* Type) const;

    /**
     * Provide access to the internal vector. This is dangerous and
     * will either be eliminated or replaced with a safe implemetation.
     */
    const TPEList<TSubstance>& Content(void) const;

    /**
     * TSubstanceSet output function, provides stream-compatible output for
     * TSubstanceSet objects.  It writes a human-readable string
     * representation of the Set object to the stream.
     * @returns the given stream.
     * @param os output stream where string is written
     * @param Set the TSubstanceSet object.
     */
    friend ostream& operator<<(ostream& os, const TSubstanceSet& Set);

    /** With the method Load you can load a TSubstanceSet object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /** With the method Save you can save a TSubstanceSet object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is to be saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool save( TDataPackageList* out, const string& sIdentifier, bool bUnique=true ) const;
  protected:
    /**
     * Locate a TSubstance in the internal vector.
     */
    TSubstance* FindSubstance(const TSubstanceType* type) const;
    /**
     * Delete a TSubstance object from the internal vector.
     */
    void DeleteSubstance(TSubstance* Subst);

    // substances contained, a list of TSubstance objects
    // the Infinity and Maximum are acceptable values
    // to identify an infinite supply or an unlimited storage space
    TPEList<TSubstance> fContains;
};




/**
 * Substance hold class. This function is derived from TSubstanceSet,
 * but you should act as if it weren't :) It provides similar
 * operation, but guarantees that the total size (positive-sized and
 * negative-sized substances) for a specified cargo class is megative,
 * i.e. you cannot put in more stuff than the space to hold it.
 *
 * Please check TSubstance for an overview of the substance classes.
 *
 * @short Substance handling classes: substance Hold
 * @version $Id: substance.h,v 1.10 2002/06/03 11:48:24 mkrohn5 Exp $
 * @see TSubstanceType,TSubstance,TSubstanceSet
 */
class TSubstanceHold : private TSubstanceSet
{
public:
    TSubstanceHold(void);
    ~TSubstanceHold(void);
    TSubstanceHold(const TSubstanceHold& Hold2);
    TSubstanceHold& operator=(const TSubstanceHold& Hold2);

    // TSubstanceHold overloads the Set functions to incorporate
    // cargo space checks
    TOSVal TotalSpace(const uint2 uCClass) const;
    TOSVal AvailableSpace(const uint2 uCClass) const;
    TOSVal UsedSpace(const uint2 uCClass) const;

    void Clear(void);
    // as clear, but only eliminates positive-size items
    void Empty(void);

    // Hold-specific manipulations (substance transfers, split, merge is Set::Add)
    bool GetAllFrom(TSubstanceHold* Hold2);
    bool GetFrom(TSubstanceHold* Hold2, const TSubstanceSet& MaxAbsolute,
		 const TSubstanceSet& MaxRelative);
    bool SplitOff(TSubstanceHold* Hold2);

    bool CanAdd(const TSubstanceSet& Set) const;
    bool Add(const TSubstanceSet& Set2, TSubstanceSet* Added);
    bool CanRemove(const TSubstanceSet& Set,
		   const int4 iNum = 1, const int4 iDenom = 1) const;
    bool Remove(const TSubstanceSet& Set, TSubstanceSet* Removed,
		const int4 iNum = 1, const int4 iDenom = 1);

    // Single substance manipulation
    bool CanAdd(const TSubstance& Subst) const;
    bool Add(const TSubstance& Subst, TSubstance* Added);
    bool CanRemove(const TSubstance& Subst,
		   const int4 iNum = 1, const int4 iDenom = 1) const;
    bool Remove(const TSubstance& Subst, TSubstance* Removed,
		const int4 iNum = 1, const int4 iDenom = 1);

    // update stuff inside the Hold
    void UpdateCargo(void);

    friend ostream& operator<<(ostream& os, const TSubstanceHold& Hold);

    /** With the method Load you can load a TSubstanceHold object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was loaded correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /** With the method Save you can save a TSubstanceHold object from the data
     *  packages in the list. For more information look in the documentation
     *  of TLinkable.
     *  @param in the list of data packages
     *  @param sIdentifier the string this item pack is to be saved under
     *  @param bUnique bool value whether the indentifiers have to be unique
     *  @return @c true means that everything was saved correctly, otherwise
     *          this method will return @c false.
     *  @see TLinkable                                                         */
    bool save( TDataPackageList* out, const string& sIdentifier, bool bUnique=true ) const;
  private:
    vector<TOSVal> fTotalSpace;
    vector<TOSVal> fAvailSpace;

    // low-level insert/remove functions
    void In(const TSubstance& s);
    void Out(const TSubstance& s, const int4 iNum, const int4 iDenom);
};



#endif        // __SUBSTANCE_INCLUDED
