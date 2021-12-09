/*
 * ks0108_low_level.h
 *
 *  Created on: 12 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_KS0108_LOW_LEVEL_H_
#define INC_KS0108_LOW_LEVEL_H_

extern void ks0108_write_instruction(uint8_t cmd);
extern void ks0108_write_data(uint8_t cmd);
extern uint8_t ks0108_read_data(void);
extern void ks0108_no_busy(void);
extern void ks0108_reset(void);
extern void ks0108_backlight(uint8_t state);

#endif /* KS0108_HAL_DRIVER_INC_KS0108_LOW_LEVEL_H_ */
