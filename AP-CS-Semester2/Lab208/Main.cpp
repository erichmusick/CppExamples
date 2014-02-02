/* Title     - Cooney
* File name - Lab208
* Programmer- 413 Erich Musick
* Assigned  - 2/26/02
* Due       - 3/7/02
* IPO       - This program plays the "Cooney" game.  Workbook page 55 #13
*             The program gives examples of what Cooney likes and does not.
*             The program then asks the user to enter a word for analysis.
*             If the word has a double letter, it is reported as liked and
*             the count of number of good guesses in a row goes up,
*             else the good guess count is reset to zero and it is reported
*             that Cooney does not like that word.
*             If the good guesses in a row makes it to 5 the program quits
*             otherwise the user is asked if they would like to enter another
*             word for analysis.
*/

#include <iostream>
#include <string>

using namespace std;

// toUpper  pre-condition  ch is a character
//         post-condition  if ch is a lower case letter, its upper case value
//                         is returned, else, the original letter is returned

char toUpper(char ch) {
	int offset = int('A') - int('a');

	if (ch >= 'a' && ch <= 'z') {
		ch = char(int(ch) + offset);
	}
	return ch;
}
// cooneyLikes pre-condition  word is an strin
//        post-condition returns true if word has the same letter two
//                       positions in a row (capital and lower case ignored)
//                       otherwise returns false.

bool cooneyLikes(const string&word) {
	int  i;         // Used as index into word (word[i]) to get individual chars.
	bool foundpair; // false unless two consecutive letters are the same.  Upper
	// and lower case is ignored i.e. aa AA aA and Aa all are good
	int  len;       // number of letters in word (use to end loop looking at word)

	len = word.length();
	foundpair = false;

	i = 0;
	while (i < (len - 1) && foundpair == false) {
		if (toUpper(word[i]) == toUpper(word[i + 1])) {
			foundpair = true;
		}

		i++;
	}

	return foundpair;
}
//****************************************************************

int main() {
	string word;
	char     another;
	int      guessCount;

	cout << "\n\n";
	cout << "Try to figure out what Cooney likes:\n\n";
	cout << "Cooney likes MOON but he doesn't like SUN\n";
	cout << "Cooney likes SOCCER but he doesn't like HOCKEY\n";
	cout << "Cooney likes SUMMER but he doesn't like SPRING\n";

	guessCount = 0;

	do { // Repeat as long as the user wants to continue:
		cout << "\nDoes Cooney like ... (enter one word) ==> ";
		cin >> word;
		cin.ignore(1000, '\n');  // throw out any extra words entered
		if (cooneyLikes(word)) {
			cout << "Yes, Cooney likes " << word << "\n";
			guessCount++;
		}
		else {
			cout << "No, Cooney doesn't like " << word << "\n";
			guessCount = 0; // Reset the count of consecutive guesses to 0
		}
		if (guessCount >= 5){
			cout << "\nI think you got the rule... I quit!\n\n";
		}
		else {
			do { // ask whether the user wants to continue:
				cout << "Another word? (y/n): ";
				cin >> another;
				another = toUpper(another);         // force to upper case
				cin.ignore(1000, '\n');      // throw out the rest of word if no or yes
			} while (another != 'Y' && another != 'N'); // and not just y or n
		}
	} while (another == 'Y' && guessCount<5);

	cout << "\nThaanks forr pplaying!\n";

	return 0;
}
//---------------------------------End Program--------------------------------

/*              LAB208 by 413 ERICH MUSICK   11:06 on Feb 13 2002



Try to figure out what Cooney likes:

Cooney likes MOON but he doesn't like SUN
Cooney likes SOCCER but he doesn't like HOCKEY
Cooney likes SUMMER but he doesn't like SPRING

Does Cooney like ... (enter one word) ==> moon
Yes, Cooney likes moon
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> sun
No, Cooney doesn't like sun
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> soccer
Yes, Cooney likes soccer
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> hockey
No, Cooney doesn't like hockey
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> summer
Yes, Cooney likes summer
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> spring
No, Cooney doesn't like spring
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> yahoo
Yes, Cooney likes yahoo
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> erich
No, Cooney doesn't like erich
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> cooney
Yes, Cooney likes cooney
Another word? (y/n): y

Does Cooney like ... (enter one word) ==> cOoney
Yes, Cooney likes cOoney
Another word? (y/n): n

Thaanks forr pplaying!

'Esc' closes window.*/