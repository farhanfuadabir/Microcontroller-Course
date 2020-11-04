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

unsigned char digit[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char show[5];
unsigned int counter = 243;
unsigned char anodeSelect = 0;

int main(void)
{
	DDRA |= 0b11100000;	
	DDRB = 0xFF;	
	DDRD &= ~(1 << PD0);		//Input for Switch
	
	//----------------------------------------------------------------------------
	TCCR0 |= (1 << CS02);		//Timer0, Normal mode, 256 prescaler
	TIMSK |= (1 << TOIE0);		//Enable Timer0 overflow interrupt
	TCNT0 = 0;					//Clear TCNT0
	sei();						//Enable Global interrupt
	//----------------------------------------------------------------------------
	
	while(1)
	{		
		show[0] = counter / 100;
		show[1] = (counter / 10) % 10;
		show[2] = counter % 10;
		
		if(!(PIND & (1 << PD0)))
		{
			while(!(PIND & (1 << PD0)));
			_delay_ms(50);
			
			counter++;
			
			if(counter > 999)
			counter = 0;
		}
	}		
}

ISR(TIMER0_OVF_vect) //ISR for Timer0 overflow
{
	anodeSelect++;
	
	if(anodeSelect == 1)
	{
		PORTA &= ~(1 << PA6);
		PORTA &= ~(1 << PA7);
		PORTA |= (1 << PA5);
		PORTB = digit[show[0]];		
	}
	else if(anodeSelect == 2)
	{
		PORTA &= ~(1 << PA5);
		PORTA &= ~(1 << PA7);
		PORTA |= (1 << PA6);
		PORTB = digit[show[1]];		
	}
	else if(anodeSelect == 3)
	{
		PORTA &= ~(1 << PA5);
		PORTA &= ~(1 << PA6);
		PORTA |= (1 << PA7);
		PORTB = digit[show[2]];
		
		anodeSelect = 0;
	}

	TCNT0 = 0;			//Clear TCNT0
	TIFR |= 1 << TOV0;	//Clear Timer0 Overflow Flag
}