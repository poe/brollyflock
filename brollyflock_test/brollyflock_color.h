#include "WProgram.h"
#ifndef brollyflock_color_h
#define brollyflock_color_h

//Your standard 3 part color class
class Color {
   public:
     Color();
     Color(int red_in, int green_in, int blue_in);
     void progressColor(Color old_color,Color new_color,float fraction);
     private:
     int red;
     int green;
     int blue;
};
// the #include statment and code go here...


//This class is used to contain a target color and the time you should take getting there
class Step {
  public:
    Step(Color inputColor, unsigned long time);
    Step();
    Color target;
    unsigned long time;
};

//This class contains a bunch of steps, so it has the whole fading rainbow that the sculpture displays.  
class ColorScheme{
  public:
    ColorScheme();
    ColorScheme(Step in_steps[],int in_numberOfSteps);
    Step* steps;
    int numberOfSteps;
};

#endif
