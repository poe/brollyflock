#include "WProgram.h"
#include "LED_serial.h"
#include "memory_color.h"

//This array is where the actual colors are stored.
//Note that this takes up about a third of the (1 K!) stack.
int LEDChannels[NumLEDs][3] = {0};

//These are integers that get pushed down the serial bus
int SB_CommandMode;
int SB_RedCommand;
int SB_GreenCommand;
int SB_BlueCommand;

//This method composes one packet for the serial bus, minus the color itself.
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

//Here we actually push out the serial bus 
void WriteLEDArray() {
    
    //Here we toggle the enable pin to reduce mystery occasional flicker.
    delayMicroseconds(15);
    digitalWrite(enablepin,HIGH); // reduce flicker
    delayMicroseconds(15);
    digitalWrite(enablepin,LOW);
 
    
    SB_CommandMode = B00; // Write to PWM control registers
    for (int h = 0;h<NumLEDs;h++) {
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

void setArrayColor(int red,int green, int blue, int brolly){
   //red is one and green is zero?  WTF!?!?
   LEDChannels[brolly][1] = red;
   LEDChannels[brolly][0] = green;
   LEDChannels[brolly][2] = blue;   
};

Color getArrayColor(int brolly){
   //red is one and green is zero?  WTF!?!?
   int red = LEDChannels[brolly][1];
   int green = LEDChannels[brolly][0];
   int blue = LEDChannels[brolly][2];
   return Color(red,green,blue);   
};

//Here is the simple setup for the LED pins and so on.
void LEDSetup(){
   pinMode(datapin, OUTPUT);
   pinMode(latchpin, OUTPUT);
   pinMode(enablepin, OUTPUT);
   pinMode(clockpin, OUTPUT);
   SPCR = (1<<SPE)|(1<<MSTR)|(0<<SPR1)|(0<<SPR0);
   digitalWrite(latchpin, LOW);
   digitalWrite(enablepin, LOW);
   Serial.println("Setup Done.");
   unsigned long setupTime = millis();
};

int serReadInt()
{
 int i, serAva;                           // i is a counter, serAva hold number of serial available
 char inputBytes [7];                 // Array hold input bytes
 char * inputBytesPtr = &inputBytes[0];  // Pointer to the first element of the array
     
 if (Serial.available()>0)            // Check to see if there are any serial input
 {
   delay(5);                              // Delay for terminal to finish transmitted
                                              // 5mS work great for 9600 baud (increase this number for slower baud)
   serAva = Serial.available();  // Read number of input bytes
   for (i=0; i<serAva; i++)       // Load input bytes into array
     inputBytes[i] = Serial.read();
   inputBytes[i] =  '\0';             // Put NULL character at the end
   return atoi(inputBytesPtr);    // Call atoi function and return result
 }
 else
   return -1;                           // Return -1 if there is no input
};


