#include"i2c.h"

#define GPIOBEN                       (1U << 1)

#define I2C1EN                       (1U << 21)
#define CR1_RSEN                     (1U << 15)
#define SD_MODE_MAX_RISE_TIME        17  // TRISE = Fclk + 1= 16+1=17
#define I2C_100KHz                   80  // CCR = Fclk / (2*fI2C) = 16000000/(2*100000)= 80
#define SR1_ADDR                     (1U << 1)
#define I2C_START                    (1U << 8)
#define I2C_SB                       (1U << 0)
#define SR1_TXE                      (1U << 7)

#define I2CEN       (1U << 0)    // CR1 PE
#define CR1_START   (1U << 8)
#define CR1_STOP    (1U << 9)
#define CR1_ACK     (1U << 10)

#define SR1_SB      (1U << 0)
#define SR1_ADDR    (1U << 1)
#define SR1_BTF     (1U << 2)
#define SR1_RXNE    (1U << 6)
#define SR1_TXE     (1U << 7)

#define SR2_BUSY    (1U << 1)

void i2c_init(void)
{
	/* Enable Clock for I2C1 */
	RCC->AHB1ENR |= GPIOBEN;

	/*Set Pb 8 AND PB 9 AS Alternate Function*/
	GPIOB->MODER |=  (1U << 17);
	GPIOB->MODER &= ~(1U << 16);

	GPIOB->MODER |=  (1U << 19);
	GPIOB->MODER &= ~(1U << 18);

	GPIOB->AFR[1] |= (1U << 2);
	GPIOB->AFR[1] &= ~(1U << 0);
	GPIOB->AFR[1] &= ~(1U << 1);
	GPIOB->AFR[1] &= ~(1U << 3);


	GPIOB->AFR[1] |= (1U << 6);
	GPIOB->AFR[1] &= ~(1U << 4);
	GPIOB->AFR[1] &= ~(1U << 5);
	GPIOB->AFR[1] &= ~(1U << 7);

	/*SET THE PB8 AND PB9 AS open Drain*/
    GPIOB->OTYPER |= (1U << 8);
    GPIOB->OTYPER |= (1U << 9);

    /*pull the PB8 AND PB9*/
    GPIOB->PUPDR  |= (1U << 16);
    GPIOB->PUPDR  &= ~(1U << 17);

    GPIOB->PUPDR  |= (1U << 18);
    GPIOB->PUPDR  &= ~(1U << 19);

    /* Enable clock for i2c */
    RCC->APB2ENR |= I2C1EN;

    /* ENABLE SOFTWARE MODE */
    I2C1->CR1 |= CR1_RSEN;

    /* EXIT from Reset */
    I2C1->CR1 &= ~CR1_RSEN;

	// SET THE PHEP CLK FRQ

	I2C1->CR2 |= (1U << 4);  // 16MHz     01000  = 16

	// SET I2C IN STANDARD MODE, 100Kz //
	I2C1->CCR |=I2C_100KHz;

	//  SET RISE TIME //
	I2C1->TRISE |= SD_MODE_MAX_RISE_TIME;

	// EB=NABLE PHERIP //

	I2C1->CR1 |= I2CEN;


}

void i2c_read_burst(uint8_t saddr, uint8_t maddr, uint8_t *data, uint8_t n)
{
    volatile int tmp;

    // wait until bus is free
    while (I2C1->SR2 & SR2_BUSY){}

    // START
    I2C1->CR1 |= CR1_START;
    while (!(I2C1->SR1 & SR1_SB)){}

    // slave address, write mode
    I2C1->DR = saddr << 1 | 0;
    while (!(I2C1->SR1 & SR1_ADDR)){}
    tmp = I2C1->SR2;                       // clears ADDR
    (void)tmp;
    // register address to read from
    while (!(I2C1->SR1 & SR1_TXE)){}
    I2C1->DR = maddr;
    while (!(I2C1->SR1 & SR1_BTF)){}       // byte fully sent

    // REPEATED START
    I2C1->CR1 |= CR1_START;
    while (!(I2C1->SR1 & SR1_SB)){}

    // slave address, read mode
    I2C1->DR = saddr << 1 | 1;
    while (!(I2C1->SR1 & SR1_ADDR)){}

    // special case: only 1 byte to read
    if (n == 1)
    {
        I2C1->CR1 &= ~CR1_ACK;             // NACK before clearing ADDR
        tmp = I2C1->SR2;                   // clears ADDR
        I2C1->CR1 |= CR1_STOP;
        while (!(I2C1->SR1 & SR1_RXNE)){}
        *data = I2C1->DR;
        return;
    }

    // multi-byte read
    I2C1->CR1 |= CR1_ACK;                  // ACK every byte except the last
    tmp = I2C1->SR2;                       // clears ADDR

    while (n > 0U)
    {
        if (n == 1U)
        {
            I2C1->CR1 &= ~CR1_ACK;         // NACK the last byte
            I2C1->CR1 |= CR1_STOP;         // then STOP
            while (!(I2C1->SR1 & SR1_RXNE)){}
            *data = I2C1->DR;
            break;
        }
        else
        {
            while (!(I2C1->SR1 & SR1_RXNE)){}
            *data++ = I2C1->DR;
            n--;
        }
    }
}


void i2c_write_byte(uint8_t saddr, uint8_t maddr, uint8_t *data)
{
    volatile int tmp;

    while (I2C1->SR2 & SR2_BUSY){}

    I2C1->CR1 |= CR1_START;
    while (!(I2C1->SR1 & SR1_SB)){}

    I2C1->DR = saddr << 1 | 0;
    while (!(I2C1->SR1 & SR1_ADDR)){}
    tmp = I2C1->SR2;
    (void)tmp;

    while (!(I2C1->SR1 & SR1_TXE)){}
    I2C1->DR = maddr;

    while (!(I2C1->SR1 & SR1_TXE)){}
    I2C1->DR = *data;

    while (!(I2C1->SR1 & SR1_BTF)){}
    I2C1->CR1 |= CR1_STOP;
}
















