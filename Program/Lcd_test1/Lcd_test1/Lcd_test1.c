/*
 * Lcd_test1.c
 *
 * Created: 15/12/2015 3:51:48 PM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd_lib.h"

int main(void)
{
    LCDinit();
	_delay_ms(100);
	while(1)
    {
        LCDWriteStringXY(0,2,"Techshop");
		_delay_ms(500);
    }
}