/*
 * ADC.c
 *
 * Created: 11/12/2015 5:48:15 PM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_lib.h"
#include <stdio.h>

volatile int adc_value = 0;
double voltage = 0;
char buffer [];

double temp;

ISR(ADC_vect)
{
	adc_value = ADC;
	ADCSRA |=(1<<ADSC);
	
}



int main(void)
{
	LCDinit();
	LCDclr();
	_delay_ms(100);
		
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	ADCSRA |= (1<<ADEN)|(1<<ADIE); //enable ADC and ADC interrupt
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); // select prescaler 128
	
	ADMUX |= (1<<REFS0); // select referecne
	ADMUX |= (1<<MUX0);//|(1<<MUX1)|(1<<MUX2); // select channel 7
	
	ADCSRA |=(1<<ADSC); // conversion started;
	
	
// paste (-Wl,-u,vfprintf -lprintf_flt -lm) this value to the linker option to show float point.
 //http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
	
	sei();
	
    while(1)
    {
// 		while(ADCSRA & (1<<ADSC));
// 		
// 			adc_value = ADC;
// 			voltage = adc_value*0.00488;
// 			
// 			LCDGotoXY(0,0);
// 			LCDWriteInt(adc_value,4);
// 			LCDGotoXY(0,1);
// 			
// 			sprintf(buffer,"%2.2lf",voltage);  //sprintf(buffer,"%2.2lf", voltage);
// 			LCDWriteString(buffer);
// 			LCDGotoXY(6,1);
// 			LCDWriteString("Volt");
// 			
// 			_delay_ms(1000);
// 			
// 		
	
	
		
	
		

///////////////////////////////////////////////////////////////////////	
// 		voltage = adc_value*0.00488;
// 
// 		LCDGotoXY(0,0);
// 		LCDWriteInt(adc_value,4);
// 		LCDGotoXY(0,1);
// 
// 		sprintf(buffer,"%2.2lf",voltage);  //sprintf(buffer,"%2.2lf", voltage);
// 		LCDWriteString(buffer);
// 		LCDGotoXY(6,1);
// 		LCDWriteString("Volt");
// 
// 		_delay_ms(10);
		
//////////////////////////////////////////////////////////////////////////////

		temp = adc_value*0.488;

		LCDGotoXY(0,0);
		LCDWriteInt(adc_value,4);
		LCDGotoXY(0,1);

		sprintf(buffer,"%2.2lf",temp);  //sprintf(buffer,"%2.2lf", voltage);
		LCDWriteString(buffer);
		LCDGotoXY(6,1);
		LCDWriteString("C");

		_delay_ms(10);
//////////////////////////////////////////////////////////////////////////////
    }
}