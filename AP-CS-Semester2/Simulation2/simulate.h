// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// simulate.h - copyright statement added 5/31/2000

#ifndef _SIMULATION_H
#define _SIMULATION_H

/**
  * Simulation controls a simulation of fish as
  * represented in an Environment.
  *
  * One step of a simulation can be performed via Step(..),
  * an arbitrary number of steps via Run(..).
  *
  */


// class declarations for those classes only used
// as references (passed by reference/const reference)

class Environment;


class Simulation
{
  public:
    Simulation();
    // postcondition: simulation is ready to run

    void Step(Environment & env);
    // postcondition: one step of simulation in env has been made

    void Run(Environment & env, int steps);
    // postcondition: simulation on env run for # steps passed as steps

};

#endif

