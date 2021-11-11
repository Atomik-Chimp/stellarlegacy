// $Id: parser-use.h,v 1.2 2002/06/03 14:23:37 mkrohn5 Exp $

// Header File to define parser's public variables and functions
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

#ifndef __PARSERUSE_INCLUDED
#define __PARSERUSE_INCLUDED


#include <cstdio>
#include <string>
#include "common/defs.h"

using namespace std;


//class TActionSequencer;
class TGame;

// parser variables
// PROVIDED BY GAME? extern TActionSequencer* parserSequencer; FIXME?
extern int4 lineno;


// reinit parser
//void yyrestart(FILE*);

// invoke parser
//int yyparse(void);
bool ReadFile(TGame* game, const string& fspec);

// report error
int yyerror(const string& s);

#endif
