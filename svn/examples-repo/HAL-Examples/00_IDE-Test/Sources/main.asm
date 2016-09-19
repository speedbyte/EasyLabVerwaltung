;***************************************************************
;* Dies ist ein kleines Testprogramm, um die korrekte Instal-  *
;* lation der Metrowerks CodeWarrior Enticklungsumgebung und   *
;* die Funktion des Boards nachzuweisen.                       *
;*																											       *
;* Autor: Joerg Friedrich                                      *
;* Copyright: FHT Esslingen                                    *
;* Letzte Aenderung: 5.9.2005                                  *
;***************************************************************

; Exportierte Symbole
            XDEF Entry, main
            ; wir benutzen 'Entry' als externes Symbol. Damit koennen
            ; wir in der Linker-Kommando-Datei "(Monitor_linker.prm fuer
            ; das Board, Simulator_linker.prm fuer den Simulator) den
            ; Reset-Vektor auf diese Stelle lenken oder dieses kleine
            ; Programm von einem C/C++-Programm aus aufrufen.

; wir lesen die speziellen Register-Definitionen und Makros
; fuer unseren Prozessortyp ein. Sie liegen im Include-Verzeichnis
; der Entwicklungsumgebung.
            INCLUDE 'mc9s12dp256.inc'

; hier kommen Variable und andere Daten hin
MY_EXTENDED_RAM: SECTION
; Momentan stellen wir hier nur einen Platzhalter rein, da wir in 
; diesem Miniprogramm keine Daten benoetigen.
platzhalter ds.b 1


STACK_RAM: SECTION
stack       ds.b 100

; hier kommt der Code hin
MyCode:     SECTION
main:
Entry:									 ; Symbol ist auch in Monitor_linker.prm als
                         ; Reset-Vektor definiert
       CLI               ; Interrupt einstellen
       lds  #stack+$100
       ldaa #$ff
       staa DDRB         ; Data Direction Register B auf Ausgabe stellen
       MOVB #255, DDRP   ; Data Direction Register P auf Ausgabe stellen
       staa PTP          ; alle LEDs ausschalten
  
loop:
       MOVB #1,platzhalter ; jetzt haengen wir den Rechner etwas
       MOVB #$76,PORTB     ; etwas kompliziert auf
       MOVB #%1110, PTP    ;
       jsr  delay
       MOVB #$79, PORTB
       MOVB #%1101, PTP
       jsr  delay       
       MOVB #$38, PORTB
       MOVB #%1011, PTP
       jsr  delay       
       MOVB #$73, PORTB
       MOVB #%0111, PTP
       jsr  delay
       BRA loop          ; Endlosschleife

delay:
       inca
       nop
       nop
       bne delay
       rts