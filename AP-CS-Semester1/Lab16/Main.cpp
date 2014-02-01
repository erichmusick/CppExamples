/* Title      - Calculating Powers
 * File name  - Lab16
 * Programmer - 415 Erich Musick
 * IPO        - Input   - User inputs the base and exponent of a power
 *              Process - Value of base raised to the power is calculated
 *              Output  - Result, and values inputed by user are displayed
 */

/*************************** H E A D E R  F I L E S ***************************/

#include <iostream>
#include <string>

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
void getValues(double &x, int &n);
double raiseToPower(double x, int n);
void displayResult(double x, int n, double result);

/****************************** F U N C T I O N S *****************************/
// GET VALUES
/* purpose    - Get the values the user would like to use for the base and the
*               exponent
* parameters - x - reference parameter of type double containing the base
*            - n - reference parameter of type int contaning the exponent
* input      - x - value of the base; n - value of the exponent
* process    - None.
* output     - None.
* return     - None.
*/
void getValues(double &x, int &n) {
	cout << "Enter the real number base: ";
	cin >> x;
	cout << "Enter the power to raise to: ";
	cin >> n;

	return;
}

// RAISE TO POWER
/* purpose    - Calculate the value of the base raised to the power
* parameters - x - value parameter of type double containing the base
*            - n - value parameter of type int contaning the exponent
* input      - None.
* process    - Using iterative statments, the value of the base raised to the
*               power is calculated
* output     - None.
* return     - result - a variable of type double containing the value of the
*               base raised to the power
*/
double raiseToPower(double x, int n) {
	int count;
	double result;

	if (n >= 0) {           // We're raising the base to a positive exponent
		for (count = 1, result = 1.; count <= n; count++) {
			result = result * x;
		}
	}
	else {                  // We're raising the base to a negitive exponent
		n = n * -1;
		for (count = 1, result = 1.; count <= n; count++) {
			result = result * (1. / x);
		}
	}

	return result;
}

// DISPLAY RESULT
/* purpose    - Display the result, as well as the values entered by the user
* parameters - x - value parameter of type double containing the base
*            - n - value parameter of type int contaning the exponent
*            - result - value parameter of type double containing the result
*               of the base raised to the power
* input      - None.
* process    - None.
* output     - Values entered by user, as well as the result, are displayed.
* return     - None.
*/
void displayResult(double x, int n, double result) {
	cout << endl;
	cout << "(";
	cout << x;
	cout << ")^";
	cout << n;
	cout << " = ";
	cout << result;
	cout << endl;
	cout << endl;

	return;
}

int main() {
	string goAgain;         // Contains user input (calculate another?)
	double base;              // Base of power
	int power;                // Power that program will raise base to
	double result;            // Variable that contains result of base^power

	cout << "CALCULATING POWERS";
	cout << endl;
	cout << "Calculates the value of a real number base raised to an integer ";
	cout << "power.";
	cout << endl;
	cout << endl;

	do {
		// USER INPUT: get values for base and power
		getValues(base, power);

		// CALCULATION: calculate the value of the base raised to the power
		result = raiseToPower(base, power);

		// DISPLAY: display the result of the calculation
		displayResult(base, power, result);

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

/*               LAB16 by 415 ERICH MUSICK   11:24 on Nov 19 2001

CALCULATING POWERS
Calculates the value of a real number base raised to an integer power.

Enter the real number base: -1.2
Enter the power to raise to: 2

(-1.2)^2 = 1.44

Again (y/n)? y

Enter the real number base: 2
Enter the power to raise to: 3

(2)^3 = 8

Again (y/n)? y

Enter the real number base: 5
Enter the power to raise to: 3

(5)^3 = 125

Again (y/n)? y

Enter the real number base: 10
Enter the power to raise to: -10

(10)^-10 = 1e-10

Again (y/n)? y

Enter the real number base: 2
Enter the power to raise to: -2

(2)^-2 = 0.25

Again (y/n)? y

Enter the real number base: 2
Enter the power to raise to: 0

(2)^0 = 1

Again (y/n)? n

'Esc' closes window.*/