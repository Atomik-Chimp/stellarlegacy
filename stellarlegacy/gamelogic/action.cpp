// $Id: action.cpp,v 1.40 2002/07/08 06:16:30 mkrohn5 Exp $

// Action Code File
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

#include "gamelogic/action.h"
#include "gamelogic/race.h"
#include "common/datapackage.h"





//----------------------------------------  TAction  ----------------------------------------

TAction::~TAction()
{
  // FIXME
  // before destroying action remove all reference to it
  // in global and object list 
  // (-> this is probably automatic with TLinkable?)

  // TO BE IMPLEMENTED!!!!!!!!!
}



TActionObject* TAction::getActor() const
{
  return fActor;
}



TRace* TAction::getCreator() const
{
  return fCreator;
}



void TAction::setActor( TActionObject* actor )
{
  if ( fActor.isNull() == true )  {
    fActor.setDest(actor);
    fValidated = FAILED;                                   // change occured => clear cache
  }
}



void TAction::setCreator( TRace* creator )
{
  if ( fCreator.isNull() == true )  {
    fCreator.setDest(creator);
    fValidated = FAILED;                                   // change occured => clear cache
  }
}



void TAction::addInvolvedObject( TActionObject* involved )
{
  fInvolvedObjects.push_back( new TLink<TActionObject>(involved) );
  fValidated = FAILED;                                     // change occured => clear cache
}



// virtual method
bool TAction::validate()
{
  if ( fValidated != FAILED )  return fValidated;          // cache o.k. => use cache value
  fValidated = false;                                     

  if (fActor.isNull())  {
    Fatal("TAction", "validate", "actor is null");
  }

  if (isPlayerAction() && fActor->getOwner() != (TRace*) fCreator) {
    Fatal("TAction", "validate", "action is player action but creator mismatches");
    return false;
  }

  if (!fActor->canPerformAction(*this))  {
    Fatal("TAction", "validate", "actor cannot perform this action");
  }

  list<TLink<TActionObject>*>::iterator i;

  for (i = fInvolvedObjects.begin(); i != fInvolvedObjects.end(); ++i)  {
    if ( (*i)->isNull() || !(**i)->canBeObjectInAction(*this) ) {
      Fatal("TAction", "validate", "object cannot be in this action");
      return false;
    }
  }

  for (i = fObservers.begin(); i != fObservers.end(); ++i)  {
    if ( (*i)->isNull() || !(**i)->canObserveAction(*this) ) {
      Fatal("TAction", "validate", "observer cannot be in this action");
      return false;
    }
  }

  fValidated = true;
  return true;
}



// virtual method
bool TAction::save(TDataPackageList* out) const
{
bool ret = true;
static const string sBlockType = "action";

  ret &= TLinkable::save( out );                           // call parent save method

  // additional information to write a block (this data will not be
  // read by the load method)
  ret &= out->add( "blocktype", &sBlockType );
  string* protoName = new string( getPrototypeName() );
  ret &= out->add( "subblocktype", protoName, true, true );     // autodelete=true

  ret &= fCreator.save( out, "creator_link" );
  ret &= fActor.save( out, "actor_link" );

  fInvolvedObjects.save( out, "objects", true );
  fObservers.save( out, "observers", true );

  return ret;
}



// virtual method
bool TAction::load(TDataPackageList* in)
{
  // load generic attributes for the action before we call
  // action's specialized LoadAttribs function
  bool bReturn = true;

  bReturn &= TLinkable::load( in );    // call parent Load method

  bReturn &= fCreator.load(in, "creator_link", true);
  bReturn &= fActor.load(in, "actor_link", true);

  // TODO: validate the creator: the race must be controlled by the
  // current active player of the game (how to check this here?)

  fInvolvedObjects.load( in, "objects", true );
  fObservers.load( in, "observers", true );

  fValidated = FAILED;

  return bReturn;
}



bool TAction::alreadyExecuted()
{
  return fExecuted;
}


void TAction::markAsExecuted()
{
  cout << "action marked as executed!" << endl;
  fExecuted = true;
}


/*
 * by default, no conflict
 */
