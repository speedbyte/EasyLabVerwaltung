/* 
 * A primitive ADC driver for the Dragon 12 board.
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
#ifndef _ADC_H_
#define _ADC_H_


/* get the ADC0 data */
unsigned int getADC0_Data(void);


/* Initialize ADC0 */
void initADC0(void);


#endif _ADC_H_
