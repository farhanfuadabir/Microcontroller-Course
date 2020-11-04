/*
 * LM35.c
 *
 * Created: 31/12/2015 10:26:46 AM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "ADC_routines.h"
#include "lcd_lib.h"

uint16_t lm35_value=0;

int main(void)
{
    DDRA &=~(1<<PA0);// as input
	LCDinit();//lcd initialize
	Init_ADC();//adc initialize
	while(1)
    {
        //TODO:: Please write your application code 
		lm35_value=readADCValue(0);
		//lm35_value=lm35_value/2.0625;
		
		LCDWriteStringXY(0,0,"Temp=");
		LCDWriteIntXY(6,0,lm35_value,4);
    }
}