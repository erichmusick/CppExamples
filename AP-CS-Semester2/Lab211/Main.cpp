/* Course     - A P   C o m p u t e r   S c i e n c e ( C + + )
* Instructor - M r .  B u r z y n s k i
* Lab        - Lab206.cpp
* Programmer - 413 Erich Musick
* Assigned   - N/A
* Due        - N/A
* Turned in  -
* Purpose    - The program displays a menu, accepts a command and executes it.
*              The application is an "Inventory Control System" which maintains
*              a list of "inventory items," each of which has its own number,
*              name, description, and quantity. Items are stored in an array of
*              structures.
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

struct inventoryType {
	int number;
	int quantity;
	string name;
	string description;
};

/****  F U N C T I O N   P R O T O T Y P E S  ****/

void displayProgramHeader(string currentAction);
void pressEnterToContinue();
int displayMenu();
void loadInventory(vector<inventoryType> &inventory, bool &isSorted);
void saveInventory(vector<inventoryType> &inventory);
void sortInventory(vector<inventoryType> &inventory, bool &isSorted);
void add(vector<inventoryType> &inventory, bool &isSorted);
void addItem(vector<inventoryType> &inventory, inventoryType part, bool &isSorted);
int find(const vector<inventoryType> &inventory, int partNum, bool isSorted);
int findFromSorted(const vector<inventoryType> &inventory, int partNum);
int findFromUnsorted(const vector<inventoryType> &inventory, int partNum);
void listTableHeader();
void list(const vector<inventoryType> &inventory);
void show(vector<inventoryType> &inventory, bool &isSorted);
void showItem(const vector<inventoryType> &inventory, int partNum, bool isSorted);
void remove(vector<inventoryType> &inventory, bool &isSorted);
void removeItem(vector<inventoryType> &inventory, inventoryType part, bool isSorted);

/**** F U N C T I O N S ****/

