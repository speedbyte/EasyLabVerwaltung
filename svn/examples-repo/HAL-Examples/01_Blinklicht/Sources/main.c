/*
Ein einfaches C-Programm, um die LED PB0 auf dem Labor-Board
zum Blinken zu bringen.

Autor: Joerg Friedrich
Copyright: FHT Esslingen
Letzte Aenderung: 5.9.2005 
*/

#include <hidef.h>           /* Einige Makros und Defines */
#include <mc9s12dp256.h>     /* Prozessorspezifischen Defin. */

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

void main(void) {

  unsigned long int i;
  const unsigned long int delay = 400000;
  
  EnableInterrupts;  // Das brauchen wir fuer den Debugger
  
 
  // Deaktiviere die 7-Segment Anzeige
  DDRP = DDRP | 0xf; // Data Direction Register Port P
  PTP  = PTP | 0x0f; // Schalte alle vier Segmente aus


  // Aktiviere die LEDs
  DDRJ_DDRJ1 	= 1;	// Data Direction Register Port J
  PTJ_PTJ1 	  = 0;  // Schalte LED-Zeile ein
    
  // Schalte Port B als Ausgang
  DDRB        = 0xFF; // Data Direction Register Port B

  
  // Schalte LED PB0 ein und aus
  PORTB = 0x01;

  for(;;) {
  	PORTB = ~PORTB & 0x01;
    for (i=0; i < delay; ++i) {
		 /* do nothing */
    }
  }
 
}
