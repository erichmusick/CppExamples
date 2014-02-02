/* Lab name 	    - Final Find Function
 * Lab number	    - Lab202.cpp
 * Programmers	  - Erich Musick
 * Date Assigned  - January 28, 2002
 * Date Due 	    - n/a
 * Date Turned in - February 1, 2002
 * Purpose		    - Use the Final Find Func. to find the array index of a value
 * Input		      - Length of list, values to find
 * Process		    - List of random numbers generated, finds values to find
 * Output		      - Displays array index of values for which user searched
 */

#include <iostream>
#include <vector>
#include <time.h>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****** 		  F U N C T I O N  P R O T O T Y P E S 			******/
void displayProgramInformation();
int getNumberOfValues();
void generateList(vector<int> &values, int arrayLength);
void displayValues(vector<int> values, int arrayLength);
int getValueToFind();
int findValue(vector<int> values, int arrayLength, int findValue);
void displayLocation(int findValue, int indexOfValue);
bool findAnother();
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
	cout << "/*";
	cout << endl;
	cout << "FIND FUNCTION";
	cout << endl;
	cout << "Generates a random list of integers from -100 to 100 (Length of list";
	cout << " is ";
	cout << endl;
	cout << "specified by the user.) Then, the user may search for a value in it";
	cout << " and the ";
	cout << endl;
	cout << "array index of that value is displayed.";
	cout << endl;
	cout << endl;
}

// GET NUMBER OF VALUES
/* Purpose    - Get the length of the list of random numbers
* Parameters - None.
* Input      - numberOfValues, an integer containing the length of the list
* Process    - None.
* Output     - Display some information about the program
* Return     - numberOfValues
*/
int getNumberOfValues() {
	int numberOfValues;
	int yLocation;

	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << "How many numbers would you like in the generated list? ";
		cin >> numberOfValues;
	} while (numberOfValues <= 0);

	return numberOfValues;
}

// GENERATE LIST
/* Purpose    - Generate the list of random values
* Parameters - values - the vector that will hold the values in the list
*            - arrayLength - an integer holding the length of the list
* Input      - None.
* Process    - Create a list of random numbers between -100 and 100
* Output     - None.
* Return     - None.
*/
void generateList(vector<int> &values, int arrayLength) {
	int index;
	
	values.resize(arrayLength);

	for (index = 0; index < arrayLength; index++) {
		values[index] = rand() % 200 - 100;
	}

	return;
}

// DISPLAY VALUES
/* Purpose    - Display the values in the list of random numbers
* Parameters - values - the vector that containing the values in the list
*            - arrayLength - an integer holding the length of the list
* Input      - None.
* Process    - None.
* Output     - Display the numbers in the list.
* Return     - None.
*/
void displayValues(vector<int> values, int arrayLength) {
	int index;

	cout << endl;
	cout << "The List: ";
	for (index = 0; index < arrayLength; index++) {
		if (index > 0) {
			cout << ", ";
			cout << values[index];
		}
		else {
			cout << values[index];
		}
	}
	cout << endl;

	return;
}

// GET VALUE TO FIND
/* Purpose    - Get the value the user would like to find
* Parameters - None.
* Input      - valueToFind, the value the user would like to find (an integer)
* Process    - None.
* Output     - None.
* Return     - valueToFind
*/
int getValueToFind() {
	int valueToFind;
	int yLocation;

	cout << endl;

	yLocation = Common::GetCursorYPosition();

	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << "What value would you like to find (-100 to 100)? ";
		cin >> valueToFind;
	} while (valueToFind > 100 || valueToFind < -100);

	return valueToFind;
}

// FIND VALUE
/* Purpose    - Find the array index of a particular value
* Parameters - values - the vector that containing the values in the list
*            - arrayLength - an integer holding the length of the list
*            - findValue - value to find in the array
* Input      - None.
* Process    - Find the value sent to the function in the array
* Output     - None.
* Return     - indexOfValue, array index of value OR -1 if value not in array
*/
int findValue(vector<int> values, int arrayLength, int findValue) {
	int index;
	int indexOfValue;

	index = 0;
	indexOfValue = -1;
	while (index < arrayLength && indexOfValue == -1) {
		if (values[index] == findValue) {
			indexOfValue = index;
		}
		index++;
	}

	return indexOfValue;
}

