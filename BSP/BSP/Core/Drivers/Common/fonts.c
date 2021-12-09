/*
 * fonts.c
 *
 *  Created on: 18 feb. 2017
 *      Author: Juan Carlos
 */

#include "Inc\Display.h"
#include "Inc\fonts.h"
#include "fonts\allFonts.h"

//#define MAX_FONTS 10
//const uint8_t *Fuentes[MAX_FONTS]={TimesNewRoman13,Callibri15,CalLite24,font8x8,CalBlk36,Arial_bold_14,lcdnums14x24,fixednums8x16,Iain5x7,System5x7};

const uint8_t *Fuentes[MAX_FONTS]={lcdnums14x24,lcdnums12x16,System5x7,fixednums6x10,Wendy3x5,fixed_bold10x15,Arial_bold_14};

struct FONT Fuente[MAX_FONTS];

void InitFonts(void)
{
	uint8_t i;
	for (i=0;i<MAX_FONTS;i++)
	{
		Fuente[i].font_head=(struct FONT_HEAD *) Fuentes[i];
		if ((Fuente[i].font_head->font_Size_H==0x00) && (Fuente[i].font_head->font_Size_L<=0x01))
		{
			Fuente[i].font_widths=NULL;
			Fuente[i].font_data=&((Fuentes[i])[sizeof (struct FONT_HEAD)]);
		}
		else
		{
			Fuente[i].font_widths= &((Fuentes[i])[sizeof (struct FONT_HEAD)]);
			Fuente[i].font_data=&((Fuentes[i])[(sizeof (struct FONT_HEAD))+(Fuente[i].font_head->font_Char_Count)]);
		}
	}
}


uint8_t DY_PutFontChar(DY_Ift_t *Me,Coord_t pos, uint8_t Character,uint8_t num_fuente,uint8_t copy_mode,uint8_t max_height,uint8_t fixed_witdh)
{
	uint8_t width;
	uint8_t height;
	uint8_t bytes_height;
	uint8_t font_width;
	uint16_t index_data=0;
	uint8_t index_witdh;
	uint8_t x,y,sp,space;
	uint8_t *buffer_up;
	uint8_t *buffer_dw;
	uint8_t shift=0;
	uint8_t fixed=0;
	uint8_t page;
	uint16_t temp,mask;
	uint8_t *tempp;
	uint8_t noalineado=0;

	if (num_fuente>MAX_FONTS)
		return 0;
	if (Character<Fuente[num_fuente].font_head->font_First_Char)
		return 0;
	index_witdh=Character-Fuente[num_fuente].font_head->font_First_Char;
	if ((index_witdh)>=Fuente[num_fuente].font_head->font_Char_Count)
		return 0;
	height=Fuente[num_fuente].font_head->font_Height;
	font_width=Fuente[num_fuente].font_head->font_Width;
	fixed=(Fuente[num_fuente].font_widths==NULL);
	page=pos.y/8;
	if (fixed) //Fuente fija
	{
		width=font_width;
		index_data=index_witdh*width;
		space=1;
	}
	else	//Fuente de anchura variable
	{
		width=Fuente[num_fuente].font_widths[index_witdh];
		for (x=0;x<index_witdh;x++)
			index_data+=Fuente[num_fuente].font_widths[x];
		if (fixed_witdh==FIXED_WIDTH)
		{
			if (font_width>width)
				space=font_width-width;
			else
				space=width;
		}
		else
		{
			space=0;
			if (Character<128)
				space=1;
		}
	}
	buffer_up=Me->CalcFrameBuffPosition(page,pos.x);
	buffer_dw=Me->CalcFrameBuffPosition(page+1,pos.x);
	bytes_height=height/8;	//Numero de bytes en vertical del font
	if (height%8!=0)
		bytes_height++;
	index_data=index_data*bytes_height;	//Numero de bytes que forma cada caracter
	noalineado=((pos.y%8)!=0);
	if (noalineado)	//Si esta alineado no es necesario
		buffer_up=Me->CalcFrameBuffPosition(page,pos.x);
	for (y=0;(y<bytes_height) && (max_height>0);y++)
	{
		if (y==(bytes_height-1) && fixed==0)
			if ((height%8)!=0)
				shift=8-(height%8);
		mask=(0xFF>>shift);	//En el ultimo byte solo aplica a los bits sobrantes
		if (max_height!=0xFF)
			if (max_height<8)
				mask&=(0xFF>>(8-max_height));
		mask=(mask<<(pos.y%8)); //mover la mascara entre los dos bytes verticales contiguos
		if (noalineado)	//Si esta alineado no es necesario
			buffer_dw=Me->CalcFrameBuffPosition(page+y+1,pos.x);
		else
			buffer_up=Me->CalcFrameBuffPosition(page+y,pos.x);
		for (x=0;x<width;x++)
		{
			temp=((Fuente[num_fuente].font_data[index_data++])>>shift);	//se desplaza en el ultimo byte porque la utilidad de font lo hace as� �?
			temp=(temp<<(pos.y%8)); //desplazar el byte si est� desalineado con la p�gina
			temp &= mask; //Limitar a la altura
			if (noalineado)
				temp|=((((uint16_t)buffer_dw[x]<<8) | ((uint16_t)buffer_up[x]))&(~mask)); //mezclar con la informaci�n del display
			else
				temp|=(((uint16_t)buffer_up[x])&(~mask)); //mezclar con la informaci�n del display
			if (copy_mode==INVERSE_COPY)
				temp^=mask;		   //Invierte solo la informaci�n del font
			if (noalineado)
				buffer_dw[x]=((temp&0xFF00)>>8); //Actualiza la pantalla
			buffer_up[x]=(temp&0xFF);
		}
		for (sp=0;sp<space;sp++)	//A�ade una linea en blanco al final
		{
			if (noalineado)
				temp=((((uint16_t)buffer_dw[x]<<8) | ((uint16_t)buffer_up[x]))&(~mask));
			else
				temp=(((uint16_t)buffer_up[x])&(~mask));
			if (copy_mode==INVERSE_COPY)
				temp^=mask;
			if (noalineado)
				buffer_dw[x]=((temp&0xFF00)>>8);
			buffer_up[x]=(temp&0xFF);
			x++;
		}
		if (noalineado)	//Si esta alineado no es necesario
		{
			tempp=buffer_up;		//Intercambiar buffers
			buffer_up=buffer_dw;
			buffer_dw=tempp;
		}
		if (max_height>=8)
			max_height-=8;
		else
			max_height=0;
	}
	return width+space;
}

uint8_t DY_PutText(DY_Ift_t *Me,Coord_t pos, char *string,uint8_t num_fuente,uint8_t copy_mode,uint8_t max_height,uint8_t fixed_witdh)
{
	uint8_t i=0;
	if (num_fuente>MAX_FONTS)
		return 0;
	while (string[i]!=0)
	{
		pos.x+=DY_PutFontChar(Me,pos,string[i],num_fuente,copy_mode,max_height,fixed_witdh);
		i++;
	}
	return pos.x;
}

