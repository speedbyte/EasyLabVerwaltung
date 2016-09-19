/*
 * This module provides functionality to sound the beeper at
 * a certain frequency on the Dragon21 board from Wytec. It uses
 * the ECT channel 5 for timing the toggle of the speaker.
 *
 * Make sure the interrupt vector routine is properly hooked into
 * the interrupt vector table in file Monitor_linker.prm like this:
 *
 * VECTOR ADDRESS 0xFFE4  isr_tc5
 *
 * IDE used: Metrowerks Codewarrior
 *
 * References:
 *   Dragon12 example program Ex6.asm by Wayne Chu, Wytec Co.
 *   MC9S12DP256B Device User Guide, V02.14, Mar 5 2003, Motorola Inc.
 *   ECT_16B8C Block User Guide, V01.03, Jul 18 2002, Motorola Inc.
 *
 * Author: Joerg Friedrich
 * Copyright: FHT Esslingen, March 2006
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 * $Id:$
 * $Rev:$
 *
 */

#include "beeper.h"

/*
 * Initialize the beeper hardware and interrupt (5)
 *
 */
void openBeeper(void) {
   /* nothing to do, we output to stdout */
}


/*
 * Turn on beeper output.
 * Mask off OM5 OL5 bits, then set to OM5=0, OL5=1
 * Set frequency to desired value (bus clock is 24.0 MHz)
 * Bus clock is determined by crystal (4.0 MHz) and registers
 * at 0x034 and 0x035.
 *
 */
void beeperOn(int freq) {
	printf("Beeper on");
}


/*
 * Turn off beeper output.
 * Mask off OM5 OL5 bits, then set to OM5=1, OL5=0.
 *
 */
void beeperOff(void) {
	printf("Beeper off");
}








