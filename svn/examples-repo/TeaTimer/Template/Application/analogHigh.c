/*
 * This module reads the last value measured by the AD converter
 * and converts it into seconds (between 0 and 240 seconds, not
 * less, not more). Seconds are only returned in 5 s intervals,
 * e.g. 0, 5, 10, 15, etc.
 *
 * It is recommended to do some low pass filtering here or have
 * a hysteresis, so that the displayed value does not jump back 
 * and forth between values.
 *
 * IDE: Metrowerks Codewarrior
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
 
#include "analog.h"


unsigned char getSecondsFromAD(void)
{
		unsigned int messWert = 0;
		unsigned char seconds = 0;
		/* .... maybe something missing here ... */
    
    messWert = getValAD();
    
    /* .... something definitely missing here ...*/
    
    return seconds;
}



