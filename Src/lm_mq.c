#include "lm_mq.h"
#include <stdint.h>
static uint32_t rl  = 200000;   /* load resistor in OHMS: use your module's value */
static uint32_t vcc = 5000;     /* mV */
static uint32_t r0  = 0;        /* set by mq3_calibrate() */

uint16_t lm35_data(uint16_t lm35_value)
{
    return (uint16_t)(((uint32_t)lm35_value * 3300U) / 4095U);
}

 uint32_t mq3_rs(uint16_t raw)
{
    uint32_t pin_mv = ((uint32_t)raw * 3300U) / 4095U;
    uint32_t v_ao   = (pin_mv * 25U) / 15U;

    if (v_ao == 0)    v_ao = 1;
    if (v_ao >= vcc)  v_ao = vcc - 1;

    return (rl * (vcc - v_ao)) / v_ao;
}

void mq3_calibrate(uint16_t avg_raw)
{
    r0 = mq3_rs(avg_raw);
}

uint16_t mq3_data(uint16_t mq3_value)
{
    if (r0 == 0) return 100;
    return (uint16_t)((mq3_rs(mq3_value) * 100U) / r0); // mq3 rs is function not variavle which is multiplied by 100 devided by r0
}
