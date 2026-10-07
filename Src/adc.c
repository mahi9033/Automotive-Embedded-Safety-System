#include "adc.h"

volatile uint8_t adc_done = 0;
volatile uint8_t adc_idx = 0;

volatile uint16_t lm35_value = 0;
volatile uint16_t mq3_value = 0;

#define GPIOAEN                 (1U << 0)
#define ADC1EN                  (1U << 8)
#define SR_EOC                  (1U << 1)
#define CR1_EOCIE               (1U << 5)
#define CR2_EOCS                (1U << 10)

 void adc1_init(void)
 {
	 /*************GPIO_CONFIGRATION*************/

	 /* Enable Clock For Pins  */
	 RCC->AHB1ENR |= GPIOAEN;

	 /* Set Mode as Analog Pin  */
	 GPIOA->MODER |= (1U << 6);
	 GPIOA->MODER |= (1U << 7);

	 GPIOA->MODER |= (1U << 14);
	 GPIOA->MODER |= (1U << 15);

	 /* Set Input For MQ3 activation */
	 GPIOA->MODER &= ~(1U << 8);
	 GPIOA->MODER &= ~(1U << 8);



	 /**************ADC_CONFIGRATION***************/
	 /* Enable Clock For ADC1 */
	 RCC->APB2ENR |= ADC1EN;

	 /* Set the sequence length */
	 ADC1->SQR1 |=  (1U << 20);
	 ADC1->SQR1 &= ~(1U << 21);
	 ADC1->SQR1 &= ~(1U << 22);
	 ADC1->SQR1 &= ~(1U << 23);

	 /* Set the sequence in ch3 and ch7 */
	       /*CH3*/
	 ADC1->SQR3 |=  (1U << 0);
	 ADC1->SQR3 |=  (1U << 1);
	 ADC1->SQR3 &= ~(1U << 2);
	 ADC1->SQR3 &= ~(1U << 3);

           /*CH7*/
	 ADC1->SQR3 |=  (1U << 4);
	 ADC1->SQR3 |=  (1U << 5);
	 ADC1->SQR3 |=  (1U << 6);
	 ADC1->SQR3 &= ~(1U << 7);

	 /* SET 12 bit Resolution */
	 ADC1->CR1 &= ~(1U << 24);
	 ADC1->CR1 &= ~(1U << 25);

	 /* Enable end of conversion Interupt for adc   */
	 ADC1->CR1 |= CR1_EOCIE;

	 /* ENBLE EOCS FOR CONVERSION SELECTION */
	 ADC1->CR2 |=CR2_EOCS;

	 /* Enable adc */
	 ADC1->CR2 |= (1 << 0);

	 NVIC_EnableIRQ(ADC_IRQn);


	 }

 void adc_start_conv(void)
 {
	 ADC1->CR2 |= ADC_CR2_SWSTART;
 }


 void ADC_IRQHandler(void)
 {

if(GPIOA->IDR & (1U << 4))
{
	if(!(ADC1->SR & SR_EOC)){}

	uint16_t value = (uint16_t)ADC1->DR;
	if(adc_idx == 0)
	{
		lm35_value = value;
		adc_idx = 1;
	}
	else
	{
		mq3_value = value;
		adc_idx = 0;
		adc_done = 1;
	}
}
	else
	{
		if(!(ADC1->SR & SR_EOC)){};

		uint16_t value = (uint16_t)ADC1->DR;
		if(adc_idx == 0)
		{
			lm35_value = value;
			adc_idx = 1;
		}
	}
 }


















