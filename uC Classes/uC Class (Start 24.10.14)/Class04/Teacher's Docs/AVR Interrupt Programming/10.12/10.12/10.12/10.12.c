/*
 * _10.c
 *
 * Created: 11/25/2012 3:55:15 PM
 *  Author: SusmImu
 * INT0 pin is connected to a switch that is normally high. Write a program that toggles PORTC.3,
   whenever INT0 pin goes low. Use the external interrupt in level-triggered mode.
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRA   = 0xFF;
	DDRC  |= 1 << PC3;			//PC3 as an output 
	DDRD = DDRD & (~(1 <<PD2));
	
	MCUCR |= 1 << ISC01;
	MCUCR &= ~(1 << ISC00);
		
	GICR |= 1 << INT0;			//Enable external int0
	sei();						//Enable interrupts
	
    while(1)
	{
		for(int i = 0; i < 8; i++)
		{
			PORTA = 1 << i; 
			_delay_ms(500);
		}
	}					
}

ISR(INT0_vect)					//ISR for external interrupt 0 
{
	PORTC ^= (1 << PC3);
}