/*
 * i2c.h
 *
 *  Created on: Oct 13, 2026
 *      Author: Mahi
 */

#ifndef I2C_H_
#define I2C_H_
#include<stdio.h>
#include<stm32f4xx.h>

void i2c_init(void);

void i2c_write_byte(uint8_t saddr, uint8_t maddr, uint8_t *data);
void i2c_read_burst(uint8_t saddr, uint8_t maddr, uint8_t *data, uint8_t n);

#endif /* I2C_H_ */
