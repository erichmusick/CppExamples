/* Title  - Classifying Triangles
File name - Lab11.cpp
Programmer- 415 Erich Musick
Assigned  - 10/28/01
Due       - 11/03/01
IPO       - This program inputs sets of three numbers (0 0 0 to quit) and then
prints out if it is a triangle and what type scalene, isosceles, or
equalateral.
*/

/*************************** H E A D E R  F I L E S ***************************/
#include <iostream>
#include <iomanip>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
void getSides(double &s1, double &s2, double &s3);
bool goAgain(double s1, double s2, double s3);
bool isTriangle(double s1, double s2, double s3);
bool isScalene(double s1, double s2, double s3);
bool isIsosceles(double s1, double s2, double s3);
bool isEquilateral(double s1, double s2, double s3);

/****************************** F U N C T I O N S *****************************/
int main() {
	double side1;
	double side2;
	double side3;

	getSides(side1, side2, side3);
	while (goAgain(side1, side2, side3)) {
		cout << setw(6);
		cout << side1;
		cout << setw(8);
		cout << side2;
		cout << setw(8);
		cout << side3;

		// Determine type of triangle if any and report results
		if (isTriangle(side1, side2, side3)) {
			// Values do form a triangle
			cout << "    True   ";

			// Determine what type of triangle is formed by the values
			if (isScalene(side1, side2, side3)) {
				cout << "        Scalene\n";
			}
			else {
				if (isEquilateral(side1, side2, side3)) {
					cout << " Isosceles & Equilateral\n";
				}
				else {
					cout << "       Isosceles\n";
				}
			}
		}
		else {
			// Values don't form a triangle
			cout << "    False   -----------------------\n";
		}
		// Set up for next set of three possible sides
		getSides(side1, side2, side3);
	}
	return 0;
}

// Get Sides
/* purpose    - Get the lengths of the sides of the triangle
* parameters - s1 - a double containing the length of side 1
*              s2 - a double containing the length of side 2
*              s3 - a double containing the length of side 3
* input      - s1, s2, s3 - the lengths of each side
* process    - None.
* output     - The first time looping through the program, the table header
*                is displayed
* return     - None.
*/
void getSides(double &s1, double &s2, double &s3) {
	static const int inputLine = Common::GetCursorYPosition();
	static       int outputLine = inputLine + 5;
	static bool firstTime = true;

	Common::GoToXY(0, inputLine);
	Common::ClearToEndOfLine();
	cout << "Enter a triangle's 3 sides (0 0 0 to quit): ";
	cin >> s1 >> s2 >> s3;

	if (firstTime) {
		firstTime = false;
		cout << "\n\nside 1  side 2  side 3  Triangle  Classification\n";
		cout << "======  ======  ======  ========  =======================\n";
	}
	Common::GoToXY(0, outputLine++);

	return;
}

// Go Again
/* purpose    - Determine whether the user wants to quit or loop through the
*                program again
* parameters - s1 - a double containing the length of side 1
*              s2 - a double containing the length of side 2
*              s3 - a double containing the length of side 3
* input      - None.
* process    - The function uses a conditional statment (if) to determine
*                whether the user has inputed three zeros, meaning they would
*                like to quit
* output     - None.
* return     - false if three zeros inputed, true if at least one side isn't
*                equal to zero
*/
bool goAgain(double s1, double s2, double s3) {
	bool returnValue = false;

	if ((s1 != 0) || (s2 != 0) || (s3 != 0)) {
		returnValue = true;
	}

	return returnValue;
}

// Is a triangle?
/* purpose    - Determine whether the values entered form a triangle
* parameters - s1 - a double containing the length of side 1
*              s2 - a double containing the length of side 2
*              s3 - a double containing the length of side 3
* input      - None.
* process    - The function uses a conditional statment (if) to determine
*                whether the three values form a triangle
* output     - None.
* return     - true if the values form a triangle; false if they don't
*/
bool isTriangle(double s1, double s2, double s3) {
	bool returnValue = false;

	if ((s1 + s2) > s3 && (s2 + s3) > s1 && (s1 + s3) > s2 && s1 > 0 && s2 > 0 &&
		s3 > 0)
	{
		// If the sum of any two sides is greater than the third side and all the
		// sides have values greater than zero, therefore the values form a triangle
		returnValue = true;
	}

	return returnValue;
}

// Is a scalene triangle?
/* purpose    - Determine whether the values entered form a scalene triangle
* parameters - s1 - a double containing the length of side 1
*              s2 - a double containing the length of side 2
*              s3 - a double containing the length of side 3
* input      - None.
* process    - The function uses a conditional statment (if) to determine
*                whether the three values form a scalene triangle (no two
*                sides are equal)
* output     - None.
* return     - true - when the values form a scalene triangle
*              false - when the values don't form a scalene triangle
*/
bool isScalene(double s1, double s2, double s3) {
	bool returnValue = false;

	if (s1 != s2 && s1 != s3 && s2 != s3) {
		// If none of the sides are equal in length, the values form a scalene
		// triangle
		returnValue = true;
	}

	return returnValue;
}

// Is an isosceles triangle?
/* purpose    -Determine whether the values entered form an isosceles triangle
* parameters - s1 - a double containing the length of side 1
*              s2 - a double containing the length of side 2
*              s3 - a double containing the length of side 3
* input      - None.
* process    - The function uses a conditional statment (if) to determine
*                whether the three values form an isosceles triangle (two or
*                more sides are equal)
* output     - None.
* return     - true - when the values form an isosceles triangle
*              false - when the values don't form an isosceles triangle
*/
bool isIsosceles(double s1, double s2, double s3) {
	bool returnValue = false;

	if (!isScalene(s1, s2, s3)){
		// If the triangle isn't scalene, the triangle is isosceles
		returnValue = true;
	}

	return returnValue;
}

// Is an equilateral triangle?
/* purpose    -Determine whether the values entered form an isosceles triangle
* parameters - s1 - a double containing the length of side 1
*              s2 - a double containing the length of side 2
*              s3 - a double containing the length of side 3
* input      - None.
* process    - The function uses a conditional statment (if) to determine
*                whether the three values form an equilateral triangle (all
*                three sides are equal)
* output     - None.
* return     - true - when the values form an equilateral triangle
*              false - when the values don't form an equilateral triangle
*/
bool isEquilateral(double s1, double s2, double s3) {
	bool returnValue = false;

	if (s1 == s2 && s2 == s3) {
		// If all the sides are equal to each other, the triangle is equlateral
		returnValue = true;
	}

	return returnValue;
}

/************************** S A M P L E  O U T P U T **************************/

/*               LAB11 by 415 ERICH MUSICK   11:17 on Oct 29 2001

Enter a triangle's 3 sides (0 0 0 to quit): 0 0 0


side 1  side 2  side 3  Triangle  Classification
======  ======  ======  ========  =======================
1       1       1    True    Isosceles & Equilateral
1       2       3    False   -----------------------
2       2       3    True          Isosceles
3       4       5    True           Scalene
5       6       5    True          Isosceles
7       4       4    True          Isosceles

'Esc' closes window.*/

