// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// position.cpp - copyright statement added 5/31/2000

#include "position.h"
#include "utils.h"

// constructors

Position::Position()
  : myRow(-1),
    myCol(-1)
// postcondition: Row() == -1, Col() == -1
{
}

Position::Position(int r, int c)
  : myRow(r),
    myCol(c)
// postcondition: Row() == r, Col() == c
{
}

// public accessing functions

int Position::Row() const
// postcondition: returns row of Position
{
  return myRow;
}

int Position::Col() const
// postcondition: returns column of Position
{
  return myCol;
}

Position Position::North() const
// postcondition: returns Position north of (up from) this position
{
  return Position(myRow - 1, myCol);
}

Position Position::Northeast() const
// postcondition: returns Position northeast of (up, right from) this position
{
  return Position(myRow - 1, myCol + 1);
}

Position Position::Northwest() const
// postcondition: returns Position northwest of (up, left from) this position
{
  return Position(myRow - 1, myCol - 1);  
}

Position Position::South() const
// postcondition: returns Position south of (down from) this position
{
  return Position(myRow + 1, myCol);
}

Position Position::Southeast() const
// postcondition: returns Position southeast of (down, right from) this position
{
  return Position(myRow + 1, myCol + 1);
}

Position Position::Southwest() const
// postcondition: returns Position southwest of (down, left from) this position
{
  return Position(myRow + 1, myCol - 1);  
}

Position Position::East() const
// postcondition: returns Position east (right) of this position
{
  return Position(myRow, myCol + 1);
}

Position Position::West() const
// postcondition: returns Position west (left) of this position
{
  return Position(myRow, myCol - 1);
}

bool Position::Equals(const Position & rhs) const
// postcondition: returns true iff this position equals rhs
{
  return myRow == rhs.myRow && myCol == rhs.myCol;
}

string Position::ToString() const
// postcondition: returns stringized form of Position
{
  string s = "(" + IntToString(myRow) + ","
               + IntToString(myCol) + ")";
  return s;

}

// free functions

ostream & operator << (ostream & out, const Position & pos)
// postcondition: pos inserted onto stream out
{
  out << pos.ToString();
  return out;
}

bool operator == (const Position & lhs, const Position & rhs)
// postcondition: returns true iff lhs == rhs
{
  return lhs.Equals(rhs);
}

bool operator != (const Position & lhs, const Position & rhs)
// postcondition: returns true iff lhs != rhs
{
  return ! lhs.Equals(rhs);
}


