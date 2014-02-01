/* Course         - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor     - M r .  B u r z y n s k i
* Lab name       - A P V E C T O R   A N D   F U N C T I O N S
* Lab number     - Lab08.cpp
* Programmer     - 415 Erich Musick
* Date Assigned  - 09/29/00
* Date Due       - 10/07/00
* Date Turned in -
* Purpose        - This program repeatedly asks for an array of numbers
*                - and then displays those numbers as a comma separated
*                - list, a tab 10 separated list, a check type value with
*                - leading dollar signs to prevent changing the value list
*                - and finally an average of the list values is displayed.
* Input          - The user supplies the number of numbers in the list and
*                - then the value of that many numbers.  The numbers are real
*                - numbers.  A zero entered for the number of numbers ends
*                - the program.
* Process        - The average of the numbers entered is calculated.
* Output         - 1: a comma separated list
*                - 2: a list set up to print values so that the last digits
*                -    of each number are 10 characters apart.
*                - 3: a column list with each value printed to represent
*                -    dollars and cents with leading $'s to prevent forged
*                -    checks.
*                - 4: the calculated average of the numbers
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

/*****************************************************************************/
/***************     F U N C T I O N  P R O T O T Y P E S     ****************/
/*****************************************************************************/
void displayCentered(string text);
void printHeading();
int getHowManyAmounts();
void resizeVector(vector<double> &v, int size);
void getAmounts(vector<double> &amount);
void displayAsCommaSeparatedList(vector<double> amount);
void displayAsTab10List(vector<double> amount);
void displayAsColumnOfDollarsAndCents(vector<double> amount);
void displayTheAverage(double theAverage);
double averageOfAmounts(vector<double> amount);

/*****************************************************************************/
/************************     F U N C T I O N S     **************************/
/*****************************************************************************/

// D I S P L A Y   C E N T E R E D

/* purpose    - Print an string centered on the screen.
* parameters - A value parameter of type string containing the text
*            - which is to be centered.
* input      - None.
* process    - None.
* output     - The string centered on the screen.
* return     - Nothing.  It is a void function.
*/

void displayCentered(string text) {
	const int screenWidth = 60;
	const int center = screenWidth / 2;
	int length;
	int charactersBeyondCenter;
	int widthToLastCharacter;

	length = text.size();
	charactersBeyondCenter = length / 2;
	widthToLastCharacter = center + charactersBeyondCenter;

	cout << setw(widthToLastCharacter);
	cout << text;
	cout << endl;

	return;
}

/*****************************************************************************/

// P R I N T   H E A D I N G

/* purpose    - Print a heading before asking for any input.
* parameters - None.
* input      - None.
* process    - None.
* output     - Name of program and programmer, both centered.
* return     - Nothing.  It is a void function
*/

void printHeading()
{
	string  title = "vector and Functions";
	string  author = "415 Erich Musick";

	displayCentered(title);
	displayCentered("by");
	displayCentered(author);
	cout << "\n\n";

	return;
}

/*****************************************************************************/

// G E T   H O W   M A N Y   A M O U N T S

/* purpose    - This is the amount of numbers you are supposed to get.
* parameters - None.
* input      - The number of numbers that the list will contain.
* process    - None.
* output     - None.
* return     - The number of numbers the list should hold.
*/

int getHowManyAmounts() {
	int numberOfAmounts;

	cout << "Enter number of amounts (0 to quit): ";
	cin >> numberOfAmounts;

	return numberOfAmounts;
}

/*****************************************************************************/

// R E S I Z E   V E C T O R

/* purpose    -  This functions resizes the vector passed in to the size
*            -  which is also passed in.
* parameters -  v - an vector of doubles (output)
*            -  size - an integer containing the desired size (input)
* input      -  None.
* process    -  The vector v is resized to size.
* output     -  None.
* return     -  None.
*/

void resizeVector(vector<double> &v, int size) {
	v.resize(size);

	return;
}

/*****************************************************************************/

// G E T   A M O U N T S

/* purpose     - To get the values of the numbers
* parameters  - amount - an vector of doubles (input)
* input       - The values of the list
* process     - Put the numbers into the list
* output      - none
* return      - nothing
*/

void getAmounts(vector<double> &amount) {
	int arraySubscript;
	int valueNumber;
	int numberOfAmounts = amount.size();

	for (arraySubscript = 0; arraySubscript < numberOfAmounts; arraySubscript++) {
		valueNumber = arraySubscript + 1;
		cout << "Enter value ";
		cout << valueNumber;
		cout << ": ";
		cin >> amount[arraySubscript];
	}
	cout << endl;

	return;
}

/*****************************************************************************/

//  D I S P L A Y   A S   C O M M A   S E P A R A T E D   L I S T

/* purpose    - Display the amounts as a comma separated list
* parameters - amount - an vector of doubles (output)
* input      - None.
* process    - None.
* output     - Display amounts, separated by commas
* return     - None.
*/

