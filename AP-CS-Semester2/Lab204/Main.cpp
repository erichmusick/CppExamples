/* Lab name 	    - File Input Output
 * Lab number	    - Lab204.cpp
 * Programmers	  - Erich Musick
 * Date Assigned  - n/a
 * Date Due 	    - n/a
 * Date Turned in - February 14, 2002
 * Purpose		    - Learn how to read from and write to files on the disk.
 * Input		      - User inputs a file name and some values.
 * Process		    - Values are written to the specified file.
 * Output		      - File contents displayed on screen for user
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****** 		  F U N C T I O N  P R O T O T Y P E S 			******/
void pressEnterToContinue();
int displayMenu();
string getFileName();
int getNumberOfValues();
void getValues(string fileName, int numberOfValues, vector<int> &values);
void writeValues(string fileName, int numberOfValues, vector<int> values);
void writeData(string fileName);
int readValues(string fileName, vector<int> &values, bool &error);
void displayValues(int numberOfValues, vector<int> values);
void readData(string fileName);

/****** 		            F U N C T I O N S 			        ******/
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
		key = _getch();
		if (key == 0) {
			key = _getch();
		}
	}
}

// DISPLAY MENU
/* Purpose    - Give the user a list of options
* Parameters - None.
* Input      - Using up/down arrows, user selects an option.
* Process    - None.
* Output     - None.
* Return     - option - integer representing the option the user has selected
*/
int displayMenu() {
	int option;
	char key;
	int cursorLocation;

	// DISPLAY: List options available to the user
	Common::GoToXY(0, 8);
	cout << "OPTIONS:\n";
	cout << "   Enter new filename\n";
	cout << "   Write data to current file\n";
	cout << "   Read data from current file\n";
	cout << "   Quit\n\n";
	cout << "Select option using the up & down arrow keys, press ENTER to accept";

	// INPUT: Move the cursor up and down when the user presses up/down arrows
	key = 5;
	cursorLocation = 9;

	Common::GoToXY(0, 9);
	cout << "->";

	while (int(key) != 13) {
		key = _getch();
		if (key == 0) {
			key = _getch();
		}

		Common::GoToXY(0, cursorLocation);
		cout << "  ";

		if (int(key) == 72 && cursorLocation > 9) {
			cursorLocation--;
		}
		if (int(key) == 80 && cursorLocation < 12) {
			cursorLocation++;
		}

		Common::GoToXY(0, cursorLocation);
		cout << "->";
	}

	// Sleep(100);
	// __flush_win95_keyup_events();

	option = cursorLocation - 9;

	return option;
}

// GET FILE NAME
/* Purpose    - Get the filename the user would like to use
* Parameters - None.
* Input      - fileName, string that will contain filename to use
* Process    - None.
* Output     - None.
* Return     - fileName
*/
string getFileName() {
	string fileName;

	Common::GoToXY(0, 8);
	cout << "Please enter a file name: ";
	cin >> fileName;
	cin.ignore(80, '\n');

	return fileName;
}

// WRITE DATA :: GET NUMBER OF VALUES
/* Purpose    - Get the number of values to write to the current file
* Parameters - None.
* Input      - numberOfValues, integer that will hold number of values to write
*                to current file
* Process    - None.
* Output     - None.
* Return     - numberOfValues
*/
int getNumberOfValues() {
	int numberOfValues;

	do {
		Common::GoToXY(0, 8);
		Common::ClearToEndOfLine();
		cout << "How many integers would you like to write to the current file";
		cout << " (1-30)? ";
		cin >> numberOfValues;
	} while (numberOfValues > 30 || numberOfValues <= 0);

	return numberOfValues;
}

// WRITE DATA :: GET VALUES
/* Purpose    - Get the values to write to the current file
* Parameters - numberOfValues - number of values to write to current file
*            - values - vector of integers that will hold the values to write
*                to the current file
* Input      - User inputs numberOfValues values into the values array
* Process    - None.
* Output     - None.
* Return     - None.
*/
void getValues(int numberOfValues, vector<int> &values) {
	int index;

	Common::GoToXY(0, 9);
	for (index = 0; index < numberOfValues; index++) {
		cout << "Enter value ";
		cout << index + 1;
		cout << ": ";
		cin >> values[index];
		cin.ignore(80, '\n');
	}

	return;
}

// WRITE DATA :: WRITE VALUES
/* Purpose    - Write the user-specified values to the current file
* Parameters - fileName - string containing current filename
*            - numberOfValues - number of values to write to current file
*            - values - vector of integers containing values to write to
*                current file
* Input      - None.
* Process    - Write number of values and values to current file
* Output     - None.
* Return     - None.
*/
void writeValues(string fileName, int numberOfValues, vector<int> values) {
	ofstream diskOut;
	int index;

	diskOut.open(fileName.c_str());
	if (!diskOut) {
		Common::GoToXY(0, 10 + numberOfValues);
		cout << "Unable to write to disk: ";
		cout << strerror(errno);
		cout << ". Please ensure ";
		cout << fileName;
		cout << " is writeable.\n";

		pressEnterToContinue();
	}
	else {
		diskOut << numberOfValues;
		diskOut << "\n";
		for (index = 0; index < numberOfValues; index++) {
			diskOut << values[index];
			diskOut << '\n';
		}
		diskOut.close();
	}

	return;
}

