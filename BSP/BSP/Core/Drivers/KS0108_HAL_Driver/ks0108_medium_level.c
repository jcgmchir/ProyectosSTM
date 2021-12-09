/*
 * ks0108_mediumlevel.c
 *
 *  Created on: 21 feb. 2017
 *      Author: Juan Carlos
 */

#include "..\Common\Inc\display.h"

//#include ".\Inc\ks0108_low_level.h"
//#include ".\Inc\ks0108_phy.h"
//#include ".\Inc\ks0108_config.h"

#ifdef DY_KS0108

void ks0108_display_on(void);
void ks0108_display_off(void);
void ks0108_clear_screen(void);
void ks0108_read_display(uint8_t column,uint8_t page,uint8_t width,uint8_t *imagebuffer);
void ks0108_write_display(uint8_t column,uint8_t page,uint8_t width,uint8_t *imagebuffer);
void ks0108_putpixel(uint8_t x, uint8_t y, uint8_t color);

void ks0108_display_on(void) {
	uint8_t i;
	for (i=1;i<=DY_MAX_CS;i++)
	{
		ks0108_set_CS_signal(i);
		ks0108_write_instruction(LCD_ON);
	}
	ks0108_set_CS_signal(0);
}

void ks0108_display_off(void) {
	uint8_t i;
	for (i=1;i<=DY_MAX_CS;i++)
	{
		ks0108_set_CS_signal(i);
		ks0108_write_instruction(LCD_OFF);
	}
	ks0108_set_CS_signal(0);
}

void ks0108_clear_screen(void) {
	uint8_t page,column,cs;

	for (page=0; page<DY_KS0108_PAGES ; page++)
		for (cs=1;cs<=DY_MAX_CS;cs++)
		{
			ks0108_set_CS_signal(cs);
			ks0108_write_instruction(X_ADDRESS | page);
			ks0108_write_instruction(Y_ADDRESS);	// column 0
			ks0108_write_instruction(LCD_DISP_START);
			for (column=0;column<DY_KS0108_WIDTH;column++)
				ks0108_write_data(0x00);
		}
	ks0108_set_CS_signal(0);
}

void ks0108_read_display(uint8_t column,uint8_t page,uint8_t width,uint8_t *imagebuffer)
{
	uint8_t x;
	uint8_t col_index=0;
	uint8_t last_col;
	last_col=DY_KS0108_WIDTH-(column%DY_KS0108_WIDTH);
	if (last_col>width)
		last_col=width;
	x=column;
	ks0108_set_CS_signal(1+(x/DY_KS0108_WIDTH)); /*CS calculation*/
	x=(x % DY_KS0108_WIDTH); /*X display to X chip*/
	ks0108_write_instruction(Y_ADDRESS | x); // column
	ks0108_write_instruction(X_ADDRESS | page); // page
	imagebuffer[0] = ks0108_read_data();	//Dummy Read after Setup new Address, otherwise lats address is read because reading use double buffer
	for (col_index=0;col_index<last_col;col_index++)
		imagebuffer[col_index] = ks0108_read_data();	//
	x=column;
	ks0108_set_CS_signal(1+((1+(x/DY_KS0108_WIDTH))%DY_MAX_CS)); /*Next CS*/
	ks0108_write_instruction(Y_ADDRESS); // column 0
	ks0108_write_instruction(X_ADDRESS | page); // same page
	imagebuffer[last_col] = ks0108_read_data();	//Dummy Read after Setup new Address, otherwise lats address is read because reading use double buffer
	while ((width-last_col)>DY_KS0108_WIDTH)
	{
		for (col_index=0;col_index<DY_KS0108_WIDTH;col_index++)
			imagebuffer[col_index+last_col] = ks0108_read_data();	//
		ks0108_set_CS_signal(1+((2+(x/DY_KS0108_WIDTH))%DY_MAX_CS)); /*Next CS*/
		ks0108_write_instruction(Y_ADDRESS); // column 0
		ks0108_write_instruction(X_ADDRESS | page); // same page
		imagebuffer[col_index+last_col] = ks0108_read_data();	//Dummy Read after Setup new Address, otherwise lats address is read because reading use double buffer
		last_col+=DY_KS0108_WIDTH;
	}
	for (col_index=0;col_index<(width-last_col);col_index++)
		imagebuffer[col_index+last_col] = ks0108_read_data();	//
}

void ks0108_write_display(uint8_t column,uint8_t page,uint8_t width,uint8_t *imagebuffer)
{
	uint8_t x;
	uint8_t col_index=0;
	uint8_t last_col;
	last_col=DY_KS0108_WIDTH-(column%DY_KS0108_WIDTH);
	if (last_col>width)
		last_col=width;
	x=column;
	ks0108_set_CS_signal(1+(x/DY_KS0108_WIDTH)); /*CS calculation*/
	x=(x % DY_KS0108_WIDTH); /*X display to X chip*/
	ks0108_write_instruction(Y_ADDRESS | x); // column
	ks0108_write_instruction(X_ADDRESS | page); // page
	for (col_index=0;col_index<last_col;col_index++)
		ks0108_write_data(imagebuffer[col_index]);
	x=column;
	ks0108_set_CS_signal(1+((1+(x/DY_KS0108_WIDTH))%DY_MAX_CS)); /*Next CS*/
	ks0108_write_instruction(Y_ADDRESS); // column 0
	ks0108_write_instruction(X_ADDRESS | page); // same page
	while ((width-last_col)>DY_KS0108_WIDTH)
	{
		for (col_index=0;col_index<DY_KS0108_WIDTH;col_index++)
			ks0108_write_data(imagebuffer[col_index+last_col]);	//
		ks0108_set_CS_signal(1+((2+(x/DY_KS0108_WIDTH))%DY_MAX_CS)); /*Next CS*/
		ks0108_write_instruction(Y_ADDRESS); // column 0
		ks0108_write_instruction(X_ADDRESS | page); // same page
		last_col+=DY_KS0108_WIDTH;
	}
	for (col_index=0;col_index<(width-last_col);col_index++)
		ks0108_write_data(imagebuffer[col_index+last_col]);
}

void ks0108_putpixel(uint8_t x, uint8_t y, uint8_t color) {
	uint8_t dat, mask=1;

	if ((x>=DY_WIDTH) || (y>=DY_HEIGHT)) {
		return;
	}
	mask=mask<<(y%8);
	ks0108_set_CS_signal(1+(x/DY_KS0108_WIDTH)); /*CS calculation*/
	x=(x % DY_KS0108_WIDTH); /*X display to X chip*/
	ks0108_write_instruction(Y_ADDRESS | x); // column
	ks0108_write_instruction(X_ADDRESS | (y/8)); // page

	dat = ks0108_read_data();	//Dummy Read after Setup new Address, otherwise lats address is read because reading use double buffer
	dat = ks0108_read_data();	//
	if (color == 0)	{
		dat &= ~ mask; //put the bit to 0
		} else {
		dat |= mask; //put the bit to 1
	}
	ks0108_write_instruction(Y_ADDRESS | x);	// column
    ks0108_write_instruction(X_ADDRESS | (y/8));	// page
	ks0108_write_data(dat);
	ks0108_set_CS_signal(0);
}

#endif //DY_KS0108
