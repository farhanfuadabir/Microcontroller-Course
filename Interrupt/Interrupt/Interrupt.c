/*
 * Interrupt.c
 *
 * Created: 11/12/2015 3:59:16 PM
 *  Author: TechClass
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	PORTC = 0xFF;
	for(int i =0; i<8; i++)
	{
	PORTC = ~PORTC;
	_delay_ms(100);
	}
	

}

int main(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	
	GICR |= (1<<INT0); // enable interrupt0 
	MCUCR |= (1<<ISC00) | (1<<ISC01); // select rising edge
	sei(); // enable global interrupt
	
    while(1)
    {
		for(int i =0; i<8; i++)
		{
			PORTC = (1<<i);
			_delay_ms(100);       
		}
	}
}