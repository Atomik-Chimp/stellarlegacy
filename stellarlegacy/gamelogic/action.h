// $Id: action.h,v 1.29 2002/07/08 06:16:30 mkrohn5 Exp $

// Action Header File
// Written by: Alberto Barsella

// Copyright (C) 1999-2001, Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
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

#ifndef __TACTION_INCLUDED
#define __TACTION_INCLUDED

#include "common/datapackage.h"
#include "common/global.h"
#include "common/plist.h"
#include "common/prototype.h"
#include "gamelogic/property.h"

#include <string>
#include <vector>

using namespace std;

class TActionObject;
class TAction;
class TActionSequencer;
class TDataPackageList;





//----------------------------------------  abbreviation  ----------------------------------------

typedef TPrototypeManager<string,TAction> TPMAction;

#define PMAction TPMAction::instance()





//----------------------------------------  TAction  ----------------------------------------

/**
* @class TAction
* @brief Handles atomic "action" performed by objects in the game
* @author Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
* @version $Id: action.h,v 1.29 2002/07/08 06:16:30 mkrohn5 Exp $
*
* The three classes TAction, TActionObject and TActionSequencer are
* used to have the game objects perform "action" in the game world.
* 
* TAction is an abstract class which is to be used as base for deriving
* the specific actions which may take place in the universe.
*
* TActionObject is an abstract class which is to be used as a base
* for any game object which can be involved in an action (either because
* it performs or is affected by one).
*
* TActionSequencer is just a container for a list of action to be performed
* "simultaneously".  The aim of TActionSequencer is to make sure that the
* action are executed in a way as to avoid or resolve any possible conflict
* resulting from the execution of actions (example, two fleets loading
* "all minerals" from a limited resource).
*
* Actions are used for two main purposes:
* - transferring order from the client to the server, ensuring that
*   the sequence is preserved
* - executing the actions, i.e. altering the game universe state
*   in a way which guarantees consistency and attempts to resolve at
*   best any conflict which may occur.
*
* The entire action framework is useless for "independent" events which
* may occur.  For example, planetary population growth cannot in any way
* interfere across the planets.  As a consequence it's completely useless
* to generate all the "grow population" actions and execute them.  The
* growth can be simply performed on a per-planet basis with no risk of
* conflict.
*
* Actions are useful when:
* - executing in the server the actions performed by the players.
*   Since no player "has priority" on the others, it may happen that
*   two actions interfere with each other.
* - non-local events, like fleet movement which may involve multiple
*   objects at the same time (fleet #1 targeting fleet #2)
* - universe state modification actions, such as load/unload minerals.
*   Since these events affect the universe and every player (actually
*   every object) does not care about what all the rest of the universe
*   is doing (or just cannot know it), some protection is needed to maintain
*   consistency.
*/
class TAction : public TLinkable, public TCanBePrototype
{
  public:
    // destructor
    virtual ~TAction();

    /**
    * @return @c true if the action was already executed, otherwise @c false.
    * @see markAsExecuted
    */
    bool alreadyExecuted();
    /**
    * The action object now is allowed to execute an action.
    */
    virtual bool execute() = 0;
    /**
    * @return The actor of this action.
    */
    TActionObject* getActor() const;
    /**
    * FIXME
    */
    virtual bool load(TDataPackageList* in);
    /**
    * Marks an action as executed. This is actually only useful in the conflict
    * resolution process, if one wants to mark one or several actions as executed. The
    * action sequencer then deletes the action during the next run.
    */
    void markAsExecuted();
    /**
    * FIXME
    */
    virtual bool save(TDataPackageList* out) const;
    /**
    * Sets a actor for this action. Note that an existing actor can not
    * be changed--the method simply will ignore the parameter.
    * @param actor Sets the actor of this action.
    */
    void setActor( TActionObject* actor );
    /**
    * Sets a creator for this action. Note that an existing creator can not
    * be changed--the method simply will ignore the parameter.
    * @param creator Sets the creator of this action.
    */
    void setCreator( TRace* creator );
    /**
    * Adds an object which is involved in the action to the internal
    * list @a fObjects. For instance: a fleet A moves towards a fleet B.
    * The movement action of A sets the actor to A and the involved object
    * to B.
    * @param The object that is involved in the action.
    */
    void addInvolvedObject( TActionObject* involved );



