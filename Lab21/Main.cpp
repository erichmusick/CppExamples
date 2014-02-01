/* Title      - Prime Factorization
 * File name  - Lab21
 * Programmer - 415 Erich Musick
 * IPO        - Input   - User inputs the first and last numbers in a range
 *              Process - Prime factorization for each number is calculated
 *              Output  - After being calculated, each prime factorization is displayed
 */

/*************************** H E A D E R  F I L E S ***************************/

#include <iostream>
#include <vector>
#include "../Common/CommonFunctions.h"

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
int getStartNumber();
int getEndNumber();
void factorANumber(int number, vector<int> &factorization);
void displayFactors(int startNumber, int endNumber);
bool goAgain();

/****************************** F U N C T I O N S *****************************/
// GET START NUMBER
/* purpose    - Get the first number in the range of numbers to factor
* parameters - None.
* input      - startNumber, integer type that will hold first number of range
* process    - None.
* output     - None.
* return     - startNumber
*/
int getStartNumber() {
	int startNumber;

	do {
		cout << "At what positive integer would you like to start? ";
		cin >> startNumber;
		cin.ignore(80, '\n');
	} while (startNumber <= 0);

	return startNumber;
}

// GET END NUMBER
/* purpose    - Get the last number in the range of numbers to factor
* parameters - None.
* input      - endNumber, integer type that will hold the last value of range
* process    - None.
* output     - None.
* return     - endNumber
*/
int getEndNumber() {
	int endNumber;

	do {
		cout << "At what positive integer would you like to stop? ";
		cin >> endNumber;
		cin.ignore(80, '\n');
	} while (endNumber <= 0);
	cout << endl;

	return endNumber;
}

// FACTOR A NUMBER
/* purpose    - Calculate the prime factorization of a number
* parameters - number - integer type containing number to factor
*            - factors - reference vector of integers that will hold factors
* input      - None.
* process    - Using a while loop, prime factorization of number is calculated
* output     - None.
* return     - None.
*/
void factorANumber(int number, vector<int> &factors, vector<int> primes) {
	int index;
	int vectorSize;
	bool foundPrime;

	factors.resize(0);
	vectorSize = 0;

	index = 0;
	while (number > 1) {
		foundPrime = false;
		while ((number % primes[index]) == 0) {
			vectorSize++;
			factors.resize(vectorSize);
			factors[vectorSize - 1] = primes[index];

			number = number / primes[index];

			foundPrime = true;
		}

		if (primes[index] > sqrt(double(number)) && !foundPrime) {
			vectorSize = vectorSize + 1;
			factors.resize(vectorSize);
			factors[vectorSize - 1] = number;
			break;
		}

		index++;
	}

	return;
}

// Display Factors
/* purpose    - Display the prime factorizations of the numbers in the range
* parameters - startNumber - integer containing the first number in the range
*            - endNumber - integer containing the last number in the range
* input      - None.
* process    - None.
* output     - Using for loops, the program starts at the first number in the
*                range. The factorization is calculated using factorANumber()
*                and is then displayed. The process is repeated until after the
*                last number in the range is displayed. To prevent the screen
*                from scrolling, the program pauses after every 45
*                factorizations.
* return     - None.
*/
void displayFactors(int startNumber, int endNumber, vector<int> primes) {
	vector<int> factors;
	int currentNumber;
	int vectorIndex;
	int vectorSize;
	int temp;
	int count;

	if (startNumber > endNumber) {
		temp = startNumber;
		startNumber = endNumber;
		endNumber = temp;
	}

	for (currentNumber = startNumber, count = 1; currentNumber <= endNumber;
		currentNumber++, count++) {
		factorANumber(currentNumber, factors, primes);
		cout << currentNumber;
		cout << " = ";
		vectorSize = factors.size();
		for (vectorIndex = 0; vectorIndex < vectorSize; vectorIndex++) {
			if (vectorIndex != 0) {
				cout << " * ";
			}
			cout << factors[vectorIndex];
		}
		if (vectorSize == 0) {
			cout << "Not a prime or composite number";
		}
		if (vectorSize == 1) {
			cout << " - Number is prime";
		}
		cout << endl;

		/*  if ((count % 45) == 0 && currentNumber != endNumber) {
		cout << endl;
		cout << "Press a key to continue.";
		cout << endl;
		cout << endl;
		getCharacter = getch();
		__flush_win95_keyup_events();
		clrscr();
		} */

	}

	return;
}

