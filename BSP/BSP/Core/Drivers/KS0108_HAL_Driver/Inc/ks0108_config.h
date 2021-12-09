/*
 * ks0108_config.h
 *
 *  Created on: 12 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_KS0108_CONFIG_H_
#define INC_KS0108_CONFIG_H_

#define DY_KS0108_WIDTH		64
#define DY_KS0108_HEIGHT	64
#define DY_KS0108_PAGES		8
#define DY_KS0108_SCR_WIDTH	 128
#define DY_KS0108_SCR_HEIGHT 64
#define DY_KS0108_MAX_CS	2

/* Display Commands*/
#define LCD_ON				0x3F
#define LCD_OFF				0x3E
#define LCD_SET_ADD			0x40
#define LCD_DISP_START		0xC0
#define LCD_SET_PAGE		0xB8
#define X_ADDRESS	LCD_SET_PAGE	/* Address base for Page 0 */
#define Y_ADDRESS	LCD_SET_ADD		/* Address base for Y0	  */

/* Display Status*/
#define LCD_BUSY_BIT		7
#define LCD_BUSY_FLAG		0x80

#define LCD_RESET_BIT		4
#define LCD_RESET_FLAG		0x10

#endif /* KS0108_HAL_DRIVER_INC_KS0108_CONFIG_H_ */
