// $Id: datapackage.h,v 1.25 2002/07/03 18:01:32 mkrohn5 Exp $

// Date Package Header File
// Written by: Marco Krohn, <marco.krohn@gmx.de>
//             Alberto Barsella, <Alberto.Barsella@univ-lille1.fr>

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

#ifndef __DATA_PACKAGE_INCLUDED
#define __DATA_PACKAGE_INCLUDED

#include <fstream>
#include <string>
#include <deque>

#include "common/defs.h"
#include "common/leakchecker.h"

class TDataPackageList;
class TObjectID;
class TPoint;


using namespace std;



//----------------------------------------  class TDataPackage  ----------------------------------------

/**
* @class TDataPackage
* @brief A wrapper for data.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: datapackage.h,v 1.25 2002/07/03 18:01:32 mkrohn5 Exp $
* @see TDataPackageList
*
* (This is the reference for TDataPackage and TDataPackageList)
*
* A data package is a wrapper for all kind of elementary data.
*
* FIXME: list of all supported data
*
* The general
* problem this class and TDataPackageList are going to solve is the
* transportation problem of data. With the help of TDataPackage and
* TDataPackageList you can unite very different data like
* (e.g. @c bool, @c string and @c double) to a package list and send this list
* to the receiver who has easily access to the stored data.
*
* Note: for convenience there are several methods implemented in TDataPackageList
* which reduce the need to understand TDataPackage to almost zero.
*
* As mentioned above the data package is only designed for elementary data,
* more complex data (e.g. TPlanet) is handled as a composite data object
* consisting of many data packages (see TDataPackageList for details).
* TDataPackage is quite flexible in its usage: it stores a pointer to the
* "real data" (often refered as "content") and let the creator of the data package
* decide whether the content should be automatically deleted or not. Since
* the data package stores only a pointer you have to ensure that the pointer
* is still valid, when the data package is used by the receiver. For example
*
* <pre>
* TDataPackageList* foo( TDataPackageList* dpl )
* {
*   string s = "this data will not survive";
*   dpl->add( "keyword", &s, true );
*   return dpl;
* }
* </pre>
*
* would be fatal since the pointer gets invalid after leaving the method.
* (Note the "true" in the add function guarantees that a data package name does
* not occur twice.)
*
* In this case the right thing to do is making a "deep copy" of the object:
*
* <pre>
* TDataPackageList* foo( TDataPackageList* dpl )
* {
*   string s = "this data will not survive";
*   dpl->add( "keyword", new string(s), true, true );
*   return dpl;
* }
* </pre>
*
* This makes (I have not tested it yet, so please tell me if the code is wrong, FIXME)
* a deep copy of the object and "sends" the resulting pointer to the data package.
* Now of course the data package has to take care of deleting the content. This is
* achieved by adding the last parameter: "true" (means that the autodelete is activated
* for this package).
*
* If you are looking for more examples of TDataPackageList you should
* have a look at the load and save methods, as well as the parser. The data package
* system also plays a central role in the rule atom mechanism.
*
* In case you want to add another data type to TDataPackage,
* please have a look at the code of @c CheckAutoDelete and
* @c TDataPackageList::WriteDataPackage. And check if it is really
* neccessary to add another data type or if an composite type
* would do it as well.
*/
class TDataPackage
{
  public:
    enum tType
    {
      BOOL=0,
      DATA_PACKAGE_LIST,
      DOUBLE,
      ID,
      INTEGER_2,
      INTEGER_4,
      POINT,
      STRING
    };

