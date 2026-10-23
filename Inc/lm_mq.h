#ifndef LM_MQ_H_
#define LM_MQ_H_

#include <stdint.h>

uint32_t mq3_rs(uint16_t raw);
void mq3_calibrate(uint16_t avg_raw);
uint16_t mq3_data(uint16_t mq3_value);
uint16_t lm35_data(uint16_t lm35_value);

//uint16_t mq3_data(uint16_t mq3_value);
//void mq3_calibrate(uint16_t avg_raw);
#endif
