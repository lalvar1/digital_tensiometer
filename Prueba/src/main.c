/**
 * Name        : main.c
 * Version     :
 * Description : main definition for FreeRTOS application
 */

/*
 * FreeRTOS includes
 */
//#include "FreeRTOS.h"
//#include "task.h"
//#include "queue.h"
//#include "semphr.h"

#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE

void __error__(char *pcFilename, unsigned long ulLine) {
}

/*
===============================================================================
 Name        : main.c
 Author      :
 Version     :
 Copyright   : Copyright (C)
 Description : main definition
===============================================================================
*/

/////////////////////////////////TENSIOMETRO DIGITAL-PROYECTO 4TO AÑO////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////HEADERS/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cr_section_macros.h>
#include <NXP/crp.h>

#include "GPIO.h"
#include "lpc_176X_PinNames.h"
#include "lpc_176X_PeriphNames.h"
#include "LPC17xx.h"
#include "LCD_text.h"
#include "LCD_Definitions.h"


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
//#include "basic_io.h"


GPIO SSEL;
GPIO MOTOR;
GPIO VALVULA;
volatile float Vout_channel0[1100],Vout_channel1[1100];

uint8_t Lectura_EEPROM[650];

typedef struct{
		float presion;
		uint8_t flag_channel;
	}param;

typedef struct{
	int Pres_Media;
	int Pres_diastolica;
	int Pres_sistolica;
}presiones;

#define REPOSO 		0
#define INFLANDO 	1
#define DESINFLANDO 2
#define CALCULO 	3
#define LECTURA 	4
#define MOSTRAR 	5

void Inic_Interrupciones(void);

xQueueHandle Cola_Var=NULL;
xQueueHandle Cola_param=NULL;
xSemaphoreHandle Sem_ADC=0;

xSemaphoreHandle Sem_I2C;

xSemaphoreHandle Sem_lectura=0;
xSemaphoreHandle Sem_General=0;
xQueueHandle Cola_Eint=NULL;
xQueueHandle Cola_LCD=NULL;
xQueueHandle Cola_I2C=NULL;

xQueueHandle Item=NULL;
xQueueHandle Cola_RTC=NULL;

xQueueHandle Item_direccion=NULL;

static uint8_t ESTADO=LECTURA;
//LCDtext display;

//////////////////////////////////////////////////ADC////////////////////////////////////////////////////////////
#define ADC_VREF	5
#define ESCALA_ADC	5

presiones Calcular_Presiones();

//////////////////////////////////////////////////RTC////////////////////////////////////////////////////////////


#define RTC_INTERRUPCION_SEG		0

typedef struct {
	uint32_t seg;
	uint32_t min;
	uint32_t hora;
	uint32_t dia_mes;
	uint32_t dia_semana;
	uint32_t dia_anio;
	uint32_t mes;
	uint32_t anio;
} RTC_HoraFecha;


void Inic(void);
void Display_HoraFecha(void);

// Prototipos
void Inic_RTC(void);
void RTC_HabilitaInterrupcion(uint32_t);
void RTC_SetHoraFecha(RTC_HoraFecha*);
void RTC_GetHoraFecha(RTC_HoraFecha*);

////////////////////////////////////////////PWM//////////////////////////////////////////////////////////////////////

#define PRENDER_MOTOR		iniciar_pwm_flanco_simple(3,90,250);
#define APAGAR_MOTOR		iniciar_pwm_flanco_simple(3,0,250);

#define CERRAR_VALVULA		iniciar_pwm_flanco_simple(4,100,250);
#define ABRIR_VALVULA		iniciar_pwm_flanco_simple(4,72,250);
#define ABRIR_VALVULA_TOT	iniciar_pwm_flanco_simple(4,0,250);

int iniciar_pwm_flanco_simple(uint8_t canal,uint8_t duty,uint32_t preescaler);
int parar_pwm(uint8_t canal);

////////////////////////////////////////////LCD//////////////////////////////////////////////////////

#define COLUMNAS            16
#define FILAS               2
#define LCD_D4               GPIO__0_5
#define LCD_D5               GPIO__0_10
#define LCD_D6               GPIO__2_4
#define LCD_D7               GPIO__2_5
#define LCD_RS               GPIO__2_6
#define LCD_EN               GPIO__0_4

#define INT_DIGITOS 63
static char buf[INT_DIGITOS + 2];		//!< Buffer para INT_DIGITS dígitos, signo - y fin de string '\0'

LCDtext display;
xQueueHandle xQueueLCD;

void LCDPutString(const char * str, unsigned char x_0, unsigned char y_0);
void LCD(void *pvParameters);
char * itoa(int i, unsigned int base);

///////////////////////////////////////////////DRIVERS/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ARRANCAR_I2C		(LPC_I2C1->I2CONSET=0x60)

//////////////////////////////////////////////I2C/////////////////////////////////////////////////////////////////

