/*
 * LCD_text.h
 *
 *  Created on: 07/04/2012
 *      Author: Alejandro
 */

#ifndef LCD_TEXT_H_
#define LCD_TEXT_H_

//TODO: Refactor! Renombralo a LCD44780 para que no queden dudas que es para ese tipo de display.

// Recibo la lista de pines en tiempo de ejecución, de modo de poder manejar multiples displays.

/* Modos sugeridos:
    - Modo Double-buffered: para evitar problemas de sincronismo.
    	Hay dos imagenes del display en memoria. Mientras se dibuja una al hardware se reciben datos en la otra.
    	Luego de un redibujo se intercambian.
	- Modo consola: Para mostrar texto al usuario. Agregarle una ColaCircular para contener los datos
		llegar al fin de la linea hace pasar el texto a la siguiente.
		cada linea nueva hace scroll vertical de la anterior con una pausa.
	- Controles graficos: Reservar un area del display para exhibir un valor, se le pasa un puntero
		al valor a exhibir y se actualiza periódicamente.
	- Menus navegables: Se define una lista de mensajes y valores de teclas en cada uno.
	*/

#include "ColaCircular.h"
#include "PIN.h"
#include "BUS.h"
#include "LCD_Definitions.h"

typedef struct LCDtextStruct {
	int n_filas;
	int n_columnas;
	int filaActual;
	int columnaActual;
	ColaCircular buffer;
	BUS busDatos;
	GPIO RS;
	GPIO EN;
} LCDtext;

typedef struct _LCDcaracter
{
   unsigned char caracter;
   unsigned char x;
   unsigned char y;
}LCDcaracter;

void	LCDtextInit		(LCDtext * display, int n_filas, int n_columnas, int D4, int D5, int D6, int D7, int RS, int EN);
res_t	LCDtextPuts		(LCDtext *, const char * s);
void 	LCDtextPutchar  (LCDtext * display, int data);	//TODO: Check! char?
void	LCDtextClear	(LCDtext *);
void	LCDtextGotoXY	(LCDtext *, int x, int y);
void	LCDworker		(LCDtext *);
void LCDPutString(const char *, unsigned char , unsigned char );

enum {
	LCD_FILA_0 = 0,
	LCD_FILA_1,
	LCD_FILA_2,
	LCD_FILA_3
};

#endif /* LCD_TEXT_H_ */
