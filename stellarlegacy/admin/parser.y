%{
// $Id: parser.y,v 1.3 2002/05/10 10:34:36 mkrohn5 Exp $

// Input file parser
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

#include "parser-use.h"
#include "common/point.h"
#include "common/link.h"
#include "common/datapackage.h"
#include "game.h"

#include <strstream>




int yyerror(const string& s);
int yylex(void);
void yyrestart(FILE*);

// the parser is not object-oriented: these globals are used as
// "temporary fields" during load (= parser is NOT reentrant!)
//TActionSequencer* parserSequencer;
TGame* parserGame;
int4 lineno;
// bool parse_failed;

%}

%union{
  string *y_str;
  double y_dbl;
  bool y_bol;
  int4 y_int;
  int* y_iar;
  TObjectID* y_oid;
  TPoint* y_pnt;
  TDataPackageList* y_dst;
};

%type  <y_iar> object_id_bytes
%type  <y_oid> object_id_spec
%type  <y_pnt> position_spec
%type  <y_dst> generic_object_spec
%type  <y_dbl> double_spec

%token <y_int> YINTEGER
%token <y_dbl> YDOUBLE
%token <y_str> YSTRING
%token <y_bol> YBOOLEAN

%token LBRACE RBRACE LBRACKET RBRACKET LPARE RPARE ASSIGN COMMA SEMICOLON
%token IDOPTTEMP INT2SPEC VEC3DSPEC

%%

input: /* NULL */
    {
      lineno = 1;
      //      parse_failed = false;
      // yydebug = 1;

      // TODO: MARK FIRST ACTION AS EXECUTABLE WHEN LOADING PLAYER ORDERS
      // CurrAction->SetCanExecute();
    }
    | input YSTRING LBRACE generic_object_spec RBRACE
    {
      // declare type
      TDataPackage* pkg = new TDataPackage("blocktype", $2);
      pkg->SetAutoDeleteMode(true);
      $4->push_back(pkg);

      // create the object
      parserGame->processDataBlock($4);

      // NOTE $2 NOT DEALLOCATED - handled by TDataPackage
      delete $4;
    }
    ;


generic_object_spec: /* NULL */
    {
      $$ = new TDataPackageList();
    }
    | generic_object_spec YSTRING ASSIGN object_id_spec SEMICOLON
    {
      // load a TObjectID into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, $4);
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
      // NOTE $4 NOT DEALLOCATED - handled by TDataPackage
    }
    | generic_object_spec YSTRING ASSIGN YINTEGER SEMICOLON
    {
      // load an int4 into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, new int4($4));
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
    }
    | generic_object_spec YSTRING ASSIGN YDOUBLE SEMICOLON
    {
      // load a double into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, new double($4));
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
    }
    | generic_object_spec YSTRING ASSIGN YBOOLEAN SEMICOLON
    {
      // load a boolean into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, new bool($4));
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
    }
    | generic_object_spec YSTRING ASSIGN INT2SPEC LPARE YINTEGER RPARE SEMICOLON
    {
      // load an int2 into the datapackage
      if ($6 > 32767 || $6 < -32768)
	yyerror("Integer value overflow");

      TDataPackage* pkg = new TDataPackage(*$2, new int2($6));
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
    }
    | generic_object_spec YSTRING ASSIGN YSTRING SEMICOLON
    {
      // load a string into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, $4);
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
      // NOTE $4 NOT DEALLOCATED - handled by TDataPackage
    }
    | generic_object_spec YSTRING ASSIGN position_spec SEMICOLON
    {
      // load a TPoint object into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, $4);
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
      // NOTE $4 NOT DEALLOCATED - handled by TDataPackage
    }
    | generic_object_spec YSTRING ASSIGN LBRACE generic_object_spec RBRACE
    {
      // load an object into the datapackage
      TDataPackage* pkg = new TDataPackage(*$2, $5);
      pkg->SetAutoDeleteMode(true);
      $$->push_back(pkg);
      delete $2;
      // NOTE $6 NOT DEALLOCATED - handled by TDataPackage
    }
    ;


object_id_spec:
      IDOPTTEMP object_id_bytes
    {
      $$ = new TObjectID($2, true);
      delete[] $2;
    }
    | object_id_bytes
    {
      $$ = new TObjectID($1);
      delete[] $1;
    }
    ;


object_id_bytes:
      LBRACKET YINTEGER COMMA YINTEGER COMMA YINTEGER COMMA YINTEGER COMMA YINTEGER COMMA YINTEGER RBRACKET
    {
      $$ = new int[6];
      $$[0] = $2;   $$[1] = $4;   $$[2] = $6;
      $$[3] = $8;   $$[4] = $10;  $$[5] = $12;
    }
    ;


position_spec: VEC3DSPEC LPARE double_spec COMMA double_spec COMMA double_spec RPARE
    {
      $$ = new TPoint($3, $5, $7);
    }
    ;


double_spec: YDOUBLE
    {
      $$ = $1;
    }
    | YINTEGER
    {
      $$ = (double)$1;
    }
    ;

%%


bool ReadFile(TGame* game, const string& fspec)
{
  FILE* f;

  if ( !(f = fopen(fspec.c_str(), "r") ) )
    return false;

  parserGame = game;

  yyrestart(f);
  yyparse();
  fclose(f);

  return true;
}


int yyerror(const string& s)
{
  ostrstream os;
  os << s << " at line " << lineno;
  Fatal("*Parser*", "*Parser*", os.str(), -1);

  //  parse_failed = true;
  return 0; // NOT REACHED
}

/*
 * $Log: parser.y,v $
 * Revision 1.3  2002/05/10 10:34:36  mkrohn5
 * changed a method name
 *
 * Revision 1.2  2001/11/27 10:16:26  mkrohn5
 * applied a patch of Alberto for reading int2
 *
 * Revision 1.1  2001/11/04 01:33:01  mkrohn5
 * moved some files around
 *
 * Revision 1.1  2001/08/07 20:58:28  mkrohn5
 * recommit parser & lex files
 *
 * Revision 1.11  2001/07/25 19:12:31  ishark
 * major additions in game/sl.cpp - skeleton of localserver
 *
 * Revision 1.10  2001/07/17 13:18:52  ishark
 * fixed memory leak in parser.y
 *
 * Revision 1.9  2001/07/10 17:57:32  ishark
 * rewrite in TGame (ProcessDataBlock/game creation, changes in TAction
 *
 * Revision 1.8  2001/07/05 20:34:18  ishark
 * added return true in test-item, fixed parser, added action Load/Save
 *
 * Revision 1.7  2001/07/02 00:38:36  mkrohn5
 * enabled call to "processDataBlock"
 *
 * Revision 1.6  2001/06/28 21:30:42  ishark
 * parser can read savefile, TObjectID now uses []
 *
 * Revision 1.5  2001/06/25 21:07:12  ishark
 * modified parser (still bad) + removed minor warnings in waypoint
 *
 * Revision 1.4  2001/05/10 23:17:30  mkrohn5
 * changed parameter list for function Fatal(...)
 *
 * Revision 1.3  2001/04/29 21:38:37  ishark
 * TAction updated to use TDataPackage/Load
 *
 * Revision 1.2  2001/04/18 20:56:52  ishark
 * minor changes in TAction, added meat in TActionSequencer
 *
 * Revision 1.1  2001/04/13 21:56:54  ishark
 * fixed osval/substance tests, added preliminary version of action
 *
 */
