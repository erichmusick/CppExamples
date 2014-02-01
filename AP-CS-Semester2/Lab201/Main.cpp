/* Lab name 	    - Graphing Calculator
 * Lab number	    - Lab201.cpp
 * Programmers	    - Erich Musick, Nick Chillemi, Chris Jakubik, CJ Wostratzky
 * Date Assigned    - January 22, 2002
 * Date Due 	    - January 25, 2002
 * Date Turned in   - January 28, 2002
 * Purpose		    - Emulate a minimal graphing calculator
 * Input		    - Graphing window and polynomial equation (up to 3rd degree)
 * Process		    - Charactors are entered into a matrix to represent the graph and window.
 * Output		    - The matrix is displayed.
*/

#include <iostream>
#include <vector>
#include "../../AP-CS-Misc/Common/CommonFunctions.h"

using namespace std;

typedef struct _GRAPH {
	double xMin;
	double xMax;
	double xScl;
	double yMin;
	double yMax;
	double yScl;
	int	 xRes;
	vector<double> coef;
	vector<vector<char>> disp;
} GRAPH;

/****** 		  F U N C T I O N  P R O T O T Y P E S 			******/
int xToColIndex(double x, const GRAPH &g);
int yToRowIndex(double y, const GRAPH &g);
void init(GRAPH &g);
bool goodX(double x, GRAPH &g);
bool goodY(double y, GRAPH &g);
void drawXaxis(GRAPH &g);
void drawYaxis(GRAPH &g);
void drawXticks(GRAPH &g);
void drawYticks(GRAPH &g);
void drawOrigin(GRAPH &g);
void clearMatrix(vector<vector<char>> &disp);
void clearDisplay(GRAPH &g);
double findY(vector<double> coef, double x);
void plotPoints(GRAPH &g);
void displayGraph(const vector<vector<char>> &d);
void setWindow(GRAPH &g);
void enterFunction(GRAPH &g);

/****** 		  F U N C T I O N S 			******/

// xToColIndex
/* purpose    - Determine matrix column for an x-value
* parameters - x - double holding x-value
*            - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - Determine matrix column for the specified x-value
* output     - None.
* return     - col, integer containg matrix column for specified x-value
*/
int xToColIndex(double x, const GRAPH &g){
	int col;

	int colCount = 0;
	if (g.disp.size() > 0)
	{
		colCount = g.disp[0].size();
	}

	col = int((x - g.xMin) / (g.xMax - g.xMin)*(colCount - 1));

	return col;
}

// yToRowIndex
/* purpose    - Determine matrix row for an y-value
* parameters - y - double holding y-value
*            - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - Determine matrix row for the specified y-value
* output     - None.
* return     - row, integer containg matrix row for specified y-value
*/
int yToRowIndex(double y, const GRAPH &g){
	int row;

	row = int((y - g.yMax) / (g.yMax - g.yMin)*(1. - g.disp.size()));

	return row;
}

// INITIALIZE
/* purpose    - Set default window and equation
* parameters - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - Fill g with the default window values, as well as the default
*              equation (1x+2)
* output     - None.
* return     - None.
*/
void init(GRAPH &g){
	int r;
	int c;

	g.xMin = -10;
	g.xMax = 10;
	g.xScl = 1;

	g.yMin = -10;
	g.yMax = 10;
	g.yScl = 1;

	g.xRes = 1;

	g.coef.resize(4);
	g.coef[0] = 0;
	g.coef[1] = 0;
	g.coef[2] = 1;
	g.coef[3] = 2;

	g.disp.resize(40);
	for (r = 0; r<40; r++){
		g.disp[r] = vector<char>(75);
		for (c = 0; c<75; c++){
			g.disp[r][c] = ' ';
		}
	}
	g.disp[yToRowIndex(10, g)][xToColIndex(-10, g)] = '+';

	return;
}

// GOOD X
/* purpose    - Determine whether an x-value is on the viewable portion of the
*              graph
* parameters - x - double holding x-value to check
*            - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - Determine whether the x-value is on the viewable portion of the
*              graph
* output     - None.
* return     - true or false, true if the x-value is on the viewable portion of
*              the graph, otherwise, false
*/
bool goodX(double x, GRAPH &g) {
	int col;
	bool returnValue = false;

	col = xToColIndex(x, g);
	if (col >= 0 && col < 75) {
		returnValue = true;
	}

	return returnValue;
}

// GOOD Y
/* purpose    - Determine whether an y-value is on the viewable portion of the
*              graph
* parameters - y - double holding y-value to check
*            - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - Determine whether the y-value is on the viewable portion of the
*              graph
* output     - None.
* return     - true or false, true if the y-value is on the viewable portion of
*              the graph, otherwise, false
*/
bool goodY(double y, GRAPH &g) {
	int row;
	bool returnValue = false;

	row = yToRowIndex(y, g);
	if (row >= 0 && row < 40) {
		returnValue = true;
	}

	return returnValue;
}

