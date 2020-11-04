/*
 * AADDCCC.c
 *
 * Created: 11/5/2015 2:50:59 PM
 * Author : Shakran
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd_lib.h"
#include <stdlib.h>
#include <stdio.h>

char buffer[7];
int val;
double voltage;
int main(void)
{
	ADMUX |= (1<<REFS0);	// set AVCC 5v as Vref
	ADCSRA |= (1<<ADEN);	// Enable ADC module
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2); // set ADC prescaler as 128
    
	//ADMUX = 0 ; // select channel
 	ADCSRA |= (1<<ADSC);	// start conversion
	
	LCDinit();
	_delay_ms(100);
	LCDclr();
	//LCDGotoXY(0,0);
	//LCDWriteString("abcd");
	
	while (1) 
    {
		while(ADCSRA & (1<<ADSC));
		val = ADC;
		ADCSRA |= (1<<ADSC);
		
		voltage = (double)val * 0.0049; // paste (-Wl,-u,vfprintf -lprintf_flt -lm) this value to the linker option to show float point.
                                        //http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
		sprintf(buffer,"%2.2lf", voltage);
		LCDGotoXY(0,0);
		LCDWriteString(buffer);	
    }
}

