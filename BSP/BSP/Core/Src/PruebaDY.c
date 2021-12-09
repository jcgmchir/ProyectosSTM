/*
 * PruebaDY.c
 *
 *  Created on: 6 dic. 2021
 *      Author: jcgmc
 */

#include "main.h"
#include "..\Drivers\Common\Inc\Display.h"
#include "..\Drivers\Common\xbm\Centigrado8x16.xbm"
#include "stdio.h"
#include "string.h"

#define DIGITS 3

int PruebaDY(void)
{
    Window_t win,win_int,win_ext;
    Frame_t frm;
    Fill_t fill;
	DY_Ift_t DY;
	Circle_t circ;

	DY=sh1106_itf;
	win.p1.x=0;
	win.p1.y=0;
	win.p2.x=DY.TotalWidth-1;
	win.p2.y=DY.TotalHeight-1;
	fill.border=BORDER_SOLID;
	fill.fill=FILL_BLANK;
	fill.pattern=NULL;
	DY.Rectangle(&DY,win,fill);
	win_int.p1.x=(DY.TotalWidth-14*DIGITS)/2;
	win_int.p1.y=(DY.TotalHeight-24)/2;
	win_int.p2.x=(win_int.p1.x+14*DIGITS)-1;
	win_int.p2.y=(win_int.p1.y+24);
	win_ext=WindowExpand(win_int,3,3);
	fill.border=BORDER_SOLID;
	fill.fill=FILL_SOLID;
    DY.Rectangle(&DY,win_ext,fill);
	fill.border=BORDER_BLANK;
	fill.fill=FILL_BLANK;
    DY.Rectangle(&DY,win_int,fill);
    frm.p.x=win_ext.p2.x+5;
    frm.p.y=DY.TotalHeight/2;
    glcd_putxbitmap(&DY,frm,DIRECT_COPY,centigrado8x16);
    circ.center.x=win_ext.p1.x/2;
    circ.center.y=DY.TotalHeight/2;
    circ.radius=circ.center.x/2;
	fill.border=BORDER_SOLID;
	fill.fill=NO_FILL;
    DY.Circle(&DY,circ,fill);
    DY.Refresh_all();

	DY=nk5110_itf;
	win.p1.x=0;
	win.p1.y=0;
	win.p2.x=DY.TotalWidth-1;
	win.p2.y=DY.TotalHeight-1;
	fill.border=BORDER_SOLID;
	fill.fill=FILL_BLANK;
	fill.pattern=NULL;
	DY.Rectangle(&DY,win,fill);
	win_int.p1.x=(DY.TotalWidth-14*DIGITS)/2;
	win_int.p1.y=(DY.TotalHeight-24)/2;
	win_int.p2.x=(win_int.p1.x+14*DIGITS)-1;
	win_int.p2.y=(win_int.p1.y+24);
	win_ext=WindowExpand(win_int,3,3);
	fill.border=BORDER_SOLID;
	fill.fill=FILL_SOLID;
    DY.Rectangle(&DY,win_ext,fill);
	fill.border=BORDER_BLANK;
	fill.fill=FILL_BLANK;
    DY.Rectangle(&DY,win_int,fill);
    frm.p.x=win_ext.p2.x+5;
    frm.p.y=DY.TotalHeight/2;
    glcd_putxbitmap(&DY,frm,DIRECT_COPY,centigrado8x16);
    circ.center.x=win_ext.p1.x/2;
    circ.center.y=DY.TotalHeight/2;
    circ.radius=circ.center.x/2;
	fill.border=BORDER_SOLID;
	fill.fill=NO_FILL;
    DY.Circle(&DY,circ,fill);
    DY.Refresh_all();

/*
  DY_rectangle(0,0,83,47,BORDER_BLANK|FILL_BLANK,NULL);
  PutText(32,18,&datos[3],FONT_LCDNUMS12x16,DIRECT_COPY,16,FIXED_WIDTH);
  dy_Refresh_all();
 */
  return 0;

}

uint32_t power10(uint8_t exp)
{
	return (((exp)>0)?10*power10((exp)-1):1);
}

void refesh_count(void)
{
    Frame_t frm;

	char datos[12];
	char format[6];
	struct DY_Interface_t DY;
	uint32_t limit;
	format[0]='%';
	format[1]='0'+DIGITS;
	format[2]='.';
	format[3]='0'+DIGITS;
	format[4]='d';
	format[5]=0;
	limit=power10(DIGITS)-1;
	static uint16_t count=0;
	sprintf(datos,format,count);
	DY=sh1106_itf;
	frm.p.x=(DY.TotalWidth-14*DIGITS)/2;
	frm.p.y=(DY.TotalHeight-24)/2;
	frm.width=14*DIGITS;
	frm.height=24;
	DY.PutText(&DY,frm.p,datos,FONT_LCDNUMS14X24,DIRECT_COPY,24,FIXED_WIDTH);
	DY.Refresh(frm);

	DY=nk5110_itf;
	sprintf(datos,format,limit-count);
	frm.p.x=(DY.TotalWidth-14*DIGITS)/2;
	frm.p.y=(DY.TotalHeight-24)/2;
	frm.width=14*DIGITS;
	frm.height=24;
	DY.PutText(&DY,frm.p,datos,FONT_LCDNUMS14X24,DIRECT_COPY,24,FIXED_WIDTH);
	DY.Refresh(frm);

	count++;
	if (count>limit)
		count=0;
}

