/*
 * interrupt.c
 *
 * Created: 02/01/2016 11:06:30 AM
 *  Author: TechClass
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    DDRA=0xFF;
	DDRD &= ~(1<<PD2);//input of Interrupt
	DDRC |=(1<<PC3);//Output for led
	
	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);
	sei();
	
	while(1)
    {
        //TODO:: Please write your application code 
		PORTA=0xFF;
		_delay_ms(10000);
		PORTA=0x00;
		_delay_ms(10000);
    }
}

ISR (INT0_vect)
{
	PORTA=0x00;
	PORTA=0xFF;
	_delay_ms(400);
	PORTA=0x00;
	_delay_ms(400);
}

