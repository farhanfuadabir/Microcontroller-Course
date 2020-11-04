//======Import info======//
//FUSE Bits: LOW  = 0x24, HIGH = 0xD9
//Clock: internal 8MHz
//BOD: 4.0V
//Startup Time: 6CK + 64ms
//-----------------------

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

uint8_t zero  = 3;
uint8_t one   = 159;
uint8_t	two   = 37;
uint8_t three = 13;
uint8_t four  = 153;
uint8_t five  = 73;
uint8_t six   = 65;
uint8_t seven = 31;
uint8_t eight = 1;
uint8_t nine  = 9;


int main(void)
{
	DDRC = 0xFF;
	
	while(1)
	{
		//PORTC=0x03;
		PORTC = zero;
		_delay_ms(1000);
		
		PORTC = one;
		_delay_ms(1000);
		
		PORTC = two;
		_delay_ms(1000);
		
		PORTC = three;
		_delay_ms(1000);
		
		PORTC = four;
		_delay_ms(1000);
		
		PORTC = five;
		_delay_ms(1000);
		
		PORTC = six;
		_delay_ms(1000);
		
		PORTC = seven;
		_delay_ms(1000);
		
		PORTC = eight;
		_delay_ms(1000);
		
		PORTC = nine;
		_delay_ms(1000);
	}
}


