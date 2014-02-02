/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab206.cpp
* Programmer - 413 Erich Musick
* Assigned   - N/A
* Due        - N/A
* Turned in  - February 27, 2002
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
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <conio.h>

#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

/****  D E F I N E   A N   I N V E N T O R Y   D A T A   T Y P E  ****/

typedef int inventoryType;    // Modified in a later version to a structure
const int QUANTITY = 1;        // Quantity for each item is set
//   to 1 in this preliminary version.
//   part of stucture in later version

/****  F U N C T I O N   P R O T O T Y P E S  ****/

void pressEnterToContinue();
int displayMenu();
void loadInventory(vector<inventoryType> &inventory, bool &isSorted);
void saveInventory(vector<inventoryType> &inventory);
void sortInventory(vector<inventoryType> &inventory, bool &isSorted);
void add(vector<inventoryType> &inventory, bool &isSorted);
void addItem(vector<inventoryType> &inventory, int partNum, bool &isSorted);
int find(const vector<inventoryType> &inventory, int partNum, bool isSorted);
int findFromSorted(const vector<inventoryType> &inventory, int partNum);
int findFromUnsorted(const vector<inventoryType> &inventory, int partNum);
void list(const vector<inventoryType> &inventory);
void show(vector<inventoryType> &inventory, bool &isSorted);
void showItem(const vector<inventoryType> &inventory, int partNum, bool isSorted);
void remove(vector<inventoryType> &inventory, bool &isSorted);
void removeItem(vector<inventoryType> &inventory, int partNum, bool isSorted);

// DISPLAY MENU
/* Purpose    - Give the user a list of options
* Parameters - yStartLocation - the line number on which to start the display
*              of the menu
* Input      - Using up/down arrows, user selects an option.
* Process    - None.
* Output     - None.
* Return     - option - integer representing the option the user has selected
*/
int displayMenu(const int yStartLocation) {
	int option;
	int key;
	int cursorLocation;
	const int numberOfMenuItems = 8;

	// DISPLAY: List options available to the user
	Common::GoToXY(1, yStartLocation);
	cout << "OPTIONS:\n";
	cout << "   Load Inventory from disk\n";
	cout << "   Save Inventory to disk\n";
	cout << "   List Inventory\n";
	cout << "   Show Inventory Item\n";
	cout << "   Add Inventory Item\n";
	cout << "   Remove Inventory Item\n";
	cout << "   Sort Inventory\n";
	cout << "   Quit\n\n";
	cout << "Select option using the up, down, page up, page down keys.\n";
	cout << "Press ENTER to accept";

	// INPUT: Move the cursor up and down when the user presses up/down arrows or
	// page up/page down keys
	key = 5;
	cursorLocation = yStartLocation + 1;

	Common::GoToXY(1, yStartLocation + 1);
	cout << "->";

	while (int(key) != 13) {
		key = _getch();
		if (key == 0) {
			key = _getch();
		}

		Common::GoToXY(1, cursorLocation);
		cout << "  ";

		if (key == 72 && cursorLocation > (yStartLocation + 1)) {
			cursorLocation--;
		}
		if (key == 80 && cursorLocation < (yStartLocation + numberOfMenuItems)) {
			cursorLocation++;
		}

		if (key == 73) {          // Page Up key, go to top of menu
			cursorLocation = yStartLocation + 1;
		}

		if (key == 81) {          // Page Down key, go to botom of menu
			cursorLocation = yStartLocation + numberOfMenuItems;
		}

		Common::GoToXY(1, cursorLocation);
		cout << "->";
	}
	/*Sleep(100);
	__flush_win95_keyup_events();*/

	option = cursorLocation - (yStartLocation + 1);

	return option;
}
// PRESS ENTER TO CONTINUE
/* Purpose    - Pause the program until the user presses enter
* Parameters - None.
* Input      - Program waits for user to press enter before continuing
* Process    - Program waits for user to press enter before continuing
* Output     - None.
* Return     - None.
*/
void pressEnterToContinue() {

	char key;

	cout << "\nPress ENTER to continue...";

	key = 'a';
	while (int(key) != 13) {
		key = char(_getch());
		if (key == 0) {
			key = char(_getch());
		}
	}

	return;

}

