/**
    @file ks0108_common.c
    @brief ks0108 glcd library. Common parts

    Simple graphical library for the ARM Cortex-M course http://armcortexm.blogs.upv.es
    Based on my previous library for the 8051

    @author Angel Perles
    @author Daniel Fernandez added font support
    @date 2008, 2012
*/

#include "Inc/Display.h"
#include "Inc/DY_BasicFunctions.h"

void DY_PutxBitmap(DY_Ift_t* Me,Frame_t frm, uint8_t copy_options, const uint8_t *xbm);
void DY_Rectangle(DY_Ift_t* Me,Window_t win, Fill_t fill);
void DY_PutPixel(DY_Ift_t* Me,Coord_t p, PixelColor_t color, uint8_t *pattern);
void DY_Circle(DY_Ift_t* Me,Circle_t circ, Fill_t fill);
void DY_Line(DY_Ift_t* Me,Window_t win,Fill_t fill);
void DY_HBar(DY_Ift_t* Me,Frame_t bar, uint16_t value);
void DY_VBar(DY_Ift_t* Me,Frame_t bar, uint16_t value);

const uint8_t motivo[8]={0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA};

#define IS_BORDER_NEED  ((fill.border & 0x3)!=0)
#define IS_BORDER_SOLID ((fill.border & 0x3)==0x01)
#define IS_BORDER_BLANK ((fill.border & 0x3)==0x02)
#define IS_NEED_FILL    ((fill.fill & 0xC)!=0)
#define IS_FILL_SOLID	((fill.fill & 0xC)==0x04)
#define IS_FILL_BLANK	((fill.fill & 0xC)==0x08)

void DY_PutPixel(DY_Ift_t* Me,Coord_t p, PixelColor_t color, uint8_t *pattern)
{
#ifdef FRAME_BUFFER
	uint8_t mask=1;
	uint8_t dat;
	uint8_t fbwidth,fbheight;
#endif
	fbwidth=Me->TotalWidth;
	fbheight=Me->TotalHeight;
	if (color==COLOR_PATTERN)
	{
		if (pattern==NULL)
			pattern=(uint8_t *)motivo;
		if ((pattern[p.x%8]&(1<<(p.y%8)))!=0)
			color=COLOR_BLACK;
		else
			color=COLOR_WHITE;
	}
	if ((p.x>=fbwidth) || (p.y>=fbheight)) {
		return;
	}
	mask=mask<<(p.y%8);
	dat=*(Me->CalcFrameBuffPosition(p.y/8,p.x));
	if (color == COLOR_WHITE)	{
		dat &= ~ mask; //put the bit to 0
		} else {
		dat |= mask; //put the bit to 1
	}
	*(Me->CalcFrameBuffPosition(p.y/8,p.x))=dat;
}

void DY_PutxBitmap(DY_Ift_t* Me,Frame_t frm, uint8_t copy_options, const uint8_t *xbm)
{
	uint8_t *dyimage;
	uint8_t pagina=0;
	uint8_t linea;
	uint8_t column;
	uint8_t file_mask;
	uint8_t bitmap_mask;
	uint8_t fbwidth,fbheight;
	fbwidth=Me->TotalWidth;
	fbheight=Me->TotalHeight;
	for (linea=0; linea<frm.height; linea++) //recorrer todas las lineas
	{
		if ((frm.p.x>=fbwidth) || (frm.p.y>=fbheight))
			return;
		pagina=(linea+frm.p.y)/8; //pagina correspondiente a la linea
		dyimage=Me->CalcFrameBuffPosition(pagina,frm.p.x);
		file_mask=(0x1<<(linea+frm.p.y)%8); //lsb es la parte superior
		bitmap_mask=0x1;
		for (column=0;column<frm.width;column++)
		{
			if (bitmap_mask==0x00)
				bitmap_mask=0x01;
			if (copy_options==DIRECT_COPY)
			{
				if ((*xbm & bitmap_mask)!=0)
					dyimage[column]|=file_mask; //esta el bit a 1.
				else
					dyimage[column]&=(~file_mask); //esta el bit a 0.
			}
			else
			{
				if ((*xbm & bitmap_mask)!=0)
					dyimage[column]&=(~file_mask); //esta el bit a 0.
				else
					dyimage[column]|=file_mask; //esta el bit a 1.
			}

			bitmap_mask=(bitmap_mask<<1);
			if (bitmap_mask==0x00)
				xbm++;
		}
		if (bitmap_mask!=0x00)
			xbm++; //ha finalizado el byte aunque no se haya completado
	}
}

