#ifndef INC_SH1106_MEDIUM_LEVEL_H_
#define INC_SH1106_MEDIUM_LEVEL_H_

#define MODE_INVERTED 1
#define MODE_STANDAR  0

extern void sh1106_init_display(void);
extern void sh1106_set_contrast(uint8_t contrast);
extern void sh1106_clear_screen(void);
extern void sh1106_enable_sleep(void);
extern void sh1106_disable_sleep(void);
extern void sh1106_invert(uint8_t mode);

#endif
