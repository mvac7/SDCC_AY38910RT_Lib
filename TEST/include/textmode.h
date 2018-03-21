#ifndef __TEXTMODE_H__
#define __TEXTMODE_H__

#include "newTypes.h"



// palette color codes
#define TRANSPARENT   0
#define BLACK         1
#define GREEN         2
#define LIGHT_GREEN   3
#define DARK_BLUE     4
#define LIGHT_BLUE    5
#define DARK_RED      6
#define CYAN          7
#define RED           8
#define LIGHT_RED     9
#define DARK_YELLOW  10
#define LIGHT_YELLOW 11
#define DARK_GREEN   12
#define MAGENTA      13
#define GRAY         14
#define GREY         14
#define WHITE        15



/* =============================================================================
   Switches to SCREEN 0 (text screen with 40 * 24 characters)
============================================================================= */
void SCREEN0();



/* =============================================================================
   Switches to SCREEN 1 (text screen with 32*24 characters)
============================================================================= */
void SCREEN1();



/* =============================================================================
   Especifica el número de caracteres por línea del modo de texto
   columns (char) = 1 to 40 in screen0 
                    1 to 32 in screen1 
============================================================================= */
void WIDTH(char columns);



/* =============================================================================
   Specifies the colors for text, background, and borders.
   Especifica los colores del texto, fondo y área de los bordes.
============================================================================= */
void COLOR(char ink, char background, char border);



/* =============================================================================
   Clears the screen 
============================================================================= */
void CLS();



/* =============================================================================
   Posiciona el cursor hasta la ubicacion especificada
   x(byte) - columna
   y(byte) - linea
============================================================================= */
void LOCATE(byte x, byte y);



/* =============================================================================
   Imprime un texto en la pantalla 
   Permite varias lineas separadas con el codigo de escape newline \n
   ejem: PRINT("ARE YOU SURE\nYOU WANT TO\nDELETE SONG?");
============================================================================= */
void PRINT(char* text);



/* =============================================================================
   Imprime un numero en la pantalla
============================================================================= */
void PrintNumber(int value);



/* =============================================================================
 16-bit Integer to ASCII (decimal)
 by baze 
 Input: HL = number to convert, DE = location of ASCII string
 Output: ASCII string at (DE)
============================================================================= */
void num2Dec16(int aNumber, char *address);



/* =============================================================================
   Displays one character (BIOS)
   Imprime un caracter en la pantalla
   value (char) - char value
============================================================================= */
void bchput(char value);



/* =============================================================================
   Current row-position of the cursor
============================================================================= */
char getLine();


#endif