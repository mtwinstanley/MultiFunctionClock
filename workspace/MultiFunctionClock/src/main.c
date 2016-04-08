/*
 * main.c
 *
 *  Created on: 7 Apr 2016
 *      Author: mw833
 */
#include "xparameters.h"
#include "xbasic_types.h"
#include "xstatus.h"
#include "xio.h"
#include "xintc.h"
#include "xil_exception.h"
#include "lcd.h"
#include "clock.h"
#include "interrupt.h"
#include "state.h"
#include <stdio.h>

/***************************************************/
/* Global variables */
/***************************************************/
char numString[12];
Xuint8 timeout = 0;

/***************************************************/
/* Main program */
/***************************************************/

int main (void) {

	xil_printf("Multifunctional Digital Clock\r\n");

    // Push data to write FIFO
    lcd_init();
    //lcd_print("Hello, world!");
    //lcd_move(1,10);
    //lcd_print("Counter value:");

    Xil_ExceptionInit();
    interrupt_init();
    //state = STATE_DISPLAY_DATE;
    //prevstate = STATE_DISPLAY_DATE;


    while (1) {
		// This loop does nothing: all activities are controlled by the ISR.
		// Lots of processing could take place here, interrupted occasionally to
		// scroll the screen!
    	if (unix != prevunix){
    		prevunix = unix;
    		if (state == STATE_DISPLAY_DATE){
    			state_date();
			}
    		else if (state == STATE_DISPLAY_ALARM){
    			state_alarm();
    			timeout++;
    			if (timeout == 30){
    				state = STATE_DISPLAY_DATE;
    				timeout = 0;
    			}
    		}
    	}
    	if (state == STATE_DISPLAY_DATE && prevstate != STATE_DISPLAY_DATE){
    		state_date();
    		prevstate = STATE_DISPLAY_DATE;
    		update = 0;
    	}
    	else if (state == STATE_DISPLAY_ALARM && prevstate != STATE_DISPLAY_ALARM){
    		state_alarm();
    		prevstate = STATE_DISPLAY_ALARM;
    		update = 0;
		}
    	else if (state == STATE_SET_HOURS && prevstate != STATE_SET_HOURS && prevstate != STATE_SET_MINUTES){
    		state_setTime_hours();
    		prevstate = STATE_SET_HOURS;
    		update = 0;
    	}
    	else if (state == STATE_SET_HOURS && update){
			state_update_setScreen();
			prevstate = STATE_SET_HOURS;
			update = 0;
		}
    	else if (state == STATE_SET_MINUTES && update){
    		state_update_setScreen();
			prevstate = STATE_SET_MINUTES;
			update = 0;
		}
    	else if (state == STATE_SET_SECONDS && update){
    		state_update_setScreen();
			prevstate = STATE_SET_SECONDS;
			update = 0;
		}
    	else if (state == STATE_SET_12_24 && update){
			state_update_setScreen();
			prevstate = STATE_SET_12_24;
			update = 0;
		}
    	else if (state == STATE_ALARM_HOURS && update){
			state_update_alarmScreen();
			prevstate = STATE_ALARM_HOURS;
			update = 0;
		}
		else if (state == STATE_ALARM_MINUTES && update){
			state_update_alarmScreen();
			prevstate = STATE_ALARM_MINUTES;
			update = 0;
		}
		else if (state == STATE_ALARM_SECONDS && update){
			state_update_alarmScreen();
			prevstate = STATE_ALARM_SECONDS;
			update = 0;
		}
		else if (state == STATE_ALARM_AMPM && update){
			state_update_alarmScreen();
			prevstate = STATE_ALARM_AMPM;
			update = 0;
		}
    }
}
