// ------------------------------------------------------
// Biblioteca do Conversor AD
// ------------------------------------------------------


// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


#ifndef lib_adc_h
#define lib_adc_h


#include <avr/io.h>         // define os nomes dos registradores
#include "lib_arduino.h"    // define bitClear etc


#define ad_voltageReference 1 // 0=external AREF, 1=AVcc interno, 3=Vref interno 1.1V
#define ad_alinment 0 //0=direita, 1=esquerda
#define ad_mux 0 // 0=canal 0, 1=canal 1, ... 8=canal 8, 14=1.1V, 15=GND
#define ad_enable 1 // 0=disabled, 1=enabled
#define ad_autoTrigger 0 // 0=disabled, 1=auto trigger
#define ad_interrupt 0 // 0=disabled, 1=enabled
#define ad_prescaler 7 // 0=div 2, 1=div 2, 2=div 4, 3=div 8, 4=div 16, 5=div 32, 6=div 64, 7=div 128
#define ad_operationMode 0 // 0=free running, 1=....


// [====================================================]
// [                 IMPLEMENTATION (.c)                ]
// [====================================================]


#define ad_selectChannel(n) ADMUX=((ADMUX&0b11110000)|n)
#define ad_start() bitSet(ADCSRA,6)
#define ad_testEndOfConversion() bitRead(ADCSRA,4)
#define ad_clearEOCflag() bitSet(ADCSRA,4)


void setupADC() {
    ADMUX  = (ad_voltageReference<<6) | (ad_alinment<<5) | (ad_mux);
    ADCSRA = (ad_enable<<7) | (ad_autoTrigger<<5) | (ad_interrupt<<3) | (ad_prescaler);
    ADCSRB = (ad_operationMode);
    DIDR0  = 0b00000001; // desativa o buffer digital do canal 0
    bitClear(PRR0,PRADC); // liga a energia do conversor AD
}


#endif // finaliza lib_adc_h
