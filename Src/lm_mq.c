#include "adc.h"
#include "lm_mq.h"
#include <stdint.h>
static uint16_t rl  =  200;   // load ressistance
static uint16_t vcc = 5000;   // input volatge
static uint16_t r0  = 1;      // to be defined

uint16_t lm35_data(uint16_t lm35_value){


	float mv_lm35 =   (( (float)lm35_value * 3300)/ 4095);
	        float temp    =(mv_lm35 /10);
	        return temp;
}

uint16_t mq3_data(uint16_t mq3_value){
uint16_t mv_mq3  = (( mq3_value * 3300)/ 4095);
        uint16_t v5_mq3  = ((mv_mq3* 25)/ 15);  // as we use volatage devide so we are adding that volatage //
        uint16_t rs      = (rl* (vcc - v5_mq3)/ v5_mq3);
          uint16_t mq3_out = ((rs*100 )/ r0);
          return mq3_out ;
}
