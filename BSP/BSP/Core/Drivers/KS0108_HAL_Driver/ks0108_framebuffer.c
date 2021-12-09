

#include "..\Common\Inc\display.h"
//#include "Inc\ks0108_low_level.h"
//#include "Inc\ks0108_phy.h"
//#include "Inc\ks0108_config.h"
//#include "Inc\ks0108_framebuffer.h"

#ifdef DY_KS0108

//Frame Buffer
uint8_t ks1808_FrameBuffer[DY_KS0108_PAGES][DY_KS0108_SCR_WIDTH];

uint8_t cs,page,point;

uint8_t* ks1808_FrameBuffPosition(uint8_t page,uint8_t col)
{
	return &ks1808_FrameBuffer[page][col];
}

void ks0108_dy_Refresh_all(void)
{
#ifdef FRAME_BUFFER
	for(page=0;page<DY_KS0108_PAGES;page++)
	{
		for(point=0;point<DY_KS0108_SCR_WIDTH;point++)
		{
			if ((point&(DY_KS0108_WIDTH-1))==0)
			{
				cs=(point/DY_KS0108_WIDTH)+1;
				ks0108_set_CS_signal(cs);
				ks0108_write_instruction(X_ADDRESS | page);
				ks0108_write_instruction(Y_ADDRESS);	// column 0
			}
			ks0108_write_data(FrameBuffer[page][point]);
		}
	}
#endif
}

void ks0108_dy_Refresh(uint8_t x,uint8_t y,uint8_t width,uint8_t heigth)
{
#ifdef FRAME_BUFFER
	uint8_t page_start;
	uint8_t page_end;
	if (((x+width)>DY_KS0108_SCR_WIDTH) || ((y+heigth)>DY_KS0108_SCR_HEIGHT))
		return;
	page_start=y/8;
	page_end=(y+heigth)/8;
	for(page=page_start;page<=page_end;page++)
	{
		cs=(x/DY_KS0108_WIDTH)+1;
		ks0108_set_CS_signal(cs);
		ks0108_write_instruction(X_ADDRESS | page);
		ks0108_write_instruction(Y_ADDRESS | x);	// column 0
		for(point=0;point<width;point++)
		{
			if (((point+x)&(DY_KS0108_WIDTH-1))==0)
			{
				cs=((point+x)/DY_KS0108_WIDTH)+1;
				ks0108_set_CS_signal(cs);
				ks0108_write_instruction(X_ADDRESS | page);
				ks0108_write_instruction(Y_ADDRESS | 0);	// column 0
			}
			ks0108_write_data(FrameBuffer[page][x+point]);
		}
	}
#endif
}

#endif //DY_KS0108
