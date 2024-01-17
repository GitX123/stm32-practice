#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN (1U << 0)
#define PIN5 	(1U << 5)
#define LED_PIN PIN5

static void dma_callback();

int main() {
	char message[31] = "Hello STM32\n\r";

	// set PA5 as output pin
	RCC->AHB1ENR |= GPIOAEN;
	GPIOA->MODER |= (1U << 10);
	GPIOA->MODER &= ~(1U << 11);

	uart2_tx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t) &USART2->DR, 31);

	while (1) {
		dma_callback();
	}

	return 0;
}

static void dma_callback() {
	for (int i = 0; i < 5; i++) {
		GPIOA->ODR ^= LED_PIN;
		for (int i = 0; i< 1000000 ; i++);
		GPIOA->ODR ^= LED_PIN;
		for (int i = 0; i< 1000000 ; i++);
	}
}

void DMA1_Stream6_IRQHandler() {
	if (DMA1->HISR & HISR_TCIF6) {
		// clear stream6 transfer complete interrupt flag
		DMA1->HIFCR |= HIFCR_CTCIF6;

	}
	dma_callback();
}

