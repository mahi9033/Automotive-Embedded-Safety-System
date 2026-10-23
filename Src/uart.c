#include "uart.h"
#include "gps.h"
#define  GPIOAEN          (1U << 0)
#define  USART1EN         (1U << 4)
#define  CR1_RXNEIE       (1U << 5)
#define  CR1_RE           (1U << 2)
#define  CR1_UE           (1U << 13)

void uart_gpio_init(void){

	/*******GPIO_CONFIGRATION*******/

	/* Enable the clock for GPIOA */
	RCC->AHB1ENR |=GPIOAEN;

	/* SET The Moder as alternate */
	GPIOA->MODER &= ~(3U << 20);
	GPIOA->MODER |=  (2U << 20);

	/* SET Alternate function as uart Rx */
	GPIOA->AFR[1] &= ~(0xFU << 8);
	GPIOA->AFR[1] |=  (7U << 8);

	/*******UART_CONFIGRATION*******/

	/* Enable Clock for USART2 */
	RCC->APB2ENR |= USART1EN;
	/* set the baud rate for usart */
    USART1->BRR = 521;

    /* Enable the Reciever */
    USART1->CR1 |= CR1_RE;

    /* ENABLE RX INTERUPT */
    USART1->CR1 |= CR1_RXNEIE;

    NVIC_EnableIRQ(USART1_IRQn);

    /* enable the USART  */
    USART1->CR1 |= CR1_UE;
}

void USART1_IRQHandler(void)
{
    if (USART1->SR & USART_SR_RXNE)
    {
        uint8_t data = (uint8_t)USART1->DR;
        gps_buffer(data);
    }
}






















