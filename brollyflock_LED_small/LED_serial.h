#include "WProgram.h"
#ifndef LED_serial_h
#define LED_serial_h
#include "memory_color.h"

//Here we define which pins we are using
#define clockpin 13 // CI
#define enablepin 10 // EI
#define latchpin 9 // LI
#define datapin 11 // DI

//This is the number of LEDs (or brollies) 
#define NumLEDs 48

//Here are the variables and array the basic LED system needs externed
extern int LEDChannels[][3];
extern int SB_CommandMode;
extern int SB_RedCommand;
extern int SB_GreenCommand;
extern int SB_BlueCommand;

//I think this is from a previous debugging set
//extern int LEDOn;

//Here are the basic fucntions for pushing the LED to the serial bus.
void SB_SendPacket();
void WriteLEDArray();

//These allow access to the color array from the higher level objects
void setArrayColor(int red,int green, int blue, int brolly);
Color getArrayColor(int brolly);

//This sets up the LED pins and stuff.
void LEDSetup();

//Here we compress the numbers in the array to the serial bus
int serReadInt();

#endif
