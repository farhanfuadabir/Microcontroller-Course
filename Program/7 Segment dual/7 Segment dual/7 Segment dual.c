//======Import info======//
//FUSE Bits: LOW  = 0x24, HIGH = 0xD9
//Clock: internal 8MHz
//BOD: 4.0V
//Startup Time: 6CK + 64ms
//-----------------------

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>

unsigned char anode_select = 0;

unsigned char digit[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char show1;
unsigned char show2;
unsigned char counter = 43;


int main(void)
{
	DDRA  |= (1 << PA7) | (1 << PA6);
	PORTA |= (1 << PA7) | (1 << PA6);
	
	DDRB = 0xFF;
	
	DDRD &= ~(1 << PD0);
	
	while(1)
	{
		_delay_ms(10);
		
		if(!(PIND & (1 << PD0)))
		{
			while(!(PIND & (1 << PD0)));
			_delay_ms(10);
			
			counter++;
			
			if(counter > 99)
			counter = 0;
		}
		
		show1 = counter / 10;
		show2 = counter % 10;
		
		//------------------------
		PORTA &= ~(1 << PA7);
		PORTA |= (1 << PA6);
		PORTB = digit[show1];
		_delay_ms(10);
		//------------------------
		
		//------------------------
		PORTA &= ~(1 << PA6);
		PORTA |= (1 << PA7);
		PORTB = digit[show2];
		_delay_ms(10);
		//------------------------
	}
}


