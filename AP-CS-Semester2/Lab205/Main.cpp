/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab205.cpp   // Only show and list need modifications
* Programmer - 413 Erich Musick
* Assigned   - Wednesday February 13, 2002
* Due        - Thursday  February 14, 2002
* Turned in  - Wednesday February 13, 2002
* Purpose    - This program illustrates the use of simple one-character
*              commands.  The program displays a menu, accepts a command
*              and executes it.  The application is an embryonic
*              "Inventory Control System" which, at this stage of development,
*              only maintains a list of "inventory items" (integers).
*              Items are stored in an integer array. The "quantity" is
*              not supported -- it is set to 1 for all inventory items.
*/

/****  I N C L U D E   F I L E S  ****/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****  D E F I N E   A N   I N V E N T O R Y   D A T A   T Y P E  ****/

typedef int inventoryType;    // Modified in a later version to a structure
const int QUANTITY = 1;        // Quantity for each item is set
//   to 1 in this preliminary version.
//   part if stucture in later version

/****  F U N C T I O N   P R O T O T Y P E S  ****/

void add(vector<inventoryType> &inventory, int partNum);
int  find(const vector<inventoryType> &inventory, int partNum);
void list(const vector<inventoryType> &inventory);
void show(const vector<inventoryType> &inventory, int partNum);
void remove(vector<inventoryType> &inventory, int partNum);

/****   M A I N  ****/

int main(){

	vector<inventoryType> inventory;   // Array of items (initially empty)
	char cmd;
	int partNum;

	cout << "\n          One Of Each, Inc.\n";
	cout << "      Inventory Control System\n";

	do{

		// Show the menu and prompt:

		cout << setw(60) << ' ' << "Item count: " << inventory.size();
		cout << "\n";  // Output a blank line

		cout << "\t (S)how inventory item\n";      // '\t' is tab
		cout << "\t (A)dd item\n";
		cout << "\t (R)emove item\n";
		cout << "\t (L)ist inventory\n";
		cout << "\t (Q)uit\n";
		cout << endl;
		cout << "Next command ==> ";

		// Accept command:

		cin >> cmd;             // Read one char.
		cin.ignore(80, '\n');   // Skip remaining input (up to 80
		//   chars) to the end of the line.
		cmd = toupper(cmd);     // Convert letter to upper case
		//   to allow lower case input
		//   for commands (for convenience).


		cout << "\n\n****************************************\n";

		// Process command:

		switch (cmd){

		case 'S':           // Show inventory item information
			cout << "Part number: ";
			cin >> partNum;
			show(inventory, partNum);
			break;
		case 'A':
			cout << "Add part number: ";
			cin >> partNum;
			add(inventory, partNum);
			break;
		case 'R':
			cout << "Remove part number: ";
			cin >> partNum;
			remove(inventory, partNum);
			break;
		case 'L':
			list(inventory);
			break;
		case 'Q':
			break;
		default: // invalid command processing
			break;
		}

		cout << "****************************************\n";
	} while (cmd != 'Q');

	return 0;
}

/****  F I N D   ****/

// Finds the part number, partNum, in the inventory array.
// Returns its index if found, -1 otherwise.

int find(const vector<inventoryType> &inventory, int partNum){

	int i;
	int nItems;
	int foundAt;

	nItems = inventory.size(); // Number of existing items
	foundAt = -1;  // The default value is 'not found'

	i = 0;
	while ((i<nItems) && (foundAt == -1)){
		if (inventory[i] == partNum){  // Found match so save index
			foundAt = i;
		}
		else{  // Part number not found yet so setup to check next item
			i++;
		}
	}
	return foundAt;
}

/****  A D D   ****/

// Adds the new inventory item with the specified part number,
//   partNum, to the inventory list.
//   Checks whether partNum is already in the list.

void add(vector<inventoryType> &inventory, int partNum){

	int nItems;

	if (find(inventory, partNum) >= 0){
		cout << "Part number " << partNum;
		cout << " already registered in the inventory list.\n";
	}
	else{
		nItems = inventory.size();
		inventory.resize(nItems + 1);
		inventory[nItems] = partNum;
		cout << "Part number " << partNum << " added to the inventory list.\n";
	}

	return;
}

/****  R E M O V E   ****/

// Removes the item partNum from the inventory list, if it
//   is there.  Displays an appropriate message if partNum is not
//   in the list.

void remove(vector<inventoryType> &inventory, int partNum) {

	int indexOfPartToRemove;
	int j;
	int nItems;

	indexOfPartToRemove = find(inventory, partNum);
	if (indexOfPartToRemove < 0) {
		cout << "Part number " << partNum << " was not found in inventory.\n";
	}
	else {
		nItems = inventory.size();
		for (j = indexOfPartToRemove + 1; j < nItems; j++){  // Shift items back one
			inventory[j - 1] = inventory[j];                   // to fill the gap.
		}

		inventory.resize(nItems - 1);     // Reduce vector length
		cout << "Part number " << partNum << " removed from the inventory list.\n";
	}

	return;
}

/****  L I S T  ****/

// List displays a heading for all the fields in inventoryType and then
// displays in neat columns the values from the inventory which is passed in.
// This version and version 2 only have the "Part Number" and "Quantity On Hand"
// Version 3 has:  Part Number  Part Name  Description  Quantity On Hand

/* Sample output for version 3:

Part Number    Part Name             Part Description          Quantity On Hand
===========  =============  =================================  ================
25268     Jacket         Blue letterman's jacket WEGO logo         14
25271     Sweatshirt     XL Green Tiger Woods Golfing logo          2
*/

void list(const vector<inventoryType> &inventory) {
	int index;
	int inventoryLength;

	inventoryLength = inventory.size();

	cout << "Part Number  Quantity On Hand\n";
	cout << "===========  ================\n";

	for (index = 0; index < inventoryLength; index++) {
		cout << setw(11);
		cout << inventory[index];
		cout << setw(18);
		cout << QUANTITY;
		cout << endl;
	}

	return;
}

/****  S H O W   ****/

// Displays inventory information for the given part number in a column fashion
// or an error message saying 'Invalid Part Number!'
// Part Number      : #####
// Part Name        : ########               // Added in version 3
// Part Description : ###################    // Added in version 3
// Quantity On Hand : ###                    // Global constant until version 3
//  O R
// Part Number ##### is  an Invalid Part Number. (Does not exist)

void show(const vector<inventoryType> &inventory, int partNum) {
	int vectorLocation;

	vectorLocation = find(inventory, partNum);

	if (vectorLocation == -1) {
		cout << "Part Number ";
		cout << partNum;
		cout << " is an Invalid Part Number. (Does not exist)";
		cout << endl;
	}
	else {
		cout << "Part Number      : ";
		cout << inventory[vectorLocation];
		cout << endl;
		cout << "Quantity On Hand : ";
		cout << QUANTITY;
		cout << endl;
	}

	return;
}

/*
****************************************
Add part number: 23466
Part number 23466 added to the inventory list.
****************************************
Item count: 2
(S)how inventory item
(A)dd item
(R)emove item
(L)ist inventory
(Q)uit

Next command ==> l


****************************************
Part Number  Quantity On Hand
===========  ================
23456                 1
23466                 1
****************************************
Item count: 2
(S)how inventory item
(A)dd item
(R)emove item
(L)ist inventory
(Q)uit

Next command ==> s


****************************************
Part number: 23456
Part Number      : 23456
Quantity On Hand : 1
****************************************
Item count: 2
(S)how inventory item
(A)dd item
(R)emove item
(L)ist inventory
(Q)uit

Next command ==> q


****************************************
****************************************

'Esc' closes window.*/