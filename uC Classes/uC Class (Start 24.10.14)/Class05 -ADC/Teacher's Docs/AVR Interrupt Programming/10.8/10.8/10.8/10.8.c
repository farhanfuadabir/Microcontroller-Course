/*
 * _10.c
 *
 * Created: 11/25/2012 11:01:32 AM
 *  Author: SusmImu
 * Using Timer0 generate a square wave on pin PORTB.5, while at the same time transfer-ring data from PORTC to PORTD.
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= 0x20;			//Set PORTB5 output
	DDRC = 0x00;
	DDRD = 0xFF;
	
	TCNT0 = -32;			//Timer value for 4uS
	TCCR0 = 0x01;			//Normal mode, internal clock, no prescaler
	
	TIMSK = (1 << TOIE0);	//Enable Timer0 overflow interrupt 
	sei();					//Enable interrupt 
	
	while(1)
	{
		PORTD = PINC;
	}    
}

ISR (TIMER0_OVF_vect)		//ISR for Timer0 overflow 
{
	TCNT0 = -32;
	PORTB ^= 0x20;
}