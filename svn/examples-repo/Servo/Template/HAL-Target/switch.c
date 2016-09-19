#include "hal.h"

void openSwitch(void) {
    
  DDRH = 0x00;       /* We only want to beep when key is pressed */
  PIEH = 0x00;       /* disable port H interrupts, just to make sure */

}


/* 
 * Read port H switch 1 (bit 0) (switch PH0 on the board).
 * Return 1 if ON, 0 if OFF
 */
int getSwitch(void) {
    return PTIH & 0x01; /* read port H for On/Off switch */
}

