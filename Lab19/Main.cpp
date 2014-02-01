/* Title      - Rock, Paper, Scissors
* File name  - Lab19
* Programmer - 415 Erich Musick
* IPO        - Input   - User selects their weapon - rock, paper, or scissors
*              Process - Computer selects random weapon, winner is determined
*              Output  - Selected weapons, winner, and win-loss-tie record are
*                displayed. User can continue to play for as long as he/she
*                would like.
*/

/*************************** H E A D E R  F I L E S ***************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include "../Common/CommonFunctions.h"
#include <Windows.h>

using namespace std;

/******************** F U N C T I O N  P R O T O T Y P E S ********************/
char getComputerChoice();
int determineWinner(char userChoice, char compChoice, int &scoreWins,
	int &scoreLosses, int &scoreTies);

/****************************** F U N C T I O N S *****************************/
// GET COMPUTER CHOICE
/* purpose    - Pick a random "weapon" for the computer
* parameters - None.
* input      - None.
* process    - A random "weapon" for the computer is selected.
* output     - None.
* return     - compChoice - char containing a letter representing computer's
*               choice
*               Possible values - r if computer's choice is a rock
*                               - p if computer's choice is paper
*                               - s if computer's choice is scissors
*/
char getComputerChoice() {
	int compChoiceInt;                  // Contains number representing weapon
	char compChoice;                    // Weapon with letter value
	vector<char> choiceTitle(3);      // Vector containing letters corresponding
	// to each possible random number

	choiceTitle[0] = 'r';
	choiceTitle[1] = 'p';
	choiceTitle[2] = 's';

	// Grab random between 0 and 2, inclusvie
	compChoiceInt = rand() % 3;
	compChoice = choiceTitle[compChoiceInt];

	return compChoice;
}

// DETERMINE WINNER
/* purpose    - Determine who won the current round.
* parameters - userChoice, variable of type char containing computer's weapon
*            - compChoice, variable of type char containing user's weapon
*            - scoreWins, reference variable of type int contaning the number
*                of times the user has won
*            - scoreLosses, reference variable of type int contaning the
*                number of times the user has lost
*            - scoreTies, reference variable of type int contaning the number
*                of times the user has tied
* input      - None.
* process    - Winner of current round is determined using switch statements
* output     - None.
* return     - thisRoundWin- int containing an integer representing the winner
*               Possible values - 0 if computer won
*                               - 1 if user won
*                               - 2 if user and computer tied
*/
int determineWinner(char userChoice, char compChoice, int &scoreWins,
	int &scoreLosses, int &scoreTies) {
	int thisRoundWin;

	switch (userChoice) {
	case 'r':
		switch (compChoice) {
		case 'r':
			thisRoundWin = 2;
			break;
		case 'p':
			thisRoundWin = 0;
			break;
		case 's':
			thisRoundWin = 1;
			break;
		}
		break;
	case 'p':
		switch (compChoice) {
		case 'r':
			thisRoundWin = 1;
			break;
		case 'p':
			thisRoundWin = 2;
			break;
		case 's':
			thisRoundWin = 0;
			break;
		}
		break;
	case 's':
		switch (compChoice) {
		case 'r':
			thisRoundWin = 0;
			break;
		case 'p':
			thisRoundWin = 1;
			break;
		case 's':
			thisRoundWin = 2;
			break;
		}
		break;
	}

	switch (thisRoundWin) {
	case 0:
		scoreLosses = scoreLosses + 1;
		break;
	case 1:
		scoreWins = scoreWins + 1;
		break;
	case 2:
		scoreTies = scoreTies + 1;
		break;
	}

	return thisRoundWin;
}

