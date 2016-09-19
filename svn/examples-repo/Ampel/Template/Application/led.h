/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: led.h 14 2012-10-03 10:17:33Z teamedu1 $
 */
#ifndef _ledh
#define _ledh

/* These routines handle the LEDs which are used to simulate the */
/* different bulbs of a traffic light.                           */
void initLed(void);
void setAllOff(void);
void RedOn(void);
void RedYellowOn(void);
void GreenOn(void);
void YellowOn(void);

#endif
