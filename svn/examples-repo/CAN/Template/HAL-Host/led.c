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

#include <stdio.h>

static char ledValue = 0;

/* Initialize PORT B */
void initLED(void) {
  
  /* we don't have to do anything here... */
  
};

/* write to the LEDs */
void writeLED(char value) {
  ledValue = value;
  printf("LED = %#2x\n", ledValue);
};

/* read current LED status */
char readLED(void) {
  return ledValue;
};

