/*
 * clock.c
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
#include "clock.h"
#include <stdio.h>

char time[8];
char alarm[8];
volatile Xuint8 time_hour = 0, time_minute = 0, time_second = 0, time_12hr = 0;
volatile Xuint8 alarm_hour = 0, alarm_minute = 0, alarm_second = 0, alarm_ampm = 0;
volatile Xuint32 unix = 0, prevunix = 0, alarm_unix = 0;
volatile Xuint8 tenths = 0;

char* getTime(Xuint32 unix){
	Xuint32 t = unix;
	Xuint8 hour = 0, min = 0, sec = 0;
	hour = unix / CLOCK_HOUR;
	t = unix - (CLOCK_HOUR*hour);
	min = t / CLOCK_MINUTE;
	sec = t - (CLOCK_MINUTE*min);
	if (time_12hr && hour > 12){
		hour = hour - 12;
	}
	else if (time_12hr && hour == 0){
		hour = 12;
	}
	sprintf(time, "%02d:%02d:%02d", hour, min, sec);
	return time;
}

void getHour(Xuint32 unix){
	time_hour = unix / CLOCK_HOUR;
}

void getMinute(Xuint32 unix){
	Xuint32 t = unix;
	Xuint8 hour = 0;
	hour = unix / CLOCK_HOUR;
	t = unix - (CLOCK_HOUR*hour);
	time_minute = t / CLOCK_MINUTE;
}

void getSecond(Xuint32 unix){
	Xuint32 t = unix;
	Xuint8 hour = 0, min = 0;
	hour = unix / CLOCK_HOUR;
	t = unix - (CLOCK_HOUR*hour);
	min = t / CLOCK_MINUTE;
	time_second = t - (CLOCK_MINUTE*min);
}
char* getAlarm(){
	sprintf(alarm, "%02d:%02d:%02d", alarm_hour, alarm_minute, alarm_second);
	return alarm;
}
