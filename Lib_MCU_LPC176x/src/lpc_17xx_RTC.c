/****************************************************************************
 *   $Id:: rtc.c 5743 2010-11-30 23:18:58Z usb00423                         $
 *   Project: NXP LPC17xx RTC example
 *
 *   Description:
 *     This file contains RTC code example which include RTC initialization, 
 *     RTC interrupt handler, and APIs for RTC access.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "lpc17xx.h"
#include "lpc17xx_rtc.h"
#include "RTC.h"

volatile uint32_t alarm_on = 0;
volatile uint32_t second_on;

//andrew
int RTCget_date(RTCDate * date)
{
    RTC_TIME_Type time;

    RTC_GetFullTime (LPC_RTC, &time);

    date->year = time.YEAR;
    date->month = time.MONTH;
    date->dayofyear = time.DOY;
    date->dayofmonth = time.DOM;
    date->dayofweek = time.DOW;
    date->hours = time.HOUR;
    date->minutes = time.MIN;
    date->seconds = time.SEC;

    return 1;
}

int RTCInit(void)
{
	RTC_Init (LPC_RTC);

	return 1;
}

int RTCconfigure_date(RTCDate * date)
{
	RTC_TIME_Type time;

	time.YEAR = date->year;
	time.MONTH = date->month;
	time.DOY = date->dayofyear;
	time.DOM = date->dayofmonth;
	time.DOW = date->dayofweek;
	time.HOUR = date->hours;
	time.MIN = date->minutes;
	time.SEC = date->seconds;

	RTC_SetFullTime (LPC_RTC, &time);

	return 1;
}

int RTCconfigure_alarm (RTCDate * alarm_date)
{
	RTC_TIME_Type time;

	time.YEAR = alarm_date->year;
	time.MONTH = alarm_date->month;
	time.DOY = alarm_date->dayofyear;
	time.DOM = alarm_date->dayofmonth;
	time.DOW = alarm_date->dayofweek;
	time.HOUR = alarm_date->hours;
	time.MIN = alarm_date->minutes;
	time.SEC = alarm_date->seconds;

	RTC_SetFullAlarmTime (LPC_RTC, &time);

	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_SECOND, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_MINUTE, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_HOUR, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_DAYOFWEEK, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_DAYOFMONTH, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_DAYOFYEAR, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_MONTH, ENABLE);
	RTC_AlarmIntConfig (LPC_RTC, RTC_TIMETYPE_YEAR, ENABLE);

	NVIC_EnableIRQ(RTC_IRQn);

	//Reset de la cuenta
	RTC_ResetClockTickCounter(LPC_RTC);
	//Lanzo a correr
	RTC_Cmd (LPC_RTC, ENABLE);

	return 1;
}


/*****************************************************************************
** Function name:		RTC_IRQHandler
**
** Descriptions:		RTC interrupt handler, it executes based on the
**						the alarm setting
**
** parameters:			None
** Returned value:		None
** 
*****************************************************************************/
extern void (*RTCAlarm_Handler)(void);

void RTC_IRQHandler (void) 
{  

	if (RTC_GetIntPending (LPC_RTC, RTC_INT_ALARM)== SET)
	{

		RTCAlarm_Handler();

		RTC_ClearIntPending (LPC_RTC, RTC_INT_ALARM);

	}
//  if(LPC_RTC->ILR & ILR_RTCCIF)	//Interrupts in Counter Increment
//  {
//	  if(LPC_RTC->CIIR & IMSEC)	//Seconds interrupt
//	  {
//		  second_on = 1;
//	  }
//
//	  LPC_RTC->ILR |= ILR_RTCCIF;		/* clear interrupt flag */
////  }
//  else if(LPC_RTC->ILR & ILR_RTCALF)	//Interrupts in Counter Increment
//  {
//	  LPC_RTC->ILR |= ILR_RTCALF;		/* clear interrupt flag */
//	  alarm_on = 1;
//  }

  return;
}

