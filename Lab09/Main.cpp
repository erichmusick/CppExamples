/* Title      - Three Means
 * File name  - Lab09
 * Programmer - 415 Erich Musick
 * IPO        - Input - User inputs two positive integers
                Processing - Arithmetic, geometric, and harmonic means are calculated
                Output - Arithmetic, geometric, and harmonic means are displayed
*/

#include <iostream>

using namespace std;

// Arithmetic Mean
/* purpose    - Calculate the arithmetic mean, using the formula (a+b)/2
* parameters - a - a short containing the first integer (process)
- b - a short containing the second integer (process)
* input      - None.
* process    - Arithmetic mean is calculated
* output     - None.
* return     - aMean - arithmetic mean
*/
double ArithmeticMean(short a, short b) {
	double aMean;

	aMean = double(a) + double(b) / 2.;

	return aMean;
}

// Geometric Mean
/* purpose    - Calculate the geometric mean, using the formula square root of
the product of the two shorts
* parameters - a - a short containing the first integer (process)
- b - a short containing the second integer (process)
* input      - None.
* process    - Geometric mean is calculated
* output     - None.
* return     - gMean - geometric mean
*/
double GeometricMean(short a, short b) {
	double gMean;

	gMean = sqrt(double(a)*double(b));

	return gMean;
}

// Harmonic Mean
/* purpose    - Calculate the harmonic mean, using the formula two divided by
the sum of the inverses of a and b

* parameters - a - a short containing the first integer (process)
- b - a short containing the second integer (process)
* input      - None.
* process    - Harmonic mean is calculated
* output     - None.
* return     - hMean - harmonic mean
*/
double HarmonicMean(short a, short b) {
	double hMean;

	hMean = 1. / double(a) + 1. / double(b);
	hMean = 2. / hMean;

	return hMean;
}

//-------------------------Start Main----------------------------------------
int main() {
	short a;
	short b;

	cout << "Enter two positive integers a and b ==> ";
	cout << endl;
	cout << "a? ";
	cin >> a;
	cout << "b? ";
	cin >> b;

	cout << endl;
	cout << "Arithmetic mean of ";
	cout << a;
	cout << " and ";
	cout << b;
	cout << " = ";
	cout << ArithmeticMean(a, b);
	cout << endl;

	cout << endl;
	cout << "Geometric mean of ";
	cout << a;
	cout << " and ";
	cout << b;
	cout << " = ";
	cout << GeometricMean(a, b);
	cout << endl;

	cout << endl;
	cout << "Harmonic mean of ";
	cout << a;
	cout << " and ";
	cout << b;
	cout << " = ";
	cout << HarmonicMean(a, b);
	cout << endl;

	return 0;
}

/*               LAB09 by 415 ERICH MUSICK   11:36 on Oct  4 2001

Enter two positive integers a and b ==>
a? 5
b? 9

Arithmetic mean of 5 and 9 = 7

Geometric mean of 5 and 9 = 6.7082

Harmonic mean of 5 and 9 = 6.42857

'Esc' closes window.*/