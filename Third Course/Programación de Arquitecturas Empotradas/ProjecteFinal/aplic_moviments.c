/*
 * aplic_moviments.c
 *
 *  Created on: 5 may. 2024
 *      Author: janaccensimarch
 */

#include <aplic_moviments.h>


void avancar()
{
    endavant(SPEED);
    espera(10);
}

void moure_robot(byte distancia_esquerra, byte distancia_centre,
                 byte distancia_dreta)
{

    // Aquesta funció det   ermina quina acció ha de prendre el robot en funció de cada estat.

    //actualitzarEstat(distance_esquerra, distance_centre, distance_dreta);

    switch (escenari_actual)
    {

    case NO_HEM_TROBAT_PARET:

        if (distancia_esquerra >= distancia_inferior && distancia_dreta >= distancia_inferior
                && distancia_centre >= distancia_inferior)
        {
            avancar();
        }
        else if (distancia_centre <= distancia_inferior)
        {
            escenari_actual = resseguim_default;
        }
        else if (distancia_esquerra <= distancia_inferior
                && distancia_esquerra <= distancia_dreta)
        {
            escenari_actual = RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA;
        }

        else if (distancia_dreta <= distancia_esquerra
                && distancia_dreta <= distancia_inferior)
        {
            escenari_actual = RESSEGUIM_PARET_ENGANXAT_A_DRETA;
        }

        break;

    case RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA:

        if (distancia_centre <= distancia_inferior && distancia_esquerra <= distancia_inferior
                && distancia_dreta <= distancia_inferior)
        {
            escenari_actual = CUL_DE_SAC;
        }

        else if (distancia_centre <= distancia_inferior
                || distancia_esquerra <= distancia_inferior)
        {
            rotar(SPEED, SPEED, ROTACIO_DRETA);
        }

        else if (distancia_centre >= distancia_superior
                && distancia_esquerra >= distancia_superior)
        {
            gir(SPEED, 2 * SPEED, GIR_ENDAVANT);

        }
        else
        {
            avancar();
        }
        break;
    case RESSEGUIM_PARET_ENGANXAT_A_DRETA:
        if (distancia_centre <= distancia_inferior && distancia_esquerra <= distancia_inferior
                && distancia_dreta <= distancia_inferior)
        {
            escenari_actual = CUL_DE_SAC;
        }

        else if (distancia_centre <= distancia_inferior || distancia_dreta <= distancia_inferior)
        {
            rotar(SPEED, SPEED, ROTACIO_ESQUERRA);
        }

        else if (distancia_centre >= distancia_superior
                && distancia_dreta >= distancia_superior)
        {
            gir(2 * SPEED, SPEED, GIR_ENDAVANT);

        }
        else
        {
            avancar();
        }
        break;

    case CUL_DE_SAC:



        if (distancia_centre != 255 && distancia_esquerra != distancia_dreta)
        {
            if (resseguim_default == RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA)
                rotar(SPEED, SPEED, ROTACIO_DRETA);
            if (resseguim_default == RESSEGUIM_PARET_ENGANXAT_A_DRETA)
                rotar(SPEED, SPEED, ROTACIO_ESQUERRA);

        }

        else
        {

            escenari_actual = resseguim_default;

        }



        break;

    default:
        break;

    }

}