// DISPLAY LOCATION
/* Purpose    - Display the array index of the value for which the prog searched
* Parameters - findValue - value to find in the array
*            - indexOfValue - array index of value for which the prog searched
* Input      - None.
* Process    - None.
* Output     - Display the array index of the value for which the prog searched
*              OR Display a message saying the value wasn't found in the list
* Return     - None.
*/
void displayLocation(int findValue, int indexOfValue) {

	cout << endl;
	cout << "You searched for ";
	cout << findValue;
	if (indexOfValue != -1) {
		cout << ". The first instance of it has an array index of ";
		cout << indexOfValue;
		cout << ".";
	}
	else {
		cout << ". It was not found in the array.";
	}
	cout << endl;

	return;
}

// FIND ANOTHER
/* Purpose    - Determine whether user would like to find another value in the
*              current list
* Parameters - None.
* Input      - findAnother - either y or n, based on user's wishes
* Process    - None.
* Output     - None.
* Return     - returnValue, true if user would like to find another, otherwise,
*              false
*/
bool findAnother() {
	char findAnother;
	bool returnValue;
	int yLocation;

	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << endl;
		cout << "Find another value (y/n)? ";
		cin >> findAnother;
	} while (findAnother != 'y' && findAnother != 'Y' && findAnother != 'n' &&
		findAnother != 'N');

	if (findAnother == 'y' || findAnother == 'Y') {
		returnValue = true;
	}
	else {
		returnValue = false;
	}

	return returnValue;
}

// GO AGAIN (CREATE ANOTHER LIST)
/* Purpose    - Determine whether user would like to generate another list
* Parameters - None.
* Input      - goAgain - either y or n, based on user's wishes
* Process    - None.
* Output     - None.
* Return     - returnValue, true if user would like to find another, otherwise,
*              false
*/
bool goAgain() {
	char goAgain;
	bool returnValue;
	int yLocation;

	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(1, yLocation);
		Common::ClearToEndOfLine();
		cout << endl;
		cout << "Generate another list (y/n)? ";
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

int main(){
	vector<int> values;
	int numberOfValues;
	int valueToFind;
	int locationOfValue;

	srand(time(NULL));

	do {
		// DISPLAY: Clear the screen
		Common::ClearScreen();

		// DISPLAY: Display a little info about the program
		displayProgramInformation();

		// USER INPUT: Get the length of the list of numbers
		numberOfValues = getNumberOfValues();

		/* PROCESS: Generate a list of length numberOfValues with random numbers
		from -100 to 100*/
		generateList(values, numberOfValues);

		// DISPLAY: Display the values in the list
		displayValues(values, numberOfValues);

		do {
			// USER INPUT: Find the array index of what value in the list?
			valueToFind = getValueToFind();

			// PROCESS: Find the index of the value
			locationOfValue = findValue(values, numberOfValues, valueToFind);

			// DISPLAY: Display the array index of the user searched for
			displayLocation(valueToFind, locationOfValue);
		} while (findAnother());
	} while (goAgain());

}

/****** 			      S A M P L E  O U T P U T					  ******/

/*
FIND FUNCTION
Generates a random list of integers from -100 to 100 (Length of list is
specified by the user.) Then, the user may search for a value in it and the
array index of that value is displayed.

How many numbers would you like in the generated list? 15

The List: 92, -20, -57, -10, 44, -38, 3, -50, -84, 89, 59, -42, 36, -34, 31

What value would you like to find (-100 to 100)? 89

You searched for 89. The first instance of it has an array index of 9.

Find another value (y/n)? y

What value would you like to find (-100 to 100)? 15

You searched for 15. It was not found in the array.

Find another value (y/n)? y

What value would you like to find (-100 to 100)? -42

You searched for -42. The first instance of it has an array index of 11.

Find another value (y/n)? n

Generate another list (y/n)? n

'Esc' closes window.*/