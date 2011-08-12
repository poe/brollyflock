// Centipede Shield Library
// Controls MCP23017 16-bit digital I/O chips

#include "WProgram.h"
#include "Centipede.h"
#include <Wire.h>

uint8_t CSDataArray[2] = {0};

#define CSAddress 0b0100000

Centipede::Centipede()
{
  // no constructor tasks yet
}

// Set device to default values
void Centipede::initialize()
{

  for (int j = 0; j < 4; j++) {

    CSDataArray[0] = 255;
    CSDataArray[1] = 255;

    WriteRegisters(0, 0x00, 2);

    CSDataArray[0] = 0;
    CSDataArray[1] = 0;

    for (int k = 2; k < 0x15; k+=2) {
      WriteRegisters(j, k, 2);
    }

  }

}


void Centipede::WriteRegisters(int port, int startregister, int quantity) {

  Wire.beginTransmission(CSAddress + port);
    Wire.send(startregister);
    for (int i = 0; i < quantity; i++) {
      Wire.send(CSDataArray[i]);
    }
  Wire.endTransmission();

}

void Centipede::ReadRegisters(int port, int startregister, int quantity) {

  Wire.beginTransmission(CSAddress + port);
    Wire.send(startregister);
  Wire.endTransmission();
  Wire.requestFrom(CSAddress + port, quantity);
  for (int i = 0; i < quantity; i++) {
    CSDataArray[i] = Wire.receive();
  }

}


void Centipede::WriteRegisterPin(int port, int regpin, int subregister, int level) {

  ReadRegisters(port, subregister, 1); 
  
  if (level == 0) {
    CSDataArray[0] &= ~(1 << regpin);
  }
  else {
    CSDataArray[0] |= (1 << regpin);
  }
  
  WriteRegisters(port, subregister, 1);
  
}

void Centipede::pinMode(int pin, int mode) {
  
  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, subregister, mode ^ 1);
  
}

void Centipede::pinPullup(int pin, int mode) {
  
  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, 0x0C + subregister, mode);
  
}


void Centipede::digitalWrite(int pin, int level) {
  
  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  int regpin = pin - ((port << 1) + subregister)*8;

  WriteRegisterPin(port, regpin, 0x12 + subregister, level);
  
}

int Centipede::digitalRead(int pin) {

  int port = pin >> 4;
  int subregister = (pin & 8) >> 3;

  ReadRegisters(port, 0x12 + subregister, 1);

  int returnval = (CSDataArray[0] >> (pin - ((port << 1) + subregister)*8)) & 1;

  return returnval;

}

void Centipede::portMode(int port, int value) {
  
  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;
  
  WriteRegisters(port, 0x00, 2);
  
}

void Centipede::portWrite(int port, int value) {
  
  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;
  
  WriteRegisters(port, 0x12, 2);
  
}

void Centipede::portPullup(int port, int value) {
  
  CSDataArray[0] = value;
  CSDataArray[1] = value>>8;
  
  WriteRegisters(port, 0x0C, 2);
  
}

int Centipede::portRead(int port) {

  ReadRegisters(port, 0x12, 2);

  int receivedval = CSDataArray[0];
  receivedval |= CSDataArray[1] << 8;

  return receivedval;  

}




