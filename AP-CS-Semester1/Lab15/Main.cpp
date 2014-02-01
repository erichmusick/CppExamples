/* Title      - ln(2)
* File name  - Lab15
* Programmer - 415 Erich Musick
* IPO        - Input   - User inputs an integer.
*              Process - Approximate value of ln(2) is calculated using:
*                                1-1/2+1/3-1/4+...+(+/-)1/n+...
*                        where n is the inputed integer.
*              Output  - Approximate and actual values (chopped at 6 decimal
*                        places) are displayed.
*/

/*************************** H E A D E R  F I L E S ***************************/

#include<iostream>
#include<string>

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/

/****************************** F U N C T I O N S *****************************/
int main() {
	string again;
	bool firstTime;
	int howManyTerms;
	double approxValue;
	int count;

	firstTime = true;
	do {
		if (firstTime) {        // If this is the first run, explain the program
			cout << "This program approximates the natural log of 2 using a series ";
			cout << "expansion";
			cout << endl;
			cout << "     ln(2) = 1-1/2+1/3-1/4+...+(+/-)1/n+...";
			cout << endl;
			cout << "out to the number of terms specified by the user.";
			cout << endl;
			cout << endl;

			firstTime = false;    // Next run won't be the first
		}

		// Ask the user how many terms the program should use
		cout << "How many terms should be used? ";
		cin >> howManyTerms;
		cout << endl;

		for (count = 1, approxValue = 0.; count <= howManyTerms; count++) {
			/* This next line adds (or subtracts) the next number in the sequence to
			the sum. The (((count % 2) * 2.) - 1.) is -1 if the number (sequence
			index) is even, 1 if the sequence index is odd. The result is
			multiplied by (1. / count) (the value of the sequence for this index
			number) so that the quantity (or its opposite) will be added.
			*/
			approxValue = approxValue + (((count % 2) * 2) - 1) * (1. / count);
		}

		// Display approxamate value and actual value
		cout << "Approxamate value using ";
		cout << howManyTerms;
		cout << " terms is: ";
		cout << approxValue;
		cout << endl;
		cout << "Using the math function log(2) is: ";
		cout << log(2);
		cout << endl;
		cout << endl;

		// Loop through again?
		cout << "Again (y/n)? ";
		cin >> again;

		// Leave an extra space if user would like to loop through again.
		if (again == "y" || again == "Y") {
			cout << endl;
		}
	} while (again == "y" || again == "Y");

	return 0;
}

/************************** S A M P L E  O U T P U T **************************/

/*               LAB15 by 415 ERICH MUSICK   11:24 on Nov 19 2001

This program approximates the natural log of 2 using a series expansion
ln(2) = 1-1/2+1/3-1/4+...+(+/-)1/n+...
out to the number of terms specified by the user.

How many terms should be used? 1

Approxamate value using 1 terms is: 1
Using the math function log(2) is: 0.693147

Again (y/n)? y

How many terms should be used? 3

Approxamate value using 3 terms is: 0.833333
Using the math function log(2) is: 0.693147

Again (y/n)? y

How many terms should be used? 100

Approxamate value using 100 terms is: 0.688172
Using the math function log(2) is: 0.693147

Again (y/n)? y

How many terms should be used? 1000000

Approxamate value using 1000000 terms is: 0.693147
Using the math function log(2) is: 0.693147

Again (y/n)? n

'Esc' closes window.*/