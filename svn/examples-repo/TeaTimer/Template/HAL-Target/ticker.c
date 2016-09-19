/* 
 * This module provides a regular timer tick every 10 ms.
 * A function can be registered with this timer so that it is
 * being called every 10 ms.
 * 
 * This module uses ECT channel 4 for keeping track of time.
 *
 * Make sure the interrupt vector routine is properly hooked into
 * the interrupt vector table in file Monitor_linker.prm like this:
 *
 * VECTOR ADDRESS 0xFFE4  isr_tc4 
 *
 * IDE used: Metrowerks Codewarrior
 *
 * References: 
 *   MC9S12DP256B Device User Guide, V02.14, Mar 5 2003, Motorola Inc.
 *   ECT_16B8C Block User Guide, V01.03, Jul 18 2002, Motorola Inc.
 *
 * Author:    Joerg Friedrich 
 * Copyright: HS Esslingen, September 2007
 *
 * License:   Gnu Lesser Public License (LGPL)
 *
 * $Id:$
 * $Rev:$
 *
 */

#include <mc9s12dp256.h>
#include <stdlib.h>
#include "ticker.h"
#include "globals.h"

static unsigned long ticks;

/* Interrupt service routine for timer channel 4 */
interrupt void isr_tc4(void);
 

/* Define "magic" numbers */
#define TENMS (1875)                 /* 10 ms */
#define TIMER_ON (0x80)              /* tscr1 value to turn ECT on */
#define TIMER_CH4 (0x10)             /* bit position for channel 4 */
#define TCTL1_CH4 (0x03)             /* Mask corresponds to TCTL1 OM4, OL4 */
#define TCTL1_CH4_DISCONNECT (0x00)	 /* Disconnect channel 4 from output pin */


/* 
 * Interrupt service routine for timer channel 4 
 *
 */
interrupt void isr_tc4(void) {

	/* increment timer count register (16 bits) */
	/* current count + increment = new count    */
	TC4 = TC4 + TENMS;
  if (ticks == 2000000) 
  {
	    ticks = 0;
	}
  ticks++; 
	 
	 /*Ausgabe des 10ms Takt auf LED*/
	 PORTB = ~PORTB & 0x01;
	/* clear the interrupt: write a 1 to bit 0 */
  TFLG1 = TIMER_CH4;      
}


/*
 * Get the Ticks
 */
unsigned long getTickCount(void)
{ 
  return ticks;
}


/*
 * reset the tick variable
 */
void resetTickCount(void)
{
  ticks =0;
}



/*
 * Initialize the timer 4 hardware and interrupt 
 *
 */
void initTicker(void) {

  //tickerFunctionPointer = 0;
  ticks = 0;
  /* Timer master ON switch  */
	TSCR1 = TIMER_ON;
	
	/* Set channel 4 in "output compare" mode  */
	TIOS = TIOS | TIMER_CH4; /* bit 4 corresponds to channel 4 */
	
	/* Enable channel 4 interrupt; bit 4 corresponds to channel 4 */
  TIE = TIE | TIMER_CH4;
   
  /* Set timer prescaler (bus clock : prescale factor)        */
  /* In our case: divide by 2^7 = 128. This gives a timer     */
  /* driver frequency of 187500 Hz or 5.3333 us time interval */
  TSCR2 = (TSCR2 & 0xf8) | 0x07;
  
  /* switch timer on */
  TCTL1 = (TCTL1 & ~TCTL1_CH4) | TCTL1_CH4_DISCONNECT;
}


/**
 *Berechnung ob eine Sekunde vergangen, wenn tick&100 == 0
 *und tick > help, dann Rückgabe 1, sonst Rückgabe -1
 *Parameter
 * 1. unsigned long -> aktueller tickcount
 * 2. unsigned long -> tickcount aus dem letzten Schritt 
 *
 */
int secTimer(unsigned long tick, unsigned long help)
{
  if( ( (tick % 100) == 0) && (tick > help) )
  {
    return 1;
  }
  else
  {
    return -1;
  }
  
}







