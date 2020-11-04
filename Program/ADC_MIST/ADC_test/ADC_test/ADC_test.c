/*
 * ADC_test.c
 *
 * Created: 20/12/2015 10:10:53 AM
 *  Author: TechClass
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd_lib.h"
#include "ADC_routines.h"

uint16_t _adc_Value=0;
uint8_t _Max_value=0;
uint8_t _Min_value=0;
uint8_t _Enter_count=0;


int main(void)
{
    DDRA &= ~(1<<PA2);//Input as adc
	DDRB &=~(1<<PB0);// input as up
	DDRB &= ~(1<<PB1);//input as down
	DDRB &= ~(1<<PB2);//input as enter 
	
	DDRD |=(1<<PD0);//output
	
	LCDinit();
	Init_ADC();
	PORTD &=~(1<<PD0);
	
	while(1)
    {
        //TODO:: Please write your application code 
		
		//LCDWriteStringXY(0,0,"Temp is:");
		//LCDWriteIntXY(0,1,_adc_Value,2);
		if (!(PINB & (1<<PB2)))//if press enter
		{
			while(!(PINB & (1<<PB2)));
			_delay_ms(10);
			_Enter_count++;
			LCDWriteStringXY(0,0,"Test");
			LCDclr();
			while(1)
			{
				if (_Enter_count==1)
				{
					LCDWriteStringXY(0,0,"Enter Max Value:");
					if (!(PINB & (1<<PB0)))//if press up
					{
						while(!(PINB & (1<<PB0)));
						_delay_ms(10);
						_Max_value++;
					}
					if (!(PINB & (1<<PB1)))//if press down
					{
						while(!(PINB & (1<<PB1)));
						_delay_ms(10);
						_Max_value--;
					}
					if (_Max_value>50 || _Max_value<1)
					{
						_Max_value=0;
					}
					LCDWriteIntXY(0,1,_Max_value,2);
					if (!(PINB & (1<<PB2)))//if press enter
					{
						while(!(PINB & (1<<PB2)));
						_delay_ms(10);
						_Enter_count++;
						//break;
					}
				}
				
				
				
				if (_Enter_count==2)
				{
					LCDWriteStringXY(0,0,"Enter Min Value:");
					if (!(PINB & (1<<PB0)))//if press up
					{
						while(!(PINB & (1<<PB0)));
						_delay_ms(10);
						_Min_value++;
					}
					if (!(PINB & (1<<PB1)))//if press down
					{
						while(!(PINB & (1<<PB1)));
						_delay_ms(10);
						_Min_value--;
					}
					if (_Min_value>50 || _Min_value<1)
					{
						_Min_value=0;
					}
					LCDWriteIntXY(0,1,_Min_value,2);
					if (!(PINB & (1<<PB2)))//if press enter
					{
						while(!(PINB & (1<<PB2)));
						_delay_ms(10);
						_Enter_count=0;
						LCDclr();
						break;
					}
				}
					
			}		
		}
		
		_adc_Value=readADCValue(2);
		_adc_Value=_adc_Value/2.0625;
		LCDWriteStringXY(0,0,"Temp:");
		LCDWriteIntXY(6,0,_adc_Value,2);
		if (_adc_Value>_Max_value)
		{
			PORTD |= (1<<PD0);
		}
		else if (_adc_Value <_Min_value)
		{
			PORTD &= ~(1<<PD0);
		}
		/*else
		{
			PORTD &=~(1<<PD0);
		}*/
		
		
    }
}	