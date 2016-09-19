/* 
 * The main for the Tea Timer project. There must be only one main,
 * no copies, no editing when switching between the host and target
 * build process, no defines. This is it, the one and only.
 *
 * This should help you to get started, but you don't have to follow
 * the design idea shown here. You can do it your way, good luck.
 *
 * Author: Joerg Friedrich
 * Copyright: HS Esslingen, February 2008
 *
 * $Id:$
 * $Rev:$
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 */
 
#include "globals.h"
#include "init.h"
#include "ticker.h"
#include "lcddrv.h"
#include "beeper.h"
#include "button.h"
#include "analog.h"


/* An enum for states is always good. You may need some
 * more states, of course...
 */



void main(void) { 

  
  /* First initialize the hardware (or simulation environment)
   */
  init();
  
  /* Put some text to the LCD */
  writeLcd("Preset",getPre_Minute(), getPre_Second(), 1);
  writeLcd("Actual",getPreset(), getSecond(),2);
	
	
	for(;;) {
	  
	   /* 
	    * Call this state machine forever
	    */

	}
}
