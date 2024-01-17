#include "uart.h"

/* UART */
#define GPIOAEN (1U << 0)
#define UART2EN (1U << 17)

#define CR1_TE 		(1U << 3) // Transmitter enable
#define CR1_UE 		(1U << 13) // UART enable
#define CR3_DMAT 	(1U << 7) // DMA transmitter
#define SR_TXE		(1U << 7)

#define SYS_FREQ 16000000
#define APB1_CLK SYS_FREQ
#define UART_BAUDRATE 115200

/* DMA */
#define DMA1EN 		(1U << 21)

#define DMA_CR_EN 				(1U << 0)
#define DMA_CR_TCIE 				(1U << 4) // transfer complete interrupt
#define DMA_CR_DIR_MEM_TO_PERIPH 	(1U << 6) // direction
#define DMA_CR_MINC 				(1U << 10) // memory increment
#define DMA_CR_CHSEL_4 				(1U << 27) // channel selection

void uart2_write(int ch);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);

// override printf's internal function
int __io_putchar(int ch) {
	uart2_write(ch);
	return ch;
}

void uart2_tx_init() {
	/* configure GPIO pin */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA2 mode to alternate function (10)
	GPIOA->MODER &= (1U << 4);
	GPIOA->MODER |= (1U << 5);

	// set alternate function type to UART_TX (AF07 0111)
	GPIOA->AFR[0] |= (1U << 8);
	GPIOA->AFR[0] |= (1U << 9);
	GPIOA->AFR[0] |= (1U << 10);
	GPIOA->AFR[0] &= ~(1U << 11);

	/* configure UART module */
	// enable clock access to UART2
	RCC->APB1ENR |= UART2EN;

	// configure baud rate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction
	USART2->CR1 = CR1_TE;

	// enable UART2 TX DMA
	USART2->CR3 |= CR3_DMAT;

	// enable UART module
	USART2->CR1 |= CR1_UE;
}

void dma1_stream6_init(uint32_t src,uint32_t dst, int len) {
	// enable clock access to DMA1
	RCC->AHB1ENR |= DMA1EN;

	// disable DMA1 stream 6 (read 0 to configure other registers)
	DMA1_Stream6->CR &= ~DMA_CR_EN;

	// clear all stream 6 interrupt flags (high interrupt flag clear register)
	DMA1->HIFCR |= (1U << 16);
	DMA1->HIFCR |= (1U << 18);
	DMA1->HIFCR |= (1U << 19);
	DMA1->HIFCR |= (1U << 20);
	DMA1->HIFCR |= (1U << 21);

	// set source buffer (memory 0 address register)
	DMA1_Stream6->M0AR = src;
	// set destination buffer (peripheral address register)
	DMA1_Stream6->PAR = dst;
	// set data length
	DMA1_Stream6->NDTR = len;

	// select stream 6 channel 4
	DMA1_Stream6->CR |= DMA_CR_CHSEL_4;
	// enable memory increment
	DMA1_Stream6->CR |= DMA_CR_MINC;
	// configure transfer direction
	DMA1_Stream6->CR |= DMA_CR_DIR_MEM_TO_PERIPH;
	// enable DMA transfer complete interrupt
	DMA1_Stream6->CR |= DMA_CR_TCIE;
	// enable direct mode
	DMA1_Stream6->FCR = 0;

	// enable DMA1 stream 6
	DMA1_Stream6->CR |= DMA_CR_EN;

	// enable DMA interrupt in NVIC
	NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void uart2_write(int ch) {
	// make sure transmit data register is empty
	while (!(USART2->SR & SR_TXE));

	USART2->DR = (ch & 0xFF); // 1 byte
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {
	return (PeriphClk + (BaudRate / 2U)) / BaudRate;
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate) {
	USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
}