// DRAW X-AXIS
/* purpose    - "Draw" X-Axis if it lies on the viewable portion of the graph
* parameters - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - If the x-axis is on the viewable portion of the graph, fill the
*              appropriate position of the display matrix
* output     - None.
* return     - None.
*/
void drawXaxis(GRAPH &g) {
	int row;
	int column;

	row = yToRowIndex(0., g);
	if (goodY(0., g)) {
		for (column = 0; column < 75; column++) {
			g.disp[row][column] = 196;
		}
	}

	return;
}

// DRAW Y-AXIS
/* purpose    - "Draw" Y-Axis if it lies on the viewable portion of the graph
* parameters - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - If the y-axis is on the viewable portion of the graph, fill the
*              appropriate position of the display matrix
* output     - None.
* return     - None.
*/
void drawYaxis(GRAPH &g) {
	int row;
	int column;

	column = xToColIndex(0., g);
	if (goodX(0., g)) {
		for (row = 0; row < 40; row++) {
			g.disp[row][column] = 179;
		}
	}

	return;
}

// DRAW TICKS (X-AXIS)
/* purpose    - "Draw" ticks on X-Axis if it lies on the viewable portion of the
*              graph
* parameters - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - If the x-axis is on the viewable portion of the graph, fill the
*              appropriate positions of the display matrix with a +, to
*              indicate a tick mark. (Ticks are drawn as specified per the xScl
*              variable
* output     - None.
* return     - None.
*/
void drawXticks(GRAPH &g) {
	double index;
	int column;
	int row;

	row = yToRowIndex(0., g);
	if (goodY(0., g)) { // there is an x-axis, draw ticks
		for (index = 0; index >= g.xMin; index -= g.xScl) {
			if (goodX(index, g)) {
				column = xToColIndex(index, g);
				g.disp[row][column] = 193;
			}
		}
		for (index = 0; index <= g.xMax; index += g.xScl) {
			if (goodX(index, g)) {
				column = xToColIndex(index, g);
				g.disp[row][column] = 193;
			}
		}
		g.disp[row][0] = 17;
		g.disp[row][74] = 16;
	}

	return;
}

// DRAW TICKS (Y-AXIS)
/* purpose    - "Draw" ticks on Y-Axis if it lies on the viewable portion of the
*              graph
* parameters - g - GRAPH holding graph data (sent as reference parameter)
* input      - None.
* process    - If the y-axis is on the viewable portion of the graph, fill the
*              appropriate positions of the display matrix with a +, to
*              indicate a tick mark. (Ticks are drawn as specified per the yScl
*              variable
* output     - None.
* return     - None.
*/
void drawYticks(GRAPH &g) {
	double index;
	int column;
	int row;

	column = xToColIndex(0, g);
	if (goodX(0., g)) { // there is a y-axis, draw ticks
		for (index = 0; index >= g.yMin; index -= g.yScl) {
			if (goodY(index, g)) {
				row = yToRowIndex(index, g);
				g.disp[row][column] = 195;
			}
		}
		for (index = 0; index <= g.yMax; index += g.yScl) {
			if (goodY(index, g)) {
				row = yToRowIndex(index, g);
				g.disp[row][column] = 195;
			}
		}
		g.disp[0][column] = 30;
		g.disp[39][column] = 31;
	}

	return;
}

// DRAW ORIGIN
/*	Purpose		  - To place the origin on the x and y axes
*	Parameters	- g - GRAPH which holds the characters to show for the graph
*                itself
*	Process		  - As long as the x and y axis are in the viewing window, show
*                the origin on their intersection by storing a "+" in g
*	Input		    - None.
*	Output		  - None.
*	Return		  - None.
*/
void drawOrigin(GRAPH &g) {
	int row;
	int column;

	row = yToRowIndex(0., g);
	column = xToColIndex(0., g);

	if (goodX(0., g) && goodY(0., g)) {
		g.disp[row][column] = 197;
	}

	return;
}

// CLEAR MATRIX
/* purpose    - Set all the characters in the matrix to spaces, in order to
*              clear the graph
* parameters - disp - apmatrix holding each "cell" of the graph
* input      - None.
* process    - Set all the characters in the matrix to spaces
* output     - None.
* return     - None.
*/
void clearMatrix(vector<vector<char>> &disp) {
	int row;
	int column;
	int numberOfRows;
	int numberOfColumns;

	numberOfRows = disp.size();
	numberOfColumns = numberOfRows > 0 ? disp[0].size() : 0;

	for (row = 0; row < numberOfRows; row++) {
		for (column = 0; column < numberOfColumns; column++) {
			disp[row][column] = ' ';
		}
	}

	return;
}

