/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: ticker.c 15 2012-10-03 12:49:01Z teamedu1 $
 */
#include <stdio.h>
#include "ticker.h"
#include "hal.h" 

/* We don't have to do anything here, since there is
 * no hardware to initialize.
 */
void initTicker() {

}

static long timerStart = 0;

void resetTimer() {
	timerStart = getTime();
}

unsigned int getTimerValue() {
	return getTime() - timerStart;
}

long getTime() {
	return getTimeSimu();
}

void registerTickRoutine(void (*functionPointer)(void)) {

}
