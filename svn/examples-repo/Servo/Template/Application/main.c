/*
 * A simple program to control a servo.
 *
 * Author: Joerg Friedrich
 * Copyright: HS Esslingen, September 2008
 *
 * $Id:$
 * $Rev:$
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 */

#include "hal.h"             /* different for host and target IDE */
#include "pwm.h"
#include "switch.h"

void main(void) {
 

	int i = -90;
	long j = 0;
	  
  EnableInterrupts;  /* We need this for the debugger */

  openSwitch();
  
	openPWM();
	
	
	positionServo(-90);
	
	while (1) {
	
	   ++i;
	   if (i > 50) i = -50;
	   
	   for (j = 0; j < 10000; ++j) {
	   }
	
	   positionServo(i);

	}
}
