




#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#include "adc.h"
#include "lm_mq.h"
#include "seatbelt.h"
#include "uart.h"
#include "mpu.h"
float data[3];

static void read_sensors(void)
{
    adc_start_conv();
    while (!adc_done);
}

int main(void)
{
    adc1_init();
    uart_gpio_init();
    seatbelt_gpio_init();
    MPU6050_Init();

    for (uint32_t k = 0; k < 3; k++)
        for (volatile uint32_t i = 0; i < 5000000UL; i++);

    /* calibrate in clean air */
    uint32_t sum = 0;
    for (int i = 0; i < 16; i++)
    {
        read_sensors();
        sum += mq3_value;
    }
    mq3_calibrate((uint16_t)(sum / 16U));

    while (1)
    {
        read_sensors();

        float    temperature = lm35_data(lm35_value) / 10.0f;
        uint16_t alcohol     = mq3_data(mq3_value);

        if (alcohol < 70)
        {
            /* alcohol detected: LED / buzzer / block ignition */
        }

        (void)temperature;   /* remove once you use it */

        if (seatbelt_status())
        {
            /* your seatbelt logic */
        }

     MPU6050_ReadScaled(data);
     float ax = data[0];
     float ay = data[1];
     float az = data[2];


    }
}
