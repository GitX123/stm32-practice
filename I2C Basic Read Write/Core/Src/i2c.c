#include "i2c.h"

#define GPIOBEN (1U << 1)

#define I2C1EN 		(1U << 21)
#define CR1_SWRST 	(1U << 15)
#define CCR_100KHZ 	80 // 0B 0101 0000

void i2c1_init(void) {
	/* GPIO setup */
	// enable clock access to GPIOB
	RCC->AHB1ENR |= GPIOBEN;

	// set PB8 and PB9 mode to alternate function
	GPIOB->MODER &= ~(1U << 16);
	GPIOB->MODER |= (1U << 17);
	GPIOB->MODER &= ~(1U << 18);
	GPIOB->MODER |= (1U << 19);

	// set PB8 and PB9 alternate function type to I2C (AF4)
	GPIOB->AFR[1] &= ~(1u << 0);
	GPIOB->AFR[1] &= ~(1u << 1);
	GPIOB->AFR[1] |= (1u << 2);
	GPIOB->AFR[1] &= ~(1u << 3);

	GPIOB->AFR[1] &= ~(1u << 4);
	GPIOB->AFR[1] &= ~(1u << 5);
	GPIOB->AFR[1] |= (1u << 6);
	GPIOB->AFR[1] &= ~(1u << 7);

	// set PB8 and PB9 output type to open drain
	GPIOB->OTYPER |= (1U << 8);
	GPIOB->OTYPER |= (1U << 9);

	// enable pull-up for PB8 and PB9
	GPIOB->PUPDR |= (1U << 16);
	GPIOB->PUPDR &= ~(1U << 17);

	GPIOB->PUPDR |= (1U << 18);
	GPIOB->PUPDR &= ~(1U << 19);

	/* I2C setup */
	// enable clock access to I2C1
	RCC->APB1ENR |= I2C1EN;

	// enter reset mode
	I2C1->CR1 |= CR1_SWRST;
	// exit reset mode
	I2C1->CR1 &= ~CR1_SWRST;

	// set peripheral clock frequency (16MHz)
	I2C1->CR2 = (1U << 4);

	// set to I2C standard mode and 100kHz clock frequency
	I2C1->CCR = CCR_100KHZ;

	// set rise time
	I2C1->TRISE =

	// enable I2C module
}

void i2c1_byteRead(char s_addr, char m_addr, char* data) {

}

void i2c1_burstRead(char s_addr, char m_addr, int n, char* data) {

}

void i2c1_burstWrite(char s_addr, char m_addr, int n, char* data) {

}
