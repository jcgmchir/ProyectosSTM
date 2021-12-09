
#ifndef INC_SH1106_PHY_H_
#define INC_SH1106_PHY_H_

#include "main.h"
extern I2C_HandleTypeDef hi2c3;


#define I2C_DY hi2c3
#define TIME_OUT 1000

extern void sh1106_write_display (uint8_t *dato, uint16_t size);
extern void sh1106_read_display (uint8_t *dato, uint16_t size);

#endif
