#include <avr/pgmspace.h>
#include "LED_serial.h"
#include "memory_propigation.h"
#include "memory_color.h"

//This outputs the LED states when set to true.
#define DEBUG true

void setup() {
   //Serial.begin(9600);
   LEDSetup();
};

void loop() {
  
  int colorDelay;
  unsigned long startTime;  
   
  for (int target_index = 0; target_index < masterColorList.numberOfElements(); target_index++){
    Color targetColor = masterColorList.getCurrentColor(target_index);
    Color oldColor = masterColorList.getLastColor(target_index);
    colorDelay = masterColorList.getDelay(target_index);
    unsigned long startTime = millis();
    for (unsigned long elapsedTime = (millis() - startTime); elapsedTime < colorDelay; elapsedTime = (millis() - startTime)){
      int fraction =  elapsedTime;
      Color fracColor = fracColor.progressColor(oldColor, targetColor, float(fraction) / colorDelay);

      Serial.print(" Delay = ");
      int thisDelay = masterColorList.getDelay(target_index);
      Serial.print(thisDelay);

      Serial.print(" target_index = ");
      Serial.print(target_index);

      Serial.print(" elapsedTime = ");
      Serial.print(elapsedTime);
      
      Serial.print(" fraction = ");
      Serial.print(fraction);
      Serial.print("/");
      Serial.print(colorDelay);

      Serial.print(" Oldred = ");
      Serial.print(oldColor.getRed());
      
      Serial.print(" Newred = ");
      Serial.print(targetColor.getRed());
      
      Serial.print(" Fracred = ");
      Serial.print(fracColor.getRed());
  
      Serial.print(" green = ");
      Serial.print(fracColor.getGreen());
  
      Serial.print(" blue = ");
      Serial.print(fracColor.getBlue());
      
      Serial.println("");
      for(int i=0;i<NumLEDs;i++){
        setColor(fracColor.getRed(),fracColor.getGreen(),fracColor.getBlue(),i); 
      }
      WriteLEDArray();
    }
  }
  
  masterColorList.incrementList();


}





