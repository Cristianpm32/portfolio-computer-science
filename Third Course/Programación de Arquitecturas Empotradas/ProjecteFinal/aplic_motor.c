/*
 * aplic_motor.c
 *
 *  Created on: 3 may. 2024
 *      Author: janaccensimarch
 */

#include "aplic_motor.h"

// Com fem perque sigui Endless?
void init_EndlessTurn(void)
{

    // Hem d'escriure 0 a les posicions CW_ANGLE_LIMIT_L, CW_ANGLE_LIMIT_H, CCW_ANGLE_LIMIT_L, CCW_ANGLE_LIMIT_H

    byte parametres[16];

    parametres[0] = CW_ANGLE_LIMIT_L; // Indiquem on comença l'espai de memòria on volem escriure
    parametres[1] = 0; // escribim 0 als 4 bytes següents de memòria.
    parametres[2] = 0;
    parametres[3] = 0;
    parametres[4] = 0;

    TxRxPacket(MOTOR_LEFT, 2, WRITE, parametres);
    TxRxPacket(MOTOR_RIGHT, 2, WRITE, parametres);

}

struct RxReturn moure(byte bId, byte direction, unsigned int speed)
{
    //definim la moving speed
    //en el registre 0x20 hem de posar el valor de la velocitat en els bits 0-9
    //i la direcció de gir en el bit 10
    //com la velocitat ocupa mes d'un byte, necessitem partirla en dos
    byte Mov_speed_L = speed & 0xFF;
    byte Mov_speed_H = ((direction << 2) & 0x04) | ((speed >> 8) & 0x03);

    // On volem escriure i els bits que volem escriure trencats en 2 perquè no hi caben
    byte bParametros[16] = { MOTOR, Mov_speed_L, Mov_speed_H };

    return TxRxPacket(bId, 3, WRITE, bParametros);
}

void stop()
{

    moure(MOTOR_LEFT, 0, 0);
    moure(MOTOR_RIGHT, 0, 0);
}

void endavant(unsigned int speed)
{
// S'ha de tenir en compte que els motors tenen direcció "oposada".

    struct RxReturn resposta1 = moure(MOTOR_LEFT, 0, speed);
    struct RxReturn resposta2 = moure(MOTOR_RIGHT, 1, speed);
}

void enrere(unsigned int speed)
{
    moure(MOTOR_LEFT, 1, speed);
    moure(MOTOR_RIGHT, 0, speed);
}
// Les rodes van en el mateix sentit
void gir(unsigned int grau_esquerra, unsigned int grau_dreta, unsigned int sentit)
{
    /*
     * El grau és la velocitat de cada motor. Si grau_esquerra és alt,
     * aleshores girarà cap a la dreta.
     *
     */

    if (sentit == GIR_ENDAVANT)
    {

        moure(MOTOR_LEFT, 0, grau_esquerra);
        moure(MOTOR_RIGHT, 1, grau_dreta);
    }
    else
    {
        moure(MOTOR_LEFT, 1, grau_esquerra);
        moure(MOTOR_RIGHT, 0, grau_dreta);
    }

}

// Les rodes van en sentit contrari
void rotar(unsigned int grau_esquerra, unsigned int grau_dreta, unsigned int sentit)
{
    if (sentit == ROTACIO_ESQUERRA)
    {
        moure(MOTOR_LEFT, 1, grau_esquerra);
        moure(MOTOR_RIGHT, 1, grau_dreta);
    }
    else
    {
        moure(MOTOR_LEFT, 0, grau_esquerra);
        moure(MOTOR_RIGHT, 0, grau_dreta);
    }

}

// PiVOTAR SOBRE SI MATEIX VElocitat 200 ok.

