#ifndef INC_NK5110_MEDIUM_LEVEL_H_
#define INC_NK5110_MEDIUM_LEVEL_H_

extern void nk5110_init_display(void);
extern void nk5110_set_contrast(uint8_t contrast);
extern void nk5110_clear_screen(void);
extern void nk5110_enable_sleep(void);
extern void nk5110_disable_sleep(void);
extern void nk5110_invert(uint8_t mode);

#endif
