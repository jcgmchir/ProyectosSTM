
#include "..\Common\Inc\display.h"

//#include "../NK5110_HAL_Driver/Inc/NK_5110_phy.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_config.h"

/*Need to define GPIO_PINS
NK5110_CS_DY_GPIO_Port
NK5110_DC_DY_GPIO_Port
NK5110_RESET_DY_GPIO_Port
NK5110_LIGHT_DY_GPIO_Port

NK5110_CS_DY_Pin
NK5110_DC_DY_Pin
NK5110_RESET_DY_Pin
NK5110_LIGHT_DY_Pin
*/

#ifdef DY_NK5110

void nk5110_set_signal(enum nk5110_TGlcdSignal sig, uint8_t value);
void nk5110_write_display (uint8_t *dato, uint16_t size);


void nk5110_set_signal(enum nk5110_TGlcdSignal sig, uint8_t value)
{
	switch(sig)
	{
	case NK5110_PLCD_CE:
		HAL_GPIO_WritePin(NK5110_CS_DY_GPIO_Port,NK5110_CS_DY_Pin, value);
		break;
	case NK5110_PLCD_DC:
		HAL_GPIO_WritePin(NK5110_DC_DY_GPIO_Port, NK5110_DC_DY_Pin, value);
		break;
	case NK5110_PLCD_RST:
		HAL_GPIO_WritePin(NK5110_RESET_DY_GPIO_Port, NK5110_RESET_DY_Pin, value);
		break;
	case NK5110_PLCD_BACKLIGHT:
		if (value==NK5110_BACKLIGHT_ON)
			HAL_GPIO_WritePin(NK5110_LIGHT_DY_GPIO_Port,NK5110_LIGHT_DY_Pin,GPIO_PIN_SET);
			else if (value==NK5110_BACKLIGHT_OFF)
			HAL_GPIO_WritePin(NK5110_LIGHT_DY_GPIO_Port,NK5110_LIGHT_DY_Pin,GPIO_PIN_RESET);
		break;
	}
}

void nk5110_write_display (uint8_t *dato, uint16_t size)
{
    HAL_SPI_Transmit(&NK5110_SPI_DY,dato,size,NK5110_TIME_OUT);
}

#endif //DY_NK5110

