/*
 * state.c
 *
 *  Created on: 7 Apr 2016
 *      Author: mw833
 */
#include "xparameters.h"
#include "xbasic_types.h"
#include "lcd.h"
#include "clock.h"
#include "state.h"

#include <stdio.h>

char time[8];
volatile Xuint8 state = 0, mode = 0, alarm = 0, update = 0;
volatile Xuint8 prevstate = 0, prevmode = 0, prevalarm = 0;

void print_time(){
	lcd_move(0,4);
	lcd_print(getTime(unix));
	if (time_12hr){
		getHour(unix);
		lcd_move(0,13);
		if (time_hour > 12){
			lcd_print("pm");
		}
		else {
			lcd_print("am");
		}
	}
}
void state_date(){
	lcd_clear();
	print_time();
	lcd_move(1,4);
	lcd_print("DD/MM/YY");
	lcd_display_ctrl(LCD_DISPLAY_ON | LCD_CURSOR_OFF);
}

void state_alarm(){
	lcd_clear();
	print_time();
	lcd_move(1,1);
	lcd_print("A");
	lcd_move(1,4);
	lcd_print(getAlarm());
	lcd_display_ctrl(LCD_DISPLAY_ON | LCD_CURSOR_OFF);
}

void state_setTime_hours(){
	getHour(unix);
	getMinute(unix);
	getSecond(unix);
	state_update_setScreen();
}

void state_update_setScreen(){
	lcd_clear();
	lcd_move(0,0);
	lcd_print("SET");
	lcd_move(0,4);
	sprintf(time, "%02d:%02d:%02d", time_hour, time_minute, time_second);
	lcd_print(time);
	lcd_move(0,13);
	if (time_12hr){
		lcd_print("12");
	}
	else {
		lcd_print("24");
	}
	lcd_move(1,4);
	lcd_print("DD/MM/YY");
	lcd_display_ctrl(LCD_DISPLAY_ON | LCD_CURSOR_ON);
	if (state == STATE_SET_HOURS){
		lcd_move(0,5);
	}
	else if (state == STATE_SET_MINUTES){
		lcd_move(0,8);
	}
	else if (state == STATE_SET_SECONDS){
		lcd_move(0,11);
	}
	else if (state == STATE_SET_12_24){
		lcd_move(0,14);
	}
}

void state_update_alarmScreen(){
	lcd_clear();
	lcd_move(0,0);
	lcd_print("SET");
	lcd_move(1,4);
	sprintf(time, "%02d:%02d:%02d", alarm_hour, alarm_minute, alarm_second);
	lcd_print(time);
	lcd_move(1,13);
	if (time_12hr){
		if (alarm_ampm){
			lcd_print("pm");
		}
		else {
			lcd_print("am");
		}
	}
	lcd_display_ctrl(LCD_DISPLAY_ON | LCD_CURSOR_ON);
	if (state == STATE_ALARM_HOURS){
		lcd_move(1,5);
	}
	else if (state == STATE_ALARM_MINUTES){
		lcd_move(1,8);
	}
	else if (state == STATE_ALARM_SECONDS){
		lcd_move(1,11);
	}
	else if (state == STATE_ALARM_AMPM){
		lcd_move(1,14);
	}
}
