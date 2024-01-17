#include "stm32f4xx.h"
#include "timer.h"

int main() {
	tim2_pa5_output_compare();

	while (1) ;

	return 0;
}
