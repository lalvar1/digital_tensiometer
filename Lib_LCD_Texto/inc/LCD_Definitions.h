/*
 * LCD_Definitions.h
 *
 *  Created on: 07/04/2012
 *      Author: Alejandro
 */

#ifndef LCD_DEFINITIONS_H_
#define LCD_DEFINITIONS_H_

/*	----------------------------------
	-	Parámetros para configurar.
	-	Tomados de la demo de JCWren.
	---------------------------------- */




#define LCD_FUNCTION_FONT_5X8   0x00
#define LCD_FUNCTION_FONT_5X11  0x04
#define LCD_FUNCTION_LINES_1    0x00
#define LCD_FUNCTION_LINES_2    0x08
#define LCD_FUNCTION_BUS_4      0x00
#define LCD_FUNCTION_BUS_8      0x10
#define LCD_FUNCTION_MASK       0x1c

#define LCD_DISPLAY_BLINK_OFF   0x00
#define LCD_DISPLAY_BLINK_ON    0x01
#define LCD_DISPLAY_CURSOR_OFF  0x00
#define LCD_DISPLAY_CURSOR_ON   0x02
#define LCD_DISPLAY_DISPLAY_OFF 0x00
#define LCD_DISPLAY_DISPLAY_ON  0x04
#define LCD_DISPLAY_MASK        0x07

#define LCD_COMMAND_CLEAR       0x01
#define LCD_COMMAND_HOME        0x02
#define LCD_COMMAND_ENTRY_MODE  0x04
#define LCD_COMMAND_DISPLAY     0x08
#define LCD_COMMAND_SHIFT       0x10
#define LCD_COMMAND_FUNCTION    0x20
#define LCD_COMMAND_CGRAM       0x40
#define LCD_COMMAND_DDRAM       0x80

#define LCD_MODE_SHIFT_NO       0x00
#define LCD_MODE_SHIFT_YES      0x01
#define LCD_MODE_DECREMENT      0x00
#define LCD_MODE_INCREMENT      0x02
#define LCD_MODE_MASK           0x03

#define LCD_SHIFT_CURSOR        0x00
#define LCD_SHIFT_DISPLAY       0x04
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x08
#define LCD_SHIFT_MASK          0x0c

#endif /* LCD_DEFINITIONS_H_ */

