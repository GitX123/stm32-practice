#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f4xx.h"

void i2c1_init(void);
void i2c1_byteRead(char s_addr, char m_addr, char* data);
void i2c1_burstRead(char s_addr, char m_addr, int n, char* data);
void i2c1_burstWrite(char s_addr, char m_addr, int n, char* data);

#endif
