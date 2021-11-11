// $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $

// Link Header File
// Written by: Pier Donini <>,
//             Marco Krohn <marco.krohn@gmx.de>

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

#ifndef __LINK_INCLUDED
#define __LINK_INCLUDED

#include <deque>
#include <fstream>
#include <list>
#include <map>
#include <string>

#include "common/defs.h"
#include "common/global.h"

using namespace std;

class TDataPackageList;
class TObjectID;
class TLinkBase;
class TLinkable;
class TLinkUpdate;





//----------------------------------------  Misc. Functions  ----------------------------------------

/**
* Stream function for TObjectID, allowing cout << objid.
* The output looks like: [0f,00,00,00,00,00] or temp[01,04,00,00,00,00].
* Actually this function calls @ref TObjectID#write.
* @param Stream The current ostream for output.
* @param ObjectID This one will be written to the output stream.
* @return The old stream + object ID.
* @see TObjectID#Write
*/
ostream& operator<<( ostream& Stream, const TObjectID& ObjectID );

/**
* Stream function for TLinkBase, allowing constructions like: cout << link.
* The output looks like: [0f,00,00,00,00,00] or temp[01,04,00,00,00,00].
* Actually this function calls the Write methode of TLink.
* @param Stream The current ostream for output.
* @param Link This one will be written to the output stream.
* @return The old stream + link.
*/
ostream& operator<<( ostream& Stream, const TLinkBase& Link );





//----------------------------------------  class TObjectID  ----------------------------------------

/**
* @class TObjectID
* @brief A class for storing an object ID.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkable
*
* This class is just a wrapper class for a byte array. The
* array size is determined by the constant ID_LENGTH.
* This gives (at the moment 6 bytes) about 2.8 * 10^14 different object
* ID's which should be enough for all purposes. Standard methods
* like equal operator, comparison operators etc. are implemented.
*
* In addition to the 6 byte array TObjectID stores a flag
* which shows if the ID is a real one or just temp.
* (temp in the sense that this ID is at once transformed to a real
* ID on the server side. Therefore temp IDs exist on the client-side only)
* This is useful on the client side, since the objects
* generated there (e.g. split fleet) need new ID numbers
* which are not unique. Note: temp IDs do only exist on the client
* side, never on the server side. The necessary transformation
* of the IDs is part of TLinkUpdate.
*
* TObjectID is mainly used in TLinkable to give all linkable
* objects their own and unique ID.
*/
class TObjectID
{
  friend class TLinkUpdate;

  public:
    /** The number of bytes used for one ID */
    static const int ID_SIZE = 6;

    /**
    * The constructor sets @a bTemp = @c false and calls @ref setNull to
    * initialize the array with 0.
    */
    TObjectID();
    /**
    * Copy constructor to allow calls like: @e TObjectID @e One = @e Two;
    * @param Object The new ID for this object.
    */
    TObjectID( const TObjectID& Object );
    /**
    * Initialization of the object ID with a byte array.
    * @a bTemp is set to @c false.
    * @param ByteArray An array of @c bytes. The array should have at least
    *   the same size as the TObjectID, that means TObjectID::GetSize()
    *   elements.
    * @param bTemp The value for the temp flag (default @c false).
    * @see SetID, GetSize
    */
    TObjectID( const byte* ByteArray, bool bTemp=false );
    /**
    * Constructor for initializing the object with an integer array.
    * It is assumed that the integers are between 0 and 255 otherwise the method
    * sends a warning message to the log file.
    * @param IntArray An array of integers. The array should have at least
    *   the same size as the TObjectID, that means TObjectID::GetSize()
    *   elements.
    * @param bTemp The value for the temp flag (default @c false).
    * @see SetID, GetSize
    */
    TObjectID( const int* IntArray, bool bTemp=false );

