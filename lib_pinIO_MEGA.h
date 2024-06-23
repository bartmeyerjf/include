// [================================================]
// [                 HEADER (.h)                    ]
// [================================================]


// --------------------------------------------------


#ifndef lib_pinIO_MEGA_h
#define lib_pinIO_MEGA_h


// Includes
#include "lib_arduino.h"


// Functions prototypes
void configPinInput(byte pin);
void configPinInputPullup(byte pin);
void configPinOutput(byte pin);
void pinSet(byte pin);
void pinClear(byte pin);
void pinToggle(byte pin);
byte pinRead(byte pin);


// defines, a more simplified form of pin functions


#define spin(x) pinSet(x)
#define cpin(x) pinClear(x)
#define tpin(x) pinToggle(x)
#define rpin(x) pinRead(x)


// mapping the pin number to its respective port


// [================================================]
// [             IMPLEMENTATION (.c)                ]
// [================================================]


// --------------------------------------------------
// Global variables


// PORTA=0 B=1 C=2 D=3 E=4 F=5 G=6 K=7 L=8
enum pinPortMap_def { PPA, PPB, PPC, PPD, PPE, PPF, PPG, PPH, PPJ, PPK, PPL };


const pinPortMap_def pinPortMap[] = {
    PPE, // 0 - PE0
    PPE, // 1 - PE1
    PPE, // 2 - PE4
    PPE, // 3 - PE5
    PPG, // 4 - PG5
    PPE, // 5 - PE3
    PPH, // 6 - PH3
    PPH, // 7 - PH4


    PPH, // 8 - PH5
    PPH, // 9 - PH6
    PPB, // 10 - PB4
    PPB, // 11 - PB5
    PPB, // 12 - PB6
    PPB, // 13 - PB7


    PPJ, // 14 - PJ1
    PPJ, // 15 - PJ0
    PPH, // 16 - PH1
    PPH, // 17 - PH0
    PPD, // 18 - PD3
    PPD, // 19 - PD2
    PPD, // 20 - PD1
    PPD, // 21 - PD0


    PPA, // 22 - PA0
    PPA, // 23 - PA1
    PPA, // 24 - PA2
    PPA, // 25 - PA3
    PPA, // 26 - PA4
    PPA, // 27 - PA5
    PPA, // 28 - PA6
    PPA, // 29 - PA7
    PPC, // 30 - PC7
    PPC, // 31 - PC6
    PPC, // 32 - PC5
    PPC, // 33 - PC4
    PPC, // 34 - PC3
    PPC, // 35 - PC2
    PPC, // 36 - PC1
    PPC, // 37 - PC0
    PPD, // 38 - PD7
    PPG, // 39 - PG2
    PPG, // 40 - PG1
    PPG, // 41 - PG0
    PPL, // 42 - PL7
    PPL, // 43 - PL6
    PPL, // 44 - PL5
    PPL, // 45 - PL4
    PPL, // 46 - PL3
    PPL, // 47 - PL2
    PPL, // 48 - PL1
    PPL, // 49 - PL0
    PPB, // 50 - PB3
    PPB, // 51 - PB2
    PPB, // 52 - PB1
    PPB, // 53 - PB0


    PPF, // A0,54 - PF0
    PPF, // A1,55 - PF1
    PPF, // A2,56 - PF2
    PPF, // A3,57 - PF3
    PPF, // A4,58 - PF4
    PPF, // A5,59 - PF5
    PPF, // A6,60 - PF6
    PPF, // A7,61 - PF7


    PPK, //  A8,62 - PK0
    PPK, //  A9,63 - PK1
    PPK, // A10,64 - PK2
    PPK, // A11,65 - PK3
    PPK, // A12,66 - PK4
    PPK, // A13,67 - PK5
    PPK, // A14,68 - PK6
    PPK  // A15,69 - PK7
};


// --------------------------------------------------


