/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: button.c 14 2012-10-03 10:17:33Z teamedu1 $
 */
#include "button.h"
#include "hal.h"

void initButton() {

}

char onDown() {
	return onDownSimu();
}

char offDown() {
	return offDownSimu();
}
