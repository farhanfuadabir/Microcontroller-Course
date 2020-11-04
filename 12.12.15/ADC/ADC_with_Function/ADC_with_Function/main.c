/*
 * ADC_with_Function.c
 *
 * Created: 11/5/2015 8:58:33 PM
 * Author : Shakran
 
  * you have to add (-Wl,-u,vfprintf -lprintf_flt -lm)
  to the linker option
  if you want to show (double)float point in LCD.
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


uint16_t raw_value;
double voltage;

void adc_init()
{
	ADMUX |= (1<<REFS0); //reference AVCC 5volt
	ADCSRA |= (1<<ADEN); //enable ADC Module
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); //prescaler 128
}

int adc_Read(uint8_t ch)
{
	ADMUX  &= ~(0x1F);				//disable all adc channel
	ADMUX |= (0x1F & ch);			//set the adc channel
	ADCSRA |= (1<<ADSC);			//start ADC conversion
	while(ADCSRA & (1<<ADSC));		//wait until conversion complete
	//while(!(ADCSRA & (1<<ADIF)));	//wait until conversion complete
	return ADC;						//return the ADC converted digital value
}

int main(void)
{
    adc_init();
	LCDinit();
	
    while (1) 
    {
		raw_value = adc_Read(0);
		LCDGotoXY(0,0);
		LCDWriteInt(raw_value,4);
		
		voltage = (double)raw_value * 0.00489;
		sprintf(buffer,"%2.2lf", voltage);
		LCDGotoXY(0,1);
		LCDWriteString(buffer);		
		
		
    }
}

