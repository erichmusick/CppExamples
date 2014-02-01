/* Title      - Square Root Function
* File name  - Lab17
* Programmer - 415 Erich Musick
* IPO        - Input   - User inputs a positive real number
*              Process - Approximate square root value of user inputed number
*                is calculated, within .01 of the acutal value
*              Output  - Approx square root value and actual value (calculated
*                using the sqrt() function) are displayed
*/

/*************************** H E A D E R  F I L E S ***************************/

#include <iostream>
#include <string>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
void SqrtEst(double a, double &approxSquareRoot, double actualSquareRoot);
void displayResult(double a, double approxSquareRoot, double actualSquareRoot);

/****************************** F U N C T I O N S *****************************/
// SQUARE ROOT ESTIMATE
/* purpose    - Calculate the approximate square root of the number entered
*            -  by the user.
* parameters - a - double containing number entered by the user.
*            - approxSquareRoot - double where approx sqrt value will be placed
*            - actualSquareRoot - double containing value of function sqrt(a)
* input      - None.
* process    - Approximate value for square root of a is calculated using a
*               recursive series.
* output     - None.
* return     - estimatedSquareRoot - double containing the approximate value
*               of the square root of the number entered by the user. The
*               approximate value is the actual value +/- .01
*/
void SqrtEst(double a, double &approxSquareRoot, double actualSquareRoot) {
	double accuracy;

	approxSquareRoot = a / 2.;
	do {
		approxSquareRoot = .5 * (approxSquareRoot + (a / approxSquareRoot));
		accuracy = fabs(actualSquareRoot - approxSquareRoot);
	} while (accuracy > .01);

	return;
}

// DISPLAY RESULT
/* purpose    - Display the calculated and actual values for the sqrt of a
* parameters - a - double containing number entered by the user.
*            - approxSquareRoot - double containing approx square root of a
*            - actualSquareRoot - double containing value of function sqrt(a)
* input      - None.
* process    - None.
* output     - Calculated and acutal values for square root of a are displayed
* return     - None.
*/
void displayResult(double a, double approxSquareRoot, double actualSquareRoot) {
	cout << endl;
	cout << "Approximate square root of ";
	cout << a;
	cout << " is                     : ";
	cout << approxSquareRoot;
	cout << " +/- .01";
	cout << endl;

	cout << "Actual square root using the C++ function sqrt(";
	cout << a;
	cout << ") is: ";
	cout << actualSquareRoot;
	cout << endl;
	cout << endl;
}

int main() {
	string goAgain;         // Contains user input (calculate another?)
	double a;
	double approxSquareRoot;
	double actualSquareRoot;
	int yLocation;

	cout << "SQUARE ROOT FUNCTION";
	cout << endl;
	cout << "Estimates the square root of a positive number.";
	cout << endl;
	cout << endl;

	do {
		// USER INPUT: get values for base and power
		cout << "Enter a positive number: ";
		yLocation = Common::GetCursorYPosition();
		do {                    // Ask for number > 0 until one is entered
			Common::GoToXY(25, yLocation);
			Common::ClearToEndOfLine();
			cin >> a;
		} while (a <= 0);

		actualSquareRoot = sqrt(a);

		// CALCULATION: calculate the value of the base raised to the power
		SqrtEst(a, approxSquareRoot, actualSquareRoot);

		// DISPLAY: display the result of the calculation
		displayResult(a, approxSquareRoot, actualSquareRoot);

		// USER INPUT: Loop through again?
		cout << "Again (y/n)? ";
		cin >> goAgain;

		// DISPLAY: Leave an extra space if user would like to loop through again.
		if (goAgain == "y" || goAgain == "Y") {
			cout << endl;
		}
	} while (goAgain == "y" || goAgain == "Y");

	return 0;
}

/************************** S A M P L E  O U T P U T **************************/

/*               LAB17 by 415 ERICH MUSICK   11:11 on Nov 27 2001

SQUARE ROOT FUNCTION
Estimates the square root of a positive number.

Enter a positive number: 25

Approximate square root of 25 is                     : 5.00001 +/- .01
Actual square root using the C++ function sqrt(25) is: 5

Again (y/n)? y

Enter a positive number: 10

Approximate square root of 10 is                     : 3.16232 +/- .01
Actual square root using the C++ function sqrt(10) is: 3.16228

Again (y/n)? y

Enter a positive number: 2.5

Approximate square root of 2.5 is                     : 1.58173 +/- .01
Actual square root using the C++ function sqrt(2.5) is: 1.58114

Again (y/n)? y

Enter a positive number: 2.25

Approximate square root of 2.25 is                     : 1.50125 +/- .01
Actual square root using the C++ function sqrt(2.25) is: 1.5

Again (y/n)? y

Enter a positive number: 100

Approximate square root of 100 is                     : 10 +/- .01
Actual square root using the C++ function sqrt(100) is: 10

Again (y/n)? y

Enter a positive number: 5463

Approximate square root of 5463 is                     : 73.9123 +/- .01
Actual square root using the C++ function sqrt(5463) is: 73.9121

Again (y/n)? n

'Esc' closes window.*/