// DISPLAY PROGRAM HEADER
/* Purpose    - Introduce the program to the user
* Parameters - currentAction - stringcontaining description of current
*                screen - what is going on?
* Input      - None.
* Process    - None.
* Output     - Display program title, company name, and current action.
* Return     - None.
*/
void displayProgramHeader(string currentAction) {

	cout << "ONE OF EACH, INC.\n";
	cout << "Inventory Control System v3.0\n";
	cout << "-----------------------------------------------------------------";
	cout << "--------------\n";

	if (currentAction != "") {
		cout << "YOU ARE AT: ";
		cout << currentAction;
		cout << endl;
		cout << "-----------------------------------------------------------------";
		cout << "--------------\n";
	}

	return;

}

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
* Process    - File is opened, data is read into a temporary variable of type
*                inventoryType and sent to the addItem function to be added to
*                the inventory list
* Output     - If file cannot be opened, displays an error. Otherwise, displays
*              a success message and waits for the user to press enter to
*              continue
* Return     - None.
*/
void loadInventory(vector<inventoryType> &inventory, bool &isSorted) {

	const string fileName = "inventory.txt";
	ifstream diskIn;
	int numberOfItems;          // Number of items in inventory.txt
	inventoryType part;
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
			diskIn >> part.number;
			diskIn.ignore(80, '\n');
			getline(diskIn, part.name);
			getline(diskIn, part.description);
			diskIn >> part.quantity;
			diskIn.ignore(80, '\n');

			// Add part number to inventory list. Program doesn't check to see whether
			// or not the number is already in the list because the add function
			// checks new numbers
			addItem(inventory, part, isSorted);
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
			diskOut << inventory[index].number;
			diskOut << endl;
			diskOut << inventory[index].name;
			diskOut << endl;
			diskOut << inventory[index].description;
			diskOut << endl;
			diskOut << inventory[index].quantity;
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
* Parameters - inventory - vector containing the inventory items
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
* Parameters - inventory - vector containing the inventory items
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

		if (inventory[location].number < partNum) {
			left = location + 1;
		}
		else if (inventory[location].number > partNum) {
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
* Parameters - inventory - vector containing the inventory items
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
		if (inventory[i].number == partNum){  // Found match so save index
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
* Input      - User inputs a part number to add. If the part number exists,
*                prompts for a quanity to add to the current. If part number
*                doesn't exist, asks if user would like to add it. If they
*                want to add it, prompt for a quanity, name, and description.
* Process    - Calls addItem function to add part information to inventory
* Output     - Waits for user to press enter to continue.
* Return     - None.
*/
void add(vector<inventoryType> &inventory, bool &isSorted){

	inventoryType part;
	char newItem;
	char updateQuantity;
	bool firstTime;

	cout << "What part number would you like to add or update? ";
	cin >> part.number;
	cin.ignore(80, '\n');
	cout << endl;

	if (find(inventory, part.number, isSorted) == -1) {
		cout << "Item currently not in inventory. Add it (y/n)? ";
		cin >> newItem;
		cout << endl;

		newItem = char(toupper(newItem));
		if (newItem == 'Y') {
			firstTime = true;
			do {
				if (!firstTime) {
					cout << "Too long. Must be no longer than 16 charaacters.\n";
				}

				cout << "Quantity on hand ? ";
				cin >> part.quantity;
				cin.ignore(80, '\n');

				firstTime = false;
			} while (Common::intLength(part.quantity) > 16);

			firstTime = true;
			do {
				if (!firstTime) {
					cout << "Too long. Must be no longer than 13 charaacters.\n";
				}

				cout << "Part Name        ? ";
				getline(cin, part.name);

				firstTime = false;
			} while (part.name.length() > 13);

			firstTime = true;
			do {
				if (!firstTime) {
					cout << "Too long. Must be no longer than 33 charaacters.\n";
				}

				cout << "Part Description ? ";
				getline(cin, part.description);

				firstTime = false;
			} while (part.description.length() > 33);

			cout << endl;

			addItem(inventory, part, isSorted);
		}
	}
	else {
		cout << "Item already in inventory. Update quantity (y/n)? ";
		cin >> updateQuantity;
		cin.ignore(80, '\n');
		cout << endl;

		updateQuantity = char(toupper(updateQuantity));
		if (updateQuantity == 'Y') {
			cout << "Quantity to add    ? ";
			cin >> part.quantity;
			cin.ignore(80, '\n');

			cout << endl;

			addItem(inventory, part, isSorted);
		}
	}

	pressEnterToContinue();

	return;

}

// ADD ITEM
/* Purpose    - Add part number to the inventory if it isn't already in it
* Parameters - inventory - vector containing the inventory items
*            - part - part information to add (inventoryType)
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Calls find function to see if part number is already in the
*              inventory vector. If it isn't, resizes list and adds the part
*              information to the end of the list. If part exists, updates
*              the quantity (adds part.quantity to current quantity). If the
*              new part number is smaller than the last number in the inventory
*              list, sets isSorted to false because list is no longer sorted.
* Output     - Displays a message saying that the number has been added or
*              that is already exists, whichever is appropriate.
* Return     - None.
*/
void addItem(vector<inventoryType> &inventory, inventoryType part,
	bool &isSorted){

	int nItems;
	int vectorLocation;

	vectorLocation = find(inventory, part.number, isSorted);

	if (vectorLocation != -1){
		// Part number is already in the list, update quantity.
		inventory[vectorLocation].quantity += part.quantity;

		// Display a success message.
		cout << "Quantity for part number ";
		cout << part.number;
		cout << " successfully updated.\n";
	}
	else{
		// Part number isn't already in the list, add part.

		nItems = inventory.size();
		inventory.resize(nItems + 1);
		inventory[nItems] = part;

		// Display a success message.
		cout << "Part number ";
		cout << part.number;
		cout << " added to the inventory list.\n";

		if (nItems > 0 && part.number < inventory[nItems - 1].number) {
			isSorted = false;
		}
	}

	return;
}

// REMOVE
/* Purpose    - Remove an item from the inventory
* Parameters - inventory - vector containing the inventory items
*            - isSorted - bool representing whether or not the data is sorted
* Input      - User inputs a part number and quantity to remove, stored in part
* Process    - Calls removeItem function to update part information in
*                inventory vector.
* Output     - None.
* Return     - None.
*/
void remove(vector<inventoryType> &inventory, bool &isSorted){

	inventoryType part;

	cout << "What part number would you like to remove? ";
	cin >> part.number;
	cin.ignore(80, '\n');
	cout << endl;

	if (find(inventory, part.number, isSorted) != -1) {
		cout << "Quantity to remove? ";
		cin >> part.quantity;
		cin.ignore(80, '\n');
		cout << endl;
	}

	removeItem(inventory, part, isSorted);

	pressEnterToContinue();

	return;
}

// REMOVE ITEM
/* Purpose    - Removed part number from the inventory if it is in it
* Parameters - inventory - vector containing the inventory
*            - part - part information for part to remove
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Calls find function to see if part is already in the
*              inventory vector. If part is in list, updates quanity. If new
*                quantity is 0, asks user if he/she would like to delete
*                the item alltogether. If the part isn't in the list, give an
*                error message.
* Output     - Displays a message saying that the number has been removed,
*              updated, or that it doesn't exist, whichever is appropriate.
* Return     - None.
*/
void removeItem(vector<inventoryType> &inventory, inventoryType part, bool isSorted) {

	int indexOfPartToRemove;
	int j;
	int nItems;
	char removeCompletely;

	indexOfPartToRemove = find(inventory, part.number, isSorted);
	if (indexOfPartToRemove < 0) {
		cout << "Part number " << part.number << " was not found in inventory.\n";
	}
	else {
		// Part number is in inventory, update quantity
		inventory[indexOfPartToRemove].quantity -= part.quantity;

		if (inventory[indexOfPartToRemove].quantity == 0) {
			// Quantity is now 0. Ask user whether or not he/she would like to
			// completely remove the item from the inventory
			cout << "Remove part completely from inventory (y/n)? ";
			cin >> removeCompletely;
			cin.ignore(80, '\n');
			cout << endl;

			removeCompletely = char(toupper(removeCompletely));

			if (removeCompletely == 'Y') {
				// User would like to completely remove the item from the inventory      
				nItems = inventory.size();
				for (j = indexOfPartToRemove + 1; j < nItems; j++){// Shift items back one
					inventory[j - 1] = inventory[j];                 // to fill the gap.
				}

				inventory.resize(nItems - 1);                    // Reduce vector length

				// Display a success message
				cout << "Part number ";
				cout << part.number;
				cout << " removed from the inventory list.\n";
			}
			else {
				// Display a success message
				cout << "Quantity for part number ";
				cout << part.number;
				cout << " successfully updated.\n";
			}
		}
		else {
			// Display a success message
			cout << "Quantity for part number ";
			cout << part.number;
			cout << " successfully updated.\n";
		}
	}

	return;

}

// LIST TABLE HEADER
/* Purpose    - Display the table header for the list items table.
* Parameters - None.
* Input      - None.
* Process    - None.
* Output     - Displays the table header for the list items table.
* Return     - None.
*/
void listTableHeader() {

	cout << "Part Number    Part Name             Part Description          ";
	cout << "Quantity On Hand\n";
	cout << "===========  =============  =================================  ";
	cout << "================\n";

	return;

}

// LIST ITEMS
/* Purpose    - List displays a heading for all the fields in inventoryType and
*                then displays in neat columns the values from the inventory
*                which is passed in.
* Parameters - inventory - vector containing the inventory
* Input      - None.
* Process    - Loops through the array of inventory items
* Output     - Displays the number, name, description and quantity of each
*                item in the inventory
* Return     - None.
*/
void list(const vector<inventoryType> &inventory) {

	int index;
	int inventoryLength;

	inventoryLength = inventory.size();

	// OUTPUT: Display the header for the table.
	listTableHeader();

	for (index = 0; index < inventoryLength; index++) {
		cout.setf(ios_base::left, ios_base::adjustfield);
		cout << setw(11);
		cout << inventory[index].number;
		cout << "  ";
		cout << setw(13);
		cout << inventory[index].name;
		cout << "  ";
		cout << setw(33);
		cout << inventory[index].description;
		cout << "  ";
		cout << setw(16);
		cout << inventory[index].quantity;
		cout << endl;

		if ((index % 40) == 0 && index != 0) {
			// OUTPUT: Wait for the user to press enter before continuing
			pressEnterToContinue();

			// OUTPUT: Clear the screen
			Common::ClearScreen();

			// OUTPUT: Display program header
			displayProgramHeader("List Inventory");

			// OUTPUT: Display the header for the table.
			listTableHeader();
		}
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
	cout << endl;

	showItem(inventory, partNum, isSorted);

	pressEnterToContinue();

	return;

}

// SHOW ITEM
/* Purpose    - Display the inventory information for the given part number
* Parameters - inventory - vector containing the inventory
*            - partNum - part number to show
*            - isSorted - bool representing whether or not the data is sorted
* Input      - None.
* Process    - Calls find function to see if part is in the inventory vector.
* Output     - Displays the number, name, description and quantity of item
*                or a message saying "Invalid Part Number", whichever is
*                appropriate.
* Return     - None.
*/
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
		cout << inventory[vectorLocation].number;
		cout << endl;
		cout << "Part Name        : ";
		cout << inventory[vectorLocation].name;
		cout << endl;
		cout << "Description      : ";
		cout << inventory[vectorLocation].description;
		cout << endl;
		cout << "Quantity On Hand : ";
		cout << inventory[vectorLocation].quantity;
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
			if (inventory[index].number > inventory[largestAt].number) {
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
	bool isSorted;
	int option;

	isSorted = false;

	option = 100;               // Set option to 100 (so switch will use default)

	do {
		Common::ClearScreen();

		switch (option) {
		case 0:
			// Load Inventory

			displayProgramHeader("Load Inventory");
			loadInventory(inventory, isSorted);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 1:
			// Save Inventory

			displayProgramHeader("Save Inventory");
			saveInventory(inventory);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 2:
			// List Inventory

			displayProgramHeader("List Inventory");
			list(inventory);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 3:
			// Show Inventory Item

			displayProgramHeader("Show Inventory Item");
			show(inventory, isSorted);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 4:
			// Add Inventory Item

			displayProgramHeader("Add/Update Inventory Item");
			add(inventory, isSorted);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 5:
			// Remove Inventory Item

			displayProgramHeader("Remove/Update Inventory Item");
			remove(inventory, isSorted);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 6:
			// Sort Inventory

			displayProgramHeader("Sort Inventory");
			sortInventory(inventory, isSorted);

			option = 100;         // Set option to 100 (so switch will use default)
			break;

		case 7:
			// Quit
			break;

		default:
			// Display menu with options

			displayProgramHeader("");
			option = displayMenu(4);

			break;
		}
	} while (option != 7);

	return 0;

}

/**** S A M P L E  O U T P U T ****/

/*

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Add/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to add or update? 25271

Item currently not in inventory. Add it (y/n)? y

Quantity on hand ? 10
Part Name        ? Sweatshirt
Part Description ? XL Green Tiger Woods Golfing logo

Part number 25271 added to the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Add/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to add or update? 25407

Item currently not in inventory. Add it (y/n)? n

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Add/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to add or update? 25271

Item already in inventory. Update quantity (y/n)? n

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Add/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to add or update? 25271

Item already in inventory. Update quantity (y/n)? y

Quantity to add    ? 5

Quantity for part number 25271 successfully updated.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Add/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to add or update? 25268

Item currently not in inventory. Add it (y/n)? y

Quantity on hand ? 20
Part Name        ? Jacket
Part Description ? Blue letterman's jacket WEGO logo

Part number 25268 added to the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: List Inventory
-------------------------------------------------------------------------------
Part Number    Part Name             Part Description          Quantity On Hand
===========  =============  =================================  ================
25271        Sweatshirt     XL Green Tiger Woods Golfing logo  10
25268        Jacket         Blue letterman's jacket WEGO logo  20

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Sort Inventory
-------------------------------------------------------------------------------
Inventory successfully sorted.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: List Inventory
-------------------------------------------------------------------------------
Part Number    Part Name             Part Description          Quantity On Hand
===========  =============  =================================  ================
25268        Jacket         Blue letterman's jacket WEGO logo  20
25271        Sweatshirt     XL Green Tiger Woods Golfing logo  10

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Show Inventory Item
-------------------------------------------------------------------------------
What part number would you like to display? 25271

Part Number      : 25271
Part Name        : Sweatshirt
Description      : XL Green Tiger Woods Golfing logo
Quantity On Hand : 10

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Show Inventory Item
-------------------------------------------------------------------------------
What part number would you like to display? 25666

Part Number 25666 is an Invalid Part Number. (Does not exist)

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Remove/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to remove? 25268

Quantity to remove? 5

Quantity for part number 25268 successfully updated.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Show Inventory Item
-------------------------------------------------------------------------------
What part number would you like to display? 25268

Part Number      : 25268
Part Name        : Jacket
Description      : Blue letterman's jacket WEGO logo
Quantity On Hand : 15

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Remove/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to remove? 25271

Quantity to remove? 10

Remove part completely from inventory (y/n)? y

Part number 25271 removed from the inventory list.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Remove/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to remove? 25268

Quantity to remove? 15

Remove part completely from inventory (y/n)? n

Quantity for part number 25268 successfully updated.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Save Inventory
-------------------------------------------------------------------------------
Inventory data saved to inventory.txt

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Load Inventory
-------------------------------------------------------------------------------
Part number 25268 added to the inventory list.
Inventory successfully loaded.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: List Inventory
-------------------------------------------------------------------------------
Part Number    Part Name             Part Description          Quantity On Hand
===========  =============  =================================  ================
25268        Jacket         Blue letterman's jacket WEGO logo  0

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Remove/Update Inventory Item
-------------------------------------------------------------------------------
What part number would you like to remove? 25260

Part number 25260 was not found in inventory.

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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
Inventory Control System v3.0
-------------------------------------------------------------------------------
YOU ARE AT: Show Inventory Item
-------------------------------------------------------------------------------
What part number would you like to display? 25260

Part Number 25260 is an Invalid Part Number. (Does not exist)

Press ENTER to continue...

ONE OF EACH, INC.
Inventory Control System v3.0
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