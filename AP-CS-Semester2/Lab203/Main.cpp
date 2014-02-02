/* Lab name 	    - Dice
* Lab number	    - Lab203.cpp
* Programmers	  - Erich Musick
* Date Assigned  - n/a
* Date Due 	    - n/a
* Date Turned in - February 7, 2002
* Purpose		    - Simulate the rolling of a die.
* Input		      - Number of times to roll a die.
* Process		    - Roll the die the number of times specified, use RandGen to
*                - simulate the randomness in rolling a die
* Output		      - Display the number of times each number, 1-6 was rolled.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****** 		  F U N C T I O N  P R O T O T Y P E S 			******/
void displayProgramInformation();
int getNumberOfRolls();
void clearHistogram(vector<int> &histogramValues);
void rollTheDie(vector<int> &histogramValues, int numberOfRolls);
int largestHistogramValue(vector<int> histogramValues);
int histogramScale(vector<int> histogramValues, int largestValue);
void displayHistogram(vector<int> histogramValues);
bool goAgain();

/****** 		            F U N C T I O N S 			        ******/

// DISPLAY PROGRAM INFORMATION
/* Purpose    - Introduce the program to the user
* Parameters - None.
* Input      - None.
* Process    - None.
* Output     - Display some information about the program
* Return     - None.
*/
void displayProgramInformation() {
	cout << "DICE\n";
	cout << "Rolls a virtual die the number of times specified by the user. ";
	cout << "Then, tabulates\nnumber of times each number (1-6) was rolled and";
	cout << " displays a histogram.\n\n";
}

// GET NUMBER OF ROLLS
/* Purpose    - Get the number of times to roll the die
* Parameters - None.
* Input      - numberOfRolls, integer, number of times to roll the die
* Process    - None.
* Output     - None.
* Return     - numberOfRolls
*/
int getNumberOfRolls() {
	int numberOfRolls;          // Number of times to roll the die

	do {
		cout << "How many times would you like to roll the die? ";
		cin >> numberOfRolls;
		cin.ignore(80, '\n');
	} while (numberOfRolls <= 0);

	return numberOfRolls;
}

// CLEAR HISTOGRAM
/* Purpose    - Reset histogram values to 0
* Parameters - histogramValues, vector of integers that contains the number
*              of times each number was rolled
* Input      - None.
* Process    - Loop through histogramValues and set each value to 0
* Output     - None.
* Return     - None.
*/
void clearHistogram(vector<int> &histogramValues) {
	int vectorIndex;            // Loop ctrl var for clear vector loop

	for (vectorIndex = 0; vectorIndex < 6; vectorIndex++) {
		histogramValues[vectorIndex] = 0;
	}

	return;
}

// ROLL THE DIE
/* Purpose    - Simulate the rolling of a die
* Parameters - histogramValues, vector of integers that will contain the
*              number of times each number was rolled
*            - numberOfRolls, integer containing number of times to roll the die
* Input      - None.
* Process    - Calculate a random die value for every roll, increment histogram
*              vector for the value rolled.
* Output     - None.
* Return     - None.
*/
void rollTheDie(vector<int> &histogramValues, int numberOfRolls) {
	int rollCount;              // loop control for "roll die" loop
	int vectorIndex;            // random vector index betweeen 0 and 5

	for (rollCount = 0; rollCount < numberOfRolls; rollCount++) {
		vectorIndex = rand() % 6;
		histogramValues[vectorIndex] += 1;
	}

	return;
}

// LARGEST HISTOGRAM VALUE
/* Purpose    - Find the largest value of the histogram
* Parameters - histogramValues, vector of integers that contains the number
*              of times each number was rolled
* Input      - None.
* Process    - Find largest value in the histogram
* Output     - None.
* Return     - largestValue, integer containing the largest value
*/
int largestHistogramValue(vector<int> histogramValues) {
	int vectorIndex;            // Loop ctrl for finding largest histogram value
	int largestValue;           // Largest value in the histogramValues array

	largestValue = 0;

	// Find the largest value in the histogram
	for (vectorIndex = 0, largestValue; vectorIndex < 6; vectorIndex++) {
		if (histogramValues[vectorIndex] > largestValue) {
			largestValue = histogramValues[vectorIndex];
		}
	}

	return largestValue;
}

// HISTOGRAM SCALE
/* Purpose    - Determine the scale to use for the histogram in order to fit
*            - the *s for each number rolled on one line
* Parameters - histogramValues, vector of integers that contains the number
*              of times each number was rolled
*            - largestValue, integer containing the largest value in the
*              the histogram
* Input      - None.
* Process    - The program determines the scale for the histogram
* Output     - None.
* Return     - scale, an integer containing the scale
*/
int histogramScale(vector<int> histogramValues, int largestValue) {
	int scale;                  // Scale of histogram
	int largestValueReduced;    // Loop control for finding histogram scale
	int largestValueLength;     // Length of the largest value

	largestValueLength = Common::intLength(largestValue);

	// Find the amount by which we should increment the star display index (the
	// scale of the histogram
	scale = 1;
	largestValueReduced = largestValue;
	while (largestValueReduced > (64 - largestValueLength)) {
		scale++;
		largestValueReduced = largestValue / scale;
	}

	return scale;
}

