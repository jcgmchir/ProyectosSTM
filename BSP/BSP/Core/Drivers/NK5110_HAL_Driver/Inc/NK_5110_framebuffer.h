/*
 * ks0108_framebuffer.h
 *
 *  Created on: 20 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_NK5110_FRAMEBUFFER_H_
#define INC_NK5110_FRAMEBUFFER_H_

#include "Display.h"
#include "nk_5110_config.h"

#define FRAME_BUFFER

extern uint8_t* nk5110_FrameBuffPosition(uint8_t page,uint8_t col);
extern void nk5110_dy_Refresh_all(void);
extern void nk5110_dy_Refresh(Frame_t frm);


#endif /* KS0108_HAL_DRIVER_INC_KS0108_FRAMEBUFFER_H_ */
