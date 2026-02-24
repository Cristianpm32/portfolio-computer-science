/*
 * aplic_motor.h
 *
 *  Created on: 3 may. 2024
 *      Author: janaccensimarch
 */


#ifndef APLIC_MOTOR_H
#define APLIC_MOTOR_H

#include "config_Transport.h"

void stop();
void endavant(unsigned int speed);
void enrere(unsigned int speed);
void rotar(unsigned int grau_esquerra,unsigned int grau_dreta, unsigned int sentit);
void gir(unsigned int grau_esquerra,unsigned int grau_dreta, unsigned int sentit);
void init_EndlessTurn(void);

#endif /* APLIC_MOTOR_H */



