/*
 * clock.h
 *
 *  Created on: 7 Apr 2016
 *      Author: mw833
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#define CLOCK_DAY		86400
#define	CLOCK_HOUR		3600
#define CLOCK_MINUTE	60

extern volatile Xuint8 time_hour , time_minute, time_second, time_12hr;
extern volatile Xuint8 alarm_hour, alarm_minute, alarm_second, alarm_ampm;

extern volatile Xuint32 unix, prevunix, alarm_unix;
extern volatile Xuint8 tenths;

void getHour(Xuint32 unix);
void getMinute(Xuint32 unix);
void getSecond(Xuint32 unix);

char* getTime(Xuint32 unix);
char* getAlarm(void);

#endif /* CLOCK_H_ */
