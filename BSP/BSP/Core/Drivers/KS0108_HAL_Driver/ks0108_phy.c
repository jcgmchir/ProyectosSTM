/*
 * ks0108_phy.c
 *
 *  Created on: 21 feb. 2017
 *      Author: Juan Carlos
 */
#include "..\Common\Inc\display.h"

#ifdef DY_KS0108

void ks0108_set_signal(enum ks0108_TGlcdSignal sig, uint8_t value);
void ks0108_set_CS_signal(uint8_t CS);
void ObtainConfigPort(void);
void BusTo_OUT(uint8_t value);
void BusTo_IN(void);
uint8_t ReadDatabus(void);

//#include "Inc\ks0108_config.h"
//#include "Inc\ks0108_phy.h"

/*************************************************************************************************/
/*
    Signals in push-pull mode
    Data bus: D7,D6,D5,D4,D3,D2,D1,D0 -> PA15,PB14,PB13,PA12,PA11,PA10,PA9,PA8. Only 5V tolerant pins.
    Control on port C only
    DY_CS1 -> PC10
    DY_CS2 -> PC11
    DY_DI  -> PC7
    DY_RW  -> PC8
    DY_E   -> PC9
    DY_RST -> PC6
*/

/* need to define in main.h
DY_DI_GPIO_Port
DY_RW_GPIO_Port
DY_E_GPIO_Port
DY_RES_N_GPIO_Port
EN_BACKLIGHT_GPIO_Port

DY_DI_Pin
DY_RW_Pin
DY_E_Pin
DY_RES_N_Pin
EN_BACKLIGHT_Pin
*/

/*need to change for port distribution*/
// Data port is distributed in two ports with consecutive pins, high byte
#define LESS_BIT_PORT	8
#define DATA_PORT_A 	GPIOA
#define SET_MASK_DY_A   (DY_D0_Pin|DY_D1_Pin|DY_D2_Pin|DY_D3_Pin|DY_D4_Pin|DY_D7_Pin)
#define DATA_MASK_DY_A	SET_MASK_DY_A
#define DATA_PORT_B 	GPIOB
#define SET_MASK_DY_B   (DY_D5_Pin|DY_D6_Pin)
#define DATA_MASK_DY_B	SET_MASK_DY_B

/*need to change for port distribution*/

uint32_t PortA_OUT_Bus;
uint32_t PortB_OUT_Bus;
uint32_t PortA_IN_Bus;
uint32_t PortB_IN_Bus;
uint32_t PortA_MASK_Bus;
uint32_t PortB_MASK_Bus;

#define CONTROL_PORT 	GPIOC
#ifdef DY_CS1_Pin
#define CS_PORT1		GPIOC
#endif
#ifdef DY_CS2_Pin
#define CS_PORT2		GPIOC
#endif
#ifdef DY_CS3_Pin
#define CS_PORT3		GPIOC
#endif
#ifdef DY_CS4_Pin
#define CS_PORT4		GPIOC
#endif
#ifdef DY_CS5_Pin
#define CS_PORT5		GPIOC
#endif
#ifdef DY_CS6_Pin
#define CS_PORT6		GPIOC
#endif
#ifdef DY_CS7_Pin
#define CS_PORT7		GPIOC
#endif
#ifdef DY_CS8_Pin
#define CS_PORT8		GPIOC
#endif


/*************************************************************************************************/
/* Basic GPIO functions to manage the graphic display
*/
void ks0108_set_signal(enum ks0108_TGlcdSignal sig, uint8_t value) {

//    ks0108_delay(100);
    switch(sig) {
    case KS0108_PLCD_DI:
        HAL_GPIO_WritePin(KS0108_DY_DI_GPIO_Port, KS0108_DY_DI_Pin, value);
        break;
    case KS0108_PLCD_RW:
        HAL_GPIO_WritePin(KS0108_DY_RW_GPIO_Port, KS0108_DY_RW_Pin, value);
        break;
    case KS0108_PLCD_E:
        HAL_GPIO_WritePin(KS0108_DY_E_GPIO_Port, KS0108_DY_E_Pin, value);
        break;
    case KS0108_PLCD_RST:
        HAL_GPIO_WritePin(KS0108_DY_RES_N_GPIO_Port, KS0108_DY_RES_N_Pin, value);
        break;
    case KS0108_PLCD_DATA_WR:
    	BusTo_OUT(value);
        break;
    case KS0108_PLCD_DATA_RD:
    	BusTo_IN();
	    break;
    case KS0108_PLCD_BACKLIGHT:
    	if (value==KS0108_BACKLIGHT_ON)
    		HAL_GPIO_WritePin(KS0108_EN_BACKLIGHT_Port,KS0108_EN_BACKLIGHT_Pin,GPIO_PIN_SET);
   		else if (value==BACKLIGHT_OFF)
    		HAL_GPIO_WritePin(KS0108_EN_BACKLIGHT_Port,KS0108_EN_BACKLIGHT_Pin,GPIO_PIN_RESET);
    	break;
    }
}

