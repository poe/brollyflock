//Matt G.
//onion@doorcreekorchard.com
//July 2008
//sendPacket code heavily heavily based (mainly copied and pasted) 
//from macetech example 
#include "ShiftBrite.h"


//====Public
//==Constructors
ShiftBrite::ShiftBrite(int dp, int lp, int ep, int cp)
{
	datapin=dp;
	latchpin=lp;
	enablepin=ep;
	clockpin=cp;
	initPins();
}


ShiftBrite::ShiftBrite(int cp)
{
	clockpin=cp;
	enablepin=cp+1;
	latchpin=cp+2;
	datapin=cp+3;
	initPins();
}

//==
void ShiftBrite::setPower(int r, int g, int b)
{
	sendPacket(B01,r,g,b); //B01 sets the mode to write to the current registers
}

void ShiftBrite::setPower(int p)
{
	sendPacket(B01,p,p,p);
}

void ShiftBrite::setColor(int r, int g, int b)
{
	sendPacket(B00,r,g,b); //B00 sets the mode to write to the PWM registers
}
#if _5BIT_SB
void ShiftBrite::setColor5b( byte r, byte g, byte b)
{
	setColor(SB_5bLUT_basic[0][r],SB_5bLUT_basic[1][g],SB_5bLUT_basic[2][b]);
}

void ShiftBrite::setColor5b(int val)
{
	setColor5b((val >>10) & 0x1F,(val >> 5) & 0x1F,val & 0x1F);
}
#endif
//============


//====Private
void ShiftBrite::initPins()
{
	pinMode(datapin, OUTPUT);
	pinMode(latchpin, OUTPUT);
	pinMode(enablepin, OUTPUT);
	pinMode(clockpin, OUTPUT);
	fastWrite(latchpin, LOW);
	fastWrite(enablepin, LOW);
}

void ShiftBrite::sendPacket(int mode, int r, int g, int b) 
{
	unsigned long SB_CommandPacket;
	
	SB_CommandPacket = mode & B11;
	SB_CommandPacket = (SB_CommandPacket << 10)  | (b & 1023);
	SB_CommandPacket = (SB_CommandPacket << 10)  | (r & 1023);
	SB_CommandPacket = (SB_CommandPacket << 10)  | (g & 1023);
	
	shiftOutHPPM(datapin, clockpin, MSBFIRST, SB_CommandPacket >> 24);
	shiftOutHPPM(datapin, clockpin, MSBFIRST, SB_CommandPacket >> 16);
	shiftOutHPPM(datapin, clockpin, MSBFIRST, SB_CommandPacket >> 8);
	shiftOutHPPM(datapin, clockpin, MSBFIRST, SB_CommandPacket);
	
	delay(1); // adjustment may be necessary depending on chain length
	fastWrite(latchpin,HIGH); // latch data into registers
	delay(5); // adjustment may be necessary depending on chain length
	fastWrite(latchpin,LOW);
}
