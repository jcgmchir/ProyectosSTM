
#include "..\Common\Inc\display.h"


#ifdef DY_SH1106

extern void sh1106_write_instruction(uint8_t cmd, uint8_t *data, uint8_t len);
extern void sh1106_write_data(uint8_t data);
extern void sh1106_write_ndata(uint8_t *data,uint16_t nsize);
extern void sh1106_write(void);

extern void sh1106_read_data(uint16_t nsize);

/*command+page+command+column_low+command_high+column+command*/
#define SPARE 10

uint8_t buffer_TX[DY_SH1106_SCR_WIDTH+SPARE];
uint8_t buffer_RX[DY_SH1106_SCR_WIDTH+SPARE];
uint16_t point_TX;
uint16_t point_RX;

void sh1106_write_instruction(uint8_t cmd, uint8_t *data, uint8_t len)
{
	uint8_t i;
	if ((point_TX+len+len+2)<(DY_SH1106_SCR_WIDTH+SPARE))
	{
		buffer_TX[point_TX++]=SH1106_COMMAND;
		buffer_TX[point_TX++]=cmd;
		for (i=0;i<len;i++)
		{
			buffer_TX[point_TX++]=SH1106_COMMAND;
			buffer_TX[point_TX++]=data[i];
		}
	}
}
void sh1106_write_data(uint8_t data)
{
	if ((point_TX+2)<(DY_SH1106_SCR_WIDTH+SPARE))
	{
		buffer_TX[point_TX++]=SH1106_DATA;
		buffer_TX[point_TX++]=data;
	}
}

void sh1106_write_ndata(uint8_t *data,uint16_t nsize)
{
	uint16_t i;
	if ((point_TX+nsize+1)<(DY_SH1106_SCR_WIDTH+SPARE))
	{
		buffer_TX[point_TX++]=SH1106_DATA_STREAM;
		for (i=0;i<nsize;i++)
			buffer_TX[point_TX++]=data[i];
	}
}

void sh1106_write(void)
{
	sh1106_write_display(buffer_TX,point_TX);
	point_TX=0;
}

void sh1106_read_data(uint16_t nsize)
{
	sh1106_read_display(buffer_RX,nsize);
	point_RX=nsize;
}

#endif //DY_SH1106
