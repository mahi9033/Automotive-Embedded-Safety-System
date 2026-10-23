/*
 * gps.h
 *
 *  Created on: Oct 8, 2026
 *      Author: Mahi
 */

#ifndef GPS_H_
#define GPS_H_

#include "stm32f4xx.h"
#include <stdint.h>
#include "uart.h"

void gps_buffer(uint8_t data);

#endif /* GPS_H_ */
