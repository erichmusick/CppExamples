#include "musickmenu.h"
#include "../Common/CommonFunctions.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void PressEnterToContinue() {
  cout << endl;
  cout << "Press [ENTER] to continue...\n";
  while (_getch() != 13);
}

int intLength(int value) {

  int length = 0;
  
  if (value < 0) {
    value *= -1;
    length++;
  }
  
  while(value > 0) {
    value /= 10;
    length++;
  }
  
  return length;
  
}

void dispSpaces(int numSpaces) {
  
  int i;
  
  if (numSpaces > 0) {
    for (i = 0; i < numSpaces; i++) {
      cout << " ";
    }
  }
  
  return;
  
}

MusickMenu::MusickMenu()
{
}

MusickMenu::MusickMenu(vector<string> options)
{
  myOptions = options;
}

void MusickMenu::SetOptions(vector<string> options)
{

  myOptions = options;
  
  return;
}

int MusickMenu::GetChoice(const int startXlocation, const int startYlocation) {

  const int numOptions = myOptions.size();
  int option;
  int key = 0;
  int i;
  int cursorY;

  for (i = 0; i < numOptions; i++) {
    Common::GoToXY(startXlocation + 3,startYlocation + i);
    cout << myOptions[i];
  }

  option = 0;  
  
  while (key != 13) {
    cursorY = option + startYlocation;
  
    Common::GoToXY(startXlocation, cursorY);
    cout << "->";  
  
    key = _getch();
    
    Common::GoToXY(startXlocation, cursorY);
    cout << "  ";
    
    if (key == 72 && option != 0) {
      // Move Up One
      option--;
    }
    if (key == 73) {
      // Move To Top
      option = 0;
    }
    if (key == 80 && option != (numOptions - 1)) {
      // Move Down One
      option++;
    }
    if (key == 81) {
      // Move To Bottom
      option = numOptions - 1;
    }
  }
  
  Common::GoToXY(startXlocation,startYlocation + numOptions);
  
  return option;

}
