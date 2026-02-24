/*
 * aplic_sensor.c
 *
 *  Created on: 3 may. 2024
 *      Author: janaccensimarch
 */


#include <aplic_sensor.h>


struct RxReturn llegir_sensor(void){

    byte parametres[16];

    /*
     *  Les posicions de memòria del sensors comencen al 0x1A
     *  0x1A (Esquerra)
     *  0x1B (Centre)
     *  0x1C (Dreta)
     *
     */
    parametres[0] = 0x1A;
    parametres[1] = 0x03; // Volem llegir 3 bytes (els 3 sensors)

    struct RxReturn resposta = TxRxPacket(SENSOR, 0x02, READ, parametres);

    return resposta;

}


void calibrar(){
    distancia_inferior = 255 - llegir_sensor().StatusPacket[6];
    distancia_superior = distancia_inferior + MARGE_SEGURETAT;
    calibrat = CALIBRAT;
}




