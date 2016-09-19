/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: states.h 14 2012-10-03 10:17:33Z teamedu1 $
 */
#ifndef _statesh
#define _statesh

/* All states as an enum */
typedef enum {
	RED = 0, REDYELLOW, YELLOW, YELLOWB, GREEN, ALLOFF, OFF
} states;

/* One function for each state */
void Red(void);
void RedYellow(void);
void Yellow(void);
void YellowB(void);
void Green(void);
void AllOff(void);
void Off(void);

/* Setter and getters for the current state */
states getCurrentState(void);
void setCurrentState(states cs);

/* Setter and getters for the previous state */
/* to detect a state transition              */
states getLastState(void);
void setLastStateState(states cs);

/* Initialization of the state machine, go to initial state */
void initStateMachine(void);
#endif
