#include <avr/pgmspace.h>
#include "LED_serial.h"
#include "memory_propigation.h"
#include "memory_color.h"
#include "brolly.h"
#include "intercom.h"

//These are the timer counters that allow you to cycle the sequences and colors
unsigned long sequenceListTime;
unsigned long colorListTime;

//This allows you to serial print debugging out put every so many loops
unsigned long loopCount = 0;
unsigned long printingLoops = 60;

unsigned long flashDelay;

//this is the setup loop.  Here we initalize brollies and the timer loops
//Serial communication here is used for debugging output
void setup() {
   Serial.begin(9600);
   //This is the setup routine for the LED C library.  Everything I wrote writes back to an array that drives this.
   LEDSetup();
   
   //Here we initalize the brollies (because you can't have millis() in a constructor) 
   for(int i=0; i<NumLEDs;i++){
     brollies[i].initialize(i);
     brollies[i].setDelay();
   }
   //Here we set the initial timers for the sequence rotator and the color rotator.
   sequenceListTime = millis();
   colorListTime = millis();
   flashDelay = millis() + 2000;
   randomSeed(analogRead(0));
};

int button_state = 0;

int flashingLEDNumber = -1;

Color flashingLEDStoredValue;

boolean flashing;

void loop() {
  button_state = listen_from_firectl();
    
  //Here we increment the debugging output loop
  loopCount++;
  
  //This is the real meat of the matter.  The array is set here, and the colors advance to the next (faded, averaged, color)
  for(int i=0; i<NumLEDs;i++){
    brollies[i].advanceColor();
  };
  
  //Here we print a few colors in the debugging output and the loop count.
  if(loopCount % printingLoops == 0){
//    brollies[0].getColor().printColor();
//    brollies[24].getColor().printColor();
//    Serial.print(" transitionRatio = ");
//    Serial.print(masterSequenceList.transitionRatio());
//    Serial.print(" loopCount = ");  
//    Serial.print(loopCount);
//    Serial.println("");
  };
  
  //This decides when to move to the next color scheme.  The colors are temporarily averaged between the two schemes.  See memory_color.cpp for details
  if(millis() - colorListTime > 30000){
    colorListTime = millis();
    masterColorList.incrementList();
//    Serial.println("**Next Color List**");
  };
  
  if(button_state == BUTTONTWO || button_state == BUTTONTHREE || button_state == BUTTONONE){
    flashing = true;
    button_state = 0;
    flashDelay = millis();
    flashingLEDNumber = random(NumLEDs);
    if(0 < flashingLEDNumber < NumLEDs){
      flashingLEDStoredValue = brollies[flashingLEDNumber].getColor();
      brollies[flashingLEDNumber].setColor(Color(1023,1023,1023));
    };
  };
  
  if(millis() - flashDelay < 2000){
    if(0 < flashingLEDNumber < NumLEDs){
      brollies[flashingLEDNumber].setColor(flashingLEDStoredValue);
    };
    flashingLEDNumber = random(NumLEDs);
    if(0 < flashingLEDNumber < NumLEDs){
      flashingLEDStoredValue = brollies[flashingLEDNumber].getColor();
      brollies[flashingLEDNumber].setColor(Color(1023,1023,1023));
    }
  }
  else{
    if(0 < flashingLEDNumber < NumLEDs){
      brollies[flashingLEDNumber].setColor(flashingLEDStoredValue);
    };
    flashingLEDNumber = -1;  //set it outside the range of the LEDs so the above conditional no longer gets called.
  }
    
  //This is the meat of the matter, where the LED array gets updated and the serial bus gets pushed out.
  WriteLEDArray();
  
  //The number on the right of the comparison here is the time to cycle to the next propagation scheme. (x)
/*  if(millis() - sequenceListTime > 300000){
    //this resets the sequence base time so we wait another x seconds where x is set above.
    sequenceListTime = millis();
    //The line below moves to the next propagation scheme.  
    masterSequenceList.incrementList();
    for(int i=0; i<NumLEDs;i++){
      brollies[i].setDelay();
    };
//    Serial.println("**Next Propigation List**");
    button_state = 0;
  };
*/

}





