/*
 * config_pantalla.h
 *
 *  Created on: 16 may. 2024
 *      Author: janaccensimarch
 */

#ifndef CONFIG_PANTALLA_H_
#define CONFIG_PANTALLA_H_

#include <definicions.h>
#include <lib_PAE.h>

void init_pantalla(void);
void EncenderRGB_Launchpad(uint8_t cuales);
void pintaLogo(Graphics_Image Imagen, uint8_t x0, uint8_t y0);
void borrar_Logo(Graphics_Image Imagen, uint8_t x0, uint8_t y0);
void actualitzar_pantalla(byte estat);


#endif /* CONFIG_PANTALLA_H_ */
