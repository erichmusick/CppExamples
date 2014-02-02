// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// aquamain.cpp - copyright statement added 5/31/2000

#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include "aquafish.h"
#include <Windows.h>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

// DISPLAY FISH
/* Purpose    - Display the current location of fish
* Parameters - oldXlocation - the old location of the fish
*            - newXlocation - the new location of the fish
*            - yLocation - the vertical location of the fish
* Input      - None.
* Process    - None.
* Output     - Displays a space in the fish's old location, displays a c
*                character that looks like a fish in the new location.
* Return     - None.
*/
void displayFish(int oldXlocation, int newXlocation, int yLocation) {

	Common::GoToXY(oldXlocation, yLocation);
	cout << " ";

	Common::GoToXY(newXlocation, yLocation);
	cout << char(224);

	return;

}

int main()
{
	int tankSize;
	int stepsPerSim;
	char displaySim;
	int step;
	int stepTime;
	int fishIndex;
	int fishXoldLocation;
	int fishXlocation;
	int fishYlocation;
	int startYlocation;
	int startLocationConst;

	// INPUT: Get the size of the fish tank
	do {
		cout << "Tank size (less than 78)? ";
		cin >> tankSize;
	} while (tankSize <= 0 || tankSize > 77);

	// INPUT: Get number of times the fish should move
	do {
		cout << "Steps in simulation? ";
		cin >> stepsPerSim;
	} while (stepsPerSim <= 0);

	// INPUT: Display the movement of the fish?
	do {
		cout << "Display Simulation (Show each move of the fish) (y/n)? ";
		cin >> displaySim;
		displaySim = toupper(displaySim);
	} while (displaySim != 'Y' && displaySim != 'N');

	if (displaySim == 'Y') {    // User wants to display the movement of the fish
		// INPUT: Get amount to pause before each "step"/move
		do {
			cout << "Time between steps (in milliseconds)? ";
			cin >> stepTime;
		} while (stepTime < 0);
	}

	cout << endl;

	// PROCESS: Calculate a constant to use in calculating the initial location of
	// each fish. The instructions said that each fish would begin at 7*fishIndex,
	// but that is restrictive because it requires that the tank be no smaller
	// than 57. Using this constant value instead allows for a tank of any size.
	startLocationConst = tankSize / 9;

	AquaFish guppy1(tankSize, startLocationConst * 0);
	AquaFish guppy2(tankSize, startLocationConst * 1);
	AquaFish guppy3(tankSize, startLocationConst * 2);
	AquaFish guppy4(tankSize, startLocationConst * 3);
	AquaFish guppy5(tankSize, startLocationConst * 4);
	AquaFish guppy6(tankSize, startLocationConst * 5);
	AquaFish guppy7(tankSize, startLocationConst * 6);
	AquaFish guppy8(tankSize, startLocationConst * 7);
	AquaFish guppy9(tankSize, startLocationConst * 8);
	string tankSide(tankSize + 2, '*');

	AquaFish *guppies[9] = { &guppy1, &guppy2, &guppy3, &guppy4,
		&guppy5, &guppy6, &guppy7, &guppy8, &guppy9 };

	if (displaySim == 'Y') {    // User wants to display movement of fish
		// OUTPUT: Display the top of the fish tank
		cout << tankSide;

		// PROCESS: Set the cursor type to no cursor, so the cursor isn't seen while
		// displaying the movement of the fish.
		// _setcursortype(0);
	}
	else {                      // User doesn't want to display movement of fish
		// OUTPUT: Inform user that computer is performing the simulation and asks
		// them to wait
		cout << "Simulating guppy movement. Please wait...";
	}
	cout << endl;

	startYlocation = Common::GetCursorYPosition();

	if (displaySim == 'Y') {
		// OUTPUT: Display bottom of tank.
		Common::GoToXY(0, startYlocation + 8);
		cout << endl;
		cout << tankSide;
		cout << endl;
		cout << "Press a key to stop simulation early.";

		for (fishIndex = 0; fishIndex < 9; fishIndex++) {
			// PROCESS: Determine initial x and y locations
			fishXlocation = startLocationConst * fishIndex + 1;
			fishYlocation = startYlocation + fishIndex;

			// OUTPUT: Display the sides of the tank
			Common::GoToXY(0, fishYlocation);
			cout << '*';
			Common::GoToXY(tankSize + 1, fishYlocation);
			cout << '*';

			// OUTPUT: Display the initial position of the fish
			displayFish(fishXlocation, fishXlocation, fishYlocation);
		}

		// PROCESS: Pause the program after initial fish location is displayed for
		// the amount of time previously specified by the user
		Sleep(stepTime);
	}

	// PROCESS: Simulate fish movement
	for (step = 0; step < stepsPerSim; step++) {
		for (fishIndex = 0; fishIndex < 9; fishIndex++) {
			if (displaySim == 'Y') {
				// If the user wants to display the fish movement, get the current
				// location of the fish before this move, so the old location can be
				// cleared before displaying the fish in the new location.
				fishXoldLocation = guppies[fishIndex]->Location() + 1;
			}

			// PROCESS: Make the fish swim - swims either right, left, or stays in its
			// current location
			guppies[fishIndex]->Swim();

			if (displaySim == 'Y') {
				// If the user wants to display the fish movement, get the current
				// location of the fish (the new location) as well as the line number
				// on which to display the fish.
				fishXlocation = guppies[fishIndex]->Location() + 1;
				fishYlocation = startYlocation + fishIndex;

				// DISPLAY: Call the displayFish function, which displays a space in the
				// old fish location and then displays the fish in the new location
				displayFish(fishXoldLocation, fishXlocation, fishYlocation);
			}
		}
		if (_kbhit()) {            // User has pressed a key, quit simulation
			_getch();
			Sleep(100);
			//__flush_win95_keyup_events();
			break;
		}
		if (displaySim == 'Y') {  // User wants to display fish movement
			// PROCESS: Pause the program after fish swims for the amount of time
			// previously specified by the user
			Sleep(stepTime);
		}
	}

	// Change the cursor back to a blinking curson
	//_setcursortype(2);


	// OUTPUT: Display a table of stats
	if (displaySim == 'Y') {
		Common::GoToXY(0, startYlocation + 12);
	}
	else {
		cout << endl;
		cout << endl;
	}
	cout << "STATS:\n";
	cout << "Number of Moves: ";
	cout << step;
	cout << endl;
	cout << "Guppy  Start Position  Minimum Position  Maximum Position  Bump Count\n";
	cout << "=====  ==============  ================  ================  ==========\n";
	for (fishIndex = 0; fishIndex < 9; fishIndex++) {
		cout << setw(5);
		cout << fishIndex + 1;

		cout << "  ";

		cout << setw(14);
		cout << startLocationConst*fishIndex;

		cout << "  ";

		cout << setw(16);
		cout << guppies[fishIndex]->MinPos();

		cout << "  ";

		cout << setw(16);
		cout << guppies[fishIndex]->MaxPos();

		cout << "  ";

		cout << setw(10);
		cout << guppies[fishIndex]->BumpCount();

		cout << endl;
	}

	return 0;
}

