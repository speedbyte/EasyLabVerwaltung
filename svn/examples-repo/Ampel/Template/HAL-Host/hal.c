/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: hal.c 14 2012-10-03 10:17:33Z teamedu1 $
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hal.h"
#include "button.h"
#include "led.h"
#include "ticker.h"

#define BUFFERSIZE 132
static long time = 0;
static int remainingTicks = 0;
static long onDownTime = 0;
static long offDownTime = 0;
static int repeatCount = 0;

void initHardware() {
	initButton();
	initLed();
	initTicker();
}

char onDownSimu() {
	if (time == 0 || time > onDownTime) {
		return 0;
	} else {
		return 1;
	}
}

char offDownSimu() {
	if (time == 0 || time > offDownTime) {
		return 0;
	} else {
		return 1;
	}
}

void tick(void) {
	time = time + 1;
	--remainingTicks;
}

long getTimeSimu() {
	return time;
}

void sampleInputs() {
	char line[BUFFERSIZE];
	char *tailptr;
	char *dum;

	/* Make sure that the state machine is called a number of times */
	/* before a new tick is permitted to avoid one off effects      */
	if (repeatCount < 2) {
		++repeatCount;
		return;
	} else {
		repeatCount = 0;
	}


	if (remainingTicks > 0) {
		tick();
		return;
	}
	if (fgets(line, BUFFERSIZE, stdin) == NULL ) {
		exit(0);
	}

	printf("<< %s",line);  /* Echo the input in the output */

	if (line[0] != '#') {

		/* advance ticker */
		if (line[0] == '+') {
			tailptr = NULL;
			remainingTicks = (int) strtol(line, &tailptr, 0);
			return;
		}

		/* switch "on" pressed */
		if (strstr(line, "on") == line) {
			remainingTicks = 1;
			/* keep switch pressed for so many ticks */
			if ((tailptr = strstr(line, "+")) != NULL ) {
				remainingTicks = (int) strtol(tailptr, &dum, 0);
			}
			onDownTime = time + remainingTicks;
			printf("%ld: on down until %ld\n", time, onDownTime);
		}

		/* switch "off" pressed */
		if (strstr(line, "off") == line) {
			remainingTicks = 1;
			/* keep switch pressed for so many ticks */
			if ((tailptr = strstr(line, "+")) != NULL ) {
				remainingTicks = (int) strtol(tailptr, &dum, 0);
			}
			offDownTime = time + remainingTicks;
			printf("%ld: off down until %ld\n", time, offDownTime);
		}
	}
}

void turnMachineOff() {
	printf("Turning machine off...\n");
	getc(stdin);
	exit(0);
}