    /**
    * @return @c true if the ID is null, otherwise @c false.
    *   (Note: the result does not depend on the setting of the
    *   variable @a bTemp.)
    */
    bool isNull() const;
    /**
    * @return @c true if the ID is temp, otherwise @c false.
    */
    bool isTemp() const;
    /**
    * @return The number of bytes used for storing the ID.
    *   (Note: the result is @e not equal to @c sizeof(TObjectID).)
    */
    static int getIDSize();
    /**
    * Loads a TObjectID object from a list of data packages.
    * Note that a successful load will delete the datapackage from the data
    * package list as well as the datapackage itself.
    * @param in The input stream of data packages.
    * @param sIdentifier The identifier to look for.
    * @param bUnique Loads the data only if the identifier is unique.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /**
    * The standard equal operator simply copies the byte array and the @e bTemp flag.
    * @param object The source object.
    * @return A reference to the dest object.
    */
    TObjectID& operator=( const TObjectID& Object );
    /**
    * The (prefix) incrementation operator increases the
    * ID by 1.
    * @return The new ID.
    */
    TObjectID operator++();                                // prefix increment operator
    /**
    * The (postfix) incrementation operator increases the
    * ID by 1.
    * @param Is not used but is necessary to differ between
    *   the postfix and the prefix version (the prefix version has no
    *   int parameter).
    * @return The old ID.
    */
    TObjectID operator++( int );                           // postfix increment operator
    /**
    * Compares two IDs to find out if they are equal. Note that two IDs are
    * never identical if their temp flag differs.
    * @param Object The ID to compare with.
    * @return @c true if the two IDs are the same (including the temp flag).
    * @see operator!=
    */
    bool operator==( const TObjectID& Object ) const;
    /**
    * Compares two IDs to find out if they are different.
    * @param Object The ID to compare with.
    * @return @c true if the two IDs are the different.
    * @see operator==
    */
    bool operator!=( const TObjectID& Object ) const;
    /**
    * Compares two IDs to find out which of them is smaller. Note: a temp ID
    * is always smaller than a real ID.
    * @param Object The ID to compare with.
    * @return @c true if the ID of @e Object is greater then the other
    *   ID, otherwise the method returns @c false.
    */
    bool operator<( const TObjectID& Object ) const;
    /**
    * Creates the data package for a TObjectID object and adds it to
    * the data package list.
    * Note: Do @e not modify the auto delete setting of the data package!
    * @param out The list of data packages.
    * @param sIdentifier The identifier which is used to store and find the data.
    * @param bUnique If set to @c true the method will check if the identifier was
    *   already used in the data package list.
    * @param bAutoDelete Setting this flag to @c true means that _this_ object
    *   will automatically be deleted by the TDataPackageList. Use with care!
    * @return @c true if everything worked fine, otherwise @c false (e.g. if
    *   the identifier was already used in the data package list).
    */
    bool save( TDataPackageList* out, const string& sIdentifier,
               bool bUnique=true, bool bAutoDelete=false ) const;
    /**
    * Reads an array of bytes to initalize the object.
    * @param ByteArray An array of bytes which should have a size equal or greater than
    *   @ref getIDSize.
    * @param bTemp The value for the temp flag.
    */
    void setID( const byte* ByteArray, bool bTemp=false );
    /**
    * Reads an array of integers to initalize the object.
    * Since integers have a different range, values >255 are treated as 255,
    * values <0 are treated as 0.
    * @param ByteArray An array of integers which should have a size (number of entries)
    *   equal or greater than @ref getIDSize.
    * @param bTemp The value for the temp flag.
    */
    void setID( const int* IntArray, bool bTemp=false );
    /**
    * Sets the ID to { 0, 0, ..., 0 }. The temp flag @a bTemp is not changed.
    * @see setTemp
    */
    void setNull();
    /**
    * Sets the @a bTemp flag. Note: the ID is not changed.
    * @param bTemp The new value for the temp flag.
    * @see setNull
    */
    void setTemp( bool bTemp );
    /**
    * Writes the ID to a stream. The result looks like: "[0f,00,00,00,00,00]"
    * or if it is a temp object "temp[01,04,00,00,00,00]".
    * @param out The output stream.
    */
    void write( ostream& out ) const;

  private:
    /**
    * The ID is an array of a fixed number of bytes
    */
    byte ObjectID[ID_SIZE];
    /**
    * Describes if the ID is a temp or a real one
    */
    bool bTemp;
};





