/* Title     - Inches Conversion
 * File name - Lab06
 * Programmer- 415 Erich Musick
 * IPO       - Input - User inputs an integer-length in inches
               Processing - Program splits the user input into yards, feet, and
			   inches using division and modulo
			   Output - Program displays calculated yards, feet, and inches
*/

#include <iostream>

using namespace std;

int main()
{

	// Declare variables
	int userInches;
	int yards;
	int remainingInches;
	int feet;
	int inches;
	bool first = true;
	char another;

	do {
		// Display two blank lines, if this is the first loop
		if (!first) {
			cout << endl << endl;
		}

		// Get input from user
		cout << "Enter length in inches: ";
		cin >> userInches;

		// Calculate yards, feet, and inches
		yards = userInches / 36;
		remainingInches = (userInches % 36);
		feet = remainingInches / 12;
		inches = remainingInches % 12;

		// Display results of calculations
		cout << endl
			<< userInches
			<< " inches = "
			<< yards
			<< " yd. "
			<< feet
			<< " ft. "
			<< inches
			<< " in."
			<< endl;

		// Does the user want the program to calculate another?
		cout << endl
			<< "Calculate another (y/n)? ";
		cin >> another;

		// Let the program know that the next loop is not the first
		first = false;
	} while (another != 110);
	return 0;
}
//--------------------------End Main-----------------------------------------

/*               LAB06 by 415 ERICH MUSICK   11:29 on Sep 14 2001

Enter length in inches: 67

67 inches = 1 yd. 2 ft. 7 in.

Calculate another (y/n)? y


Enter length in inches: 54

54 inches = 1 yd. 1 ft. 6 in.

Calculate another (y/n)? y


Enter length in inches: 36

36 inches = 1 yd. 0 ft. 0 in.

Calculate another (y/n)? y


Enter length in inches: 12

12 inches = 0 yd. 1 ft. 0 in.

Calculate another (y/n)? n

'Esc' closes window.*/
