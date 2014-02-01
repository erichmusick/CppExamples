/* Title     - Multiplication
 * File name - Lab10
 * Programmer- 415 Erich Musick
 * IPO       - Input - User inputs the number of rows and columns he/she wants
 *               for the table.
 *             Processing - Table is resized to satisfy user's input, values of
 *               table are filled.
 *             Output - Table is displayed, with some formatting.
 */

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
void welcomeUser();
int getNumberOfRows();
int getNumberOfColumns();
void resizeMatrix(vector<vector<int>> &theTable, int numberOfRows, int numberOfColumns);
void fillTable(vector<vector<int>> &theTable);
void displayTableHeader(vector<vector<int>> theTable);
void displayTable(vector<vector<int>> theTable);

/****************************** F U N C T I O N S *****************************/
// Welcome User
/* purpose    - Let the user know about the program, warn about using large
*                values for number of columns.
* parameters - None.
* input      - None.
* process    - None.
* output     - Display welcome message.
* return     - None.
*/
void welcomeUser() {
	cout << "This program will calcluate and print the values of a multiplication";
	cout << " table when";
	cout << endl;
	cout << "given the number of rows and columns. When entering the number of ";
	cout << "columns, be";
	cout << endl;
	cout << "sure to enter no more than 18, or the table will wrap and will be ";
	cout << "difficult to";
	cout << endl;
	cout << "read.";
	cout << endl;
	cout << endl;

	return;
}

// Get Number of Rows
/* purpose    - Allow the user to enter the number of rows for the mult. table
* parameters - None.
* input      - Number of rows for the multiplication table
* process    - None.
* output     - None.
* return     - howManyRows, the value the user entered for the number of rows
*/
int getNumberOfRows() {
	int howManyRows;

	cout << "Enter number of rows   : ";
	cin >> howManyRows;

	return howManyRows;
}

// Get Number of Columns
/* purpose    - Allow the user to enter the number of columns for the
*                multiplication table
* parameters - None.
* input      - Number of columns for the multiplication table
* process    - None.
* output     - None.
* return     - howManyColumns, the value the user entered for the number of
*                columns
*/
int getNumberOfColumns() {
	int howManyColumns;

	cout << "Enter number of columns: ";
	cin >> howManyColumns;

	return howManyColumns;
}

// Fill Table
/* purpose    - To fill the table with the correct values
* parameters - theTable - apmatrix of integers
* input      - None.
* process    - theTable matrix is filled with the values of the
*                multiplication table specified by the user
* output     - None.
* return     - None.
*/
void fillTable(vector<vector<int>> &theTable, int numberOfRows, int numberOfColumns) {
	int row;
	int column;

	theTable = vector<vector<int>>(numberOfRows);

	row = 0;
	while (row < numberOfRows) {
		theTable[row] = vector<int>(numberOfColumns);
		column = 0;
		while (column < numberOfColumns) {
			theTable[row][column] = row * column;
			column = column + 1;
		}
		row = row + 1;
	}

	return;
}

// Display Table Header
/* purpose    - To display the table heading
* parameters - theTable - apmatrix of integers
* input      - None.
* process    - None
* output     - For each column, displays the column number and three dashes
*                below it (loops through a second time to display dashes).
* return     - None.
*/
void displayTableHeader(vector<vector<int>> theTable) {
	int howManyColumns;
	int column;

	if (theTable.size() == 0)
	{
		cout << "Table is empty";
		return;
	}

	// Assume all rows have same number of columns
	howManyColumns = theTable[0].size();

	cout << endl;

	// Display column numbers
	cout << " x |";
	column = 0;
	while (column < howManyColumns) {
		cout << setw(4);
		cout << column;

		column = column + 1;
	}
	cout << endl;

	// Display three dashes under each column number
	cout << "---+";
	column = 0;
	while (column < howManyColumns) {
		cout << "----";
		column = column + 1;
	}
	cout << endl;

	return;
}

// Display Table
/* purpose    - To display the values of the table
* parameters - theTable - apmatrix of integers
* input      - None.
* process    - Loops through the table. Displays all values of table with
*                formatting and in the correct column and correct row.
* output     - None.
* return     - None.
*/
void displayTable(vector<vector<int>> theTable) {
	int howManyRows;
	int howManyColumns;
	int row;
	int column;

	howManyRows = theTable.size();

	row = 0;
	while (row < howManyRows) {
		cout << setw(2);
		cout << row;
		cout << " |";

		howManyColumns = theTable[row].size();
		column = 0;
		while (column < howManyColumns) {
			cout << setw(4);
			cout << theTable[row][column];

			column = column + 1;
		}

		cout << endl;

		row = row + 1;
	}

	return;
}

