#include "..\Common\Inc\display.h"

//#include "../NK5110_HAL_Driver/Inc/NK_5110_config.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_low_level.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_phy.h"

#ifdef DY_NK5110

void nk5110_init_display(void);
void nk5110_set_contrast(uint8_t contrast);
void nk5110_clear_screen(void);
void nk5110_enable_sleep(void);
void nk5110_disable_sleep(void);
void nk5110_invert(uint8_t mode);


static uint8_t Contraste;

void nk5110_init_display(void)
{
	nk5110_reset();
	nk5110_write_instruction(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
	nk5110_write_instruction(PCD8544_SETVOP | LCD_CONTRAST);
	nk5110_write_instruction(PCD8544_SETTEMP | LCD_TEMP);
	nk5110_write_instruction(PCD8544_SETBIAS | LCD_BIAS);
	nk5110_write_instruction(PCD8544_FUNCTIONSET);
	nk5110_clear_screen();
	nk5110_write_instruction(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
	Contraste=LCD_CONTRAST;
}

void nk5110_set_contrast(uint8_t contrast)
{
	if (contrast>0x7F)
		contrast=0x7F;
	if (contrast<0)
		contrast=0;
	Contraste=contrast;
	nk5110_write_instruction(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
	nk5110_write_instruction(PCD8544_SETVOP | Contraste);
	nk5110_write_instruction(PCD8544_FUNCTIONSET);
}

void nk5110_enable_sleep(void)
{
	nk5110_clear_screen();
	nk5110_write_instruction(PCD8544_FUNCTIONSET | PCD8544_POWERDOWN);
}

void nk5110_disable_sleep(void)
{
	nk5110_write_instruction(PCD8544_FUNCTIONSET | PCD8544_EXTENDEDINSTRUCTION);
	nk5110_write_instruction(PCD8544_SETVOP | Contraste);
	nk5110_write_instruction(PCD8544_SETTEMP | LCD_TEMP);
	nk5110_write_instruction(PCD8544_SETBIAS | LCD_BIAS);
	nk5110_write_instruction(PCD8544_FUNCTIONSET);
	nk5110_write_instruction(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

void nk5110_clear_screen(void)
{
	uint16_t c;
	nk5110_write_instruction(PCD8544_SETYADDR);
	nk5110_write_instruction(PCD8544_SETXADDR);
	for (c=0; c<504; c++)
		nk5110_write_data(0x00);

}

void nk5110_invert(uint8_t mode)
{
	if (mode==MODE_INVERTED)
		nk5110_write_instruction(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYINVERTED);
	else
		nk5110_write_instruction(PCD8544_DISPLAYCONTROL | PCD8544_DISPLAYNORMAL);
}

#endif //DY_NK5110
