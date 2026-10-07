/*
 * seatbelt.h
 *
 *  Created on: Oct 7, 2026
 *      Author: Mahi
 */

#ifndef SEATBELT_H_
#define SEATBELT_H_

#include "stm32f4xx.h"
#include <stdint.h>

void seatbelt_gpio_init(void);
uint8_t seatbelt_status(void);

#endif /* SEATBELT_H_ */
