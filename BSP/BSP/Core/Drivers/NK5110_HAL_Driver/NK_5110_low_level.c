
#include "..\Common\Inc\display.h"

//#include "../NK5110_HAL_Driver/Inc/NK_5110_low_level.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_phy.h"
//#include "Inc\nk_5110_config.h"


#ifdef DY_NK5110

extern void nk5110_write_instruction(uint8_t cmd);
extern void nk5110_write_data(uint8_t data);
extern void nk5110_write_ndata(uint8_t *data,uint16_t nsize);
extern uint8_t nk5110_read_data(void);
extern void nk5110_no_busy(void);
extern void nk5110_reset(void);
extern void nk5110_backlight(uint8_t state);



extern void nk5110_write_instruction(uint8_t cmd)
{
	nk5110_set_signal(NK5110_PLCD_DC,LCD_COMMAND);
	nk5110_set_signal(NK5110_PLCD_CE,0);
	nk5110_write_display(&cmd,1);
	nk5110_set_signal(NK5110_PLCD_CE,1);
}
extern void nk5110_write_data(uint8_t data)
{
	nk5110_set_signal(NK5110_PLCD_DC,LCD_DATA);
	nk5110_set_signal(NK5110_PLCD_CE,0);
	nk5110_write_display(&data,1);
	nk5110_set_signal(NK5110_PLCD_CE,1);
}
extern void nk5110_write_ndata(uint8_t *data,uint16_t nsize)
{
	nk5110_set_signal(NK5110_PLCD_DC,LCD_DATA);
	nk5110_set_signal(NK5110_PLCD_CE,0);
	nk5110_write_display(data,nsize);
	nk5110_set_signal(NK5110_PLCD_CE,1);
}

extern uint8_t nk5110_read_data(void)
{
	return(0);
}

extern void nk5110_no_busy(void)
{

}

extern void nk5110_reset(void)
{
	nk5110_set_signal(NK5110_PLCD_RST,0);
	HAL_Delay(10);
	nk5110_set_signal(NK5110_PLCD_RST,1);
}

extern void nk5110_backlight(uint8_t state)
{
	nk5110_set_signal(NK5110_PLCD_BACKLIGHT,(~state)&0x01);
}

#endif //DY_NK5110
