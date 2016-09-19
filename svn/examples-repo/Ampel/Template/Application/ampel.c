/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author: J. Friedrich
 $Id: ampel.c 14 2012-10-03 10:17:33Z teamedu1 $
 */

#include "ticker.h"
#include "button.h"
#include "hal.h"
#include "states.h"

/* A table with function pointers. Each state is represented by a single function */
/* It must be made sure that the order of the functions here correspond to the    */
/* order of the state enumeration in the states.h header file.                    */

void (*stateTable[])()= {Red, RedYellow, Yellow, YellowB, Green, AllOff, Off };

int main(void) {

	initHardware();
	initStateMachine();

	/* This is the heart of the state machine */
	for (;;) {
		sampleInputs();
		stateTable[getCurrentState()]();
	}
}

