// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// aquafish.cpp - copyright statement added 5/31/2000

#include <iostream>
#include "aquafish.h"
#include "randgen.h"

using namespace std;

AquaFish::AquaFish(int tankSize)
  : myPosition(tankSize/2),
    myMinimumPosition(tankSize/2),
    myMaximumPosition(tankSize/2),
    myTankSize(tankSize),
    myBumpCount(0),
    myDebugging(false)
{

}

AquaFish::AquaFish(int tankSize, int startPosition)
  : myPosition(startPosition),
    myMinimumPosition(startPosition),
    myMaximumPosition(startPosition),
    myTankSize(tankSize),
    myBumpCount(0),
    myDebugging(false)
{

}

void AquaFish::Swim()
{
  RandGen randomVals;
  int flip;

  if (myPositionCount.size() != myTankSize) {
    myPositionCount.resize(myTankSize);
    ResetCounts();
  }

  if (myTankSize > 1) {
    if (myPosition == myTankSize - 1)
    {
      myPosition--;
    }
    else if (myPosition == 0)
    {
      myPosition++;
    }
    else
    {
      flip = randomVals.RandInt(3);

      if (flip == 0)
      {
        myPosition++;
      }
      else if (flip == 1)
      {
        myPosition--;
      }
      else
      {
        // Got a 3, fish stays in same position, no increment/decrement needed
      }
    }
  }
  myPositionCount[myPosition]++;
  
  if (myDebugging)
  {
    cout << "*** Position = " << myPosition << endl;
  }
  
  if (myPosition == 0 || myPosition == myTankSize - 1)
  {
    // Fish is at one end of the tank and has run into a wall, incr. bump count
    myBumpCount++;
  }

  if (myPosition < myMinimumPosition)
  {
    // The current position is less than the minimum position, change the
    //   minimum position to the current position
    myMinimumPosition = myPosition;
  }

  if (myPosition > myMaximumPosition)
  {
    // The current position is greater than the maximum position, change the
    //   maximum position to the current position
    myMaximumPosition = myPosition;
  }

  return;
}

int AquaFish::BumpCount() const
{
  return myBumpCount;
}

int AquaFish::GetCount(int location)
{

  int maxIndex;
  int locationCount;

  maxIndex = myPositionCount.size() - 1;

  if (location > maxIndex) {
    locationCount = -1;
  }
  else {
    locationCount = myPositionCount[location];
  }

  return locationCount;

}

void AquaFish::ResetCounts()
{

  int index;
  int vectorLength;

  // RESET VECTOR COUNT
  vectorLength = myPositionCount.size();

  for (index = 0; index < vectorLength; index++) {
    myPositionCount[index] = 0;
  }

  // RESET BUMP COUNT
  myBumpCount = 0;

  return;

}

int AquaFish::MinPos()
{
  // Return the minimum position of the fish
  return myMinimumPosition;
}

int AquaFish::MaxPos()
{
  // Return the maximum position of the fish
  return myMaximumPosition;
}

int AquaFish::Location()
{
  // Return the current position of the fish
  return myPosition;
}
