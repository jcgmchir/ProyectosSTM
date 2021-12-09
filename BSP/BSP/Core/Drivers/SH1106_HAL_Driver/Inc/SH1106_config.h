
#ifndef INC_SH1106_CONFIG_H_
#define INC_SH1106_CONFIG_H_

#define DY_SH1106_WIDTH		132
#define DY_SH1106_HEIGHT	48
#define DY_SH1106_PAGES		8
#define DY_SH1106_SCR_WIDTH	 128
#define DY_SH1106_SCR_HEIGHT 64
#define DY_LEFT_MARGIN 		2

/* Display Commands*/

// SH1106 Commandset
// ------------------
// General commands

  #define SH1106_ADDRESS           0x3C
  // Command definition
  // -----------------------------------
  #define SH1106_COMMAND           0x80  /* Continuation bit=1, D/C=0; 1000 0000 */
  #define SH1106_COMMAND_STREAM    0x00  /* Continuation bit=0, D/C=0; 0000 0000 */
  #define SH1106_DATA              0xC0  /* Continuation bit=1, D/C=1; 1100 0000 */
  #define SH1106_DATA_STREAM       0x40  /* Continuation bit=0, D/C=1; 0100 0000 */

// Command 1
  #define SH1106_SET_LOWER_COLUMN  0x00	 /*Select column address, low Nible data, Range 0x00 to 0xFF, POR(0x00H)*/
// Command 2
  #define SH1106_SET_HIGHER_COLUMN 0x10	 /*Select column address, high Nible data, Range 0x10 to 0x1F, POR(0x10H)*/
// Command 3
  #define SH1106_SET_PUMP_VOLTAGE  0x30  /*Pump voltage, Range 0x30 to 0x33, POR(0x32)*/
// Command 4
  #define SH1106_SET_START_LINE    0x40  /*Select RAM display line for COM0, range 0x40 to 0x7F, POR(0x40)*/
// Command 5
  #define SH1106_SET_CONTRAST      0x81  /*Set contrast*/ /*Next byte contrast value form 0x00 to 0xFF, POR(0x80)*/
// Command 6
  #define SH1106_SEG_REMAP_R_ROT   0xA0  /*Set segment remap Right, POR()*/
  #define SH1106_SEG_REMAP_L_ROT   0xA1  /*Set segment remap left*/
// Command 7
  #define SH1106_DIS_REFLECTS_RAM  0xA4  /*Not set entire display ON, POR()*/
  #define SH1106_DIS_ENT_DISP_ON   0xA5  /*Set entire display ON, LEFT()*/
// Command 8
  #define SH1106_DIS_NORMAL        0xA6  /*Set Normal, POR()*/
  #define SH1106_DIS_INVERSE       0xA7  /*Set Reverse*/
// Command 9
  #define SH1106_SET_MUX_RATIO     0xA8  /*Set MuxRatio*/ /*Next Byte set Mux Ratio form 0 to 63, POR(0x3F)*/
// Command 10
  #define SH1106_SET_DCDC_ON	   0x8B	 /*Set DC-DC state set, 1st byte*/
  #define SH1106_SET_DCDC_OFF	   0x8A  /*2nd byte to DCDC off*/
  #define SH1106_SET_DCDC_CM_SET   0xAD  /*2nd byte to DCDC on POR()*/
// Command 11
  #define SH1106_DISPLAY_OFF       0xAE	 /*Turns Panel OFF POR()*/
  #define SH1106_DISPLAY_ON        0xAF  /*Turns Panel ON*/
// Command 12
  #define SH1106_SET_PAGE_ADRESS   0xB0	 /*Select Page Address, low nible data, Range 0xB0 to 0xBF PAGE (0-7) POR(0xB0)*/
// Command 13
  #define SH1106_COM_SCAN_DIR      0xC0  /*Select SCAN DIRECTION COM increase POR()*/
  #define SH1106_COM_SCAN_DIR_REV  0xC8  /*Select SCAN DIRECTION COM decrease*/
// Command 14
  #define SH1106_DISPLAY_OFFSET    0xD3	 /*Display start line column*/ /*Next byte OFFSET 0 to 63 POR(0x00)*/
// Command 15
  #define SH1106_DIS_CLOCK_DIV_RT  0xD5  /*Set display divide Ratio and Oscillator frequency*/ /*Next DIVIDE RATIO 1 to 16 low nibble +50% to -25% (5% step) high nibble POR(0x50)*/
// Command 16
  #define SH1106_SET_PRECHARGE     0xD9  /*Set display precharge and discharge in DCLK (0 invalid, 1 to 15)*/ /*Next PRECHARGE low nibble DISCHARGE high nibble POR(0x22)*/
// Command 17
  #define SH1106_COM_PADS_CONF     0xDA  /*Common Pads HW configuration mode set, 1st byte*/
  #define SH1106_COM_PADS_CONF_SEQ 0x02	 /*2nd byte command COM31 to COM 0, SEG 0 to SEG 131, COM 32 to COM 63*/
  #define SH1106_COM_PADS_CONF_ALT 0x12  /*2nd byte command COM62,60 to COM 2,0  SEG 0 to SEG 131, COM 1,3 to COM 62,63 POR()*/
// Command 18
  #define SH1106_VCOM_DESELECT     0xDB  /*Set Common pads output voltage level*/ /*Next VCOM 0 to 63 (0.43+0.006415*Val) Vref, 64 a 255 = Vref POR(0x35)*/
// Command 19
  #define SH1106_READ_MOD_WR_START 0xE0  /*Set Read Modify Write mode*/
// Command 20
  #define SH1106_READ_MOD_WR_END   0xEE  /*Ends Read Modify Write mode*/
// Command 21
  #define SH1106_NOP			   0xE3

/* Display Status*/
  #define SH1106_READ_ST_BUSY_MASK	0x80
  #define SH1106_READ_ST_BUSY		SH1106_READ_ST_BUSY_MASK
  #define SH1106_READ_ST_READY		0x00
  #define SH1106_READ_ST_DYOFF_MASK	0x40
  #define SH1106_READ_ST_OFF		SH1106_READ_ST_DYOFF_MASK
  #define SH1106_READ_ST_ON			0x00

#endif /* INC_SH1106_CONFIG_H_ */