#define ANALOG0 54
#define ANALOG1 55
#define ANALOG2 56
#define ANALOG3 57
#define ANALOG4 58
#define ANALOG5 59
#define ANALOG6 60
#define ANALOG7 61
#define ANALOG8 62
#define ANALOG9 63
#define ANALOG10 64
#define ANALOG11 65
#define ANALOG12 66
#define ANALOG13 67
#define ANALOG14 68
#define ANALOG15 69


// --------------------------------------------------


const byte pinBitMap[] = {
    0, // 0 - PE0
    1, // 1 - PE1
    4, // 2 - PE4
    5, // 3 - PE5
    5, // 4 - PG5
    3, // 5 - PE3
    3, // 6 - PH3
    4, // 7 - PH4


    5, // 8 - PH5
    6, // 9 - PH6
    4, // 10 - PB4
    5, // 11 - PB5
    6, // 12 - PB6
    7, // 13 - PB7


    1, // 14 - PJ1
    0, // 15 - PJ0
    1, // 16 - PH1
    0, // 17 - PH0
    3, // 18 - PD3
    2, // 19 - PD2
    1, // 20 - PD1
    0, // 21 - PD0


    0, // 22 - PA0
    1, // 23 - PA1
    2, // 24 - PA2
    3, // 25 - PA3
    4, // 26 - PA4
    5, // 27 - PA5
    6, // 28 - PA6
    7, // 29 - PA7
    7, // 30 - PC7
    6, // 31 - PC6
    5, // 32 - PC5
    4, // 33 - PC4
    3, // 34 - PC3
    2, // 35 - PC2
    1, // 36 - PC1
    0, // 37 - PC0
    7, // 38 - PD7
    2, // 39 - PG2
    1, // 40 - PG1
    0, // 41 - PG0
    7, // 42 - PL7
    6, // 43 - PL6
    5, // 44 - PL5
    4, // 45 - PL4
    3, // 46 - PL3
    2, // 47 - PL2
    1, // 48 - PL1
    0, // 49 - PL0
    3, // 50 - PB3
    2, // 51 - PB2
    1, // 52 - PB1
    0, // 53 - PB0


    0, // A0,54 - PF0
    1, // A1,55 - PF1
    2, // A2,56 - PF2
    3, // A3,57 - PF3
    4, // A4,58 - PF4
    5, // A5,59 - PF5
    6, // A6,60 - PF6
    7, // A7,61 - PF7


    0, //  A8,62 - PK0
    1, //  A9,63 - PK1
    2, // A10,64 - PK2
    3, // A11,65 - PK3
    4, // A12,66 - PK4
    5, // A13,67 - PK5
    6, // A14,68 - PK6
    7  // A15,69 - PK7
};


// --------------------------------------------------
// Functions


void configPinInput(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: bitClear(DDRA,bt); bitClear(PORTA,bt); break;
        case PPB: bitClear(DDRB,bt); bitClear(PORTB,bt); break;
        case PPC: bitClear(DDRC,bt); bitClear(PORTC,bt); break;
        case PPD: bitClear(DDRD,bt); bitClear(PORTD,bt); break;
        case PPE: bitClear(DDRE,bt); bitClear(PORTE,bt); break;
        case PPF: bitClear(DDRF,bt); bitClear(PORTF,bt); break;
        case PPG: bitClear(DDRG,bt); bitClear(PORTG,bt); break;
        case PPH: bitClear(DDRH,bt); bitClear(PORTH,bt); break;
        case PPJ: bitClear(DDRJ,bt); bitClear(PORTJ,bt); break;
        case PPK: bitClear(DDRK,bt); bitClear(PORTK,bt); break;
        default:  bitClear(DDRL,bt); bitClear(PORTL,bt); break;
    }
}


// --------------------------------------------------


