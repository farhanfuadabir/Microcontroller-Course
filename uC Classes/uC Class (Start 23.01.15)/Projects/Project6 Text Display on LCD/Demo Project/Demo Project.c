#define F_CPU 8000000UL 

#include <avr/io.h> 
#include <util/delay.h>
#include "lcd_lib.h"

int main(void)
{
	LCDinit();			//Initialize the LCD
	_delay_ms(50);		//Delay for stabilization
	
	while(1) 
	{
		LCDWriteStringXY(3, 0,"Text"); 
		_delay_ms(1000);
		//LCDWriteString("Pi Labs BD");
		
		
	}
}