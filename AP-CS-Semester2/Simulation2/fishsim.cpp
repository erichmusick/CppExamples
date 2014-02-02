// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// fishsim.cpp - copyright statement added 5/31/2000

/****  I N C L U D E   F I L E S  ****/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector> // erichmusick
#include <Windows.h> // erichmusick

#include "environ.h"
#include "display.h"
#include "simulate.h"
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****  F U N C T I O N   P R O T O T Y P E S  ****/
void pressEnterToContinue();

/**** F U N C T I O N S ****/

// PRESS ENTER TO CONTINUE
/* Purpose    - Pause the program until the user presses enter
 * Parameters - None.
 * Input      - Program waits for user to press enter before continuing
 * Process    - Program waits for user to press enter before continuing
 * Output     - None.
 * Return     - None.
 */
void pressEnterToContinue() {

  char key;

  cout << "\nPress ENTER to continue...";

  key = 'a';
  while (int(key) != 13) {
    key = char(_getch());
    if (key == 0) {
      key = char(_getch());
    }
  }

  return;

}

/**** M A I N ****/

int main()
{

  // Get initial environment settings
  char setEnv;
  int numRows;
  int numCols;
  int numFish;
  int index;
  vector<int> fishRow;
  vector<int> fishCol;

  cout << "Would you like to define an environment? (Y/N; N uses current ";
  cout << "settings in\nfish.dat)\n? ";
  cin >> setEnv;
  cout << endl;

  if (toupper(setEnv) == 'Y') {
    do {
      cout << "Number of rows? ";
      cin >> numRows;
    } while (numRows <= 0 || numRows >= 46);

    do {
      cout << "Number of columns? ";
      cin >> numCols;
    } while (numCols <= 0 || numCols >= 78);

    do {
      cout << "Number of fish? ";
      cin >> numFish;
    } while (numFish < 0);

    if (numFish != 0) {
      fishRow.resize(numFish);
      fishCol.resize(numFish);
    }

    for (index = 0; index < numFish; index++) {
      do {
        cout << "Fish ";
        cout << index + 1;
        cout << " initial row: ";
        cin >> fishRow[index];
      } while (fishRow[index] < 0 || fishRow[index] >= numRows);

      do {
        cout << "Fish ";
        cout << index + 1;
        cout << " initial column: ";
        cin >> fishCol[index];
      } while (fishCol[index] < 0 || fishCol[index] >= numCols);
    }

    ofstream output;

    output.open("fish.dat");

    if (!output) {
      cerr << "Unable to open fish.dat.";
    }
    else {
      output << numRows << " " << numCols << endl;
      for (index = 0; index < numFish; index++) {
        output << fishRow[index] << " " << fishCol[index] << endl;
      }
    }

    output.close();

  }

  // replace filename below with appropriate file (full path if necessary)
  ifstream input("fish.dat");
  Environment env(input);

  //Display display(100,100); // for graphics display
  Display display; // for text display
  string s;

  Simulation sim;

  int step;
  int numSteps;
  char displaySim;
  int stepTime;

  // INPUT: Get number of times the fish should move
  do {
    cout << "Steps in simulation? ";
    cin >> numSteps;
  } while (numSteps < 0);

  // INPUT: Display the movement of the fish?
    // commented out at this time because there is no point in not
    // displaying the simulation at this point in time
  /* do {
    cout << "Display Simulation (Show each move of the fish) (y/n)? ";
    cin >> displaySim;
    displaySim = toupper(displaySim);
  } while (displaySim != 'Y' && displaySim != 'N'); */
  displaySim = 'Y';

  if (displaySim == 'Y') {    // User wants to display the movement of the fish
    // INPUT: Get amount to pause before each "step"/move
    do {
      cout << "Time between steps (in milliseconds)? ";
      cin >> stepTime;
    } while (stepTime < 0);
  }

  pressEnterToContinue();

  if (displaySim == 'Y') {

    //_setcursortype(0);

    Common::ClearScreen();
    display.Show(env, true);
    cout << "Press a key to end simulation early";
    Sleep(stepTime);
  }

  for (step = 0; step < numSteps; step++)
  {
    sim.Step(env);

    if (displaySim == 'Y') {
      display.Show(env, false, 2, 2);
      Sleep(stepTime);      
    }
    else {
      if (step == 0) {
        cout << "Simulating guppy movement. Please wait...\n";
        cout << "Press a key to end simulation early";
      }
    }
    if (_kbhit()) {
      _getch();
      //__flush_win95_keyup_events();
      break;
    }
  }

  //_setcursortype(2);

  return 0;
}


