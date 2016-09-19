/*
 * A simple program to demonstrate usage of the LCD driver
 * routines.
 *
 * IDE: Metrowerks Codewarrior
 *
 * Author: Joerg Friedrich
 * Copyright: FHT Esslingen, March 2006
 *
 * $Id:$
 * $Rev:$
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 */

#include <hidef.h>           /* Some macros and defines        */
#include <mc9s12dp256.h>     /* processor specific definitions */
#include "lcddrv.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"


void main(void) {
 
  
  EnableInterrupts;  /* We need this for the debug monitor */
 
	initLcd();         /* initialize the driver first */
	
	writeLine("First line\0",0);
	writeLine("Second line\0",1);
	
	for(;;) { /* Hang'm up */

	}
}

