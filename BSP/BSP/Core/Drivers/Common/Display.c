/*
 * Display.c
 *
 *  Created on: Dec 8, 2021
 *      Author: jcgmc
 */
#include "Inc/Display.h"
#include "stdlib.h"

void none_reset(void) {}
void none_backlight(uint8_t state) {}

#ifdef DY_SH1106

const struct DY_Interface_t sh1106_itf ={
			 DY_SH1106,
			 &sh1106_dy_Refresh_all,
			 &sh1106_dy_Refresh,
			 &sh1106_init_display,
			 &sh1106_set_contrast,
			 &sh1106_clear_screen,
			 &sh1106_enable_sleep,
			 &sh1106_disable_sleep,
			 &sh1106_invert,
			 &none_reset,
			 &none_backlight,
			 &sh1106_FrameBuffPosition,
			 DY_SH1106_SCR_WIDTH,
			 DY_SH1106_SCR_HEIGHT,
			 &DY_PutPixel,
			 &DY_Line,
			 &DY_Circle,
			 &DY_Rectangle,
			 &DY_PutxBitmap,
			 &DY_HBar,
			 &DY_VBar,
			 &DY_PutFontChar,
			 &DY_PutText
			};
#endif

#ifdef DY_NK5110

const struct DY_Interface_t nk5110_itf ={
			 DY_NK5110,
			 &nk5110_dy_Refresh_all,
			 &nk5110_dy_Refresh,
			 &nk5110_init_display,
			 &nk5110_set_contrast,
			 &nk5110_clear_screen,
			 &nk5110_enable_sleep,
			 &nk5110_disable_sleep,
			 &nk5110_invert,
			 &nk5110_reset,
			 &nk5110_backlight,
			 &nk5110_FrameBuffPosition,
			 DY_NK5110_SCR_WIDTH,
			 DY_NK5110_SCR_HEIGHT,
			 &DY_PutPixel,
			 &DY_Line,
			 &DY_Circle,
			 &DY_Rectangle,
			 &DY_PutxBitmap,
			 &DY_HBar,
			 &DY_VBar,
			 &DY_PutFontChar,
			 &DY_PutText
			};
#endif

Frame_t WindowToFrame(Window_t *window)
{
	Frame_t frame;
	frame.p.x=window->p1.x;
	if (window->p2.x < frame.p.x)
		frame.p.x=window->p2.x;
	frame.p.y=window->p1.y;
	if (window->p2.y < frame.p.y)
		frame.p.y=window->p2.y;
	frame.width=abs(window->p2.x-window->p1.x);
	frame.height=abs(window->p2.y-window->p1.y);
	return frame;
}

Window_t FrameToWindow(Frame_t *frame)
{
	Window_t window;
	window.p1=frame->p;
	window.p2.x=frame->p.x+frame->width;
	window.p2.y=frame->p.y+frame->height;
	return window;
}

Window_t WindowExpand(Window_t win,uint8_t horz,uint8_t vert)
{
	uint8_t dim1,dim2;
	dim1=win.p1.x;
	dim2=win.p2.x;
	if (dim2<dim1)
	{
		dim1=win.p2.x;
		dim2=win.p1.x;
	}
	win.p1.x=dim1-horz;
	win.p2.x=dim2+horz;

	dim1=win.p1.y;
	dim2=win.p2.y;
	if (dim2<dim1)
	{
		dim1=win.p2.y;
		dim2=win.p1.y;
	}
	win.p1.y=dim1-vert;
	win.p2.y=dim2+vert;

	return win;
}


