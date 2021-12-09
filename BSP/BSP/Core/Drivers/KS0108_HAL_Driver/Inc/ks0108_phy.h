/*
 * ks0108_phy.h
 *
 *  Created on: 21 feb. 2017
 *      Author: Juan Carlos
 */

#ifndef INC_KS0108_PHY_H_
#define INC_KS0108_PHY_H_

enum ks0108_TGlcdSignal {KS0108_PLCD_DATA_WR, KS0108_PLCD_DATA_RD, KS0108_PLCD_DI, KS0108_PLCD_RW, KS0108_PLCD_E, KS0108_PLCD_RST, KS0108_PLCD_BACKLIGHT};
#define KS0108_BACKLIGHT_ON	1
#define KS0108_BACKLIGHT_OFF	0

extern void ks0108_set_signal(enum ks0108_TGlcdSignal sig, uint8_t value);
extern void ks0108_set_CS_signal(uint8_t CS);
extern void ObtainConfigPort(void);
extern void BusTo_OUT(uint8_t value);
extern void BusTo_IN(void);
extern uint8_t ReadDatabus(void);
extern uint8_t MaxCS(void);


#endif /* KS0108_HAL_DRIVER_INC_KS0108_PHY_H_ */
