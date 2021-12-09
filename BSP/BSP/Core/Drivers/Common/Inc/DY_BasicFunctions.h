/*
 * DY_BasicFunctions.h
 *
 *  Created on: 21 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef KS0108_HAL_DRIVER_INC_DY_BASICFUNCTIONS_H_
#define KS0108_HAL_DRIVER_INC_DY_BASICFUNCTIONS_H_

#include "Display.h"

/*
#define NO_BORDER		0x00
#define BORDER_SOLID	0x01
#define BORDER_BLANK	0x02
#define BORDER_PATTERN	0x03
#define NO_FILL		    0x00
#define FILL_SOLID  	0x04
#define FILL_BLANK	    0x08
#define FILL_PATTERN    0x0C

#define COLOR_WHITE		0
#define COLOR_BLACK		1
#define COLOR_PATTERN	2
*/
/*Upper layer functions fast raw mode*/

extern void DY_PutxBitmap(DY_Ift_t* Me,Frame_t frm, uint8_t copy_options, const uint8_t *xbm);
extern void DY_Rectangle(DY_Ift_t* Me,Window_t win, Fill_t fill);
extern void DY_HBar(DY_Ift_t* Me,Frame_t bar, uint16_t value);
extern void DY_VBar(DY_Ift_t* Me,Frame_t bar, uint16_t value);

/*Upper layer functions slow pixel mode*/
extern void DY_PutPixel(DY_Ift_t* Me,Coord_t p, PixelColor_t color, uint8_t *pattern);
extern void DY_Circle(DY_Ift_t* Me,Circle_t circ, Fill_t fill);
extern void DY_Line(DY_Ift_t* Me,Window_t,Fill_t fill);

#define glcd_putxbitmap(FB,FRM,CPY,XBM) {FRM.width=XBM##_width;FRM.height=XBM##_height; DY_PutxBitmap(FB,FRM,CPY,(const uint8_t*)XBM##_bits);}

#define INVERSE_COPY	1
#define DIRECT_COPY		0

#endif /* KS0108_HAL_DRIVER_INC_DY_BASICFUNCTIONS_H_ */
