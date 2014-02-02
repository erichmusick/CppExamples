// AP Computer Science Marine Biology Case Study program
// Copyright (C) 2000  College Board and Educational Testing Service

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// simulate.cpp - copyright statement added 5/31/2000

#include <vector>

#include "simulate.h"
#include "environ.h"
#include "utils.h"
#include "randgen.h"

using namespace std;

// constructor

Simulation::Simulation()
// postcondition: simulation is ready to run
{

}

// public modifying functions

void Simulation::Step(Environment & env)
// postcondition: one step of simulation in env has been made
{
  vector<Fish> fishList;
  int k;
  RandGen r;
  Neighborhood nbrs;

  fishList = env.AllFish();

  Sort(fishList, fishList.size());

  for (k = 0; k < fishList.size(); k++)
  {
    fishList[k].Move(env);
  }
  for (k = 0; k < fishList.size(); k++)
  {
    if (r.RandInt(25) == 0) {
      nbrs = fishList[k].EmptyNeighbors(env, fishList[k].Location());
      if (nbrs.Size() > 0 && fishList[k].CanMate(env)) {
        env.AddFish(nbrs.Select(r.RandInt(0, nbrs.Size() - 1)),r.RandInt(0,1));
      }
    }
    if (r.RandInt(195) == 0) {
      env.RemoveFish(fishList[k]);
    }    
  }
}

void Simulation::Run(Environment & env, int steps)
// postcondition: simulation on env run for # steps passed as steps
{
  int k;

  for (k = 0; k < steps; k++)
  {
    Step(env);
  }
}