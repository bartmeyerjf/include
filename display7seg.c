
// ------------------------------------------------------
// 7 segments driver
// ------------------------------------------------------


// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


#include <avr/io.h>         // define os nomes dos registradores
#include "lib_arduino.h"    // define bitSet, Clear, Toggle, Read e delay
#include "lib_pinIO_UNO.h"  // define funções configPin; pinSet, Clear, Toggle,Read
#include "lib_shieldMF.h"   // configura o shield: LEDS, DISPLAY 7 SEG, BOTÕES etc
#include "lib_timer0.h"     // configurar o timer 0
// #include "lib_timer2.h"     // configurar o timer 2

// protótipos das funções
void write595(uint8_t displaySet, uint8_t segmentSet);
void displayTest(uint8_t displaySet, uint8_t segmentSet);
void task_sweep();
void timerPause();
void timerReset();

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
volatile uint8_t timerFlag = {1};
// timerFlag == 0 => run timer

ISR(TIMER0_OVF_vect) {
    bitSet(TIFR0,TOV0); // zera a flag de overflow
    if(timerFlag == 0)
    { global_time_ms++; }
    task_sweep();
}

// ------------------------------------------------------
volatile uint8_t displaySet, segmentSet;

void write595(uint8_t displaySet, uint8_t segmentSet) 
{
    volatile uint16_t temp;
    temp = (displaySet<<8) | (segmentSet);  // merge 2 bytes into one word
    for(uint8_t i=0; i<=15; i++) 
    {
        if (temp & 0b1) { pinSet(SDI); }    // use mask to separate LSB
        else            { pinClear(SDI); }
        pinSet(SHCLOCK); pinClear(SHCLOCK); // shift clock pulse
        temp = temp >> 1;
    }
    pinSet(LTCLOCK); pinClear(LTCLOCK);     // latch clock pulse
}

// ------------------------------------------------------
void countUp() 
{
    for (uint8_t i=0; i<=15; i++) 
    {
        write595(0b00010000, decode7seg[i]);
        delay(1000);
    }
}

// ------------------------------------------------------
#define tempo 500

void testeVarredura() {
    write595(0b10000000, decode7seg[8]); delay(tempo);
    write595(0b01000000, decode7seg[8]); delay(tempo);
    write595(0b00100000, decode7seg[8]); delay(tempo);
    write595(0b00010000, decode7seg[8]); delay(tempo);
}

// ------------------------------------------------------
volatile uint8_t displayValue[4];

void task_sweep() 
{
    volatile static uint8_t displayOn = {0};
    volatile static uint8_t count;
    count --;
    if(count == 0) 
    {
        count = 5;
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

}

// ------------------------------------------------------

void timerPause()
{
    if(timerFlag == 0)
    { timerFlag = 1; }
    else
    { timerFlag = 0; }
}


void timerReset()
{
    for(uint8_t i=0; i<=3; i++) 
    {   displayValue[i] = 0;    }
    timerFlag = 1;
}

// ------------------------------------------------------
void displayTest(uint8_t displaySet, uint8_t segmentSet)
{
    volatile uint16_t data;

    data = (displaySet << 8) || segmentSet;

    for(uint8_t i = 0; i<=15; i++)
    {
        if(data & 0b1) { pinSet(SDI); }
        else           { pinClear(SDI); }
        pinSet(SHCLOCK);
        pinClear(SHCLOCK);
        data = data >> 1;
    }

    pinSet(LTCLOCK); pinClear(LTCLOCK);
}

// ------------------------------------------------------
void timerDisplayHex()
{
    if(smartDelay(1, 100) == 0)
    {
        displayValue[0]++;
        for(uint8_t i=0; i<=3; i++) 
        {
            if(displayValue[i] == 0)
            {
                displayValue[i+1]++;
            }    
        }
    }
    return;
}

// ------------------------------------------------------
void timerDisplay()
{
    if(timerFlag != 0)
    {   return; }
    else 
    if(smartDelay(1, 100) == 0)
    {
        displayValue[0]++;
        if(displayValue[0] >= 10)
        {
            displayValue[0] = 0;
            displayValue[1]++;
            if(displayValue[1] >= 10)
            {
                displayValue[1] = 0;
                displayValue[2]++;
                if(displayValue[2] >= 10)
                {
                    displayValue[2] = 0;
                    displayValue[3]++;
                    if(displayValue[3] >= 10)
                    {
                        displayValue[3] = 0;
                    }
                }
            }
        }
    }
    return;
}

// ------------------------------------------------------
void setup() {
    cli();                  // global interrupt disable 
    setupShieldMF();
    setupTimer0();
    bitSet(TIMSK0, TOIE0);  // interrupt enable overflow timer 0
    sei();                  // global interrupt enable 

}

// ------------------------------------------------------
void loop() {
    // testeDisplays();
    // write595(0b11000000, decod7seg[7]);
    // while(1) {} // halt
    // countUp();
    // testeVarredura();
    // task_sweep();
    timerDisplay();
    if(readSW1()) { timerPause(); }
    if(readSW2()) { timerReset(); }
}

