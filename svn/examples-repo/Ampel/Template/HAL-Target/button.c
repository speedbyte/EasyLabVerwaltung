/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, October 2012
    
    $Id:$  
*/
#include "button.h"
#include "hal.h"
#include <mc9s12dp256.h>

void initButton() {
   DDRH = 0x00;
}

char onDown() {
	if (PTH & 0x01) {
	/* if (~PTH & 0x01) { */ /* for real hardware inverted */	
	  return 1;
	} 
	else {
	  return 0;  
	}
}

char offDown() {
	if (PTH & 0x02) {
	/* if (~PTH & 0x02) { */ /* for real hardware inverted */

	  return 1;
	} 
	else {
	  return 0;  
	}
}