// WRITE DATA :: MAIN
/* Purpose    - Perform all the necessary actions for writing numbers to current
*                file
* Parameters - fileName - string containing current filename
* Input      - None.
* Process    - Check that current file is writable, call "sub-functions"
* Output     - None.
* Return     - None.
*/
void writeData(string fileName) {
	int numberOfValues;
	vector<int> values;
	ofstream diskOut;
	
	diskOut.open(fileName.c_str());
	if (!diskOut) {
		Common::GoToXY(0, 8);
		cout << "Unable to write to disk: ";
		cout << _sys_errlist[_doserrno];
		cout << ". Please ensure ";
		cout << fileName;
		cout << " is writeable or enter a new filename\n";

		pressEnterToContinue();

	}
	else {
		numberOfValues = getNumberOfValues();

		values.resize(numberOfValues);

		getValues(numberOfValues, values);

		writeValues(fileName, numberOfValues, values);
	}

	return;
}

// READ DATA :: READ VALUES
/* Purpose    - Read the values of the current file into an array
* Parameters - fileName - string containing current filename
*            - values - vector of integers - will contain values in current
*                file
* Input      - None.
* Process    - Read data from current file into values array
* Output     - None.
* Return     - numberOfValues - number of values in file
*/
int readValues(string fileName, vector<int> &values, bool &error) {
	ifstream diskIn;
	int numberOfValues;
	int index;
	
	diskIn.open(fileName.c_str());
	if (!diskIn) {
		Common::GoToXY(0, 8);
		cout << "Unable to read from disk: ";
		cout << _sys_errlist[_doserrno];
		cout << ". Try writing data to the file before reading it.";
		cout << "\n";

		pressEnterToContinue();

		error = true;
	}
	else {
		diskIn >> numberOfValues;

		values.resize(numberOfValues);

		for (index = 0; index < numberOfValues; index++) {
			diskIn >> values[index];
		}
		diskIn.close();
	}

	return numberOfValues;
}

// READ DATA :: DISPLAY VALUES
/* Purpose    - Display the values in the current file
* Parameters - numberOfValues - number of values in the current file
*            - values - vector containing values in current file
* Input      - None.
* Process    - None.
* Output     - Display values in values vector
* Return     - None.
*/
void displayValues(int numberOfValues, vector<int> values) {
	int index;

	Common::GoToXY(0, 8);

	for (index = 0; index < numberOfValues; index++) {
		cout << "Value ";
		cout << index + 1;
		cout << ": ";
		cout << values[index];
		cout << "\n";
	}

	return;
}

// READ DATA :: MAIN
/* Purpose    - Determine whether user would like to roll the die again
* Parameters - None.
* Input      - goAgain - either y or n, based on user's wishes
* Process    - None.
* Output     - None.
* Return     - returnValue, true if user would like to roll again, otherwise,
*              false
*/
void readData(string fileName) {
	int numberOfValues;
	vector<int> values;
	bool error;

	error = false;

	numberOfValues = readValues(fileName, values, error);

	if (!error) {               /* Previous function call was able to read file,
								continue with program (we only want to display
								the file contents if we were able to read from
								the file */
		displayValues(numberOfValues, values);

		pressEnterToContinue();

	}

	return;
}

/****** 			               M A I N					          ******/
int main()
{
	string fileName;
	int option;

	fileName = "default.txt"; // Give the fileName variable a default value

	option = 4;

	do {
		Common::ClearScreen();

		cout << "/*\t\t\t LAB204 by 413 ERICH MUSICK\n\n";
		cout << "FILE INPUT/OUTPUT\n";
		cout << "Simple program that demonstrates file input and output with C++\n";
		cout << "-------------------------------------------------------------------------------\n";
		cout << "Current Filename: ";
		cout << fileName;
		cout << "\n";
		cout << "-------------------------------------------------------------------------------\n";

		if (option == 0) {
			fileName = getFileName();
			option = 5;
		}
		else if (option == 1) {
			writeData(fileName);
			option = 5;
		}
		else if (option == 2) {
			readData(fileName);
			option = 5;
		}
		else {
			option = displayMenu();
		}
	} while (option != 3);

	return 0;
}

/****** 			      S A M P L E  O U T P U T					  ******/

/*                       LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: default.txt
-------------------------------------------------------------------------------
OPTIONS:
-> Enter new filename
Write data to current file
Read data from current file
Quit

Select option using the up & down arrow keys, press ENTER to accept

/*                      LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: default.txt
-------------------------------------------------------------------------------
Please enter a file name: somefile.txt

/*                       LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: somefile.txt
-------------------------------------------------------------------------------
OPTIONS:
Enter new filename
-> Write data to current file
Read data from current file
Quit

Select option using the up & down arrow keys, press ENTER to accept

/*                      LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: somefile.txt
-------------------------------------------------------------------------------
How many integers would you like to write to the current file (1-30)? 5
Enter value 1: 1
Enter value 2: 2
Enter value 3: 3
Enter value 4: 4
Enter value 5: 5

/*                       LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: somefile.txt
-------------------------------------------------------------------------------
OPTIONS:
Enter new filename
Write data to current file
-> Read data from current file
Quit

Select option using the up & down arrow keys, press ENTER to accept

/*                      LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: somefile.txt
-------------------------------------------------------------------------------
Value 1: 1
Value 2: 2
Value 3: 3
Value 4: 4
Value 5: 5

Press ENTER to continue...

/*                     LAB204 by 413 ERICH MUSICK

FILE INPUT/OUTPUT
Simple program that demonstrates file input and output with C++
-------------------------------------------------------------------------------
Current Filename: somefile.txt
-------------------------------------------------------------------------------
OPTIONS:
Enter new filename
Write data to current file
Read data from current file
-> Quit

Select option using the up & down arrow keys, press ENTER to accept

*/