    virtual bool checkActionConflicts();
    virtual bool resolveActionConflicts();

    virtual bool canUndo() const;

    TRace* getCreator() const;
    virtual bool validate();

    virtual bool isPlayerAction() const;

    // overloading of TType methods
    virtual int2 getType() const;
    virtual const string& getTypeName() const;
    const TPEList< TLink<TActionObject> >* getInvolvedObjects() const;


  protected:
    /**
    * Declaring this a protected makes it impossible to make TAction objects.
    * Initializes all variables.
    */
    TAction();

    TLink<TRace> fCreator;
    TDoubleLink<TActionObject> fActor;
    TPEList< TLink<TActionObject> > fInvolvedObjects;
    TPEList< TLink<TActionObject> > fObservers;

  // for all objects: ensure they exists and check they can be involved
  // and make sure the race who created the action owns the actor

  private:
    /**
    * @c true if the action was already executed, otherwise @c false.
    * This flag is needed in the action sequencer.
    */
    bool fExecuted;
    /**
    * Stores the information if the action object is valid or not.
    * The action object tries to validate itself whenever one tries
    * to call one of these methods: @ref execute, @ref checkActionConflicts
    * @ref resolveActionConflicts. The only reason for the existance of
    * this variable is making @ref validate work faster since the result is cached.
    *
    * @c FAILED = -1 = cache is empty<br>
    * @c false = 0 = action object not valid<br>
    * @c true = 1 = action object valid
    */
    int2 fValidated;
};


ostream& operator<<(ostream& os, const TAction& Act);



/**
* @class TActionObject
* @brief An object that can execute actions (TAction).
* @author Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
* @version $Id: action.h,v 1.29 2002/07/08 06:16:30 mkrohn5 Exp $
* @see TAction
*
* bla bla FIXME
*/
class TActionObject : public TProperty
{
    friend class TAction;

  public:
    TActionObject();
    virtual ~TActionObject();

    virtual bool canPerformAction(const TAction& action);
    virtual bool canBeObjectInAction(const TAction& action);
    virtual bool canObserveAction(const TAction& action);

    /**
    * Loads a TActionObject. Note that classes that are derived from
    * this class @e must call TActionObject::Load explicitly to load the data
    * correctly.
    * @param in The list of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a TActionObject by adding the data packages to the list. Note that
    * classes that are derived from this class @e must call TActionObject::Save
    * explicitly to save the data correctly.
    * @param out The output stream of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;

    // overloading of TType methods done by derived classes

  private:
};



/**
 * @class TActionSequencer
 * @brief FIXME
 * @author Alberto Barsella <Alberto.Barsella@univ-lille1.fr>
 * @version $Id: action.h,v 1.29 2002/07/08 06:16:30 mkrohn5 Exp $
 * @see TAction
 *
 * bla bla FIXME
 */
class TActionSequencer {
  public:
    TActionSequencer(const bool client);
    ~TActionSequencer();

    /**
    * @return @c true if the action sequencer is set to client mode,
    *   i.e. it executes actions immediately and store them, 
    *   otherwise (server mode) return @c false.
    */
    bool isInClientMode() const;
    void clear();
    bool addAction(TAction* action);
    bool runSequence();
    bool saveLists(ofstream& out) const;

  private:
    bool ClientMode;

    typedef map<TObjectID, TPList<TAction> > tActionTable;

    tActionTable ActionLists;
};


#endif        // __TACTION_INCLUDED
