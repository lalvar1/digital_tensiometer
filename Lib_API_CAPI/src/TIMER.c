/*
 * TIMER.c
 *
 *  Created on: 25/06/2012
 *      Author: Alejandro
 *
 *  Modification @ May-2013: Include PWM to use with timer1
 *  	Author: Pablo Montalti
 */

void Timer0Init	(void);
void Timer0Count(int uSecDelay);

int flagTimer;
int timer0Inicializado = 0;
int timer1Inicializado = 0;
void (*TIMER1_MatchInterrupt_Handler[2])(void); //Callbacks a la rutinas a ejecutar

void TIMERdelay (int uSec){
	if(!timer0Inicializado){
		Timer0Init();
		timer0Inicializado = 1;
	}
	flagTimer = 0;
	Timer0Count(uSec);
	while(!flagTimer)
		;// Espero la interrupcion del timer que suba el flag
	return;
}

int TIMERpwm_start (int frequency_in_hertz, int duty_cycle_in_percentage, void (*callback_transition_to_inactive)(void), void(*callback_period_complete)(void))
{
	int status;

	if(!timer1Inicializado){
		status = Timer1Init_for_PWM(frequency_in_hertz, duty_cycle_in_percentage);
		if (!status)
			return 0;
		timer1Inicializado = 1;
		TIMER1_MatchInterrupt_Handler[0] = callback_transition_to_inactive;
		TIMER1_MatchInterrupt_Handler[1] = callback_period_complete;
	}
}
