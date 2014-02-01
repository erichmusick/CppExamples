/* Title      - Copying CD's
* File name  - Lab12.cpp
* Programmer - 415 Erich Musick
* Assigned   - 11/05/01
* IPO        - Input -
*              User inputs the length of two CD's and a tape
*            - Process -
*              The program determines which, if any, CD(s) will fit on the tape
*            - Output -
*              The program displays the values entered by the user and tells
*              the user which CD(s) (if any) fit on the tape
*/

/*************************** H E A D E R  F I L E S ***************************/
#include <iostream>
#include <iomanip>
#include "../common/CommonFunctions.h"

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
void getLengths(int &t1, int &t2, int &t);
bool goAgain(int t1, int t2, int t3);
int copyGivenLengths(int t1, int t2, int t);

/****************************** F U N C T I O N S *****************************/
int main() {
	int cd1Length;
	int cd2Length;
	int tapeLength;
	int whatFits;

	getLengths(cd1Length, cd2Length, tapeLength);
	while (goAgain(cd1Length, cd2Length, tapeLength)) {
		cout << setw(6);
		cout << cd1Length;
		cout << setw(8);
		cout << cd2Length;
		cout << setw(8);
		cout << tapeLength;

		// Determine what fits on tape
		whatFits = copyGivenLengths(cd1Length, cd2Length, tapeLength);

		if (whatFits == 0) {
			cout << "          Neither";
		}
		else if (whatFits == 1) {
			cout << "           CD 1";
		}
		else if (whatFits == 2) {
			cout << "           CD 2";
		}
		else if (whatFits == 3) {
			cout << "           Both";
		}
		else {
			cout << "          Either";
		}

		// Set up for next set of three possible sides
		getLengths(cd1Length, cd2Length, tapeLength);
	}
	return 0;
}

// Get Lengths
/* purpose    - Get the lengths of the two CD's and the tape
* parameters - t1 - an int containing the length of cd 1
*              t2 - an int containing the length of cd 2
*              t  - an int containing the length of the tape
* input      - t1, t2, t
* process    - None.
* output     - The first time looping through the program, the table header
*                is displayed
* return     - None.
*/
void getLengths(int &t1, int &t2, int &t) {
	static const int inputLine = Common::GetCursorYPosition();
	static       int outputLine = inputLine + 5;
	static bool firstTime = true;

	Common::GoToXY(0, inputLine);
	Common::ClearToEndOfLine();
	cout << "Enter the length of CD 1, CD 2 and the tape (0 0 0 to quit): ";
	cin >> t1 >> t2 >> t;

	if (firstTime) {
		firstTime = false;
		cout << "\n\n CD 1    CD 2    Tape            Copy:\n";
		cout << "======  ======  ======  =======================\n";
	}
	Common::GoToXY(0, outputLine++);

	return;
}

// Go Again
/* purpose    - Determine whether the user wants to quit or loop through the
*                program again
* parameters - t1 - an int containing the length of cd 1
*              t2 - an int containing the length of cd 2
*              t  - an int containing the length of the tape
* input      - None.
* process    - The function uses a conditional statment (if) to determine
*                whether the user has inputed three zeros, meaning they would
*                like to quit
* output     - None.
* return     - false if three zeros inputed, true if at least one value isn't
*                equal to zero
*/
bool goAgain(int t1, int t2, int t) {
	bool returnValue = false;

	if ((t1 != 0) || (t2 != 0) || (t != 0)) {
		returnValue = true;
	}

	return returnValue;
}

// Copy Given Lengths
/* purpose    - Determine which CD(s) (if any) should be copied to the tape
* parameters - t1 - an int containing the length of cd 1
*              t2 - an int containing the length of cd 2
*              t  - an int containing the length of the tape
* input      - t1, t2, t
* process    - Using a series of if statements, the program determines which
*                CD(s) (if any) should be copied to the tape
* output     - None.
* return     - 0 if neither CD fits on the tape
*              1 if CD 1 should be copied to the tape
*              2 if CD 2 should be copied to the tape
*              3 if both CD's should be copied to the tape
*              4 if either CD can be copied to the tape (both are of equal
*                length)
*/
int copyGivenLengths(int t1, int t2, int t) {
	int whatFits;

	if (t1 + t2 <= t) {
		whatFits = 3;
	}
	else {
		if (t1 <= t || t2 <= t) {
			if (t1 <= t && t2 <= t) {
				if (t1 > t2) {
					whatFits = 1;
				}
				else {
					if (t1 == t2) {
						whatFits = 4;
					}
					else {
						whatFits = 2;
					}
				}
			}
			else {
				if (t1 <= t) {
					whatFits = 1;
				}
				else {
					whatFits = 2;
				}
			}
		}
		else {
			whatFits = 0;
		}
	}

	return whatFits;
}

/************************** S A M P L E  O U T P U T **************************/

/*               LAB12 by 415 ERICH MUSICK   11:22 on Nov  6 2001

Enter the length of CD 1, CD 2 and the tape (0 0 0 to quit): 0 0 0


CD 1    CD 2    Tape            Copy:
======  ======  ======  =======================
2       2       2          Either
2       2       3          Either
2       3       4           CD 2
2       3       5           Both
3       2       4           CD 1
4       4       3          Neither
3       4       9           Both
3       2       3           CD 1
2       3       2           CD 1

'Esc' closes window.*/