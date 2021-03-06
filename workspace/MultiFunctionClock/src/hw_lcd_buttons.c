#include "xparameters.h"
#include "xbasic_types.h"
#include "xstatus.h"
#include "xio.h"
#include "xintc.h"
#include "xil_exception.h"
#include <stdio.h>

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
/* Utility functions */
/***************************************************/

void lcd_clear() {
    // Clears the screen and sets cursor to (0,0)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x01);
}

void lcd_home() {
    // Sets cursor to (0,0)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x00);
}

void lcd_entry_mode(Xuint32 command) {
    // Sets the entry mode (see LCD_ENTRY_* constants)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x04 | (command & 0x03));
}

void lcd_display_ctrl(Xuint32 command) {
    // Controls display and cursor (see LCD_DISPLAY_* and LCD_CURSOR_* constants)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x08 | (command & 0x07));
}

void lcd_nudge_cursor(Xuint32 command) {
    // Nudges cursor right or left (see LCD_NUDGE_* constants)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x10 | (command & 0x04));
}

void lcd_scroll(Xuint32 command) {
    // Scrolls entire display (see LCD_SCROLL_* constants)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x18 | (command & 0x04));
}

void lcd_cgram_set(Xuint32 address) {
    // Sets entry point to a CGRAM location, allowing custom character generation
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x40 | (address & 0x3F));
}

void lcd_ddram_set(Xuint32 address) {
    // Sets entry point to a DDRAM location, allowing text entry
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x80 | (address & 0x7F));
}

void lcd_data_write(Xuint32 data) {
    // Writes a byte to the current address (CGRAM or DDRAM)
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x100 | (data & 0xFF));
}

/***************************************************/
/* Convenience functions */
/***************************************************/

void lcd_init() {
    // 4-bit mode, 2 line display, etc.
    XIo_Out32(XPAR_LCD_0_BASEADDR, 0x2C);
    // Display on, no cursor
    lcd_display_ctrl(LCD_DISPLAY_ON);
    // Sensible default entry mode
    lcd_entry_mode(LCD_ENTRY_CURSOR_RIGHT);
    // Clear the screen
    lcd_clear();
}

void lcd_move(Xuint32 line, Xuint32 pos) {
    // Moves the cursor to a new position, line and pos both 0-indexed
    // Line may be 0 or 1, pos may be 0 to 39
    lcd_ddram_set((0x40 * (line%2)) + (pos%40));
}

void lcd_print(char *text) {
    // Prints a string to the screen (if the current address is in DDRAM)
    while (*text != 0) {
        lcd_data_write(*text);
        ++text;
    }
}

/***************************************************/
/* Utility functions */
/***************************************************/

// Converts an integer into an 11-character string
void num_to_text(int n, char *str) {
	// str should be sufficient to hold an 11-character string
	// The result will be padded to the right with spaces
	char temp[12];
	char *ptr = temp;
	char *out_ptr = str;
	if (n == 0) {
		str[0] = '0';
		str[1] = 0;
		return;
	}
	if (n < 0) {
		*out_ptr = '-';
		++out_ptr;
		n = -n;
	}
	while (n > 0) {
		*ptr = 48 + (n % 10);
		n = n / 10;
		++ptr;
	}
	while (ptr > temp) {
	  --ptr;
	  *out_ptr = *ptr;
	  ++out_ptr;
	}
	while (out_ptr < (str + 11)) {
		*out_ptr = ' ';
		++out_ptr;
   }
	*out_ptr = 0;
}

/***************************************************/
/* Global variables */
/***************************************************/

volatile Xuint32 count = 0;
char numString[12];

/***************************************************/
/* ISRs */
/***************************************************/

void timer_isr(void *baseaddr_p) {
	num_to_text(count, numString);
	lcd_move(1,25);
	lcd_print(numString);
	lcd_scroll(LCD_SCROLL_LEFT);
}
// Add your own ISRs here

/***************************************************/
/* Main program */
/***************************************************/

int main (void) {

	xil_printf("Interrupt Test\r\n");

    // Push data to write FIFO
    lcd_init();
    lcd_print("Hello, world!");
    lcd_move(1,10);
    lcd_print("Counter value:");

    Xil_ExceptionInit();
    XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
    		XPAR_AXI_INTC_0_FIT_TIMER_0_INTERRUPT_INTR,
    		(XInterruptHandler)timer_isr,
    		(void*) 0);
    XIntc_MasterEnable(XPAR_AXI_INTC_0_BASEADDR);
    XIntc_SetIntrSvcOption(XPAR_AXI_INTC_0_BASEADDR, XIN_SVC_ALL_ISRS_OPTION);
    XIntc_EnableIntr(XPAR_AXI_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
    		(Xil_ExceptionHandler)XIntc_DeviceInterruptHandler,
    		(void*) 0);
    Xil_ExceptionEnable();

    while (1) {
		// This loop does nothing: all activities are controlled by the ISR.
		// Lots of processing could take place here, interrupted occasionally to
		// scroll the screen!
    }
}
