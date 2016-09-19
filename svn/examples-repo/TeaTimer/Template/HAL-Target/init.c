/*
 * Initialize all hardware 
 *
 * Author: Joerg Friedrich
 * Copyright: HS Esslingen, September 2007
 *
 * $Id:$
 * $Rev:$
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 */
 
 #include <hidef.h>
 #include <mc9s12dp256.h>
 #include "init.h"
 #include "ticker.h"
 #include "lcddrv.h"
 #include "beeper.h"
 #include "button.h"
 #include "analog.h"
 
 							
 void init(void)
 {
  EnableInterrupts;  /* We need this for the debugger */
  
  
  /* Deaktiviere die 7-Segment Anzeige */
  DDRP = DDRP | 0xf; /* Data Direction Register Port P */
  PTP  = PTP  | 0x0f; /* Schalte alle vier Segmente aus */


  /* Aktiviere die LEDs */
  DDRJ_DDRJ1 	= 1;	/* Data Direction Register Port J */
  PTJ_PTJ1 	  = 0;  /* Schalte LED-Zeile ein */
    
  /*Schalte Port B als Ausgang */
  DDRB = 0xFF;      /* Data Direction Register Port B */
  
  
  /*Port H einstellen*/
  DDRH = 0x00;       /* We only want to beep when key is pressed */
  PIEH = 0x0F;       /*enable PORT H Bit 0-4 interrupts*/
  
  
  initBeeper();
	initTicker();
	initLcd();
	adcInit();
 
 }