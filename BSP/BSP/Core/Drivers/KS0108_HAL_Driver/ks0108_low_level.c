/*
 * ks0108.c
 *
 *  Created on: 12 feb. 2017
 *      Author: Juan Carlos
 */

#include "..\Common\Inc\display.h"

//#include "Inc\ks0108_low_level.h"
//#include "Inc\ks0108_config.h"
//#include "Inc\ks0108_phy.h"


#ifdef DY_KS0108

// Delays, change for your display and uC, 0 generally, but take care of superfast 8051 i.e. Silabs
#define DELAY_RESET 65535
#define DELAY_TWL 	5		// 450 nS
#define DELAY_TWH	5		// 450 nS
#define DELAY_TDHWR	1		// data hold time for read and write 20 ns
#define DELAY_TASU	2		// address set-up time 140 nS
#define DELAY_TD	4		// data delay time 320 nS max.
#define DELAY_READ	10
#define MAX_BUSY_WAIT 200	// wait cnt. for the no busy condition, avoids software lock if glcd malfunction

//Prototype Functions
void ks0108_write_instruction(uint8_t cmd);
void ks0108_write_data(uint8_t cmd);
uint8_t ks0108_read_data(void);
void ks0108_no_busy(void);
void ks0108_reset(void);
void ks0108_backlight(uint8_t state);

uint32_t retardo;
// Aprox 100 ns per unit

void ks0108_delay(uint32_t cnt)
{
	retardo=cnt/2;
	while (retardo>0)
		retardo--;
}


/*************************************************************************************************/
// ------ write data to the selected CSx of the glcd

void ks0108_write_data(uint8_t data) {

	// it is assumed that the right chip is selected
	ks0108_no_busy();

    ks0108_set_signal(PLCD_E,0);		// enable off
    ks0108_set_signal(PLCD_DI,1);		// data mode
    ks0108_set_signal(PLCD_RW,0);		// write mode
    ks0108_set_signal(PLCD_DATA_WR,data);// write data

	// strobe
	ks0108_delay(DELAY_TWL);
    ks0108_set_signal(PLCD_E,1);
	ks0108_delay(DELAY_TWH);
    ks0108_set_signal(PLCD_E,0);
	ks0108_delay(DELAY_TDHWR);
}


/*************************************************************************************************/
// ------ write an instruccion to the selected CSx of the glcd
void ks0108_write_instruction(uint8_t cmd) {
	// it is assumed that the right chip is selected
	ks0108_no_busy();

	ks0108_set_signal(PLCD_E,0);		// enable off
    ks0108_set_signal(PLCD_DI,0);		// instruction mode
    ks0108_set_signal(PLCD_RW,0);	    // write mode
    ks0108_set_signal(PLCD_DATA_WR,cmd);// write command

	// strobe
	ks0108_delay(DELAY_TWL);
    ks0108_set_signal(PLCD_E,1);
	ks0108_delay(DELAY_TWH);
    ks0108_set_signal(PLCD_E,0);
	ks0108_delay(DELAY_TDHWR);
}

/*************************************************************************************************/
// ------ read a data from the selected CSx of the glcd

uint8_t ks0108_read_data(void) {
	uint8_t data;
	ks0108_no_busy();

    ks0108_set_signal(PLCD_DATA_RD,0xFF);	//Modo Lectura
    ks0108_set_signal(PLCD_E,0);		// enable
    ks0108_set_signal(PLCD_DI,1);	// data mode
    ks0108_set_signal(PLCD_RW,1);	// read mode

	// strobe
	ks0108_delay(DELAY_TASU);
    ks0108_set_signal(PLCD_E,1);
	ks0108_delay(DELAY_READ);
    data=ReadDatabus();
	ks0108_delay(DELAY_TD);
    ks0108_set_signal(PLCD_E,0);
    return data;

}

/*************************************************************************************************/
// ------ waits until no busy but with max loops iterations

void ks0108_no_busy(void) {

	uint8_t wait_cnt;
	uint8_t data;
    ks0108_set_signal(PLCD_DATA_RD,0xFF);	// Read mode
    ks0108_set_signal(PLCD_E,0);			// enable off
    ks0108_set_signal(PLCD_DI,0);			// instruction mode
    ks0108_set_signal(PLCD_RW,1);			// read mode

	// strobe
	wait_cnt = MAX_BUSY_WAIT;
    do
    {
    	ks0108_delay(DELAY_TASU);
    	ks0108_set_signal(PLCD_E,1);
    	ks0108_delay(DELAY_READ);
    	data=ReadDatabus();
        ks0108_set_signal(PLCD_E,0);
		wait_cnt--;
    }
    while (((data & LCD_BUSY_FLAG) != 0) && (wait_cnt!=0));
}

/*************************************************************************************************/
// -------- prepare LCD for its use and clear the screen ------------------------

void ks0108_reset(void) {

	uint8_t i;
    ks0108_set_signal(PLCD_E,0);
    ks0108_set_CS_signal(0);
    ks0108_set_signal(PLCD_DI,1);
    ks0108_set_signal(PLCD_RW,1);
    ks0108_set_signal(PLCD_DATA_RD,0xFF);

    ks0108_set_signal(PLCD_RST,0);
    ks0108_delay(DELAY_RESET);

    ks0108_set_signal(PLCD_RST,1);
    ks0108_delay(DELAY_RESET);

    ObtainConfigPort();

    for (i=1;i<=MaxCS();i++)
    {
    	ks0108_set_CS_signal(i);
		ks0108_write_instruction(LCD_DISP_START);/* Adress base for line 0 */
    }

    ks0108_set_CS_signal(0);
    ks0108_backlight(BACKLIGHT_ON);
}

void ks0108_backlight(uint8_t state)
{
	ks0108_set_signal(PLCD_BACKLIGHT,state);
}

#endif //DY_KS0108

