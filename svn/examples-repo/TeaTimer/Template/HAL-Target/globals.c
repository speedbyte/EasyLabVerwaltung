/*
 * A common place for all global variables
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

#include <stdio.h>
#include "globals.h"

/********************************************************
 * Global variables
 */					
static int minute = 0;     /* actual minute  */
static int second = 0;     /* actual seconds */
static int pre_minute = 0; /* preset minutes */
static int pre_second = 0; /* preset seconds */
static int preset = 0;

/********************************************************
 * Getter and setter methods
 */


int getMinute(void)			   	
{
 return minute;
}

void setMinute(int m)		    
{
 minute = m;
}


int getSecond(void)			  
{
 return second;
}

void setSecond(int s)
{
 second = s;
}

int getPre_Minute(void)
{
 return pre_minute;
}

void setPre_Minute(int m) 
{
 pre_minute = m;
}

int getPre_Second(void)
{
 return pre_second;
}

void setPre_Second(int s)
{
 pre_second = s;
}

int  getPreset(void) {
  return preset;
};