void DY_Rectangle(DY_Ift_t* Me,Window_t win, Fill_t fill)
{
	uint8_t *dyimage;
	uint8_t column;
	uint8_t linea;
	uint8_t page;
	uint8_t width;
	uint8_t mask;

	if ((win.p1.x>win.p2.x) || (win.p1.y>win.p2.y))
		return;
	width=(win.p2.x-win.p1.x)+1;
	page=win.p1.y/8;
	dyimage=Me->CalcFrameBuffPosition(page,win.p1.x);
	for (linea=win.p1.y;linea<=win.p2.y;linea++)
	{
		page=linea/8;
		dyimage=Me->CalcFrameBuffPosition(page,win.p1.x);
		mask=1<<(linea%8);
		for (column=0;column<width;column++)
		{
			if ((linea==win.p1.y) || (linea==win.p2.y) || (column==0) || (column==(width-1)))
			{
				if (IS_BORDER_NEED)
				{
					if (IS_BORDER_SOLID)
						dyimage[column]|=(mask);
					else if (IS_BORDER_BLANK)
						dyimage[column]&=(~mask);
					else // es motivo
					{
						if (fill.pattern==NULL)
							fill.pattern=(uint8_t *)motivo;
						if ((fill.pattern[(column+win.p1.x)%8]&mask)!=0)
							dyimage[column]|=mask;
						else
							dyimage[column]&=(~mask);
					}
				}
			}
			else if (IS_NEED_FILL)
			{
				if (IS_FILL_SOLID)
					dyimage[column]|=mask;
				else if (IS_FILL_BLANK)
					dyimage[column]&=(~mask);
				else
				{
					if (fill.pattern==NULL)
						fill.pattern=(uint8_t *)motivo;
					if ((fill.pattern[(column+win.p1.x)%8]&mask)!=0)// es motivo
						dyimage[column]|=mask;
					else
						dyimage[column]&=(~mask);
				}
			}
		}
	}
}


//void DY_line(uint8_t FB_num,uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color, uint8_t *pattern)
void DY_Line(DY_Ift_t* Me,Window_t win,Fill_t fill)
{
	uint8_t deltax, deltay, x,y, steep;
	Coord_t point;
	int8_t error, ystep;
	uint8_t	temp;
	PixelColor_t color;

	if (IS_BORDER_SOLID)
		color=COLOR_BLACK;
	else if(IS_BORDER_BLANK)
		color=COLOR_WHITE;
	else //border pattern
		color=COLOR_PATTERN;
	if (win.p1.y>win.p2.y)			//Calcula el valor absoluto de la diferencia en direccion y
		deltay=win.p1.y-win.p2.y;
	else
		deltay=win.p2.y-win.p1.y;
	if (win.p1.x>win.p2.x) 			//Calcula el valor absoluto de la diferencia en direccion x
		deltax=win.p1.x-win.p2.x;
	else
		deltax=win.p2.x-win.p1.x;
	steep = (deltay > deltax);	//Si la diferencia en y es mayor intercambiar x por y.
	if ( steep )				//interesa que el bucle sea en el incremento mayor y sea en x asi el
	{							//incremento en y sera entre -1 y +1
		temp=win.p1.x; win.p1.x=win.p1.y; win.p1.y=temp;
		temp=win.p2.x; win.p2.x=win.p2.y; win.p2.y=temp;
	}
	if (win.p1.x > win.p2.x)				//Si el punto inicial tiene mayor coordenada, intercambiar puntos
	{
		temp=win.p1.x; win.p1.x=win.p2.x; win.p2.x=temp;
		temp=win.p1.y; win.p1.y=win.p2.y; win.p2.y=temp;
	}
	deltax = win.p2.x - win.p1.x;
	if (win.p1.y>win.p2.y)			//Calcula el valor absoluto de la diferencia en direccion y
		deltay=win.p1.y-win.p2.y;
	else
		deltay=win.p2.y-win.p1.y;
	error = deltax / 2;			//error a la mitad de la diferencia de x
	point.y = win.p1.y;						//punto inicial y en win.p1.y
	if(win.p1.y < win.p2.y) ystep = 1;  else ystep = -1; 	//direccion inicial del paso en y a uno con signo dependiente de la diferencia en y
	for(x = win.p1.x; x <= win.p2.x; x++)				//recorrido en x desde punto inicial a final
	{
		point.x=x;
		if (steep)							//si esta intercambiado X por Y representar con las coordenadas invertidas
			DY_PutPixel(Me,point,color,fill.pattern);
		else								//si no esta intercambiado X por Y representar con las coordenadas normales
			DY_PutPixel(Me,point,color,fill.pattern);
		error = error - deltay;				//comprobar la desviacion y ajustar y de acuerdo a la misma de uno en uno
		if (error < 0)						//para incrementar una unidad en i se requieren tantas iteraciones en X como relaci�n X/Y
		{									//el mecanismo incremental permite reducir el error al ser acumulativo
			y = y + ystep;
			error = error + deltax;
		}
	}
}


