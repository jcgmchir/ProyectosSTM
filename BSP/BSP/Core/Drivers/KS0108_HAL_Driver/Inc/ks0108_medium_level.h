/*
 * ks0108_medium_level.h
 *
 *  Created on: 21 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_KS0108_MEDIUM_LEVEL_H_
#define INC_KS0108_MEDIUM_LEVEL_H_

extern void ks0108_display_on(void);
extern void ks0108_display_off(void);
extern void ks0108_clear_screen(void);
extern void ks0108_read_display(uint8_t column,uint8_t page,uint8_t width,uint8_t *imagebuffer);
extern void ks0108_write_display(uint8_t column,uint8_t page,uint8_t width,uint8_t *imagebuffer);
extern void ks0108_putpixel(uint8_t x, uint8_t y, uint8_t color);

#endif /* KS0108_HAL_DRIVER_INC_KS0108_MEDIUM_LEVEL_H_ */
