/* intercom.cpp */
/* brollyflock
   22 Jun 2011
   
*/ 

#include "wProgram.h"
#include "intercom.h"

// import processing.serial.*;

#define BAUDRATE 9600


void setup_serial(void) {
  Serial.begin(BAUDRATE);
}

int listen_from_firectl(void) {
//   returns 0 for nothing of interest yet
//   returns nonzero for something useful

  int inByte = 0;

  if (Serial.available() > 0) {
    inByte = Serial.read();
    
    Serial.println(inByte);
    
    switch (inByte) {
       case BUTTONONE:
       case BUTTONTWO:
       case BUTTONTHREE:    // we got something we like
          return (inByte);
          break;
       default:        // we got something but we didn't like it
//          complain();
          return 0;
          break;
     }
  }

  // we got nuthin
  return 0;

}


void send_to_firectl(char thing_to_send) {
   Serial.print(thing_to_send, BYTE);
}


int listen_from_ledctl(void) {

}


void send_to_ledctl(int thing_to_send) {
   Serial.print(thing_to_send, BYTE);     
}

