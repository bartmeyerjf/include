// ------------------------------------------------------
// Biblioteca do Shield Multifunção
// ------------------------------------------------------


// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


//  PIN   PORT  I/O Description
// ------ ----  --- --------------------
//   8     PB0   O  74HC595-SDI
//   9     PB1   ?  PWM/OC1A (livre)
//  10     PB2   O  led 1
//  11     PB3   O  led 2 / MOSI (SPI)
//  12     PB4   O  led 3 / MISO (SPI)
//  13     PB5   O  led 4 / SCK (SPI)
//  A0,14  PC0   I  Potenciômetro
//  A1,15  PC1   I  BOT1
//  A2,16  PC2   I  BOT2
//  A3,17  PC3   I  BOT3
//  A4,18  PC4   O  A4 (I2C SDA)
//  A5,19  PC5   O  A5 (I2C SCL)
//   0     PD0   ?  APC220-5 (livre)
//   1     PD1   ?  APC220-4 (livre)
//   2     PD2   ?  Header Temp (livre)
//   3     PD3   O  Buzzer
//   4     PD4   O  74HC595-LATCHCLK
//   5     PD5   ?  T1 / OC0B (PWM) (livre)
//   6     PD6   ?  OC0A (PWM) (livre)
//   7     PD7   O  74HC595-SHIFTCLK


#ifndef lib_shieldMF_h       // trava múltiplas inclusões
#define lib_shieldMF_h


#include <avr/io.h>         // define os registradores
#include "lib_arduino.h"    // define bitSet e outras funções de bit
#include "lib_pinIO_MEGA.h"  // mapeamento PORTA/pino funções config


#define LED1 10
#define LED2 11
#define LED3 12
#define LED4 13
#define SW1 ANALOG1
#define SW2 ANALOG2
#define SW3 ANALOG3
#define SDI 8  // serrial data in
#define SHCLOCK 7 // shift clock
#define LTCLOCK 4 // latch clock

// [====================================================]
// [                 IMPLEMENTATION (.c)                ]
// [====================================================]


void setupShieldMF() {
    configPinOutput(LED1);
    configPinOutput(LED2);
    configPinOutput(LED3);
    configPinOutput(LED4);
    configPinInput(SW1);
    configPinInput(SW2);
    configPinInput(SW3);
    configPinOutput(SDI);
    configPinOutput(SHCLOCK);
    configPinOutput(LTCLOCK);
}

#define deadTime() stop_time = global_time_ms + 15
uint8_t readSW1()
{
    volatile static uint8_t SW, SWM, returnValue; // switch, switch memory, return value
    volatile static uint32_t stop_time = {0};
    returnValue = 0;

    if(global_time_ms >= stop_time)
    {
        SW = pinRead(SW1);
        if(SW != SWM)
        {
            if(SWM == 1)
            {
                SWM = 0;
                returnValue = 1;
                deadTime();
            }
            else
            {
                SWM = 1;
                deadTime();
            }
        }
    }
    return returnValue;
}

uint8_t readSW2()
{
    volatile static uint8_t SW, SWM, returnValue; // switch, switch memory, return value
    volatile static uint32_t stop_time = {0};
    returnValue = 0;

    if(global_time_ms >= stop_time)
    {
        SW = pinRead(SW2);
        if(SW != SWM)
        {
            if(SWM == 1)
            {
                SWM = 0;
                returnValue = 1;
                deadTime();
            }
            else
            {
                SWM = 1;
                deadTime();
            }
        }
    }
    return returnValue;
}

uint8_t readSW3()
{
    volatile static uint8_t SW, SWM, returnValue; // switch, switch memory, return value
    volatile static uint32_t stop_time = {0};
    returnValue = 0;

    if(global_time_ms >= stop_time)
    {
        SW = pinRead(SW3);
        if(SW != SWM)
        {
            if(SWM == 1)
            {
                SWM = 0;
                returnValue = 1;
                deadTime();
            }
            else
            {
                SWM = 1;
                deadTime();
            }
        }
    }
    return returnValue;
}

#endif
