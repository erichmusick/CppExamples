/* Title     - First Name
 * File name - Lab01
 * Programmer- 415 Erich Musick
 * IPO       - Input person's first name, no processing, output person's first name
 */

#include <iostream>
#include <string>

using namespace std;

int main() {

	string firstName;

	cout << "Please enter your first name: ";
	cin >> firstName;

	cout << firstName;
	cout << ", congratulations on your first program!";
	cout << endl;

	return 0;

}