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

#include <stdio.h>        /* derivative information */


/* define global result variable */
static unsigned int  ADC0_Data;

unsigned int getADC0_Data() {
   return ADC0_Data; 
}

/* ******* ADC0 Interrupthandler ************ */
// store conversion result in ADC_Data and restart conversion
static void ADC0_Interrupthandler(void) { 
  
  ///* return value in global variable 'ADC0_Data' */
  //ADC0_Data = ATD0DR0; 
  //ATD0CTL5 = 0x87;         // start sequence, channel AN07, result right-aligned

}




//******** ADC_Init *************** 
// Initialize ADC
void initADC0(void){

  //ATD0CTL2 = 0x82; // enable ADC
  //// bit 7 ADPU=1 enable
  //// bit 6 AFFC=0 ATD Fast Flag Clear All
  //// bit 5 AWAI=0 ATD Power Down in Wait Mode
  //// bit 4 ETRIGLE=0 External Trigger Level/Edge Control
  //// bit 3 ETRIGP=0 External Trigger Polarity
  //// bit 2 ETRIGE=0 External Trigger Mode Enable
  //// bit 1 ASCIE=0 ATD Sequence Complete Interrupt Enable
  //// bit 0 ASCIF=0 ATD Sequence Complete Interrupt Flag
  //
  //ATD0CTL4 = 0x05; // enable ADC
  //// bit 7 SRES8=0 A/D Resolution Select
  ////             1 = 8 bit resolution
  ////             0 = 10 bit resolution
  //// bit 6 SMP1=0 Sample Time Select 
  //// bit 5 SMP0=0 2 clock period
  //// bit 4 PRS4=0 ATD Clock Prescaler divide by 12
  //// bit 3 PRS3=0 ATD Clock Prescaler
  //// bit 2 PRS2=1 ATD Clock Prescaler
  //// bit 1 PRS1=0 ATD Clock Prescaler
  //// bit 0 PRS0=1 ATD Clock Prescaler
  //
  ///* clear global return variable */
  //ADC0_Data = 0;

  ///* start conversion */
  //ATD0CTL5 = 0x87;         // start sequence, channel AN07, result right-aligned
  
}