// Main
int main() {
	/* Declare variables*/
	vector<vector<int>> theTable;           // Matrix to hold values of table
	int howManyRows;                  // Number of rows for table
	int howManyColumns;               // Number of columns for table

	/* Explain what program is about */
	welcomeUser();

	/* Get dimensions of table (user input) */
	howManyRows = getNumberOfRows();
	howManyColumns = getNumberOfColumns();

	/* Set the values for the multiplication table */
	fillTable(theTable, howManyRows, howManyColumns);

	/* Format table display, display the values */
	displayTableHeader(theTable);
	displayTable(theTable);

	return 0;
}

/**************************** E N D  P R O G R A M ****************************/

/*               LAB10 by 415 ERICH MUSICK   11:16 on Oct 11 2001

This program will calcluate and print the values of a multiplication table when
given the number of rows and columns. When entering the number of columns, be
sure to enter no more than 18, or the table will wrap and will be difficult to
read.

Enter number of rows   : 3
Enter number of columns: 6

x |   0   1   2   3   4   5
---+------------------------
0 |   0   0   0   0   0   0
1 |   0   1   2   3   4   5
2 |   0   2   4   6   8  10

'Esc' closes window.*/

/*               LAB10 by 415 ERICH MUSICK   11:16 on Oct 11 2001

This program will calcluate and print the values of a multiplication table when
given the number of rows and columns. When entering the number of columns, be
sure to enter no more than 18, or the table will wrap and will be difficult to
read.

Enter number of rows   : 35
Enter number of columns: 18

x |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17
---+------------------------------------------------------------------------
0 |   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
1 |   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17
2 |   0   2   4   6   8  10  12  14  16  18  20  22  24  26  28  30  32  34
3 |   0   3   6   9  12  15  18  21  24  27  30  33  36  39  42  45  48  51
4 |   0   4   8  12  16  20  24  28  32  36  40  44  48  52  56  60  64  68
5 |   0   5  10  15  20  25  30  35  40  45  50  55  60  65  70  75  80  85
6 |   0   6  12  18  24  30  36  42  48  54  60  66  72  78  84  90  96 102
7 |   0   7  14  21  28  35  42  49  56  63  70  77  84  91  98 105 112 119
8 |   0   8  16  24  32  40  48  56  64  72  80  88  96 104 112 120 128 136
9 |   0   9  18  27  36  45  54  63  72  81  90  99 108 117 126 135 144 153
10 |   0  10  20  30  40  50  60  70  80  90 100 110 120 130 140 150 160 170
11 |   0  11  22  33  44  55  66  77  88  99 110 121 132 143 154 165 176 187
12 |   0  12  24  36  48  60  72  84  96 108 120 132 144 156 168 180 192 204
13 |   0  13  26  39  52  65  78  91 104 117 130 143 156 169 182 195 208 221
14 |   0  14  28  42  56  70  84  98 112 126 140 154 168 182 196 210 224 238
15 |   0  15  30  45  60  75  90 105 120 135 150 165 180 195 210 225 240 255
16 |   0  16  32  48  64  80  96 112 128 144 160 176 192 208 224 240 256 272
17 |   0  17  34  51  68  85 102 119 136 153 170 187 204 221 238 255 272 289
18 |   0  18  36  54  72  90 108 126 144 162 180 198 216 234 252 270 288 306
19 |   0  19  38  57  76  95 114 133 152 171 190 209 228 247 266 285 304 323
20 |   0  20  40  60  80 100 120 140 160 180 200 220 240 260 280 300 320 340
21 |   0  21  42  63  84 105 126 147 168 189 210 231 252 273 294 315 336 357
22 |   0  22  44  66  88 110 132 154 176 198 220 242 264 286 308 330 352 374
23 |   0  23  46  69  92 115 138 161 184 207 230 253 276 299 322 345 368 391
24 |   0  24  48  72  96 120 144 168 192 216 240 264 288 312 336 360 384 408
25 |   0  25  50  75 100 125 150 175 200 225 250 275 300 325 350 375 400 425
26 |   0  26  52  78 104 130 156 182 208 234 260 286 312 338 364 390 416 442
27 |   0  27  54  81 108 135 162 189 216 243 270 297 324 351 378 405 432 459
28 |   0  28  56  84 112 140 168 196 224 252 280 308 336 364 392 420 448 476
29 |   0  29  58  87 116 145 174 203 232 261 290 319 348 377 406 435 464 493
30 |   0  30  60  90 120 150 180 210 240 270 300 330 360 390 420 450 480 510
31 |   0  31  62  93 124 155 186 217 248 279 310 341 372 403 434 465 496 527
32 |   0  32  64  96 128 160 192 224 256 288 320 352 384 416 448 480 512 544
33 |   0  33  66  99 132 165 198 231 264 297 330 363 396 429 462 495 528 561
34 |   0  34  68 102 136 170 204 238 272 306 340 374 408 442 476 510 544 578

'Esc' closes window.*/