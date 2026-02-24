/*
 * OSI_Transport.h
 *
 *  Created on: 29 abr. 2024
 *      Author: cristianpradomendez
 */

#ifndef CONFIG_TRANSPORT_H_
#define CONFIG_TRANSPORT_H_


#include "definicions.h"
#include "config_timer.h"
/*
 * FUNCIONS DE COMUNICACIO
 */
struct RxReturn TxRxPacket(byte bID, byte bParameterLength, byte bInstruction, byte Parametros[16]);
byte TxPacket(byte bID, byte bParameterLength, byte bInstruction, byte Parametros[16]);
struct RxReturn RxPacket(void);

/*
 * CONFIGURACIÓ
 */


void init_port3(void);

void init_UART(void);

void Sentit_Dades_Rx(void);

void Sentit_Dades_Tx(void);

/* funció TxUACx(byte): envia un byte de dades per la UART0 */
// Aquesta funció en temps de compilació es decideix quins s'agafa.
void TxUACx(uint8_t bTxdData);



#endif /* CONFIG_TRANSPORT_H_ */
