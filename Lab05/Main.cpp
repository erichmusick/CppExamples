/* Title     - Triangle Formulas
 * File name - Lab05
 * Programmer- 415 Erich Musick
 * IPO       - Input - The user inputs the real number lengths of three sides of
               a triangle.
			   Processing - The program calculates the area and perimeter using
			   the values entered by the user and the formulas for perimeter
			   and for area.
			   Output - The lengths of the three sides, the perimeter, and the
			   area are printed on the user's screen.
 */

#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include "../Common/CommonFunctions.h"

using namespace std;

int main()
{
	double s;
	const string colSep = "   "; // Column Seperator
	double perimeterAry[10];
	double areaAry[10];
	double sideAary[10];
	double sideBary[10];
	double sideCary[10];
	string another;
	int count;
	int a;
	count = 0;

	do {
		Common::ClearScreen();
		Common::GoToXY(1, 2);
		// Tell what the program is about
		cout << "This program will calculate the perimeter and area of any triangle. "
			<< "The user\nonly needs to enter the real-number lengths of the sides of"
			<< " a triangle. The\nprogram DOES NOT protect against values that do not"
			<< " form a triangle.\n"
			<< endl;
		// Get the lengths of the sides of the triangle
		cout << "Enter the length of side a: ";
		cin >> sideAary[count];
		cout << "\n"
			<< "Enter the length of side b: ";
		cin >> sideBary[count];
		cout << "\n"
			<< "Enter the length of side c: ";
		cin >> sideCary[count];

		// Calculate the permiter
		//perimeter = sideA + sideB + sideC;
		perimeterAry[count] = sideAary[count] + sideBary[count] + sideCary[count];

		// Calculate the area using hero's formula
		s = (sideAary[count] + sideBary[count] + sideCary[count]) / 2;
		//area = sqrt(s*(s-sideA)*(s-sideB)*(s-sideC));
		areaAry[count] = sqrt(s*(s - sideAary[count])*(s - sideBary[count])*(s - sideCary[count]));
		cout << endl
			<< "Another (y/n)? ";
		cin >> another;
		count++;
	} while (another == "y" && count < 10);
	// Display the lengths of each side, the perimeter, and the area
	cout << "\n"
		<< setw(10)
		<< "Side A  "
		<< colSep
		<< setw(10)
		<< "Side B  "
		<< colSep
		<< setw(10)
		<< "Side C  "
		<< colSep
		<< setw(11)
		<< "Perimeter "
		<< colSep
		<< setw(10)
		<< "Area   "
		<< endl
		<< setw(10)
		<< "----------"
		<< colSep
		<< setw(10)
		<< "----------"
		<< colSep
		<< setw(10)
		<< "----------"
		<< colSep
		<< setw(11)
		<< "----------"
		<< colSep
		<< setw(10)
		<< "----------"
		<< colSep
		<< endl;
	for (a = 0; a < count; a++) {
		cout << setw(10)
			<< sideAary[a]
			<< colSep
			<< setw(10)
			<< sideBary[a]
			<< colSep
			<< setw(10)
			<< sideCary[a]
			<< colSep
			<< setw(11)
			<< perimeterAry[a]
			<< colSep
			<< setw(10)
			<< areaAry[a]
			<< endl;
	}
	return 0;
}

/*               LAB05 by 415 ERICH MUSICK   11:04 on Sep  7 2001

This program will calculate the perimeter and area of any triangle. The user
only needs to enter the real-number lengths of the sides of a triangle. The
program DOES NOT protect against values that do not form a triangle.

Enter the length of side a: 6

Enter the length of side b: 9.5

Enter the length of side c: 5

Side A       Side B       Side C      Perimeter       Area
----------   ----------   ----------    ----------   ----------
6          9.5            5          20.5      13.0968

'Esc' closes window.*/
