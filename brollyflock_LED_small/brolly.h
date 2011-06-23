//all arduino libraries require this
#include "WProgram.h"

//Here we keep the header from being included multiple times
#ifndef brolly_h
#define brolly_h

//We use both other brolly libraries here
#include "memory_propigation.h"
#include "memory_color.h"

//Here is the brolly class.  This encapsulates color and offset for each brolly.
class Brolly{
  public:
    //constructor
    Brolly();
    
    //move along the color scheme
    Color advanceColor();

    //these wrap the LEDchannels array
    Color setColor(Color in_color);
    Color getColor();
    
    //Here are initalizers we use because the constructor can't use millis
    void initialize(int i);
    void setDelay();

  //here are the private data
  private:  
    //address of the brolly.  initalized to the number of the brolly in the array
    int address;
    
    //this is the delay from the previous sequence
    unsigned long lastDelayTime;
    
    //this is the delay from the current sequence
    unsigned long delayTime;
};

extern Brolly brollies[];

#endif