bool TAction::checkActionConflicts()
{
  return false;
}



bool TAction::resolveActionConflicts()
{
  return true;
}



bool TAction::canUndo() const
{
  // by default, undo is possible if ANY object referenced by
  // the action is not implied in any action with a lower id
  // TO BE IMPLEMENTED

  return false;
}



bool TAction::isPlayerAction() const
{
  // by default actions are "player actions", i.e. they require the
  // creator (player) to be in control of the object performing the action
  return true;
}



const TPEList< TLink<TActionObject> >* TAction::getInvolvedObjects() const
{
  return &fInvolvedObjects;
}



/*
 * Overloading of TType methods to indicate an object of type "ACTION"
 */
int2 TAction::getType() const
{
  return TType::ACTION;
}



const string& TAction::getTypeName() const
{
static const string sTypeName = "TAction";

  return sTypeName;
}





//----------------------------------------  protected  ----------------------------------------

TAction::TAction()
{
  LOG("TAction","TAction") << "TAction created" << endl;

  fActor.setNull();
  fActor.setInverse( this );
  fCreator = 0;
  fValidated = FAILED;
  fExecuted = false;

  fInvolvedObjects.setAutoDeleteMode( true );
  fObservers.setAutoDeleteMode( true );
}







//----------------------------------------  TActionObject  ----------------------------------------


/*
 * TActionObject member functions
 */
TActionObject::TActionObject() : TProperty()
{
  LOG("TActionObject","TActionObject") << "action object created." << endl;
  // nothing to do
}



TActionObject::~TActionObject()
{
  // remove object from all actions referring to it

  // TO BE IMPLEMENTED
}



/*
 * by default, they all return false.  It's up to the derived class(es)
 * to "filter in" the acceptable actions
 */
bool TActionObject::canPerformAction(const TAction&)
{
  return false;
}



bool TActionObject::canBeObjectInAction(const TAction&)
{
  return false;
}



bool TActionObject::canObserveAction(const TAction&)
{
  return false;
}




// virtual method
bool TActionObject::load( TDataPackageList* in )
{
  TProperty::load( in );            // first of all load the parents data
  // now load own data

  return true;
}



// virtual method
bool TActionObject::save( TDataPackageList* out ) const
{
  TProperty::save( out );           // first of all save the parents data
  // now save own data

  return true;
}



/*
 * TActionSequencer member functions
 */
TActionSequencer::TActionSequencer(const bool client) :
     ClientMode(client)
{
}



TActionSequencer::~TActionSequencer()
{
  // all actions will be nicely deleted when we kill the map<>
}



bool TActionSequencer::isInClientMode() const
{
  return ClientMode;
}



void TActionSequencer::clear()
{
  // delete all actions in the lists
  ActionLists.clear();
}



bool TActionSequencer::addAction(TAction* action)
{
  // add the action to the appropriate list
  // (by using the ID of the race who created it)
  ActionLists[action->getCreator()->getID()].push_back(action);

  // this will be repeated too much, but who cares?
  ActionLists[action->getCreator()->getID()].setAutoDeleteMode(true);

  // if we are in client mode, after recording the action we should
  // execute it  to provide immediate feedback 
  // (we don't really care if the right race created the
  // action, if a player messes up, the server will catch it)
  if (ClientMode)
    return action->execute();

  return true;
}



/*
 * runSequence is meaningful only in non-client mode
 * When reloading a pre-existing order file in the client, the
 * action are recorded with addAction, which will execute them
 * immediately (no conflict can occur in that case)
 */
