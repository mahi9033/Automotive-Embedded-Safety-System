/*
 * adc.h
 *
 * Created on: Oct 6, 2026
 * Author: Mahi
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"
#include <stdint.h>

/* ADC functions */
void adc1_init(void);
void adc_start_conv(void);

/* ADC variables */
extern volatile uint8_t adc_done;
extern volatile uint8_t adc_idx;

extern volatile uint16_t lm35_value;
extern volatile uint16_t mq3_value;

#endif /* ADC_H_ */
