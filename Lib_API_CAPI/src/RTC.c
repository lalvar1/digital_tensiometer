/*
 * RTC.c
 *
 *  Created on: May-2013
 *  	Author: Pablo Montalti
 */

#include "RTC.h"

int RTCInicializado = 0;

void (*RTCAlarm_Handler)(void); //Callbacks a la rutinas a ejecutar para las fuentes de interrupción

int RTCset_date (RTCDate * date)
{
	int status;

	if(!RTCInicializado){
		status = RTCInit();
		if (!status)
			return 0;
		RTCInicializado = 1;
	}

	RTCconfigure_date(date);

	return 1;
}

int RTCset_alarm (RTCDate * alarm_date, void(*callback_alarm_handler)(void))
{

	RTCAlarm_Handler = callback_alarm_handler;
	RTCconfigure_alarm(alarm_date);
}
