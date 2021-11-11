// $Id: ruleatom.h,v 1.15 2002/08/12 23:47:51 mkrohn5 Exp $

// RuleAtom Header File
// Written by: Marco Krohn <marco.krohn@gmx.de>

// Copyright (C) 2001 - 2002, Marco Krohn <marco.krohn@gmx.de>
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

#ifndef __RULEATOM_INCLUDED
#define __RULEATOM_INCLUDED

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

#include "common/datapackage.h"
#include "common/defs.h"
#include "common/leakchecker.h"
#include "common/prototype.h"
#include "gamelogic/rulesystem.h"

class TLinkable;
class TRuleAtom;

using namespace std;





//----------------------------------------  type definitions  ----------------------------------------

/**
* This defines the "key" to access rule atoms: name + rule set.
* The structure is used in TPrototypeManager as the key which is associated
* with a prototype. See TPrototypeManager for more information.
*/
typedef struct tRuleAtomKey
{
  tRuleAtomKey( const string& name, const string& set ) : rule_name(name), rule_set(set) { };
  bool operator<( const tRuleAtomKey& key2 ) const
  {
    if ( rule_name == key2.rule_name )  return rule_set < key2.rule_set;
    return rule_name < key2.rule_name;
  }
  ostream& write( ostream& stream ) const
  {
    return stream << '(' << rule_name << ',' << rule_set << ')';
  }

  string rule_name;
  string rule_set;
};



/**
* Stream operator for tRuleAtomKey, allowing e.g. "cout << key".
* The output is a combination of the rule name and the used rule set,
* for instance: "(fleet_movement,stellarlegacy)".
* @param stream the current ostream for output.
* @param key this one will be written to the output stream.
* @return The old stream + the new string.
*/
ostream& operator<<( ostream& stream, const tRuleAtomKey& key );



/**
* Just an abbreviation to avoid typing.
*/
typedef TPrototypeManager<tRuleAtomKey,TRuleAtom> TPMRuleAtom;






//----------------------------------------  Some evil defines  ----------------------------------------
// this makes writing rule atoms a lot easier

#define RuleAtomBaseClass(a)        TRuleAtom##a
#define RuleAtomClass(a,b)          TRuleAtom##a##b
#define RuleAtomProto(a,b)          RuleAtom##a##b##Proto
#define RuleAtomName(a,b)           "TRA"#a#b
#define RuleAtomMethod(a,b)         RuleAtomClass(a,b)

#define DefineRuleAtom(a,b,c,d)     RuleAtomClass(a,b)* RuleAtomProto(a,b) = new RuleAtomClass(a,b)(c); \
                                    RuleAtomClass(a,b)::RuleAtomClass(a,b)(const string& name)    \
                                      : RuleAtomBaseClass(a)()                                    \
                                    {                                                             \
                                      declareAsPrototype( name );                                 \
                                      TPMRuleAtom::instance().registerPrototype(tRuleAtomKey(c,d),this); \
                                    }                                                             \
                                    RuleAtomClass(a,b)::RuleAtomClass(a,b)()                      \
                                      : RuleAtomBaseClass(a)()                                    \
                                    { }                                                           \
                                    RuleAtomClass(a,b)::~RuleAtomClass(a,b)()                     \
                                    { }

#define DeclareRuleAtom(a,b)        class RuleAtomClass(a,b) : public RuleAtomBaseClass(a) {      \
                                      public:                                                     \
                                        RuleAtomClass(a,b)(const string& name);                   \
                                        virtual ~RuleAtomClass(a,b)();                            \
                                        virtual bool execute();                                   \
                                        virtual bool checkDependencies( list<TRuleSystem::tError>* errors ) const; \
                                      private:                                                    \
                                        RuleAtomClass(a,b)();                                     \
                                        virtual TCanBePrototype* clone() const { return new RuleAtomClass(a,b)(); }

#define EndDeclareRuleAtom          }

