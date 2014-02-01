/* Title     - First and Last Name
 * File name - Lab03
 * Programmer- 415 Erich Musick
 * IPO       - Input person's first name and then last name, no processing, output person's first name and last name, with a congrats phrase
 */

#include <iostream>
#include <string>

using namespace std;

int main() {
	string firstName;
	string lastName;

	cout << "Please enter your first name: ";
	cin >> firstName;
	cin.ignore(80, '\n');
	cout << endl << "Please enter your last name: ";
	cin >> lastName;
	cin.ignore(80, '\n');
	cout << endl
		<< firstName
		<< " "
		<< lastName
		<< ", congratulations on your second program!\n";
	return 0;
}

/*               LAB03 by 415 ERICH MUSICK   15:54 on Aug 21 2001

Please enter your first name: Erich

Please enter your last name: Musick

Erich Musick, congratulations on your second program!

'Esc' closes window.*/

