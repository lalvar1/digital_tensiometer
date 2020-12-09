/*
 * lpc_17xx_TIMER.c
 *
 *  Created on: 25/06/2012
 *      Author: Alejandro
 */

#include "lpc17xx_timer.h"
#include "lpc17xx_clkpwr.h"

void Timer0Init (void)
{
	//Lo inicializo para que cuente de a 1uS, y que cuando llegue pare y resetee
	TIM_MATCHCFG_Type matchCfg;
	matchCfg.MatchChannel		= 0;
	matchCfg.IntOnMatch			= SET;
	matchCfg.StopOnMatch		= SET;
	matchCfg.ResetOnMatch		= SET;
	matchCfg.ExtMatchOutputType	= TIM_EXTMATCH_NOTHING;
	TIM_ConfigMatch(LPC_TIM0, &matchCfg);

	TIM_TIMERCFG_Type timerCfg;
	timerCfg.PrescaleOption = TIM_PRESCALE_USVAL;
	timerCfg.PrescaleValue	= 1;
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, (void*)&timerCfg);

	NVIC_EnableIRQ(TIMER0_IRQn);
}

void Timer0Count (int uSegundos)
{
	TIM_Cmd(LPC_TIM0, DISABLE);	//Parar la cuenta
	TIM_ResetCounter(LPC_TIM0);	//La reseteo
	TIM_UpdateMatchValue(LPC_TIM0, 0, uSegundos); // Cargo el valor hasta el que quiero contar
	TIM_Cmd(LPC_TIM0, ENABLE);	//Arrancar la cuenta
}

extern int flagTimer;
void TIMER0_IRQHandler (void)
{
	flagTimer = 1;
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

/*TIMER 1*/
#define OPTIMAL_FRACTION_ERROR 0.02

//Inicializado para manejar el PWM del ejemplo
int Timer1Init_for_PWM (int frequency_in_hertz, int duty_cycle_in_percentage)
{

	float counter_value_fraction, fcounter_value, pClk;
	int counter_value_to_use=-1, timer_prescaler_to_use, timer_prescaler, uClk_divider, uClk_divider_to_use, uClk;

	//Inicializo los parámettros de la cuenta que lleva el timer
	//Calculo previo para obtener la mejor resolución
	uClk = SystemCoreClock;
	for (uClk_divider = 4; uClk_divider>0 ; uClk_divider>>=1)
	{
		for (timer_prescaler = 100; timer_prescaler>0; timer_prescaler--)
		{
			pClk = (float)(uClk/uClk_divider);
			fcounter_value =  (float)(frequency_in_hertz * timer_prescaler);
			fcounter_value = pClk/fcounter_value;
			counter_value_fraction = fcounter_value - ((int)fcounter_value);
			if (counter_value_fraction > 0.5)
			{
				counter_value_fraction = (int)fcounter_value + 1 - fcounter_value;
				fcounter_value ++;
			}

			if(counter_value_fraction < OPTIMAL_FRACTION_ERROR)
			{
				timer_prescaler_to_use = timer_prescaler;
				uClk_divider_to_use = uClk_divider;
				counter_value_to_use = (int) fcounter_value;
				//rompo loop
				timer_prescaler = 1;
				uClk_divider = 1;
			}
		}
	}

	if(counter_value_to_use < 0)
		return 0;

	TIM_TIMERCFG_Type timerCfg;
	timerCfg.PrescaleOption = TIM_PRESCALE_TICKVAL;
	timerCfg.PrescaleValue	= timer_prescaler_to_use;
	TIM_Init(LPC_TIM1, TIM_TIMER_MODE, (void*)&timerCfg);
	switch (uClk_divider_to_use)
	{
	//case 8: CLKPWR_SetPCLKDiv (CLKPWR_PCLKSEL_TIMER1, CLKPWR_PCLKSEL_CCLK_DIV_8); break;
	case 4: CLKPWR_SetPCLKDiv (CLKPWR_PCLKSEL_TIMER1, CLKPWR_PCLKSEL_CCLK_DIV_4); break;
	case 2: CLKPWR_SetPCLKDiv (CLKPWR_PCLKSEL_TIMER1, CLKPWR_PCLKSEL_CCLK_DIV_2); break;
	case 1: CLKPWR_SetPCLKDiv (CLKPWR_PCLKSEL_TIMER1, CLKPWR_PCLKSEL_CCLK_DIV_1); break;
	default: CLKPWR_SetPCLKDiv (CLKPWR_PCLKSEL_TIMER1, CLKPWR_PCLKSEL_CCLK_DIV_4); break;
	}


	//Inicializo canal 0 para llevar cuenta del tiempo activo del PWM
	//No debe resetear el TC, pero debe generar una interrupción.
	TIM_MATCHCFG_Type matchCfg;
	matchCfg.MatchChannel		= 0;
	matchCfg.IntOnMatch			= SET;
	matchCfg.StopOnMatch		= RESET;
	matchCfg.ResetOnMatch		= RESET;
	matchCfg.ExtMatchOutputType	= TIM_EXTMATCH_NOTHING;
	TIM_ConfigMatch(LPC_TIM1, &matchCfg);

	//Inicializo canal 1 para llevar cuenta del tiempo del período del PWM
    //Debe resetear el TC y debe generar una interrupción.
	matchCfg.MatchChannel		= 1;
	matchCfg.IntOnMatch			= SET;
	matchCfg.StopOnMatch		= RESET;
	matchCfg.ResetOnMatch		= SET;
	matchCfg.ExtMatchOutputType	= TIM_EXTMATCH_NOTHING;
	TIM_ConfigMatch(LPC_TIM1, &matchCfg);

	TIM_Cmd(LPC_TIM1, DISABLE);	//Parar la cuenta
	TIM_ResetCounter(LPC_TIM1);	//La reseteo

	//Cuenta del período
	TIM_UpdateMatchValue(LPC_TIM1, 1, counter_value_to_use); // Cargo el valor hasta el que quiero contar
	//Cuenta del tiempo activo
	TIM_UpdateMatchValue(LPC_TIM1, 0, (counter_value_to_use*duty_cycle_in_percentage)/100); // Cargo el valor hasta el que quiero contar

	NVIC_EnableIRQ(TIMER1_IRQn);

	TIM_Cmd(LPC_TIM1, ENABLE);	//Arrancar la cuenta

	return 1;
}


extern void (*TIMER1_MatchInterrupt_Handler[2])(void); //Callbacks a la rutinas a ejecutar
void TIMER1_IRQHandler (void)
{

	if (TIM_GetIntStatus(LPC_TIM1,TIM_MR0_INT))
	{
		TIM_ClearIntPending(LPC_TIM1, TIM_MR0_INT);
		TIMER1_MatchInterrupt_Handler[0]();
	}

	if (TIM_GetIntStatus(LPC_TIM1,TIM_MR1_INT))
	{
		TIM_ClearIntPending(LPC_TIM1, TIM_MR1_INT);
		TIMER1_MatchInterrupt_Handler[1]();
	}
}
