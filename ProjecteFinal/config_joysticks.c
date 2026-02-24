/*
 * config_joysticks.c
 *
 *  Created on: 16 may. 2024
 *      Author: janaccensimarch
 */

#include <config_joysticks.h>

void init_joysticks()
{

    //Configuramos joysticks y leds
    //***************************

    //Led RGB del launchpad:
    P2DIR |= BIT0 | BIT1 | BIT2; //Puerto P2.0 (R), 2.1 (G) y 2.2 (B) como salidas Led2 (RGB)
    P2OUT &= ~(BIT0 | BIT1 | BIT2 );   //Inicializamos Led RGB a 0 (apagados)

    /*
     * Port 5.1 (POLSADOR S1):
     *
     */
    P5SEL0 &= ~(BIT1 );
    P5SEL1 &= ~(BIT1 );

    P5DIR &= ~(BIT1);
    P5REN |= (BIT1);
    P5OUT |= (BIT1 );

    P5IE |= (BIT1);
    P5IES &= ~(BIT1);
    P5IFG = 0;

    /*
     * JOYSTICKS
     */

    P5DIR &= ~(BIT4 + BIT5 );  //Pines P5.4 y 5.5 como entrades,
    P5SEL0 &= ~(BIT4 + BIT5 ); //Pines P5.4 y 5.5 como I/O digitales,
    P5SEL1 &= ~(BIT4 + BIT5 );
    P5IE |= BIT4 + BIT5;  //Interrupciones activadas en 5.4 y 5.5,
    P5IES &= ~(BIT4 + BIT5 ); //las interrupciones se generaran con transicion L->H
    P5IFG = 0;    //Limpiamos todos los flags de las interrupciones del puerto 4
    // - Ya hay una resistencia de pullup en la placa

    /*
     * NVIC
     */
    //Int. port 5 = 39 corresponde al bit 7 del segundo registro ISERx:
    NVIC->ICPR[1] |= BIT7; //Primero, me aseguro de que no quede ninguna interrupcion residual pendiente para este puerto,
    NVIC->ISER[1] |= BIT7; //y habilito las interrupciones del puerto



}

