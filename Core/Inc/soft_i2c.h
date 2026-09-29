#ifndef __SOFT_I2C_H
#define __SOFT_I2C_H
#include "main.h"
void DWT_Init(void);
void delay_us(uint32_t us);
void w_scl(uint8_t bitvalue);
void w_sda(uint8_t bitvalue);
uint8_t r_sda(void);
void soft_i2c_start(void);
void soft_i2c_stop(void);
void soft_i2c_sendbyte(uint8_t byte);
uint8_t soft_i2c_receivebyte(void);
void sendack(uint8_t bit);
uint8_t receiveack(void);




#endif



