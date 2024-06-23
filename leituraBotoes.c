// ------------------------------------------------------
// Programa leitura de botões
// ------------------------------------------------------


// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


// #include <Arduino.h>     // incluir somente se necessário
#include "lib_arduino.h"    // define bitSet,Clear,Toggle,Read e delay
#include "lib_pinIO_Uno.h"  // define funções configPin; pinSet,Clear,Toggle,Read
#include "lib_shieldMF.h"   // configura o shield


// protótipos das funções


// [====================================================]
// [                 IMPLEMENTATION (.c)                ]
// [====================================================]


void acendeLeds() {
    pinClear(LED1);
    pinClear(LED2);
    pinClear(LED3);
    pinClear(LED4);
}


void apagaLeds() {
    pinSet(LED1);
    pinSet(LED2);
    pinSet(LED3);
    pinSet(LED4);
}


void trocaLeds() {
    pinToggle(LED1);
    pinToggle(LED2);
    pinToggle(LED3);
    pinToggle(LED4);
}

#define tempoMorto() delay(5)

// ------------------------------------------------------


uint8_t leSW1() {
    static uint8_t BT, BTA, valRetorno;  // BTA precisa ser static para lembrar do seu valor
    valRetorno = 0;
    BT = pinRead(SW1);       // lê o pino
    if( BT != BTA ) {        // borda?
        if( BTA==1 ) {       // borda de descida?
            BTA=0;
            valRetorno = 1;  // indica borda de descida (botão acabou de ser pressionado)
            tempoMorto();
        }
        else {               // borda de subida
            BTA=1;
            tempoMorto();
        }
    }
    return valRetorno;
}

uint8_t leSW2() {
    static uint8_t BT, BTA, valRetorno;  // BTA precisa ser static para lembrar do seu valor
    valRetorno = 0;
    BT = pinRead(SW2);       // lê o pino
    if( BT != BTA ) {        // borda?
        if( BTA==1 ) {       // borda de descida?
            BTA=0;
            valRetorno = 1;  // indica borda de descida (botão acabou de ser pressionado)
            tempoMorto();
        }
        else {               // borda de subida
            BTA=1;
            tempoMorto();
        }
    }
    return valRetorno;
}

uint8_t leSW3() {
    static uint8_t BT, BTA, valRetorno;  // BTA precisa ser static para lembrar do seu valor
    valRetorno = 0;
    BT = pinRead(SW3);       // lê o pino
    if( BT != BTA ) {        // borda?
        if( BTA==1 ) {       // borda de descida?
            BTA=0;
            valRetorno = 1;  // indica borda de descida (botão acabou de ser pressionado)
            tempoMorto();
        }
        else {               // borda de subida
            BTA=1;
            tempoMorto();
        }
    }
    return valRetorno;
}

// ------------------------------------------------------

void setup() {
    // DDRB = 0b00111100; // define como saída sinais dos LEDs.
    // DDRC = 0b00000000; // define os botões como entradas
    setupShieldMF();
}

// ------------------------------------------------------

void loop() {
    // leBotao1();
    // leBotaoFiltro();
    if (leSW1() == 1) { pinToggle(LED1); }
    if (leSW2() == 1) { pinToggle(LED2); }
    if (leSW3() == 1) { pinToggle(LED3); }
    // if (leSW1() == 1) { trocaLeds(); }
}
