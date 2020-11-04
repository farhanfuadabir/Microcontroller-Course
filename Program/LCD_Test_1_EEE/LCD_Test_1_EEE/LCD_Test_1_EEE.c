/*
 * LCD_Test_1_EEE.c
 *
 * Created: 17/12/2015 4:13:32 PM
 *  Author: TechClass
 */ 


#include <avr/io.h>
#include "lcd_lib.h"
int i=12;

int main(void)
{
    LCDinit();
	_delay_ms(10);
	while(1)
    {
        //TODO:: Please write your application code
		 LCDWriteStringXY(0,1,"Techshop BD");
		 LCDWriteIntXY(0,0,i,3);
    }
}