/*
 * A simple program to demonstrate usage of the 10 ms ticker
 * routines.
 *
 * IDE: Metrowerks Codewarrior
 *
 * Author:    Joerg Friedrich
 * Copyright: FHT Esslingen, March 2006
 *
 * $Id:$
 * $Rev:$
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 */

#include <hidef.h>           /* some macros and defines        */
#include <mc9s12dp256.h>     /* processor specific definitions */
#include "ticker.h"

void tickRoutine(void);

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

static unsigned long cc = 0;

void main(void) {  
  
  EnableInterrupts;  /* We need this for the debugger */
  
  DDRB = 0xff;
  
  PORTB = 0x00;


	initTicker();
	registerTickRoutine(&tickRoutine);
	
	for(;;) {
	
	}
}


void tickRoutine(void) {
	 ++cc;
	 if (cc > 100) {
	  cc = 0;
	  PORTB = ~PORTB & 0x01;
	 }
  
}
