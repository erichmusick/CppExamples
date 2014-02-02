// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// fish.h - copyright statement added 5/31/2000

#ifndef _FISH_H
#define _FISH_H

/**
  * The Fish class represents a fish/swimmer.  A fish has an integer id
  * and maintains its position in a grid. Both these pieces of information
  * are set by the constructor, and the id is never changed.
  * A Fish moves via the member function Move.
  *
  * A fish whose "amIDefined" field is false represents an "empty"
  * or "undefined" fish.  The IsUndefined() member function distinguishes
  * defined fish from undefined fish.  The default Fish() constructor
  * creates an empty/undefined fish.
  */

#include <iostream>
#include <string>
#include "position.h"
#include "nbrhood.h"

using namespace std;

// class declarations for those classes only used
// as references (passed by reference/const reference)

class Environment;

class Fish
{
  public:

    // constructors

    Fish();
      // postcondition: IsUndefined() == true

    Fish(int id, const Position & pos, int gender = 0);
      // postcondition: Location() returns pos, Id() returns id,
      //                IsUndefined() == false

    // accessing functions

    int Id() const;
      // precondition:  ! IsUndefined()
      // postcondition: returns id number of fish

    Position Location() const;
      // postcondition: returns current fish position

    Position Fish::OldLocation() const;
      // postcondition: returns previous fish position

    bool IsUndefined() const;
      // postcondition: returns true if constructed via default
      //                constructor, false otherwise

    string ToString() const;
      // postcondition: returns a stringized form of Fish

    char ShowMe() const;
      // postcondition: returns a character that can make me visible

    // modifying functions

    void Move(Environment & env);
      // precondition:  Fish stored in env at Location()
      // postcondition: Fish has moved to a new location in env (if possible)

    int Gender() const;      

    bool CanMate(const Environment & env) const;

    Neighborhood EmptyNeighbors(const Environment & env,
                                const Position & pos) const;      

  private:

    // helper functions
    Fish FindFishFromPosition(const Environment & env,
                                    const Position & pos) const;
    void AddIfEmpty(const Environment & env,
                    Neighborhood & nbrs, const Position & pos) const;

    int myId;
    Position myPos;
    Position myOldPos;
    bool amIDefined;
    int myGender;               // 0 = male; 1 = female
};

ostream & operator << (ostream & out, const Fish & fish);
  // postcondition: fish inserted onto stream out

#endif

