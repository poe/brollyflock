#include <avr/pgmspace.h>
#include "LED_serial.h"
#include "memory_propigation.h"
#include "memory_color.h"
#include "brolly.h"

//This outputs the LED states when set to true.
#define DEBUG true

unsigned long sequenceListTime;
unsigned long colorListTime;
unsigned long loopCount = 0;
unsigned long printingLoops = 60;

void setup() {
   Serial.begin(9600);
   LEDSetup();
   for(int i=0; i<NumLEDs;i++){
     brollies[i].initialize(i);
     brollies[i].setDelay();
   }
   sequenceListTime = millis();
   colorListTime = millis();
};

void loop() {
  
  loopCount++;
  
  for(int i=0; i<NumLEDs;i++){
    brollies[i].advanceColor();
  };
  
  if(loopCount % printingLoops == 0){
    brollies[0].getColor().printColor();
    brollies[24].getColor().printColor();
    Serial.print(" loopCount = ");  
    Serial.print(loopCount);
    Serial.println("");
  };
  
  if(millis() - colorListTime > 40000){
    colorListTime = millis();
    masterColorList.incrementList();
//    Serial.println("**Next Color List**");
  };
  
  WriteLEDArray();

  if(loopCount % printingLoops == 0){
    if(millis() - sequenceListTime > 2000){
      sequenceListTime = millis();
//      masterSequenceList.incrementList();
      for(int i=0; i<NumLEDs;i++){
        brollies[i].setDelay();
      };
//      Serial.println("**Next Propigation List**");
    };
  };

}





