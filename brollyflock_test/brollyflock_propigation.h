#include "WProgram.h"
#ifndef brollyflock_propigation_h
#define brollyflock_propigation_h

class Direction{
  public:
    Direction();
    Direction(int in_from, int in_to, unsigned long in_extraTime);
    int from;
    int to;
    unsigned long extraTime;
};

class Propigation{
  public:
    Propigation();
    Propigation(Direction in_movement[],int in_numberOfSteps);
    Direction* movement;
    int numberOfSteps;
};

#endif
