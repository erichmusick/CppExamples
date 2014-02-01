/**
 * This is a little program I put together when I was first learning C++ to experiment with the general structure
 * of Linked Lists and classes while in high school.
 */
#include <iostream>
#include <string>
#include "musickmenu.h"
#include "../Common/CommonFunctions.h"

using namespace std;

struct MEMBERDATA {
	int id;
	string username;
	string password;
	MEMBERDATA * next;
};

void displayProgramHeader() {

	string bar(78, char(196));

	cout << "Address Book 1.0\n";
	cout << "By Erich Musick\n";
	cout << bar;
	cout << endl;

	return;

}

int numberOfMembers(MEMBERDATA * members) {

	MEMBERDATA * member;
	int numMembers = 0;

	member = members;

	while (member != NULL) {
		numMembers++;
		member = member->next;
	}

	return numMembers;

}

MEMBERDATA *findMember(int id, MEMBERDATA * members) {

	MEMBERDATA * member;
	MEMBERDATA * foundAt;

	foundAt = NULL;
	member = members;

	while (member != NULL && foundAt == NULL) {
		if (member->id == id) {
			foundAt = member;
		}
		member = member->next;
	}

	return foundAt;

}

void addMember(string username, string password, MEMBERDATA * &members) {
	MEMBERDATA *newMember;
	MEMBERDATA *lastMember;

	newMember = new MEMBERDATA;

	if (!newMember) {
		cout << "ERROR: Not enough free memory to complete this operation. Member Not Added!\n";
	}
	else {

		newMember->next = NULL;
		newMember->id = 1;
		newMember->username = username;
		newMember->password = password;

		if (members != NULL) {
			lastMember = members;
			while (lastMember->next != NULL) {
				lastMember = lastMember->next;
			}
			newMember->id = lastMember->id + 1;
			lastMember->next = newMember;
		}
		else {
			members = newMember;
		}

		cout << "Member Added!\n";

	}

	return;
}

void removeMember(int id, MEMBERDATA * &members) {
	MEMBERDATA *member;
	MEMBERDATA *memberToDelete;
	int numMembers;
	
	memberToDelete = findMember(id, members);

	numMembers = numberOfMembers(members);

	if (numMembers > 1) {
		member = members;
		while (member != NULL) {
			if (member->next == memberToDelete) {
				member->next = memberToDelete->next;
				delete memberToDelete;

				cout << "Member Deleted!\n";
			}

			member = member->next;
		}
	}
	else {
		if (numMembers == 1 && memberToDelete != NULL) {
			delete members;
			members = NULL;

			cout << "Member Deleted!\n";
		}
		else {
			cout << "ERROR: Unable to delete member - id not found.\n";
		}
	}

	return;
}

void sortMembers(MEMBERDATA * &members) {

	MEMBERDATA * member;
	MEMBERDATA * smallestAt;
	MEMBERDATA * pointerToSmallest;
	MEMBERDATA * temp;
	MEMBERDATA * first;
	MEMBERDATA * previous;
	MusickMenu myMenu;
	vector<string> menuOptions(3);
	int sortBy;
	int i;

	// PROCESS: Get field to sort.

	i = 0;
	menuOptions[i++] = "ID";
	menuOptions[i++] = "Username";
	menuOptions[i++] = "Password";

	Common::GoToXY(1, 4);
	cout << "Select the field to use in sorting address book: ";

	myMenu.SetOptions(menuOptions);
	sortBy = myMenu.GetChoice(1, 5);

	Common::ClearScreen();

	displayProgramHeader();

	// PROCESS: Sort

	first = members;
	pointerToSmallest = NULL;

	while (first != NULL) {
		// Find largest value
		member = first;
		previous = NULL;
		smallestAt = first;
		while (member != NULL) {
			switch (sortBy) {
			case 0:
				if (member->id < smallestAt->id) {
					smallestAt = member;
					pointerToSmallest = previous;
				}
				break;
			case 1:
				if (member->username < smallestAt->username) {
					smallestAt = member;
					pointerToSmallest = previous;
				}
				break;
			case 2:
				if (member->password < smallestAt->password) {
					smallestAt = member;
					pointerToSmallest = previous;
				}
				break;
			default:
				break;
			}

			previous = member;
			member = member->next;
		}

		cout << "members: " << members << endl;
		cout << "smallestAt: " << smallestAt << endl;
		cout << "pointerToSmallest: " << pointerToSmallest << endl;
		cout << "first: " << first << endl;

		// smallestAt points to smallest
		// pointerToSmallest value whose next pointer points to largestAt

		if (first == members) {
			members = smallestAt;
		}
		else {

			//    if (first != pointerToSmallest) {
			if (pointerToSmallest != first) {
				pointerToSmallest->next = first;
			}
			else {
				pointerToSmallest->next = smallestAt->next;
			}
		}

		temp = first->next;
		first->next = smallestAt->next;
		smallestAt->next = temp;

		pointerToSmallest = smallestAt;
		first = smallestAt->next;
	}

	return;

}

void listMembers(MEMBERDATA *members) {
	MEMBERDATA *member;

	member = members;

	cout << " ID   Username   Password\n";
	cout << "==== ========== ==========\n";
	while (member != NULL) {
		dispSpaces(4 - intLength(member->id));
		cout << member->id;
		dispSpaces(11 - member->username.length());
		cout << member->username;
		dispSpaces(11 - member->password.length());
		cout << member->password;
		cout << endl;

		member = member->next;
	}
}

int main()
{
	MEMBERDATA *members = NULL;
	string idString;
	int id;
	string username;
	string password;
	int option;
	vector<string> options(7);
	MusickMenu myMenu;
	int i;

	i = 0;
	options[i++] = "Load Member List [Not Implemented]";
	options[i++] = "Save Member List [Not Implemented]";
	options[i++] = "Add Member";
	options[i++] = "Remove Member";
	options[i++] = "Sort Member List [Not Implemented Properly]";
	options[i++] = "List Members";
	options[i++] = "Quit";

	myMenu.SetOptions(options);

	do {

		Common::ClearScreen();

		displayProgramHeader();

		option = myMenu.GetChoice(1, 4);

		Common::ClearScreen();

		displayProgramHeader();

		switch (option) {
		case 2:
			do {
				cout << "Username (1-10 characters)? ";
				cin >> username;
				cin.ignore(80, '\n');
			} while (username.length() < 1 || username.length() > 10);

			do {
				cout << "Password (4-10 characters)? ";
				cin >> password;
				cin.ignore(80, '\n');
			} while (password.length() < 4 || password.length() > 10);
			cout << endl;

			addMember(username, password, members);
			PressEnterToContinue();
			break;
		case 3:
			do {
				cout << "Member ID to delete (-1 to cancel)? ";
				cin >> idString;
				cin.ignore(80, '\n');

				id = atoi(idString.c_str());
			} while (findMember(id, members) == NULL && id != -1);

			if (id != -1) {
				cout << endl;
				removeMember(id, members);
			}

			PressEnterToContinue();
			break;
		case 4:
			sortMembers(members);

			PressEnterToContinue();
			break;
		case 5:
			listMembers(members);

			PressEnterToContinue();
			break;
		default:
			break;
		}
	} while (option != (options.size() - 1));

	delete members;

	return 0;
}