void configPinInputPullup(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: bitClear(DDRA,bt); bitSet(PORTA,bt); break;
        case PPB: bitClear(DDRB,bt); bitSet(PORTB,bt); break;
        case PPC: bitClear(DDRC,bt); bitSet(PORTC,bt); break;
        case PPD: bitClear(DDRD,bt); bitSet(PORTD,bt); break;
        case PPE: bitClear(DDRE,bt); bitSet(PORTE,bt); break;
        case PPF: bitClear(DDRF,bt); bitSet(PORTF,bt); break;
        case PPG: bitClear(DDRG,bt); bitSet(PORTG,bt); break;
        case PPH: bitClear(DDRH,bt); bitSet(PORTH,bt); break;
        case PPJ: bitClear(DDRJ,bt); bitSet(PORTJ,bt); break;
        case PPK: bitClear(DDRK,bt); bitSet(PORTK,bt); break;
        default:  bitClear(DDRL,bt); bitSet(PORTL,bt); break;
    }
}


// --------------------------------------------------


void configPinOutput(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: bitSet(DDRA,bt); break;
        case PPB: bitSet(DDRB,bt); break;
        case PPC: bitSet(DDRC,bt); break;
        case PPD: bitSet(DDRD,bt); break;
        case PPE: bitSet(DDRE,bt); break;
        case PPF: bitSet(DDRF,bt); break;
        case PPG: bitSet(DDRG,bt); break;
        case PPH: bitSet(DDRH,bt); break;
        case PPJ: bitSet(DDRJ,bt); break;
        case PPK: bitSet(DDRK,bt); break;
        default:  bitSet(DDRL,bt); break;
    }
}


// --------------------------------------------------


void pinSet(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: bitSet(PORTA,bt); break;
        case PPB: bitSet(PORTB,bt); break;
        case PPC: bitSet(PORTC,bt); break;
        case PPD: bitSet(PORTD,bt); break;
        case PPE: bitSet(PORTE,bt); break;
        case PPF: bitSet(PORTF,bt); break;
        case PPG: bitSet(PORTG,bt); break;
        case PPH: bitSet(PORTH,bt); break;
        case PPJ: bitSet(PORTJ,bt); break;
        case PPK: bitSet(PORTK,bt); break;
        default:  bitSet(PORTL,bt); break;
    }
}


// --------------------------------------------------


void pinClear(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: bitClear(PORTA,bt); break;
        case PPB: bitClear(PORTB,bt); break;
        case PPC: bitClear(PORTC,bt); break;
        case PPD: bitClear(PORTD,bt); break;
        case PPE: bitClear(PORTE,bt); break;
        case PPF: bitClear(PORTF,bt); break;
        case PPG: bitClear(PORTG,bt); break;
        case PPH: bitClear(PORTH,bt); break;
        case PPJ: bitClear(PORTJ,bt); break;
        case PPK: bitClear(PORTK,bt); break;
        default:  bitClear(PORTL,bt); break;
    }
}


// --------------------------------------------------


void pinToggle(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: bitToggle(PORTA,bt); break;
        case PPB: bitToggle(PORTB,bt); break;
        case PPC: bitToggle(PORTC,bt); break;
        case PPD: bitToggle(PORTD,bt); break;
        case PPE: bitToggle(PORTE,bt); break;
        case PPF: bitToggle(PORTF,bt); break;
        case PPG: bitToggle(PORTG,bt); break;
        case PPH: bitToggle(PORTH,bt); break;
        case PPJ: bitToggle(PORTJ,bt); break;
        case PPK: bitToggle(PORTK,bt); break;
        default:  bitToggle(PORTL,bt); break;
    }
}


// --------------------------------------------------


byte pinRead(byte pin) {
    pinPortMap_def PP = pinPortMap[pin];
    byte bt = pinBitMap[pin];
    switch(PP) {
        case PPA: return bitRead(PINA,bt); break;
        case PPB: return bitRead(PINB,bt); break;
        case PPC: return bitRead(PINC,bt); break;
        case PPD: return bitRead(PIND,bt); break;
        case PPE: return bitRead(PINE,bt); break;
        case PPF: return bitRead(PINF,bt); break;
        case PPG: return bitRead(PING,bt); break;
        case PPH: return bitRead(PINH,bt); break;
        case PPJ: return bitRead(PINJ,bt); break;
        case PPK: return bitRead(PINK,bt); break;
        default:  return bitRead(PINL,bt); break;
    }
}


#endif
