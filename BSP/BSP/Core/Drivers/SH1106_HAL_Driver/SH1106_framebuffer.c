#include "..\Common\Inc\display.h"

#ifdef DY_SH1106

//Frame Buffer
uint8_t sh1106_FrameBuffer[DY_SH1106_PAGES][DY_SH1106_SCR_WIDTH];

uint8_t cs,page,point;

uint8_t* sh1106_FrameBuffPosition(uint8_t page,uint8_t col)
{
	return &sh1106_FrameBuffer[page][col];
}

void sh1106_dy_Refresh_all(void)
{
	uint16_t i;
	uint8_t *buffer;
	for (i=0;i<DY_SH1106_PAGES;i++)
	{
		buffer=&sh1106_FrameBuffer[i][0];
		sh1106_write_instruction(SH1106_SET_PAGE_ADRESS|i,NULL,0);
		sh1106_write_instruction(SH1106_SET_LOWER_COLUMN|DY_LEFT_MARGIN,NULL,0);
		sh1106_write_instruction(SH1106_SET_HIGHER_COLUMN,NULL,0);
		sh1106_write_ndata(buffer,DY_SH1106_SCR_WIDTH);
		sh1106_write();
	}
}

void sh1106_dy_Refresh(Frame_t frm)
{
	uint8_t page_start;
	uint8_t page_end;
	uint8_t *buffer;
	if (((frm.p.x+frm.width)>DY_SH1106_SCR_WIDTH) || ((frm.p.y+frm.height)>DY_SH1106_SCR_HEIGHT))
		return;
	page_start=frm.p.y/8;
	page_end=(frm.p.y+frm.height)/8;
	for(page=page_start;page<=page_end;page++)
	{
		buffer=&sh1106_FrameBuffer[page][frm.p.x];
		sh1106_write_instruction(SH1106_SET_PAGE_ADRESS|page,NULL,0);
		sh1106_write_instruction(SH1106_SET_LOWER_COLUMN|((frm.p.x+DY_LEFT_MARGIN)&0x0F),NULL,0);
		sh1106_write_instruction(SH1106_SET_HIGHER_COLUMN|(((frm.p.x+DY_LEFT_MARGIN)&0xF0)>>4),NULL,0);
		sh1106_write_ndata(buffer,frm.width);
		sh1106_write();
	}
}

#endif //DY_SH1106
