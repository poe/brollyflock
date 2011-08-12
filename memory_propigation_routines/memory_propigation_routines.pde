#include <avr/pgmspace.h>
#include "memory_propigation.h"



void setup()			  
{
  Serial.begin(9600);
}

void loop()			  
{
//  Serial.print(" currentList.sizeOfList = ");
//  Serial.print(currentList._sizeOfList);
   
  for (int i = 0; i < masterList.getNumberOfElements(); i++){
    Serial.print(" i = ");
    Serial.print(i);
    
    int from = masterList.getFrom(i);
    Serial.print(" from = ");
    Serial.print(from);

    int to = masterList.getTo(i);
    Serial.print(" to = ");
    Serial.print(to);

    int delayMove = masterList.getDelay(i);
    Serial.print(" delayMove = ");
    Serial.print(delayMove);
    
    Serial.println("");
  }
  
  masterList.incrementList();

  Serial.println("");
  Serial.println(" loop ");
  Serial.println("");
}

