/*
 * A simple program to demonstrate usage of beeper driver
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

#include <hidef.h>           /* some macros and defines        */
#include <mc9s12dp256.h>     /* processor specific definitions */
#include "beeper.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

/* read port H switch 1 (bit 0) */
int get_switch(void);

void main(void) {

  int isBeeperOn = 0;  
  
  EnableInterrupts;  /* We need this for the debugger */

  DDRH = 0x00;       /* We only want to beep when key is pressed */
  PIEH = 0x00;       /* disable port H interrupts, just to make sure */
  
	initBeeper();
	beeperOn(1000);
	
	for(;;) {
		if(get_switch()) {
		    isBeeperOn = 0;
		    beeperOff();  
    }
    else {
        if (!isBeeperOn) {
          		beeperOn(4000);
		          isBeeperOn = 1;
        }
		}
	}
}


/* 
 * Read port H switch 1 (bit 0) (switch PH0 on the board).
 * Return 1 if ON, 0 if OFF
 */
int get_switch(void) {
    return PTIH & 0x01; /* read port H for On/Off switch */
}