#define DeclareRuleAtomBase(a)      class RuleAtomBaseClass(a) : public TRuleAtom                 \
                                    {                                                             \
                                      public:                                                     \
                                        virtual ~RuleAtomBaseClass(a)() { }                       \
                                        RuleAtomBaseClass(a)() : TRuleAtom()                      \
                                        {  }                                                      \
                                      protected:                                                  \
                                        void validate()                                           \
                                        {

#define CHECK(a)                          validateInfo(a);

#define EndDeclareRuleAtomBase          }                                                         \
                                    }


#define RAUnsupported(type)         Fatal( #type, "unsupported method", "an unsupported method was called for a rule atom "#type, -1)







//----------------------------------------  class TRuleAtom  ----------------------------------------

/**
* @class TRuleAtom
* @brief The base class for all rule atoms.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: ruleatom.h,v 1.15 2002/08/12 23:47:51 mkrohn5 Exp $
* @see TRuleSystem
*
* FIXME: TRuleAtoms are now created with the prototype pattern.
* this means that you can't directly create prototypes, but instead have
*
* FIXME: some other stuff is outdated as well.
*
* FIXME: rule atoms may use other rule atoms
*
* This class is the base class for all rule atoms. The general idea is,
* that all game rules are seperated into small pieces and implemented
* as so called "rule atoms" (examples for rule atoms are: the fuel consumption
* of a fleet, the rule that decides if a fleet engine ignites or not, ...).
*
* One advantage of using rule atoms is the possibility of using different
* implementations for the very same rule. Therefore one needs
* (in order to distinguish rule atoms) two pieces of information: the name of
* the rule atom and the "rule set" the rule atom belongs too.
*
* Examples for rule atoms: fleet_movement, fleet_engine_failure, ...
*
* Examples for rule sets: basic, stars!, stellarlegacy, ...
*
* A "rule set" is basically a collection of rule atoms. The "basic" rule set
* contains all rule atoms which use a very simple logic to decide something
* (e.g. the fleet max. speed is always constant). The "stars" rule set
* contains the rule atoms which emulate the famous stars! (tm) strategy game
* and finaly "stellarlegacy" contains the rules for the "real" Stellar Legacy
* game (note: SL is basically a frame work for space and turn based strategy
* games and @e one possible rule set are the so called "stellarlegacy" rules).
* And of course you are free to write your own set of rules!
*
* Since there are different implementations available one has to decide for a
* rule set during the game setup. The class which is responsible for storing
* the used rule atoms is TRuleSystem.
*
* Actually it is even possible to use a mixture of rule atoms from different rule sets
* within the same game. For instance you can use the "fleet_movement" rule of
* "stars!" and the "population_growth" rule atom from the "stellarlegacy" rule
* set. TRuleSystem stores these information, checks certain dependecies and
* returns the wanted rule via the method @ref TRuleSystem::getRuleAtom (examples follow
* below). Mixing rule atoms allows very different games e.g. it is
* possible (by choosing the right rule atoms) to use a simple economic
* model on the one hand and a very complex battle / movement model on the
* other.
*
* What follows is a detailed description and example code how to write and implement
* rule atoms.
*
* <h2>Using Rule Atoms</h2>
*
* Imagine we want to move a fleet around. This means that a lot of things
* have to be considered: what is the speed of the fleet, are there any minefields
* in the way, does the fleet ran out of fuel and so on. The rule atom which
* takes care of these aspects is called (surprise!) "fleet_movement". Note: a rule
* atom can call other rule atoms. For instance in this case the "fleet_movement"
* makes heavy use of other rule atoms such as rules which decide if the fleet
* hits a mine field, the damage of mines--even the fuel consumption is implemented
* as its own rule atom.
*
* Now let's have a look at the following real world code:
*
* <pre>
*  1   TRuleAtom* ra = TRuleSystem::instance().getRuleAtom("fleet_movement");
*  2   ra->addInfo( "fleet", a_fleet );
*  3   ra->addInfo( "time", 1.0 );
*  4   ra->execute( ra );
*  5   delete ra;
* </pre>
*
* (1) The first thing you have to do is fetching the right rule from the rule
* system. TRuleSystem looks up which rule atom will is in use (again: SL
* allows different implementations of the very same rule atom, see above).
*
* (2,3) In almost all situations the rule atom needs information before the rule
* atom can be executed. To find out what information is needed for a rule atom
* you can look at the documentation, e.g. TRuleAtomFleetMovementBasic. Note: the
* parameters and return values of a rule atom should be all the same (meaning
* there should be no difference if you look at the "stars!" or "basic"
* implementation of a rule atom).
*
* (4) Eventually the rule atom can be executed: this means in some cases you
* get a "return value" (e.g. if the engines ignite or not) or in other cases
* objects are directly modified (e.g. applying damage to a fleet and
* reducing the number of mines in a mine field). More about
* returning information from the rule atom to the caller follows below.
*
* <h2>Writing Rule Atoms</h2>
*
* First we should make clear again that we are talking of one rule
* (e.g. "fleet_movement"), but that this rule atom can have different
* implementations: one for basic rule set, one for the stars! rule set, ...
*
* For example the rule "fleet_movement" exists in at least three "flavours":
* TRuleAtomFleetMovementBasic, TRuleAtomFleetMovementStars and TRuleAtomFleetMovementSL.
* These three implementations of the rule are all derived from the
* @e baseclass TRuleAtomFleetMovement (which purpose is only validating
* data and defining a common documentation interface).
*
* Writing the declaration is simple as the following example illustrates:
*
* <pre>
*  1   #include "gamelogic/ruleatom.h"
*  2
*  3   ... class documentation ...
*  4   DeclareNewRuleAtom(FleetMovement,Basic)
*  5   EndDeclareRuleAtom;
* </pre>
*
* That is everything you have to add to the header file.
*
* (1) ensure that the ruleatom.h file is included since this includes the
* macros needed below.
*
* (3) do not forget to write the documentation and ensure that you use
* exactly the same parameters and return values as all other rule atoms
* of the same type do. This interface is defined in the base class, in
* this case TRuleAtomFleetMovement.
*
* (4) First name the rule atom (here: "FleetMovement") then write down
* to which rule set you want this rule atom belong to (here: "Basic").
*
*
*
* The definition of the rule atom then might look like the following
* example code:
*
* <pre>
*  1   DefineNewRuleAtom(FleetMovement,Basic,"fleet_movement","basic");
*  2
*  3   bool RAMember(FleetMovement,Basic)::execute()
*  4   {
*  5     if ( validateInfo() == false )  return false;
*  6
*  7     double time = getInfoDouble("time");
*  8     TFleet* fleet = dynamic_cast<TFleet*>( getInfoObject("fleet") );
*  9     ... code for calculating the new fleet pos ...
* 10     fleet->setPos( src );
* 11
* 12     return true;
* 13   }
* </pre>
*
*
*
* fo() (see more below). Lets not talk about l. 5 here,
* which is explained in more detail in the section about "return" values.
* The interesting thing starts in l.6: as we find out in the documentation
* there exists a piece of information called "fleet" and this fleet is
* indeed a TFleet object. This fleet is converted to the correct time
* and used to find out the current speed of this fleet and also some other
* things.
*
* Note that we refer to the base class of TFleet and not to a special
* implementation like TFleetStars. While the latter is allowed we have
* to introduce dependencies from this special module which is explained
* below. In this case we don't have any dependencies on special modules.
*
* Actually this is all you need to know to write an implementation of a rule.
* Always check which information (as in l. 6) you can use by reading the
* documentation of the base class (in this case TFleetEngineFailure).
* And vice versa document the information which is needed to execute the
* rule in the base class.
*
* <h2>Providing Additional Information</h2>
*
* This method is implemented in the @e base @e class and tries to find out
* additional information if needed. It also checks the existence of all
* neccessary information and therefore if called by @ref execute prevents
* execution of the rule atom if not all information is gathered.
* (That is why @ref execute always should call this method).
*
* FIXME
* rule of thumb: anything which needs more than one simple call
* (like fleet->getOwner) can be provide by this method.
* should also check if obj!=0
*
* <h2>Checking Dependencies</h2>
*
* Some rule atoms might require a special functionality of a module.
* For example if we have a (part of a) rule like: "if a race has the LRT
* (lesser racial trait) X then item Y is not allowed for that race" we
* certainly need the functionality that the "race" module offers a method
* like "hasLRT". The general interface TRace does not provide this method,
* but the "stars!" implementation of TRace does.
*
* Now to ensure that rule atoms and modules fit nicely together each
* rule atom is "asked" in the beginning if the current set of modules
* is o.k. or not. All you have to do is overwriting the method
* "checkDependencies(...)", like in the following example code:
*
* <pre>
* bool TRAItemAccessStars :: checkDependencies( list<TRuleSystem::tError>* errors ) const
* {
*   if ( rules->getModule(TRuleSystem::RACE) == TRuleSystem::STARS ) {
*     return true;
*   }
*   errors->push_back( TRuleSystem::tError("item_access", TRuleSystem::RACE) );
*   return false;
* }
* </pre>
*
* This code tests (for the stars! rule set of the rule atom "item_access")
* if the race module is from the stars! rule set. Of course if the SL
* rule set also offers the needed "hasLRT()" functionality
* one can extent the condition and also allow TRuleSystem::SL.
* If the dependency check fails the method should add an error message
* to the list of errors, since this list is needed by a client to give some
* feedback to the user what went wrong. The information you have to
* provide is: 1. the name of the rule atom, and 2. with which module
* the conflict exists. It is explicitly allowed (actually it is desired) that
* more than one error message is added to the list if more conflicts
* exist.
*
* Note: if you only use methods which are provided by the general
* interface of a module (this means for example the interface of TRace, but
* not the interface of TRaceSL) than you don't need to care about
* dependencies.
*
* <h2>Returning Information</h2>
*
* Sometimes it is neccessary for the ruleatom to "return" some results to
* the caller of the ruleatom. Therefore the ruleatom has a TDataPackageList,
* which stores the results. The caller of a ruleatom is then able to read
* this list, but of course he has to do it before deleting the rule atom.
* Note that only some datatypes are allowed for TDataPackageList--namely in
* this case these are: @c bool, @c double, @c int2, @c int4, @c string and
* TPoint which should be sufficent for most cases.
*
* Adding results and getting them is very easy--on the ruleatom side
* you write:
*
* <pre>
*   fResults->set( "engine_failure", false );
*   fResults->set( "test_string", "some useless string" );
* </pre>
*
* to store the data (nothing else is needed) and on the other side
*
* <pre>
*   ra->getResults()->getBool("engine_failure");
*   ra->getResults()->getString("test_string")
* </pre>
*
* to get the data (where @c ra is of course a TRuleAtom). Note that it is
* o.k. to change the results on the rule atom side, whenever you want,
* for example the following code is completly o.k.:
*
* <pre>
*   fResults->set( "engine_failure", false );
*   fResults->set( "engine_failure", true );               // overwrites the old result
* </pre>
*
* You should document the possible results of the rule atom in the base class,
* e.g. in TRuleAtomFleetEngineFailure.
*
* <h2>Miscellaneous</h2>
*
* <ul>
*   <li>The folder "code/tools/make_ra" contains a simple script to create
*     skeleton .cpp and .h files. Simply make the obvious adaptions in
*     the script "create" and run it. Copy the files to gamelogic/ruleatoms
*     and start writing your own rule atom.</li>
*   <li>Do not forget to make the neccessary changes in TRuleSystem::fetchRule(...)
*     and TRuleSystem::TRuleSystem() if you started a new rule.</li>
*   <li>The README file in gamelogic/ruleatoms gives an overview about
*     the existing rule atoms. Please keep this file up to date.</li>
* </ul>
*/
class TRuleAtom : public TCanBePrototype
{
  public:
    /**
    * Deletes the result lists.
    */
    virtual ~TRuleAtom();

    /**
    * Adds a piece of information to the rule atom. It is up to you
    * to ensure that you do not use two times the same identifier
    * with a different data type.
    * @param info The name for the information e.g. "observer" for a race
    *   which watches a situation.
    * @param obj The "real" information, e.g. the race from the example above.
    */
    void addInfo( const string& identifier, TLinkable* obj );
    void addInfo( const string& identifier, double data );
    void addInfo( const string& identifier, int2 data );
    /**
    * FIXME
    */
    virtual bool checkDependencies( list<TRuleSystem::tError>* errors ) const = 0;
    /**
    * After sending all neccessary information to the rule atom
    * (see @ref addInfo) the rule can be executed.
    * @return @c true execution was successful, otherwise @c false
    *   (e.g. if not enought information was available).
    */
    virtual bool execute() = 0;

    double getInfoDouble( const string& identifier ) const;
    /**
    * Note that this command will FIXME
    * @param identifier The name for the information.
    * @return The
    * @see addInfo
    */
    int2 getInfoInt2( const string& identifier ) const;
    /**
    * @param identifier The name for the information.
    * @return The object which belongs to the identifier or 0 if the identifier
    *   does not exist.
    * @see addInfo
    */
    TLinkable* getInfoObject( const string& identifier ) const;
    /**
    * @return A list with "return" values, see @a fResults.
    */
    const TDataPackageList* getResults() const;

  protected:
    /**
    * This list contains the information added by the creator of the rule atom.
    */
    TDataPackageList* fInfo;
    /**
    * This list contains some pointers. The reason for this it that storing
    * pointers in a data package list is not possible and that storing links
    * is very slow.
    *
    * Details why storing links does not work: loading links is slow since
    * the ID of a link is stored and we therefore have to call
    * @ref TLinkUpdate::requestUpdate which is @e very slow (since it has
    * to search through a long list).
    */
    map<string,TLinkable*> fInfoObj;
    /**
    * A list of data packages. This list is used to "return" values
    * to the executer of a rule atom.
    */
    TDataPackageList* fResults;

    /**
    * Initializes member data values.
    */
    TRuleAtom();

    /**
    * Tests if a piece of information is part of the @a fInfo list.
    * @param identifier Name of a data package list to look for.
    */
    void validateInfo( const string& identifier ) const;

  private:
    #ifdef SECURE_MODE
      /**
      * A small check for detecting memory leaks.
      * @see TLeakChecker
      */
      static TLeakChecker lc;
    #endif // SECURE_MODE
};





#endif        // __RULEATOM_INCLUDED