/************************* S A M P L E  O U T P U T **************************/

/*              LAB215 by 413 ERICH MUSICK   11:04 on Apr  8 2002

Tank size (less than 78)? 25
Steps in simulation? 250
Display Simulation (Show each move of the fish) (y/n)? y
Time between steps (in milliseconds)? 0

***************************
*                _        *
*   _                     *
*                     _   *
*                _        *
*    _                    *
* _                       *
*                   _     *
*  _                      *
*                  _      *
***************************
Press a key to stop simulation early.

STATS:
Number of Moves: 250
Guppy  Start Position  Minimum Position  Maximum Position  Bump Count
=====  ==============  ================  ================  ==========
1               0                 0                18           4
2               2                 0                13           2
3               4                 0                24           9
4               6                 0                18          22
5               8                 0                13           9
6              10                 0                11           7
7              12                12                24          10
8              14                 0                20           6
9              16                15                24          13

'Esc' closes window.*/

/*              LAB215 by 413 ERICH MUSICK   11:04 on Apr  8 2002

Tank size (less than 78)? 55
Steps in simulation? 25000
Display Simulation (Show each move of the fish) (y/n)? y
Time between steps (in milliseconds)? 100

*********************************************************
*           _                                           *
*   _                                                   *
*                    _                                  *
*                            _                          *
*                        _                              *
*                                               _       *
*                                                    _  *
*                                              _        *
*                                                  _    *
*********************************************************
Press a key to stop simulation early.

STATS:
Number of Moves: 83
Guppy  Start Position  Minimum Position  Maximum Position  Bump Count
=====  ==============  ================  ================  ==========
1               0                 0                13           0
2               6                 0                 6           5
3              12                12                20           0
4              18                13                28           0
5              24                20                27           0
6              30                29                48           0
7              36                36                53           0
8              42                37                50           0
9              48                42                50           0

'Esc' closes window.*/

/*              LAB215 by 413 ERICH MUSICK   11:04 on Apr  8 2002

Tank size (less than 78)? 60
Steps in simulation? 23
Display Simulation (Show each move of the fish) (y/n)? n

Simulating guppy movement. Please wait...


STATS:
Number of Moves: 23
Guppy  Start Position  Minimum Position  Maximum Position  Bump Count
=====  ==============  ================  ================  ==========
1               0                 0                 7           4
2               6                 5                11           0
3              12                10                13           0
4              18                17                23           0
5              24                20                24           0
6              30                29                32           0
7              36                32                37           0
8              42                35                43           0
9              48                44                50           0

'Esc' closes window.*/

/*              LAB215 by 413 ERICH MUSICK   11:04 on Apr  8 2002

Tank size (less than 78)? 18
Steps in simulation? 2500000
Display Simulation (Show each move of the fish) (y/n)? n

Simulating guppy movement. Please wait...


STATS:
Number of Moves: 20529
Guppy  Start Position  Minimum Position  Maximum Position  Bump Count
=====  ==============  ================  ================  ==========
1               0                 0                17         899
2               2                 0                17         857
3               4                 0                17         912
4               6                 0                17         783
5               8                 0                17         897
6              10                 0                17         845
7              12                 0                17         878
8              14                 0                17         807
9              16                 0                17         853

'Esc' closes window.*/