/* Title     - Pythagorean Triple
 * File name - Lab04
 * Programmer- 415 Erich Musick
 * IPO       - Input - User enters m and n - two positive integers, where m > n
			   and both m and n are greater than zero
			   Processing - Using m and n, the lengths of three sides of a right
			   triangle (consisting of integer-length sides) are calculated.
			   Output - The pythagorean triplet calculated in the processing
			   step is printed on the user's screen.
 */

#include <iostream>

using namespace std;

int main() {
	int a;
	int b;
	int c;
	int m;
	int n;

	cout << "Enter the larger of two integers greater than zero:\nm? ";
	cin >> m;
	cout << "\nEnter the lesser of the integers (must be greater than zero and not equal to m):\nn? ";
	cin >> n;

	if (m <= n || m <= 0 || n <= 0) {
		cout << "\nError: n must be less than m and both m and n must be greater than zero";
	}
	else {
		a = m*m - n*n;
		b = 2 * m*n;
		c = m*m + n*n;
		cout << "\nPythagorean triple: a = "
			<< a
			<< ", b = "
			<< b
			<< ", c = "
			<< c
			<< endl;
	}
	return 0;
}

/*               LAB04 by 415 ERICH MUSICK   15:54 on Aug 21 2001

Enter the larger of two integers greater than zero:
m? 2

Enter the lesser of the integers (must be greater than zero):
n? 1

Pythagorean triple: a = 3, b = 4, c = 5

'Esc' closes window.*/

/*               LAB04 by 415 ERICH MUSICK   15:54 on Aug 21 2001

Enter the larger of two integers greater than zero:
m? 1

Enter the lesser of the integers (must be greater than zero):
n? 2

Error: n must be less than m and both m and n must be greater than zero
'Esc' closes window.*/

/*               LAB04 by 415 ERICH MUSICK   15:54 on Aug 21 2001

Enter the larger of two integers greater than zero:
m? 0

Enter the lesser of the integers (must be greater than zero):
n? 2

Error: n must be less than m and both m and n must be greater than zero
'Esc' closes window.*/

/*               LAB04 by 415 ERICH MUSICK   15:54 on Aug 21 2001

Enter the larger of two integers greater than zero:
m? 6

Enter the lesser of the integers (must be greater than zero):
n? -3

Error: n must be less than m and both m and n must be greater than zero
'Esc' closes window.*/