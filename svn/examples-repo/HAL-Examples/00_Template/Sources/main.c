/*
A simple C program to blink LED PB0 on the Dragon12 board.

Author: Joerg Friedrich
Copyright: University of Applied Sciences Esslingen
Last change: 12.2.2008 
*/

#include <hidef.h>           /* Some macros and defines */
#include <mc9s12dp256.h>     /* Processor specific definitions. */

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

void main(void) {

  unsigned long int i;
  const unsigned long int delay = 400000;
  
  EnableInterrupts;  // This we need for the debugger
  
 
  // Configure Port B as output
  DDRB        = 0xFF; // Data Direction Register Port B

  
  // Turn LED PB0 on and off
  PORTB = 0x01;

  for(;;) {
  	PORTB = ~PORTB & 0x01;
    for (i=0; i < delay; ++i) {
		 /* do nothing */
    }
  }
 
}
