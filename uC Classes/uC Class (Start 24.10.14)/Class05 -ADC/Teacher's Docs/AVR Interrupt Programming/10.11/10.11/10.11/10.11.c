/*
 * _10.c
 *
 * Created: 11/25/2012 3:31:48 PM
 *  Author: SusmImu 
 * Using Timer0, write a program that toggles pin PORTB.5 every second, 
   while at the same time transferring data from PORTC to PORTD. 
   Assume XTAL = 8 MHz.
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= 0x20; //POTRB.5 output 
	DDRC = 0x00;
	DDRD = 0xFF;
	
	OCR0 = 40;
	TCCR0 = 0x09; //CTC mode, internal clock, no prescaler
	
	TIMSK = (1 << OCIE0); //Enable Timer0 compare match interrupt 
	sei(); //Enable interrupts 
	
    while(1)
    {
        PORTD = PINC;
    }
}

ISR(TIMER0_COMP_vect) //ISR for Timer0 compare match 
{
	PORTB ^= 0x20;
}