#include "pic18f4520.h"
#include "lcd.h"
#include "delay.h"

void lcdWrite(unsigned char val) {
    PORTD = val;
}

void lcdCommand(unsigned char val) {
    BitSet(PORTE,1); // Enable - PORTEbits.RE1
    lcdWrite(val);
    BitClr(PORTE,2); // Data - PORTEbits.RE2
    atraso_ms(3);
    BitClr(PORTE,1); 
    atraso_ms(3);
    BitSet(PORTE,1); 
}

void lcdData(unsigned char val) {
    BitSet(PORTE,1); 
    lcdWrite(val);
    BitSet(PORTE,2); 
    atraso_ms(3);
    BitClr(PORTE,1); 
    atraso_ms(3);
    BitSet(PORTE,1); 
}

void lcdInit(void) {
    BitClr(PORTE,1); 
    BitClr(PORTE,2); 
    atraso_ms(20);
    BitSet(PORTE,1); 

    lcdCommand(L_CFG);
    atraso_ms(5);
    lcdCommand(L_CFG);
    atraso_ms(1);
    lcdCommand(L_CFG); //configura
    lcdCommand(L_OFF); //desliga
    lcdCommand(L_ON);  //liga
    lcdCommand(L_CLR); //limpa
    lcdCommand(L_CFG); //configura
    lcdCommand(L_L1);
}

void lcdPrint(const char* str) {
    unsigned char i = 0;

    while (str[i] != 0) {
        lcdData(str[i]);
        i++;
    }
}