// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// utils.h - copyright statement added 5/31/2000

#ifndef _UTILS_H
#define _UTILS_H

#include <string>
#include <vector>
#include "fish.h"

using namespace std;

// Collection of useful utility functions

string IntToString(int n);
  // postcondition: returns stringized form of n

void Sort(vector<Fish> & list, int numElts);
  // precondition:  list contains numElts Fish
  // postcondition: list sorted so that entries are
  //                in order top-down/left-right by Position

void DebugPrint(int level, const string & msg);
  // print the given debugging error message if level is low enough
  //   (which levels are actually printed can be set in utils.cpp)

#endif

