/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: led.c 14 2012-10-03 10:17:33Z teamedu1 $
 */
#include "led.h"
#include "ticker.h"
#include <stdio.h>

void initLed() {

}

void setAllOff() {
	printf("%ld: All off\n", getTime());
}

void RedOn() {
	printf("%ld: Red on\n", getTime());
}

void RedYellowOn() {
	printf("%ld: RedYellow on\n", getTime());
}

void GreenOn() {
	printf("%ld: Green on\n", getTime());
}

void YellowOn() {
	printf("%ld: Yellow on\n", getTime());
}

