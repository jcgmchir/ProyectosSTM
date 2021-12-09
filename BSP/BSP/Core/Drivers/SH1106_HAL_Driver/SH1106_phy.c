
#include "..\Common\Inc\display.h"


#ifdef DY_SH1106

void sh1106_read_display (uint8_t *dato, uint16_t size)
{
	uint32_t timeout;
	timeout=100*size;
	HAL_I2C_Master_Receive(&I2C_DY,SH1106_ADDRESS<<1,dato,size,timeout);
}
HAL_StatusTypeDef status;

void sh1106_write_display (uint8_t *dato, uint16_t size)
{
	uint32_t timeout;
	timeout=TIME_OUT*size;
	status=HAL_I2C_Master_Transmit(&I2C_DY,SH1106_ADDRESS<<1,dato,size,timeout);
}

#endif //DY_SH1106

