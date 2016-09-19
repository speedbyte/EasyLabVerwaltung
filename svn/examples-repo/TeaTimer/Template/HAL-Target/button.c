/*
 * This module handles the lower level of reading the button.
 *
 * Author: Joerg Friedrich
 * Copyright: HS Esslingen, September 2007
 *
 * $Id:$
 * $Rev:$
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 **/


#include "button.h"
#include <mc9s12dp256.h> 
 

int button = NOSW;

void initButtons(void) {

/* .. maybe we need something here, maybe not */
  
}

/*
 * We detect a pressed button via interrupt. We can't detect the release
 * of a button via interrupt, at least not on this board.
 * 
 * But be aware, these buttons bounce badly!
 */
interrupt ?? void isrBUTTON(void)
{
  PIEH = 0x00;         /* Deactivate interrupt while isr is active */
  button =  PTIH & 0x0F;
  PIFH = PIFH | 0x0F;  /* clear interrupt flags */
  
  PIEH = 0x0F;         /* reactivate interrupts */
}


/* It is advised to call this routine regularly (e.g. every 10 ms).
 * Then there should be some debouncing logic added on top of this.
 * The debouncing logic should be part of the application, not the driver,
 * since we want to simulate the debouncing mechanism.
 */
int getButtonPressed(void)
{
    
   return button; 
}


void resetButton(void)
{
  button = NOSW;
}