// LOAD INVENTORY
/* Purpose    - Load the previously saved inventory.
* Parameters - inventory - vector containing the inventory
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - File is opened, data is read and sent to the addItem function
*              to be added to the inventory list
* Output     - If file cannot be opened, displays an error. Otherwise, displays
*              a success message and waits for the user to press enter to
*              continue
* Return     - None.
*/
void loadInventory(vector<inventoryType> &inventory, bool &isSorted) {

	const string fileName = "inventory.txt";
	ifstream diskIn;
	int numberOfItems;          // Number of items in inventory.txt
	int partNum;
	int index;

	diskIn.open(fileName.c_str());

	if (!diskIn) {
		// Display error msg - unable to open file for reading
		cout << "Unable to read from disk: ";
		cout << _sys_errlist[_doserrno];
		cout << ". Please ensure ";
		cout << fileName;
		cout << " exists and can be read.\n";

		pressEnterToContinue();
	}
	else {
		diskIn >> numberOfItems;

		for (index = 0; index < numberOfItems; index++) {
			diskIn >> partNum;

			// Add part number to inventory list. Program doesn't check to see whether
			// or not the number is already in the list because the add function
			// checks new numbers
			addItem(inventory, partNum, isSorted);
		}

		cout << "Inventory successfully loaded.\n";

		pressEnterToContinue();
	}

	return;

}

// SAVE INVENTORY
/* Purpose    - Save the current inventory list to the disk
* Parameters - inventory - vector containing the inventory
* Input      - None.
* Process    - inventory.txt is opened, inventory list is written to it
* Output     - If inventory.txt cannot be opened, displays an error message.
*              Otherwise, displays success message and waits for the user to
*              press enter to continue.
* Return     - None.
*/
void saveInventory(vector<inventoryType> &inventory) {

	const string fileName = "inventory.txt";
	ofstream diskOut;
	int numberOfItems;          // Number of items in inventory array
	int index;

	diskOut.open(fileName.c_str());

	if (!diskOut) {
		// Display error msg - unable to open file for writing
		cout << "Unable to write to disk: ";
		cout << _sys_errlist[_doserrno];
		cout << ". Please ensure ";
		cout << fileName;
		cout << " exists and can be written to.\n";

		pressEnterToContinue();
	}
	else {
		numberOfItems = inventory.size();

		diskOut << numberOfItems;
		diskOut << endl;

		for (index = 0; index < numberOfItems; index++) {
			diskOut << inventory[index];
			diskOut << endl;
		}

		diskOut.close();

		cout << "Inventory data saved to inventory.txt\n";

		pressEnterToContinue();
	}

	return;

}

// FIND
/* Purpose    - Find a part number in the inventory list
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to find
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - If the list is sorted, call findFromSorted function otherwise,
*              call findFromUnsorted function
* Output     - None.
* Return     - foundAt - vector location where part number was found; if not
*              found, returns -1
*/
int find(const vector<inventoryType> &inventory, int partNum, bool isSorted) {

	int foundAt;

	if (isSorted) {
		foundAt = findFromSorted(inventory, partNum);
	}
	else {
		foundAt = findFromUnsorted(inventory, partNum);
	}

	return foundAt;

}

// FIND FROM SORTED
/* Purpose    - Find a part number in the inventory list if it is sorted
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to find
* Input      - None.
* Process    - Uses a binary search to find the partNumber in the inventory
* Output     - None.
* Return     - foundAt - vector location where part number was found; if not
*              found, returns -1
*/
int findFromSorted(const vector<inventoryType> &inventory, int partNum) {
	int vectorLength;
	int left;
	int right;
	int location;
	int foundAt;

	vectorLength = inventory.size();
	left = 0;
	right = vectorLength - 1;
	foundAt = -1;

	while (left <= right && foundAt == -1) {
		location = (left + right) / 2;

		if (inventory[location] < partNum) {
			left = location + 1;
		}
		else if (inventory[location] > partNum) {
			right = location - 1;
		}
		else {
			foundAt = location;
		}
	}

	return foundAt;

}