// C L E A R  D I S P L A Y
/* Purpose    - Clear out the matrix, and redraw the axes, ticks, and origin
* Parameters - g - GRAPH holding the graph data (reference)
* Input      - none
* Process    - call previous functions
* Output     - none
* Return     - none
*/
void clearDisplay(GRAPH &g) {

	// Clear Matrix - set all values in the matrix to a blank space
	clearMatrix(g.disp);

	// "Draw" X-Axis
	drawXaxis(g);

	// "Draw" X-Ticks
	drawXticks(g);

	// "Draw" Y-Axis
	drawYaxis(g);

	// "Draw" Y-Ticks
	drawYticks(g);

	// "Draw" Origin
	drawOrigin(g);

	return;
}

// FIND Y
/* Purpose    - Find the y-value for an x value
* Parameters - coef - vector of doubles holding coefficients of polynomial
*              x - double holding x-value to use for finding y-value
* Input      - None.
* Process    - Calculate y-value for x-value
* Output     - None.
* Return     - None.
*/
double findY(vector<double> coef, double x) {
	double y;
	double addToY;
	int index;
	int index2;
	int largestExponent;
	int thisExponent;

	largestExponent = coef.size() - 1;

	for (index = 0, y = 0; index < coef.size(); index++) {
		thisExponent = largestExponent - index;
		for (index2 = 0, addToY = 1; index2 < thisExponent; index2++) {
			addToY *= x;
		}
		addToY *= coef[index];

		y += addToY;
	}

	return y;
}

// PLOT POINTS 
/* Purpose    - Plot the points of the graph
* Parameters - g - GRAPH holding values of graph
* Input      - None.
* Process    - Fill the matrix with a * for every point of the graph
* Output     - None.
* Return     - None.
*/
void plotPoints(GRAPH &g) {
	int row;
	int col;
	double x;
	double y;
	double increment;

	increment = (double(g.xMax - g.xMin) / 75.) / g.xRes;

	if (g.coef.size() >= 1) {
		for (x = g.xMin; x < g.xMax && x < g.disp[0].size(); x += increment) {
			y = findY(g.coef, x);
			col = xToColIndex(x, g);
			row = yToRowIndex(y, g);

			if (row < g.disp.size() && col < g.disp[0].size() && row >= 0 && col >= 0) {
				g.disp[row][col] = 249;
			}
		}
	}

	return;
}

// D I S P L A Y  G R A P H
/* Purpose    - Display the matrix, d, as the graph
* Parameters - The display matrix, d
* Input      - Char, ch, to loop to the top
* Process    - Find where the border of the graph is, and what is in the matrix
* Output     - Graph, and the border
* Return     - none
*/
void displayGraph(const vector<vector<char>> &d){
	int r;
	int c;
	char ch;

	for (c = 0; c<d[0].size() + 4; c++){
		cout << ':';
	}
	cout << endl;

	for (r = 0; r<d.size(); r++){
		cout << "::";
		for (c = 0; c< d[r].size(); c++){
			cout << d[r][c];
		}
		cout << "::\n";
	}

	for (c = 0; c<d[0].size() + 4; c++){
		cout << ':';
	}
	cout << endl;

	cout << "Press any key then rtn:	";
	cin >> ch;

	return;
}

// SET WINDOW
/* Purpose    - Get the window settings
* Parameters - g - GRAPH holding graph data
* Input      - xMin, xMax, xScl, yMin, yMax, yScl, xRes - values for window
*              settings of graph
* Process    - None.
* Output     - None.
* Return     - None.
*/
void setWindow(GRAPH &g) {
	do {
		cout << "xMin: ";
		cin >> g.xMin;
		cout << "xMax: ";
		cin >> g.xMax;
	} while (g.xMin >= g.xMax);
	do {
		cout << "xScl: ";
		cin >> g.xScl;
	} while (g.xScl <= 0);
	do {
		cout << "yMin: ";
		cin >> g.yMin;
		cout << "yMax: ";
		cin >> g.yMax;
	} while (g.yMin >= g.yMax);
	do {
		cout << "yScl: ";
		cin >> g.yScl;
	} while (g.yScl <= 0);
	do {
		cout << "xRes: ";
		cin >> g.xRes;
	} while (g.xRes <= 0);

	return;
}

