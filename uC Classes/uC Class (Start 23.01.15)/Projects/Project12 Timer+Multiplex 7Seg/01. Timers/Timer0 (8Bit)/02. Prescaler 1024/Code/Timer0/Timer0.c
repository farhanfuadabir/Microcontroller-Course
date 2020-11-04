/*
 * Timer0.c
 *
 * Created: 11/20/2014 8:05:26 PM
 *  Author: SAIYEB
 */ 

#define F_CPU 8000000UL				//Set CPU clock speed to 8MHz

#include <avr/io.h>					//Include header files
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRA  = 0xFF; 
	PORTA = 0x00;
	
	TCCR0 |= (1 << CS00) | (1 << CS02);		//Timer0, Normal mode, 1024 prescaler
	TIMSK |= (1 << TOIE0);					//Enable Timer0 overflow interrupt
	TCNT0 = 0;								//Clear TCNT0
	sei();									//Enable Global interrupt
	
    while(1)
    {
		_delay_ms(5000);
    }
}
	
ISR(TIMER0_OVF_vect) //ISR for Timer0 overflow
{
	PORTA = ~PORTA;	

	TCNT0 = 0;			//Clear TCNT0
	TIFR |= 1 << TOV0;	//Clear Timer0 Overflow Flag
}