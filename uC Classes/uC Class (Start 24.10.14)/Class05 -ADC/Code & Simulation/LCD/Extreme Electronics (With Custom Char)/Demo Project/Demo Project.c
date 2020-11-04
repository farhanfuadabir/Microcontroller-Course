#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

int main(void)
{
	unsigned char i;
	
	LCDInit(LS_NONE);						//Initialize LCD module
	LCDClear();								//Clear the screen

	LCDWriteString("Congrats");				//Simple string printing	
	LCDWriteStringXY(0, 1,"Loading...");	//A string on line 2

	for (i = 0; i < 100; i++)				//Print some numbers
	{
		LCDWriteIntXY(9, 1, i, 3);
		LCDWriteStringXY(12, 1, "% ");
		_delay_loop_2(0);
		_delay_loop_2(0);	
	}
	
	for(i = 0; i < 50; i++)					//Wait
		_delay_loop_2(0);
	
	LCDClear();

	for(i = 0; i < 50; i++)					//Wait
		_delay_loop_2(0);
		
	LCDWriteString("Custom Char!!!");
	_delay_ms(100);
	LCDWriteStringXY(0, 1,"%0%1%2%3%4%5%6%7");
}