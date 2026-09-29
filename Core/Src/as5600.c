#include "as5600.h"



uint16_t AS5600_ReadRaw(void)
{uint8_t high,low;
	uint16_t degdata;
 soft_i2c_start();
	soft_i2c_sendbyte(0x6C);
	receiveack();

		soft_i2c_sendbyte(0x0E);
	receiveack();
		
	soft_i2c_start();
	soft_i2c_sendbyte(0x6D);
	receiveack();
	high=soft_i2c_receivebyte();
	sendack(0);
	low=soft_i2c_receivebyte();
	sendack(1);
	soft_i2c_stop();
	degdata=(((uint16_t)high&0x0F)<<8)|low;
	return degdata;
}