void Inic_I2C(){
	LPC_SC->PCONP |= (0x1<<19);				//habilito I2C1 que esta en el bit 19 del PCONP
	LPC_SC->PCLKSEL1 |=(0x3<<6);			//elijo un clock de 12.5MHz

	LPC_PINCON->PINSEL0  |= 0xF;				//pongo a P0.0 y P0.1 en modo 11 para que funcionen como SDA y SCL
	LPC_PINCON->PINMODE0 |= 0xA;				//no deben ser ni pull up ni pull down las lineas (pag 428)
	LPC_PINCON->PINMODE_OD0 |=0x3;				//las lineas deben estar en open drain

	NVIC->ISER[0] |=(0x1<<11);					//habilito interrupcion en el NVIC

	//al elegir el clock de 12.5MHz necesito que se trabaje a 100Khz por ende de la formula en la pagina 448
	//necesito que la suma de los registros me de 500

	LPC_I2C1->I2SCLH=0x7D;				//lo hago valer 250
	LPC_I2C1->I2SCLH=0x7D;				//lo hago valer 250

	LPC_I2C1->I2CONSET=0x40;			//prendo el I2C al poner el bit EN en 1
}


//Esta memoria posee 32768 posiciones en donde se contienen 8-bits (Bytes).
//Por eso dice que es de 256kbits, o sea 32768x8=262144=256k-bits.

//el bloque de memoria va a ir desde el 0x0000 al 0x7FFF
//cuando se haya calculado correctamente una presion se enviara a la EEPROM el siguiente bloque de 13 Bytes

//	| Centena de Sistolica 	|
//	| Decena de Sistolica	|
//	| Unidad de Sistolica	|
//	| Decena de Diastolica	|
//	| Unidad de Diastolica	|
//	| Decena Dia del Mes	|
//	| Unidad Dia del Mes	|
//	| 	   Decena Mes		|
//	|	   Unidad Mes		|
//	| 	   Decena Hora		|
//	| 	   Unidad Hora		|
//	|	  Decena Minutos	|
//	| 	  Unidad Minutos	|


#define CARGANDO 	0
#define DATOS		1


///////////////////////////////////////////////RTC/////////////////////////////////////////////////////////////////
void Inic_RTC(void)
{

	LPC_RTC->ILR=0x00;			//limpio Flags
	LPC_RTC->CIIR=0x00;			//Deshabilito Interrupciones
	LPC_RTC->AMR=0xFF;			//Enmascaro comparadores de alarma
	LPC_RTC->CALIBRATION=0x00;	//Inicializo registro de calibracion
	LPC_RTC->CCR=0x01;			//Arranca contador

	RTC_HabilitaInterrupcion(RTC_INTERRUPCION_SEG);

}

void RTC_HabilitaInterrupcion(uint32_t tipo_int)
{
	LPC_RTC->CIIR |= 1<< tipo_int;	//se habilita el tipo de interrupcion pedido
	LPC_RTC->ILR = 0x03;				//limpio flags de interrupcion

	NVIC->ISER[0] |= 1<<17;			//habilito interrupcion desde el NVIC

}

void RTC_SetHoraFecha(RTC_HoraFecha* horafecha)
{
	LPC_RTC->SEC = horafecha->seg;
	LPC_RTC->MIN = horafecha->min;
	LPC_RTC->HOUR = horafecha->hora;
	LPC_RTC->DOM = horafecha->dia_mes;
	LPC_RTC->DOW = horafecha->dia_semana;
	LPC_RTC->DOY = horafecha->dia_anio;
	LPC_RTC->MONTH = horafecha->mes;
	LPC_RTC->YEAR = horafecha->anio;
}

void RTC_GetHoraFecha(RTC_HoraFecha* horafecha)
{
	horafecha->seg = LPC_RTC->SEC;
	horafecha->min = LPC_RTC->MIN;
	horafecha->hora = LPC_RTC->HOUR;
	horafecha->dia_mes = LPC_RTC->DOM;
	horafecha->dia_semana = LPC_RTC->DOW;
	horafecha->dia_anio = LPC_RTC->DOY;
	horafecha->mes = LPC_RTC->MONTH;
	horafecha->anio = LPC_RTC->YEAR;
}


void RTC_IRQHandler(void)
{
	LPC_RTC->ILR |= 0xFF;		//limpio todos los flags de interrupcion
}

/////////////////////////////////////////////////PWM//////////////////////////////////////////////////////////////