bool TActionSequencer::runSequence()
{
  if (ClientMode)
    return false;

  tActionTable::iterator mi;
  bool actions_remaining;
  int4 executed_actions, resolved_conflicts;

  // loop until all actions have been executed
  actions_remaining = true;

  while ( actions_remaining ) {
    LOG("TActionSequencer", "runSequence") << "Begin execution loop" << endl;

    actions_remaining = false;
    executed_actions = 0;

    // scan every list in ActionList, and try to execute all actions from
    // that list, stopping only if a conflict is found
    for (mi = ActionLists.begin(); mi != ActionLists.end(); ++mi) {

      // any action left in this list?
      while (mi->second.size()) {
        // yes, try to execute the head of the list
        TAction* act = mi->second.front();

        if (act->alreadyExecuted()) {
          // action has already been executed!
          LOG("TActionSequencer", "runSequence")
            << "Purging already executed action: "
            << act->getPrototypeName() << " " << act->getID() << endl;

          delete act;
          mi->second.pop_front();
                       
        }
        else {
          // action has not been executed yet, try to execute it
          LOG("TActionSequencer", "runSequence")
            << "Attempting execution of action: "
            << act->getPrototypeName() << " " << act->getID() << endl;

          if ( act->checkActionConflicts() ) {
            // conflicts were found, postpone resolution as much as possible
            LOG("TActionSequencer", "runSequence") << "...conflict found, postponing" << endl;
            actions_remaining = true;
            // leave the internal (while size != 0) loop
            break;

          }
          else {
            LOG("TActionSequencer", "runSequence") << "executing action..." << endl;
            if ( act->execute() ) {
              // execution successful, delete the action
              executed_actions++;
              delete act;
              mi->second.pop_front();

            }
            else {
              // this is fatal
              Fatal("TActionSequencer", "runSequence","internal error (fail exec)");
            }
          }
        }
      }
    }

    LOG("TActionSequencer", "runSequence") << "executed " << executed_actions << " actions" << endl;
    if ( actions_remaining == true )  {
      LOG("TActionSequencer", "runSequence") << "there are remaining actions" << endl;
    }

    // one loop was completed.  Check for troubles
    if (actions_remaining && executed_actions == 0) {
      // not everything was executed, a conflict must be blocking execution
      // try resolution on all available actions
      resolved_conflicts = 0;

      for (mi = ActionLists.begin(); mi != ActionLists.end(); ++mi) {
        // any actions left in this list?
        if (mi->second.size()) {
          // ok, we are NOT at the end of this list
          TAction* act = mi->second.front();

          LOG("TActionSequencer", "runSequence") << "force conflict resolution..." << endl;
          if ( act->resolveActionConflicts() )  {
            resolved_conflicts++;
            break;  // let's try to advance after a single conflict resolution
          }
        }
      }

      if (resolved_conflicts == 0) {
        Fatal("TActionSequencer", "runSequence", "internal error (unresolvable conflict)");
      }
    }
  }

  return true;
}



bool TActionSequencer::saveLists(ofstream& out) const
{
  bool bReturn = true;
  TPList<TAction>::const_iterator ai;
  tActionTable::const_iterator mi;
  TDataPackageList DataGroup;

  // iterate on all list
  for (mi = ActionLists.begin(); mi != ActionLists.end(); ++mi) {
    for (ai = mi->second.begin(); ai != mi->second.end(); ++ai) {
      (*ai)->save( &DataGroup );
      bReturn &= DataGroup.save( out );
      out << endl;
      DataGroup.DeleteAll();
    }
  }

  return bReturn;
}