void displayAsCommaSeparatedList(vector<double> amount) {
	int arraySubscript;
	int numberOfAmounts = amount.size();

	for (arraySubscript = 0; arraySubscript < numberOfAmounts; arraySubscript++) {
		if (arraySubscript != 0) {
			cout << ", ";
		}
		cout << amount[arraySubscript];
	}
	cout << endl;
	cout << endl;
	return;
}

/*****************************************************************************/

// D I S P L A Y   A S   T A B 1 0   L I S T

/* purpose    - Display amounts as a tab10 separated list
* parameters - amount - vector of doubles (output)
* input      - None.
* process    - None.
* output     - Display amounts, each gets 10 "spaces" to fill
* return     - None.
*/

void displayAsTab10List(vector<double> amount) {
	int arraySubscript;
	int numberOfAmounts = amount.size();

	for (arraySubscript = 0; arraySubscript < numberOfAmounts; arraySubscript++) {
		cout << setw(10);
		cout << amount[arraySubscript];
	}
	cout << endl;
	cout << endl;

	return;
}

/*****************************************************************************/

// D I S P L A Y   A S   C O L U M N   O F   D O L L A R S   A N D   C E N T S

/* purpose    - Display the amounts as a column of dollars and cents
* parameters - amount - vector of doubles (output)
* input      - None.
* process    - None.
* output     - Display each amount on a separate value, with dollar signs in
front of each number, so that they all fill the same amount
of space
* return     - None.
*/

void displayAsColumnOfDollarsAndCents(vector<double> amount) {
	int arraySubscript;
	int numberOfAmounts = amount.size();

	for (arraySubscript = 0; arraySubscript < numberOfAmounts; arraySubscript++) {
		cout << setw(8);
		cout << setfill('$');
		cout.setf(ios::showpoint | ios::fixed);
		cout << setprecision(2);
		cout << amount[arraySubscript];
		cout << setfill(' ');
		cout.unsetf(ios::showpoint | ios::fixed);
		cout << setprecision(0);
		cout << endl;
	}
	cout << endl;

	return;
}

/*****************************************************************************/

// D I S P L A Y   T H E   A V E R A G E

/* purpose    - Display the average of the amounts
* parameters - theAverage - type: double (output)
* input      - None.
* process    - None.
* output     - Displays the average of the amounts
* return     - None.
*/

void displayTheAverage(double theAverage) {
	cout << "The average of the amounts is: ";
	cout << theAverage;
	cout << endl;
	cout << endl;
	return;
}

/*****************************************************************************/

// A V E R A G E   O F   A M O U N T S

/* purpose    - Calculate the average of the amounts
* parameters - amount - vector of doubles (process)
* input      - None.
* process    - All amounts are added to a variable, then divided by the
number of amounts (the average is calulated)
* output     - None.
* return     - The average that is calulated.
*/

double averageOfAmounts(vector<double> amount) {
	double amountsTotal = 0;
	double amountsAverage;
	int arraySubscript;
	int numberOfAmounts = amount.size();

	for (arraySubscript = 0; arraySubscript < numberOfAmounts; arraySubscript++) {
		amountsTotal = amountsTotal + amount[arraySubscript];
	}

	amountsAverage = amountsTotal / numberOfAmounts;

	return amountsAverage;
}

/*****************************************************************************/
/***********************  M A I N   P R O G R A M  ***************************/
/*****************************************************************************/

int main() {
	//  D E C L A R E   V A R I A B L E S

	vector<double> amount;
	int              numberOfAmounts;
	double           average;

	// P R I N T   H E A D I N G

	printHeading();

	// I N P U T

	numberOfAmounts = getHowManyAmounts();

	while (numberOfAmounts > 0) {
		resizeVector(amount, numberOfAmounts);
		getAmounts(amount);

		// P R O C E S S

		average = averageOfAmounts(amount);

		// O U T P U T

		displayAsCommaSeparatedList(amount);
		displayAsTab10List(amount);
		displayAsColumnOfDollarsAndCents(amount);
		displayTheAverage(average);

		// I N P U T  F O R   N E X T   S E T   O F   N U M B E R S

		numberOfAmounts = getHowManyAmounts();

	} // End of while loop

	return 0;
}

/*               LAB08 by 415 ERICH MUSICK   11:00 on Sep 25 2001

vector and Functions
by
415 Erich Musick


Enter number of amounts (0 to quit): 4
Enter value 1: 23.593
Enter value 2: 65.238
Enter value 3: 12.492
Enter value 4: 59

23.593, 65.238, 12.492, 59

23.593    65.238    12.492        59

$$$23.59
$$$65.24
$$$12.49
$$$59.00

The average of the amounts is: 40.0808

Enter number of amounts (0 to quit): 0

'Esc' closes window.*/