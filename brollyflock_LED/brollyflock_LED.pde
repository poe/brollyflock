#include <avr/pgmspace.h>
//#include "memory_color.h"
//#include "memory_propigation.h"
//#include "brollyflock_sculpture.h"

#define NumLEDs 48

//Here we define which pins we are using
#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI

//This outputs the LED states when set to true.
#define DEBUG true

int LEDChannels[NumLEDs][3] = {0};
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;

void setColor(int red,int green, int blue, int brolly){
   LEDChannels[brolly][0] = red;
   LEDChannels[brolly][1] = green;
   LEDChannels[brolly][2] = blue;   
};


void setup() {
  if(DEBUG){
   Serial.begin(9600);
  }
  Serial.println("in setup");
//   sculpture.initializeBrollies(firstBrollies,showMovement);
   pinMode(datapin, OUTPUT);
   pinMode(latchpin, OUTPUT);
   pinMode(enablepin, OUTPUT);
   pinMode(clockpin, OUTPUT);
   SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
   digitalWrite(latchpin, LOW);
   digitalWrite(enablepin, LOW);
   Serial.println("Brolly Flock Sequencer Setup Done.");
   unsigned long setupTime = millis();
};


void SB_SendPacket() {
    if (SB_CommandMode == B01) {
     SB_RedCommand = 120;
     SB_GreenCommand = 100;
     SB_BlueCommand = 100;
    }
 
    SPDR = SB_CommandMode << 6 | SB_BlueCommand>>4;
    while(!(SPSR & (1<<SPIF)));
    SPDR = SB_BlueCommand<<4 | SB_RedCommand>>6;
    while(!(SPSR & (1<<SPIF)));
    SPDR = SB_RedCommand << 2 | SB_GreenCommand>>8;
    while(!(SPSR & (1<<SPIF)));
    SPDR = SB_GreenCommand;
    while(!(SPSR & (1<<SPIF)));
 
};
 
void WriteLEDArray() {
 
    SB_CommandMode = B00; // Write to PWM control registers
    for (int h = 0;h<NumLEDs-1;h++) {
	  SB_RedCommand = LEDChannels[h][0];
	  SB_GreenCommand = LEDChannels[h][1];
	  SB_BlueCommand = LEDChannels[h][2];
	  SB_SendPacket();
    }
 
    delayMicroseconds(15);
    digitalWrite(latchpin,HIGH); // latch data into registers
    delayMicroseconds(15);
    digitalWrite(latchpin,LOW);
 
    SB_CommandMode = B01; // Write to current control registers
    for (int z = 0; z < NumLEDs; z++) SB_SendPacket();
    delayMicroseconds(15);
    digitalWrite(latchpin,HIGH); // latch data into registers
    delayMicroseconds(15);
    digitalWrite(latchpin,LOW);
 
};

void loop() {
  for(int i=0;i<NumLEDs;i++){
//    firstBrollies[i].stepProgress(colorScheme);
//    firstBrollies[i].moveColor(colorScheme);
    if(DEBUG){
      Serial.print(" NumLEDs = ");
      Serial.print(NumLEDs);      
/*      Serial.print(" firstBrollies[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.print(" delay = ");
      Serial.print(firstBrollies[i].extraDelay);
      Serial.print("\t red  = ");
      Serial.print(firstBrollies[i].currentColor.getRed());
      Serial.print("\t green  = ");
      Serial.print(firstBrollies[i].currentColor.getGreen());
      Serial.print("\t blue  = ");
      Serial.print(firstBrollies[i].currentColor.getBlue());
      Serial.print("\t millis = ");
      Serial.print(millis());
      Serial.print("\t currentStep = ");
      Serial.print(firstBrollies[i].currentStep);
      Serial.println("");
*/
    }
//    setColor(firstBrollies[i].currentColor.red,firstBrollies[i].currentColor.green,firstBrollies[i].currentColor.blue,i); 
//    setColor(500,500,500,2); 
//   LEDChannels[0][0] = 500;
  }
//   WriteLEDArray();
};
