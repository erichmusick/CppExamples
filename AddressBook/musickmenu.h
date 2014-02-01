#ifndef _MUSICKMENU_H
#define _MUSICKMENU_H

#include <vector>
#include <string>

using namespace std;

void PressEnterToContinue();
int intLength(int value);
void dispSpaces(int numSpaces);

class MusickMenu {

  public:
  
  // Constructors:
  MusickMenu();
  
  MusickMenu(vector<string> options);
  
  void SetOptions(vector<string> options);
  
  int GetChoice(const int startXlocation = 1, const int startYlocation = 1);

  private:
  vector<string> myOptions;

};

#endif

