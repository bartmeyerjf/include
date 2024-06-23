
// Finite State Machine

// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


#include <avr/io.h>         // define os nomes dos registradores
#include "lib_arduino.h"    // define bitSet, Clear, Toggle, Read e delay
#include "lib_pinIO_MEGA.h"  // define funções configPin; pinSet, Clear, Toggle,Read
#include "lib_shieldMF.h"   // configura o shield: LEDS, DISPLAY 7 SEG, BOTÕES etc
// #include "lib_timer0.h"     // configurar o timer 0
#include "lib_timer2.h"     // configurar o timer 2

void write595(uint8_t displaySet, uint8_t segmentSet);
void displayTest(uint8_t displaySet, uint8_t segmentSet);
void task_sweep();
void timerPause();
void timerReset();

// protótipos das funções

// [====================================================]
// [                 IMPLEMENTATION (.c)                ]
// [====================================================]

uint8_t decode7seg[] = 
{ 
    0b00000011, // 0
    0b10011111, // 1
    0b00100101, // 2
    0b00001101, // 3
    0b10011001, // 4
    0b01001001, // 5
    0b01000001, // 6
    0b00011111, // 7
    0b00000001, // 8
    0b00001001, // 9
    0b00010001, // A
    0b11000001, // b
    0b11100101, // c
    0b10000101, // d
    0b01100001, // E
    0b01110001, // F
    0b11111111  // 16: turn off 
};

// ------------------------------------------------------
ISR(TIMER0_OVF_vect) {
    T2_clearOverflowFlag(); // zera a flag de overflow
    global_time_ms++;
    task_sweep();
}

// ------------------------------------------------------
volatile uint8_t displaySet, segmentSet;

void write595(uint8_t displaySet, uint8_t segmentSet) 
{
    volatile uint16_t temp;
    temp = (displaySet<<8) | (segmentSet);  // merge 2 bytes into one word
    for(uint8_t i=0; i<=15; i++) {
        if (temp & 0b1) { pinSet(SDI); }    // use mask to separate LSB
        else            { pinClear(SDI); }
        pinSet(SHCLOCK); pinClear(SHCLOCK); // shift clock pulse
        temp = temp >> 1;
    }
    pinSet(LTCLOCK); pinClear(LTCLOCK);     // latch clock pulse
}

// ------------------------------------------------------
volatile uint8_t displayValue[4] = {0};

void task_sweep() 
{
    volatile static uint8_t displayOn = {0};
    switch(displayOn) 
    {
        case 1: 
            displayOn = 2;
            write595(0b00100000, decode7seg[displayValue[1]]);
            break;
        case 2: 
            displayOn = 3;
            write595(0b01000000, decode7seg[displayValue[2]]);
            break;
        case 3: 
            displayOn = 0;
            write595(0b10000000, decode7seg[displayValue[3]]);
            break;
        default: 
            displayOn = 1;
            write595(0b00010000, decode7seg[displayValue[0]]);
            break;
    }

}

// ------------------------------------------------------
volatile uint8_t S1, S2;

void stateMachine()
{
    volatile static uint8_t state = {1};

    switch (state)
    {
        case 1:     // read event signals
            S1 = !pinRead(SW1);
            S2 = !pinRead(SW2);
            if(S1 == 1) { state = 2; } // sensor 1 active => state 2
            if(S2 == 1) { state = 4; } // sensor 2 active => state 4
        break;
        case 2:     // 
            S1 = !pinRead(SW1);
            S2 = !pinRead(SW2);
            if(S1 == 0) { state = 1; } // sensor 1 active => state 2
            if(S2 == 1) { state = 3; } // sensor 2 active => state 4
        break;
        case 3:     //
            S1 = !pinRead(SW1);
            S2 = !pinRead(SW2);
            if(S1 == 0) { state = 4; } // sensor 1 active => state 2
            if(S2 == 0) { state = 2; } // sensor 2 active => state 4
        break;
        default:    //
            S1 = !pinRead(SW1);
            S2 = !pinRead(SW2);
            if(S1 == 1) { state = 3; } // sensor 1 active => state 2
            if(S2 == 0) { state = 1; } // sensor 2 active => state 4
        break;
    }
    displayValue[0] = state;
    return;
}

// ------------------------------------------------------
void setup() 
{
    cli();                  // global interrupt disable 
    setupShieldMF();
    setupTimer2();
    T2_enableInterruptOV();  // interrupt enable overflow timer 2
    sei();                  // global interrupt enable 
}

// ------------------------------------------------------
void loop() 
{
    stateMachine();
}