vector<int> getPrimes(int max) {
	vector<int> primes = { 2 };
	int vectorSize;
	int factor;
	bool foundFactor;
	
	vectorSize = 1;
	// max = 65535;
	for (int currentNumber = 3; currentNumber <= max; currentNumber += 2) {

		factor = 3;
		while (factor > 1) {
			foundFactor = false;
			if ((currentNumber % factor) == 0) {
				foundFactor = true;
			}
			factor += 2;

			if ((factor > sqrt(double(currentNumber)) && !foundFactor) || !foundFactor) {
				break;
			}
		}

		if (!foundFactor) {
			vectorSize++;
			primes.resize(vectorSize);
			primes[vectorSize - 1] = currentNumber;
		}
	}

	return primes;
}

// GO AGAIN
/* purpose    - Determine whether the user would like to display another diamond
* parameters - None.
* input      - yORn, a char that is used to hold user's input ('y' or 'n')
* process    - Based on the value in yORn, returnValue is set to true or false,
*                true if the user would like to go again, false if the user
*                would like to quit.
* output     - None.
* return     - returnValue, bool - possible values described in "process"
*/
bool goAgain() {
	int xLocation;
	int yLocation;
	char yORn;
	bool returnValue;

	cout << "Go again ('y' or 'n')? ";
	xLocation = Common::GetCursorXPosition();
	yLocation = Common::GetCursorYPosition();
	do {
		Common::GoToXY(xLocation, yLocation);
		Common::ClearToEndOfLine();
		cin >> yORn;
	} while (yORn != 'y' && yORn != 'n');
	cin.ignore(80, '\n');

	if (yORn == 'y') {
		returnValue = true;
	}
	else {
		returnValue = false;
	}

	return returnValue;
}

int main() {
	int startNumber;
	int endNumber;
	bool firstTime;
	bool dispMoreFactorizations;
	vector<int> primes;

	firstTime = true;
	do {
		if (firstTime) {
			cout << "PRIME FACTORIZATION";
			cout << endl;
			cout << "Given a range of positive numbers, displays prime factorization for each.";
			cout << endl;
			cout << endl;
			firstTime = false;
		}
		else {
			cout << endl;
		}

		// USER INPUT: Get first and last numbers of the range
		startNumber = getStartNumber();
		endNumber = getEndNumber();

		primes = getPrimes(endNumber);

		// PROCESS/DISPLAY: calculate and display prime factorizations
		displayFactors(startNumber, endNumber, primes);

		// USER INPUT: go again?
		cout << endl;
		dispMoreFactorizations = goAgain();
	} while (dispMoreFactorizations);

	return 0;
}

/************************** S A M P L E  O U T P U T **************************/

/*               LAB21 by 415 ERICH MUSICK   11:23 on Dec 20 2001

PRIME FACTORIZATION
Given a range of positive numbers, displays prime factorization for each.

At what positive integer would you like to start? 1
At what positive integer would you like to stop? 45

1 = Not a prime or composite number
2 = 2 - Number is prime
3 = 3 - Number is prime
4 = 2 * 2
5 = 5 - Number is prime
6 = 2 * 3
7 = 7 - Number is prime
8 = 2 * 2 * 2
9 = 3 * 3
10 = 2 * 5
11 = 11 - Number is prime
12 = 2 * 2 * 3
13 = 13 - Number is prime
14 = 2 * 7
15 = 3 * 5
16 = 2 * 2 * 2 * 2
17 = 17 - Number is prime
18 = 2 * 3 * 3
19 = 19 - Number is prime
20 = 2 * 2 * 5
21 = 3 * 7
22 = 2 * 11
23 = 23 - Number is prime
24 = 2 * 2 * 2 * 3
25 = 5 * 5
26 = 2 * 13
27 = 3 * 3 * 3
28 = 2 * 2 * 7
29 = 29 - Number is prime
30 = 2 * 3 * 5
31 = 31 - Number is prime
32 = 2 * 2 * 2 * 2 * 2
33 = 3 * 11
34 = 2 * 17
35 = 5 * 7
36 = 2 * 2 * 3 * 3
37 = 37 - Number is prime
38 = 2 * 19
39 = 3 * 13
40 = 2 * 2 * 2 * 5
41 = 41 - Number is prime
42 = 2 * 3 * 7
43 = 43 - Number is prime
44 = 2 * 2 * 11
45 = 3 * 3 * 5

Go again ('y' or 'n')? n

'Esc' closes window.*/

