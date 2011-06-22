#include "WProgram.h"
#include "brolly.h"
#include "LED_serial.h"

Brolly::Brolly(){
  lastDelayTime = 0;
  delayTime = 0;
};

Color Brolly::getColor(){
  return getArrayColor(address);
};

Color Brolly::setColor(Color in_color){
  setArrayColor(in_color.getRed(),in_color.getGreen(),in_color.getBlue(),address);
  return Color(in_color.getRed(),in_color.getGreen(),in_color.getBlue());
};

void Brolly::initialize(int i){
  address = i;
  colorDelay = 500;
  delayTime = 0;
};

void Brolly::setDelay(){
  lastDelayTime = delayTime;
  delayTime = masterSequenceList.getAverageDelay(address);
};

Color Brolly::advanceColor(){
   Color newColor = masterColorList.getSmoothColorNow(delayTime);
   if (masterSequenceList.transitionRatio() == 1){
     return setColor(newColor);
   };
   Color oldColor = masterColorList.getSmoothColorNow(lastDelayTime);   
   Color transitionColor = transitionColor.progressColor(oldColor, newColor, masterSequenceList.transitionRatio());
   return setColor(transitionColor);
};

Brolly brollies[NumLEDs];
