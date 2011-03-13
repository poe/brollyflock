#include "ShiftBrite.h"

ShiftBrite SB(10); //A ShiftBrite starting on pin 10, assumes the next pins are sequentially going up
byte i;
void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH); //this is un UGLY HACK to supply +5 on pin 9 
                    //so the SB can be directly hooked on the the arduino.  
                    //This will probably burn out your arduino and cause the end of days.  
                    //Find a better way of supply power to the SBs
  SB.setPower(127); //Full power captin!
  i=0;
}


//This examples has three ShiftBrites chained together in series, and cycles some colours through them
//This uses 5 bit colors (0-31 values)
void loop() {
  SB.setColor5b(i,0,0); // SB #3 (since the data gets pushed through the SBs, the last one is set first
  SB.setColor5b(0,i,0); // SB #2
  SB.setColor5b(0,0,i); // SB #1
  delay(500);
  SB.setColor5b(0,i,0); 
  SB.setColor5b(0,0,i);
  SB.setColor5b(i,0,0);
  delay(500);
  SB.setColor5b(0,0,i); 
  SB.setColor5b(i,0,0);
  SB.setColor5b(0,i,0);
  delay(500);
  i++; //next level of color
  if (i>31) i=0; //only 5 bit color, so start the cycle over again.
}
