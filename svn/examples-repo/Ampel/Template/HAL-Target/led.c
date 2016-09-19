/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/
#include <mc9s12dp256.h>
#include "led.h"

void initLed() {
   DDRJ_DDRJ1 = 1;
   PTJ_PTJ1 = 0;
   DDRB = 0xff;
   PORTB = 0x00;
}

void setAllOff() {
  PORTB = 0x00;
};

void RedOn() {
  PORTB = 0x80;
};

void RedYellowOn() {
  PORTB = 0x80 | 0x40;
};

void GreenOn() {
	PORTB = 0x20;
};

void YellowOn() {
  PORTB = 0x40;
};









