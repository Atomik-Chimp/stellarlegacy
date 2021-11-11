// $Id: testing.cpp,v 1.4 2002/05/10 10:40:43 mkrohn5 Exp $

// Testing Code File
// Written by: Marco Krohn

// Copyright (C) 2001-, Marco Krohn, marco.krohn@gmx.de>
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





/*
* Test dependencies:
*
* DataTypes          - none
* testRandom         - DataTypes
* testObjectID       - TDataPackageList (for load & save tests)
* testLinkClass      - TObjectID
*/





#include <stdio.h>
#include <iostream>

#include "common/defs.h"
#include "testing/testing.h"

using namespace std;





#define RESET           0
#define BRIGHT          1
#define DIM             2
#define UNDERLINE       3
#define BLINK           4
#define REVERSE         7
#define HIDDEN          8

#define BLACK           0
#define RED             1
#define GREEN           2
#define YELLOW          3
#define BLUE            4
#define MAGENTA         5
#define CYAN            6
#define WHITE           7





//----------------------------------------  Prototypes  ----------------------------------------

void textcolor(int attr, int fg, int bg);

bool RunTestScripts();
bool testDataTypes();
bool testLinkClass();
bool testObjectIDClass();
bool testRandomClass();
bool TestOSValClass();
bool TestSubstanceClass();
bool TestActionClass();
bool TestShipDesignClass();
bool TestSubFleetClass();
bool TestFleetClass();





//----------------------------------------  class TTesting  ----------------------------------------

TTesting :: TTesting()
{
  reset();
}



int4 TTesting :: getChecksDone() const
{
  return fChecksDone;
}



int4 TTesting :: getSuccess() const
{
  return fSuccess;
}



void TTesting :: report( bool check )
{
  // how to read the escape sequence?
  // the first two bytes stand for the CSI (control sequence introducer) <esc>[
  // the third and fourth byte decode the absolute position in octal notation
  // 060 = "0", 061 = "1", ... 071 = "9"
  // and the 'G' tells us that we want an absolute horizontal offset
  printf("%c%c%c%c%c",033,0133,066,071,'G');
  cout << " ... ";

  if ( check == true )  {
    textcolor(BRIGHT, GREEN, BLACK);
    cout << "Success";
    textcolor(RESET, WHITE, BLACK);
  }
  else  {

    textcolor(BRIGHT, RED, BLACK);
    cout << "FAILED!";
    textcolor(RESET, WHITE, BLACK);
  }
  cout << endl;

  fChecksDone++;
  fSuccess += (int4) check;
}



void TTesting :: reset()
{
  fChecksDone = 0;
  fSuccess = 0;
}



bool TTesting :: result() const
{
  if ( fSuccess == fChecksDone )  return true;
  return false;
}





//----------------------------------------  Functions  ----------------------------------------

void textcolor(int attr, int fg, int bg)
{
char command[13];

  /* Command is the control command to the terminal */
  sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
  printf("%s", command);
}



bool RunATest(const char* tname, bool (*testfunc)())
{
  cout << "\nStart test ----------------------------(output from test function)" << endl;

  bool result = testfunc();

  cout << "------------------------------------------------------------------\n" << tname << " : ";

  if ( result )
    cout << "o.k." << endl;
  else
    cout << "FAILED!" << endl;

  cout << "==================================================================" << endl;

  return result;
}


/**
* Runs some automatic tests which give an indication if
* everything is o.k. or not.
* @return @c true if none of the executed tests failed, otherwise @c false.
*/
bool runTestScripts()
{
bool bReturn = true;

  textcolor(RESET, WHITE, BLACK);
  LOG("-", "RunTestScripts()") << "Now executing some test scripts ... " << endl;

  bReturn &= RunATest("data types .................", testDataTypes);
  bReturn &= RunATest("TRandom ....................", testRandomClass);
  bReturn &= RunATest("TObjectID ..................", testObjectIDClass);
  bReturn &= RunATest("TLink (and related) ........", testLinkClass);
  bReturn &= RunATest("TOSVal .....................", TestOSValClass);
  bReturn &= RunATest("TSubstance (and related) ...", TestSubstanceClass);
  bReturn &= RunATest("TShipDesign (and related) ..", TestShipDesignClass);
  bReturn &= RunATest("TSubFleet (and related) ....", TestSubFleetClass);
  bReturn &= RunATest("TFleet (and related) .......", TestFleetClass);
  bReturn &= RunATest("TAction (and related) ......", TestActionClass);

  //--------------------  Result
  if ( bReturn == true )
  {
    LOG("-", "RunTestScripts()") << "Everything was fine and all systems go ..." << endl;
  }
  else
  {
    LOG("-", "RunTestScripts()") << "At least one test script failed :-(" << endl;
  }

  return bReturn;
}

