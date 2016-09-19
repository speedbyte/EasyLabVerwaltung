/* 
 * A primitive LED driver for the Dragon 12 board.
 *
 * Author: Joerg Friedrich
 * Copyright: HS Esslingen, November 2008
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 * $Id:$
 * $Rev:$
 *
 */

#include <mc9s12dp256.h>        /* derivative information */
#include "led.h"

static char ledValue = 0;

/* Initialize PORT B */
void initLED(void) {
  
  /* set port B as output (LEDs) */
  
  DDRB  = 0xff;       /* Port B is output */
  DDRH = 0x00;
  
  DDRJ = 0xff;	      /* Data Direction Register Port J */
  DDRP = 0xff;
  PTP = 0xFF;
  PTJ_PTJ1 	  = 0;    /* Turn On the LED line */

  /* allow all interrupts to take place */
  asm cli  
  
};

/* write to the LEDs */
void writeLED(char value) {
  ledValue = value;
  PORTB = ledValue;
};

/* read current LED status */
char readLED(void) {
  return ledValue;
};

