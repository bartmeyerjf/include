// -----------------------------------------
// LIBRARY ARDUINO (funções do Arduino)
// -----------------------------------------


// -----------------------------------------
// SEÇÃO HEADER (.h)
// -----------------------------------------


// trava de múltiplas inclusões da biblioteca
#ifndef lib_arduino_h
#define lib_arduino_h


#include "avr/io.h"
#include <avr/interrupt.h>
#include "avr8-stub.h"

uint32_t smartDelay(uint8_t index, uint32_t delay_ms);

// Defines
void delayMicroseconds();
typedef uint8_t byte;


#define bitSet(p,b)     (p = p|(1<<b))
#define bitClear(p,b)   (p = p&(~(1<<b)))
#define bitToggle(p,b)  (p = p^(1<<b))
#define bitRead(p,b)    ((p&(1<<b))>>b)


// protótipos das funções
extern "C" { void delay_1_ms(); }
void setup();
int main();
void loop();


// -----------------------------------------
// SEÇÃO DE IMPLEMENTAÇÃO (.c)
// -----------------------------------------

volatile uint32_t global_time_ms = 0;    // current time in ms

// -----------------------------------------
void delay(uint16_t ms) 
{
    while(ms>0) {
        delay_1_ms();
        ms--;
    }
}

// -----------------------------------------
void delayMicroseconds(unsigned int us) // 16 bit unsigned
{
    // for the 16 MHz clock on most Arduino boards
    if (us <= 1) return; //  = 3 cycles, (4 when true)
    us <<= 2; // x4 us, = 4 cycles
    us -= 5; // = 2 cycles,
    // busy wait
    __asm__ __volatile__(
        "1: sbiw %0,1" "\n\t" // 2 cycles
        "brne 1b" : "=w" (us) : "0" (us) // 2 cycles
    );
}


// -----------------------------------------

// this function recieves an index and time for delay
// it retuns the remaining time or 0 and resets timer
/*
//example call: delay number 3 for 250 ms:
if(smartDelay(3, 250) == 0 )
{
    // code to be executed after delay
}
*/
uint32_t smartDelay(uint8_t index, uint32_t delay_ms) 
{
    static uint32_t endTime[256] = {0};
    if(global_time_ms <= endTime[index])
    {
        return  endTime[index] - global_time_ms;
    }
    else
    {
        endTime[index] = global_time_ms + delay_ms;
        return 0;
    }
}

// -----------------------------------------

#endif
