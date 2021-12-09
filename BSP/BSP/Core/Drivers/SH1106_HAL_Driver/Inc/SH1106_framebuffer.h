/*
 * ks0108_framebuffer.h
 *
 *  Created on: 20 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_SH1106_FRAMEBUFFER_H_
#define INC_SH1106_FRAMEBUFFER_H_

#include "Display.h"
#include "SH1106_config.h"

#define FRAME_BUFFER

//extern uint8_t sh1106_FrameBuffer[DY_SH1106_PAGES][DY_SH1106_SCR_WIDTH];
extern uint8_t* sh1106_FrameBuffPosition(uint8_t page,uint8_t col);
extern void sh1106_dy_Refresh_all(void);
extern void sh1106_dy_Refresh(Frame_t frm);


#endif /* KS0108_HAL_DRIVER_INC_KS0108_FRAMEBUFFER_H_ */
