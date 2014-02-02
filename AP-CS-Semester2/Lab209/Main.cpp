/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab209.cpp
* Programmer - 413 Erich Musick
* Turned in  -
* Input      - User enters a name.
* Process    - If first and last name are entered, swaps first and last name.
*                Middle names are included with the first name.
* Output     -
*/

/****  I N C L U D E   F I L E S  ****/
#include <iostream>
#include <string>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****  F U N C T I O N   P R O T O T Y P E S  ****/
void displayProgramInformation();
string getFullName();
int findLastSpace(string fullName);
void SwapFirstLast(string &fullName);
void displayFullName(string fullName);
bool goAgain();

/****  F U N C T I O N S  ****/

// DISPLAY PROGRAM INFORMATION
/* Purpose    - Introduce the program to the user
* Parameters - None.
* Input      - None.
* Process    - None.
* Output     - Display some information about the program
* Return     - None.
*/
void displayProgramInformation() {

	cout << "FULL NAME\n";
	cout << "Given a name in \"firstName lastName\" form, swaps ";
	cout << "the first and\nlast name.\n\n";

	return;

}

// GET FULL NAME
/* Purpose    - Get a name.
* Parameters - None.
* Input      - User inputs their full name, value is stored in fullName.
* Process    - None.
* Output     - None.
* Return     - fullName
*/
string getFullName() {

	string fullName;

	cout << "Enter first and last name: ";
	getline(cin, fullName);

	return fullName;

}

// FIND LAST SPACE
/* Purpose    - Find the last space in fullName.
* Parameters - fullName, string containing the full name.
* Input      - None.
* Process    - Starting at the end of fullName, loops through name until
*                the beginning of fullName is reached, or until a space is
*                found, whichever comes first.
* Output     - None.
* Return     - lastSpace, location in fullName array where the last space
*                was found
*/
int findLastSpace(string fullName) {

	int index;
	int nameLength;
	int lastSpace;

	nameLength = fullName.length();

	lastSpace = -1;

	index = nameLength - 1;
	while (index > 0 && lastSpace == -1) {
		if (fullName[index] == ' ') {
			lastSpace = index;
		}
		index--;
	}

	return lastSpace;

}

// SWAP FIRST AND LAST NAMES
/* Purpose    - Switch the first and last names around in fullName
* Parameters - fullName, string containing the user's input
* Input      - None.
* Process    - Calls findLastSpace to find the location of the last space in
*                fullName. If a last space was found, there is a first name, so
*                the first and last names are found using the substr function.
*                Middle name(s) are included as part of the first name. Then,
*                fullName is rebuilt, in the format lastName, firstName.
* Output     - None.
* Return     - None.
*/
void SwapFirstLast(string &fullName) {

	int lastSpace;
	int nameLength;
	string firstName;
	string lastName;

	nameLength = fullName.length();
	lastSpace = findLastSpace(fullName);

	if (lastSpace >= 0) {       // There is a space
		firstName = fullName.substr(0, lastSpace);
		lastName = fullName.substr(lastSpace + 1, nameLength - 1);

		fullName = lastName + ", " + firstName;
	}

	return;

}

// DISPLAY FULL NAME
/* Purpose    - Display the full name, once it's been swapped
* Parameters - fullName, string containing the user's input
* Input      - None.
* Process    - None.
* Output     - A simple message and the full name are displayed.
* Return     - None.
*/
void displayFullName(string fullName) {

	cout << "In applications, I will use: ";
	cout << fullName;
	cout << endl;

	return;

}

// GO AGAIN
/* Purpose    - Determine whether user would like to rotate the list again
* Parameters - None.
* Input      - goAgain - either y or n, based on user's wishes
* Process    - None.
* Output     - None.
* Return     - returnValue, true if user would like to rotate again, otherwise,
*              false
*/
bool goAgain() {

	char goAgain;               // User input - y/n
	bool returnValue;           // Value to return (true/false)
	int yLocation;              // yLocation for Common::GoToXY

	yLocation = Common::GetCursorYPosition();

	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << "Go again (y/n)? ";
		cin >> goAgain;
		cin.ignore(80, '\n');

		goAgain = char(toupper(goAgain));
	} while (goAgain != 'Y' && goAgain != 'N');

	if (goAgain == 'Y') {
		returnValue = true;
		cout << endl;
	}
	else {
		returnValue = false;
	}

	return returnValue;

}

/****   M A I N  ****/

int main() {

	string fullName;          // Full Name user enters
	string fullNameSwaped;    // Full Name, swapped

	// OUTPUT: Display some information about this program
	displayProgramInformation();

	do {

		// INPUT: Get full name
		fullName = getFullName();

		// PROCESS: Swap first and last name
		SwapFirstLast(fullName);

		// OUTPUT: Display inputed full name and swapped full name
		displayFullName(fullName);

	} while (goAgain());

	return 0;

}

/**** S A M P L E  O U T P U T ****/

/*              LAB209 by 413 ERICH MUSICK   11:06 on Feb 13 2002

FULL NAME
Given a name in "firstName lastName" form, swaps the first and
last name.

Enter first and last name: John Doe
In applications, I will use: Doe, John
Go again (y/n)? y

Enter first and last name: John M. Smith
In applications, I will use: Smith, John M.
Go again (y/n)? y

Enter first and last name: Erich D. Musick
In applications, I will use: Musick, Erich D.
Go again (y/n)? y

Enter first and last name: Erich
In applications, I will use: Erich
Go again (y/n)? y

Enter first and last name: Musick
In applications, I will use: Musick
Go again (y/n)? n

'Esc' closes window.*/