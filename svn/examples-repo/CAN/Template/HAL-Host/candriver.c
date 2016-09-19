/* 
 * A primitive CAN driver for the Dragon 12 board.
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
 
#include <stdio.h>      	/* common defines and macros */
 
static unsigned char rdata[8];   /* for data received */
static unsigned char rid[4];
static unsigned char length; 
 
static void CAN0_RECInterruptHandler(void) {

}


void initCAN(void) 
{
/* TODO */
  return;
}




int writeCAN(unsigned char* id, unsigned char* data, unsigned char plength) 
{
	/* TODO */
	
	//if (plength > 7) {
	//  return -1;
	//}
	//
	//if ((CAN0TFLG & 0x07)==0) {
	//  return -1;
	//}
	//
	//CAN0TBSEL_TX0=1;		
	//
	//if (CAN0TBSEL_TX0==1) {
	// 	  CAN0TBSEL=0x01;		   /* Select transmit buffer 1 */
	//}
	//
	//CAN0TXIDR0 = id[0];	     /*                          */
	//CAN0TXIDR1 = id[1];
	//CAN0TXIDR2 = id[2];
	//CAN0TXIDR3 = id[3];
	//CAN0TXDSR0 = data[0];
	//CAN0TXDSR1 = data[1];
	//CAN0TXDSR2 = data[2];
	//CAN0TXDSR3 = data[3];
	//CAN0TXDSR4 = data[4];
	//CAN0TXDSR5 = data[5];
	//CAN0TXDSR6 = data[6];
	//CAN0TXDSR7 = data[7];
	//CAN0TXDLR = plength;		/* Data length register	*/
	//CAN0TXTBPR = 0;			
	//CAN0TFLG = 0x01;		    /* Set transmit flag */
	return 0;	
}
  

  
int readCAN(unsigned char* id, unsigned char* data, unsigned char *plength)
{
 /* 
   char i = 0;
   while (i < length) {
     data[i] = rdata[i];
     ++i;
   }
   *plength = length;
   id[0] = rid[0];
   id[1] = rid[1];
   id[2] = rid[2];
   id[3] = rid[3];*/
   return 0; 
}
	