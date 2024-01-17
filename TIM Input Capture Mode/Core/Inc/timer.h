#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#define SR_CC1IF (1U << 1)

void tim2_1hz_pa5_output_compare();
void tim3_pa6_input_capture();

#endif
