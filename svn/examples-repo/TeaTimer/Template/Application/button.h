/*
 * Work with buttons 
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


#ifndef _button_
#define _button_

#ifdef __cplusplus
extern "C" {
#endif

/*Defines ffor function getButtonPressed()*/
#define SW2  0x07
#define SW3  0x0B
#define SW4  0x0D
#define SW5  0x0E
#define NOSW 0x0F


void initButtons(void);

/**
 * Returns which button has been pressed. Possible
 * values: SW2, SW3, SW4, SW5
 */
int getButtonPressed(void);


void resetButton(void);

#ifdef __cplusplus
}
#endif

#endif