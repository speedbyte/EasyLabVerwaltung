/*  
 Real-Time Systems
 (C) J. Friedrich
 University of Applied Sciences Esslingen

 Author:  J. Friedrich
 $Id: hal.h 14 2012-10-03 10:17:33Z teamedu1 $
 */
#ifndef _halh
#define _halh

/* Initialize the real hardware here */
void initHardware(void);

/* This we need to get inputs, either from events delivered by interrupts */
/* or polling the hardware, or by reading the input file during simulation */
void sampleInputs(void);

/* This is the exit for the simulation, and could possibly put the */
/* real system to sleep.                                           */
void turnMachineOff(void);

/* This increments the real-world time on either the hardware or during simulation.  */
/* In hardware, this is driven by a hardware timer interrupt. In the simulation this */
/* is driven by the simulation input file.                                           */
void tick(void);

/* As the name says, this is a very low level routine to get the time from the */
/* simulation input file. The real time is to be obtained from the ticker(.h)  */
/* You can replace this with a dummy for the real system.                      */
long getTimeSimu(void);

/* Again, two routines solely for simulation. They simulate the two buttons,   */
/* where the values are read from the simulation input file. For the real      */
/* system these would be obtained from button(.h), and you could provide just  */
/* dummies for these routines.                                                 */
char onDownSimu(void);
char offDownSimu(void);

/* Some more information on the simulation input file supported here:

 # (as a first character in a line) makes this line a comment
 # all text below has to be left aligned in a line
 +10     advances ticker by 10 ticks
 on      presses "on" button for one tick (at time == 10)
 off     presses "off" button for one tick (at time == 11)
 +5      advances ticker by 5 ticks to 16
 off+10  presses "off" button for 10 ticks (from time 16 until time 26)

 */
#endif
