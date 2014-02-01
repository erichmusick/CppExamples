/* Title      - Credit Card Type
* File name  - Lab18
* Programmer - 415 Erich Musick
* IPO        - Input   - User inputs a credit card number
*              Process - The program determines, based on the first few numbers
*                of the credit card, what type of credit card the number
*                identifies
*              Output  - The type of credit card is displayed
*/

/*************************** H E A D E R  F I L E S ***************************/

#include <iostream>
#include <vector>

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
char CreditCardType(vector<char> cardNumber);

/****************************** F U N C T I O N S *****************************/
// CREDIT CARD TYPE
/* purpose    - Determine the type of credit card using the account number
* parameters - cardNumber - vector of chars containing user's account
*               (credit card) number
* input      - None.
* process    - The program uses a switch statement to determine the card type,
*               based on the first few numbers of the account number
* output     - None.
* return     - cardType - char containing a letter representing the card type
*               Possible values - V (if account is a Visa account)
*                               - M (if account is a Mastercard account)
*                               - A (if account is an American Express acct)
*                               - D (if account is a Discover account)
*                               - X (if account is none of the above)
*/
char CreditCardType(vector<char> cardNumber) {
	char cardType;
	int index;

	switch (cardNumber[0]) {
	case '4':               // If first number is 4, card type is Visa
		cardType = 'V';
		break;

	case '5':               // If first number is 5, card type is Mastercard
		cardType = 'M';
		break;

	case '3':               // If first number is 3, test second number
		switch (cardNumber[1]) {
		case '7':           // If second number is 7, card is American Express
			cardType = 'A';
			break;

		default:
			cardType = 'X';   // Default card type is Unknown
			break;
		}
		break;

	case '6':               // If first number is 6, test second number
		switch (cardNumber[1]) {
		case '0':           // If second number is 0, test third number
			switch (cardNumber[2]) {
			case '1':       // If third number is 1, test fourth number
				switch (cardNumber[3]) {
				case '1':   // If fourth number is 1, card type is Discover
					cardType = 'D';
					break;

				default:    // Default card type is Unknown
					cardType = 'X';
					break;
				}
				break;

			default:        // Default card type is Unknown
				cardType = 'X';
				break;
			}
			break;

		default:            // Default card type is Unknown
			cardType = 'X';
			break;
		}
		break;

	default:               // Default card type is Unknown
		cardType = 'X';
		break;
	}

	return cardType;
}

int main() {
	char goAgain;                   // Contains user input (calculate another?)
	vector<char> cardNumber(16);  // Contains credit card number
	char cardType;                  // Contains card type
	int index;                      // vector index

	cout << "CREDIT CARD TYPE";
	cout << endl;
	cout << "Given a credit card number, this program determines type of ";
	cout << " credit card. The";
	cout << endl;
	cout << "program only recognizes American Express, Discover, Mastercard, and";
	cout << " Visa cards.";
	cout << endl;
	cout << endl;

	do {
		// USER INPUT: get credit card number
		cout << "                                   ";
		cout << "1234567890123456";
		cout << endl;
		cout << "Enter 16-digit credit card number: ";
		for (index = 0; index < 16; index++) {
			cin >> cardNumber[index];
		}
		cin.ignore(80, '\n');

		// PROCESS: determine credit card type
		cardType = CreditCardType(cardNumber);

		// DISPLAY: display card number and type
		cout << endl;

		cout << "Card Number:";
		for (index = 0; index < 16; index++) {
			if ((index % 4) == 0) {     // Display a space after every four digits
				cout << " ";
			}
			cout << cardNumber[index];
		}
		cout << endl;

		cout << "Card Type: ";
		switch (cardType) {
		case 'A':
			cout << "American Express";
			break;

		case 'D':
			cout << "Discover";
			break;

		case 'M':
			cout << "Mastercard";
			break;

		case 'V':
			cout << "Visa";
			break;

		default:
			cout << "Unknown";
			break;
		}
		cout << endl;
		cout << endl;

		// USER INPUT: Loop through again?
		cout << "Again (y/n)? ";
		cin >> goAgain;
		cin.ignore(80, '\n');

		// DISPLAY: Leave an extra space if user would like to loop through again.
		if (goAgain == 'y' || goAgain == 'Y') {
			cout << endl;
		}
	} while (goAgain == 'y' || goAgain == 'Y');

	return 0;
}

/************************** S A M P L E  O U T P U T **************************/
/*               LAB18 by 415 ERICH MUSICK   10:52 on Dec  4 2001

CREDIT CARD TYPE
Given a credit card number, this program determines type of  credit card. The
program only recognizes American Express, Discover, Mastercard, and Visa cards.

1234567890123456
Enter 16-digit credit card number: 3756432165865435

Card Number: 3756 4321 6586 5435
Card Type: American Express

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 3856432154846543

Card Number: 3856 4321 5484 6543
Card Type: Unknown

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 4658465132165445

Card Number: 4658 4651 3216 5445
Card Type: Visa

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 5654846513213465

Card Number: 5654 8465 1321 3465
Card Type: Mastercard

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 6011548946513214

Card Number: 6011 5489 4651 3214
Card Type: Discover

Again (y/n)? n

'Esc' closes window.*/

/*               LAB18 by 415 ERICH MUSICK   10:52 on Dec  4 2001

CREDIT CARD TYPE
Given a credit card number, this program determines type of  credit card. The
program only recognizes American Express, Discover, Mastercard, and Visa cards.

1234567890123456
Enter 16-digit credit card number: 6012987654321564

Card Number: 6012 9876 5432 1564
Card Type: Unknown

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 6022654846513214

Card Number: 6022 6548 4651 3214
Card Type: Unknown

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 6222548465465432

Card Number: 6222 5484 6546 5432
Card Type: Unknown

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 9654231654845234

Card Number: 9654 2316 5484 5234
Card Type: Unknown

Again (y/n)? y

1234567890123456
Enter 16-digit credit card number: 2368548465132123

Card Number: 2368 5484 6513 2123
Card Type: Unknown

Again (y/n)? n

'Esc' closes window.*/
