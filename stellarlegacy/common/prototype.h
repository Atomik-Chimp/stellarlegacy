// $Id: prototype.h,v 1.10 2002/07/12 10:05:35 mkrohn5 Exp $

// Prototype Header File
// Written by: Marco Krohn, <marco.krohn@gmx.de>

// Copyright (C) 2002 - , Marco Krohn, <marco.krohn@gmx.de>
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

#ifndef __PROTOTYPE_INCLUDED
#define __PROTOTYPE_INCLUDED

#include <map>
#include <string>
#include <typeinfo>

#include "common/defs.h"


using namespace std;





//----------------------------------------  TCanBePrototype  ----------------------------------------

class TCanBePrototype
{
  friend class TPrototypeManagerBase;

  public:
    /**
    * Not used at the moment.
    */
    virtual ~TCanBePrototype()
    {
      LOG("TCanBePrototype","~TCanBePrototype") << fPrototypeName << " deleted" << endl;
    }

    /**
    * @return A cloned object of the same type. This method is used to create
    *   clones from the prototypes in TPrototypeManager. The caller of this
    *   this method is responsible for deleting the created object.
    */
    virtual TCanBePrototype* clone() const = 0;
    /**
    * @return @c true if the two objects are of the same type,
    *   otherwise @c false.
    * @see getTypeID
    */
    bool compareType( const TCanBePrototype* obj ) const
    {
      return ( typeid(*this) == typeid(*obj) );
    }
    /**
    * Defines this object as prototype and sets a type name and ID.
    * Note calling this method once is obligatory for prototype objects.
    * @param name The name of this prototype. It is @e not a problem
    *   if you do not specify a name or if you use the same name for
    *   two different prototypes. The name is optional, the prototypes
    *   can be retrieved by assigning a key to the prototype
    *   (see TPrototypeManager).
    */
    void declareAsPrototype( const string& name )
    {
      fPrototypeName = name;
    }
    /**
    * @return The type name of the prototype.
    */
    const string& getPrototypeName() const
    {
      if ( fPrototype == 0 )  return fPrototypeName;
      return fPrototype->getPrototypeName();
    }
    /**
    * This method should only be used. It is only used by TPrototypeManager.
    */
    void setPrototypeName( const string& name )
    {
      fPrototypeName = name;
    }

  protected:
    /**
    * Making the constructor protected prevents making instances of this class.
    */
    TCanBePrototype()
    {
      fPrototype = 0;
    }

  private:
    /**
    * All objects (except the prototypes themselves) are created via @ref clone
    * from a prototype object. This pointer points to the prototype, or in case
    * the object itself is a prototype it is set to 0.
    */
    TCanBePrototype* fPrototype;
    /**
    * A name for the prototype (not neccessarily needed).
    */
    std::string fPrototypeName;
};





//----------------------------------------  TPrototypeManagerBase  ----------------------------------------

/**
* @class TPrototypeManagerBase
* @brief Common base for prototype managers.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: prototype.h,v 1.10 2002/07/12 10:05:35 mkrohn5 Exp $
* @see TPrototypeManager
*
* This class is a common layer between all TPrototypeManager 
* template classes. TCanBePrototype can not make all TPrototypeManager
* classes to a friend (because it is not clear which template classes exist),
* but TPrototypeManagerBase is a friend of TCanBePrototype and therfore
* allows doing modifications in TCanBePrototype. This base class is
* actually kind of a trick to make TPrototypeManger partially a friend
* class.
*/
class TPrototypeManagerBase
{
  protected:
    /**
    * Empty constructor.
    */
    TPrototypeManagerBase()
    {
    }

    /**
    * Changes the private variable @ref TCanBePrototype::fPrototype.
    * @param obj The object which will be modified.
    * @param proto The new value for @e fPrototype.
    */
    void changePrototype( TCanBePrototype* obj, TCanBePrototype* proto )
    {
      obj->fPrototype = proto;
    }
};





//----------------------------------------  TPrototypeManager  ----------------------------------------

