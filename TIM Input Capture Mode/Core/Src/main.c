#include <stdint.h>
#include "stm32f4xx.h"
#include "timer.h"

int counter;

int main(void)
{
	tim2_1hz_pa5_output_compare();
	tim3_pa6_input_capture();

	while (1) {
		// wait until value is captured
		while (!(TIM3->SR & SR_CC1IF));

		// read captured value
		counter = TIM3->CCR1;
	}
}