#define KS0108_MAX_CS	0

void ks0108_set_CS_signal(uint8_t CS) {
#ifdef KS0108_DY_CS1_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT1, KS0108_DY_CS1_Pin,(CS==1));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	1
#endif
#ifdef KS0108_DY_CS2_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT2, KS0108_DY_CS2_Pin,(CS==2));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	2
#endif
#ifdef KS0108_DY_CS3_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT3, KS0108_DY_CS3_Pin,(CS==3));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	3
#endif
#ifdef KS0108_DY_CS4_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT4, KS0108_DY_CS4_Pin,(CS==4));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	4
#endif
#ifdef KS0108_DY_CS5_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT5, KS0108_DY_CS5_Pin,(CS==5));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	5
#endif
#ifdef KS0108_DY_CS6_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT6, KS0108_DY_CS6_Pin,(CS==6));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	6
#endif
#ifdef KS0108_DY_CS7_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT7, KS0108_DY_CS6_Pin,(CS==7));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	7
#endif
#ifdef KS0108_DY_CS8_Pin
		HAL_GPIO_WritePin(KS0108_CS_PORT8, KS0108_DY_CS6_Pin,(CS==8));
#undef KS0108_MAX_CS
#define KS0108_MAX_CS	8
#endif
}

uint8_t MaxCS(void)
{
	return KS0108_MAX_CS;
}


/*************************************************************************************************/
// ------ Funciones de Getion de los GPIOS del Bus de Datos
// 		  aceleraci�n para configuraci�n de direcci�n de pines
//		  Asume que los pines estan en PORTx 15 a 8
/*************************************************************************************************/

void ObtainConfigPort(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = SET_MASK_DY_A;			//Change databus to Output Mode
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(DATA_PORT_A, &GPIO_InitStruct);
	PortA_OUT_Bus=GPIOA->CRH;
	GPIO_InitStruct.Pin = SET_MASK_DY_B;
	HAL_GPIO_Init(DATA_PORT_B, &GPIO_InitStruct);
	PortB_OUT_Bus=GPIOB->CRH;
	GPIO_InitStruct.Pin = SET_MASK_DY_A;			//Change databus to Input Mode
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(DATA_PORT_A, &GPIO_InitStruct);
	PortA_IN_Bus=GPIOA->CRH;
	GPIO_InitStruct.Pin = SET_MASK_DY_B;
	HAL_GPIO_Init(DATA_PORT_B, &GPIO_InitStruct);
	PortB_IN_Bus=GPIOB->CRH;
	PortA_MASK_Bus=~(PortA_OUT_Bus^PortA_IN_Bus);
	PortB_MASK_Bus=~(PortB_OUT_Bus^PortB_IN_Bus);
}

void BusTo_OUT(uint8_t value)
{
	uint32_t GPIO_CR;
    GPIO_CR=GPIOA->CRH;
   	GPIO_CR&=PortA_MASK_Bus;
   	GPIO_CR|=PortA_OUT_Bus;
   	GPIOA->CRH=GPIO_CR;
   	GPIO_CR=GPIOB->CRH;
   	GPIO_CR&=PortB_MASK_Bus;
   	GPIO_CR|=PortB_OUT_Bus;
   	GPIOB->CRH=GPIO_CR;
	GPIOA->BSRR=(SET_MASK_DY_A<<(LESS_BIT_PORT+8));				//Put the value to databus output pins
	GPIOA->BSRR=(SET_MASK_DY_A&(value<<LESS_BIT_PORT));
	GPIOB->BSRR=(SET_MASK_DY_B<<(LESS_BIT_PORT+8));
	GPIOB->BSRR=(SET_MASK_DY_B&(value<<LESS_BIT_PORT));

}

void BusTo_IN(void)
{
	uint32_t GPIO_CR;
    GPIO_CR=GPIOA->CRH;
   	GPIO_CR&=PortA_MASK_Bus;
   	GPIO_CR|=PortA_IN_Bus;
   	GPIOA->CRH=GPIO_CR;
   	GPIO_CR=GPIOB->CRH;
   	GPIO_CR&=PortB_MASK_Bus;
   	GPIO_CR|=PortB_IN_Bus;
   	GPIOB->CRH=GPIO_CR;
}

/*************************************************************************************************/
// ------ Read data from the selected CSx of the glcd
/*************************************************************************************************/

uint8_t ReadDatabus(void)
{
    uint16_t value;
    uint8_t dat;

    value=((GPIOA->IDR)&DATA_MASK_DY_A);
    value|=((GPIOB->IDR)&DATA_MASK_DY_B);
    dat = ((value>>LESS_BIT_PORT) & 0xFF);
    return(dat);

}

#endif //DY_KS0108