// FIND FROM UNSORTED
/* Purpose    - Find a part number in the inventory list if it is not sorted
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to find
* Input      - None.
* Process    - Uses a while loop to find the partNumber in the inventory
* Output     - None.
* Return     - foundAt - vector location where part number was found; if not
*              found, returns -1
*/
int findFromUnsorted(const vector<inventoryType> &inventory, int partNum){

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

// ADD
/* Purpose    - Add a new item to the inventory
* Parameters - inventory - vector containing the inventory
*            - isSorted - bool representing whether or not the data is sorted
* Input      - User inputs a part number to add, stored in partNum
* Process    - Calls addItem function to add part number to inventory
* Output     - Waits for user to press enter to continue.
* Return     - None.
*/
void add(vector<inventoryType> &inventory, bool &isSorted){

	int partNum;

	cout << "What part number would you like to add? ";
	cin >> partNum;

	addItem(inventory, partNum, isSorted);

	pressEnterToContinue();

	return;

}

// ADD ITEM
/* Purpose    - Add part number to the inventory if it isn't already in it
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to add
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Calls find function to see if partNum is already in the
*              inventory vector. If partNum isn't already in list, resizes list
*              and adds the part number to the end of the list. If the new
*              part number is smaller than the last number in the inventory
*              list, sets isSorted to false because list won't be sorted
*              any longer.
* Output     - Displays a message saying that the number has been added or
*              that is already exists, whichever is appropriate.
* Return     - None.
*/
void addItem(vector<inventoryType> &inventory, int partNum, bool &isSorted){

	int nItems;

	if (find(inventory, partNum, isSorted) != -1){
		cout << "Part number " << partNum;
		cout << " already registered in the inventory list.\n";
	}
	else{
		nItems = inventory.size();
		inventory.resize(nItems + 1);
		inventory[nItems] = partNum;
		cout << "Part number " << partNum << " added to the inventory list.\n";

		if (nItems > 0 && partNum < inventory[nItems - 1]) {
			isSorted = false;
		}
	}

	return;
}

// REMOVE
/* Purpose    - Remove an item from the inventory
* Parameters - inventory - vector containing the inventory
*            - isSorted - bool representing whether or not the data is sorted
* Input      - User inputs a part number to remove, stored in partNum
* Process    - Calls removeItem function to remove part number from inventory
* Output     - None.
* Return     - None.
*/
void remove(vector<inventoryType> &inventory, bool &isSorted){

	int partNum;

	cout << "What part number would you like to remove? ";
	cin >> partNum;

	removeItem(inventory, partNum, isSorted);

	pressEnterToContinue();

	return;
}

// REMOVE ITEM
/* Purpose    - Removed part number from the inventory if it is in it
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to remove
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Calls find function to see if partNum is already in the
*              inventory vector. If partNum is in list, removes number and
*              resizes inventory array.
* Output     - Displays a message saying that the number has been removed or
*              that it doesn't exist, whichever is appropriate.
* Return     - None.
*/
void removeItem(vector<inventoryType> &inventory, int partNum, bool isSorted) {

	int indexOfPartToRemove;
	int j;
	int nItems;

	indexOfPartToRemove = find(inventory, partNum, isSorted);
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

// LIST ITEMS
/* Purpose    - List displays a heading for all the fields in inventoryType and
*              then displays in neat columns the values from the inventory
*              which is passed in.
* Parameters - inventory - vector containing the inventory
* Input      - None.
* Process    - Loops through the array of inventory items
* Output     - Displays each part number and number on hand
*              (in this version, number on hand is a constant)
* Return     - None.
*/

/* Sample output for version 3: (current version = 2)

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

	pressEnterToContinue();

	return;
}

// SHOW
/* Purpose    - Show an item in the inventory
* Parameters - inventory - vector containing the inventory
*            - isSorted - bool representing whether or not the data is sorted
* Input      - User inputs a part number to show, stored in partNum
* Process    - Calls showItem function to display the information for the
*              entered part number
* Output     - None.
* Return     - None.
*/
void show(vector<inventoryType> &inventory, bool &isSorted){

	int partNum;

	cout << "What part number would you like to display? ";
	cin >> partNum;

	showItem(inventory, partNum, isSorted);

	pressEnterToContinue();

	return;

}

// SHOW ITEM
/* Purpose    - Display the inventory information for the given part number
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to add
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Calls find function to see if partNum is already in the
*              inventory vector.
* Output     - Displays part number and quantity on hand (currently a constant:
*              1) or a message saying "Invalid Part Number", whichever is
*              appropriate.
* Return     - None.
*/
// Sample Output:
// Part Number      : #####
// Part Name        : ########               // Added in version 3
// Part Description : ###################    // Added in version 3
// Quantity On Hand : ###                    // Global constant until version3
//  O R
// Part Number ##### is  an Invalid Part Number. (Does not exist)
void showItem(const vector<inventoryType> &inventory, int partNum, bool isSorted) {

	int vectorLocation;

	vectorLocation = find(inventory, partNum, isSorted);

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

// SORT INVENTORY
/* Purpose    - Sort the inventory in ascending order by part number
* Parameters - inventory - vector containing the inventory
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Sorts the inventory using a selection sort. Changes isSorted
*              to true
* Output     - Displays a message explaining that inventory has been sorted,
*              waits for the user to press enter to continue.
* Return     - None.
*/
void sortInventory(vector<inventoryType> &inventory, bool &isSorted) {

	int index;
	int largestAt;
	int maxNeededIndex;
	inventoryType temp;

	maxNeededIndex = inventory.size() - 1;

	while (maxNeededIndex > 0) {
		largestAt = 0;
		for (index = 1; index <= maxNeededIndex; index++) {
			if (inventory[index] > inventory[largestAt]) {
				largestAt = index;
			}
		}

		// Swap the largest number with the number at the relative end of the list
		temp = inventory[maxNeededIndex];
		inventory[maxNeededIndex] = inventory[largestAt];
		inventory[largestAt] = temp;

		maxNeededIndex--;
	}

	cout << "Inventory successfully sorted.\n";

	pressEnterToContinue();

	isSorted = true;

	return;

}

/**** M A I N ****/
int main(){

	vector<inventoryType> inventory;   // Array of items (initially empty)
	int partNum;
	bool isSorted;
	int option;

	isSorted = false;

	option = 100;               // Set option to 100 (so switch will use default)

	do {
		Common::ClearScreen();

		cout << "ONE OF EACH, INC.\n";
		cout << "Inventory Control System v2.0\n";
		cout << "-----------------------------------------------------------------";
		cout << "--------------\n";

		switch (option) {
		case 0:
			// Load Inventory

			loadInventory(inventory, isSorted);

			option = 100;
			break;

		case 1:
			// Save Inventory

			saveInventory(inventory);

			option = 100;
			break;

		case 2:
			// List Inventory

			list(inventory);

			option = 100;
			break;

		case 3:
			// Show Inventory Item

			show(inventory, isSorted);

			option = 100;
			break;

		case 4:
			// Add Inventory Item

			add(inventory, isSorted);

			option = 100;
			break;

		case 5:
			// Remove Inventory Item

			remove(inventory, isSorted);

			option = 100;
			break;

		case 6:
			// Sort Inventory

			sortInventory(inventory, isSorted);

			option = 100;
			break;

		case 7:
			// Quit
			break;

		default:
			// Display menu with options

			option = displayMenu(4);

			break;
		}
	} while (option != 7);

	return 0;

}

/**** S A M P L E  O U T P U T ****/

/*
ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
-> Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to add? 6549
Part number 6549 added to the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
-> Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to add?
9876
Part number 9876 added to the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
-> Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to add? 9876
Part number 9876 already registered in the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
-> Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to add? 210
Part number 210 added to the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
-> Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Part number 15 added to the inventory list.
Part number 20 added to the inventory list.
Part number 25 added to the inventory list.
Part number 26 added to the inventory list.
Part number 2256 added to the inventory list.
Part number 2564 added to the inventory list.
Part number 35 added to the inventory list.
Part number 45 added to the inventory list.
Part number 55 added to the inventory list.
Part number 65 added to the inventory list.
Part number 75 added to the inventory list.
Part number 85 added to the inventory list.
Part number 95 added to the inventory list.
Part number 105 added to the inventory list.
Part number 110 added to the inventory list.
Part number 120 added to the inventory list.
Part number 130 added to the inventory list.
Part number 140 added to the inventory list.
Part number 150 added to the inventory list.
Part number 160 added to the inventory list.
Part number 170 added to the inventory list.
Part number 180 added to the inventory list.
Part number 190 added to the inventory list.
Part number 200 added to the inventory list.
Part number 210 already registered in the inventory list.
Part number 220 added to the inventory list.
Part number 230 added to the inventory list.
Inventory successfully loaded.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
-> List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Part Number  Quantity On Hand
===========  ================
6549                 1
9876                 1
210                 1
15                 1
20                 1
25                 1
26                 1
2256                 1
2564                 1
35                 1
45                 1
55                 1
65                 1
75                 1
85                 1
95                 1
105                 1
110                 1
120                 1
130                 1
140                 1
150                 1
160                 1
170                 1
180                 1
190                 1
200                 1
220                 1
230                 1

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
-> Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Inventory successfully sorted.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
-> List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Part Number  Quantity On Hand
===========  ================
15                 1
20                 1
25                 1
26                 1
35                 1
45                 1
55                 1
65                 1
75                 1
85                 1
95                 1
105                 1
110                 1
120                 1
130                 1
140                 1
150                 1
160                 1
170                 1
180                 1
190                 1
200                 1
210                 1
220                 1
230                 1
2256                 1
2564                 1
6549                 1
9876                 1

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
-> Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to display? 210
Part Number      : 210
Quantity On Hand : 1

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
-> Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to remove? 200
Part number 200 removed from the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
-> Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
What part number would you like to remove? 98765
Part number 98765 was not found in inventory.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
-> List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Part Number  Quantity On Hand
===========  ================
15                 1
20                 1
25                 1
26                 1
35                 1
45                 1
55                 1
65                 1
75                 1
85                 1
95                 1
105                 1
110                 1
120                 1
130                 1
140                 1
150                 1
160                 1
170                 1
180                 1
190                 1
210                 1
220                 1
230                 1
2256                 1
2564                 1
6549                 1
9876                 1

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
-> Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Inventory data saved to inventory.txt

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
-> Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
-> Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Part number 15 added to the inventory list.
Part number 20 added to the inventory list.
Part number 25 added to the inventory list.
Part number 26 added to the inventory list.
Part number 35 added to the inventory list.
Part number 45 added to the inventory list.
Part number 55 added to the inventory list.
Part number 65 added to the inventory list.
Part number 75 added to the inventory list.
Part number 85 added to the inventory list.
Part number 95 added to the inventory list.
Part number 105 added to the inventory list.
Part number 110 added to the inventory list.
Part number 120 added to the inventory list.
Part number 130 added to the inventory list.
Part number 140 added to the inventory list.
Part number 150 added to the inventory list.
Part number 160 added to the inventory list.
Part number 170 added to the inventory list.
Part number 180 added to the inventory list.
Part number 190 added to the inventory list.
Part number 210 added to the inventory list.
Part number 220 added to the inventory list.
Part number 230 added to the inventory list.
Part number 2256 added to the inventory list.
Part number 2564 added to the inventory list.
Part number 6549 added to the inventory list.
Part number 9876 added to the inventory list.
Inventory successfully loaded.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
-> List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
Part Number  Quantity On Hand
===========  ================
15                 1
20                 1
25                 1
26                 1
35                 1
45                 1
55                 1
65                 1
75                 1
85                 1
95                 1
105                 1
110                 1
120                 1
130                 1
140                 1
150                 1
160                 1
170                 1
180                 1
190                 1
210                 1
220                 1
230                 1
2256                 1
2564                 1
6549                 1
9876                 1

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v2.0
-------------------------------------------------------------------------------
OPTIONS:
Load Inventory from disk
Save Inventory to disk
List Inventory
Show Inventory Item
Add Inventory Item
Remove Inventory Item
Sort Inventory
-> Quit

Select option using the up, down, page up, page down keys.
Press ENTER to accept

*/