#include "seatbelt.h"


#define GPIOAEN          (1U << 0)

void seatbelt_gpio_init(void)
{
	/* Enable Clock for GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/* Set ModeR  as Input For PA0 */
	GPIOA->MODER &= ~(1U << 0);
	GPIOA->MODER &= ~(1U << 1);

	/* Pull Down the Pin */
	GPIOA->PUPDR |=  (1U << 1);
	GPIOA->PUPDR &= ~(1U << 1);

}

uint8_t seatbelt_status(void)
{
	if(GPIOA->IDR & (1U < 0))
	{
		return 1U;
	}
	else{
		return 0U;
	}
}

// here take only seatbelt_status

