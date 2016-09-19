/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: ticker.h 14 2012-10-03 10:17:33Z teamedu1 $
 */
#ifndef _tickerh
#define _tickerh

/* Initialize the timer. Doesn't do much in simulation, but initializes */
/* the hardware to provide a tick every 10 ms                           */
void initTicker(void);

/* We provide a short period timer, which can be reset using this routine. */
void resetTimer(void);

/* Get the current value of the timer */
unsigned int getTimerValue(void);

/* Get the number of ticks since the system started its operation. */
long getTime(void);

/* Register a routine so that it is called by the ticker every tick */
void registerTickRoutine(void (*tickFunction)(void));

#endif
