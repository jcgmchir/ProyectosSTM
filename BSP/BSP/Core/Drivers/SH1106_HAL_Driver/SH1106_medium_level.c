#include "..\Common\Inc\display.h"


#ifdef DY_SH1106

void sh1106_init_display(void);
void sh1106_set_contrast(uint8_t contrast);
void sh1106_clear_screen(void);
void sh1106_enable_sleep(void);
void sh1106_disable_sleep(void);
void sh1106_invert(uint8_t mode);

static uint8_t Contraste;

void sh1106_init_display(void)
{
	uint8_t val;
	sh1106_write_instruction(SH1106_DISPLAY_OFF,NULL,0);
	val=0x50;
	sh1106_write_instruction(SH1106_DIS_CLOCK_DIV_RT,&val,1);
	val=0x3F;
	sh1106_write_instruction(SH1106_SET_MUX_RATIO,&val,1);
	val=0x00;
	sh1106_write_instruction(SH1106_DISPLAY_OFFSET,&val,1);
	val=0x00;
	sh1106_write_instruction(SH1106_SET_START_LINE|val,NULL,0);
	sh1106_write_instruction(SH1106_SEG_REMAP_L_ROT,NULL,0);
	sh1106_write_instruction(SH1106_COM_SCAN_DIR_REV,NULL,0);
	val=SH1106_COM_PADS_CONF_ALT;
	sh1106_write_instruction(SH1106_COM_PADS_CONF,&val,1);
	val=0x7F;
	sh1106_write_instruction(SH1106_SET_CONTRAST,&val,1);
	val=0xf1;
	sh1106_write_instruction(SH1106_SET_PRECHARGE,&val,1);
	val=0x40;
	sh1106_write_instruction(SH1106_VCOM_DESELECT,&val,1);
	sh1106_write_instruction(SH1106_DIS_REFLECTS_RAM,NULL,0);
	sh1106_write_instruction(SH1106_DISPLAY_ON,NULL,0);
	sh1106_write();
}

void sh1106_set_contrast(uint8_t contrast)
{
	uint8_t val;
	val=0x7F;
	sh1106_write_instruction(SH1106_SET_CONTRAST,&val,1);
	sh1106_write();
	Contraste=contrast;
}

void sh1106_enable_sleep(void)
{
	//Don' have this mode
	sh1106_write_instruction(SH1106_DISPLAY_OFF,NULL,0);
	sh1106_write();
}

void sh1106_disable_sleep(void)
{
	//Don' have this mode
	sh1106_write_instruction(SH1106_DISPLAY_ON,NULL,0);
	sh1106_write();
}

void sh1106_clear_screen(void)
{
	uint16_t i;
	uint8_t j;
	uint8_t buffer[DY_SH1106_SCR_WIDTH];
	for (i=0;i<DY_SH1106_PAGES;i++)
	{
		for (j=0;j<DY_SH1106_SCR_WIDTH;j++)
			buffer[j]=0;
		sh1106_write_instruction(SH1106_SET_PAGE_ADRESS|i,NULL,0);
		sh1106_write_instruction(SH1106_SET_LOWER_COLUMN|DY_LEFT_MARGIN,NULL,0);
		sh1106_write_instruction(SH1106_SET_HIGHER_COLUMN,NULL,0);
		sh1106_write_ndata(buffer,DY_SH1106_SCR_WIDTH);
		sh1106_write();
	}
}

void sh1106_invert(uint8_t mode)
{
	if (mode==MODE_INVERTED)
		sh1106_write_instruction(SH1106_DIS_INVERSE,NULL,0);
	else
		sh1106_write_instruction(SH1106_DIS_NORMAL,NULL,0);
	sh1106_write();
}

#endif //DY_SH1106
