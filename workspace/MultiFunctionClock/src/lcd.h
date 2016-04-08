/*
 * lcd.h
 *
 *  Created on: 7 Apr 2016
 *      Author: mw833
 */

#ifndef LCD_H_
#define LCD_H_

/***************************************************/
/* Constants */
/***************************************************/

// Display feature flags
#define LCD_DISPLAY_ON 0x4
#define LCD_DISPLAY_OFF 0x0
#define LCD_CURSOR_ON 0x2
#define LCD_CURSOR_OFF 0x0
#define LCD_CURSOR_BLINK 0x1
#define LCD_CURSOR_NO_BLINK 0x0
// Entry modes
#define LCD_ENTRY_CURSOR_RIGHT 0x2
#define LCD_ENTRY_CURSOR_LEFT 0x0
#define LCD_ENTRY_SCROLL_RIGHT 0x1
#define LCD_ENTRY_SCROLL_LEFT 0x3
// Cursor nudge
#define LCD_NUDGE_RIGHT 0x4
#define LCD_NUDGE_LEFT 0x0
// Scroll display
#define LCD_SCROLL_RIGHT 0x4
#define LCD_SCROLL_LEFT 0x0

/***************************************************/
/* Function Prototypes */
/***************************************************/
void lcd_clear(void);
void lcd_home(void);
void lcd_entry_mode(Xuint32 command);
void lcd_display_ctrl(Xuint32 command);
void lcd_nudge_cursor(Xuint32 command);
void lcd_scroll(Xuint32 command);
void lcd_cgram_set(Xuint32 address);
void lcd_ddram_set(Xuint32 address);
void lcd_data_write(Xuint32 data);

void lcd_init(void);
void lcd_move(Xuint32 line, Xuint32 pos);
void lcd_print(char *text);
void num_to_text(int n, char *str);

#endif /* LCD_H_ */
