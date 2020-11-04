/*
 * test2.c
 *
 * Created: 03/01/2016 12:23:33 PM
 *  Author: TechClass
 */ 

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



volatile int number=0;
int main(void)
{
	DDRB = 0xFF;
	DDRD &= ~(1<<PD2);
	DDRD &= ~(1<<PD3);
	
	MCUCR |= (1<<ISC01) | (1<<ISC11);
	GICR |= (1<<INT0) | (1<<INT1);	
	
	DDRB  |= 1 << PB3; //PWM pin as Output
	OCR0   = 0;
	TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS01); //Fast PWM, Non-inverting mode, prescaling 8
	sei();
	while(1)
	{
		if(number>255)
		{
			number=255;
		}
		if (number<1)
		{
			number=0;
		}
		OCR0=number;
	}
}

ISR(INT0_vect)
{
	number+=10;
}

ISR(INT1_vect)
{
	number-=10;
}

