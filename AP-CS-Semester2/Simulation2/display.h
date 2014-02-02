// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// display.h - copyright statement added 5/31/2000

#ifndef _DISPLAY_H
#define _DISPLAY_H

/**
  * Display displays all entries in an environment
  * in a text format, e.g., using fish-supplied characters
  * for fish and space ' ' for empty-space.
  *
  * Show(..) is used to display the current state of
  * an environment.  In this text-based display, all information
  * for Show(..) is accessible via the Environment passed into Show(..).
  *
  *
  */

// class declarations for those classes only used
// as references (passed by reference/const reference)

class Environment;

class Display
{
  public:

  // constructor
  Display();
    // postcondition: ready to display an Environment

  // modifying function
  void Show(const Environment & env, bool displayBorder = false, int startXlocation = 1, int startYlocation = 1);  // display state of env
    // postcondition: state of env written as text to cout

  private:

    // nothing here now

};

#endif


