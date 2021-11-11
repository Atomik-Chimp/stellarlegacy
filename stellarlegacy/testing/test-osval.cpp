// $Id: test-osval.cpp,v 1.1 2001/04/13 21:56:54 ishark Exp $

// OSval class testing
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

#include "common/osval.h"


static int2 success;
static int2 checksdone; 


static
void report(const bool check)
{
  cout << " ... " << ((check)? "Success" : "FAILED") << endl;
  checksdone++;
  success += check;
}



bool TestOSValClass()
{
  TOSVal v1, v2, v3;
  int4 i, n, d;
  success = 0;

  v1 = 600000000;
  v2 = 0;

  cout << "------- test 1 -------" << endl;

  for (i = 0; i < 6; i++) {
    cout << v2 << "+" << v1 << " = ";
    v2 += v1;
    cout << v2;

    switch(i) {
    case 0:
      report(v2 == 600000000);
      break;
    case 1:
      report(v2 == 1200000000);
      break;
    case 2:
      report(v2 == 1800000000);
      break;
    case 3:
      report(v2 == TOSVal::iMaximum);
      break;
    case 4:
      report(v2 == TOSVal::iMaximum);
      break;
    case 5:
      report(v2 == TOSVal::iMaximum);
      break;
    }
  }

  for (i = 0; i < 6; i++) {
    cout << v2 << "-" << v1 << " = ";
    v2 -= v1;
    cout << v2;

    switch(i) {
    case 0:
      report(v2 == 1400000000);
      break;
    case 1:
      report(v2 == 800000000);
      break;
    case 2:
      report(v2 == 200000000);
      break;
    case 3:
      report(v2 == -400000000);
      break;
    case 4:
      report(v2 == -1000000000);
      break;
    case 5:
      report(v2 == -1600000000);
      break;
    }
  }

  v1 = -600000000;
  v2 = 0;

  for (i = 0; i < 6; i++) {
    cout << v2 << "+(" << v1 << ") = ";
    v2 += v1;
    cout << v2;

    switch(i) {
    case 0:
      report(v2 == -600000000);
      break;
    case 1:
      report(v2 == -1200000000);
      break;
    case 2:
      report(v2 == -1800000000);
      break;
    case 3:
      report(v2 == -TOSVal::iMaximum);
      break;
    case 4:
      report(v2 == -TOSVal::iMaximum);
      break;
    case 5:
      report(v2 == -TOSVal::iMaximum);
      break;
    }
  }

  for (i = 0; i < 6; i++) {
    cout << v2 << "-(" << v1 << ") = ";
    v2 -= v1;
    cout << v2;

    switch(i) {
    case 0:
      report(v2 == -1400000000);
      break;
    case 1:
      report(v2 == -800000000);
      break;
    case 2:
      report(v2 == -200000000);
      break;
    case 3:
      report(v2 == 400000000);
      break;
    case 4:
      report(v2 == 1000000000);
      break;
    case 5:
      report(v2 == 1600000000);
      break;
    }
  }

  cout << "------- test 2 -------" << endl;

  v1 = TOSVal::iInfinity;
  v2 = TOSVal::iMaximum;
  v3 = v1 + v2;
  cout << v1 << "+" << v2 << "=" << v3;
  report(v3 == TOSVal::iInfinity);
  v3 = v2 + v1;
  cout << v2 << "+" << v1 << "=" << v3;
  report(v3 == TOSVal::iInfinity);

  v1 = TOSVal::iMaximum;
  v2 = TOSVal::iInfinity;
  v3 = v1 + v2;
  cout << v1 << "+" << v2 << "=" << v3;
  report(v3 == TOSVal::iInfinity);
  v3 = v2 + v1;
  cout << v2 << "+" << v1 << "=" << v3;
  report(v3 == TOSVal::iInfinity);

  v1 = TOSVal::iInfinity;
  v2 = TOSVal::iMaximum;
  v3 = v1 - v2;
  cout << v1 << "-" << v2 << "=" << v3;
  report(v3 == TOSVal::iInfinity);
  v3 = v2 - v1;
  cout << v2 << "-" << v1 << "=" << v3;
  report(v3 == -TOSVal::iInfinity);

  v1 = TOSVal::iMaximum;
  v2 = TOSVal::iInfinity;
  v3 = v1 - v2;
  cout << v1 << "-" << v2 << "=" << v3;
  report(v3 == -TOSVal::iInfinity);
  v3 = v2 - v1;
  cout << v2 << "-" << v1 << "=" << v3;
  report(v3 == TOSVal::iInfinity);

  cout << "------- test 3 -------" << endl;

  v1 = 100000;
  n = 2800; d = 1000;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 280000);

  v1 = 1000000;
  n = 2800; d = 1000;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 2800000);

  v1 = 10000000;
  n = 2800; d = 1000;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 28000000);

  v1 = 100000000;
  n = 2800; d = 1000;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 280000000);

  v1 = 1000000000;
  n = 2800; d = 1000;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == TOSVal::iMaximum);

  v1 = TOSVal::iMaximum;
  n = 2800; d = 1000;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == TOSVal::iMaximum);

  v1 = 100000;
  n = 2520; d = 900;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 280000);

  v1 = 1000000;
  n = 2520; d = 900;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 2799720);

  v1 = 10000000;
  n = 2520; d = 900;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 27999720);

  v1 = 100000000;
  n = 2520; d = 900;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == 279999720);

  v1 = 1000000000;
  n = 2520; d = 900;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == TOSVal::iMaximum);

  v1 = TOSVal::iMaximum;
  n = -2520; d = 900;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == -TOSVal::iMaximum);

  v1 = 100;
  n = 1; d = 0;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == TOSVal::iInfinity);

  v1 = 100;
  n = -1; d = 0;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == -TOSVal::iInfinity);

  v1 = -100;
  n = 1; d = 0;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == -TOSVal::iInfinity);

  v1 = -TOSVal::iInfinity;
  n = 1; d = 0;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == -TOSVal::iInfinity);

  v1 = TOSVal::iInfinity;
  n = 0; d = 1;
  v2 = v1.Scale(n, d);
  cout << v1 << " * (" << n << "/" << d << ") = " << v2;
  report(v2 == TOSVal::iInfinity);

  return success == checksdone;
}
