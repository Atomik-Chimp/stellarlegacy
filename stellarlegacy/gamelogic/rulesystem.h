// $Id: rulesystem.h,v 1.1 2002/07/12 10:10:35 mkrohn5 Exp $

// Rule System Header File
// Written by: Marco Krohn

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

#ifndef __RULESYSTEM_INCLUDED
#define __RULESYSTEM_INCLUDED

#include "common/defs.h"

#include <list>
#include <map>
#include <string>

using namespace std;

class TDataPackageList;
class TFleet;
class TGalaxy;
class TItem;
class TRace;
class TRuleAtom;
class TSystem;





//----------------------------------------  class TRuleSystem  ----------------------------------------

/**
* @class TRuleSystem
* @brief Stores information about the game rules.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: rulesystem.h,v 1.1 2002/07/12 10:10:35 mkrohn5 Exp $
*
* FIXME
*
* what are rules, modules?
*
* Singelton, reset => set rules, modules => check dependencies
* => you can ask for rules etc.
*/
class TRuleSystem
{
  public:
    /**
    * A structure to save an dependency error. A dependency is
    * always of the type that a rule atom requires a module. If
    * the module does not exist, the checkDependency method
    * stores this information in tError. The description of TRuleAtom
    * contains more information about dependencies.
    * If one entry is empty (that means rule=="" or module==-1)
    * this means that there is a missing module or rule atom.
    * Examples:
    *
    * <ol>
    *   <li>rule="", module=TRuleSystem::FLEET: the module "fleet"
    *     has no reasonable value.</li>
    *   <li>rule="fleet_movement", module=TRuleSystem::NONE: the rule atom
    *     "fleet_movement" has no reasonable value.</li>
    *   <li>rule="item_access", module=TRuleSystem::RACE: the used implementation
    *     for the rule "item_access" is not satisfied with the module "race". You have
    *     to use a different rule system for that module, but note: there is no hint
    *     which rule system for the module is compatible with the rule atom.</li>
    * </ol>
    */
    typedef struct tError
    {
      tError() { rule=""; module=""; };
      tError( const tError& err ) { set( err.rule, err.module ); };
      tError( const string& r, const string& m )  { set( r, m ); };
      void set( const string& r, const string& m )  { rule=r; module=m; };
      /** The rule that needs a certain module. */
      string rule;
      /** a module, e.g. "fleet" */
      string module;
    };

    /**
    * Call this method to find out if all rule atoms and modules play nicely
    * together or not and to find out if all neccessary information was provided.
    * (Some rule atoms might need special modules to work properly). This
    * check was introduced to make mixing different rule systems possible
    * without crashing the game. A successful check of the dependencies sets
    * @a fVerified to @c true.
    * @return The new value of @a fVerified.
    * @see getErrors
    */
    bool checkDependencies();
    /**
    * Creates an empty fleet depending on the game rules
    * (e.g. TFleetBasic, TFleetSL, TFleetStars).
    * Note: The fleet is @e not added to the galaxy (see @ref TGalaxy::Add).
    * Also note that the @e caller is in charge of deallocation!
    * @return A new fleet or 0 if an error occured.
    * @see TFleet
    */
    TFleet* createFleet() const;
    /**
    * Creates an item depending on the @e itemtype.
    * Possible item types are described in TItem.
    * Note that the @e caller is in charge of deallocation!
    * @param itemtype The type of the item (see TItem::tItemType for details)
    * @return A new item or 0 if an error occured.
    * @see TItem
    */
    TItem* createItem( int2 type ) const;
    /**
    * Creates an empty race depending on the game rules
    * (e.g. TRaceBasic, TRaceSL, TRaceStars).
    * Note that the @e caller is in charge of deallocation!
    * @return A new race or 0 if an error occured.
    * @see TRace
    */
    TRace* createRace() const;
    /**
    * Creates an empty system depending on the game rules
    * (e.g. TSystemBasic, TSystemSL, TSystemStars).
    * Note: The system is @e not added to the galaxy (see @ref TGalaxy::Add).
    * Also note that the @e caller is in charge of deallocation!
    * @return A new system or 0 if an error occured.
    * @see TSystem
    */
    TSystem* createSystem() const;
    /**
    * Looks up a specific rule (please see TRuleAtom for more
    * information and example code).
    * @param ruleName The name of the rule e.g. "fleet movement".
    * @return Either the searched rule or 0 if the rule atom does not exist.
    *   Note that the @e caller is in charge of deallocation!
    * @see TRuleAtom
    */
    TRuleAtom* getRuleAtom( const string& ruleName ) const;
    /**
    * @return The list of errors created by the last @ref checkDependencies call.
    */
    const list<TRuleSystem::tError>* getErrorList() const;
    /**
    * @param module The name of the module e.g. "system", "fleet", ...
    * @return The used rules for that module, or there is nothing defined yet.
    * @see setModule
    */
    string getModule( const string& module ) const;
    /**
    * @return the value of @a fVerified.
    */
    bool getStatus() const;
    /**
    * @return The unique instance of TRuleSystem.
    */
    static TRuleSystem& instance();
    /**
    * Loads a TRuleSystem object. Note that you have to call checkDependencies
    * after loading on your own and also note that this method triggers a call
    * to the @ref reset method.
    * @param in The list of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    bool load( TDataPackageList* in );
    /**
    * Sets the modules and the rule atoms to the default value: NONE.
    * Especially this means that @a fVerified is set to @c false and therefore
    * you have to call @ref checkDependencies in order to get any rules.
    * You should know what you are doing! Use with care!
    */
    void reset();
    /**
    * Saves a TRuleSystem object by adding the data packages to the list.
    * @param out The output stream of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    bool save( TDataPackageList* out ) const;
    /**
    * Sets the used rule set for a module.
    * Note that no dependency check is done (see @ref checkDependencies)
    * and also note that you have to check dependencies again after
    * calling this method.
    * @param module The module e.g. "fleet", "race", ...
    * @param rule The used rule set for that module e.g. "basic", "stars", ...
    * @return @c true means the change was accepted, otherwise @c false.
    */
    bool setModule( const string& module, const string& rule );
    /**
    * Sets the used rule set for a rule atom.
    * Note that no dependency check is done (see @ref checkDependencies)
    * and also note that you have to check dependencies again after
    * calling this method.
    * @param rule The rule atom (e.g. "fleet movement").
    * @param ruleset The used rule set for that rule set e.g. "basic", "stars", ...
    * @return @c true means the change was accepted, otherwise @c false.
    */
    bool setRuleAtom( const string& rule, const string& ruleset );

  protected:
    /**
    * Calls calls @ref reset.
    *
    * Note: The constructor is protected to ensure that there is @e exactly one
    * instance of this class available.
    * @see instance
    */
    TRuleSystem();

  private:
    /** List of errors from the last check dependencies call */
    list<tError> fErrorList;
    /** Stores which version of a module (e.g. fleet, race, etc.) is used */
    map<string, string> fModules;
    /** Stores which rule system for the rule atoms are used in this game */
    map<string, string> fRules;
    /**
    * Stores the information if all rule atoms / modules play nicely together or not.
    * @c true means everything is o.k., while @c false means that it either wasn't
    * checked, or that there is some conflict in the rule system.
    * @see checkDependencies
    */
    bool fVerified;
};





#endif        // __RULESYSTEM_INCLUDED
