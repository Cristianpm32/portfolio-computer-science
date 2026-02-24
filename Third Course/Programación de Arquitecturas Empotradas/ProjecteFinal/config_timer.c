
#include <config_timer.h>

void init_timers(void)
{

    /**
     * Timer A1
     * Sense divisió (divisor de 1)
     * FONT: SMCLK
     * CCR0 240 - 1
     * Mode UP
     */
    TIMER_A1->CTL = TIMER_A_CTL_ID__1 | TIMER_A_CTL_SSEL__SMCLK
            | TIMER_A_CTL_CLR | TIMER_A_CTL_MC__UP;
    TIMER_A1->CCR[0] = 240 - 1; // Base de 10 microsegons
    TIMER_A1->CCTL[0] |= TIMER_A_CCTLN_CCIE; //Interrupciones activadas en CCR0

}

int TimeOut(int desenes_microsec)
{

    if (cnt > desenes_microsec)
    {
        return 1;  // Hi ha hagut TimeOut
    }
    else
    {
        return 0; // TOT Ok, No hi ha timeout de moment
    }
}

void Reset_Timeout(void)
{

    cnt = 0;
}

void espera(int t){

    Reset_Timeout();
    int hihaHagutTimeout = 0;

    while(true){
        hihaHagutTimeout = TimeOut(t);
        if(hihaHagutTimeout){
            break;
        }
    }
}



