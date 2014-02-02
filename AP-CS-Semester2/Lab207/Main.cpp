/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab207.cpp
* Programmer - 413 Erich Musick
* Turned in  - March 6, 2002
* Input      - User inputs the amount to rotate the alphabet
* Process    - Alphabet is rotated.
* Output     - New list is displayed.
*/

/****  I N C L U D E   F I L E S  ****/

#include <iostream>
#include <string>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****  F U N C T I O N   P R O T O T Y P E S  ****/
void displayProgramInformation();
string setDefaultCharacterList();
void displayList(string characterList);
int getAmountToRotate(int listLength);
void rotateList(string&characterList, int amountToRotate);
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

	cout << "ROTATE\n";
	cout << "Rotates alphabet by amount entered by user and displays list of";
	cout << " letters.\n\n";

	return;
}

// SET DEFAULT CHARACTERS
/* Purpose    - Set the array of characters to the default, which, in this case
*                is the alphabet
* Parameters - None.
* Input      - None.
* Process    - stringof characters defined, filled with default values
*                (alphabet)
* Output     - None.
* Return     - characters - string- contains default characters
*/
string setDefaultCharacterList() {

	return "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

}

// DISPLAY LIST
/* Purpose    - Display the current list of characters
* Parameters - characters - stringcontaining the list of letters
* Input      - None.
* Process    - None.
* Output     - Displays list of characters.
* Return     - None.
*/
void displayList(string characterList) {

	cout << characterList;
	cout << endl;
	cout << endl;

	return;

}

// GET AMOUNT TO ROTATE
/* Purpose    - Get the amount to rotate the list.
* Parameters - listLength - int containing size of list
* Input      - User inputs the amount they would like to rotate the list
* Process    - Amount to rotate is divided by size of list, remainder is stored
*                as amountToRotate. Then, if amountToRotate is negative, made
*                positive by adding size of list to amountToRotate.
* Output     - None.
* Return     - amountToRotate - amount to rotate list.
*/
int getAmountToRotate(int listLength) {
	int amountToRotate;

	cout << "Amount to rotate by: ";
	cin >> amountToRotate;

	// Divide amountToRotate by vectorLength, store remainder because it is a
	// waste of time to shift more than vectorLength times. This line gets the
	// same task accomplished in less time
	amountToRotate %= listLength;

	// Since program is set up to rotate in a positive direction, needs
	// amountToRotate to be positive. These next three lines convert a negative
	// rotate to a positive rotate
	if (amountToRotate < 0) {
		amountToRotate = listLength + amountToRotate;
	}

	return amountToRotate;

}

// ROTATE LIST
/* Purpose    - Rotate the list of characters
* Parameters - characterList - contains list of characters
*            - amountToRotate - integer containing amount to rotate list
* Input      - None.
* Process    - List is rotated using nested for loops. The outer for loop
*                repeats amountToRotate times. The inner for loop takes the
*                list and shifts the characters to the right one. Before the
*                inner for loop is called, the last value in the list is saved,
*                so it can be added to the beginning of the list once the rest
*                of the list has been rotated.
* Output     - None.
* Return     - None because characters was passed in as a reference variable.
*/
void rotateList(string&characterList, int amountToRotate) {

	int count;
	int index;
	int listLength;
	char lastValue;

	listLength = characterList.length();

	for (count = 0; count < amountToRotate; count++) {
		lastValue = characterList[listLength - 1];
		for (index = listLength - 1; index > 0; index--) {
			characterList[index] = characterList[index - 1];
		}
		characterList[0] = lastValue;
	}

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
	bool returnValue;           // Value to return
	int yLocation;              // yLocation

	yLocation = Common::GetCursorYPosition();

	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << "Rotate list again (y/n)? ";
		cin >> goAgain;

		goAgain = toupper(goAgain);
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

	string characterList;     // List of characters
	int amountToRotate;         // Amount to rotate list

	// DISPLAY: Display a little information about the program
	displayProgramInformation();

	// PROCESS: Set the list of characters to the default (the alphabet)
	characterList = setDefaultCharacterList();

	// DISPLAY: Display the original list
	cout << "Original List: ";
	displayList(characterList);

	do {

		// INPUT: Get the amount to rotate the list
		amountToRotate = getAmountToRotate(characterList.length());

		// PROCESS: Rotate the list
		rotateList(characterList, amountToRotate);

		// DISPLAY: Display the rotated list
		cout << "\tNew List: ";
		displayList(characterList);

	} while (goAgain());

	return 0;
}

/**** S A M P L E  O U T P U T ****/

/*              LAB207 by 413 ERICH MUSICK   11:06 on Feb 13 2002

ROTATE
Rotates alphabet by amount entered by user and displays list of letters.

Original List: ABCDEFGHIJKLMNOPQRSTUVWXYZ

Amount to rotate by: 25
New List: BCDEFGHIJKLMNOPQRSTUVWXYZA

Rotate list again (y/n)? y

Amount to rotate by: 10
New List: RSTUVWXYZABCDEFGHIJKLMNOPQ

Rotate list again (y/n)? y

Amount to rotate by: -25
New List: QRSTUVWXYZABCDEFGHIJKLMNOP

Rotate list again (y/n)? y

Amount to rotate by: -10
New List: ABCDEFGHIJKLMNOPQRSTUVWXYZ

Rotate list again (y/n)? n

'Esc' closes window.*/

/*              LAB207 by 413 ERICH MUSICK   11:06 on Feb 13 2002

ROTATE
Rotates alphabet by amount entered by user and displays list of letters.

Original List: ABCDEFGHIJKLMNOPQRSTUVWXYZ

Amount to rotate by: 54
New List: YZABCDEFGHIJKLMNOPQRSTUVWX

Rotate list again (y/n)? y

Amount to rotate by: -31
New List: DEFGHIJKLMNOPQRSTUVWXYZABC

Rotate list again (y/n)? n

'Esc' closes window.*/