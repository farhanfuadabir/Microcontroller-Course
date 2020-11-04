//======Import info======//
//FUSE Bits: LOW  = 0x24, HIGH = 0xD9
//Clock: internal 8MHz
//BOD: 4.0V
//Startup Time: 6CK + 64ms
//-----------------------

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h> 

char zero  = 0x3F;
char one   = 0x06;
char two   = 0x5B;
char three = 0x4F;
char four  = 0x66;
char five  = 0x6D;
char six   = 0x7D;
char seven = 0x07;
char eight = 0x7F;
char nine  = 0x6F;


int main(void)
{	
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = zero;
		_delay_ms(1000);
		
		PORTB = one;
		_delay_ms(1000);
		
		PORTB = two;
		_delay_ms(1000);
		
		PORTB = three;
		_delay_ms(1000);
		
		PORTB = four;
		_delay_ms(1000);
		
		PORTB = five;
		_delay_ms(1000);
		
		PORTB = six;
		_delay_ms(1000);
		
		PORTB = seven;
		_delay_ms(1000);
		
		PORTB = eight;
		_delay_ms(1000);
		
		PORTB = nine;
		_delay_ms(1000);
	}		
}


