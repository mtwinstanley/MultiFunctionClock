/*
 * state.h
 *
 *  Created on: 7 Apr 2016
 *      Author: mw833
 */

#ifndef STATE_H_
#define STATE_H_

#define STATE_DISPLAY_DATE		0
#define STATE_DISPLAY_ALARM		1
#define STATE_SET_HOURS			2
#define STATE_SET_MINUTES		3
#define STATE_SET_SECONDS		4
#define STATE_SET_12_24			5
#define STATE_ALARM_HOURS		6
#define STATE_ALARM_MINUTES		7
#define STATE_ALARM_SECONDS		8
#define STATE_ALARM_AMPM		9

#define ALARM_SET				0
#define ALARM_UNSET				1
#define ALARM_ALERT				2

extern volatile Xuint8 state, mode, alarm, update;
extern volatile Xuint8 prevstate, prevmode, prevalarm;

void state_date(void);
void state_alarm(void);
void state_setTime_hours(void);
void state_update_setScreen(void);
void state_update_alarmScreen(void);

#endif /* STATE_H_ */
