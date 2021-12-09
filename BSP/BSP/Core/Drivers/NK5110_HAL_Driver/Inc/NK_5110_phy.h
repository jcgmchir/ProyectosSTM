
#ifndef INC_NK5110_PHY_H_
#define INC_NK5110_PHY_H_

//#include "spi.h" /*definicion de Handlers*/

enum nk5110_TGlcdSignal {NK5110_PLCD_CE, NK5110_PLCD_DC, NK5110_PLCD_RST, NK5110_PLCD_BACKLIGHT};
#define NK5110_BACKLIGHT_ON	1
#define NK5110_BACKLIGHT_OFF	0

SPI_HandleTypeDef hspi3;

#define NK5110_SPI_DY hspi3
#define NK5110_TIME_OUT 1000

extern void nk5110_set_signal(enum nk5110_TGlcdSignal sig, uint8_t value);
extern void nk5110_write_display (uint8_t *dato, uint16_t size);


#endif