//----------------------------------------  class TLinkBase  ----------------------------------------

/**
* @class TLinkBase
* @brief An easy way to link objects.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLink, TLinkable, TLinkUpdate
*
* This is the base class for linking objects. Setting a link to an object
* does not only store the pointer to the dest object but also the destination
* ID. That makes it possible to load and save links which is normaly (using
* pointers only) almost impossible.
*
* While loading the game the link receives only the dest ID and @e not the
* pointer to the object (see @ref setDest(const TObjectID&) ).
* There is no way around this because the dest object might be loaded after
* the object which sets the link. The @a bNeedUpdate flag shows if the
* link is complete or needs an update. The information if the link
* needs an update (to become a "real" link) is also stored in the
* TLinkUpdate class (see TLinkUpdate for details about the update process).
*
* A link is always in one of the three following states:
* <ol>
*   <li>Null link (comparable with a null pointer)<br>
*     That means that the destination pointer (@a pDest) is 0 as well as
*     the dest ID is 0. The method @ref isNull can be used to find out
*     if the link is a null link or not.
*   </li>
*   <li>"Real" link  (the "normal" state)<br>
*     The ID as well as the pointer have values which are different from 0. The
*     link is in any case valid if @ref isValid says so. If the dest object
*     is deleted than the link will automatically (this is a special feature
*     of the @ref TLinkable class) be set to a null link (see above).
*     Use the method @ref isValid to find out if the link is a real one or not.
*   </li>
*   <li>Link waiting for update<br>
*     This state normaly only occurs during the loading process
*     (see @ref TLinkUpdate for more details). The link needs an update
*     (the internal update flag @a bNeedUpdate is set to @c true). The dest
*     ID has a value and the pointer is set to 0 so in this case the link
*     is also a null link.
*     The method @ref isUpdated shows if the link is waiting for an update or not.
*   </li>
* </ol>
*
* A special feature of the TLink and TLinkable classes is that links always
* point to valid objects or are null links. If a dest object is removed
* the link will automatically be set to null (see @ref TLinkable
* for more details).
*/
class TLinkBase
{
  friend class TLinkUpdate;
  friend class TLinkable;

  public:
    /**
    * see @ref getType for details.
    */
    enum {
      LINK_BASE = 0,
      LINK,
      DOUBLE_LINK
    };