int iniciar_pwm_flanco_simple(uint8_t canal,uint8_t duty,uint32_t preescaler)
{
LPC_SC->PCONP|=(1<<6);    //Habilito el PWM1
LPC_PWM1->PR=preescaler;    //25MHz/(100*Preescaler)=250kHz/Preescaler

switch(canal)
{
      case 3: 	//P2.2 es el PWM1.3
            {
                LPC_PINCON->PINSEL4&=~((0x3<<4));
                LPC_PINCON->PINSEL4|=(0x1<<4);		//pongo el motor como PWM
                LPC_PINCON->PINMODE4&=~((3<<4));  //Pull-up

                LPC_PWM1->MR3=duty;
                break;
            }

        case 4: //P2.3 es el PWM1.4
            {
                LPC_PINCON->PINSEL4&=~((0x3<<6));
                LPC_PINCON->PINSEL4|=(0x1<<6);		//pongo la valvula como PWM
                LPC_PINCON->PINMODE4&=~((3<<6));    //Pull-up

                LPC_PWM1->MR4=duty;
                break;
            }
        default:{return -1;}
    }
    LPC_PWM1->MR0=100;    // Máximo valor del duty -> 100%
    LPC_PWM1->LER=(1<<canal)|(1<<0);

    LPC_PWM1->MCR|=(1<<1);    //Reseteo el contador cuando llega MR0

    LPC_PWM1->CTCR=0;    //Funciona por matcheo , no por captura.
    LPC_PWM1->TCR=0x9;	//Habilito la cuenta y el modo PWM

    LPC_PWM1->PCR &= ~(1<<canal) ;//Deshabilito el flanco doble en el canal
    LPC_PWM1->PCR|=(1<<(8+canal));//Habilito salida PWM por flanco simple
    return 1;
}

int parar_pwm(uint8_t canal)
{
    if(canal>6)
        return -1;
    else
    {
        if(!canal)
            return -1;

        LPC_PWM1->PCR&=~(1<<(8+canal));    //Deshabilito salida PWM
    }

    return 1;
}

////////////////////////////////////////////////ADC///////////////////////////////////////////////////////////////

void Inic_ADC(void){
	LPC_PINCON->PINSEL0 |= (0x2<<30);		//P0.15 COMO SCK0
	LPC_PINCON->PINSEL1 |= (0x2<<02);		//P0.16 COMO MISO0
	LPC_PINCON->PINSEL1 |= (0x2<<04);		//P0.9 COMO MOSI0

	GPIO_Init(&SSEL, SALIDA, ALTO, (int)GPIO__0_16); //EL SSEL LO USO COMO GPIO,
	//CUANDO QUIERA ARRANCAR A COMUNICAR LO PONGO EN BAJO

	//el PCLKSEL del SSP1 lo dejo en 00, es decir el PLCK_SSP1 sera 25MHz
	//el PCONP del SSP1 amanece prendido

	NVIC->ISER[0] |= (0x1<<14);	//habilito interrupcion del SPI en el NVIC

	LPC_SSP0->CPSR =250; 	//el preescaler lo pongo en 50, por lo que la frecuencia del clock que
	//enviare sera de 500 KHz
	LPC_SSP0->CR0= 0x7;		//transmito 8 bits, modo SPI, modo 00, SCR=0
	LPC_SSP0->CR0 |= (0x9<<8);
	LPC_SSP0->IMSC= 0x2;
	LPC_SSP0->CR1=0x2;		//al final de la inicializacion
}



///////////////////////////////////////INTERRUPCIONES e INICIALIZACIONES////////////////////////////////////////////

GPIO SW1;
GPIO SW2;

void Inic_Pulsadores(){

	GPIO_Init(&SW1,ENTRADA,BAJO,GPIO__2_10);
	GPIO_Init(&SW2,ENTRADA,BAJO,GPIO__2_11);

}


void SetupHardware(void){

	SystemInit();
	Inic_RTC();
	Inic_ADC();
	Inic_Pulsadores();
	Inic_I2C();
	LCDtextInit  (&display, FILAS, COLUMNAS, (int)LCD_D4, (int)LCD_D5, (int)LCD_D6, (int)LCD_D7, (int)LCD_RS, (int)LCD_EN);

}

void SSP0_IRQHandler(){

	uint32_t var;
	portBASE_TYPE y;

	var=LPC_SSP0->DR;

	LPC_SSP0->ICR=0x2;
	xQueueSendFromISR(Cola_Var,&var,y);
	portEND_SWITCHING_ISR(&y);

}


//////////////////////////////////////////////LCD//////////////////////////////////////////////////


void LCDPutString(const char * str, unsigned char x_0, unsigned char y_0)
{
	unsigned char i=0;
   while(str[i]!=0)
   {
	   LCDtextGotoXY(&display, x_0+i , y_0);
	   LCDtextPutchar(&display, str[i]);
	   i++;
   }
}

char * itoa(int i, unsigned int base)
{
	char *p = buf + INT_DIGITOS + 1; /* apunta a posición de unidades */
	int dig, signo=0;
	if (i<0) {signo=1;i = -i;}
	if(base<=0 || base>36) base=10; /*evita división por cero */

	do { dig=(i%base); if (dig <=9) *--p = '0' + dig; else *--p= '7'+ dig ; i /= base;}
	while (i != 0);

	if(signo) *--p = '-';
	return p;
}