// DISPLAY HISTOGRAM
/* Purpose    - Display a histogram for the number of times each value was rolled
* Parameters - histogramValues, vector of integers that contains the number
*              of times each number was rolled
*            - numberOfRolls, integer containing number of times to roll the die
* Input      - None.
* Process    - Determine the scale of the histogram
* Output     - Display the histogram
* Return     - None.
*/
void displayHistogram(vector<int> histogramValues) {
	int vectorIndex;            // Loop ctrl variable for the histogram disp loop
	int starIndex;              // Loop control variable for the star display loop
	int increment;              // Amount by which to increment the star disp loop
	int largestValue;           // Largest value in the histogram
	int xLocation;              // x-coordinate of histogram actual value display
	int yLocation;              // y-coordinate of histogram actual value display

	largestValue = largestHistogramValue(histogramValues);
	increment = histogramScale(histogramValues, largestValue);
	xLocation = (largestValue / increment) + 13;

	cout << "\n\tRESULTS: \n";
	cout << "\t( Key: * = ";
	cout << increment;
	cout << " rolls )\n\n";

	for (vectorIndex = 0; vectorIndex < 6; vectorIndex++) {
		yLocation = Common::GetCursorYPosition();

		cout << "\t";
		cout << vectorIndex + 1;
		cout << ": ";

		// DISPLAY: Star Display Loop - display *s of histogram for the current die
		// value
		for (starIndex = 0; starIndex < histogramValues[vectorIndex];
			starIndex += increment) {
			cout << '*';
		}

		// Display the acutal value for this row of the histogram
		Common::GoToXY(xLocation, yLocation);
		cout << " (";
		cout << setw(Common::intLength(largestValue));
		cout << setfill('0');
		cout << histogramValues[vectorIndex];
		cout << ")\n";
	}

	return;
}

// GO AGAIN (ROLL THE DIE AGAIN)
/* Purpose    - Determine whether user would like to roll the die again
* Parameters - None.
* Input      - goAgain - either y or n, based on user's wishes
* Process    - None.
* Output     - None.
* Return     - returnValue, true if user would like to roll again, otherwise,
*              false
*/
bool goAgain() {
	char goAgain;               // User input - y/n
	bool returnValue;           // Value to return
	int yLocation;              // yLocation

	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << endl;
		cout << "Roll die again (y/n)? ";
		cin >> goAgain;
	} while (goAgain != 'y' && goAgain != 'Y' && goAgain != 'n' && goAgain != 'N');

	if (goAgain == 'y' || goAgain == 'Y') {
		returnValue = true;
		cout << endl;
	}
	else {
		returnValue = false;
	}

	return returnValue;
}

/****** 			               M A I N					          ******/
int main() {
	vector<int> histogramValues(6, 0); // Contains values of die for each roll
	int numberOfRolls;                  // Number of times to roll the die

	srand(time(NULL));

	// OUTPUT: Display a little info about the program
	displayProgramInformation();

	do {
		// INPUT: Get number of times to roll die
		numberOfRolls = getNumberOfRolls();

		// PROCESS: Clear the vector so it doesn't contain values from the previous
		// rolls
		clearHistogram(histogramValues);

		// PROCESS: Fill vector with random values, so as to "roll" the die
		rollTheDie(histogramValues, numberOfRolls);

		// OUTPUT: Display the values for each roll
		displayHistogram(histogramValues);

	} while (goAgain());
}

/****** 			      S A M P L E  O U T P U T					  ******/

/*              LAB203 by 413 ERICH MUSICK   11:35 on Feb  6 2002

DICE
Rolls a virtual die the number of times specified by the user. Then, tabulates
number of times each number (1-6) was rolled and displays a histogram.

How many times would you like to roll the die? 25

RESULTS:
( Key: * = 1 rolls )

1: *         (1)
2: ****      (4)
3: ********  (8)
4: ****      (4)
5: *         (1)
6: *******   (7)

Roll die again (y/n)? y

How many times would you like to roll the die? 75

RESULTS:
( Key: * = 1 rolls )

1: ***********         (11)
2: *************       (13)
3: ************        (12)
4: ******************  (18)
5: **********          (10)
6: ***********         (11)

Roll die again (y/n)? y

How many times would you like to roll the die? 1000

RESULTS:
( Key: * = 3 rolls )

1: ********************************************************** (172)
2: *******************************************************    (165)
3: ********************************************************   (167)
4: *******************************************************    (165)
5: *******************************************************    (165)
6: ********************************************************   (166)

Roll die again (y/n)? n

'Esc' closes window.*/