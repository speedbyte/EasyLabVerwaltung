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
 
#include <mc9s12dp256.h>
#include "analog.h"



/* Global variable for measurement value */
static unsigned int ADC_Data =0;

/* Function to retrieve measurement value */ 
unsigned int getValAD(void)
{
  return ADC_Data;
}
 

/* We operate the AD converter continuously in interrupt mode. 
 * The value measured is placed into ADC_Data.
 * Don't forget to install the interrupt vector:
 * -> VECTOR ADDRESS 0xFFD2 ADC_ISR 
 */
interrupt void ADC_ISR(void) 
{
  /* yes, you have to do it ... */   
}




/* Initialize the AD converter here */
void adcInit(void)
{  
 /* give it a try */
}

