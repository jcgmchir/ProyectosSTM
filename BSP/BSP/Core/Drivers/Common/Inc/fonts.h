/*
 * fonts.h
 *
 *  Created on: 18 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef HAL_DRIVER_INC_FONTS_H_
#define HAL_DRIVER_INC_FONTS_H_

//#include "../../NK5110_HAL_Driver/Inc/NK_5110_config.h"

#include "Display.h"

struct FONT_HEAD {
	 uint8_t    font_Size_H; //_in_Bytes_over_all_included_Size_it_self;
	 uint8_t    font_Size_L; //_in_Bytes_over_all_included_Size_it_self;
	 uint8_t    font_Width; //_in_Pixel_for_fixed_drawing;
	 uint8_t    font_Height; //_in_Pixel_for_all_characters;
	 uint8_t    font_First_Char;
	 uint8_t    font_Char_Count;
};

struct FONT {
	 struct FONT_HEAD	const *font_head;
	 uint8_t	const *font_widths;
	 uint8_t	const *font_data;
};

#define GLCDFONTDECL(fuente) const uint8_t (fuente)[]
#define DIRECT_COPY		0
#define INVERSE_COPY	1
#define KERNING_WIDTH	0
#define FIXED_WIDTH		1
#define TOTAL_HEIGHT	0xFF

//Tipos de Fuentes
#define FONT_LCDNUMS14X24	 0
#define FONT_LCDNUMS12x16	 1
#define FONT_SYSTEM5X7		 2
#define FONT_FIXEDNUMS6x10	 3
#define FONT_WENDY3x5 		 4
#define FONT_FIXED_BOLD10X15 5
#define FONT_ARIALBOLD14	 6

#define MAX_FONTS 7

void InitFonts(void);
uint8_t DY_PutFontChar(DY_Ift_t *Me,Coord_t pos, uint8_t Character,uint8_t num_fuente,uint8_t copy_mode,uint8_t max_height,uint8_t fixed_witdh);
uint8_t DY_PutText(DY_Ift_t *Me,Coord_t pos, char *string,uint8_t num_fuente,uint8_t copy_mode,uint8_t max_height,uint8_t fixed_witdh);

#endif /* HAL_DRIVER_INC_FONTS_H_ */
