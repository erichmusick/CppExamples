// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// display.cpp - copyright statement added 5/31/2000

#include <iomanip>
#include <conio.h>
#include "display.h"
#include "environ.h"
#include "fish.h"
#include "utils.h"

#include "../../AP-CS-Misc/Common/CommonFunctions.h"

// constructor

Display::Display()
// postcondition: ready to display an Environment
{
}

// public modifying function

void Display::Show(const Environment & env, bool displayBorder, int startXlocation, int startYlocation)
// postcondition: state of env written as text to cout
{
  const int WIDTH = 1;  // for each fish

  int rows = env.NumRows();
  int cols = env.NumCols();
  int fishIndex = 0;
  int numFish;
  int r, c, i;

  Position pos;        // position of fish to be displayed next
  Position oldPosition;

  vector<Fish> fishList;
  fishList = env.AllFish();
  numFish = fishList.size();

  vector<Position> positionsToClear;

  // find position of first fish to be displayed (if any)
  if (fishIndex < numFish)
  {
    pos = fishList[fishIndex].Location();
    oldPosition = fishList[fishIndex].OldLocation();

  }

  // OUTPUT: Display border of fish environment
  if (displayBorder) {
    // Top border
    Common::GoToXY(startXlocation,startYlocation);
    cout << char(201);
    cout << setw(cols+1) << setfill(char(205));
    cout << char(187);
    cout << endl;

    // Bottom border
    Common::GoToXY(startXlocation,startYlocation + rows + 1);
    cout << char(200);
    cout << setw(cols+1) << setfill(char(205));
    cout << char(188);
    cout << endl;

    // OUTPUT: Display left and right border of fish environment
    for (r = 0; r < rows; r++) {
      Common::GoToXY(startXlocation,startYlocation + r + 1);
      cout << char(186);

	  Common::GoToXY(startXlocation + cols + 1, startYlocation + r + 1);
      cout << char(186);
    }

    startXlocation++;
    startYlocation++;
  }

  positionsToClear = env.PositionsToClear();

  for (i = 0; i < positionsToClear.size(); i++) {
    if (env.IsEmpty(positionsToClear[i]) && positionsToClear[i].Col() >= 0 && positionsToClear[i].Row() >= 0) {
		Common::GoToXY(startXlocation + positionsToClear[i].Col(), startYlocation + positionsToClear[i].Row());
      cout << setw(WIDTH) << ' ';
    }
  }

  for (r = 0; r < rows; r++)
  {
    // OUTPUT: Display left border of fish environment
    if (displayBorder) {

    }

    // OUTPUT: Display fish
    for (c = 0; c < cols; c++)
    {
      if (pos.Row() == r && pos.Col() == c)
      {
        // this is a position with a fish
        // old code: cout << setw(WIDTH) << fishList[fishIndex].ShowMe();
        if (env.IsEmpty(oldPosition) && oldPosition.Col() >= 0 && oldPosition.Row() >= 0) {
          // The old position is valid, not a negative coordinate
		  Common::GoToXY(startXlocation + oldPosition.Col(), startYlocation + oldPosition.Row());
          cout << setw(WIDTH) << ' ';
        }

		Common::GoToXY(startXlocation + c, startYlocation + r);
        cout << fishList[fishIndex].ShowMe();
        fishIndex++;

        // find position of next fish to be displayed
        if (fishIndex < numFish)
        {
          pos = fishList[fishIndex].Location();
          oldPosition = fishList[fishIndex].OldLocation();
        }
        else  // no more fish to display
        {
          pos = Position();   // not in the grid, won't be displayed
        }
      }
      else  // this position has no fish
      {
//        cout << setw(WIDTH) << ' ';
      }
    }  // finished processing all columns in a row
  }  // finished processing all rows in the grid

  // Go to the line after the environment so text from cout isn't displayed
  // at the location of the last fish displayed
  Common::GoToXY(1, startYlocation + rows + 2);

}

