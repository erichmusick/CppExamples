/* Title     - Time Clock
 * File name - Lab07
 * Programmer- 415 Erich Musick
 * IPO       - Input - The user inputs the time he/she began and finished work
               Processing - The program calculates the amount of time the user
			   worked
			   Output - The program displays the amout of time the user worked
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int startHour;                  // Hour user started work
	int startMinute;                // Minute user started work
	int startAllMinutes;            // Time user started work, in minutes
	char colon;                     // Colon separating time user enters
	int endHour;                    // Hour user finished work
	int endMinute;                  // Minute user finished work
	int endAllMinutes;              // Time user finished work, in minutes
	const int minutesInAnHour = 60; // Number of minutes in an hour
	const int minutesInAday = 1440; // Number of minutes in a day
	int minDiffPlusMinInADay;       /* The difference of endAllMinutes and
									startAllMinutes, plus minutesInAday */
	int totalMinutesWorked;         // Time worked, in minutes
	int minutesWorked;              // Time worked, minutes part
	int hoursWorked;                // Time worked, hours part

	/* Let the user know what the program is about */
	cout << "This program, given the time a person starts and ends work in "
		<< "military time,"
		<< endl
		<< "will calculate the time worked."
		<< endl
		<< endl;

	/* Prompt the user for the time he/she began working */
	cout << "Start  : ";
	cin >> startHour;
	cin >> colon;
	cin >> startMinute;

	/* Prompt the user for the time he/she finished working */
	cout << "End    : ";
	cin >> endHour;
	cin >> colon;
	cin >> endMinute;

	/* Convert the start hours to minutes and add them to startAllMinutes */
	startAllMinutes = startHour * minutesInAnHour;
	startAllMinutes = startAllMinutes + startMinute;

	/* Convert the end hours to minutes and add them to endAllMinutes */
	endAllMinutes = endHour * minutesInAnHour;
	endAllMinutes = endAllMinutes + endMinute;

	/* Find the total number of minutes worked, even the time passes midnight*/
	minDiffPlusMinInADay = minutesInAday + endAllMinutes - startAllMinutes;
	totalMinutesWorked = minDiffPlusMinInADay % minutesInAday;

	/* Convert the total number of minutes worked to hours and minutes */
	hoursWorked = totalMinutesWorked / minutesInAnHour;
	minutesWorked = totalMinutesWorked % minutesInAnHour;

	/* Output total time worked */
	cout << "Worked : "
		<< setfill('0')
		<< setw(2)
		<< hoursWorked
		<< ":"
		<< setfill('0')
		<< setw(2)
		<< minutesWorked
		<< endl;
	return 0;
}

/*               LAB07 by 415 ERICH MUSICK   11:25 on Sep 18 2001

This program, given the time a person starts and ends work in military time,
will calculate the time worked.

Start  : 23:15
End    : 07:20
Worked : 08:05

'Esc' closes window.*/

/*               LAB07 by 415 ERICH MUSICK   11:25 on Sep 18 2001

This program, given the time a person starts and ends work in military time,
will calculate the time worked.

Start  : 7:45
End    : 15:15
Worked : 07:30

'Esc' closes window.*/