///////////////////////////////////////////////TAREAS//////////////////////////////////////////////

void ADC(){

	param parametros;
	static presiones Pres;
	unsigned int resultado=0;
	float vout,vout_final=0;
	uint32_t var,var1,var2,cont_ch0=0,cont_ch1=0;
	parametros.flag_channel=0;

	int aux, cola_presiones[5];

	static uint16_t i,j,k,aux5=0;
	static int posicion;
	static float Vout_Media=0,Vout_diastolica=0;
	static float min=0.1,aux2=0;
	float Vector_aux[220],Vector_aux2[4],dif,aux3;


	portTickType x_adc= xTaskGetTickCount();

	while(1){

		if(ESTADO==REPOSO){
			cont_ch0=cont_ch1=parametros.flag_channel=parametros.presion=0;
		}

		if((ESTADO==INFLANDO)||(ESTADO==DESINFLANDO))
			{

				var=var2=resultado=vout=vout_final=0;

				Pasivar(&SSEL);				//pasivo SSEL para seleccionar al ADC

				LPC_SSP0->DR=0x1;
				xQueueReceive(Cola_Var,&var,portMAX_DELAY);

				if(!(parametros.flag_channel))					//invierto entre el channel0 y el channel1
					LPC_SSP0->DR=0x80;
				else
					LPC_SSP0->DR=0x90;

				xQueueReceive(Cola_Var,&var,portMAX_DELAY);
				var1=(var&0x3);

				LPC_SSP0->DR=0xFF;
				xQueueReceive(Cola_Var,&var,portMAX_DELAY);
				var2=var;

				resultado= (var2 | (var1<<8));		//esta es la cuenta del adc
				vout= resultado*ADC_VREF;		//este es el voltaje que tiene el adc
				vout_final=vout/1023;

				//Vout= Vs* (0.018*P+0.04) siendo Vs=5v

				parametros.presion= (((vout_final/5)-0.04)/0.018);	//presion en KPa
				parametros.presion*=7.5;			//presion en mmHg
				Activar(&SSEL);

				if(ESTADO==DESINFLANDO){
					if(!(parametros.flag_channel)){
						Vout_channel0[cont_ch0]=vout_final;
						parametros.flag_channel=1;
						cont_ch0++;
					}
					else{
						Vout_channel1[cont_ch1]=vout_final;
						parametros.flag_channel=0;
						cont_ch1++;
					}
				}

				xQueueSend(Cola_param,&parametros,0);
				xSemaphoreGive(Sem_ADC);

			}

		if(ESTADO==CALCULO){

				//1° hallo la posicion del punto maximo del channel 1

				for(i=100;i<1100;i++){
					if((Vout_channel1[i]>aux2)&&(Vout_channel1[i]<1.20)){
						posicion=i;
						aux2=Vout_channel1[i];
					}
				}

				//2° una vez obtenido la posicion del maximo en ch1 voy a la otra curva y busco esa posicion
				//para obtener la presion arterial media
				Vout_Media=0;
				for(i=1;i<4;i++){
					Vout_Media=Vout_Media+Vout_channel0[posicion+i];
					Vout_Media=Vout_Media+Vout_channel0[posicion-i];
				}

				Vout_Media=Vout_Media+Vout_channel0[posicion]; // Presion arterial a nivel de tension

				Vout_Media=Vout_Media/7;

				//3° a partir de la posicion Pres Media hay que sacar los picos

				for(i=posicion,j=0;i<1098;i=i+aux5)
				{
					if((Vout_channel1[i]>0.45)&&(Vout_channel1[i]<1.20)) //saco los picos presentes
					{
						k=0;
						Vector_aux2[k]=Vout_channel1[i];
						   aux5=1;

						if((Vout_channel1[i+1]>0.45)&&(Vout_channel1[i+1]<1.20)) //en el peor de los casos tengo 3 picos
						{
							Vector_aux2[k+1]=Vout_channel1[i+1];
							aux5=2;
						}
						if((Vout_channel1[i+2]>0.45)&&(Vout_channel1[i+2]<1.20))
						{
							Vector_aux2[k+2]=Vout_channel1[i+2];
							aux5=3;
						}

						for(k=0,aux3=0;k<aux5;k++) //calculo pico valido
						{
							if(Vector_aux2[k]>aux3)
							aux3=Vector_aux2[k];

						}
						Vector_aux[j]=aux3; //guardo pico correcto en vector que usare para pte max
						j++;
					}

					else
						aux5=1;

					}




				//4° con todos los picos sacamos la pendiente mas abrupta, es decir la amyor diferencia entre picos




				for(i=0;i<220;i++){
					if(((Vector_aux[i]-Vector_aux[i+1])>dif) && (Vector_aux[i+1]>min)){
						dif=Vector_aux[i]-Vector_aux[i+1];
						aux3=Vector_aux[i+1];
					}
				}



				//5° en aux3 guardo el valor vout correspondiente a la diastolica. ese valor lo busco en el vector del channel 1

				for(i=0;i<1100;i++){
					if(Vout_channel1[i]==aux3){
						posicion=i;
					}
				}

				//6° con la posicion de la diastolica en el channel1 nos vamos al channel 0 a sacar el vout de la diastolica

				for(i=1;i<4;i++){
						Vout_diastolica+=Vout_channel0[posicion+i];
						Vout_diastolica+=Vout_channel0[posicion-i];
					}

				Vout_diastolica+= Vout_channel0[posicion];

				Vout_diastolica/=7;


				//7° pasamos la arterial media y la diastolica a nivel de presion en vez de a tension

				//Vout= Vs* (0.018*P+0.04) siendo Vs=5v

				Pres.Pres_Media= ((((Vout_Media+0.1125)/5)-0.04)/0.018);	//presion en KPa
				Pres.Pres_Media*=7.50062;						//presion en mmHg

				Pres.Pres_diastolica= (((((Vout_diastolica)/5)-0.04)/0.018))*7.50062;	//presion en KPa

				//8° obtengo la presion sistolica con la formula 3PAM=2D+S

				Pres.Pres_sistolica=(int)(3*Pres.Pres_Media - 2*Pres.Pres_diastolica);

				Vout_Media=Vout_diastolica=0;

				LPC_SC->PCONP &=~(0x1<<21);
				LPC_SC->PCONP |= (0x1<<21);
				Inic_ADC();

			aux=Pres.Pres_sistolica/100;
			cola_presiones[0]=+aux;			//el 48 es para pasarlo a ascii
			Pres.Pres_sistolica%=100;
			aux=Pres.Pres_sistolica/10;
			cola_presiones[1]=+aux;
			Pres.Pres_sistolica%=10;
			cola_presiones[2]=+Pres.Pres_sistolica;

			aux=Pres.Pres_diastolica/10;
			cola_presiones[3]=+aux;
			Pres.Pres_diastolica%=10;
			cola_presiones[4]=Pres.Pres_diastolica;

			xQueueSend(Cola_LCD,&cola_presiones,0);
		}


		vTaskDelayUntil(&x_adc,25/portTICK_RATE_MS);
		//al hacer cada 25ms tomo muestras por canal cada 50ms es decir a una frecuencia de 20hz
		//nuestra frecuencia de señal es de 1hz

		}
}

