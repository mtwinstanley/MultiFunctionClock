/*
 * interrupt.c
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
#include "interrupt.h"
#include "clock.h"
#include "lcd.h"
#include "state.h"
#include <stdio.h>

/***************************************************/
/* ISRs */
/***************************************************/

void timer_isr(void *baseaddr_p) {
	tenths++;
	if (tenths > 9){
		tenths = 0;
		unix++;
	}
}

void north_isr(void *baseaddr_p) {
	if (state == STATE_SET_HOURS){
		time_hour++;
		if (time_hour == 24){
			time_hour = 0;
		}
	}
	if (state == STATE_SET_MINUTES){
		time_minute++;
		if (time_minute == 60){
			time_minute = 0;
		}
	}
	if (state == STATE_SET_SECONDS){
		time_second++;
		if (time_second == 60){
			time_second = 0;
		}
	}
	if (state == STATE_SET_12_24){
		time_12hr = !time_12hr;
	}
	if (state == STATE_ALARM_HOURS){
		alarm_hour++;
		if (alarm_hour == 255){
			alarm_hour = 23;
		}
	}
	if (state == STATE_ALARM_MINUTES){
		alarm_minute++;
		if (alarm_minute == 255){
			alarm_minute = 59;
		}
	}
	if (state == STATE_ALARM_SECONDS){
		alarm_second++;
		if (alarm_second == 255){
			alarm_second = 59;
		}
	}
	if (state == STATE_ALARM_AMPM){
		alarm_ampm = !alarm_ampm;
	}
	update = 1;
}

void south_isr(void *baseaddr_p) {
	if (state == STATE_SET_HOURS){
		time_hour--;
		if (time_hour == 255){
			time_hour = 23;
		}
	}
	if (state == STATE_SET_MINUTES){
		time_minute--;
		if (time_minute == 255){
			time_minute = 59;
		}
	}
	if (state == STATE_SET_SECONDS){
		time_second--;
		if (time_second == 255){
			time_second = 59;
		}
	}
	if (state == STATE_SET_12_24){
		time_12hr = !time_12hr;
	}
	if (state == STATE_ALARM_HOURS){
		alarm_hour--;
		if (alarm_hour == 255){
			alarm_hour = 23;
		}
	}
	if (state == STATE_ALARM_MINUTES){
		alarm_minute--;
		if (alarm_minute == 255){
			alarm_minute = 59;
		}
	}
	if (state == STATE_ALARM_SECONDS){
		alarm_second--;
		if (alarm_second == 255){
			alarm_second = 59;
		}
	}
	if (state == STATE_ALARM_AMPM){
		alarm_ampm = !alarm_ampm;
	}
	update = 1;
}

void east_isr(void *baseaddr_p) {
	state++;
	if (state == 10){
		state = 0;
	}
	update = 1;
}

void west_isr(void *baseaddr_p) {
	state--;
	if (state < 0){
		state = 0;
	}
	update = 1;
}

void center_isr(void *baseaddr_p) {
	if (state == STATE_DISPLAY_DATE){
		state = STATE_SET_HOURS;
	}
	else if (state == STATE_DISPLAY_ALARM){
		state = STATE_ALARM_HOURS;
	}
	else if (state == STATE_SET_HOURS){
		state = STATE_SET_MINUTES;
	}
	else if (state == STATE_SET_MINUTES){
		state = STATE_SET_SECONDS;
	}
	else if (state == STATE_SET_SECONDS){
		state = STATE_SET_12_24;
	}
	else if (state == STATE_SET_12_24){
		unix = time_hour * CLOCK_HOUR + time_minute * CLOCK_MINUTE + time_second;
		state = STATE_DISPLAY_DATE;
	}
	else if (state == STATE_ALARM_HOURS){
		state = STATE_ALARM_MINUTES;
	}
	else if (state == STATE_ALARM_MINUTES){
		state = STATE_ALARM_SECONDS;
	}
	else if (state == STATE_ALARM_SECONDS){
		if (time_12hr){
			state = STATE_ALARM_AMPM;
		}
		else {
			alarm_unix = alarm_hour * CLOCK_HOUR + alarm_minute * CLOCK_MINUTE + alarm_second;
			state = STATE_DISPLAY_DATE;
		}
	}
	else if (state == STATE_ALARM_AMPM){
		alarm_unix = alarm_hour * CLOCK_HOUR + alarm_minute * CLOCK_MINUTE + alarm_second;
		state = STATE_DISPLAY_DATE;
	}
	update = 1;
}
// Add your own ISRs here

void interrupt_init(){
	XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
	    		XPAR_AXI_INTC_0_FIT_TIMER_0_INTERRUPT_INTR,
	    		(XInterruptHandler)timer_isr,
	    		(void*) 0);
	XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
				XPAR_AXI_INTC_0_DEBOUNCER_0_OUTPUT1_INTR,
				(XInterruptHandler)north_isr,
				(void*) 0);
	XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
				XPAR_AXI_INTC_0_DEBOUNCER_0_OUTPUT2_INTR,
				(XInterruptHandler)west_isr,
				(void*) 0);
	XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
				XPAR_AXI_INTC_0_DEBOUNCER_0_OUTPUT3_INTR,
				(XInterruptHandler)south_isr,
				(void*) 0);
	XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
				XPAR_AXI_INTC_0_DEBOUNCER_0_OUTPUT4_INTR,
				(XInterruptHandler)east_isr,
				(void*) 0);
	XIntc_RegisterHandler(XPAR_AXI_INTC_0_BASEADDR,
				XPAR_AXI_INTC_0_DEBOUNCER_0_OUTPUT5_INTR,
				(XInterruptHandler)center_isr,
				(void*) 0);
	XIntc_MasterEnable(XPAR_AXI_INTC_0_BASEADDR);
	XIntc_SetIntrSvcOption(XPAR_AXI_INTC_0_BASEADDR, XIN_SVC_ALL_ISRS_OPTION);
	XIntc_EnableIntr(XPAR_AXI_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK |
			XPAR_DEBOUNCER_0_OUTPUT1_MASK | XPAR_DEBOUNCER_0_OUTPUT2_MASK |
			XPAR_DEBOUNCER_0_OUTPUT3_MASK | XPAR_DEBOUNCER_0_OUTPUT4_MASK |
			XPAR_DEBOUNCER_0_OUTPUT5_MASK);
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
    		(Xil_ExceptionHandler)XIntc_DeviceInterruptHandler,
    		(void*) 0);
    Xil_ExceptionEnable();
}


