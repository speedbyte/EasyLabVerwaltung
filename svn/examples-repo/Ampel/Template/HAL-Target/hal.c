/*  
    Real-Time Systems
    (C) 2009 J. Friedrich
    University of Applied Sciences Esslingen

    Author:  J. Friedrich, April 2009  
*/

#include <hidef.h>
#include <mc9s12dp256.h>
#include <stdlib.h>
#include "ticker.h"
#include "button.h"
#include "led.h"

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

/* Initialize the real hardware here */
void initHardware(void) {
	initButton();
	initLed();
	initTicker();
	EnableInterrupts;  
};

/* This we need to get inputs, either from events delivered by interrupts */
/* or polling the hardware, or by reading the input file during simulation */
void sampleInputs(void) {
  
};

/* This is the exit for the simulation, and could possibly put the */
/* real system to sleep.                                           */
void turnMachineOff(void) {
  
};

/* This increments the real-world time on either the hardware or during simulation.  */
/* In hardware, this is driven by a hardware timer interrupt. In the simulation this */
/* is driven by the simulation input file.                                           */
void tick(void) {
  
};

/* As the name says, this is a very low level routine to get the time from the */
/* simulation input file. The real time is to be obtained from the ticker(.h)  */
/* You can replace this with a dummy for the real system.                      */
unsigned long getTimeSimu(void) {
    return 0L;
};

/* Again, two routines solely for simulation. They simulate the two buttons,   */
/* where the values are read from the simulation input file. For the real      */
/* system these would be obtained from button(.h), and you could provide just  */
/* dummies for these routines.                                                 */
char onDownSimu(void) {
    return 0;
};

char offDownSimu(void) {
    return 0;
};


