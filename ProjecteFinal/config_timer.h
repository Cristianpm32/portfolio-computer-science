#ifndef CONFIG_TIMER_H_
#define CONFIG_TIMER_H_

#include "definicions.h"

void init_timers(void);


void Reset_Timeout(void);


int TimeOut(int desenes_microsec);

void espera(int t);


#endif /* CONFIG_TIMER_H_ */
