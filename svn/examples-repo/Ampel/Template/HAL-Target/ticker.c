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
 * Copyright: University of Applied Sciences Esslingen, April 2009
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

static long ticks;
static long timerStart;

/* Interrupt service routine for timer channel 4 */
interrupt void isr_tc4(void);

void (*tickerFunctionPointer)(void) = (void (*)(void)) 0x0000; 

/* Define "magic" numbers */
#define TENMS (1875)                 /* 10 ms */
#define TIMER_ON (0x80)              /* tscr1 value to turn ECT on */
#define TIMER_CH4 (0x10)             /* bit position for channel 4 */
#define TCTL1_CH4 (0x03)             /* Mask corresponds to TCTL1 OM4, OL4 */
#define TCTL1_CH4_TOGGLE (0x01)      /* TCTL1 OM4, OL4 Output toggle */
#define TCTL1_CH4_LOW (0x02)         /* TCTL1 OM4, OL4 Output zero */
#define TCTL1_CH4_DISCONNECT (0x00)	 /* Disconnect channel 4 from output pin */


/* We provide a short period timer, which can be reset using this routine. */
void resetTimer() {
   timerStart = ticks; 
};

/* Get the current value of the timer */
unsigned int getTimerValue() {
   return ticks - timerStart; 
};

/* Get the number of ticks since the system started its operation. */
long getTime() {
  return ticks;
};

/* 
 * Interrupt service routine for timer channel 4 
 *
 */
interrupt 12 void isr_tc4(void) {

	/* increment timer count register (16 bits) */
	/* current count + increment = new count    */
	TC4 = TC4 + TENMS;
	++ticks;
	// if (ticks > 100) {
	//     ticks = 0;
	//   	PORTB = ~PORTB & 0x01;
	// }
	if ((void *) tickerFunctionPointer > NULL) {
	  tickerFunctionPointer();
	}
	/* clear the interrupt: write a 1 to bit 4 */
  TFLG1 = TIMER_CH4;      
}

void callTheTicker() {
  tickerFunctionPointer();
}


/*
 * Initialize the timer 4 hardware and interrupt 
 *
 */
void initTicker(void) {

  tickerFunctionPointer = 0;
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

/* 
 * Register this routine so that it is called
 * by the ticker every 10 ms.
 *
 */
void registerTickRoutine(void (*_functionPointer)(void)){
    tickerFunctionPointer =  _functionPointer;
}


/* 
 * Turn off the timer.
 */
void tickerOff(void) {
    TIE = TIE & ~TIMER_CH4;
}