    /**
    * Sets @a bAutoDelete to c false and @a pData to null.
    */
    TDataPackage();
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c bool.
    */
    TDataPackage( const string& sIdentifier, const bool* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c double.
    */
    TDataPackage( const string& sIdentifier, const double* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c int2.
    */
    TDataPackage( const string& sIdentifier, const int2* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c int4.
    */
    TDataPackage( const string& sIdentifier, const int4* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c string.
    */
    TDataPackage( const string& sIdentifier, const string* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c TObjectID.
    */
    TDataPackage( const string& sIdentifier, const TDataPackageList* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c TObjectID.
    */
    TDataPackage( const string& sIdentifier, const TObjectID* pData );
    /**
    * Sets @a bAutoDelete to @c false and initializes @a pData
    * with the specified @c TPoint.
    */
    TDataPackage( const string& sIdentifier, const TPoint* pData );
    /**
    * Calls CheckAutoDelete();
    */
    ~TDataPackage();

    /**
    * @return The settings of the auto-delete mode.
    * @see SetAutoDeleteMode
    */
    bool GetAutoDeleteMode() const;
    /**
    * @return The identifier for this data package.
    */
    const string& GetIdentifier() const;
    /**
    * @return The type for this data package.
    */
    const tType GetType() const;
    /**
    * Cast operator to type @c bool*.
    */
    operator bool*() const;
    /**
    * Cast operator to type @c double*.
    */
    operator double*() const;
    /**
    * Cast operator to type @c int2*.
    */
    operator int2*() const;
    /**
    * Cast operator to type @c int4*.
    */
    operator int4*() const;
    /**
    * Cast operator to type @c string*.
    */
    operator string*() const;
    /**
    * Cast operator to type @c TDataPackageList*.
    */
    operator TDataPackageList*() const;
    /**
    * Cast operator to type @c TObjectID*.
    */
    operator TObjectID*() const;
    /**
    * Cast operator to type @c TPoint*.
    */
    operator TPoint*() const;
    /**
    * Enabling auto-delete (enable is @c true) will automatically delete the
    * object whenever the pointer variable @a pData is changed.
    * The default setting is @c false.
    *
    * Examples: Setting new data (the old data is than deleted automatically)
    * and calling the destructor.
    * @param The new value for the auto delete mode. If set to @c true
    *   the objects this object wraps will be deleted.
    */
    void SetAutoDeleteMode( bool bAutoDelete );
    /**
    * FIXME
    */
    void SetData( const string& sIdentifier, const bool* pData );
    void SetData( const string& sIdentifier, const double* pData );
    void SetData( const string& sIdentifier, const int2* pData );
    void SetData( const string& sIdentifier, const int4* pData );
    void SetData( const string& sIdentifier, const TDataPackageList* pData );
    void SetData( const string& sIdentifier, const TObjectID* pData );
    void SetData( const string& sIdentifier, const TPoint* pData );
    void SetData( const string& sIdentifier, const string* pData );

  private:
    #ifdef SECURE_MODE
      /**
      * A small check for detecting memory leaks.
      * @see TLeakChecker
      */
      static TLeakChecker lc;
    #endif // SECURE_MODE
    /**
    * Current settings for the auto-delete mode (see @ref SetAutoDeleteMode
    * for more information).
    */
    bool bAutoDelete;
    /**
    * Pointer to the real data.
    */
    void* pData;
    /**
    * An identifier for the data.
    */
    string sIdentifier;
    /**
    * The type of the data.
    */
    tType type;

    /**
    * Deletes the current data @a pData if @a bAutoDelete is set to @c true and
    * @p pData is not equal null.
    */
    void CheckAutoDelete();
    /**
    * Sets @a bAutoDelete to @c false and @a pData to 0.
    */
    void Reset();
};





//----------------------------------------  class TDataPackageList  ----------------------------------------

/**
* @class TDataPackageList
* @brief A simple list of data packages.
* @author Marco Krohn <marco.krohn@gmx.de>
* @version $Id: datapackage.h,v 1.25 2002/07/03 18:01:32 mkrohn5 Exp $
* @see TDataPackage
*
* Note that TDataPackageList will delete all TDataPackage objects
* when the destructor is called. It depends on the settings
* of the individual TDataPackage objects if their content is also
* deleted. Please read the documentation of TDataPackage for more
* information and examples.
*
* FIXME: extent documentation
* (in TDataPackage is a reference to this text)
*/
class TDataPackageList : public deque<TDataPackage*>
{
  public:
    TDataPackageList();
    /**
    * Deletes all data packages. It depends on the settings of the
    * individual TDataPackage objects if their content is also deleted.
    * @see TDataPackage::SetAutoDeleteMode
    */
    ~TDataPackageList();
    
    /**
     * Adds a data package containing a @c bool to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case of boolean type.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const bool* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a @c double to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case of type @c double.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const double* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a @c int2 to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case of type @c int2.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const int2* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a @c int4 to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case of type @c int4.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const int4* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a @c string to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case of type @c string.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const string* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a TDataPackageList to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case a TDataPackageList object.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const TDataPackageList* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a TObjectID to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case a TObjectID object.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const TObjectID* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
     * Adds a data package containing a TPoint to the list of data packages.
     * @param sIdentifier The identifier of the data package.
     * @param pData The real data, in this case a TPoint object.
     * @param bUnique If set to @c true the data will only be added if no identifier
     *   with the same name already exists.
     * @param bAutoDelete Determines if the data will be automatically deleted after
     *   the data package is not needed any more. This means that something like
     *   <tt>delete pData</tt> will be called. Use with care!
     * @return @c true if the data package was added without problems,
     *   otherwise @c false.
     */
    bool add( const string& sIdentifier, const TPoint* pData,
              bool bUnique=true, bool bAutoDelete=false );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a @c bool variable.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const bool& data, bool unique=true );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a @c double variable.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const double& data, bool unique=true );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a @c int2 variable.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const int2& data, bool unique=true );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a @c int4 variable.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const int4& data, bool unique=true );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a string.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const string& data, bool unique=true );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a TObjectID.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const TObjectID& data, bool unique=true );
    /**
    * In contrast to @ref add this method first makes a copy of the object
    * and then adds it to the data package list (and of course takes care
    * of deleting the object finally).
    * @param identifier The identifier of the data package.
    * @param data The real data, in this case a TPoint.
    * @param unique If set to @c true the data will only be added if no identifier
    *   with the same name already exists.
    * @return @c true if the data package was added without problems,
    *   otherwise @c false.
    */
    bool addCopy( const string& identifier, const TPoint& data, bool unique=true );
    /**
    * Deletes all elements of the list as well as the list itself.
    */
    void DeleteAll();
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, bool* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, double* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, int2* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, int4* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, string* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, TDataPackageList* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, TObjectID* pData, bool bUnique=true );
    /**
    * Reads a TDataPackage object from a list of datapackages.
    * After reading the data package the package is deleted.
    * @param sIdentifier The identifier of the data package.
    * @param pData The pointer where the data is copied to.
    * @param bUnique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return @c true if the datapackage was unpacked without problems, in
    *   case that the identifier was not found or not unique the method will
    *   return @c false.
    */
    bool getAndDelete( const string& sIdentifier, TPoint* pData, bool bUnique=true );
    /**
    * Reads a @c bool value from a list of data packages.
    * In contrary to @ref get it will @e not delete anything and also
    * note that the return value is used in a different way.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @param valid Contains the information if the date package really
    *   exists or not (@c true means that the package exists and you can
    *   trust the return value).
    * @return The content of the datapackage.
    */
    bool getBool( const string& identifier, bool unique=true, bool* valid=0  ) const;
    /**
    * Reads a @c double value from a list of data packages.
    * In contrary to @ref get it will @e not delete anything and also
    * note that the return value is used in a different way.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @param valid Contains the information if the date package really
    *   exists or not (@c true means that the package exists and you can
    *   trust the return value).
    * @return The content of the datapackage.
    */
    double getDouble( const string& identifier, bool unique=true, bool* valid=0 ) const;
    /**
    * Reads an @c int2 value from a list of data packages.
    * In contrary to @ref get it will @e not delete anything and also
    * note that the return value is used in a different way.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @param valid Contains the information if the date package really
    *   exists or not (@c true means that the package exists and you can
    *   trust the return value).
    * @return The content of the datapackage.
    */
    int2 getInt2( const string& identifier, bool unique=true, bool* valid=0 ) const;
    /**
    * Reads an @c int4 value from a list of data packages.
    * In contrary to @ref get it will @e not delete anything and also
    * note that the return value is used in a different way.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @param valid Contains the information if the date package really
    *   exists or not (@c true means that the package exists and you can
    *   trust the return value).
    * @return The content of the datapackage.
    */
    int4 getInt4( const string& identifier, bool unique=true, bool* valid=0 ) const;
    /**
    * Reads an string from a list of data packages.
    * In contrary to @ref get it will @e not delete anything and also
    * note that the return value is used in a different way.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @param valid Contains the information if the date package really
    *   exists or not (@c true means that the package exists and you can
    *   trust the return value).
    * @return The content of the datapackage.
    */
    const string getString( const string& identifier, bool unique=true, bool* valid=0 ) const;
    /**
    * Reads an object TPoint from a list of data packages.
    * In contrary to @ref get it will @e not delete anything and also
    * note that the return value is used in a different way.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @param valid Contains the information if the date package really
    *   exists or not (@c true means that the package exists and you can
    *   trust the return value).
    * @return The content of the datapackage.
    */
    const TPoint getPoint( const string& identifier, bool unique=true, bool* valid=0 ) const;
    /**
    * FIXME
    * be careful: this is not doing a deep copy of the lists. Therfore we
    * get two lists which point to the same object. That is not good!
    * Idea: change the behaviour of operator= and make a deep copy?!
    * meaning: make a real copy of the data packages, but set them for the
    * new version to autodelete=false. Fixing the method may have influence on
    * getAndDelete( const string& sIdentifier, TDataPackageList* pData,
    *                          bool bUnique )
    * !!!
    * Better write a good test of TDataPackage / TDataPackageList before
    * changing anything (MK, 2002/06/21).
    */
    TDataPackageList& operator=( const TDataPackageList& src );
    /**
    * Writes a list of data packages to a stream. Note that calling this
    * method will also delete @e all elements in the data package list.
    * @param out The output stream.
    * @return @c true if no problems occured while saving, otherwise @c false.
    */
    bool save( ofstream& out );
    /**
     * Searches for a data package with a given identifier.
     * @param sIdentifier The identifier of the data package to look for.
     * @return The pointer to the data package or 0 if no data package with
     *   the name @e sIdentifier was not found.
     */
    TDataPackage* Search( const string& sIdentifier ) const;
    /**
     * Searches for a data package with a given identifier and
     * ensures that the identifier is unique.
     * @param sIdentifier The identifier of the data package to look for.
     * @return The pointer to the data package or 0 if no data package with
     *   the name @e sIdentifier was not found or the package was no unique.
     */
    TDataPackage* SearchUnique( const string& sIdentifier ) const;
    /**
     * Searches for a data package with a given identifier and extracts
     * the data package from the list of data packages.
     * It is your duty to delete the data package after that.
     * @param sIdentifier The identifier of the data package to look for.
     * @return The pointer to the data package or 0 if no data package with
     *   the name @e sIdentifier was not found.
     */
    TDataPackage* SearchAndExtract( const string& sIdentifier );
    /**
     * Searches for a data package with a given identifier and extracts
     * the data package from the list of data packages if the identifier
     * was unique. It is your duty to delete the data package after that.
     * @param sIdentifier The identifier of the data package to look for.
     * @return The pointer to the data package or 0 if no data package with
     *   the name @e sIdentifier was not found (or the data package was not
     *   unique).
     */
    TDataPackage* SearchAndExtractUnique( const string& sIdentifier );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, bool value );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, double value );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, int2 value );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, int4 value );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, const string& value );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, const char* value );
    /**
    * Sets a data package with the name @e identifier to @e value.
    * If the data package does not exist it is created.
    * @param identifier The "name" of the data package.
    * @param value The new value for the content of the data package.
    */
    void set( const string& identifier, const TPoint& value );
    /**
    * For debugging only!
    * This method writes the content of the datapackage list to the log file.
    */
    void showContent( int indent=0 ) const;

  private:
    #ifdef SECURE_MODE
      /**
      * A small check for detecting memory leaks.
      * @see TLeakChecker
      */
      static TLeakChecker lc;
    #endif // SECURE_MODE
    /**
    * Looks up a package and deletes it from the list.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return The data package or 0 in case the package does not exist or
    *   (if unique is set to @c true) is not unique.
    */
    TDataPackage* getAndExtractPackage( const string& identifier, bool unique );
    /**
    * Looks up a package without deleting it.
    * @param identifier The "name" of the data package.
    * @param unique If set to @c true this method will read the data package
    *   only if there are no other data packages with the same name.
    * @return The data package or 0 in case the package does not exist or
    *   (if unique is set to @c true) is not unique.
    */
    TDataPackage* getPackage( const string& identifier, bool unique ) const;
    /**
    * Writes a number of spaces to the ofstream.
    * (This is used to make the output file a bit nicer).
    * @param out The output stream.
    * @param iIndent The number of spaces.
    */
    void Indent( ofstream& out, int2 iIndent ) const;
    /**
    * Writes a data package to an ofstream.
    * @param out The stream to write to.
    * @param pPackage The data package to write.
    * @return
    */
    bool WriteDataPackage( ofstream& out,
                           const TDataPackage& pPackage, int2 iIndent=0 ) const;
};





#endif        // __DATA_PACKAGE_INCLUDED