    /**
    * Creates an empty link by calling the method @ref reset.
    */
    TLinkBase();
    /**
    * Initializes the object with the destination object.
    * The ID of the destination object is copied to this object.
    * @param p The destination object of the link.
    */
    TLinkBase( TLinkable* p );
    /**
    * Initializes the object with the destination ID.
    * The pointer will be updated when the link/object couple is committed.
    * @param DestID The destination ID of the link.
    */
    TLinkBase( const TObjectID& DestID );
    /**
    * Copy constructor.
    * @param link The destination of the link.
    */
    TLinkBase( const TLinkBase& link );
    /**
    * Removes the link. If the link needs an update it is also
    * removes the update request from TLinkUpdate.
    */
    virtual ~TLinkBase();
    /**
    * @return The pointer to the dest object or 0 if the dest object
    *   does not exist.
    */
    TLinkable* getDest() const;
    /**
    * @return The ID of the dest object.
    */
    const TObjectID& getDestID() const;
    /**
    * @return The type of the dest object.
    * @see TType
    */
    int2 getDestType() const;
    /**
    * Note: there are three different link types possible: TLinkBase, TLink
    * and TDoubleLink. In some cases it is useful to know whether the object is
    * a double link or not (this is the main reason for this method). Also note
    * that using RTTI might be unhandy since TLink, TDoubleLink are template classes
    * and therefore decideing if the object is a TDoubleLink object might be
    * difficult.
    * @return The link type.
    */
    virtual int2 getType() const;
    /**
    * @return The name of the type of the dest object.
    * @see TType
    */
    const string& getDestTypeName() const;
    /**
    * Checks if the link is a null object (that means that the destination
    * pointer @e and the dest ID is 0). Note: a null link never needs an
    * update.
    * @return @c true if @a pDest and @a DestID is zero, otherwise @c false.
    * @see IsValid
    */
    bool isNull() const;
    /**
    * @return @c true if the object does not need an update. If the
    *   object is waiting an update the method returns @c false.
    */
    bool isUpdated() const;
    /**
    * @return @c true if the link points to a real object, otherwise @c false.
    *   Note: you can always(!) trust this information. Links will automatically
    *   be set to null if the dest object is deleted (see @ref TLinkable for more
    *   information on inverse links). Note also that a link that is waiting for
    *   an update is @e not a valid link.
    *   (For more details please see the class description above.)
    * @see IsNull
    */
    bool isValid() const;
    /**
    * Loads a TLinkBase object from a list of data packages.
    * Note that a successful load will delete the datapackage from the data
    * package list as well as the datapackage itself.
    * @param in The input stream of data packages.
    * @param sIdentifier The identifier to look for.
    * @param bUnique Loads the data only if the identifier is unique.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    bool load( TDataPackageList* in, const string& sIdentifier, bool bUnique=true );
    /**
    * The standard operator= copies all components. It also takes care
    * that if @e src needs an update that the copy also gets an update.
    * @param src The link you want to copy.
    * @return The new link.
    */
    TLinkBase& operator=( const TLinkBase& src );
    /**
    * Two links are equal if they need no update and if their
    * destination object is the same.
    */
    bool operator==( const TLinkBase& Two ) const;
    /**
    * Creates the data package of TLinkBase object and adds it to
    * the data package list.
    * @param out The list of data packages.
    * @param sIdentifier The identifier which is used to store and find the data.
    * @param bUnique If set to @c true the method will check if the identifier was
    *   already used in the data package list.
    * @return @c true if everything worked fine, otherwise @c false (e.g. if
    *   the identifier was already used in the data package list).
    */
    bool save( TDataPackageList* out, const string& sIdentifier,
               bool bUnique=true ) const;
    /**
    * Sets a link to an object type of TLinkable.
    * @param p pointer to the object which should be linked.
    */
    virtual void setDest( TLinkable* p );
    /**
    * Changes the link to a null link  (that means that the destination
    * pointer and the dest ID is 0).
    * Note: Identical to call setDest(0).
    * @see setDest(TLinkable*)
    */
    virtual void setNull();
    /**
    * Writes the dest ID to a stream.
    * @param out The output stream.
    */
    void Write( ostream& out ) const;

  protected:
    /**
    * Shows if the link needs an update or not. This flag is only
    * useful while loading the game.
    */
    bool bNeedUpdate;
    /**
    * The dest object.
    */
    TLinkable* pDest;
    /**
    * The ID of the dest object.
    */
    TObjectID DestID;
    /**
    * ID which is null.
    */
    static TObjectID NullID;
    /**
    * If @a bNeedUpdate is set to @c true this method
    * will remove the update request from TLinkUpdate
    * and reset all values to zero.
    * @see Reset
    */
    void removeUpdateRequest();
    /**
    * Sets @a bNeedUpdate to @c true and requests an update
    * from TLinkUpdate.
    * @RemoveUpdateRequest
    */
    void requestUpdate();
    /**
    * Resets the link to the default values, that means @a bNeedUpdate to
    * @c false, @a pDest = 0, @a DestID = 0.
    * Note: This method will _not_ check if the @a bNeedUpdate flag
    * is @c true and also will not remove the inverse link to avoid
    * recursion loops.
    */
    void reset();
    /**
    * Sets an incomplete link, since only the dest ID is known.
    * This will automatically set the @a bUpdateFlag to @c true.
    * The dest pointer (@a pDest) is set to 0 so that @ref isNull
    * will always return @c true.
    */
    void setDest( const TObjectID& DestID );
};





//----------------------------------------  class TLink  ----------------------------------------