/*               LAB21 by 415 ERICH MUSICK   11:23 on Dec 20 2001

PRIME FACTORIZATION
Given a range of positive numbers, displays prime factorization for each.

At what positive integer would you like to start? 60
At what positive integer would you like to stop? 75

60 = 2 * 2 * 3 * 5
61 = 61 - Number is prime
62 = 2 * 31
63 = 3 * 3 * 7
64 = 2 * 2 * 2 * 2 * 2 * 2
65 = 5 * 13
66 = 2 * 3 * 11
67 = 67 - Number is prime
68 = 2 * 2 * 17
69 = 3 * 23
70 = 2 * 5 * 7
71 = 71 - Number is prime
72 = 2 * 2 * 2 * 3 * 3
73 = 73 - Number is prime
74 = 2 * 37
75 = 3 * 5 * 5

Go again ('y' or 'n')? y

At what positive integer would you like to start? 90
At what positive integer would you like to stop? 100

90 = 2 * 3 * 3 * 5
91 = 7 * 13
92 = 2 * 2 * 23
93 = 3 * 31
94 = 2 * 47
95 = 5 * 19
96 = 2 * 2 * 2 * 2 * 2 * 3
97 = 97 - Number is prime
98 = 2 * 7 * 7
99 = 3 * 3 * 11
100 = 2 * 2 * 5 * 5

Go again ('y' or 'n')? n

'Esc' closes window.*/

/*               LAB21 by 415 ERICH MUSICK   11:23 on Dec 20 2001

PRIME FACTORIZATION
Given a range of positive numbers, displays prime factorization for each.

At what positive integer would you like to start? 46
At what positive integer would you like to stop? 100

46 = 2 * 23
47 = 47 - Number is prime
48 = 2 * 2 * 2 * 2 * 3
49 = 7 * 7
50 = 2 * 5 * 5
51 = 3 * 17
52 = 2 * 2 * 13
53 = 53 - Number is prime
54 = 2 * 3 * 3 * 3
55 = 5 * 11
56 = 2 * 2 * 2 * 7
57 = 3 * 19
58 = 2 * 29
59 = 59 - Number is prime
60 = 2 * 2 * 3 * 5
61 = 61 - Number is prime
62 = 2 * 31
63 = 3 * 3 * 7
64 = 2 * 2 * 2 * 2 * 2 *
65 = 5 * 13
66 = 2 * 3 * 11
67 = 67 - Number is prime
68 = 2 * 2 * 17
69 = 3 * 23
70 = 2 * 5 * 7
71 = 71 - Number is prime
72 = 2 * 2 * 2 * 3 * 3
73 = 73 - Number is prime
74 = 2 * 37
75 = 3 * 5 * 5
76 = 2 * 2 * 19
77 = 7 * 11
78 = 2 * 3 * 13
79 = 79 - Number is prime
80 = 2 * 2 * 2 * 2 * 5
81 = 3 * 3 * 3 * 3
82 = 2 * 41
83 = 83 - Number is prime
84 = 2 * 2 * 3 * 7
85 = 5 * 17
86 = 2 * 43
87 = 3 * 29
88 = 2 * 2 * 2 * 11
89 = 89 - Number is prime
90 = 2 * 3 * 3 * 5

Press a key to continue.

91 = 7 * 13
92 = 2 * 2 * 23
93 = 3 * 31
94 = 2 * 47
95 = 5 * 19
96 = 2 * 2 * 2 * 2 * 2 * 3
97 = 97 - Number is prime
98 = 2 * 7 * 7
99 = 3 * 3 * 11
100 = 2 * 2 * 5 * 5

Go again ('y' or 'n')?  n

'Esc' closes window.*/