//void DY_circle(uint8_t FB_num,uint8_t xCenter, uint8_t yCenter, uint8_t radius, uint8_t fill_mode,uint8_t* pattern)
void DY_Circle(DY_Ift_t* Me,Circle_t circ, Fill_t fill)
{
	uint8_t x,y,width,height;
	int16_t tSwitch;
	uint8_t x1 = 0;
	uint8_t y1;
	uint8_t lastx;
	uint8_t color;
	Coord_t point;
	Window_t window;
	y1 = circ.radius;
	x=circ.center.x-circ.radius;
	y=circ.center.y-circ.radius;
	width=circ.radius*2+1;
	height=circ.radius*2+1;
	tSwitch = 3 - 2 * circ.radius;
	lastx=x1;
	while (x1 <= y1)
	{
		if(IS_BORDER_NEED)
		{
			if (IS_BORDER_SOLID)
				color=COLOR_BLACK;
			else if(IS_BORDER_BLANK)
				color=COLOR_WHITE;
			else //border pattern
				color=COLOR_PATTERN;
			// upper left corner
			point.x=x+circ.radius-x1;
			point.y=y+circ.radius-y1;
			DY_PutPixel(Me,point,color,fill.pattern); // upper half
			point.x=x+circ.radius - y1;
			point.y=y+circ.radius - x1;
			DY_PutPixel(Me,point,color,fill.pattern); // lower half
			// upper right corner
			point.x=x+width-circ.radius-1 + x1;
			point.y=y+circ.radius - y1;
			DY_PutPixel(Me,point,color,fill.pattern); // upper half
			point.x=x+width-circ.radius-1 + y1;
			point.y=y+circ.radius - x1;
			DY_PutPixel(Me,point,color,fill.pattern); // lower half
			// lower right corner
			point.x=x+width-circ.radius-1 + x1;
			point.y=y+height-circ.radius-1 + y1;
			DY_PutPixel(Me,point,color,fill.pattern); // lower half
			point.x=x+width-circ.radius-1 + y1;
			point.y=y+height-circ.radius-1 + x1;
			DY_PutPixel(Me,point,color,fill.pattern); // upper half
			// lower left corner
			point.x=x+circ.radius - x1;
			point.y=y+height-circ.radius-1 + y1;
			DY_PutPixel(Me,point,color,fill.pattern); // lower half
			point.x=x+circ.radius - y1;
			point.y=y+height-circ.radius-1 + x1;
			DY_PutPixel(Me,point,color,fill.pattern); // upper half
		}
		if (tSwitch < 0)
			tSwitch += (4 * x1 + 6);
		else
		{
			tSwitch += (4 * (x1 - y1) + 10);
			//draw rectangle Y1 & Y1 at last item
			if(IS_NEED_FILL)
			{
				//color=fill_mode&FILL_PATTERN;
				//color|=(color>>2);
				window.p1.x=circ.center.x+lastx;
				window.p1.y=circ.center.y-y1+1;
				window.p2.x=circ.center.x+x1;
				window.p2.y=circ.center.y+y1-1;
				DY_Rectangle(Me,window,fill);
				window.p1.x=circ.center.x-x1;
				window.p1.y=circ.center.y-y1+1;
				window.p2.x=circ.center.x-lastx;
				window.p2.y=circ.center.y+y1-1;
				DY_Rectangle(Me,window,fill);
				y1--;
				window.p1.x=circ.center.x-y1;
				window.p1.y=circ.center.y-x1;
				window.p2.x=circ.center.x-y1;
				window.p2.y=circ.center.y+x1;
				DY_Rectangle(Me,window,fill);
				window.p1.x=circ.center.x+y1;
				window.p1.y=circ.center.y-x1;
				window.p2.x=circ.center.x+y1;
				window.p2.y=circ.center.y+x1;
				DY_Rectangle(Me,window,fill);
				lastx=x1+1;
			}
			else
			{
				y1--;
			}
		}
		x1++;
	}
}

//void DY_HBar(uint8_t FB_num,uint8_t posx,uint8_t posy,uint8_t width,uint8_t heigth, uint16_t value)
void DY_HBar(DY_Ift_t* Me,Frame_t bar, uint16_t value)
{
	uint8_t mid;
	Window_t window;
	Fill_t fill_vacio,fill_lleno;
	fill_vacio.border=BORDER_SOLID;
	fill_vacio.fill=FILL_BLANK;
	fill_vacio.pattern=NULL;
	fill_lleno.border=BORDER_SOLID;
	fill_lleno.fill=FILL_SOLID;
	fill_lleno.pattern=NULL;
	mid=((value*bar.width)/100);
	window=FrameToWindow(&bar);
	DY_Rectangle(Me,window,fill_vacio);
	if (mid!=0)
	{
		window.p2.x+=mid;
		DY_Rectangle(Me,window,fill_lleno);
	}
}

//void DY_VBar(uint8_t FB_num,uint8_t posx,uint8_t posy,uint8_t width,uint8_t heigth, uint16_t value)
void DY_VBar(DY_Ift_t* Me,Frame_t bar, uint16_t value)
{
	uint8_t mid;
	Window_t window;
	Fill_t fill_vacio,fill_lleno;
	fill_vacio.border=BORDER_SOLID;
	fill_vacio.fill=FILL_BLANK;
	fill_vacio.pattern=NULL;
	fill_lleno.border=BORDER_SOLID;
	fill_lleno.fill=FILL_SOLID;
	fill_lleno.pattern=NULL;
	mid=((value*bar.height)/100);
	window=FrameToWindow(&bar);
	DY_Rectangle(Me,window,fill_vacio);
	if (mid!=0)
	{
		window.p1.y-=mid;
		DY_Rectangle(Me,window,fill_lleno);
	}
}

