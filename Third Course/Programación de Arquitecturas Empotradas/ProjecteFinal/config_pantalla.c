/*
 * config_pantalla.c
 *
 *  Created on: 16 may. 2024
 *      Author: janaccensimarch
 */

#include <config_pantalla.h>

void init_pantalla()
{
    extern const Graphics_Image logoUB8BPP_UNCOMP; //Los datos del logo UB, que estan en "logoUB_256.c"

    halLcdInit(); //Inicializar y configurar la pantallita
    halLcdClearScreenBkg(); //Borrar la pantalla, rellenando con el color de fondo

    Color_Texto_Inv = COLOR_16_ORANGE; //cambiamos el color del texto en modo INVERT_TEXT
    uint16_t x0 = (getScreenWidth() - logoUB8BPP_UNCOMP.xSize) >> 1; //Coordenadas para pintar el logo centrado
    uint16_t y0 = 1; //y abajo de la pantalla

    pintaLogo(logoUB8BPP_UNCOMP, x0, y0);

    linia = 5; //Para memorizar en que linea estoy escribiendo en todo momento

    halLcdPrintLine(" Projecte Final PAE! ", linia++, INVERT_TEXT);
    halLcdPrintLine(" Autors: ", linia++, NORMAL_TEXT);
    halLcdPrintLine(" Cristian Prado", linia++, NORMAL_TEXT);
    halLcdPrintLine(" Jan Accensi", linia++, NORMAL_TEXT);
    halLcdPrintLine(" Press to start", linia++, NORMAL_TEXT);

}
void pintar_menu()
{

    halLcdClearScreenBkg(); //Borrar la pantalla, omplim amb el color de fons

    /*
     * QUAN ES PREMI SOBRE AQUESTA LÍNIA SI ESTÀ CALIBRAT COMENÇARÀ EL ROBOT
     */

    halLcdPrintLine("  Press to Star", 1, NORMAL_TEXT);

    /*
     * AQUÍ ES POT CALIBRAR
     */
    halLcdPrintLine("  Calibrar: ", 2, NORMAL_TEXT);
    if (calibrat == CALIBRAT)
    {

        char dst[5];
        sprintf(dst, "%d", distancia_inferior);
        halLcdPrintLineCol(dst, 2, 11, NORMAL_TEXT);
    }
    else
    {
        halLcdPrintLineCol("?", 2, 11, NORMAL_TEXT);
    }

    /*
     * AQUÍ S'ESCULL PER QUIN COSTAT ES VOL RESSEGUIR L'OBSTACLE
     */

    halLcdPrintLine("  Left/Right", 3, NORMAL_TEXT);

    if (resseguim_default == RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA)
    {
        halLcdPrintLineCol("L", 3, 13, NORMAL_TEXT);
    }
    else if (resseguim_default == RESSEGUIM_PARET_ENGANXAT_A_DRETA)
    {
        halLcdPrintLineCol("R", 3, 13, NORMAL_TEXT);
    }

    halLcdPrintLine("  Musica: ", 4, NORMAL_TEXT);

    if (musica == MUSICA_ON)
    {
        halLcdPrintLineCol("ON", 4, 10, NORMAL_TEXT);
    }
    else
    {
        halLcdPrintLineCol("OFF", 4, 10, NORMAL_TEXT);
    }

    char apl[5];
    sprintf(apl, "%d %d", num_aplaudiments_anterior, comencar);

    halLcdPrintLineCol(apl, 6, 2, NORMAL_TEXT);






    /*
     * AMB AIXÒ MARQUEM QUINA LÍNIA ESTÀ SELECCIONADA
     */

    halLcdPrintLineCol("*", linia_seleccionada, 0, NORMAL_TEXT);

}

void actualitzar_pantalla(byte estat)
{

    estat_anterior_pantalla = estat_pantalla;

    switch (estat)
    {
    case PANTALLA_BENVINGUDA:
        init_pantalla();
        break;
    case MENU_PRINCIPAL:
        pintar_menu();
        break;
    }

}

void EncenderRGB_Launchpad(uint8_t cuales)
{
    P2OUT &= ~0x07; //Primero apago los Leds
    P2OUT |= cuales; //y luego enciendo los que me indica el parametro recibido
}

void pintaLogo(Graphics_Image Imagen, uint8_t x0, uint8_t y0)
{
    uint16_t w, h;
    w = Imagen.xSize;
    h = Imagen.ySize;
    halLcdDrawImageLut(x0, y0, w, h, Imagen.pPixel, Imagen.pPalette,
                       Imagen.numColors);
}

void borrar_Logo(Graphics_Image Imagen, uint8_t x0, uint8_t y0)
{
    uint16_t x, y;
    x = x0 + Imagen.xSize;
    y = y0 + Imagen.ySize;
    halLcdFillRect(x0, y0, x, y, Color_Fondo);
}

