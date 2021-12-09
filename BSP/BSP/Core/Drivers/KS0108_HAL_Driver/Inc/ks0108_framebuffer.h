/*
 * ks0108_framebuffer.h
 *
 *  Created on: 20 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_KS0108_FRAMEBUFFER_H_
#define INC_KS0108_FRAMEBUFFER_H_

#include "ks0108_config.h"

#define FRAME_BUFFER

//extern uint8_t ks1808_FrameBuffer[DY_KS0108_PAGES][DY_KS0108_SCR_WIDTH];
extern uint8_t* ks1808_FrameBuffPosition(uint8_t page,uint8_t col);
extern void ks1808_dy_Refresh_all(void);
extern void ks1808_dy_Refresh(uint8_t x,uint8_t y,uint8_t width,uint8_t eigth);


#endif /* KS0108_HAL_DRIVER_INC_KS0108_FRAMEBUFFER_H_ */
