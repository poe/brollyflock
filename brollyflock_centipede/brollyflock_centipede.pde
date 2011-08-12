#include <Wire.h>
#include "Centipede.h"

/* Available commands
  .digitalWrite([0...127], [LOW...HIGH]) - Acts like normal digitalWrite
  .digitalRead([0...127]) - Acts like normal digitalRead
  .pinMode([0...127], [INPUT...OUTPUT]) - Acts like normal pinMode
  .portWrite([0...7], [0...65535]) - Writes 16-bit value to one port (device)
  .portRead([0...7]) - Reads 16-bit value from one port (device)
  .portMode([0...7], [0...65535]) - Write I/O mask to one port (device)
  .init() - Sets all register to initial values

  Examples
  CS.init();
  CS.pinMode(0,OUTPUT);
  CS.digitalWrite(0, HIGH);
  int recpin = CS.digitalRead(0);
  CS.portMode(0, 0b0111111001111110);
  CS.portWrite(0, 0b1000000110000001);
  int recport = CS.portRead(0);
*/

Centipede CS; // create Centipede object

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting centipede test.");

  Wire.begin(); // start I2C
  CS.initialize(); // set all register to default

  for(int i = 0; i < 55; i++)
  { 
    Serial.print(i);
    Serial.println(" OUTPUT"); 
    CS.pinMode(i, OUTPUT); // set all pins on port 0 to output
  }
  
}

void loop()
{
  for(int i = 0; i < 8; i++)
  {
    Serial.println(i); 
    CS.digitalWrite(i,HIGH);
    Serial.println("HIGH");
    delay(500);
    CS.digitalWrite(i,LOW);
    Serial.println("LOW");
    delay(500);
  }
} 

void flash()
{
  for(int i = 0; i < 55; i++)
  { 
    Serial.println("HIGH"); 
    CS.digitalWrite(i, HIGH); 
  }
  delay(1500);
  for(int i = 0; i < 55; i++)
  {
    Serial.println("LOW"); 
    CS.digitalWrite(i, LOW); 
  }
  delay(150);

}
