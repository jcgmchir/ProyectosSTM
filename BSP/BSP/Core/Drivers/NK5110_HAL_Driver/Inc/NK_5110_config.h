
#ifndef INC_NK5110_CONFIG_H_
#define INC_NK5110_CONFIG_H_

#define DY_NK5110_WIDTH		84
#define DY_NK5110_HEIGHT	48
#define DY_NK5110_PAGES		6
#define DY_NK5110_SCR_WIDTH	 84
#define DY_NK5110_SCR_HEIGHT 48
#define DY_NK5110_MAX_CS	1

/* Display Commands*/


// PCD8544 Commandset
// ------------------
// General commands
#define PCD8544_POWERDOWN			0x04
#define PCD8544_ENTRYMODE			0x02
#define PCD8544_EXTENDEDINSTRUCTION	0x01
#define PCD8544_DISPLAYBLANK		0x00
#define PCD8544_DISPLAYNORMAL		0x04
#define PCD8544_DISPLAYALLON		0x01
#define PCD8544_DISPLAYINVERTED		0x05
// Normal instruction set
#define PCD8544_FUNCTIONSET			0x20
#define PCD8544_DISPLAYCONTROL		0x08
#define PCD8544_SETYADDR			0x40
#define PCD8544_SETXADDR			0x80
// Extended instruction set
#define PCD8544_SETTEMP				0x04
#define PCD8544_SETBIAS				0x10
#define PCD8544_SETVOP				0x80
// Display presets
#define LCD_BIAS					0x03	// Range: 0-7 (0x00-0x07)
#define LCD_TEMP					0x02	// Range: 0-3 (0x00-0x03)
#define LCD_CONTRAST				0x46	// Range: 0-127 (0x00-0x7F)

#define LCD_COMMAND 0
#define LCD_DATA 1




/* Display Status*/

#endif /* NK5110_HAL_DRIVER_INC_KS0108_CONFIG_H_ */
