/*
Ein einfaches C-Programm, um die LED PB0 auf dem Labor-Board
zum Blinken zu bringen. Demonstriert Interrupt-Routine in C.

Autor: Joerg Friedrich
Copyright: FHT Esslingen
Letzte Aenderung: 26.9.2005 
*/

#include <hidef.h>           /* Einige Makros und Defines */
#include <mc9s12dp256.h>     /* Prozessorspezifischen Defin. */

#pragma LINK_INFO DERIVATIVE "mc9s12dp256b"

void main(void) {
  
  EnableInterrupts;  // Das brauchen wir fuer den Debugger und RTI
  
 
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
  
  // Stelle Teiler für RTI ein
  RTICTL = 0x7f;
  CRGINT = CRGINT | 0x80;

  for(;;) {
    /* Daeumchen drehen ... */
  }
}


  
interrupt void rtiISR (void) {
    
    
		CRGFLG = CRGFLG | 0x80; /* setze Interrupt-Flag zurueck */
  	PORTB = ~PORTB & 0x01;  /* das war's auch schon */
}