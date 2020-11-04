/*
 * button_with_interrupt.c
 *
 * Created: 02/01/2016 11:56:04 AM
 *  Author: TechClass
 */ 


//======Import info======//
//FUSE Bits: LOW  = 0x24, HIGH = 0xD9
//Clock: internal 8MHz
//BOD: 4.0V
//Startup Time: 6CK + 64ms
//-----------------------

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


char digit[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

volatile int number=0;
int main(void)
{
	DDRB = 0xFF;
	DDRD &= ~(1<<PD2);
	DDRD &= ~(1<<PD3);
	
	MCUCR |= (1<<ISC01) | (1<<ISC11);
	GICR |= (1<<INT0) | (1<<INT1);	
	sei();
	while(1)
	{
		if(number>9)
		{
			number=0;
		}
		if (number<0)
		{
			number=9;
		}
		PORTB=digit[number];
	}
}

ISR(INT0_vect)
{
	number++;
}

ISR(INT1_vect)
{
	number--;
}

