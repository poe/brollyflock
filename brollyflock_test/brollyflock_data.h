#include "WProgram.h"
#ifndef brollyflock_data_h
#define brollyflock_data_h
#include "brollyflock_color.h"
//#include "brollyflock_propigation.h"
//#include "brollyflock_sculpture.h"


//This is the number of LEDs (or brollies) 
#define NumLEDs 48

//This is the number of directional propigations the LEDs are programmed with.
#define PropigationSteps 48

//#define ColorSteps 6

extern Step colorScheme[];

extern int colorSteps;

//extern Direction firstShow[];


//extern Direction firstShow[] = {Direction(0,1,1000),Direction(1,2,1000)};



#endif
