/* 
 * A primitive LED driver for the Dragon 12 board (Port B).
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
#ifndef _LED_H_
#define _LED_H_


/* Initialize PORT B */
void initLED(void);

/* write to the LEDs */
void writeLED(char value);

/* read current LED status */
char readLED(void);


#endif _LED_H_