/*
 * $Log: action.cpp,v $
 * Revision 1.40  2002/07/08 06:16:30  mkrohn5
 * fActor is now a TDoubleLink
 *
 * Revision 1.39  2002/07/02 23:15:52  mkrohn5
 * added method "getActor"
 *
 * Revision 1.38  2002/07/01 20:56:21  mkrohn5
 * - added docu
 * - bug fix (fValidated was never set to true)
 * - added a method to access fInvolvedObjects
 *
 * Revision 1.37  2002/07/01 00:05:56  mkrohn5
 * prototype pattern used in action.cpp/.h
 *
 * Revision 1.36  2002/06/28 10:12:07  mkrohn5
 * - Add -> add (TDataPackageList)
 * - readded validated cache flag in TAction
 *
 * Revision 1.35  2002/06/26 19:16:07  ishark
 * more work on act-to-cpp and fleetactions
 *
 * Revision 1.34  2002/06/25 23:07:54  mkrohn5
 * changes to make it compile again
 *
 * Revision 1.33  2002/06/24 23:42:56  mkrohn5
 * removed unneccessary variable, two methods, one variable renamed
 *
 * Revision 1.32  2002/06/24 19:58:32  ishark
 * modified TActionSequencer::runSequence
 *
 * Revision 1.31  2002/06/23 15:50:48  ishark
 * added act-to-cpp tool, fixes in TActionSequencer, gcc3 fixes
 *
 * Revision 1.30  2002/06/23 11:59:37  mkrohn5
 * work on action conflict + bugfix
 *
 * Revision 1.29  2002/06/23 10:59:45  mkrohn5
 * - made fObjects, fObservers in action a TPEList which fixes a  memory leak and makes loading/saving easier.
 * - added method in action to add "involved" action objects
 *
 * Revision 1.28  2002/06/04 09:21:18  mkrohn5
 * cosmetic changes
 *
 * Revision 1.27  2002/05/15 08:30:55  ishark
 * actionsequencer now uses lists + cosmetic fixes
 *
 * Revision 1.26  2002/05/13 23:00:02  mkrohn5
 * constructor now calls initialize
 *
 * Revision 1.25  2002/05/10 10:39:49  mkrohn5
 * all kind of changes (my cvs frontend is f#%$§ up so I can not see a detailed list of changes). Have a look at the ChangeLog file to see the changes.
 *
 * Revision 1.24  2002/04/25 23:19:55  prolator
 * removed line break in string
 *
 * Revision 1.23  2002/04/01 21:43:35  mkrohn5
 * bugfix which prevented a call to saveAttributes
 *
 * Revision 1.22  2002/04/01 19:12:05  mkrohn5
 * - added & corrected macros
 * - two new methods
 * - style fixes
 *
 * Revision 1.21  2002/03/24 18:02:38  mkrohn5
 * uppercase -> lowercase fixes
 *
 * Revision 1.20  2002/03/24 13:36:35  mkrohn5
 * mostly style changes
 *
 * Revision 1.19  2001/12/16 11:37:24  ishark
 * TLink now uses dynamic_cast<>, lots of TAction-related fixes
 *
 * Revision 1.18  2001/12/03 01:34:40  mkrohn5
 * minor fixes due to new method style
 *
 * Revision 1.17  2001/12/02 14:21:59  mkrohn5
 * changed Load -> load, Save -> save,
 * puuh, more work than expected :-(
 *
 * Revision 1.16  2001/11/08 21:13:54  ishark
 * action uses new method names, additions in sl/race/game
 *
 * Revision 1.15  2001/08/07 20:50:27  mkrohn5
 * added a log message which was needed for debugging
 *
 * Revision 1.14  2001/07/31 00:26:09  mkrohn5
 * TActionObject is now derived from TProperty
 *
 * Revision 1.13  2001/07/28 15:23:11  ishark
 * added filters in stolist, more client code in sl.cpp
 *
 * Revision 1.12  2001/07/10 17:57:32  ishark
 * rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
 *
 * Revision 1.11  2001/07/05 20:34:18  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.10  2001/06/21 11:27:50  mkrohn5
 * added debug output
 *
 * Revision 1.9  2001/06/19 21:06:32  ishark
 * some modifications in action (& parser) code
 *
 * Revision 1.8  2001/06/13 00:12:39  mkrohn5
 * added load and save methods
 *
 * Revision 1.7  2001/05/10 23:04:41  mkrohn5
 * corrected parameters for Fatal calls
 *
 * Revision 1.6  2001/04/29 21:38:37  ishark
 * TAction updated to use TDataPackage/Load
 *
 * Revision 1.5  2001/04/27 01:18:38  mkrohn5
 * added "const" to a string
 *
 * Revision 1.4  2001/04/26 00:05:06  mkrohn5
 * changes a return value from "string" to "const string&"
 *
 * Revision 1.3  2001/04/18 20:56:52  ishark
 * minor changes in TAction, added meat in TActionSequencer
 *
 * Revision 1.2  2001/04/17 18:58:21  mkrohn5
 * fixed compiling errors--Alberto please have a look at the FIXME if the code is correct
 *
 * Revision 1.1  2001/04/13 21:56:54  ishark
 * fixed osval/substance tests, added preliminary version of action
 *
 */