/**
* FIXME
*
* In order to make debugging easier, you have to overload the output
* operator "<<" for the KEY.
*/
template<class KEY, class VALUE> class TPrototypeManager : public TPrototypeManagerBase
{
  public:
    /**
    * Calls reset.
    */
    ~TPrototypeManager()
    {
      reset();
    }

    /**
    * Example: returns @c true if the action is an TActionAddWaypoint,
    * otherwise @c false.
    * <pre>
    *   isType( action, "ADD_WAYPOINT" )
    * </pre>
    * @param obj Object number one.
    * @param key The key which is associated to a prototype.
    * @return @c true if the object and the "key" are of the same type (here: 
    *   key = prototype). Otherwise @c false.
    */
    bool isType( const TCanBePrototype* obj, const KEY& key ) const
    {
      TCanBePrototype* proto = find( key );
      if ( proto == 0 )  return false;
      return obj->compareType( proto );
    }
    /**
    * @param key The type of object to create (a key is associated with a prototype).
    * @return A clone from the prototype associated with the given key. The caller
    *   of this method is responsible for deleting the newly created object. If the
    *   key does not exist, the return value is 0.
    */
    VALUE* create( const KEY& key )
    {
      VALUE* proto = find( key );
      if ( proto == 0 )  {                                 // failed to create the prototype
        WLOG("TPrototypeManager","create") << "failed to create prototype: " << key << endl;
        return 0;
      }
      
      LOG("TPrototypeManager","create") << "creating object from prototype: "
        << proto->getPrototypeName() << endl;
      VALUE* obj = dynamic_cast<VALUE*>( proto->clone() );
      changePrototype( obj, proto );
      return obj;
    }
    /**
    * @param key The key to look for in the registry.
    * @return A pointer to the prototype or 0 if the key was not found.
    */
    VALUE* find( const KEY& key ) const
    {
      typename std::map<KEY,VALUE*>::const_iterator it = fPrototypes.find(key);
      if ( it == fPrototypes.end() )  {
        LOG("TPrototypeManager","find") << "info: key not found: " << key << endl;
        return 0;
      }
      return it->second;
    }
    /**
    * Note that this class is a template and therefore there might exist
    * different prototype manager classes.
    * @return The unique instance of TPrototypeManager<...>.
    */
    static TPrototypeManager<KEY,VALUE>& instance()
    {
      static TPrototypeManager<KEY,VALUE> theInstance;
      return theInstance;
    }
    /**
    * Registers a prototype in the prototype manager (registry).
    * Note that the prototype manager will care of deleting the object
    * after registration.
    * @param key is the key associated with the protoype.
    * @param prototype The prototype itself.
    * @return @c true if the registration was successful, otherwise @c false.
    */
    bool registerPrototype( KEY key, VALUE* prototype )
    {
      if ( prototype == 0 )  return false;

      LOG("TPrototypeManager", "registerPrototype")
        << "register new prototype: " << prototype->getPrototypeName() << endl;

      typename std::map<KEY,VALUE*>::iterator it = fPrototypes.find(key);
      if ( it != fPrototypes.end() )  {
        LOG("TPrototypeManager", "registerPrototype")
          << "another prototype with the same key does already exist => delete this element" << endl;
        delete it->second;
      }
      fPrototypes[key] = prototype;
      return true;
    }
    /**
    * Resets the prototype manager which means that the whole map and all
    * prototypes are cleared. You should know what you are doing!
    */
    void reset()
    {
      typename std::map<KEY,VALUE*>::iterator it;

      LOG("TPrototypeManager", "reset") << "reset called" << endl;

      for ( it=fPrototypes.begin(); it!=fPrototypes.end(); it++ )  {
        delete it->second;
      }
      fPrototypes.clear();
    }

  protected:
    /**
    * The constructor is protected to ensure that there is @e exactly one
    * instance of this class available.
    * @see instance
    */
    TPrototypeManager<KEY,VALUE>() : TPrototypeManagerBase()
    {
      LOG("TPrototypeManager","TPrototypeManager") << "prototype manager created" << endl;
    }

  private:
    /**
    * A map of all prototypes.
    */
    typename std::map<KEY,VALUE*> fPrototypes;
};





#endif        // __PROTOTYPE_INCLUDED
