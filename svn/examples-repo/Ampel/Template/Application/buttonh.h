/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: buttonh.h 14 2012-10-03 10:17:33Z teamedu1 $
 */
#ifndef _buttonhh
#define _buttonhh

/* These routines return 1 if the "on" or "off" buttons were pressed    */
/* Debouncing is taken care off. The buttons need to be released before */
/* these routines return 1 again.                                       */
/* These routines are not hardware specific.                            */

unsigned char eventOn(void);
unsigned char eventOff(void);

#endif