int main() {
	char playAgain;                     // Contains user input (play again)
	char userChoice;                    // User's selection ('r','p', or 's')
	char compChoice;                    // Computer's selection ('r','p', or 's')
	int thisRoundWin;                   // User wins = 1; Tie = 2; User Lose = 0;
	int scoreWins;                      // Number of wins (user)
	int scoreLosses;                    // Number of losses (user)
	int scoreTies;                      // Number of ties
	bool firstTime;                     // First time through the do-while?
	int dispLocationY;
	char password;
	int pauseLocation;

	// Seed the random generator
	srand(time(NULL));

	scoreWins = 0;
	scoreLosses = 0;
	scoreTies = 0;
	firstTime = true;
	dispLocationY = 9;
	do {
		// PROCESS: Get Random Computer choice
		compChoice = getComputerChoice();

		Common::GoToXY(2, 1);
		pauseLocation = rand() % 3;
		switch (pauseLocation) {
		case 0:
			cout << " * ";
			break;
		case 1:
			cout << "  *";
			break;
		case 2:
			cout << "*  ";
			break;
		}

		Common::GoToXY(77, 1);
		pauseLocation = rand() % 3;
		switch (pauseLocation) {
		case 0:
			cout << "*  ";
			break;
		case 1:
			cout << "***";
			break;
		case 2:
			cout << "* *";
			break;
		}

		Common::GoToXY(0, 1);
		pauseLocation = rand() % 3;
		switch (pauseLocation) {
		case 0:
			cout << "***";
			break;
		case 1:
			cout << "** ";
			break;
		case 2:
			cout << "* *";
			break;
		}

		Common::GoToXY(48, 1);
		switch (compChoice) {
		case 'r':
			cout << "01";
			break;
		case 'p':
			cout << "02";
			break;
		case 's':
			cout << "00";
			break;
		}

		Common::GoToXY(0, 3);
		cout << "ROCK, PAPER, SCISSORS";
		cout << endl;
		pauseLocation = rand() % 3;
		switch (pauseLocation) {
		case 0:
			cout << "---------------------";
			break;
		case 1:
			cout << "~--------------------";
			break;
		case 2:
			cout << "+--------------------";
			break;
		}
		cout << endl;
		cout << "The classic rock, paper, scissors game.";
		cout << endl;
		cout << endl;

		// USER INPUT: get choice
		pauseLocation = rand() % 3;
		do {
			Common::GoToXY(0, 7);
			Common::ClearToEndOfLine();

			switch (pauseLocation) {
			case 0:
				cout << "What is your choice (rock = 'r'";
				Sleep(100);
				cout << ", paper = 'p', scissors = 's')? ";
				break;
			case 1:
				cout << "What is your choice (rock = 'r', paper = 'p',";
				Sleep(200);
				cout << " scissors = 's')? ";
				break;
			case 2:
				cout << "What is your choice (rock = 'r', paper = 'p', scissors = 's'";
				Sleep(300);
				cout << ")? ";
				break;
			}
			cin >> userChoice;
			cin.ignore(80, '\n');
		} while (userChoice != 'r' && userChoice != 'p' && userChoice != 's');
		Common::GoToXY(0, 7);
		Common::ClearToEndOfLine();

		// PROCESS: get computer's random guess, determine winner, increment score
		thisRoundWin = determineWinner(userChoice, compChoice, scoreWins, scoreLosses, scoreTies);

		// DISPLAY: display choices, the winner, and the score
		if (firstTime) {
			Common::GoToXY(0, dispLocationY);
			cout << "Comp Choice  User Choice    Winner    Wins  Losses  Ties\n";
			cout << "===========  ===========  ==========  ====  ======  ====\n";

			dispLocationY = dispLocationY + 2;
			firstTime = false;
		}
		Common::GoToXY(0, dispLocationY + 1);
		Common::ClearToEndOfLine();
		Common::GoToXY(0, dispLocationY);
		switch (compChoice) {
		case 'r':
			cout << "   rock      ";
			break;
		case 'p':
			cout << "   paper     ";
			break;
		case 's':
			cout << " scissors    ";
			break;
		}
		switch (userChoice) {
		case 'r':
			cout << "   rock      ";
			break;
		case 'p':
			cout << "   paper     ";
			break;
		case 's':
			cout << " scissors    ";
			break;
		}
		switch (thisRoundWin) {
		case 0:
			cout << " computer   ";
			break;
		case 1:
			cout << "   user     ";
			break;
		case 2:
			cout << "   tie      ";
			break;
		}
		cout << setw(4);
		cout << scoreWins;
		cout << "  ";
		cout << setw(6);
		cout << scoreLosses;
		cout << "  ";
		cout << setw(4);
		cout << scoreTies;
		cout << endl;
		dispLocationY = dispLocationY + 1;

		if ((scoreWins + scoreLosses + scoreTies) % 34 == 0) {
			dispLocationY = 10;
		}

		// USER INPUT: Play again?
		do {
			playAgain = 'z';
			Common::GoToXY(0, 46);
			Common::ClearToEndOfLine();
			cout << "Play again ('y' or 'n')? ";
			cin >> playAgain;
			cin.ignore(80, '\n');
		} while (playAgain != 'y' && playAgain != 'n');

		// DISPLAY: Remove "go again" prompt if user is playing again
		Common::GoToXY(0, 46);
		Common::ClearToEndOfLine();

		// DISPLAY: If user is exiting, let them know if they won, lost, or tied
		if (playAgain == 'n') {
			if (scoreWins > scoreLosses) {
				cout << "Congratulations, you won the game!";
			}
			else {
				if (scoreWins < scoreLosses) {
					cout << "I'm sorry, but you lost the game!";
				}
				else {
					cout << "Not too bad, you tied with the computer.";
				}
			}
			cout << endl;
			cout << endl;
			cout << "Thank you for playing rock, paper, scissors!";
		}
	} while (playAgain == 'y');

	return 0;
}

