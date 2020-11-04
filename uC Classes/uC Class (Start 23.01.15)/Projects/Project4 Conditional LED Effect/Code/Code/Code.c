/*
 * Code.c
 *
 * Created: 2/17/2015 5:47:42 PM
 *  Author: SusmImu
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRC |= 1 << PC0; //PC0 Output
	DDRC |= 1 << PC2; //PC2 Output
	
	DDRD &= ~(1 << PD2); //PD2 Input
	DDRD &= ~(1 << PD3); //PD3 Input
	
	while(1)
	{		
		if(!(PIND & (1 << PD2)))
		{
			PORTC |= 1 << PC0;
			_delay_ms(1000);
			PORTC &= ~(1 << PC0);
		}
		
		
		if((PIND & (1 << PD3)))
		{
			PORTC |= 1 << PC2;
			_delay_ms(1000);
			PORTC &= ~(1 << PC2);
		}
	}
}