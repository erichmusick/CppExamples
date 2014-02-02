/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab212.cpp
* Programmer - 413 Erich Musick
* Turned in  - March 19, 2002
* Input      - None.
* Process/Output - Using a for loop and the new constructor in the string
*                    class that I wrote, a triangle is displayed on the screen.
*/

/****  I N C L U D E   F I L E S  ****/

#include <iostream>
#include <string>

using namespace std;

//MyString(const int length, const char fillCharacter = ' ');

class MyString : std::string
{
	public:
	MyString::MyString(const int length, const char fillCharacter = ' ')
	{
		this->capacity = length + 1; // +1 for the terminating null
		this->c_str = new char[this->capacity];
		
		// Fill the string with the fill character
		for (int index = 0; index < length; index++) {
			this->c_str[index] = fillCharacter;
		}

		// Add the null character to the end of the string.
		this->c_str[this->c_str - 1] = '\0';
	}
};

/****  F U N C T I O N   P R O T O T Y P E S  ****/
void displayProgramInformation();

/****  F U N C T I O N S  ****/

// DISPLAY PROGRAM INFORMATION
/* Purpose    - Introduce the program to the user
* Parameters - None.
* Input      - None.
* Process    - None.
* Output     - Display some information about the program
* Return     - None.
*/
void displayProgramInformation() {

	cout << "CONSTRUCTOR TEST\n";
	cout << "Tests a new constructor added to the string class by building a ";
	cout << "triangle.\n\n";

	return;

}

/****   M A I N  ****/

int main() {

	int numberOfSpaces;         // Number of spaces on current line
	int numberOfCharacters;     // Number of characters on current line
	char fillCharacter = '*';   // Character to use for the triangle

	// OUTPUT: Display some information about the program
	displayProgramInformation();

	numberOfCharacters = 1;
	numberOfSpaces = 6;
	while (numberOfSpaces >= 0) {
		// PROCESS: Define a variable that pads the triangle so it is centered.
		// This uses the new constructor in strin.cpp
		MyString spaces(numberOfSpaces);

		// PROCESS: Define a variable that contains the proper number of symbols for
		// this line of the triangle. This uses the new constructor in strin.cpp
		MyString characters(numberOfCharacters, fillCharacter);

		// OUTPUT: Display the spaces, characters, and a new line.
		cout << spaces;
		cout << characters;
		cout << endl;

		// PROCESS: Increment/decrement the number of characters and spaces for the
		// next loop iteration.
		numberOfCharacters += 2;
		numberOfSpaces--;
	}

	return 0;

}

/*              LAB212 by 413 ERICH MUSICK   11:34 on Mar 18 2002

CONSTRUCTOR TEST
Tests a new constructor added to the string class by building a triangle.

*
***
*****
*******
*********
***********
*************

'Esc' closes window.*/

/*

// ADDED TO strin.H:

strin(const int length, const char fillCharacter = ' ');
// Builds a string of size length and fills with
// the value stored in fillCharacter (e.g., length=5
// and fillCharacter='*' will give you *****) If no
// character is specified, fillCharacter is set to
// a space

// ADDED TO strin.CPP:

strin::strin(const int length, const char fillCharacter)

{

int index;

mCapacity = length + 1;       // +1 for the terminating null
mCstring = new char[mCapacity];

// Fill the string with the fill character
for (index = 0; index < mCapacity - 1; index++) {
mCstring[index] = fillCharacter;
}

// Add the null character to the end of the string.
mCstring[mCapacity - 1] = '\0';

}

*/