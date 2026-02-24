/*
 * aplic_sound.c
 *
 *  Created on: 18 may. 2024
 *      Author: janaccensimarch
 */

#include "aplic_sound.h"

byte llegir_aplaudiments()
{

    byte parametres[16];
    parametres[0] = DETECTOR;
    parametres[1] = 0x01;

    struct RxReturn resposta = TxRxPacket(SENSOR, 2, READ, parametres);

    return resposta.StatusPacket[5];

}

void comprovar_si_vol_comencar()
{

    /*
     * Seguint la documentació del sensor, podem detectar quants cops aplaudeix
     */
    nombreAplaudiments = llegir_aplaudiments();
    //num_aplaudiments_anterior = llegir_aplaudiments();
    // Si s'ha detectat algun aplaudiment, comencem el robot
    if (nombreAplaudiments != num_aplaudiments_anterior)
    {
        num_aplaudiments_anterior = nombreAplaudiments;

        if(nombreAplaudiments != 1 ){

           comencar = 1;
        }
        else {
            comencar = 0;
        }

        estat_anterior_pantalla = 0;
        estat_pantalla = MENU_PRINCIPAL;
        linia_seleccionada = 1;
    }

}