// ENTER FUNCTION
/*	Purpose		  - To find and store the degree and coefficients of the
*                polynomial
*	Parameters	- g - GRAPH which holds the characters to show for the graph
*                itself
*	Input		    - The Degree of the polynomial and the Coefficients
*	Process		  - Stores the coefficients as long as there are coefficients to
*                store
*	Output		  - None.
*	Return		  - None.
*/
void enterFunction(GRAPH &g) {
	int polyDegree;
	int index;
	int exponent;

	do {
		cout << "What degree polynomial would you like to enter? ";
		cin >> polyDegree;
	} while (polyDegree <= 0);

	polyDegree++; // increment because we need degree + 1 elements in the array

	g.coef.resize(polyDegree);

	for (index = 0; index < polyDegree; index++) {
		exponent = polyDegree - index - 1;

		if (index > 0) {
			cout << " + ";
		}
		cout << "(C";
		cout << index;
		if (exponent > 1) {
			cout << " * x ^ ";
			cout << exponent;
		}
		else {
			if (exponent == 1) {
				cout << " * x";
			}
		}

		cout << ")";
	}
	cout << endl;

	index = 0;
	while (index < polyDegree) {
		cout << "Enter C";
		cout << index;
		cout << ": ";
		cin >> g.coef[index];

		index++;
	}

	return;
}

/****** 			   M A I N					******/

int main(){

	GRAPH g;
	char choice;

	init(g);
	clearDisplay(g);									// Display axes and origin in case user displays graph before performing another action
	do{
		Common::ClearScreen(); // comment this out in linux
		cout << "0 - Clear Display\n"; //Set disp to spaces, insert x and y axes
		cout << "1 - Set Window\n";    //Enter new window dimensions then Clear Disp
		cout << "2 - Enter Function\n";//chg coef[0]x^3+coef[1]x^2+coef[2]x+coef[3]
		cout << "3 - Display Graph\n";
		cout << "4 - Quit\n\n";
		cout << "Enter choice (0-4):  ";
		cin >> choice;
		switch (choice){
		case '0':										// Clear Display
			clearDisplay(g);
			break;
		case '1':										// Set Window
			setWindow(g);
			clearDisplay(g);					// Clear display because Window has changed
			break;
		case '2':										// Get user's input - enter the function
			enterFunction(g);
			break;
		case '3':										// Plot the points, display graph
			plotPoints(g);
			displayGraph(g.disp);
			break;
		case '4':										// User wants to quit, nothing special needs to be done
			break;
		default:                    // If user enters something else, don't do anything, prompt shows up again
			break;
		}

	} while (choice != '4');

	return 0;
}


/****** 			   S A M P L E  O U T P U T					******/

/*


Enter choice (0-4):  1
xMin: -10
xMax: 10
xScl: 1
yMin: -10
yMax: 10
yScl: 1
xRes: 1

Enter choice (0-4):  2
What degree polynomial would you like to enter? 3
(C0 * x ^ 3) + (C1 * x ^ 2) + (C2 * x) + (C3)
Enter C0: 1
Enter C1: 0
Enter C2: -4
Enter C3: 0

Enter choice (0-4):  3

*** Note: Some characters below didn't transfer properly when we copied and
pasted the output

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                                                          ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +        •                            ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                ••   +                                     ::
::                               •  •  ¦       •                             ::
::                                     +                                     ::
::                              •    • ¦                                     ::
::                                     +                                     ::
::                                    •¦                                     ::
::----------------------------•-------+------•-----------------------------::
::                                     •                                     ::
::                                     +                                     ::
::                                     ¦•    •                               ::
::                                     +                                     ::
::                            •        ¦ •  •                                ::
::                                     +  ••                                 ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                           •         +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                     +                                     ::
::                                     ¦                                     ::
::                                                                          ::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

Enter choice (0-4):  1
xMin: -10
xMax: 10
xScl: 1
yMin: -10
yMax: 10
yScl: 1
xRes: 10

*** Note: Some characters below didn't transfer properly when we copied and
pasted the output

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::                                              •                           ::
::                                     +         •                           ::
::                                     ¦        •                            ::
::                                     +        •                            ::
::                                     ¦        •                            ::
::                                     +        •                            ::
::                                     ¦        •                            ::
::                                     +        •                            ::
::                                     ¦        •                            ::
::                                     +        •                            ::
::                                     ¦       •                             ::
::                                     +       •                             ::
::                                     ¦       •                             ::
::                               •••   +       •                             ::
::                               • ••  ¦       •                             ::
::                              ••  •• +       •                             ::
::                              •    • ¦      ••                             ::
::                             ••    ••+      •                              ::
::                             •      •¦      •                              ::
::----------------------------•------••------•-----------------------------::
::                             •       •      •                              ::
::                             •       ••    ••                              ::
::                            ••       ¦•    •                               ::
::                            •        +••  ••                               ::
::                            •        ¦ •• •                                ::
::                            •        +  •••                                ::
::                            •        ¦                                     ::
::                            •        +                                     ::
::                            •        ¦                                     ::
::                           •         +                                     ::
::                           •         ¦                                     ::
::                           •         +                                     ::
::                           •         ¦                                     ::
::                           •         +                                     ::
::                           •         ¦                                     ::
::                           •         +                                     ::
::                           •         ¦                                     ::
::                          •          +                                     ::
::                          •          ¦                                     ::
::                          •                                               ::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

*/