#define CANT_REBOTES	10
#define NO_KEY 			0x4
#define TECLA_1			0x1
#define TECLA_2			0x2
#define DETECCION		1
#define OPRIMIDO		2
#define REBOTE2 		3



uint8_t Get_Tecla(){

	static uint8_t estado=REPOSO,CodAct=NO_KEY;
	static uint8_t cont=CANT_REBOTES;
	static uint8_t final=0;
	static uint8_t AUX=0;

	if(isActivo(&SW1))	CodAct=TECLA_1;
	else if(isActivo(&SW2))
		CodAct=TECLA_2;
	else
		CodAct=NO_KEY;

	switch(estado)
	{
	case REPOSO:
		if(CodAct!=NO_KEY)
		estado=DETECCION;
		break;
	case DETECCION:
		if(CodAct==NO_KEY)
		{
			estado=REPOSO;
			cont=CANT_REBOTES;
		}
		else{
			cont--;
			if(!cont)
			{
				AUX=CodAct;
				cont=CANT_REBOTES;
				estado=OPRIMIDO;
			}
		}
		break;
	case OPRIMIDO:
		if(CodAct==NO_KEY)
			estado=REBOTE2;
		break;
	case REBOTE2:
		if(CodAct!=NO_KEY){
			cont=CANT_REBOTES;
			estado=OPRIMIDO;
		}
		else{
			cont--;
			if(!cont){
				cont=CANT_REBOTES;
				estado=REPOSO;
				final=AUX;
			}
		}
		break;
	default:break;

	}

	if(!final)
		return NO_KEY;
	else{
		final=0;
		return AUX;
	}
}


