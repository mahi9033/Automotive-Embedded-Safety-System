#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>

#include "adc.h"
#include "lm_mq.h"
#include "seatbelt.h"

int main(void){

	adc1_init();
	adc_start_conv();
	seatbelt_gpio_init();
	while(1){

     	if (adc_done)
		{
		 float temperature = lm35_data(lm35_value);
		 uint16_t alcohol = mq3_data(mq3_value);

		    adc_done = 0;
		}

     	if(seatbelt_status)
     	{
     		// do some thing //
     	}


}
}
