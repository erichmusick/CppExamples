// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// aquafish.h - copyright statement added 5/31/2000

#ifndef _AQUAFISH_H
#define _AQUAFISH_H

#include <vector>

using namespace std;

class AquaFish
{
  public:

    // CONSTRUCTORS:
      AquaFish(int tankSize);    
      AquaFish(int tankSize, int startPosition);

    // METHODS:
      void Swim();               // Swim one foot.
      int BumpCount() const;     // Return the bump count.
      int GetCount(int location);// Return value in myPositionCount for location
      void ResetCounts();        // Reset positionCount and myBumpCount
      int MinPos();              // Return minimum position in the tank
      int MaxPos();              // Return maximum position in the tank
      int Location();            // Return current location of fish

  private:
    int myPosition;              // Current position of fish
    int myMinimumPosition;       // Minimum position of fish
    int myMaximumPosition;       // Maximum position of fish
    int myBumpCount;             // Number of times fish has bumped into walls
    int myTankSize;              // Size of fish tank
    bool myDebugging;            // Display debugging output (true/false)
    vector<int> myPositionCount;// No. of times fish has been at each location
};

#endif