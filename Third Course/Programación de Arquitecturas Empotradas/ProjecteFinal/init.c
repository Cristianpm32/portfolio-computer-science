/*
 * config.c
 *
 *  Created on: 29 abr. 2024
 *      Author: janaccensimarch
 */

#include <init.h>

void init(void)
{
    // Inicialitzem el clock
    init_ucs_24MHz();

    // Inicialitzem el port 3 per tal de poder utilitzar la linia half-duplex
    init_port3();

    // Configurem i activem les interrupcions a nivell de NVIC
    init_interrupciones_NVIC();

    init_joysticks();

    // Activem les interrupcions a nivell global.
    __enable_interrupts();

    // Inicialitzem la UART, aquest metode és decideix en temps de compilació en funció de si utilitzem l'emulador o no
    // Aquí també s'activen les interrupcions de UART
    init_UART();

    // Configurem i activem el timer (+ interrupcions)
    init_timers();

    // Configurem que els motors siguin Endless turn
    init_EndlessTurn();

    init_pantalla();

    #ifdef emulador
        distancia_inferior = 50; // Aquest valor se sobreescriurà amb la mesura
        comencar = 1; // Fals
        calibrat = CALIBRAT;
    #else
        distancia_inferior = 100;
        comencar = 0; // Fals
        calibrat = NO_CALIBRAT;
    #endif

    distancia_superior = distancia_inferior + MARGE_SEGURETAT;
    estat_anterior_pantalla = PANTALLA_BENVINGUDA;
    estat_pantalla = PANTALLA_BENVINGUDA;
    linia_seleccionada = 0;
    escenari_actual = NO_HEM_TROBAT_PARET;
    resseguim_default = RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA; // Aquest valor es canvia en el menú. Només fem que primer surti la L
    musica = MUSICA_OFF;
    playing = 0;

    nombreAplaudiments = llegir_aplaudiments();
    num_aplaudiments_anterior = llegir_aplaudiments();
    parar = 0;

}