/************************** S A M P L E  O U T P U T **************************/

/*               LAB19 by 415 ERICH MUSICK   11:28 on Dec 10 2001

ROCK, PAPER, SCISSORS
The classic rock, paper, scissors game.

What is your choice (rock = 'r', paper = 'p', scissors = 's')? s

Comp Choice  User Choice    Winner    Wins  Losses  Ties
===========  ===========  ==========  ====  ======  ====
scissors       rock         user        1       0     0
paper        paper        tie         1       0     1
paper      scissors       user        2       0     1
scissors     scissors       tie         2       0     2
scissors       rock         user        3       0     2
scissors       paper      computer      3       1     2
scissors       rock         user        4       1     2
scissors       paper      computer      4       2     2
rock         rock         tie         4       2     3
scissors       rock         user        5       2     3
paper        rock       computer      5       3     3
scissors     scissors       tie         5       3     4

Congratulations, you won the game!

Thank you for playing rock, paper, scissors!
'Esc' closes window.*/

/*               LAB19 by 415 ERICH MUSICK   11:28 on Dec 10 2001

ROCK, PAPER, SCISSORS
The classic rock, paper, scissors game.

What is your choice (rock = 'r', paper = 'p', scissors = 's')? r

Comp Choice  User Choice    Winner    Wins  Losses  Ties
===========  ===========  ==========  ====  ======  ====
paper        paper        tie         0       0     1
scissors       rock         user        1       0     1
scissors     scissors       tie         1       0     2
paper        paper        tie         1       0     3
rock         rock         tie         1       0     4
paper        rock       computer      1       1     4
scissors       rock         user        2       1     4
paper        rock       computer      2       2     4
rock         rock         tie         2       2     5
paper        rock       computer      2       3     5

I'm sorry, but you lost the game!

Thank you for playing rock, paper, scissors!
'Esc' closes window.*/

/*               LAB19 by 415 ERICH MUSICK   11:28 on Dec 10 2001

ROCK, PAPER, SCISSORS
The classic rock, paper, scissors game.

What is your choice (rock = 'r', paper = 'p', scissors = 's')? r

Comp Choice  User Choice    Winner    Wins  Losses  Ties
===========  ===========  ==========  ====  ======  ====
scissors       rock         user        1       0     0
scissors       rock         user        2       0     0
paper        paper        tie         2       0     1
scissors       rock         user        3       0     1
rock         paper        user        4       0     1
paper      scissors       user        5       0     1
scissors       paper      computer      5       1     1
scissors       paper      computer      5       2     1
rock         paper        user        6       2     1
rock       scissors     computer      6       3     1
paper      scissors       user        7       3     1
scissors       paper      computer      7       4     1
paper        paper        tie         7       4     2
rock         rock         tie         7       4     3
paper        rock       computer      7       5     3
paper        rock       computer      7       6     3
rock         rock         tie         7       6     4
paper        rock       computer      7       7     4

Not too bad, you tied with the computer.

Thank you for playing rock, paper, scissors!
'Esc' closes window.*/