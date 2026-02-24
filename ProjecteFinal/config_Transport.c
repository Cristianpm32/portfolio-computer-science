/*
 * OSI_Transport.c
 *
 *  Created on: 29 abr. 2024
 *      Author: cristianpradomendez
 */

#include "config_Transport.h"

#ifdef emulador
void init_UART(void)
{
    UCA0CTLW0 |= UCSWRST; //Fem un reset de la USCI, desactiva la USCI
    //UCSYNC=0 mode asíncron
    //UCMODEx=0 seleccionem mode UART
    //UCSPB=0 nomes 1 stop bit
    //UC7BIT=0 8 bits de dades
    //UCMSB=0 bit de menys pes primer
    //UCPAR=x ja que no es fa servir bit de paritat
    //UCPEN=0 sense bit de paritat
    UCA0CTLW0 |= UCSSEL__SMCLK; //Triem SMCLK (24MHz) com a font del clock BRCLK
    UCA0MCTLW = UCOS16; // Necessitem sobre-mostreig => bit 0 = UCOS16 = 1
    UCA0BRW = 3; //Prescaler de BRCLK fixat a 3. Com SMCLK va a24MHz,
    //volem un baud rate de 500 kbps i fem sobre-mostreig de 16
    //el rellotge de la UART ha de ser de 8MHz (24MHz/3).
    //UCA0MCTLW |= (0x25 << 8); //UCBRSx, part fractional del baud rate
    //Configurem els pins de la UART
    P1SEL0 |= BIT2 | BIT3; //I/O funció: P1.3 = UART0TX, P1.2 = UART0RX
    P1SEL1 &= ~(BIT2 | BIT3 );
    UCA0CTLW0 &= ~UCSWRST; //Reactivem la línia de comunicacions sèrie
    EUSCI_A0->IFG &= ~EUSCI_A_IFG_RXIFG; // Clear eUSCI RX interrupt flag
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE; // Enable USCI_A0 RX interrupt, nomes quan tinguem la recepcio

}
#else
    void init_UART(void)
    {

        UCA2CTLW0 |= UCSWRST; //Fem un reset de la USCI, desactiva la USCI
        UCA2CTLW0 |= UCSSEL__SMCLK; //Triem SMCLK (24MHz) com a font del clock BRCLK

        UCA2MCTLW = UCOS16; // Fem oversampling
        UCA2BRW = 3; // Setegem el prescaler

        //UCA2MCTLW |= (0x00 << 8); // Posem error del prescaler

        P3SEL0 |= BIT2 | BIT3; //Declarem que els pins 3.2 i 3.3 son funcio I/O
        P3SEL1 &= ~(BIT2 | BIT3 ); //

        UCA2CTLW0 &= ~UCSWRST; // Reactivem la linia de comunicació sèrie

        EUSCI_A2->IFG &= ~EUSCI_A_IFG_RXIFG; // Netejem la flag d'interrupcio
        EUSCI_A2->IE |= EUSCI_A_IE_RXIE; // Enable USCI_A0 RX interrupt, nomes quan tinguem la recepcio

    }
#endif

void Sentit_Dades_Rx(void)
{ //Configuració del Half Duplex dels motors: Recepció
    P3OUT &= ~BIT0; //El pin P3.0 (DIRECTION_PORT) el posem a 0 (Rx)
}

void Sentit_Dades_Tx(void)
{ //Configuració del Half Duplex dels motors: Transmissió
    P3OUT |= BIT0; //El pin P3.0 (DIRECTION_PORT) el posem a 1 (Tx)
}

void init_port3(void)
{
    P3SEL0 &= ~BIT0;
    P3SEL1 &= ~BIT0;
    P3DIR |= BIT0;
    P3OUT &= ~BIT0;

}

#ifdef emulador
/* funció TxUACx(byte): envia un byte de dades per la UART0 */
void TxUACx(uint8_t bTxdData)
{
    while (!TXD0_READY)
        ; // Espera a que estigui preparat el buffer de transmissió
    UCA0TXBUF = bTxdData;
}
#else
    void TxUACx(uint8_t bTxdData)
    {
        while (!TXD2_READY); // Espera a que estigui preparat el buffer de transmissió
        UCA2TXBUF = bTxdData;
    }
#endif

struct RxReturn TxRxPacket(byte bID, byte bParameterLength, byte bInstruction,
                           byte Parametros[16])
{
    TxPacket(bID, bParameterLength, bInstruction, Parametros);
    return RxPacket();
}

