/*
 * aplic_led.h
 *
 *  Created on: 2 may. 2024
 *      Author: janaccensimarch
 */

#ifndef APLIC_LED_H_
#define APLIC_LED_H_

#include "config_transport.h"

struct RxReturn encendreLED(byte id);
struct RxReturn apagarLED(byte id);

#endif /* APLIC_LED_H_ */
