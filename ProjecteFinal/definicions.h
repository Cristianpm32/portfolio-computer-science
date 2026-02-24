/*
 * definicions.h
 *
 *  Created on: 2 may. 2024
 *      Author: janaccensimarch
 */

#ifndef DEFINICIONS_H_
#define DEFINICIONS_H_

#include <msp432p401r.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lib_PAE.h"

/*
 *
 * FITXER AMB TOTES LES DEFINICIONS NECESSÀRIES PER AL CORRECTE FUNCIONAMENT DEL CODI
 *
 *
 */

/*
 * ***** GLOBALS *****
 */
typedef uint8_t byte;
//#define emulador


/*
 * ***** RX and TX *****
 */

// Definim els id de les instruccions de lectura i escriptura
#define WRITE 0x03
#define READ 0x02

// Variables volatils necessaries per un bon funcionament del RxPacket i TxPacket
volatile byte DatoLeido_UART;
volatile byte Byte_Recibido;

// Variables pel timer
// Observem que és important que el cnt sigui un enter. Si és un uint8_t només serà un valor entre 0-255
volatile int cnt;


// Estructura per al RxPacket i poder rebre paquets
typedef struct RxReturn
{
    // Packet rebut
    byte StatusPacket[32];

    // Indiquem si hem accedit el temps en llegir el packet
    byte Timeout;

    // Indiquem si el checksum es correcte. 1 incorrecte, 0 correcte
    byte CheckSumCorrecte;

} RxReturn;

#define TXD0_READY (UCA0IFG & UCTXIFG)
#define TXD2_READY (UCA2IFG & UCTXIFG)


#ifdef emulador
    #define UCANSTATW (UCA0STATW & UCBUSY)
#else
    #define UCANSTATW (UCA2STATW & UCBUSY)
#endif



/*
 * ***** LED *****
 */

#define LED 0x19

/*
 * ***** MOTOR *****
 */

// Definim els id pel motor
#define MOTOR 0x20

// Definim constants pel moviment continu del robot
#define CW_ANGLE_LIMIT_L 0x06 // Els bits de la part baixa per escriure l'angle CW
#define CW_ANGLE_LIMIT_H 0x07 // Els bits de la part alta per escriure l'angle CW
#define CCW_ANGLE_LIMIT_L 0x08 // Els bits de la part baixa per escriure l'angle CCW
#define CCW_ANGLE_LIMIT_H 0x09 // Els bits de la part alta per escriure l'angle CCW

// Definim els id dels motors i del sensor
#ifdef emulador
    #define MOTOR_LEFT 0x01
    #define MOTOR_RIGHT 0x02
    #define SENSOR 0x03

#else
    #define MOTOR_LEFT 0x03
    #define MOTOR_RIGHT 0x02
    #define SENSOR 100
#endif


#define GIR_ENDAVANT 0
#define GIR_ENRERE 1
#define ROTACIO_ESQUERRA 0
#define ROTACIO_DRETA 1

/*
 * ***** BOTONS *****
 */

// Definim els valors que utilitzarem per les interrupcions dels botons
#define BOTO1 0x01
#define BOTO2 0x02
#define DRETA 0x03
#define ESQUERRA 0x04


/*
 * ***** MOVIMENT AUTÒNOM i OBSTACLES*****
 */

#define SPEED 500 // 500 o menys es un valor segur
volatile int distancia_inferior;
volatile int distancia_superior;
#define MARGE_SEGURETAT 20 // 25 si volem anar sobre segur

/*
 * ESCENARI
 */
volatile int escenari_actual;

#define NO_HEM_TROBAT_PARET -1
#define RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA 0
#define RESSEGUIM_PARET_ENGANXAT_A_DRETA 1
volatile byte resseguim_default; // per defecte ressegueix a l'esquerra
#define CUL_DE_SAC 4


/*
 * ESTAT
 */

/*
volatile int ESTAT_ACTUAL;


#define NO_OBSTACLE 0
#define ONLY_LEFT 1
#define ONLY_CENTER 2
#define ONLY_RIGHT 4
#define LEFT_AND_CENTER 3
#define LEFT_AND_RIGHT 5
#define RIGHT_AND_CENTER 6
#define CENTER_LEFT_AND_RIGHT 7

#define OBSTACLE_ESQUERRA BIT0;
#define OBSTACLE_CENTRE BIT1;
#define OBSTACLE_DRETA BIT2;
#define HA_TROBAT_PARET BIT3;

#define OBSTACLE_SENSE_SORTIDA 3

*/


/*
 * ***** PANTALLA *****
 */

volatile byte linia; // Linia on està pintant actualment
volatile byte linia_seleccionada; // Linia seleccionada del menú
#define NUM_LINIES_MENU 4


// Variables per a controlar si hi ha hagtu canvis en els joysticks
volatile byte estat_pantalla;
volatile byte estat_anterior_pantalla;


// Estats pantalla:
#define PANTALLA_BENVINGUDA 1 // PER DEFECTE
#define MENU_PRINCIPAL 2


volatile byte comencar; // Boolea que ens indica si podem començar o no
volatile byte parar;
// Integer que ens indica si NO hem calibrat (ni ho hem intentat) 0. Si volem calibrar = 1; Si hem calibra = 2
volatile byte calibrat;

#define CALIBRAT 0
#define PENDENT_CALIBRAR 1
#define NO_CALIBRAT 2


/*
 * MUSICA
 */


#define BUZZER 0x28
#define MELODIA 0x2 // Podem seleccionar una melodia entre 0-26

volatile byte musica;
#define MUSICA_OFF 0
#define MUSICA_ON 1
volatile byte playing;


/*
 * APLAUDIMENTS (PARAR EL ROBOT)
 *
 */

#define DETECTOR 0x25
volatile byte num_aplaudiments_anterior;
volatile byte nombreAplaudiments;

#endif /* DEFINICIONS_H_ */
