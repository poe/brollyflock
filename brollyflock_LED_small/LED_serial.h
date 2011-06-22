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

extern int LEDChannels[][3];
extern int SB_CommandMode;
extern int SB_RedCommand;
extern int SB_GreenCommand;
extern int SB_BlueCommand;

extern int LEDOn;

void SB_SendPacket();
void WriteLEDArray();
void setArrayColor(int red,int green, int blue, int brolly);
Color getArrayColor(int brolly);
void setTargetArrayColor(int red,int green, int blue, int brolly);
Color getTargetArrayColor(int brolly);
void LEDSetup();
int serReadInt();

#endif
