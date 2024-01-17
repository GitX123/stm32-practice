#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

int main() {

	uart2_tx_init();
	while (1) {
		printf("Hello World.\n");
	}

	return 0;
}

