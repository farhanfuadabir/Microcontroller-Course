/*
 * Example01.c
 * Created: 12/6/2014 9:02:54 PM
 *  Author: Shakran
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB  |= 1 << PB3; //PWM pin as Output
	OCR0 = 191;	
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS00); //Fast PWM, Non-inverting mode, No prescaling
	
    while(1);
}