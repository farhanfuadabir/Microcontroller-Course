/*
 * ADC_with_ISR.c
 *
 * Created: 11/5/2015 8:13:21 PM
 * Author : Shakran
 
 * you have to add (-Wl,-u,vfprintf -lprintf_flt -lm) 
   to the linker option
   if you want to show float point in LCD.
   DO NOT ASK ANYTHING ABOUT IT !!! JUST DO IT!!! :P
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char buffer[7];
char buffer_raw[7];

uint16_t val;
double voltage;

ISR(ADC_vect)
{
	val = ADC;
	ADCSRA |= (1<<ADSC);	
}

int main(void)
{
    ADMUX |= (1<<REFS0);											// set AVCC 5v as Vref
    ADCSRA |= (1<<ADEN);	// Enable ADC module
    ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2)|(1<<ADIE);		// set ADC prescaler as 128
    	
    //ADMUX = 0 ;													// Do not need to set ADMUX when use ADC channel 0
    ADCSRA |= (1<<ADSC);											// Start ADC conversion
    	
    LCDinit();
    _delay_ms(100);
    LCDclr();
	LCDGotoXY(0,0);
																	
	sei();
	
    while (1) 
    {		
		LCDGotoXY(0,0);
		LCDWriteInt(val,4);
			
		voltage = (double)val * 0.00489;
		sprintf(buffer,"%2.2lf", voltage);
		LCDGotoXY(0,1);
		LCDWriteString(buffer);		
    }
}

