#include <pins_arduino.h>
#include <binary.h>

#define LSBFIRST 0//from wiring.h
#define MSBFIRST 1//from wiring.h
typedef uint8_t byte; //from wiring.h
//credit of the following code goes to mem on the arduino board (for fastWrite)
//and to MartinFick (all the shiftOut stuff)



//fastWrite()
// the following macro sets a digital pin high or low, pin must be between 0 and 13 inclusive
// usage: fastWrite(2,HIGH); fastWrite(13,LOW);
#define fastWrite(_pin_, _state_) ( _pin_ < 8 ? (_state_ ?  PORTD |= 1 << _pin_ : PORTD &= ~(1 << _pin_ )) : (_state_ ?  PORTB |= 1 << (_pin_ -8) : PORTB &= ~(1 << (_pin_ -8)  )))
// the macro sets or clears the appropriate bit in port D if the pin is less than 8 or port B if between 8 and 13



void shiftOutHPPM(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, byte val);
