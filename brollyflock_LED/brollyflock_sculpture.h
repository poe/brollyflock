

#ifndef brollyflock_sculpture_h
#define brollyflock_sculpture_h
#include "WProgram.h"
#include "memory_color.cpp"
#include "memory_propigation.h"


#define NumLEDs 48

class Brolly {
   public:
     Brolly();
     void nextStep();
     void stepProgress(ColorList* colorScheme);
     void moveColor(ColorList* colorScheme);
     Color currentColor;
     int currentStep;
     unsigned long extraDelay;
     boolean delaying;
   private:
     unsigned long lastStep;
     unsigned long timeInStep;
     int numberOfSteps;
};

/*
class Sculpture {
  public:
    int numberOfBrollies;
    int numberOfPropSteps;
    Sculpture();
//    Sculpture(int in_numberOfBrollies,int in_numberOfPropSteps,Brolly in_brollies[],Step in_colorScheme[]);
    Brolly* brollies;
//    Step* colorScheme;
//    void initializeBrollies(Brolly firstBrollies[],Propigation showMovement);
};
*/
extern Brolly firstBrollies[NumLEDs];

//extern Sculpture sculpture();

#endif
