#include "systick.h"

#define CTRL_ENABLE	 	(1U << 0)
#define CTRL_TICKINT 	(1U << 1)
#define CTRL_CLKSRC		(1U << 2)

#define ONE_SEC_LOAD 16000000 // 16M

void systick_1hz_interrupt() {
	// configure reload value register
	SysTick->LOAD = ONE_SEC_LOAD - 1;

	// clear current value register
	SysTick->VAL = 0;

	// enable SYSTICK and select internal clock source
	SysTick->CTRL = CTRL_CLKSRC | CTRL_ENABLE;

	// enable SYSTICK interrupt
	SysTick->CTRL |= CTRL_TICKINT;
}