byte TxPacket(byte bID, byte bParameterLength, byte bInstruction,
              byte Parametros[16])
{
    byte bCount, bCheckSum, bPacketLength;
    byte TxBuffer[32];
    Sentit_Dades_Tx();
    TxBuffer[0] = 0xff;
    TxBuffer[1] = 0xff;
    TxBuffer[2] = bID;
    TxBuffer[3] = bParameterLength + 2;
    TxBuffer[4] = bInstruction;

    char error[] = "adr. no permitida";
    if ((Parametros[0] < 6) && (bInstruction == 3))
    { //si se intenta escribir en una direccion <= 0x05,
      //emitir mensaje de error de direccion prohibida:
        halLcdPrintLine(error, 8, INVERT_TEXT);
        //y salir de la funcion sin mas:
        return 0;
    }

    for (bCount = 0; bCount < bParameterLength; bCount++) //Comencem a generar la trama que hem d’enviar
    {

        TxBuffer[bCount + 5] = Parametros[bCount];
//El pin P3.0 (DIRECTION_PORT) el posem a 1 (Transmetre) //Primers 2 bytes que indiquen inici de trama FF, FF.
//ID del mòdul al que volem enviar el missatge //Length(Parameter,Instruction,Checksum) //Instrucció que enviem al Mòdul
    }
    bCheckSum = 0;
    bPacketLength = bParameterLength + 4 + 2;
    for (bCount = 2; bCount < bPacketLength - 1; bCount++) //Càlcul del checksum
    {
        bCheckSum += TxBuffer[bCount];
    }
    TxBuffer[bCount] = ~bCheckSum; //Escriu el Checksum (complement a 1)

    for (bCount = 0; bCount < bPacketLength; bCount++) //Aquest bucle és el que envia la trama al Mòdul Robot
    {
        // Aquesta funció es determina en temps de compilació
        TxUACx(TxBuffer[bCount]);
    }

    while (UCANSTATW)
        ; //Espera fins que s’ha transmès el últim byte

    Sentit_Dades_Rx(); //Posem la línia de dades en Rx perquè el mòdul Dynamixel envia resposta
    return (bPacketLength);
}

#ifdef emulador
    int QTY = 1000000; // Comptem fins a 1000, això és un timeout de 10 ms
#else
    int QTY = 1000; // Comptem fins a 1000, això és un timeout de 10 ms
#endif


struct RxReturn RxPacket(void)
{

    struct RxReturn respuesta;
    byte bCount = 0;
    byte bCheckSum = 0;
    byte hihaHagutTimeOut = 0;

    Sentit_Dades_Rx(); //Posem la linea en rebre

    for (bCount = 0; bCount < 4; bCount++) //bRxPacketLength; bCount++)
    {
        Reset_Timeout();
        Byte_Recibido = 0; //No_se_ha_recibido_Byte();
        while (!Byte_Recibido) //Se_ha_recibido_Byte())
        {
            hihaHagutTimeOut = TimeOut(QTY); // tiempo en decenas de microsegundos

            if (hihaHagutTimeOut)
                break; //sale del while

        }
        if (hihaHagutTimeOut)
            break;


        respuesta.StatusPacket[bCount] = DatoLeido_UART; //Get_Byte_Leido_UART();
    }

    respuesta.Timeout = hihaHagutTimeOut;
    if (hihaHagutTimeOut)
    {
        return respuesta;
    }

    // TOT BE A L'INICI

    byte bLength = respuesta.StatusPacket[3];

    for (bCount = 0; bCount < bLength; bCount++)
    {
        Reset_Timeout();
        Byte_Recibido = 0; //No_se_ha_recibido_Byte();
        while (!Byte_Recibido) //Se_ha_recibido_Byte())
        {

            hihaHagutTimeOut = TimeOut(QTY); // tiempo en decenas de microsegundos

            if (hihaHagutTimeOut)
                break; //sale del while

        }
        if (hihaHagutTimeOut)
            break;

        respuesta.StatusPacket[bCount + 4] = DatoLeido_UART; //Get_Byte_Leido_UART();
    }

    respuesta.Timeout = hihaHagutTimeOut;
    if (hihaHagutTimeOut)
    {
        return respuesta;

    }

    // Comprovem que les dades s'hagin llegit correctament
    bCheckSum = 0;

    // Calculem CheckSum
    for (bCount = 2; bCount < bLength + 3; bCount++)
    {
        bCheckSum += respuesta.StatusPacket[bCount];
    }
    bCheckSum = ~bCheckSum;

    // Comprovem Checksum

    if (bCheckSum != respuesta.StatusPacket[bLength + 3])
    {
        respuesta.CheckSumCorrecte = 1;
    }
    else
    {
        respuesta.CheckSumCorrecte = 0;
    }

    return respuesta;

}
