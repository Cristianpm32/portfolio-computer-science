#include "config_interrupcions.h"

void init_interrupciones_NVIC(void)
{

    // Configurem a nivell de NVIC les interrupcions dels UART
#ifdef emulador

    NVIC->ICPR[0] |= 1 << EUSCIA0_IRQn;
    NVIC->ISER[0] |= 1 << EUSCIA0_IRQn;
#else
    NVIC->ICPR[0] |= 1 << EUSCIA2_IRQn;
    NVIC->ISER[0] |= 1 << EUSCIA2_IRQn;
#endif

    // Configurem a nivell de NVIC les interrupcions del timer
    NVIC->ICPR[0] |= 1 << TA1_0_IRQn;
    NVIC->ISER[0] |= 1 << TA1_0_IRQn;

}

//Emulador
void EUSCIA0_IRQHandler(void)
{
    // Netejem la interrupci�
    EUSCI_A0->IFG &= ~ EUSCI_A_IFG_RXIFG;

    // Desactivem les interrupcions en Rx
    UCA0IE &= ~UCRXIE;
    DatoLeido_UART = UCA0RXBUF;
    Byte_Recibido = 1;

    // Reactivem les interrupcions en Rx
    UCA0IE |= UCRXIE;
}

//real

void EUSCIA2_IRQHandler(void)
{
    // Netejem la interrupci�
    EUSCI_A2->IFG &= ~ EUSCI_A_IFG_RXIFG;

    // Desactivem les interrupcions en Rx
    UCA2IE &= ~UCRXIE;
    DatoLeido_UART = UCA2RXBUF;
    Byte_Recibido = 1;

    // Reactivem les interrupcions en Rx
    UCA2IE |= UCRXIE;
}

void TA1_0_IRQHandler(void)
{

    TA1CCTL0 &= ~TIMER_A_CCTLN_CCIFG; //Clear interrupt flag
    cnt += 1;

}


void PORT5_IRQHandler(void)
{
    uint8_t flag = P5IV; //guardamos el vector de interrupciones. De paso, al acceder a este vector, se limpia automaticamente.

    /*
     * 5.1 BOTO S1 FLAG: 0x04
     * 5.4 JOYSTICK UP FLAG: 0x0A
     * 5.5 JOYSTICK DOWN FLAG: 0x0C
     */

    P5IE &= ~(BIT4 + BIT5 + BIT1);  //Interrupciones desactivadas
    if (flag == 0x0A)
    {
        //Jstick_Up; //pin 4
        if (linia_seleccionada - 1 >= 1)
        {
            linia_seleccionada--;
        }
        estat_anterior_pantalla = 0;
        estat_pantalla = MENU_PRINCIPAL;
    }
    else if (flag == 0x0C)
    {
        //Jstick_Down; //pin5
        if (linia_seleccionada + 1 <= NUM_LINIES_MENU)
        {
            linia_seleccionada++;
        }
        estat_anterior_pantalla = 0;
        estat_pantalla = MENU_PRINCIPAL;
    }

    else if (flag == 0x04)
    {  //5.1

        switch (linia_seleccionada)
        {
        case 0:
            // Aquest cas és que s'ha premut el botó per primer cop per obrir el menú (no tornarà a entrar més)

            comencar = 0; // Si estem treballant amb el menu per primer cop el robot ha de parar.
            linia_seleccionada = 1;
            estat_anterior_pantalla = 0;
            estat_pantalla = MENU_PRINCIPAL;
            break;

        case 1:
            comencar = comencar ? 0 : 1;

            if(parar == 0 && comencar == 1){
                parar = 1;
            }
            estat_anterior_pantalla = 0;
            estat_pantalla = MENU_PRINCIPAL;
            break;
        case 2:
            //podem calibrar tantes vegades com vulguem
            calibrat = PENDENT_CALIBRAR;  // Volem calibrar
            estat_anterior_pantalla = 0;
            estat_pantalla = MENU_PRINCIPAL;

            break;

        case 3:
            resseguim_default =
                    resseguim_default ?
                    RESSEGUIM_PARET_ENGANXAT_A_ESQUERRA :
                                        RESSEGUIM_PARET_ENGANXAT_A_DRETA; // 0 esquerra, 1 dreta
            estat_anterior_pantalla = 0;
            estat_pantalla = MENU_PRINCIPAL;
            break;

        case 4:

            musica = musica ? MUSICA_OFF : MUSICA_ON; // Invertim
            estat_anterior_pantalla = 0;
            estat_pantalla = MENU_PRINCIPAL;
            break;

        default:
            break;
        }

    }

    // Forcem actualització de pantalla

    P5IE |= BIT4 + BIT5 + BIT1;    //Interrupciones reactivadas
}

