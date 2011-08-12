#include "WProgram.h"
#include "brollyflock_propigation.h"

Direction::Direction(){
   int from = 0;
   int to = 1;
   extraTime = 0;
};

Direction::Direction(int in_from, int in_to, unsigned long in_extraTime){
   from = in_from;
   to = in_to;
   extraTime = in_extraTime;
};

Propigation::Propigation(){ 
   numberOfSteps = 0;
};

Propigation::Propigation(Direction in_movement[],int in_numberOfSteps){
   numberOfSteps = in_numberOfSteps;
   movement = in_movement;   
};

