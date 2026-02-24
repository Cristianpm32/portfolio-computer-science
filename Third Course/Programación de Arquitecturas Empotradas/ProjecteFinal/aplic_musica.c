/*
 * aplic_musica.c
 *
 *  Created on: 18 may. 2024
 *      Author: janaccensimarch
 */



#include "aplic_musica.h"


void play()

{
    byte Parametros[16];
    Parametros[0] = BUZZER;
    Parametros[1] = MELODIA;
    Parametros[2] = 0xFF; // Amb això podem seleccionar una melodia per defecte
    struct RxReturn resposta = TxRxPacket(SENSOR, 3, WRITE, Parametros);
    playing = 1;
}