void PRINCIPAL(){

	static param parametros;
	portTickType x= xTaskGetTickCount();
	uint8_t aux=0;

	static uint16_t i=0;
	uint8_t j;
	int vector_display[13];

	uint8_t Tecla;

	LCDPutString("Bienvenido",3,0);
	LCDPutString("Presione START",0,1);


	while(1){

		Tecla=Get_Tecla();					//llamo a una funcion que me devolvera
											//NO_KEY, TECLA1,TECLA2 segun si se aoreto una tecla o ninguna

			switch(ESTADO){

			case REPOSO:
				if(Tecla==TECLA_1)
				{
					LCDtextClear(&display);
					LCDPutString("CALCULANDO...",1,0);
					ESTADO=INFLANDO;
					PRENDER_MOTOR;
					CERRAR_VALVULA;
					Tecla=NO_KEY;
				}
				if(Tecla==TECLA_2)
				{
					LCDtextClear(&display);
					LCDPutString("MAPA MEMORIA",1,0);
					LCDPutString("PULSE START",2,1);
					xSemaphoreGive(Sem_lectura);
					xSemaphoreGive(Sem_General);
					ESTADO=LECTURA;
				}
				break;
			case INFLANDO:

				if(Tecla==TECLA_1)
				{
					LCDtextClear(&display);
					LCDPutString("Reiniciado",3,0);
					LCDPutString("Presione START",0,1);
					ESTADO=REPOSO;
					APAGAR_MOTOR;
					ABRIR_VALVULA_TOT;
				}

				if((xSemaphoreTake(Sem_ADC,0))&&(xQueueReceive(Cola_param,&parametros,0)==pdTRUE))
					{
						if(parametros.presion>170){
							APAGAR_MOTOR;
							ABRIR_VALVULA;
							ESTADO=DESINFLANDO;
						}
					}
				break;

			case DESINFLANDO:
				if(Tecla== TECLA_1)
				{
					LCDtextClear(&display);
					LCDPutString("Reiniciado",3,0);
					LCDPutString("Presione START",0,1);
					ESTADO=REPOSO;
					APAGAR_MOTOR;
					ABRIR_VALVULA_TOT;
				}

				if((xSemaphoreTake(Sem_ADC,0))&&(xQueueReceive(Cola_param,&parametros,0==pdTRUE)))
				{
					if((parametros.flag_channel)&&(parametros.presion<40)){
						ABRIR_VALVULA_TOT;
						ESTADO=CALCULO;
					}
				}
			break;
			case MOSTRAR:

				if(Tecla == TECLA_1)
				{
					if((Lectura_EEPROM[i]>9) ||(!(Lectura_EEPROM[i]+Lectura_EEPROM[i+1]+Lectura_EEPROM[i+2])))
					{
						//si ya no hay mas para leer, es decir esta vacio
						LCDtextClear(&display);
						LCDPutString("FIN MEMORIA",3,0);
						LCDPutString("Presione START",0,1);
						ESTADO=REPOSO;
						i=0;
					}
					else
					{
						for(j=0;j<13;j++)
						{
							vector_display[j]=Lectura_EEPROM[i+j];
						}
						i+=13;
						// ya levante toddo lo de la eeprom y se lo mando al lcd par que lo muestre
						xQueueSend(Cola_LCD,&vector_display,0);
					}
				}

				if(Tecla==TECLA_2)
				{
					LCDtextClear(&display);
					LCDPutString("FIN LECTURA",3,0);
					LCDPutString("Presione START",0,1);
					ESTADO=REPOSO;
					i=0;
				}
			}

			vTaskDelayUntil(&x,2.5/portTICK_RATE_MS);

		}

	}


