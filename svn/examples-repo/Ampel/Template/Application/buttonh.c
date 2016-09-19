/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: buttonh.c 15 2012-10-03 12:49:01Z teamedu1 $
 */
#include "button.h"
#include "buttonh.h"
#include "ticker.h"

static char onDownLast = 0;
static char offDownLast = 0;

static unsigned long bounceTimerOn = 0;
static unsigned long bounceTimerOff = 0;
static const unsigned int bounceDelay = 4; /* 4 ticks to limit bouncing */

unsigned char eventOn() {
	if ((getTime() - bounceTimerOn) < bounceDelay) {
		return 0; /* silence during bounce delay */
	}

	if (onDown() && (onDownLast == 0)) {
		onDownLast = 1;
		bounceTimerOn = getTime();
		return 1;
	}

	if (onDown() && (onDownLast == 1)) {
		return 0;
	}

	onDownLast = 0;
	return 0;
}

unsigned char eventOff() {
	if ((getTime() - bounceTimerOff) < bounceDelay) {
		return 0; /* silence during bounce delay */
	}
	if (offDown() && (offDownLast == 0)) {
		offDownLast = 1;
		bounceTimerOff = getTime();
		return 1;
	}

	if (offDown() && (offDownLast == 1)) {
		return 0;
	}

	offDownLast = 0;
	return 0;
}
