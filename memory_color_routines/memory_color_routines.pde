#include "memory_color.h"

void setup()			  
{
  Serial.begin(9600);
}

void loop()			  
{
//  Serial.print(" currentList.sizeOfList = ");
//  Serial.print(currentList._sizeOfList);

  unsigned int from;
  unsigned int to;
  unsigned int delayMove;  
   
  for (int target_index = 0; target_index < masterColorList.numberOfElements(); target_index++){
    Color targetColor = masterColorList.getCurrentColor(target_index);
    Color oldColor = masterColorList.getLastColor(target_index);
    for (int fraction = 0; fraction < 11; fraction++){
      Color fracColor = fracColor.progressColor(oldColor, targetColor, float(fraction) / 10);
      Serial.print(" target_index = ");
      Serial.print(target_index);
      
      Serial.print(" fraction = ");
      Serial.print(fraction);
      Serial.print("/10");

      Serial.print(" Oldred = ");
      Serial.print(oldColor.getRed());
      
      Serial.print(" Newred = ");
      Serial.print(targetColor.getRed());
      
      Serial.print(" Fracred = ");
      Serial.print(fracColor.getRed());
  
      Serial.print(" green = ");
      Serial.print(fracColor.getGreen());
  
//      Serial.print(" blue = ");
//      Serial.print(fracColor.getBlue());
      
      Serial.println("");
    }
  }
  
  masterColorList.incrementList();

  Serial.println("");
  Serial.println(" loop ");
  Serial.println("");
}

