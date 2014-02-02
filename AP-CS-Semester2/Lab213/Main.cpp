/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab213.cpp
* Programmer - 413 Erich Musick
* Turned in  - March 21, 2002
* Input      - User inputs the number of sets of six flips they'd like to do.
* Process    - For each set of six flips, uses RandGen class to simulate random
*                movement of a fish. Tabulates final location of fish (after
*                each set) and stores tabulation in an array.
* Output     - Tabulation is displayed.
*/

/************************  I N C L U D E   F I L E S  *************************/

#include <iostream>
#include <vector>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/******************  F U N C T I O N   P R O T O T Y P E S  *******************/
void displayProgramInformation();
int getNumberOfFlips();
int flipSixTimes();
void tabulateFinalLocations(vector<int> &endPositions, int numberOfFlips);
void displayFinalLocations(vector<int> endPositions);

/****************************  F U N C T I O N S  *****************************/

// DISPLAY PROGRAM INFORMATION
/* Purpose    - Introduce the program to the user
* Parameters - None.
* Input      - None.
* Process    - None.
* Output     - Display some information about the program
* Return     - None.
*/
void displayProgramInformation() {

	cout << "SIX FLIPS\n";
	cout << "This program is part of the Marine Biology Case Study. It simulates";
	cout << " the random\nswimming of fish. The user enters the number of sets ";
	cout << " of six rolls (six random\nmovements of a fish either to the left";
	cout << " or to the right of its position, with an\ninitial position of 10).";
	cout << " Program then displays a tabulation of the final\nlocations of the ";
	cout << "fish after each of these sets of rolls.\n\n";

	return;

}

// GET NUMBER OF FLIPS
/* Purpose    - Get the number of sets of six flips the user would like to do.
* Parameters - None.
* Input      - User inputs the number of sets of six flips they'd like to do.
* Process    - If input is less than or equal to 0, prompts again.
* Output     - None.
* Return     - numberOfFlips - user's input.
*/
int getNumberOfFlips() {

	int numberOfFlips;
	int yLocation;

	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << "How many sets of six flips would you like to do? ";
		cin >> numberOfFlips;
		cin.ignore(80, '\n');
	} while (numberOfFlips <= 0);

	cout << endl;

	return numberOfFlips;

}

// FLIP SIX TIMES
/* Purpose    - Simulate the flipping of a coin six times and the associated
*                movement (either right or left from the previous position),
*                starting at an initial position of 10.
* Parameters - None.
* Input      - None.
* Process    - RandGen class is used to simulate flipping of coin. Movement
*                left and right, based on results of coin is tracked.
* Output     - None.
* Return     - position, once the loop is finished, is equal to the final
*                position of the fish.
*/
int flipSixTimes() {

	int k;
	int flip; // the coin value
	int position;

	position = 10;
	for (k = 0; k < 6; k++) {
		flip = rand() % 2;
		if (flip == 0) {
			position++;
		}
		else {
			position--;
		}
	}

	return position;

}

// TABULATE FINAL LOCATION
/* Purpose    - Tabulate the number of times the fish ends up at each particular
*                location.
* Parameters - endPositions - vector of integers used to hold the number of
*                times the fish ends up at each position.
*            - numberOfFlips - number of sets of six flips to do
* Input      - None.
* Process    - Calls flipSixTimes function, which returns the final position
*                of the fish after six rolls. Increments the vector value for
*                that location. Repeat until this has been done numberOfFlips
*                times.
* Output     - None.
* Return     - None.
*/
void tabulateFinalLocations(vector<int> &endPositions, int numberOfFlips) {

	int index;
	int finalPosition;

	for (index = 0; index < numberOfFlips; index++) {
		finalPosition = flipSixTimes();
		endPositions[finalPosition]++;
	}

	return;

}

// DISPLAY FINAL LOCATIONS
/* Purpose    - Display the tabulation done in tabulateFinalLocations function.
* Parameters - endPositions - vector of integers used to hold the number of
*                times the fish ends up at each position.
* Input      - None.
* Process    - None.
* Output     - Display the tabulation done in tabulateFinalLocations function.
* Return     - None.
*/
void displayFinalLocations(vector<int> endPositions) {

	int index;
	int vectorLength;

	vectorLength = endPositions.size();

	for (index = 0; index < vectorLength; index++) {
		cout << index;
		cout << ": ";
		cout << endPositions[index];
		cout << endl;
	}

	return;

}

/*********************************** M A I N **********************************/

int main() {

	vector<int> endPositions(17, 0); // Array that will hold the tabulation of
	// final positions
	int numberOfFlips;                // Number of sets of six flips the user
	// would like to do

	// OUTPUT: Display information about the program
	displayProgramInformation();

	// INPUT: Get the number of sets of six flips the user would like to do
	numberOfFlips = getNumberOfFlips();

	// PROCESS: Tabulate the number of times the fish ends up at each position
	tabulateFinalLocations(endPositions, numberOfFlips);

	// OUTPUT: Display tabulation calculated in the process
	displayFinalLocations(endPositions);

	return 0;

}

/*************************** S A M P L E  O U T P U T *************************/

/*              LAB213 by 413 ERICH MUSICK   11:34 on Mar 18 2002

SIX FLIPS
This program is part of the Marine Biology Case Study. It simulates the random
swimming of fish. The user enters the number of sets  of six rolls (six random
movements of a fish either to the left or to the right of its position, with an
initial position of 10). Program then displays a tabulation of the final
locations of the fish after each of these sets of rolls.

How many sets of six flips would you like to do? 25

0: 0
1: 0
2: 0
3: 0
4: 0
5: 0
6: 4
7: 0
8: 5
9: 0
10: 5
11: 0
12: 7
13: 0
14: 4
15: 0
16: 0

'Esc' closes window.*/

/*              LAB213 by 413 ERICH MUSICK   11:34 on Mar 18 2002

SIX FLIPS
This program is part of the Marine Biology Case Study. It simulates the random
swimming of fish. The user enters the number of sets  of six rolls (six random
movements of a fish either to the left or to the right of its position, with an
initial position of 10). Program then displays a tabulation of the final
locations of the fish after each of these sets of rolls.

How many sets of six flips would you like to do? 1000

0: 0
1: 0
2: 0
3: 0
4: 14
5: 0
6: 100
7: 0
8: 213
9: 0
10: 323
11: 0
12: 232
13: 0
14: 105
15: 0
16: 13

'Esc' closes window.*/