// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// nbrhood.cpp - copyright statement added 5/31/2000

#include "nbrhood.h"
#include "utils.h"

// constructor

Neighborhood::Neighborhood()
  : myList(4),
    myCount(0)
// postcondition: Size() == 0
{

}

// public accessing functions

int Neighborhood::Size() const
// postcondition: returns # Positions in the neighborhood
{
  return myCount;
}

Position Neighborhood::Select(int index) const
// precondition:  0 <= index < Size()
// postcondition: returns the index-th Position in Neighborhood
{
  DebugPrint(5, "Selecting neighborhood element # " + IntToString(index));
  return myList[index];
}


string Neighborhood::ToString() const
// postcondition: returns a string version of all Positions in Neighborhood
{
  string s = "Neighborhood: ";
  int k;
  for (k = 0; k < myCount; k++)
  {
    s += myList[k].ToString() + " ";
  }
  return s;
}

// public modifying function

void Neighborhood::Add(const Position & pos)
// precondition:  there is room in the neighborhood
// postcondition: pos added to Neighorhood
{
  if (myCount < myList.size())
  {
    DebugPrint(5, "Adding " + pos.ToString() + " to neighborhood.");
    myList[myCount] = pos;
    myCount++;
  }
  else
  {
    DebugPrint(5, "Neighborhood had no room for " + pos.ToString());
  }
}

// free function

ostream & operator << (ostream & out, const Neighborhood & nbrhood)
// postcondition: nbrhood inserted onto stream out
{
  out << nbrhood.ToString();
  return out;
}

