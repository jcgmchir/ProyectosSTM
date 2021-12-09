
#ifndef INC_SH1106_LOW_LEVEL_H_
#define INC_SH1106_LOW_LEVEL_H_

#include "SH1106_config.h"

extern void sh1106_write_instruction(uint8_t cmd, uint8_t *data, uint8_t len);
extern void sh1106_write_data(uint8_t data);
extern void sh1106_write_ndata(uint8_t *data,uint16_t nsize);
extern void sh1106_read_data(uint16_t nsize);
extern void sh1106_write(void);

#endif
