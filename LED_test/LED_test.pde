#include "LED_serial.h"

//This outputs the LED states when set to true.
#define DEBUG true

void setup() {
   Serial.begin(9600);
   LEDSetup();
};

void loop() {
  
   if (Serial.available()>0){            // Check to see if there are any serial input
      LEDOn = serReadInt();
      Serial.print("LEDOn = ");
      Serial.println(LEDOn);
    if(LEDOn > NumLEDs - 1){
      Serial.println("LED Number too great");
      LEDOn = 0;
      Serial.print("LEDOn = ");
      Serial.println(LEDOn);
    }
    if(LEDOn < 0){
      Serial.println("Negative LED number");
      LEDOn = 0;
      Serial.print("LEDOn = ");
      Serial.println(LEDOn);
    }

   }

  for(int i=0;i<NumLEDs;i++){
    setColor(0,0,500,i); 
  }
  setColor(1023,1023,0,LEDOn);
  WriteLEDArray();

}





