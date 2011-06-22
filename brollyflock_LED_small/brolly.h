#include "WProgram.h"
#ifndef brolly_h
#define brolly_h
#include "memory_propigation.h"
#include "memory_color.h"

class Brolly{
  public:
    Brolly();
    Color advanceColor();

    void setOldColor(Color in_color);
    Color getOldColor();
    Color setColor(Color in_color);
    Color getColor();
    
    void initialize(int i);
    void setDelay();

    void nextTarget();
    
    int colorDelay;
    int address;
    unsigned long lastDelayTime;
    unsigned long delayTime;
};

extern Brolly brollies[];

#endif
