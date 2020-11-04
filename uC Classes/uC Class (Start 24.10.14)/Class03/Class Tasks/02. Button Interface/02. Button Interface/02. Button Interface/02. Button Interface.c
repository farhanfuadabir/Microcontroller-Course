/*
 * _02.c
 *
 * Created: 11/7/2014 12:01:47 PM
 *  Author: SAIYEB
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//Output for LED
	DDRC = DDRC | 1 << PC0;
	DDRC = DDRC | 1 << PC1;
	
	//Input for Button
	DDRD = DDRD &(~(1 << PD2));
	DDRD = DDRD &(~(1 << PD3));
		
    while(1)
    {
		if((PIND &(1 << PD2)) == 0)
		{
			_delay_ms(50);
			
			PORTC = PORTC | 1 << PC0;
			_delay_ms(1000);
			PORTC = PORTC & (~(1 << PC0));
			
			while((PIND &(1 << PD2)) == 0);
		}
		else if((PIND &(1 << PD3)) == 0)
		{
			_delay_ms(50);
			
			PORTC = PORTC | 1 << PC1;
			_delay_ms(1000);
			PORTC = PORTC & (~(1 << PC1));
			
			while((PIND &(1 << PD3)) == 0);
		}
	}
}