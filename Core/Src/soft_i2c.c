#include "soft_i2c.h"
void DWT_Init(void)
{
CoreDebug->DEMCR|=CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL|=DWT_CTRL_CYCCNTENA_Msk;
}
void delay_us(uint32_t us)
{

uint32_t startTick=DWT->CYCCNT;
	uint32_t dealyTicks=us*(SystemCoreClock/1000000);
	while((DWT->CYCCNT-startTick)<dealyTicks);
}
void w_scl(uint8_t bitvalue)
{
if(bitvalue==1)
	{HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);
  delay_us(1);}
else
	{HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);
 delay_us(1);}
}

void w_sda(uint8_t bitvalue)
{
if(bitvalue==1)
	{HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_SET);
	delay_us(1);}
else
{	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2,GPIO_PIN_RESET);
  delay_us(1);}
}
uint8_t r_sda(void)
{
 uint8_t bitvalue;
	bitvalue=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2);
	delay_us(1);
  return bitvalue;
}

void soft_i2c_start(void)
{
	w_sda(1);
	w_scl(1);
	w_sda(0);
	w_scl(0);
}
void soft_i2c_stop(void)
{
	w_sda(0);
w_scl(1);
w_sda(1);
}
void soft_i2c_sendbyte(uint8_t byte)
{uint8_t i;
	for(i=0;i<8;i++)
{
w_sda((byte&((0x80)>>i))>>(7-i));
w_scl(1);
w_scl(0);
}
}
uint8_t soft_i2c_receivebyte(void)
{
	
	uint8_t i, byte=0x00;
	w_sda(1);
	for(i=0;i<8;i++)
	{
		w_scl(1);
 if(r_sda()==1) byte|=(0x80>>i);
	w_scl(0);
	}
	return byte;
}
void sendack(uint8_t bit)
{
w_sda(bit);
w_scl(1);
w_scl(0);
}
uint8_t receiveack(void)
{
	uint8_t ackbit;
w_sda(1);
w_scl(1);
	ackbit=r_sda();
	w_scl(0);
	return ackbit;
}



