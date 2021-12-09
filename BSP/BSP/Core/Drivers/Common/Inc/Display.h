#ifndef DISPLAY_H
#define DISPLAY_H

#include "main.h"

enum enPixelColor{
	COLOR_WHITE=0,
	COLOR_BLACK,
	COLOR_PATTERN
};

typedef enum enPixelColor PixelColor_t;

enum enBorderStyle{
	NO_BORDER=0,
	BORDER_SOLID,
	BORDER_BLANK,
	BORDER_PATTERN
};

typedef enum enBorderStyle BorderStyle_t;

enum enFillStyle{
	NO_FILL		    =0x00,
	FILL_SOLID  	=0x04,
	FILL_BLANK	    =0x08,
	FILL_PATTERN    =0x0C
};

typedef enum enFillStyle FillStyle_t;

struct Coord
{
	uint8_t x;
	uint8_t y;
};

typedef struct Coord Coord_t;

struct Pixel
{
	Coord_t pos;
	uint8_t color;
};

typedef struct Pixel Pixel_t;

struct Window
{
	Coord_t p1;
	Coord_t p2;
};

typedef struct Window Window_t;


struct Circle
{
	Coord_t center;
	uint8_t radius;
};

typedef struct Circle Circle_t;

struct Fill
{
	BorderStyle_t border;
	FillStyle_t fill;
	uint8_t *pattern;
};

typedef struct Fill Fill_t;

struct Line
{
	Window_t points;
	uint8_t color;
};

typedef struct Line Line_t;

struct Frame
{
	Coord_t p;
	uint8_t width;
	uint8_t height;
};

typedef struct Frame Frame_t;

extern Frame_t WindowToFrame(Window_t *window);
extern Window_t FrameToWindow(Frame_t *frame);
Window_t WindowExpand(Window_t win,uint8_t horz,uint8_t vert);

struct DY_Interface_t{
	uint8_t MeType;
	void (*Refresh_all)(void);
	void (*Refresh)(Frame_t win);
	void (*init)(void);
	void (*set_contrast)(uint8_t contrast);
	void (*clear_screen)(void);
	void (*enable_sleep)(void);
	void (*disable_sleep)(void);
	void (*invert)(uint8_t mode);
	void (*reset)(void);
	void (*backlight)(uint8_t state);
	uint8_t* (*CalcFrameBuffPosition)(uint8_t page,uint8_t col);
	uint8_t TotalWidth;
	uint8_t TotalHeight;
	void (*PutPixel)(struct DY_Interface_t* Me,Coord_t p, PixelColor_t color, uint8_t *pattern);
	void (*Line)(struct DY_Interface_t* Me,Window_t win,Fill_t fill);
	void (*Circle)(struct DY_Interface_t* Me,Circle_t circ, Fill_t fill);
	void (*Rectangle)(struct DY_Interface_t* Me,Window_t win, Fill_t fill);
	void (*PutxBitmap)(struct DY_Interface_t* Me,Frame_t frm, uint8_t copy_options, const uint8_t *xbm);
	void (*HBar)(struct DY_Interface_t* Me,Frame_t bar, uint16_t value);
	void (*VBar)(struct DY_Interface_t* Me,Frame_t bar, uint16_t value);
	uint8_t (*PutFontChar)(struct DY_Interface_t *Me,Coord_t pos, uint8_t Character,uint8_t num_fuente,uint8_t copy_mode,uint8_t max_height,uint8_t fixed_witdh);
	uint8_t (*PutText)(struct DY_Interface_t* Me,Coord_t pos, char *string,uint8_t num_fuente,uint8_t copy_mode,uint8_t max_height,uint8_t fixed_witdh);
};

typedef struct DY_Interface_t DY_Ift_t;

#define DY_NK5110 0
//#define DY_KS0108 1
#define DY_SH1106 2

#ifdef DY_NK5110

#define DY_NK5110_FB_NUM 0
#include "../../NK5110_HAL_Driver/Inc/NK_5110_phy.h"
#include "../../NK5110_HAL_Driver/Inc/NK_5110_low_level.h"
#include "../../NK5110_HAL_Driver/Inc/NK_5110_medium_level.h"
#include "../../NK5110_HAL_Driver/Inc/NK_5110_framebuffer.h"
extern const struct DY_Interface_t nk5110_itf;

#endif

#ifdef DY_KS0108

#define DY_KS0108_FB_NUM 1
#include "../../KS0108_HAL_Driver/Inc/KS0108_phy.h"
#include "../../KS0108_HAL_Driver/Inc/KS0108_low_level.h"
#include "../../KS0108_HAL_Driver/Inc/KS0108_medium_level.h"
#include "../../KS0108_HAL_Driver/Inc/KS0108_framebuffer.h"

#endif

#ifdef DY_SH1106

#define DY_SH1106_FB_NUM 2
#include "../../SH1106_HAL_Driver/Inc/SH1106_phy.h"
#include "../../SH1106_HAL_Driver/Inc/SH1106_low_level.h"
#include "../../SH1106_HAL_Driver/Inc/SH1106_medium_level.h"
#include "../../SH1106_HAL_Driver/Inc/SH1106_framebuffer.h"
extern const struct DY_Interface_t sh1106_itf;

#endif //DY_SH1106

#include "DY_BasicFunctions.h"
#include "fonts.h"



#endif

