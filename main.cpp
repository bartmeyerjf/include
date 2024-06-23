// -----------------------------------------
// Programa principal MAIN
// -----------------------------------------


// -----------------------------------------
// SEÇÃO HEADER (.h)
// -----------------------------------------


//#include "piscaLedsTimer.c"
//#include "display7seg.c"
//#include "fsm.c"
#include "test_lcd.c"

// -----------------------------------------
// SEÇÃO DE IMPLEMENTAÇÃO (.c)
// -----------------------------------------


#ifndef Arduino_h
int main(void) {
    //debug_init(); // inicializa a estrutura de debug
    //sei();    // habilita as interrupções
    setup();
    while(1) {loop();}
    return 0;
}
#endif


