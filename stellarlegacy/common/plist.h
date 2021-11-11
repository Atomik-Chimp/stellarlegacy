// $Id: plist.h,v 1.16 2002/07/08 06:17:05 mkrohn5 Exp $

// Pointer List Header File
// Written by: Marco Krohn <marco.krohn@gmx.de>

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

#ifndef __PLIST_INCLUDED
#define __PLIST_INCLUDED

#include <algorithm>
#include <list>
#include <string>

using namespace std;

#include "common/datapackage.h"





//----------------------------------------  class TPList  ----------------------------------------

/**
* @class TPList
* @brief An improved list for pointers only.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: plist.h,v 1.16 2002/07/08 06:17:05 mkrohn5 Exp $
* @see TPEList
*
* This template class makes handling a list of pointers a bit easier since
* the autodelete (see @ref #setAutoDeleteMode) feature is added.
* If you also need load and save methods have a look at the extended version
* TPEList.
*
* Example:
*
* <pre>
* TPList<TSubFleet> fSubFleets;
* fSubFleets.setAutoDeleteMode( true );
*
* subFleet = new TSubFleet(...);
* fSubFleets.push_back( subFleet );
* fSubFleets.push_back( new TSubFleet(...) );
* fSubFleets.remove( subFleet );        // <= also deltes the subFleet itself!
* </pre>
*
* So usage is similar to a list. Note though the remove command
* and that a destructor call of TPList<...> also deletes all objects
* if the "auto delete mode" is set to true.
*/
template<class X> class TPList : public list<X*>
{
  public:
    // types:
    typedef typename list<X*>::iterator iterator;
    typedef typename list<X*>::const_iterator const_iterator;

    /**
    * The constructor initializes the auto delete variable (@ref #SetAutoDeleteMode).
    * @param autoDelete The new settings for the @a fAutoDelete variable.
    */
    TPList<X>( bool autoDelete=false ) : list<X*>()
    {
      setAutoDeleteMode( autoDelete );
    }
    TPList<X>( const TPList<X>& src ) : list<X*>( src )
    {
      *this = src;
    }
    /**
    * The destructor calls @ref deleteAll to clean up everything.
    */
    virtual ~TPList()
    {
      deleteAll();
    }

    /**
    * Adds a object to the list. Note this method is doing the same
    * as the list method "push_back". There is no check which prevents adding
    * the same object twice.
    * @param pObj The new object.
    */
    void add( X* obj )
    {
      push_back( obj );
    }
    /**
    * Deletes all elements from the list.
    * @see fAutoDelete
    */
    void deleteAll()
    {
      // If you are confused by the meaning of "typename" read
      // C.13.5 "Typename and Template" in
      // "The C++ Programming Language", Bjarne Stroustrup
      // (this is in the gcc world only needed if you use -pedantic switch)
      iterator it;

      if ( fAutoDelete == true )  {
        for ( it=begin(); it!=end(); it++ )  delete *it;   // deletes all objects
      }
      clear();                                             // deletes the whole list
    }
    /**
    * @return The first iterator @c i in the list, such that <tt>*i == pObj</tt>.
    *   It returns @c end() if no such object exist.
    */
    iterator find( X* obj )
    {
      return std::find( list<X*>::begin(), list<X*>::end(), obj );
    }
    /**
    * @return The first element in the list or 0 if the list is empty.
    */
    X* getFirst() const
    {
      if ( empty() == true )  return 0;
      return *(begin());
    }
    /**
    * Returns the iterator for the @e n-th element.
    * Note: this operation is slow O(@e n).
    * @param n The @e n-th element of the list (@e n=0 means the first element).
    * @return The @e n-th element of the list. If @e n is greater than the list
    *   size the return value is end() (especially if the list is empty).
    */
    iterator goTo( int4 n )
    {
      int4 i;
      iterator it, last;

      it = begin();
      last = end();

      for ( i=0; i<n; i++ )  {
        if ( it == end() )  return end();
        it++;
      }

      return it;
    }
    /**
    * Just another name for the STL list method "empty".
    */
    bool isEmpty() const
    {
      return empty();
    }
    /**
    * The operator= copies the pointer list, but not the variable
    * @a fAutoDelete. @e fAutoDelete is not copied, but set to @c false,
    * to prevent that objects are deleted twice.
    * @param The source list.
    * @return The modified object.
    */
    TPList<X>& operator=( const TPList& Src )
    {
      if ( this == &Src )  return *this;                   // src and dest are the same

      deleteAll();
      // the list is now empty
      // call base-class version of operator=() => base-class assignment
      list<X*>::operator=( Src );
      // regardless of the settings of Src: set the auto delete variable to
      // false, otherwise the object will be deleted twice
      setAutoDeleteMode( false );

      return *this;
    }
    /**
    * Removes an object from the list. Note that this method is the same as
    * @c erase, if and only if @a fAutoDelete is set to @c false. If
    * @a fAutoDelete is @c true, than the object is also deleted.
    * @param obj is the object to remove (and perhaps also delete).
    * @return @c true if the object was removed from the list successfuly,
    *   otherwise @c false.
    */
    bool remove( X* obj )
    {
      iterator it = find( obj );
      return remove( it );
    }
    /**
    * Removes an object from the list. Note that this method is the same as
    * @c erase, if and only if @a fAutoDelete is set to @c false. If
    * @a fAutoDelete is @c true, than the object is also deleted.
    * @param it the object to remove (and perhaps also delete).
    * @return @c true if the object was removed from the list successfuly,
    *   otherwise @c false.
    */
    bool remove( iterator it )
    {
      if ( it == end() )  return false;                    // no such object
      if ( fAutoDelete == true )  delete *it;              // delete the object
      erase( it );                                         // remove the object

      return true;                            // object removed --> return true
    }
    /**
    * Removes the first object from the list. Depending on the setting of
    * @c fAutoDelete the object itself is also deleted.
    * @return @c true if the object was removed from the list successfuly,
    *   otherwise @c false.
    */
    bool removeFirst()
    {
      if ( empty() == true )  return false;
      return remove( begin() );
    }
    /**
    * Sets the auto delete mode (see @a fAutoDelete for details).
    * @param autoDelete The new settings for the @a fAutoDelete variable.
    */
    void setAutoDeleteMode( bool autoDelete )
    {
      fAutoDelete = autoDelete;
    }

  protected:
    /**
    * If set to @c true not only the list is deleted, but also all elements.
    * @c false on the other hand will delete the list only without taking care
    * of the objects.
    */
    bool fAutoDelete;
};





