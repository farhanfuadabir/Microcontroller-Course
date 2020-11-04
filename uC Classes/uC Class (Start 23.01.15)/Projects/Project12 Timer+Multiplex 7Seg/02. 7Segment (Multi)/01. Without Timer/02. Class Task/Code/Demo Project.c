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


int main(void)
{
	DDRA |= 0b11100000;
	
	DDRB = 0xFF;
	
	DDRD &= ~(1 << PD0); //Input for Switch
	
	while(1)
	{		
		show[0] = counter / 100;
		show[1] = (counter / 10) % 10;
		show[2] = counter % 10;					
		
		PORTA &= ~(1 << PA6);
		PORTA &= ~(1 << PA7);
		PORTA |= (1 << PA5);
		PORTB = digit[show[0]];		
		_delay_ms(1);
		
		PORTA &= ~(1 << PA5);
		PORTA &= ~(1 << PA7);
		PORTA |= (1 << PA6);
		PORTB = digit[show[1]];		
		_delay_ms(1);
		
		PORTA &= ~(1 << PA5);
		PORTA &= ~(1 << PA6);
		PORTA |= (1 << PA7);
		PORTB = digit[show[2]];
		_delay_ms(1);
		
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