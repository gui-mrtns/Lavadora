#include "pic18f4520.h"
#include "config.h"
#include "lcd.h"
#include "delay.h"
#include "keypad.h"
#include "pwm.h"

unsigned int lerTeclado() {
    unsigned char tecla;
    do {
        TRISD = 0x0F;
        tecla = kpRead(0) + 0x30;
        TRISD = 0x00;
        lcdCommand(0x8F);
        if(tecla != '1' && tecla != '2' && tecla != '3') lcdPrint("X");
        else lcdData(tecla);
        atraso_s(1);
        lcdCommand(0x8F);
        lcdPrint(" ");
    } while(tecla != '1' && tecla != '2' && tecla != '3');
    return tecla - '0';
}

unsigned int lerNivel() {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("Nivel de agua:");
    lcdCommand(L_L2);
    lcdPrint("(1)Baixo");
    lcdCommand(L_L3);
    lcdPrint("(2)Medio");
    lcdCommand(L_L4);
    lcdPrint("(3)Alto");
    return lerTeclado();
}

unsigned int lerRoupa() {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("Tipo de roupa:");
    lcdCommand(L_L2);
    lcdPrint("(1)Delicada");
    lcdCommand(L_L3);
    lcdPrint("(2)Colorida");
    lcdCommand(L_L4);
    lcdPrint("(3)Branca");
    return lerTeclado();
}

unsigned int lerSituacao() {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("Situacao roupa:");
    lcdCommand(L_L2);
    lcdPrint("(1)Pouco suja");
    lcdCommand(L_L3);
    lcdPrint("(2)Suja");
    lcdCommand(L_L4);
    lcdPrint("(3)Muito suja");
    return lerTeclado();
}

unsigned int lerLavagem() {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("Tipo lavagem:");
    lcdCommand(L_L2);
    lcdPrint("(1)Economica");    // Lava, enxagua, centrifuga
    lcdCommand(L_L3);
    lcdPrint("(2)Normal");       // Economica + molho
    lcdCommand(L_L4);
    lcdPrint("(3)Completa");     // Normal + pre-lava
    return lerTeclado();
}

unsigned int lerMolho() {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("Tempo de molho:");
    lcdCommand(L_L2);
    lcdPrint("(1)Curto");
    lcdCommand(L_L3);
    lcdPrint("(2)Medio");
    lcdCommand(L_L4);
    lcdPrint("(3)Longo");
    return lerTeclado();
}

void injetarAgua(unsigned int tempo) {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("INJETANDO AGUA");
    PORTC = 0x01;
    atraso_s(tempo*3);
    PORTC = 0x00;
}

void retirarAgua(unsigned int tempo) {
    lcdCommand(L_CLR);
    lcdCommand(L_L1);
    lcdPrint("RETIRANDO AGUA");
    PORTE = 0x01;
    atraso_s(tempo*3);
    PORTE = 0x00;
}

void testeTecla() {
    lcdCommand(L_L4);
    lcdPrint("Pressione RB3");
    while(BitTst(PORTB, 3));
    lcdCommand(L_L4 + 14);
    lcdPrint("Ok");
    atraso_s(1);
}

void main(void) {
    unsigned int nivel, roupa, situacao, lavagem, molho;
    for(;;) {
        ADCON1 = 0x06;
        TRISB = 0xF8;
        TRISC = 0x00;
        TRISD = 0x00;
        TRISE = 0x00;
        lcdInit();
        pwmInit();
        lcdCommand(L_CLR);
        lcdCommand(L_L1);
        lcdPrint("Inicializando...");
        atraso_s(3);
        lcdCommand(L_L4);
        testeTecla();
        
        nivel = lerNivel();
        roupa = lerRoupa();
        situacao = lerSituacao();
        lavagem = lerLavagem();
        if(lavagem != 1) molho = lerMolho();
        
        lcdCommand(L_CLR);
        lcdCommand(L_L1);
        lcdPrint("Iniciar lavagem?");
        testeTecla();
        
        injetarAgua(nivel);
        
        if(lavagem == 3) {
            lcdCommand(L_CLR);
            lcdCommand(L_L1);
            lcdPrint("PRE-LAVANDO");
            pwmSet1(((nivel+roupa+situacao)*5 + 54)*3/4);
            atraso_s(situacao*3);
            pwmSet1(0);
            retirarAgua(nivel);
            injetarAgua(nivel);
        }
        
        if(lavagem != 1) {
            lcdCommand(L_CLR);
            lcdCommand(L_L1);
            lcdPrint("EM MOLHO");
            atraso_s(molho*5);
        }
        
        lcdCommand(L_CLR);
        lcdCommand(L_L1);
        lcdPrint("LAVANDO");
        pwmSet1((nivel+roupa+situacao)*5 + 54);
        atraso_s(situacao*5);
        pwmSet1(0);
    
        retirarAgua(nivel);
        injetarAgua(nivel);
        
        lcdCommand(L_CLR);
        lcdCommand(L_L1);
        lcdPrint("ENXAGUANDO");
        pwmSet1((nivel+roupa)*8 + 51);
        atraso_s(nivel*5);
        pwmSet1(0);
        
        retirarAgua(nivel);
        
        lcdCommand(L_CLR);
        lcdCommand(L_L1);
        lcdPrint("CENTRIFUGANDO");
        pwmSet1((nivel+roupa)*6 + 63);
        atraso_s(nivel*5);
        pwmSet1(0);
        
        lcdCommand(L_CLR);
        lcdCommand(L_L1);
        lcdPrint("A lavagem foi");
        lcdCommand(L_L2);
        lcdPrint("concluida!");
        testeTecla();
    }
}