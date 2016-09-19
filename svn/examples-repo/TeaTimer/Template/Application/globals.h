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

#ifndef _GLOBALS
#define _GLOBALS

/* Place your getter and setter methods for global variables here */

#ifdef __cplusplus
extern "C" {
#endif

int  getSecond(void);				
void setSecond(int s);			
int  getPre_Minute(void);
void setPre_Minute(int m); 
int  getPre_Second(void);
void setPre_Second(int s);
int  getPreset(void);

/* You may need others, and you may need more */

#ifdef __cplusplus
}
#endif

#endif