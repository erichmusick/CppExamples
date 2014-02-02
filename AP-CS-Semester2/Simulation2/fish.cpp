// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// fish.cpp - copyright statement added 5/31/2000

#include "fish.h"
#include "environ.h"
#include "randgen.h"
#include "position.h"
#include "nbrhood.h"
#include "utils.h"

// constructors

Fish::Fish()
  : myId(0),
    amIDefined(false)
// postcondition: IsUndefined() == true
{

}

Fish::Fish(int id, const Position & pos, int gender)
  : myId(id),
    myPos(pos),
    amIDefined(true),
    myGender(gender)
// postcondition: Location() returns pos, Id() returns id,
//                IsUndefined() == false
{

}

// public accessing functions

int Fish::Id() const
// precondition:  ! IsUndefined()
// postcondition: returns id number of fish
{
  return myId;
}

int Fish::Gender() const
// postcondition: returns fish's gender
{
  return myGender;
}

Position Fish::Location() const
// postcondition: returns current fish position
{
  return myPos;
}

Position Fish::OldLocation() const
// postcondition: returns previous fish position
{
  return myOldPos;
}

bool Fish::IsUndefined() const
// postcondition: returns true if constructed via default constructor,
//                false otherwise
{
  return ! amIDefined;
}

string Fish::ToString() const
// postcondition: returns a stringized form of Fish
{
  return IntToString(myId) + " " + myPos.ToString();
}

// public modifying functions

void Fish::Move(Environment & env)
// precondition:  Fish stored in env at Location()
// postcondition: Fish has moved to a new location in env (if possible)
{
  RandGen randomVals;
  Neighborhood nbrs = EmptyNeighbors(env, myPos);
  DebugPrint(3, nbrs.ToString());

  if (nbrs.Size() > 0)
  {
    // there were some empty neighbors, so randomly choose one
    myOldPos = myPos;
    myPos = nbrs.Select(randomVals.RandInt(0, nbrs.Size() - 1));
    DebugPrint(1, "Fish at " + myOldPos.ToString() + " moves to " + myPos.ToString());

    env.Update(myOldPos, *this); // *this means this fish

  }
  else
  {
    DebugPrint(1, "Fish " + ToString() + " can't move.");
  }
}

char Fish::ShowMe() const
// postcondition: returns a character that can make me visible
{
  if (1 <= Id() && Id() <= 26)
  {
    return 'A' + (Id() - 1);

  }
  return '*';
}

bool Fish::CanMate(const Environment &env) const
// postcondition: returns a Neighborhood of pos
{
  Neighborhood nbrs;
  Fish neighboringFish;
  bool canMate = false;
  int i;

  if (!env.IsEmpty(myPos.North())) {
    nbrs.Add(myPos.North());
  }
  if (!env.IsEmpty(myPos.Northwest())) {
    nbrs.Add(myPos.Northwest());
  }
  if (!env.IsEmpty(myPos.Northeast())) {
    nbrs.Add(myPos.Northeast());
  }
  if (!env.IsEmpty(myPos.South())) {
    nbrs.Add(myPos.South());
  }
  if (!env.IsEmpty(myPos.Southwest())) {
    nbrs.Add(myPos.Southwest());
  }
  if (!env.IsEmpty(myPos.Southeast())) {
    nbrs.Add(myPos.Southeast());
  }

  i = 0;
  while (canMate == false && i < nbrs.Size()) {
    neighboringFish = FindFishFromPosition(env,nbrs.Select(i));
    if (!neighboringFish.IsUndefined() && neighboringFish.Gender() != myGender) {
      canMate = true;
    }
    i++;
  }
  
  return canMate;

}

Neighborhood Fish::EmptyNeighbors(const Environment & env,
                                  const Position & pos) const
//  precondition:  pos is in the grid being modelled
//  postcondition: returns a Neighborhood of pos of empty positions
{
  Neighborhood nbrs;

  AddIfEmpty(env, nbrs, pos.North());
  AddIfEmpty(env, nbrs, pos.Northwest());
  AddIfEmpty(env, nbrs, pos.Northeast());
  AddIfEmpty(env, nbrs, pos.South());
  AddIfEmpty(env, nbrs, pos.Southwest());
  AddIfEmpty(env, nbrs, pos.Southeast());
  AddIfEmpty(env, nbrs, pos.East());
  AddIfEmpty(env, nbrs, pos.West());
  
  return nbrs;
}

// private helper functions

Fish Fish::FindFishFromPosition(const Environment & env,
                                  const Position & pos) const
{
  Fish undefFish;
  vector<Fish> theFish;
  int i;

  theFish = env.AllFish();
  for (i = 0; i < theFish.size(); i++) {
    if (theFish[i].Location() == pos) {
      return theFish[i];
    }
  }
  
  return undefFish;
}

void Fish::AddIfEmpty(const Environment & env,
                      Neighborhood & nbrs, const Position & pos) const
// postcondition: pos is added to nbrs if pos in env and empty
{
  if (env.IsEmpty(pos))
  {
    nbrs.Add(pos);
  }
}

// free functions

ostream & operator << (ostream & out, const Fish & fish)
// postcondition: fish inserted onto stream out
{
  out << fish.ToString();
  return out;
}




