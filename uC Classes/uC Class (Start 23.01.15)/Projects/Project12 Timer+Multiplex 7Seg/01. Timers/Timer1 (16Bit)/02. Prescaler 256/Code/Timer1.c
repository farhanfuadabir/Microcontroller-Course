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
	
	TCCR1B |= (1 << CS12);	//Timer1, Normal mode, 256 prescaler
	TIMSK |= (1 << TOIE1);	//Enable Timer1 overflow interrupt
	TCNT1 = 0x7A12;			//Input value to TCNT1
	sei();					//Enable Global interrupt
	
    while(1)
    {
		_delay_ms(5000);
    }
}

ISR(TIMER1_OVF_vect)		//ISR for Timer1 overflow
{
	PORTA = ~PORTA;

	TCNT1 = 0x7A12;			//Input value to TCNT1
	TIFR |= 1 << TOV1;		//Clear Timer1 Overflow Flag
}