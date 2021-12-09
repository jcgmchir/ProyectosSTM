#include "..\Common\Inc\display.h"

//#include "../NK5110_HAL_Driver/Inc/NK_5110_framebuffer.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_config.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_low_level.h"
//#include "../NK5110_HAL_Driver/Inc/NK_5110_phy.h"

#ifdef DY_NK5110

//Frame Buffer
uint8_t nk5110_FrameBuffer[DY_NK5110_PAGES][DY_NK5110_SCR_WIDTH];

uint8_t cs,page,point;

uint8_t* nk5110_FrameBuffPosition(uint8_t page,uint8_t col)
{
	return &nk5110_FrameBuffer[page][col];
}

void nk5110_dy_Refresh_all(void)
{
	nk5110_write_instruction(PCD8544_SETXADDR); // column 0
	nk5110_write_instruction(PCD8544_SETYADDR);	//Fila 0
	nk5110_write_ndata(&nk5110_FrameBuffer[0][0],DY_NK5110_PAGES*DY_NK5110_SCR_WIDTH);
}

void nk5110_dy_Refresh(Frame_t frm)
{
	uint8_t page_start;
	uint8_t page_end;
	uint8_t point;

	if (((frm.p.x+frm.width)>DY_NK5110_SCR_WIDTH) || ((frm.p.y+frm.height)>DY_NK5110_SCR_HEIGHT))
		return;
	page_start=frm.p.y/8;
	page_end=(frm.p.y+frm.height)/8;
	for(page=page_start;page<=page_end;page++)
	{
		nk5110_write_instruction(PCD8544_SETYADDR | page);
		nk5110_write_instruction(PCD8544_SETXADDR | frm.p.x);	// column 0
		for(point=0;point<frm.width;point++)
			nk5110_write_data(nk5110_FrameBuffer[page][frm.p.x+point]);
	}
}

#endif //DY_NK5110
