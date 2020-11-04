/*
 * GccApplication1.c
 * Created: 12/31/2012 10:35:22 PM
 *  Author: SusmImu
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "lcd_lib.h"

int main(void)
{
	LCDinit();			//Initializes LCD
	LCDclr();			//Clear LCD and move cursor home position 
	LCDcursorOFF();		//Turn off cursor
	
    while(1)
    {
		LCDstring("HASAN");	//Print string to current cursor position
		_delay_ms(3000);
		LCDclr();	//Clear LCD and move cursor home position 
		_delay_ms(500);
		
		LCDcursorOn();		//Underline cursor ON 
		_delay_ms(3000);
		LCDclr();			//Clear LCD and move cursor home position 
		_delay_ms(500);
		
		LCDcursorOnBlink();	//Underline blinking cursor ON
		_delay_ms(3000);
		_delay_ms(500);
		
		LCDGotoXY(5, 0);	//Cursor to X(Clo5), Y(Row0) position
		_delay_ms(3000);
		_delay_ms(500);
		
		LCDGotoXY(14, 1);	//Cursor to X(Clo14), Y(Row1) position
		_delay_ms(3000);
		_delay_ms(500);
		
		LCDhome();			//LCD cursor home
		_delay_ms(3000);
		_delay_ms(500);
		
		LCDcursorOFF();		//Cursor OFF
		_delay_ms(3000);
		_delay_ms(500);
		
		LCDstring("LCD OFF-ON");
		_delay_ms(1000);
		LCDblank();			//LCD blank but not cleared
		_delay_ms(2000);
				
		LCDvisible();		//LCD visible
		_delay_ms(3000);
		
		LCDshiftLeft(6);	//Shift by n(6) characters Left
		_delay_ms(3000);
		
		LCDshiftRight(4);	//Shift by n(3) characters Right
		_delay_ms(3000);
		
		LCDclr();			//Clear LCD and move cursor home position
		_delay_ms(500);		
		LCDcursorOnBlink();	//Underline blinking cursor ON
		_delay_ms(500);
		LCDcursorRight(7);	//shift cursor right by n(7)
		_delay_ms(2000);
		
		LCDcursorLeft(3);	//shift cursor left by n(3)
		_delay_ms(2000);		
		LCDclr();			//Clear LCD and move cursor home position 
		_delay_ms(500);		
    }
}

/*
void CopyStringtoLCD(const uint8_t*, uint8_t, uint8_t); //copies flash string to LCD at x,y
void LCDdefinechar(const uint8_t *, uint8_t);			//write char to LCD CGRAM
*/