void I2C1_IRQHandler(){
	portBASE_TYPE xTaskWokenByReceive = pdFALSE;
	portBASE_TYPE y=pdFALSE;
	uint8_t i=0;
	static int mensaje[5],mensaje_aux[8];
	static uint8_t cont=0,ESTADO_I2C=CARGANDO,contador=0,contador_aux=0;
	static uint16_t contador_lectura=0,direccion=0x0000;
	static uint8_t inicio=0;


	switch(LPC_I2C1->I2STAT)
	{
		case 0x08:
			LPC_I2C1->I2DAT=0xA0; //bit en 0 para escritura y direccion esclavo, si coincide me devuelve ack y va a 0x18
			LPC_I2C1->I2CONCLR=0x18; //11000
			break;
		case 0x10:
			LPC_I2C1->I2DAT=0xA1;// bit en 1 para lectura
			LPC_I2C1->I2CONCLR=0x18;//dir esclavo, si coincide devuelve ack y al estar en modo master receive voy al 0x40
			break;
		case 0x18:
			if(ESTADO==LECTURA)
			{
				LPC_I2C1->I2DAT=0x00;  //mando parte alta, voy a leer desde el principio
				LPC_I2C1->I2CONCLR=0x38;
			}
			else
			{ //me fijo que no este escrito ya el lugar de la memoria donde voy a guardar mis datos
				//recoriendo bloque por bloque, por eso +13
				while((Lectura_EEPROM[direccion]<9)&&(!(Lectura_EEPROM[direccion]+Lectura_EEPROM[direccion])))
				{
					direccion+=13;
				}

				LPC_I2C1->I2DAT=(uint8_t)((direccion&0xFF00)>>8);		//mando parte alta direccion del bloque a guardar
				LPC_I2C1->I2CONCLR=0x38;

			}
			break;
		case 0x28:
			if(ESTADO==LECTURA)
			{
				if(!cont)
				{
					cont++;
					LPC_I2C1->I2DAT=0x00; //mando parte baja
					LPC_I2C1->I2CONCLR=0x38;
				}
				else{		//Ya mande la direccion entera. Si tengo que leer mando la condicion de restart
					LPC_I2C1->I2CONSET=0x20;		//STA=1			//mando start condicion seguido de un ack
					LPC_I2C1->I2CONCLR=0x18;		//STO=SI=0
					cont=0;
				}
			}
			else
			{
				if(ESTADO_I2C==CARGANDO)//escritura
				{
					LPC_I2C1->I2DAT=(uint8_t)(direccion & 0x00FF);			//mando la parte baja de la direccion a escribir
					LPC_I2C1->I2CONCLR=0x38;
					ESTADO_I2C=DATOS;
					direccion+=13;
				}

				else if(ESTADO_I2C==DATOS)//ya mande toda la direccion ahora procedo a escribir datos
				{
					if(contador<5)						//escribo los datos de la presion
					{
						if(inicio)
						{
							inicio=0;
							xQueueReceiveFromISR(Cola_I2C,&mensaje,&xTaskWokenByReceive); //recibp presiones
							LPC_I2C1->I2DAT= mensaje[0];
							LPC_I2C1->I2CONCLR=0x38;
							contador++;

						}
						else{		//guardo el resto(no voy a recibir la cola de nuevo)
							LPC_I2C1->I2DAT= mensaje[contador];
							LPC_I2C1->I2CONCLR=0x38;
							contador++;

						}
					}
					else{
						if(contador_aux<8)						//escribo los datos de la hora y fecha
						{
							if(!inicio) //de nuevo pregunto por inicio para recibir la cola y despues levantar toddo sin recibir cola de nuevo
							{
								inicio=1;
								xQueueReceiveFromISR(Cola_RTC,&mensaje_aux,&y);
								LPC_I2C1->I2DAT= mensaje_aux[0];
								LPC_I2C1->I2CONCLR=0x38;
								contador_aux++;
							}
							else{
								LPC_I2C1->I2DAT= mensaje_aux[contador_aux];
								LPC_I2C1->I2CONCLR=0x38;
								contador_aux++;
							}
						}
						else{ //escribi todos los datos y mando start para empezar a leer
							contador=contador_aux=0;
							ESTADO_I2C=CARGANDO;
							LPC_I2C1->I2CONSET=0x10;			//mando condicion restart
							LPC_I2C1->I2CONCLR=0x28;

						}
					}

				}
			}
			break;
		case 0x40 :
			LPC_I2C1->I2CONCLR=0x38;		//STA=STO=SI=0
			LPC_I2C1->I2CONSET=0x04;		//AA=1 y entonces voy al 0x50
			break;

		case 0x48:
			LPC_I2C1->I2CONSET=0x20;		//STA=1
			LPC_I2C1->I2CONCLR=0x18;		//STO=SI=0
			break;


		case 0x50: //aca voy a entrar 648 veces, 50 bloques de 13 posiciones=650 total
			if(contador_lectura<648)
			{
				Lectura_EEPROM[contador_lectura]=LPC_I2C1->I2DAT;
				contador_lectura++;
				LPC_I2C1->I2CONCLR=0x38;			//STA=STO=SI=0
				LPC_I2C1->I2CONSET=0x04;			//AA=1
			}
			else{
				Lectura_EEPROM[contador_lectura]=LPC_I2C1->I2DAT;	//leo el dato 648 y recibire not ack al poner AA=0
				contador_lectura=0;									//entonces ire al 0x58
				LPC_I2C1->I2CONCLR=0x3C;						//STA=STO=SI=AA=0
			}
			break;
		case 0x58:
			Lectura_EEPROM[649]=LPC_I2C1->I2DAT; //guardo ultimo byte
			LPC_I2C1->I2CONSET=0x10;
			LPC_I2C1->I2CONCLR=0x28;
			if(!inicio){
				ESTADO=REPOSO;					//lo primero que hace el programa es leer la eeprom entera
				inicio=1;
			}
			else
				ESTADO=MOSTRAR;


			break;
	}



}



void I2C(void){

	int mensaje[5],mensaje_aux[8];
	RTC_HoraFecha Data;
	int aux;

		while(1)
		{
			xSemaphoreTake(Sem_General,portMAX_DELAY); //lo recibo despues de mostrar presiones medidas y cuando
													//se presiona tecla 2 porque se quiere leer datos

			if(xSemaphoreTake(Sem_lectura,0))
			{
				ARRANCAR_I2C;

			}


			if(xQueueReceive(Cola_I2C,&mensaje,0))
			{
				RTC_GetHoraFecha(&Data);			//obtengo la hora de la muestra

				xQueueSend(Cola_I2C,&mensaje,0);	//envio la presion al ISR para que la envie por I2C a la eeprom

				aux=(Data.dia_mes/10);	mensaje_aux[0]=aux;
				aux=(Data.dia_mes%10);	mensaje_aux[1]=aux;
				aux=(Data.mes/10);		mensaje_aux[2]=aux;
				aux=(Data.mes%10);		mensaje_aux[3]=aux;
				aux=(Data.hora/10);		mensaje_aux[4]=aux;
				aux=(Data.hora%10);		mensaje_aux[5]=aux;
				aux=(Data.min/10);		mensaje_aux[6]=aux;
				aux=(Data.min%10);		mensaje_aux[7]=aux;

				xQueueSend(Cola_RTC,&mensaje_aux,0); //envio hora actual para guardarla en eeprom

				ARRANCAR_I2C;




			}
		}
}


