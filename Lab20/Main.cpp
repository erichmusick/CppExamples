/* Title      - Diamond
* File name  - Lab20
* Programmer - 415 Erich Musick
* IPO        - Input   - User inputs a max width and symbol
*              Process - None.
*              Output  - Diamond is displayed with proper spacing
*/

/*************************** H E A D E R  F I L E S ***************************/

#include <iostream>
#include <iomanip>
#include "../Common/CommonFunctions.h"

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
int getDiamondSize();
char getDiamondCharacter();
void displayDiamond(int diamondSize, char diamondCharacter);
bool goAgain();

/****************************** F U N C T I O N S *****************************/
// GET DIAMOND SIZE
/* purpose    - Get the size of the diamond (width)
* parameters - None.
* input      - diamondSize, integer that will hold size of diamond
* process    - None.
* output     - None.
* return     - diamondSize, integer containing size of diamond
*/
int getDiamondSize() {
	int diamondSize;
	int xLocation;
	int yLocation;

	cout << "Size of Diamond (must be an odd positive integer ";
	cout << "between 1 and 49)? ";
	xLocation = Common::GetCursorXPosition();
	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(xLocation, yLocation);
		Common::ClearToEndOfLine();
		cin >> diamondSize;
	} while (diamondSize <= 0 || (diamondSize % 2) == 0 || diamondSize > 49);
	cin.ignore(80, '\n');

	return diamondSize;
}

// GET DIAMOND CHARACTER
/* purpose    - Get the character for the diamond
* parameters - None.
* input      - diamondCharacter, char that will hold character for diamond
* process    - None.
* output     - None.
* return     - diamondSize, char containing character for diamond
*/
char getDiamondCharacter() {
	char diamondCharacter;

	cout << "Diamond Character? ";
	cin >> diamondCharacter;
	cin.ignore(80, '\n');

	return diamondCharacter;
}

// DISPLAY THE DIAMOND
/* purpose    - Display the diamond
* parameters - diamondSize, integer holding value for width of diamond
*            - diamondCharacter, char holding symobl used when displaying diamond
* input      - None.
* process    - None.
* output     - Program uses for loops to display the diamond on the screen,
*                starting with one symbol for the first line and increasing by
*                2 for each row. When the max is reached, the program decreases
*                the number of symbols per row by 2 every row. Proper spaces
*                are displayed using setw() (in order to make the symbols loop
*                like a diamond rather than a triangle)
* return     - None.
*/
void displayDiamond(int diamondSize, char diamondCharacter) {
	int loopControl1;
	int loopControl2;
	int numberOfSpaces;

	for (loopControl1 = 1, numberOfSpaces = 40; loopControl1 < diamondSize;
		loopControl1 = loopControl1 + 2, numberOfSpaces--) {
		cout << setw(numberOfSpaces);
		cout << ' ';
		for (loopControl2 = 0; loopControl2 < loopControl1; loopControl2++) {
			cout << diamondCharacter;
		}
		cout << endl;
	}
	for (loopControl1 = diamondSize; loopControl1 > 0;
		loopControl1 = loopControl1 - 2, numberOfSpaces++) {
		cout << setw(numberOfSpaces);
		cout << ' ';
		for (loopControl2 = 0; loopControl2 < loopControl1; loopControl2++) {
			cout << diamondCharacter;
		}
		cout << endl;
	}
}

// GO AGAIN
/* purpose    - Determine whether the user would like to display another diamond
* parameters - None.
* input      - yORn, a char that is used to hold user's input ('y' or 'n')
* process    - Based on the value in yORn, returnValue is set to true or false,
*                true if the user would like to go again, false if the user
*                would like to quit.
* output     - None.
* return     - returnValue, bool - possible values described in "process"
*/
bool goAgain() {
	int xLocation;
	int yLocation;
	char yORn;
	bool returnValue;

	cout << "Go again ('y' or 'n')? ";
	xLocation = Common::GetCursorXPosition();
	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(xLocation, yLocation);
		Common::ClearToEndOfLine();
		cin >> yORn;
	} while (yORn != 'y' && yORn != 'n');
	cin.ignore(80, '\n');

	if (yORn == 'y') {
		returnValue = true;
	}
	else {
		returnValue = false;
	}

	return returnValue;
}

int main() {
	int diamondSize;
	char diamondCharacter;
	bool displayAnother;
	bool firstTime;

	firstTime = true;
	do {
		if (firstTime) {
			cout << "Diamond";
			cout << endl;
			cout << "Given a max width and a character, program displays a diamond.";
			cout << endl;
			cout << endl;
			firstTime = false;
		}
		else {
			Common::ClearScreen();
		}

		// USER INPUT: get diamond size
		diamondSize = getDiamondSize();

		// USER INPUT: get diamond character
		diamondCharacter = getDiamondCharacter();

		// DISPLAY: display diamond
		displayDiamond(diamondSize, diamondCharacter);

		// USER INPUT: display another diamond?
		displayAnother = goAgain();
	} while (displayAnother);

	return 0;
}

/************************** S A M P L E  O U T P U T **************************/
/*               LAB20 by 415 ERICH MUSICK   11:45 on Dec 18 2001

Diamond
Given a max width and a character, program displays a diamond.

Size of Diamond (must be an odd positive integer between 1 and 49)? 11
Diamond Character? *
*
***
*****
*******
*********
***********
*********
*******
*****
***
*
Go again ('y' or 'n')? n

'Esc' closes window.*/

/*               LAB20 by 415 ERICH MUSICK   11:45 on Dec 18 2001

Diamond
Given a max width and a character, program displays a diamond.

Size of Diamond (must be an odd positive integer between 1 and 49)? 23
Diamond Character? @
@
@@@
@@@@@
@@@@@@@
@@@@@@@@@
@@@@@@@@@@@
@@@@@@@@@@@@@
@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@
@@@@@@@@@@@@@
@@@@@@@@@@@
@@@@@@@@@
@@@@@@@
@@@@@
@@@
@
Go again ('y' or 'n')? n

'Esc' closes window.*/

/*               LAB20 by 415 ERICH MUSICK   11:45 on Dec 18 2001

Diamond
Given a max width and a character, program displays a diamond.

Size of Diamond (must be an odd positive integer between 1 and 49)? 39
Diamond Character? @
@
@@@
@@@@@
@@@@@@@
@@@@@@@@@
@@@@@@@@@@@
@@@@@@@@@@@@@
@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@
@@@@@@@@@@@@@
@@@@@@@@@@@
@@@@@@@@@
@@@@@@@
@@@@@
@@@
@
Go again ('y' or 'n')? n

'Esc' closes window.*/
