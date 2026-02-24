#include "aplicacio.h"

void main(void)
{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    /*
     * ATENCIÓ! ASSEGURAR-SE QUE LA VARIABLE #define emulador
     * DE LA CLASSE DEFINICIONS.H ESTÀ COMENTADA.
     * AIXÒ PERMET TREBALLAR AMB L'EMULADOR EN CAS DE VOLER-HO.
     */

    init();

    while (true)
    {

        if (musica == MUSICA_ON)
        {
            play();
        }
        if (calibrat == PENDENT_CALIBRAR)
        {
            calibrar();
        }
        if (estat_anterior_pantalla != estat_pantalla)
        {
            actualitzar_pantalla(estat_pantalla);
        }

        comprovar_si_vol_comencar(); // Si aplaudeixes 2 vegades pots parar el robot.


        if (comencar && (calibrat == CALIBRAT))
        {
            struct RxReturn sensors = llegir_sensor();

            byte distancia_esquerra = 255 - sensors.StatusPacket[5];
            byte distancia_centre = 255 - sensors.StatusPacket[6];
            byte distancia_dreta = 255 - sensors.StatusPacket[7];

            moure_robot(distancia_esquerra, distancia_centre, distancia_dreta);

        }






    }

}

