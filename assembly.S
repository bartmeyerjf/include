
; -----------------------------------------
;   Programa em Assembly
; -----------------------------------------

#define __SFR_OFFSET 0

; Nesse arquivo são definidos todos os
; registradores do ATMega
#include "avr/io.h"

.global configPortB
.global countUp
.global countDown
.global piscaLeds
.global sequencialLeds
.global delay_1_ms
.global delay_n_ms

; -----------------------------------------

configPortB:
        ldi     r16,0b00111100  ; r16 = 0b00111100 (bits 5..2count)
        out     DDRB,r16        ; r16 -> DDRB: Configura PB5..PB2 como saídas (LEDs)
        ret

; -----------------------------------------
; A count é count registrador R16


countUp:
L1a:    ldi     r16,0b00000000    ; R16 = 0
L1b:    inc     r16         ; R16+1 -> R16
        ; rjmp delay_1_ms
        cpi     r16,9       ; R16 = 9? (compara REG com valor IMEDIATO) (faz uma subtração, descountrecount
        ; se r16=9 -> flag Zero ativa por cpi
        brne    L1b         ; NOT EQUAL (flag Z=0): vai para L1b
        ; Opção 1: permanece no Assembly:
        ; rjmp    L1a         ;  vai para L1a
        ; Opção 2: retorna para a função loop() da linguagem C
        ret                 ; retorna para a função loop()

; -----------------------------------------

countDown:
CDS:    ldi     r16, 0x09   ; R16 <- 9
CDL:    dec     r16         ; R16 <- R16 -1 (note: this operation sets the zero flag)
        brne    CDL         ; R16 == 0? NO: go to CDL, YES: continue
        ; rjmp  CDS         ; restarts counting down
        ret                 ; returns to calling point
; -----------------------------------------

delay_1_ms:
        ldi r31, 4000>>8    ; 1 cycle
        ldi r30, 4000&255   ; 1 cycle
loop:   sbiw r30, 1         ; 4000*2 cycles
        brne loop           ; 3999*2+1 cycles
        ret

; ------------------------------

delay_n_ms:
; generates a delay for the time set in register r20 (in milliseconds)
        call delay_1_ms
        dec r20
        brne delay_n_ms
        ret

piscaLeds:
        
        ldi r16, 0b00000000     ; load value on register (leds on)
        out PORTB, r16          ; set port b
        ldi r20, 250            ; load delay value on register (250 ms)
        call delay_n_ms         ; delay 

        ldi r16, 0b00111100     ; load value on register (leds off)
        out PORTB, r16          ; set port b
        ldi r20, 250            ; load delay value on register (250 ms)
        call delay_n_ms         ; delay

        rjmp piscaLeds          ; loop back to start


sequencialLeds:

        ldi r16, 0b11111011     ; load value on register
SL:     out PORTB, r16          ; set port b
        ldi r20, 150            ; load delay value on register (150 ms)
        call delay_n_ms         ; delay 
        sec                     ; set carry
        rol r16                 ; rotate left
        sbrc r16, 5             ; skip if bit 5 == 0
        rjmp SL                 ; jump to SL

SR:     out PORTB, r16          ; set port b
        ldi r20, 150            ; load delay value on register (150 ms)
        call delay_n_ms         ; delay 
        sec                     ; set carry
        ror r16                 ; rotate right
        sbrc r16, 2             ; skip if bit 2 == 0
        rjmp SR                 ; jump to SR
        ;rjmp SL                 ; jump to SL        

; -----------------------------------------
; Observações:
; load immediate (ldi) só é possível nos registradores R16..R31
; Para poder usar os registradores R0..R15, é preciso fazer
; MOV entre registradores. Por exemplo, para colocar o valor
; 7 no registrador R0, tem que fazer em duacount:
;       ldi     r16,7   ; R16 = 7
;       mov     r0,r16  ; R16 -> R0
