//all arduino libraries 
#include "WProgram.h"

//Brolly header
#include "brolly.h"

//We access the array in this header directly from these objects
#include "LED_serial.h"

//This is your basic brolly constructor
//Note that the brollies still have to be initialized because millis() is not accessable outside setup and loop
//It is also the case that the initializer depends on the masterColorList and masterSequenceList being constructed
Brolly::Brolly(){
  lastDelayTime = 0;
  delayTime = 0;
};

//Returns the colors in color from the LED array in convenient color objects.  
Color Brolly::getColor(){
  return getArrayColor(address);
};

//This sets the color in the array from a convenient color object.
Color Brolly::setColor(Color in_color){
  setArrayColor(in_color.getRed(),in_color.getGreen(),in_color.getBlue(),address);
  return Color(in_color.getRed(),in_color.getGreen(),in_color.getBlue());
};

//Here we initalize the brollies.
void Brolly::initialize(int i){
  address = i;
  delayTime = 0;
};

//This is the place we initialize or reset the extra offsets in the sequences
void Brolly::setDelay(){
  //lastDelayTime is designed to allow us to move between sequences smoothly.
  lastDelayTime = delayTime;
  //Here we set the offset through a *recursive* function in memory_propigation.cpp
  delayTime = masterSequenceList.getAverageDelay(address);
};

Color Brolly::advanceColor(){
   //This gets a color from the master color list, smoothed from the last color list to the current one
   //Then it offsets it by the delay stored in the brolly via memory_propigation
   Color newColor = masterColorList.getSmoothColorNow(delayTime);

   //if we are outside of a sequence transition we can do one calculation instead of two.
   if (masterSequenceList.transitionRatio() == 1){
     //return for debugging purposes
     return setColor(newColor);
   };
   
   //Here we get the old color and use the ratio to move it along toward the new color
   Color oldColor = masterColorList.getSmoothColorNow(lastDelayTime);   
   Color transitionColor = transitionColor.progressColor(oldColor, newColor, masterSequenceList.transitionRatio());
   return setColor(transitionColor);
};

//This is the actual array of brollies with data.  
Brolly brollies[NumLEDs];
