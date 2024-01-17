#include "uart.h"

#define GPIOAEN			(1U<<0)
#define UART2EN			(1U<<17)

#define CR1_TE			(1U<<3)
#define CR1_RE			(1U<<2)

#define CR1_UE			(1U<<13)
#define CR1_RXNEIE		(1U<<5)

#define SYS_FREQ		16000000
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE	115200

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);

void uart2_rx_interrupt_init() {
	__disable_irq();
	/* configure GPIO */
	// enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// set PA3 mode to alternate function mode
	GPIOA->MODER &= ~(1U << 6);
	GPIOA->MODER |= (1U << 7);

	// set PA3 alternate function type to UART_RX (AF07)
	GPIOA->AFR[0] |= (1U << 12);
	GPIOA->AFR[0] |= (1U << 13);
	GPIOA->AFR[0] |= (1U << 14);
	GPIOA->AFR[0] &= ~(1U << 15);

	/* configure UART module */
	// enable clock access to UART2
	RCC->APB1ENR |= UART2EN;

	// configure baud rate
	uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

	// configure transfer direction
	USART2->CR1 =  CR1_RE;

	// enable RXNE interrupt
	USART2->CR1 |= CR1_RXNEIE;

	// enable UART2 interrupt in NVIC
	NVIC_EnableIRQ(USART2_IRQn);

	// enable UART2 module'
	USART2->CR1 |= CR1_UE;
	__enable_irq();
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk,  uint32_t BaudRate) {
	USARTx->BRR =  compute_uart_bd(PeriphClk,BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate) {
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}
