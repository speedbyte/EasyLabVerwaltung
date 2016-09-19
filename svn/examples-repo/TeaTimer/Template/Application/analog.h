/*
 * Get seconds from AD converter AD7
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

#include "globals.h"

#ifndef _ANALOG
#define _ANALOG

#ifdef __cplusplus
extern "C" {
#endif

/* get the seconds */
unsigned char getSecondsFromAD(void);


/*
 * Run this before doing anything with the AD converter. 
 */
void adcInit(void);

/*
 * Get the last measured value from the AD converter
 *
 */
unsigned int getValAD(void);

#ifdef __cplusplus
}
#endif

#endif