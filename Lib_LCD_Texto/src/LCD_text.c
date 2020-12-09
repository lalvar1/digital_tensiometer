/*
 * LCD_text.c
 *
 *  Created on: 07/04/2012
 *      Author: Alejandro
 */

#include "CAPI_Definitions.h"
#include "GPIO.h"
#include "BUS.h"
#include "LCD_text.h"
#include "TIMER.h"

//En el de 2x16, las direcciones de inicio son 00h, 40h
//En el de 4x20, las direcciones de inicio son 00h, 40h, 14h, 54h
//Lo dejo hard-coded asi, si luego otros displays son incompatibles habra que
//agregar una lista de estos inicios

enum {
	DIRECCION_COMIENZO_LINEA_0 = 0x00L,
	DIRECCION_COMIENZO_LINEA_1 = 0x40L,
	DIRECCION_COMIENZO_LINEA_2 = 0x14L,
	DIRECCION_COMIENZO_LINEA_3 = 0x54L
};

#define L_BUFFER_DISPLAY 200
static char displayBuffer[L_BUFFER_DISPLAY];	// FIXME! Asignalo como en la uart, es una truchada esto

enum LCD_DELAYS_US {	// Valores tomados del datasheet con ciertos margenes de seguridad
	DELAY_EN_CYCLE_TIME = 1,	// De acuerdo al datasheet, los pulsos de enable no pueden ser muy proximos
	DELAY_TIEMPO_INSTRUCCION = 60,
	DELAY_POWERUP = 60*1000,
	DELAY_CLEAR_SCREEN = 2000
};

//-----------------------------------------------------------------------------
// Declaracion de funciones locales
static int	getPosicionPantalla (LCDtext * display);
static bool esFinDeLinea (LCDtext * display);
static void avanzarLinea (LCDtext * display);

static void writeCommand(LCDtext * display, int command);
static void writeData	(LCDtext * display, int data);
static void writeByte	(LCDtext * display, int dato);
static void writeNibble	(LCDtext * display, int nibble);

//-----------------------------------------------------------------------------

void	LCDtextInit		(LCDtext * display, int n_filas, int n_columnas, int D4, int D5, int D6, int D7, int RS, int EN)
{
	BusInit(&display->busDatos, SALIDA, ALTO);
	BusAgregarPin(&display->busDatos, D4);	// Agregar primero el menos significativo!
	BusAgregarPin(&display->busDatos, D5);
	BusAgregarPin(&display->busDatos, D6);
	BusAgregarPin(&display->busDatos, D7);

	GPIO_Init(&display->RS, SALIDA, ALTO, RS);
	GPIO_Init(&display->EN, SALIDA, ALTO, EN);

	display->n_filas		= n_filas;
	display->n_columnas		= n_columnas;
	display->filaActual 	= 0;
	display->columnaActual	= 0;

	ColaCircular_Init(&display->buffer, displayBuffer, L_BUFFER_DISPLAY);

	TIMERdelay(DELAY_POWERUP);
	AsignarNivel(&display->RS, BAJO);

	/**********************************************************************************************
	 * ERRATA IMPORTANTE: La hoja de datos del controlador KS0066 en su pagina 27 dice que hay
	 * que escribir dos veces el nibble  (LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4) >> 4)
	 * Al menos en el controlador que viene con la rubenboard (WH1602B) hay que hacerlo
	 * una vez sola, sino el display la primera vez se incializa siempre en modo 1-Linea
	 *********************************************************************************************/
	writeNibble(display, (LCD_COMMAND_FUNCTION | LCD_FUNCTION_BUS_4) >> 4);
	writeNibble(display, ( n_filas > 1 ? LCD_FUNCTION_LINES_2 : LCD_FUNCTION_LINES_1 ) | LCD_FUNCTION_FONT_5X8 );
	TIMERdelay(DELAY_TIEMPO_INSTRUCCION);

	writeCommand(display, LCD_COMMAND_DISPLAY | LCD_DISPLAY_DISPLAY_ON | LCD_DISPLAY_CURSOR_ON | LCD_DISPLAY_BLINK_OFF);
	TIMERdelay(DELAY_TIEMPO_INSTRUCCION);

	writeCommand(display, LCD_COMMAND_CLEAR);
	TIMERdelay(DELAY_CLEAR_SCREEN);

	writeCommand(display, LCD_COMMAND_ENTRY_MODE | LCD_MODE_INCREMENT | LCD_MODE_SHIFT_NO);
	TIMERdelay(DELAY_TIEMPO_INSTRUCCION);
}

