#include "WProgram.h"
#include "brollyflock_color.h"
#include "brollyflock_data.h"

Color::Color(){
  red   = 0;
  green = 0;
  blue  = 0;
};

Color::Color(int red_in, int green_in, int blue_in){
  red   = red_in;
  green = green_in;
  blue  = blue_in;
};

Step::Step(){
   target.red = 0;
   target.green = 0;
   target.blue = 0;
};

Step::Step(Color inputColor, unsigned long set_time){
  target.red = inputColor.red;
  target.green = inputColor.green;
  target.blue = inputColor.blue;
  time = set_time;
};


ColorScheme::ColorScheme(){
  numberOfSteps = colorSteps;
};

ColorScheme::ColorScheme(Step in_steps[],int in_numberOfSteps){
  numberOfSteps = in_numberOfSteps;
  steps = in_steps;
};