/**
* @class TLink
* @brief The class for setting links to objects.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkBase
*
* This template class handles FIXME.
*
* See @ref TLinkBase for more general information about links.
*/
template<class X> class TLink : public TLinkBase
{
  friend class TLinkUpdate;

  public:
    TLink() : TLinkBase()
    {
    };
    TLink( const TObjectID& DestID ) : TLinkBase( DestID )
    {
    };
    TLink( X* p ) : TLinkBase( p )
    {
    };
    TLink( const TLink<X>& link ) : TLinkBase( link )
    {
      // TLink does not introduce any new data, so we can simply use
      // base-class assignment
      TLinkBase::operator=( link );
    }

    /**
    * Casts the link to a pointer. Note: this method is similar to
    * @ref getPointerToDest with the exception that an error message is
    * triggered if the dest pointer is zero.
    * @param The pointer to the dest object
    */
    operator X*() const
    {
      if ( getDest() == 0 )  {
        ELOG("TLink","operator X*") << "Link -> pointer conversion for null link :-(" << endl;
      }
      return getPointerToDest();
    }
    /**
    * This allows using a link in the same way as a pointer. E.g. the following
    * code is exactly doing what you would expect:
    *
    * <pre>
    *   TFoo f;      // derived from TLinkable
    *   link<TFoo> l( &f );
    *   l->aMethodOfTFoo();
    * </pre>
    *
    * @return A pointer to the dest object.
    */
    X* operator->() const
    {
      if ( getDest()== 0 )  {
        ELOG("TLink","operator->") << "Null pointer used for call :-(" << endl;
      }
      return getPointerToDest();
    }
    /**
    * Converts the pointer (to a TLinkable) to a pointer
    * to the real object. If the conversion fails the method
    * calls the Fatal function.
    * @return A pointer to the object or 0 if the link points to nowhere.
    */
    X* getPointerToDest() const
    {
      if ( TLinkBase::getDest() == 0 )  return 0;
      X* p = dynamic_cast<X*>(TLinkBase::getDest());
      if ( p == 0 )
        Fatal("TLink","GetPointerToDest", "TLink => TLinkable type mismatch or null pointer");
      return p;
    }
    /**
    * @return The type of the link, that means TLinkBase::LINK in this case.
    * @see TLinkBase::getType()
    */
    virtual int2 getType() const
    {
      return TLinkBase::LINK;
    }
    /**
    * Sets a link to an object type of @e X.
    * @param A pointer to the object which should be linked.
    */
    void setDest( X* p )
    {
      TLinkBase::setDest( p );
    }
    /**
    * @see TLinkBase::setNull()
    */
    virtual void setNull()
    {
      TLinkBase::setDest( (X*) 0 );
    }

  private:
    /**
    * Makes the implementation of TLinkBase::setDest private. This is neccessary
    * because we now need the exact type of the destination object (otherwise
    * it would be possible to pass an pointer to an object with the wrong (!=X)
    * type. Note that there is another setDest method with correct type checking.
    */
    virtual void setDest( TLinkable* )  { }
};




//----------------------------------------  class TDoubleLinkBase  ----------------------------------------
/**
* @class TDoubleLinkBase
* @brief Abstract base class for TDoubleLink.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TDoubleLink
*
* Defines a common interface for TDoubleLink.
*/
class TDoubleLinkBase
{
  public:
    /**
    * @return The object that "owns" the double link.
    */
    virtual TLinkable* getInverse() const = 0;
};





//----------------------------------------  class TDoubleLink  ----------------------------------------
/**
* @class TDoubleLink
* @brief Similar to TLink, but also stores the inverse direction.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkBase, TLink
*
* This class is basically a link, but also stores the information
* about the owner of the TDoubleLink object. This makes it possible
* to get more information for a linked object, as you can see in the following
* example:
*
* A subfleet uses a double link, which points to the used ship design.
* The ship design object has now the possibility via TLinkable::getLinkedByList
* to get the list of objects which points towards it. Refining leads to FIXME
*/
template<class X> class TDoubleLink : public TDoubleLinkBase, public TLink<X>
{
  public:
    TDoubleLink() : TLink<X>()
    {
      setInverse( 0 );
    }
    TDoubleLink( TLinkable* src, X* dest ) : TLink<X>()
    {
      setDest( dest );
      setInverse( src );
    };

    /**
    * @return The object that "owns" the double link.
    */
    virtual TLinkable* getInverse() const
    {
      return fInverse.getDest();
    }
    /**
    * @return The type of the link, that means TLinkBase::DOUBLE_LINK in this case.
    * @see TLinkBase::getType()
    */
    virtual int2 getType() const
    {
      return TLinkBase::DOUBLE_LINK;
    }
    /**
    * Sets the "source" of the link.
    * @param src The object this link belongs to (a value of 0 means that this
    *   link is a null link (see TLinkBase for details).
    */
    void setInverse( TLinkable* src )
    {
      fInverse.setDest( src );
    }

  private:
    TLinkBase fInverse;
};





