/* 
 * Example program to demonstrate usage of the primitive
 * CAN driver, using the potis to drive the LEDs.
 * Turning the poti changes the number of LEDs lighting up
 * on the partner board.
 *
 * Author: Joerg Friedrich
 * Copyright: HS Esslingen, November 2008
 *
 * License: Gnu Lesser Public License (LGPL)
 *
 * $Id:$
 * $Rev:$
 *
 */
 
#include "adc.h"                
#include "candriver.h"
#include "led.h"

void main(void) {

int  i;
char led;


unsigned char id[4] = {0,0,0,0}; 
unsigned char sdata[8];
unsigned char rdata[8];
unsigned char rid[4];
unsigned char rlength;


  
  id[0]=0x22;  /* Just some value, read from configuration switch in real life! */

  /* initialize Hardware */
  initCAN();    
  initADC0();
  initLED(); 

 
  /* forever */
  for(;;) {
  
    /* determine LED bit pattern */
    for(i=0, led=0x00; i<(getADC0_Data() & 0x3FF); i += 0x3FF/8) 
      {
      
      /* assemble LED bit pattern */
      led = led<<1 | 0x01;
      }

    /* set LED array to new value */
   
    sdata[0]=led;
    writeCAN(id, sdata, 1);
    
    rlength = sizeof(rdata);
    
    while (readCAN(rid, rdata, &rlength)==-1)
      {

      }
    writeLED(rdata[0]);
    
  }
}