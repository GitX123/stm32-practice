#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define HISR_TCIF6 		(1U << 21) // stream 6 transfer complete interrupt flag
#define HIFCR_CTCIF6 	(1U << 21) // stream 6 clear transfer complete interrupt flag

void uart2_tx_init();
void dma1_stream6_init(uint32_t src,uint32_t dst, int len);

#endif