//----------------------------------------  class TLinkBaseList  ----------------------------------------

/**
* @class TLinkBaseList
* @brief List that contains pointers to different(!) links.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkList, TLinkBase, TLink
*
* Note that this is a list of pointers to TLinkBase objects. If you are looking
* for a list of links of the same type have a look at TLinkList.
*/
class TLinkBaseList : public list<TLinkBase*>
{
};





//----------------------------------------  class TLinkList  ----------------------------------------

/**
* @class TLinkList
* @brief A list of links to the same type of object.
* @author Marco Krohn, <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkBaseList, TLinkBase, TLink
*
* In contrary to TLinkBaseList this list is only useful for storing
* links of the same type.
*/
template<class X> class TLinkList : public list< TLink<X> >
{
};





//----------------------------------------  class TType  ----------------------------------------

/**
* @class TType
* @brief Simple replacement for RTTI (run time type information).
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkable
*
* The class is just to avoid usage of the RTTI feature which not all
* compilers support at the moment.
*/
class TType
{
  public:
    enum
    {
      UNKNOWN = 0,
      LINKABLE,
      FLEET,
      SUBFLEET,
      GALAXY,
      SHIPDESIGN,
      ITEM,
      MINEFIELD,
      MINERAL_PACKAGE,
      MYSTERY_TRADER,
      PLANET,
      SYSTEM,
      ACTION
    };

    /**
    * @return The object type.
    */
    virtual int2 getType() const;
    /**
    * @return The object type name.
    */
    virtual const string& getTypeName() const;
};





//----------------------------------------  class TLinkable  ----------------------------------------

/**
* @class TLinkable
* @brief Stores the ID and a list of links which point to this object.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkBase, TLinkList, TLinkBaseList, TLinkUpdate, TObjectID
*
* All objects which need to be linked (like TRace, TFleet, ...) must
* be derived from TLinkable. TLinkable has its own unique ID and also stores
* a list of all links which are pointing to the object. The real advantage
* of this class over a pointer is that it is possible to save all objects and
* the links to disk and also restore this information. See TLinkUpdate for more
* information.
*
* If the object is deleted all links pointing to the object
* are automatically resetted.
*
* FIXME: add example / usage
*/
class TLinkable : public TType
{
  friend class TLinkBase;
  friend class TLinkUpdate;

  public:
    /**
    * @return The ID of this object.
    */
    const TObjectID& getID() const;
    /**
    * @return List of links pointing to this object.
    */
    const TLinkBaseList& getLinkedByList() const;
    /**
    * @return The number of links pointing to this object.
    * @see getLinkedByList
    */
    int4 getNumberOfLinks() const;
    /**
    * @return The type of the object (TType::TLinkable)
    */
    virtual int2 getType() const;
    /**
    * @return "TLinkable".
    */
    virtual const string& getTypeName() const;
    /**
    * Loads a TLinkable. Note that classes that are derived from
    * this class @e must call TLinkable::Load explicitly to load the data
    * correctly.
    * @param in The list of data packages.
    * @return @c true means that everything was loaded correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool load( TDataPackageList* in );
    /**
    * Saves a TLinkable object by adding the data packages to the list. Note that
    * classes that are derived from this class @e must call TLinkable::Save
    * explicitly to save the data correctly.
    * @param out The output stream of data packages.
    * @return @c true means that everything was saved correctly, otherwise
    *   this method will return @c false.
    */
    virtual bool save( TDataPackageList* out ) const;

  protected:
    /**
    * Generates a unique ID for the object. Making the constructor
    * protected forbids creating objects of the type TLinkable.
    */
    TLinkable();
    /**
    * Resets all links pointing to this object. This of course needs
    * the @a LinkedBy list.
    * @see Reset
    */
    virtual ~TLinkable();

