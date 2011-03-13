#ifndef ShiftBrite_h
#define ShiftBrite_h

#define SB_Ver 1.1

#ifndef _5BIT_SB
#define _5BIT_SB 1 //default include the 5bit part of the library.
#endif

#include "wiring.h"
#include "LUTs_SB.h"
extern "C" {
#include "fastSB.h"
}

class ShiftBrite
{
  private:
	int datapin; //pins the ShiftBrite is connected to
	int latchpin;
	int enablepin;
	int clockpin;
	
	void initPins(); //sets up pins modes, etc.
	void sendPacket(int mode, int r, int g, int b);
  
 public:
    ShiftBrite(int dp, int lp, int ep, int cp);
	ShiftBrite(int cp);
	
	void setPower(int r, int g, int b);
	void setPower(int p);
	
	void setColor(int r, int g, int b);
#if _5BIT_SB
	void setColor5b(byte r, byte g, byte b); //sets a 5 bit color via a LUT
	void setColor5b(int val); //same as above, but from a packed 16 bit word
#endif
};

#endif
