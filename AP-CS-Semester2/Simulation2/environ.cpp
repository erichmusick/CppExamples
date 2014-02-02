// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// environ.cpp - copyright statement added 5/31/2000

#include "environ.h"
#include "fish.h"
#include "utils.h"
#include "randgen.h"

// constructor

Environment::Environment(istream & input)
  : myWorld(0,0),
    myFishCreated(0),
    myFishCount(0)
// precondition:  input is open for reading, in correct format
// postcondition: environment initialized and populated from input
{
  int numRows, numCols, row, col;
  RandGen r;

  if (input >> numRows >> numCols)    // resize the matrix
  {
    myWorld.resize(numRows, numCols);
  }
  else
  {
    cerr << "reading rows/columns failed in Environment" << endl;
    exit(1);
  }
  while (input >> row >> col)
  {
    AddFish(Position(row, col),r.RandInt(0,1));
  }
}

// public accessing functions

int Environment::NumRows() const
// postcondition: returns # rows in grid
{
  return myWorld.numrows();
}

int Environment::NumCols() const
// postcondition: returns # columns in grid
{
  return myWorld.numcols();
}

vector<Fish> Environment::AllFish() const
// postcondition: returned vector (call it fishList) contains all fish
//                in top-down, left-right order:
//                top-left fish in fishList[0],
//                bottom-right fish in fishList[fishList.length()-1];
//                # fish in environment is fishList.length()
{
  vector<Fish> fishList(myFishCount);
  int r, c, k;
  int count = 0;
  string s = "";

  // look at all grid positions, store fish found in vector fishList

  for (r = 0; r < NumRows(); r++)
  {
    for (c = 0; c < NumCols(); c++)
    {
      if (! myWorld[r][c].IsUndefined())
      {
        fishList[count] = myWorld[r][c];
        count++;
      }
    }
  }

  /*
  for (c = NumCols() - 1; c >= 0; c--)
  {
    for (r = NumRows() - 1; r >= 0; r--)
    {
      if (! myWorld[r][c].IsUndefined())
      {
        fishList[count] = myWorld[r][c];
        count++;
      }
    }
  }*/

  for (k = 0; k < count; k++)
  {
    s += fishList[k].Location().ToString() + " ";
  }
  DebugPrint(5, "Fish vector = " + s);
  return fishList;
}

bool Environment::IsEmpty(const Position & pos) const
// postcondition: returns true if pos in grid and no fish at pos,
//                returns false otherwise
{
  if (! InRange(pos))
  {
    return false;    // debug msg printed in InRange
  }
  
  if (myWorld[pos.Row()][pos.Col()].IsUndefined())
  {
    return true;    // pos in grid and no fish at pos
  }
  
  DebugPrint(5, pos.ToString() + " contains a fish.");
  return false;
}

// public modifying functions

void Environment::Update(const Position & oldLoc, Fish & fish)
// precondition:  fish was located at oldLoc, has been updated
// postcondition: if (fish.Location() != oldLoc) then oldLoc is empty;
//                Fish fish is updated properly in this environment
{
  Fish emptyFish;

  if (InRange(oldLoc))
  {
    if (myWorld[oldLoc.Row()][oldLoc.Col()].Id() != fish.Id())
    {
      cerr << "illegal fish move" << endl;
    }
    else
    {
      // Put an updated copy of fish in fish's current position.
      Position newLoc = fish.Location();
      myWorld[newLoc.Row()][newLoc.Col()] = fish;

      // If fish moved, empty out fish's old location.
      if (oldLoc != newLoc)
      {
        myWorld[oldLoc.Row()][oldLoc.Col()] = emptyFish;
      }
    }
  }
}

void Environment::AddFish(const Position & pos, int gender)
// precondition:  no fish already at pos, i.e., IsEmpty(pos)
// postcondition: fish created at pos
{
  if (! IsEmpty(pos))
  {
    cerr << "error, attempt to create fish at non-empty: " << pos << endl;
    return;
  }
  myFishCreated++;
  myWorld[pos.Row()][pos.Col()] = Fish(myFishCreated, pos, gender);
  myFishCount++;
}

void Environment::RemoveFish(Fish &fish) {
  Position pos;
  Position oldPos;
  Fish undefFish;

  pos = fish.Location();
  oldPos = fish.OldLocation();

  myFishCount--;
  myWorld[pos.Row()][pos.Col()] = undefFish;

  myNeedToClear.resize(myNeedToClear.size() + 1);
  myNeedToClear[myNeedToClear.size() - 1] = oldPos;  

}

vector<Position> Environment::PositionsToClear() const {

  vector<Position> returnValue;
  returnValue = myNeedToClear;

  // myNeedToClear.resize(0);

  return returnValue;   
}


// private helper functions

bool Environment::InRange(const Position & pos) const
// postcondition: returns true if pos is in the grid,
//                returns false otherwise
{
  if (0 <= pos.Row() && pos.Row() < NumRows() &&
      0 <= pos.Col() && pos.Col() < NumCols())
  {
    return true;
  }

  DebugPrint(5, pos.ToString() + " is out of range.");
  return false;
}