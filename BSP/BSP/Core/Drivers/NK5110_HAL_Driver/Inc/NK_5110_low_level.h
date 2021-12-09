
#ifndef INC_NK5110_LOW_LEVEL_H_
#define INC_NK5110_LOW_LEVEL_H_

#include "NK_5110_config.h"

#define MODE_INVERTED 1
#define MODE_STANDAR  0

extern void nk5110_write_instruction(uint8_t cmd);
extern void nk5110_write_data(uint8_t data);
extern void nk5110_write_ndata(uint8_t *data,uint16_t nsize);
extern uint8_t nk5110_read_data(void);
extern void nk5110_no_busy(void);
extern void nk5110_reset(void);
extern void nk5110_backlight(uint8_t state);

#endif
