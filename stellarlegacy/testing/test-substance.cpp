// $Id: test-substance.cpp,v 1.2 2002/03/24 13:39:07 mkrohn5 Exp $

// Substance class testing
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

#include "gamelogic/substance.h"


static int2 success;
static int2 checksdone;


static
void report(const bool check)
{
  cout << " ... " << ((check)? "Success" : "FAILED") << endl;
  checksdone++;
  success += check;
}



bool TestSubstanceClass()
{
  int4 n, d, i;
  bool result;
  success = 0;
  checksdone = 0;

  TSubstanceType* Ironium = new TSubstanceType("Ironium", "Ir", 0, 1, 1);
  TSubstanceType* Boranium = new TSubstanceType("Boranium", "Bo", 0, 1, 1);
  TSubstanceType* Germanium = new TSubstanceType("Germanium", "Ge", 0, 1, 1);
  TSubstanceType* Colonists = new TSubstanceType("Colonists", "Co", 0, 1, 1);
  TSubstanceType* Fuel = new TSubstanceType("Fuel", "Fu", 1, 1, 0);
  TSubstanceType* Cargo = new TSubstanceType("Cargo Space", "CS", 0, -1, 0);
  TSubstanceType* FTank = new TSubstanceType("Fuel Tank", "FT", 1, -1, 0);
  TSubstanceType* Resources = new TSubstanceType("Resources", "Rs", 2, 0, 0);

  TSubstance* u;
  TSubstanceSet s, item;

  cout << "--- add substances ---" << endl;
  cout << s << endl;

  u = Germanium->Create(100); s.Add(*u); delete u;
  u = Ironium->Create(200); s.Add(*u); delete u;
  u = Fuel->Create(2000); s.Add(*u); delete u;

  cout << s << endl;

  cout << "--- check fuel ---" << endl;

  TSubstance* f = Fuel->Create(1000);
  n = 1; d = 1;
  cout << "Have " << *f << "*" << n << "/" << d << " ?  ";
  result = s.HasEnough(*f, n, d);
  cout << ((result)? "yes" : "no");
  report(result);

  n = 3; d = 1;
  cout << "Have " << *f << "*" << n << "/" << d << " ?  ";
  result = s.HasEnough(*f, n, d);
  cout << ((result)? "yes" : "no");
  report(!result);

  n = 4; d = 2;
  cout << "Have " << *f << "*" << n << "/" << d << " ?  ";
  result = s.HasEnough(*f, n, d);
  cout << ((result)? "yes" : "no");
  report(result);

  cout << "--- infinite supply ---" << endl;
  u = Fuel->Create(TOSVal::iInfinity); s.Add(*u); delete u;
  cout << s << endl;

  f->Amount() = 10000;
  n = 1; d = 1;
  cout << "Have " << *f << "*" << n << "/" << d << " ?  ";
  result = s.HasEnough(*f, n, d);
  cout << ((result)? "yes" : "no");
  report(result);

  n = 3; d = 1;
  cout << "Have " << *f << "*" << n << "/" << d << " ?  ";
  result = s.HasEnough(*f, n, d);
  cout << ((result)? "yes" : "no");
  report(result);

  f->Amount() = TOSVal::iMaximum;
  n = 4; d = 3;
  cout << "Have " << *f << "*" << n << "/" << d << " ?  ";
  result = s.HasEnough(*f, n, d);
  cout << ((result)? "yes" : "no");
  report(result);
  delete f;

  cout << "--- item production ---" << endl;
  u = Ironium->Create(25); item.Add(*u); delete u;
  u = Germanium->Create(15); item.Add(*u); delete u;
  u = Resources->Create(50); item.Add(*u); delete u;
  u = Resources->Create(1500); s.Add(*u); delete u;

  cout << "item:   " << item << endl;
  cout << "planet: " << s << endl;

  for (i = 1; i <= 10; i++) {
    result = s.HasEnough(item, i, 1);
    cout << " enough for " << i << " items?  " << ((result)? "yes" : "no");
    if (i > 6)
      report(!result);
    else
      report(result);
  }

  n = 1; d = 1;
  result = s.Remove(item, n, d);
  cout << "build " << n << " items!  " << ((result)? "yes" : "no");
  report(result);
  cout << "planet: " << s << endl;

  n = 2; d = 1;
  result = s.Remove(item, n, d);
  cout << "build " << n << " items!  " << ((result)? "yes" : "no");
  report(result);
  cout << "planet: " << s << endl;

  n = 5; d = 1;
  result = s.Remove(item, n, d);
  cout << "build " << n << " items!  " << ((result)? "yes" : "no");
  report(!result);
  cout << "planet: " << s << endl;

  n = 3; d = 1;
  result = s.Remove(item, n, d);
  cout << "build " << n << " items!  " << ((result)? "yes" : "no");
  report(result);
  cout << "planet: " << s << endl;

  cout << "--- scrapping back items ---" << endl;
  s.Add(item);
  s.Add(item);
  s.Add(item);
  cout << "planet: " << s << endl;
  s.Add(item);
  s.Add(item);
  cout << "planet: " << s << endl;
  s.Add(item);
  cout << "planet: " << s << endl;

  // check total
  cout << "validating total";
  report(s[Germanium] && s[Germanium]->Amount() == 100 &&
	 s[Ironium] && s[Ironium]->Amount() == 200 &&
	 s[Resources] && s[Resources]->Amount() == 1500);

  cout << "--- fleet hold capacity test ---" << endl;
  TSubstanceHold h;
  TSubstance* r = Fuel->Create(0); // temp container

  u = Cargo->Create(250); h.Add(*u, r); delete u;
  u = FTank->Create(1000); h.Add(*u, r); delete u;

  cout << "hold: " << h << endl;

  for (i = 0; i < 10; i++) {
    u = Ironium->Create(30); 
    cout << "Can add " << *u << "? ";
    result = h.CanAdd(*u);
    if (!result) {
      cout << "no! trying partial";
      report( (i>7)? !result : result );

      h.Add(*u, r);
      cout << "Could add: " << *r;

      if (i == 8)  report(r->Amount() == 10);
      if (i == 9)  report(r->Amount() == 0);
      if (r->Amount().Zero())
        break;
    } else {
      cout << "yes! adding...";
      h.Add(*u, r);
      report( (i<8)? result : !result );
    }
    delete u;

    cout << "hold: " << h << endl;
  }
  delete r;

  cout << "--- hold content removal test ---" << endl;

  cout << "hold: " << h << endl;

  for (i = 0; i < 10; i++) {
    u = Ironium->Create(40); 
    cout << "Can remove " << *u << "? ";
    result = h.CanRemove(*u);
    if (!result) {
      cout << "not enough! trying partial";       ;
      report( (i>5)? !result : result );

      h.Remove(*u, r, 1, 1);
      cout << "Could remove: " << *r;       ;

      if (i == 6)  report(r->Amount() == 10);
      if (i == 7)  report(r->Amount() == 0);
      if (r->Amount().Zero())
	break;

    } else {
      cout << "yes! removing...";
      h.Remove(*u, r);
      report( (i<6)? result : !result );
    }
    delete u;

    cout << "hold: " << h << endl;
  }

  cout << "--- hold space removal test ---" << endl;

  u = Germanium->Create(150); h.Add(*u, r); delete u;

  cout << "hold: " << h << endl;

  for (i = 0; i < 10; i++) {
    u = Cargo->Create(30); 
    cout << "Can remove " << *u << "? ";
    result = h.CanRemove(*u);
    if (!result) {
      cout << "not enough! trying partial";
      report( (i>2)? !result : result );

      h.Remove(*u, r, 1, 1);
      cout << "Could remove: " << *r;

      if (i == 3)  report(r->Amount() == 10);
      if (i == 4)  report(r->Amount() == 0);
      if (r->Amount().Zero())
	break;

    } else {
      cout << "yes! removing...";
      h.Remove(*u, r, 1, 1);
      report( (i<3)? result : !result );
    }
    delete u;

    cout << "hold: " << h << endl;
  }

  // TSubstanceType objects CANNOT be destroyed

  return success == checksdone;
}
