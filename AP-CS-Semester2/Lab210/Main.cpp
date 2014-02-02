/* Course         - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor     - M r .  B u r z y n s k i
* Lab name       - Reverse It
* Lab number     - Lab210.cpp
* Programmer     - 413 Erich Musick
* Date Assigned  - 02/15/02
* Date Turned in - 03/11/02
* Purpose        - Write and test a function to reverse the order of a string
*                  of characters.  Example abcd becomes dcba
*/

#include <iostream>
#include <string>

using namespace std;

// reverse receives an string"str" and reverses the letters and returns the
// string "str" so that str[0] = str[len-1], str[1] = str[len-2] ...
// Do not create a temporary string inside the function.
void reverse(string& str){

	int stringLength;
	int index;
	int index2;
	char temp;

	stringLength = str.length();
	for (index = 0; index < (stringLength / 2); index++) {
		index2 = stringLength - (index + 1);

		temp = str[index];
		str[index] = str[index2];
		str[index2] = temp;
	}

	return;
}

/******  M a i n   P r o g r a m  ******/

int main(int argc, char**argv)
{

	cout << argv[argc - 1] << "\n\n";

	string myString;

	cout << "Enter a string of characters (quit to quit): ";
	getline(cin, myString);

	while (myString != "quit"){
		reverse(myString);

		cout << "Reversed is : \"" << myString << "\"\n";

		cout << "Enter a string of characters (quit to quit): ";
		getline(cin, myString);
	}

	return 0;

}

/*              LAB210 by 413 ERICH MUSICK   11:45 on Mar  8 2002

G:\CPLUS\413 ERICH MUSICK\TEMP\LAB210.EXE

Enter a string of characters (quit to quit): abcd
Reversed is : "dcba"
Enter a string of characters (quit to quit): erich
Reversed is : "hcire"
Enter a string of characters (quit to quit): erich musick
Reversed is : "kcisum hcire"
Enter a string of characters (quit to quit): 2334332
Reversed is : "2334332"
Enter a string of characters (quit to quit): Error
Reversed is : "rorrE"
Enter a string of characters (quit to quit): quit

'Esc' closes window.*/