void LCD(void *pvParameters)
{
	portTickType x= xTaskGetTickCount();
	char* renglon;
	int mensaje[13],mensaje_aux[13];
	uint8_t i;

	while(1)
	{
		xQueueReceive(Cola_LCD, &mensaje, portMAX_DELAY);

		if(ESTADO!=MOSTRAR) //cuando voy a mostrar luego de medir
		{

				for(i=0;i<13;i++)
					mensaje_aux[i]=mensaje[i];

				LCDtextClear(&display);

				LCDPutString("Sistolica:",0,0);
				LCDPutString("Diastolica:",0,1);
				renglon=itoa(mensaje_aux[0],10);
				LCDPutString(renglon,11,0);
				renglon=itoa(mensaje_aux[1],10);
				LCDPutString(renglon,12,0);
				renglon=itoa(mensaje_aux[2],10);
				LCDPutString(renglon,13,0);

				renglon=itoa(mensaje_aux[3],10);
				LCDPutString(renglon,11,1);
				renglon=itoa(mensaje_aux[4],10);
				LCDPutString(renglon,12,1);
				ESTADO=REPOSO;

				xQueueSend(Cola_I2C,&mensaje_aux,0);
				xSemaphoreGive(Sem_General);
			}
		else //cuando muestro al leer la eeprom
		{
			for(i=0;i<13;i++)
				mensaje_aux[i]=mensaje[i];
			LCDtextClear(&display);
			LCDPutString("S:",0,0);
			renglon=itoa(mensaje_aux[0],10);
			LCDPutString(renglon,2,0);
			renglon=itoa(mensaje_aux[1],10);
			LCDPutString(renglon,3,0);
			renglon=itoa(mensaje_aux[2],10);
			LCDPutString(renglon,4,0);
			LCDPutString("D:",6,0);
			renglon=itoa(mensaje_aux[3],10);
			LCDPutString(renglon,8,0);
			renglon=itoa(mensaje_aux[4],10);
			LCDPutString(renglon,9,0);

			renglon=itoa(mensaje_aux[5],10);
			LCDPutString(renglon,3,1);
			renglon=itoa(mensaje_aux[6],10);
			LCDPutString(renglon,4,1);
			LCDPutString("/",5,1);
			renglon=itoa(mensaje_aux[7],10);
			LCDPutString(renglon,6,1);
			renglon=itoa(mensaje_aux[8],10);
			LCDPutString(renglon,7,1);

			renglon=itoa(mensaje_aux[9],10);
			LCDPutString(renglon,10,1);
			renglon=itoa(mensaje_aux[10],10);
			LCDPutString(renglon,11,1);
			LCDPutString(":",12,1);
			renglon=itoa(mensaje_aux[11],10);
			LCDPutString(renglon,13,1);
			renglon=itoa(mensaje_aux[12],10);
			LCDPutString(renglon,14,1);

		}
	}

}





int main(void) {


	//Incialización del Hardware
		SetupHardware();

		//Creación de las tareas
		xTaskCreate(ADC,"ADC",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+2,NULL);
		xTaskCreate(PRINCIPAL,"TENSIOMETRO",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+1,NULL);
		xTaskCreate(LCD,"LCD",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY+3,NULL);
		xTaskCreate(I2C,"I2C",(configMINIMAL_STACK_SIZE),NULL,tskIDLE_PRIORITY+4,NULL);


		Cola_Var=xQueueCreate(2,sizeof(uint32_t));
		Cola_param=xQueueCreate(2,sizeof(param));
		Cola_Eint=xQueueCreate(2,sizeof(uint8_t));
		Cola_LCD = xQueueCreate(2, sizeof(int[13]));
		Cola_I2C = xQueueCreate(2,sizeof(int[5]));
		Cola_RTC = xQueueCreate(2,sizeof(int[8]));


		vSemaphoreCreateBinary(Sem_General);
		vSemaphoreCreateBinary(Sem_ADC);
		vSemaphoreCreateBinary(Sem_I2C);
		vSemaphoreCreateBinary(Sem_lectura);



		//Inicio el Scheduler
		vTaskStartScheduler();

		// Enter an infinite loop, just incrementing a counter
		volatile static int i = 0 ;
		while(1) {
			i++ ;
		}
		return 0 ;
}

void vApplicationTickHook ( void )
{

}

void vApplicationIdleHook ( void )
{
	__ASM volatile ("wfe");
}