res_t	LCDtextPuts		(LCDtext * display, const char * s)
{
	ColaCircular * out = &display->buffer;
	while(*s){	// TODO: No estoy chequeando que la cola pueda contener el mensaje
		ColaPoner(out, *s++);
	}
	return CAPI_EXITO;
}

//TODO: Este es el hardware putChar, el que usa el worker, no el Stream::putchar, hacelo static!
void 	LCDtextPutchar	(LCDtext * display, int value)
{
    if (value == '\n') {
    	avanzarLinea(display);
    } else {
    	writeData(display, value);
        display->columnaActual++;
        if (esFinDeLinea(display)) {
        	avanzarLinea(display);
        }
    }
}

void	LCDtextGotoXY	(LCDtext * display, int x, int y)
{
	display->columnaActual = x;
	display->filaActual = y;
	int posicion = getPosicionPantalla(display);
	writeCommand(display, posicion);
	TIMERdelay(DELAY_CLEAR_SCREEN);
}

void 	LCDtextClear	(LCDtext * display) {
    writeCommand(display, LCD_COMMAND_CLEAR); // cls, and set cursor to 0
    TIMERdelay(DELAY_CLEAR_SCREEN);
}

void	LCDworker 		(LCDtext * display)
{
#if 0
	if(displayBusy(display)){
		return CAPI_ERROR;
	}
#endif
	ColaCircular * out = &display->buffer;
	if(!ColaVacia(out)){
		LCDtextPutchar(display, ColaSacar(out)); // Solo datos, los comandos van por funciones aparte
	}
	return;
}

//-----------------------------------------------------------------------------

static int getPosicionPantalla (LCDtext * display)
{
	int posicionFila = LCD_COMMAND_DDRAM;
	switch(display->filaActual)
	{
		case 0:
			posicionFila += DIRECCION_COMIENZO_LINEA_0;
			break;
		case 1:
			posicionFila += DIRECCION_COMIENZO_LINEA_1;
			break;
		case 2:
			posicionFila += DIRECCION_COMIENZO_LINEA_2;
			break;
		case 3:
			posicionFila += DIRECCION_COMIENZO_LINEA_3;
			break;
		default:
			posicionFila += DIRECCION_COMIENZO_LINEA_0;
			break;
	}

	return posicionFila + display->columnaActual;
}

static bool esFinDeLinea (LCDtext * display)
{
	return display->columnaActual >= display->n_columnas;
}

static void avanzarLinea (LCDtext * display)
{
	display->columnaActual = 0;
	display->filaActual++;
	if (display->filaActual >= display->n_filas) {
		display->filaActual = 0;
		LCDtextClear(display);
	} else {
		LCDtextGotoXY(display, display->columnaActual, display->filaActual);
	}
}

//-----------------------------------------------------------------------------

static void writeCommand(LCDtext * display, int command)
{
	AsignarNivel(&display->RS, BAJO);
    writeByte(display, command);
}

static void writeData(LCDtext * display, int data)
{
	AsignarNivel(&display->RS, ALTO);
	writeByte(display, data);
}

static void writeByte(LCDtext * display, int dato)
{
	writeNibble(display, NIBBLE_ALTO(dato));
	writeNibble(display, NIBBLE_BAJO(dato));
	TIMERdelay(DELAY_TIEMPO_INSTRUCCION);
}

static void writeNibble(LCDtext * display, int nibble)
{
	Activar(&display->EN);
	BusPoner(&display->busDatos, nibble);
	Pasivar(&display->EN);
	TIMERdelay(DELAY_EN_CYCLE_TIME);
}

//Cosas tomadas de ElmChan:
//Fuel indicator (bateria), Bargraph, Point. Estan sin portar

/*-----------------------------------------------------------------------*/
/* Put a fuel indicator                                                  */
/*-----------------------------------------------------------------------*/

#if _USE_FUEL
void lcd_put_fuel (
	int8_t val,		/* Fuel level (-1:plugged, 0:empty cell, ..., 5:full cell) */
	uint8_t chr		/* User character to use */
)
{
	static const uint8_t plg[8] = {10,10,31,31,14,4,7,0};
	uint8_t gfx[8], d, *p;
	int8_t i;


	if (val >= 0) {		/* Cell (0..5) */
		p = &gfx[8];
		*(--p) = 0; *(--p) = 0x1F;
		for (i = 1; i <= 5; i++) {
			d = 0x1F;
			if (val < i) d = (i == 5) ? 0x1B : 0x11;
			*(--p) = d;
		}
		*(--p) = 0x0E;
	} else {			/* Plug (-1) */
		p = (uint8_t*)plg;
	}
	lcd_setcg(chr, 1, p);
	lcd_putc(chr);
}


