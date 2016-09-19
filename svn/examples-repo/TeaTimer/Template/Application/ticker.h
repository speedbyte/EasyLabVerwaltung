/* 
 * This module provides a regular timer tick every 10 ms.
 * A function can be registered with this timer so that it is
 * being called every 10 ms.
 * 
 * This module uses ECT channel 4 for keeping track of time.
 *
 * The bus frequency is currently defined here, but should actually
 * taken from where the clock and reset module is initialized.
 * Since this is done in the debug monitor, we write it out here
 * again.
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
#ifndef _tickerH
#define _tickerH

#define BUSFREQ 24000000

/**
 * Get actual tick count. One tick is 10 ms.
 */
unsigned long getTickCount(void);

/**
 * Reset tick count to 0
 */
void resetTickCount(void);

/* 
 * Initialize the timer hardware and interrupt.
 * Has to be called before the timer can be used.
 *
 */
void initTicker(void);

#endif