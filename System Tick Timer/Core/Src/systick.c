#include "stm32f4xx.h"

#define SYSTICK_LOAD_VAL 	16000
#define CTRL_ENABLE			(1U << 0)
#define CTRL_CLKSRC			(1U << 2)
#define CTRL_COUNTFLAG		(1U << 16)

void systickDelayMs(int n) {
	// configure reload value register
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// clear current value register
	SysTick->VAL = 0;

	// enable SYSTICK and select clock source
	SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC;

	// delay loop
	for (int i = 0; i < n; i++) {
		while (!(SysTick->CTRL & CTRL_COUNTFLAG));
	}

	// disable SYSTICK
	SysTick->CTRL = 0;
}
