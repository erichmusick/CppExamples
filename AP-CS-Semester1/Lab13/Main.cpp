/* Name       - Adding Big Integers
* Lab        - Lab13.cpp
* Programmer - 415 Erich Musick
* Assigned   - 11/12/01
* Due        - 11/??/01
* Purpose    - This program tests the Add function written for the work
*              book chapter 7 problem 16 on page 38.
* Input      - Two "big integers" are entered by the user.
* Process    - The sum of those integers is calculated.
* Output     - The two numbers and their sum with leading zeros stripped
*              off and commas used to make the numbers more readable.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

/******     G L O B A L   C O N S T A N T S     ******/

const int N = 900;   // The maximum digits in a big integer.

/******            F U N C T I O N S            ******/

/* Function name         - getNumber
* Purpose               - input a "big integer" of up to N digits.
* Reference parameter n - an vector able to contain up to N digits.
* Pre-Condition         - n is an vector capable of holding "N" integers.
* Post-Condition        - n contains the "N" digit number with the least
*                         significant digit in n[N-1].
* Input                 - up to an "N" digit number with non-digit characters
*                         ignored and overflow digits ignored
* Output                - none.
* Return                - none.
*/

void getNumber(vector<int> &n) {
	int i;         // index into the vector of digits n
	int j;         // index into the string entered by user
	string str;  // number entered (stored as a string of characters)

	cout << "Enter a number up to " << N << " digits long:  ";
	cin >> str;
	cin.ignore(200, '\n');                             // throw out end of line

	for (i = N - 1, j = str.length() - 1; i >= 0; i--, j--) {
		if (j >= 0) {
			if (str[j] >= '0' && str[j] <= '9') {
				n[i] = int(str[j]) - int('0');
			}
			else {  // not a valid digit so ignore it by undoing the upcoming decriment
				i++;
			}
		}
		else {
			n[i] = 0;
		}
	}

	return;
}

/* Function name     - displayNumber
* Purpose           - print out a "big integer" of up to N digits.
* Value parameter n - an vector containing a big integer with the most
*                     significant digit at n[0].
* Pre-Condition     - n contains N digits 0-9
* Post-Condition    - the digits are displayed as a "big integer".
* Output            - the number with leading zeros suppressed.
* Return            - none.
*/

void displayNumber(const vector<int> &n) {
	int i;
	int offsetFromMultipleOf3;
	int a;

	i = 0;
	while (i<N - 1 && n[i] == 0) { // Skip leading zeros except the last one if # zero.
		i++;
	}
	if (n.size() > N) {
		a = N + 1;
	}
	else {
		a = N;
	}
	while (i<a) {              // Output digits from first significant digit.
		cout << n[i];

		offsetFromMultipleOf3 = (a - 1) % 3;

		if (!((i - offsetFromMultipleOf3) % 3) && ((i + 1) != a)) {
			// Add in commas for readability
			cout << ",";
		}
		i++;
	}
	return;
}

/* Function name     - add
* Purpose           - calculate the sum of two "big integer" numbers.
* Value parameter a - an vector containing a big integer with the most
*                     significant digit at n[0].  The first number to add.
* Value parameter b - an vector containing a big integer with the most
*                     significant digit at n[0].  The second number to add.
* Reference parameter sum - an vector which is changed to contain the sum
*                           of the first two value parameters.
* Pre-Condition     - a and b each contain N digits 0-9 and a+b<10^11.
* Post-Condition    - sum contains the digits of a "big integer" equal to a+b.
* Output            - none.
* Return            - none.
*/

void add(const vector<int> &a, const vector<int> &b, vector<int> &sum) {
	int i;     // index into the digits of a, b, and sum.
	int d;     // the sum of one set of digits along with any carry from before.
	int carry; // used to hold the carry digit when the sum of two digits is > 9.

	carry = 0;

	sum.resize(N);
	for (i = (N - 1); i >= 0; i--) {
		d = a[i] + b[i] + carry;
		sum[i] = d % 10;
		carry = d / 10;
	}

	if (carry != 0) {
		sum.resize(N + 1);
		for (i = N; i > 0; i--) {
			sum[i] = sum[i - 1];
		}
		sum[0] = carry;
	}

	return;
}

/******                M A I N                  ******/

int main() {

	// D E C L A R E   V A R I A B L E S

	vector<int> i1(N);
	vector<int> i2(N);
	vector<int> theSum(N, 0);

	// I N P U T

	getNumber(i1);
	getNumber(i2);

	// P R O C E S S

	add(i1, i2, /* giving */ theSum);

	// O U T P U T

	displayNumber(i1);
	cout << " + ";
	displayNumber(i2);
	cout << " = ";
	displayNumber(theSum);
	cout << endl;

	// E X I T

	return 0;
}

/*               LAB13 by 415 ERICH MUSICK   10:52 on Nov 13 2001

Enter a number up to 100 digits long:  564287913
Enter a number up to 100 digits long:  1642753
564,287,913 + 1,642,753 = 565,930,666

'Esc' closes window.*/

/*               LAB13 by 415 ERICH MUSICK   10:52 on Nov 13 2001

Enter a number up to 100 digits long:  11111111111111111
Enter a number up to 100 digits long:  99999999999999999
11,111,111,111,111,111 + 99,999,999,999,999,999 = 111,111,111,111,111,110

'Esc' closes window.*/

/*               LAB13 by 415 ERICH MUSICK   10:52 on Nov 13 2001

Enter a number up to 100 digits long:  1234
Enter a number up to 100 digits long:  5678
1,234 + 5,678 = 6,912

'Esc' closes window.*/

/*               LAB13 by 415 ERICH MUSICK   10:52 on Nov 13 2001

Enter a number up to 100 digits long:  55682
Enter a number up to 100 digits long:  22896
55,682 + 22,896 = 78,578

'Esc' closes window.*/