/*
 *  fastSB.c
 *  
 *
 *  
 *  
 *
 */

#include "fastSB.h"

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

static inline void turnOffPWM(uint8_t timer) __attribute__ ((always_inline));
static inline void turnOffPWM(uint8_t timer)
{
	if (timer == TIMER1A) cbi(TCCR1A, COM1A1);
	if (timer == TIMER1B) cbi(TCCR1A, COM1B1);
	
#if defined(__AVR_ATmega168__)
	if (timer == TIMER0A) cbi(TCCR0A, COM0A1);
	if (timer == TIMER0B) cbi(TCCR0A, COM0B1);
	if (timer == TIMER2A) cbi(TCCR2A, COM2A1);
	if (timer == TIMER2B) cbi(TCCR2A, COM2B1);
#else
	if (timer == TIMER2) cbi(TCCR2, COM21);
#endif
}

void shiftOutHPPM(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, byte val)
{
	uint8_t dport = digitalPinToPort(dataPin);
	uint8_t cport = digitalPinToPort(clockPin);
	if (dport == NOT_A_PIN || cport == NOT_A_PIN ) return;
	uint8_t dmask = digitalPinToBitMask(dataPin);
	uint8_t cmask = digitalPinToBitMask(clockPin);
	volatile uint8_t *dreg = portOutputRegister(dport);
	volatile uint8_t *creg = portOutputRegister(cport);
	uint8_t dtimer = digitalPinToTimer(dataPin);
	uint8_t ctimer = digitalPinToTimer(clockPin);
	if (dtimer != NOT_ON_TIMER) turnOffPWM(dtimer);
	if (ctimer != NOT_ON_TIMER) turnOffPWM(ctimer);
	
	if (bitOrder == LSBFIRST) {
		if (val & B00000001) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00000010) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00000100) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00001000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00010000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00100000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B01000000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B10000000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
	} else {
		if (val & B10000000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B01000000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00100000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00010000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00001000) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00000100) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00000010) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
		if (val & B00000001) *dreg |=  dmask;
		else		     *dreg &= ~dmask;
		*creg |= cmask; *creg &= ~cmask;
	}
}