//----------------------------------------  class TPEList  ----------------------------------------

/**
* @class TPEList
* @brief Extented version (load + save) of TPList.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: plist.h,v 1.16 2002/07/08 06:17:05 mkrohn5 Exp $
* @see TPEList
*
* This is an extended version of the TPList in the sense that it
* also handles datapackages correctly and therefore allows
* loading and saving objects which provide the neccessary methods.
*
* FIXME: example
*/
template<class X> class TPEList : public TPList<X>
{
  public:
    /**
    * Loads the list of objects from a list of data packages.
    * Note that also the @a fAutoDelete flag will be restored.
    * @param in The input stream of data packages.
                * @param identifier The identifier to look for.
    * @param unique Loads the data only if the identifier is unique.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    bool load( TDataPackageList* in, const string& identifier,
               bool unique=true )
    {
      bool ret = true;
      X* pNew;
      TDataPackageList* pList = new TDataPackageList();

      // read the object => sub list
      ret &= in->getAndDelete( identifier, pList, unique );

      // read the real data from the sub list
      ret &= pList->getAndDelete( "autodelete", &fAutoDelete, true );
      pList->showContent();

      while( pList->Search("listitem") != 0 )
      {
        pNew = new X;
        // this assumes that load(...) will load the first
        // element in the list "pList". Otherwise the order
        // of elements is not conserved.
        ret &= pNew->load( pList, "listitem", false );
        // adds (push_back) the element to the list
        add( pNew );
      }
      delete pList;                                        // clean up

      return ret;
    }
    /**
    * Creates the data packages for this list of objects and adds them to
    * the data package list.
    * @param out The list of data packages.
    * @param identifier The identifier which is used to store and find the data.
    * @param unique If set to @c true the method will check if the identifier was
    *   already used in the data package list.
    * @return @c true if everything worked fine, otherwise @c false (e.g. if
    *   the identifier was already used in the data package list).
    */
    virtual bool save( TDataPackageList* out, const string& identifier,
               bool unique=true ) const
    {
      bool ret = true;
      typename list<X*>::const_iterator it;

      TDataPackageList* pList = new TDataPackageList();    // create a new datapackage list
      // autoDelete=true so that pList is deleted sometime
      ret &= out->add( identifier, pList, unique, true );

      // add the data packages to the new list
      ret &= pList->add( "autodelete", &fAutoDelete, true, false );

      for ( it=begin(); it!=end(); it++ )
      {
        // note: the "listitem" identifier is not unique
        ret &= (*it)->save( pList, "listitem", false );
      }
      return ret;
    }
};





#endif        // PLIST_INCLUDED
