/*
 * aplic_led.c
 *
 *  Created on: 2 may. 2024
 *      Author: janaccensimarch
 */


#include "aplic_led.h"

struct RxReturn encendreLED(byte id)
{
    byte Parametros[16];
    Parametros[0] = LED;
    Parametros[1] = 1;
    return TxRxPacket(id, 2, WRITE, Parametros);
}

struct RxReturn apagarLED(byte id)
{

    byte Parametros[2] = {LED, 0};
    return TxRxPacket(id, 2, WRITE, Parametros);
}



