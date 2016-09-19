/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich

 $Id:$
 */
#ifndef _buttonh
#define _buttonh

/* Initialize the button hardware */
void initButton(void);

/* Low level routines which detect if the "on" or "off" buttons are pressed. */
/* There is no need for debouncing, this is handled elsewhere.    */
char onDown(void);
char offDown(void);

#endif