    /**
    * Resets all values (this will also reset all links pointing
    * to this object).
    */
    virtual void reset();

  private:
    /**
    * This counter always points to the next unique ID.
    */
    static TObjectID UniqueID;
    /**
    * The ID of this object.
    */
    TObjectID ID;
    /**
    * List of links to TLinkable objects linking this object.
    */
    TLinkBaseList LinkedBy;

    /**
    * The copy constructor is not implemented since it is forbidden to
    * copy a TLinkable object. IDs have to be unique. This is also the
    * reason for making the copy constructor private: to make it impossible
    * to copy this object.
    */
    TLinkable( const TLinkable& Src );

    /**
    * Adds a link to the @a LinkedBy list.
    * @param p FIXME
    */
    void addInverseLink( TLinkBase* p );
    /**
    * Copying a TLinkable object is forbidden since all objects have to
    * have different IDs. That's why this method is private and is doing
    * nothing.
    */
    TLinkable& operator=( const TLinkable& Src );
    /**
    * Removes a link from the @a LinkedBy list.
    * @param p is the pointer which should be removed from the @a LinkedBy list.
    */
    void removeInverseLink( TLinkBase* p );
};





//----------------------------------------  class TLinkUpdate  ----------------------------------------

/**
* @class TLinkUpdate
* @brief Updates link objects during the loading process.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: link.h,v 1.39 2002/07/08 06:17:55 mkrohn5 Exp $
* @see TLinkBase, TLink, TLinkable, TObjectID
*
* A link consists (as described in TLink, TLinkBase) consists of two parts,
* the ID of the dest object and the address of the object. During the loading
* process a link loads only the ID of the dest object since the dest object
* might not even be there during loading time. All loaded links and linkable
* objects register themselves (automatically, you don't have to care about
* the details) in TLinkUpdate which than cares about updating the links.
*
* For details please read the RFC "Object ID Handling".
*/
class TLinkUpdate
{
  public:
    /**
    * Calls @ref checkConsistency to ensure that everything is o.k.
    */
    ~TLinkUpdate();

    /**
    * Checks if the class really updated all links which requested an update.
    * This method should be called after all objects are loaded.
    * @return @c true no problems during update, otherwise @c false.
    */
    bool checkConsistency();
    /**
    * When a new TLinkable object is read the pointer to the object and the
    * old ID of the object are send to LinkUpdate. These information are then
    * stored in a map. If one of the links in the @a UpdateList points to the
    * old ID than this link is updated and removed from the list.
    * @param pNew Pointer to the new object.
    * @param OldID The ID the object had before.
    */
    void commitUpdate( TLinkable* pNew, const TObjectID& OldID );
    /**
    * In case the link does not need an update any more the request
    * is deleted from the @a UpdateList.
    * @param pLink The link that does not need an update anymore.
    */
    void deleteUpdateRequest( const TLinkBase* pLink );
    /**
    * @return The unique instance of TLinkUpdate.
    */
    static TLinkUpdate* instance();
    /**
    * Requests an update for a link. If @a Map already provides
    * the needed information the link is immediately updated. Otherwise
    * the pointer is added to the @a UpdateList and has to wait for the update.
    * @param pLink The link that needs an update.
    */
    void requestUpdate( TLinkBase* pLink );
    /**
    * Resets the class to the initial state. You should know what you
    * are doing!
    */
    void reset();

  protected:
    /**
    * Constructor made protected to ensure that the users of this
    * class can only create exactly one instance.
    * @see instance
    */
    TLinkUpdate();

  private:
    /** The global (and unique) instance of TUniverse */
    static TLinkUpdate* fInstance;
    /**
    * A map that stores for all old ID the new pointer to the object.
    */
    map<TObjectID, TLinkable*> fMap;
    /**
    * The list of links which need an update.
    */
    TLinkBaseList fUpdateList;

    // FIXME: remove the following methods later (for debugging only)
    void showMap();
    void showUpdateList();
};





#endif        // __LINK_INCLUDED
