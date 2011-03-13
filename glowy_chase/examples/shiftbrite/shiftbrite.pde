#include "ShiftBrite.h"

ShiftBrite SB(10); //A ShiftBrite starting on pin 10, assumes the next pins are sequentially going up

void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH);
  SB.setPower(127);
}


//This examples has three ShiftBrites chained together in series, and cycles some colours through them
void loop() {
  SB.setColor(1023,0,0); // SB #3 (since the data gets pushed through the SBs, the last one is set first
  SB.setColor(0,1023,0); // SB #2
  SB.setColor(0,0,1023); // SB #1
  delay(500);
  SB.setColor(0,1023,0); 
  SB.setColor(0,0,1023);
  SB.setColor(1023,0,0);
  delay(500);
  SB.setColor(0,0,1023); 
  SB.setColor(1023,0,0);
  SB.setColor(0,1023,0);
  delay(500);
}
