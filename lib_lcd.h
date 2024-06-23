// ------------------------------------------------------
// Biblioteca do display LCD alfanumérico
// ------------------------------------------------------


// [====================================================]
// [                    HEADER (.h)                     ]
// [====================================================]


#ifndef lib_lcd_h       // trava múltiplas inclusões
#define lib_lcd_h


#include <avr/io.h>         // define os registradores
#include "lib_arduino.h"    // define bitSet e outras funções de bit
#include "lib_pinIO_MEGA.h"    // define mapeamento dos pinos


// Definição das conexões do display LCD com os pinos do kit


// GND should be 55, that is not I/O but GND by itself
#define LCDVCC 53
#define LCDVP  51
#define LCDRS  49   // RS: 0=comando, 1=dados
#define LCDRW  47
#define LCDEN  45   // EN: pulso de clock 0 -> 1 -> 0
#define LCD0   43   // D0 (not used in 4-bit data bus)
#define LCD1   41   // D1 (not used in 4-bit data bus)
#define LCD2   39   // D2 (not used in 4-bit data bus)
#define LCD3   37   // D3 (not used in 4-bit data bus)
#define LCD4   35   // D4 / D0 (in 4-bit data bus)
#define LCD5   33   // D5 / D1 (in 4-bit data bus)
#define LCD6   31   // D6 / D2 (in 4-bit data bus)
#define LCD7   29   // D7 / D3 (in 4-bit data bus)
#define TESTPIN 5   // pino usado para teste (no caso verificar o sinal PWM)

#define lcdComando(x) lcdWrite8(0,x)
#define lcdDado(x) lcdWrite8(1,x)
#define lcdClear() lcdWrite8(0,0b00000001); delay(3);
#define lcdCursorOn() lcdComando(0b00001100)
#define lcdCursorOff() lcdComando(0b00001110)
#define lcdCursorBlink() lcdComando(0b00001111)
 
// --------------------------------------------------
// Function prototypes


// --------------------------------------------------


void setupLCD() {
    configPinOutput(LCD0);
    configPinOutput(LCD1);
    configPinOutput(LCD2);
    configPinOutput(LCD3);
    configPinOutput(LCD4);
    configPinOutput(LCD5);
    configPinOutput(LCD6);
    configPinOutput(LCD7);
    configPinOutput(LCDRS);
    configPinOutput(LCDRW);
    configPinOutput(LCDEN);
    configPinOutput(LCDVP);
    configPinOutput(LCDVCC);
    pinSet(LCDVCC);  // Alimentação 5V
    pinClear(LCDVP); // contraste máximo
    pinClear(LCDRS); // RS=0 inicialmente
    pinClear(LCDRW); // coloca em mode de escrita (Write)
    pinClear(LCDEN); // condição inicial do CLOCK
    pinClear(LCD0);  // alguns programadores recomendam...
    pinClear(LCD1);  // deixar esses sinais aterrados
    pinClear(LCD2);
    pinClear(LCD3);
    // T2_interruptEnableCMPA(); // necessário para PWM
    OCR2A = 16; // valor PWM de VP calibrado na função ajustPwmLcd do arquivo lcd.c
}


// --------------------------------------------------
void lcdWrite8(uint8_t RSmode, uint8_t ch) 
{
    if(RSmode) pinSet(LCDRS); else pinClear(LCDRS); // prepara o sinal RS
    if( bitRead(ch,7) ) pinSet(LCD7); else pinClear(LCD7);
    if( bitRead(ch,6) ) pinSet(LCD6); else pinClear(LCD6);
    if( bitRead(ch,5) ) pinSet(LCD5); else pinClear(LCD5);
    if( bitRead(ch,4) ) pinSet(LCD4); else pinClear(LCD4);
    if( bitRead(ch,3) ) pinSet(LCD3); else pinClear(LCD3);
    if( bitRead(ch,2) ) pinSet(LCD2); else pinClear(LCD2);
    if( bitRead(ch,1) ) pinSet(LCD1); else pinClear(LCD1);
    if( bitRead(ch,0) ) pinSet(LCD0); else pinClear(LCD0);
    pinSet(LCDEN);
    delayMicroseconds(2);
    pinClear(LCDEN);
    delayMicroseconds(100);//delayMicroseconds(50);
}

// --------------------------------------------------
void initLCD8() {
    delayMicroseconds(50000); // tempo de espera apos kit ligado
    delayMicroseconds(30000); // tempo de espera apos kit ligado


    lcdWrite8(0,0b00111000); // barramento 8 bits, 2 linhas, matriz 5x7
    delayMicroseconds(4500);
    lcdWrite8(0,0b00111000); // barramento 8 bits, 2 linhas, matriz 5x7
    delayMicroseconds(4500);
    lcdWrite8(0,0b00111000); // barramento 8 bits, 2 linhas, matriz 5x7
    delayMicroseconds(4500);


    lcdWrite8(0,0b00001111); // display ON, cursor ON piscante
    lcdWrite8(0,0b00000001); // display clear (3 ms)
    delay(3);
    lcdWrite8(0,0b00000110); // entry mode set
}

// --------------------------------------------------
void initLCD4()
{
    
}

// --------------------------------------------------
void lcdString(const char *ch) 
{
    while (*ch != 0) {
        if(*ch == '\n') lcdComando(0xC0);
        else if (*ch == '\f') {lcdClear();}
             else lcdDado(*ch);
        ch++;
    }
}


#endif // lib_lcd_h
