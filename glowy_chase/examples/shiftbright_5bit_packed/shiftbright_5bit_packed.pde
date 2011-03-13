#include "ShiftBrite.h"

ShiftBrite SB(10); //A ShiftBrite starting on pin 10, assumes the next pins are sequentially going up

void setup() {
  pinMode(9,OUTPUT);
  digitalWrite(9,HIGH); //this is un UGLY HACK to supply +5 on pin 9 
                    //so the SB can be directly hooked on the the arduino.  
                    //This will probably burn out your arduino and cause the end of days.  
                    //Find a better way of supply power to the SBs
  SB.setPower(127); //Full power captin!
}


//This examples has three ShiftBrites chained together in series, and cycles some colours through them
void loop() {
  int val;
  byte r = 0x00;
  byte g = 0x04;
  byte b = 0x05;
  
  val = (r & 0x1F); //pack the channels into a single int
  val = (val << 5) | (g & 0x1F);
  val = (val << 5) | (b & 0x1F);
  
  SB.setColor5b(val);
  delay(100);
}