#endif

/*-----------------------------------------------------------------------*/
/* Draw bargraph                                                         */
/*-----------------------------------------------------------------------*/

#if _USE_BAR
void lcd_put_bar (
	uint16_t val,	/* Bar length (0 to _MAX_BAR represents bar length from left end) */
	uint8_t width,	/* Display area (number of chars from cursor position) */
	uint8_t chr		/* User character code (2 chars used from this) */
)
{
	static const uint8_t ptn[] = {
		0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0x80, 0,
		0xF0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0xC0, 0,
		0xF0, 0xF0, 0xE0, 0xE0, 0xE0, 0xC0, 0xC0, 0
	};
	const uint8_t *pp;
	uint16_t n, m, s, gi;
	uint8_t gfx[16];


	for (n = 0; n < 16; n++)		/* Register common pattern (space/fill) */
		gfx[n] = n < 7 ? 0 : 0xFF;
	lcd_setcg(_BASE_GRAPH, 2, gfx);

	/* Draw edge pattern into gfx[] */
	val = (unsigned long)val * (width * 18) / (_MAX_BAR + 1);
	pp = &ptn[(val % 3) * 8];		/* Get edge pattern */
	s = val / 3 % 6;				/* Bit shift */
	for (n = 0; n < 7; n++) {		/* Draw edge pattern into the pattern buffer */
		m = (*pp++ | 0xFF00) >> s;
		gfx[n] = m;
		gfx[n + 8] = m >> 6;
	}

	/* Put graphic pattern into the LCD module */
	gi = val / 18;						/* Indicator start position */
	for (n = 1; n <= width; n++) {		/* Draw each location in the bargraph */
		if (n == gi) {					/* When edge pattern is exist at the location */
			m = chr + 1;				/* A edge pattern */
		} else {
			if (n == gi + 1) {
				lcd_setcg(chr, 2, gfx);	/* Register edge pattern */
				m = chr;
			} else {
				m = (n >= gi) ? _BASE_GRAPH : _BASE_GRAPH + 1;	/* A space or fill */
			}
		}
		lcd_putc(m);					/* Put the character into the LCD */
	}
}
#endif

/*-----------------------------------------------------------------------*/
/* Draw point indicator                                                  */
/*-----------------------------------------------------------------------*/

#if _USE_POINT
void lcd_put_point (
	uint16_t val,	/* Dot position (0 to _MAX_POINT represents left end to write end) */
	uint8_t width,	/* Display area (number of chars from cursor position) */
	uint8_t chr		/* User character code (2 chars used from this) */
)
{
	static const uint8_t ptn[] = {
		0x06, 0x0C, 0x0C, 0x0C, 0x18, 0x18, 0x18, 0,
		0x06, 0x06, 0x0C, 0x0C, 0x0C, 0x18, 0x18, 0,
		0x06, 0x06, 0x06, 0x0C, 0x0C, 0x0C, 0x18, 0
	};
	const uint8_t *pp;
	uint16_t n, m, s, gi;
	uint8_t gfx[16];


	for (n = 0; n < 16; n++)		/* Register common pattern (space) */
		gfx[n] = n < 7 ? 0 : 0xFF;
	lcd_setcg(_BASE_GRAPH, 1, gfx);

	/* Draw edge pattern into gfx[] */
	val = (uint32_t)val * (width * 18 - 12) / (_MAX_BAR + 1);
	pp = &ptn[(val % 3) * 8];		/* Get edge pattern */
	s = val / 3 % 6;				/* Bit shift */
	for (n = 0; n < 7; n++) {		/* Draw edge pattern into the pattern buffer */
		m = *pp++; m <<= 6; m >>= s;
		gfx[n] = m;
		gfx[n + 8] = m >> 6;
	}
	lcd_setcg(chr, 2, gfx);				/* Register dot pattern */

	/* Put graphic pattern into the LCD module */
	gi = val / 18;						/* Indicator start position */
	for (n = 0; n < width; n++) {		/* Draw each location in the bargraph */
		if (n == gi) {					/* When edge pattern is exist at the location */
			m = chr + 1;				/* A edge pattern */
		} else {
			if (n == gi + 1)
				m = chr;
			else
				m = _BASE_GRAPH;		/* A space */
		}
		lcd_putc(m);					/* Put the character into the LCD */
	}
}
#endif


