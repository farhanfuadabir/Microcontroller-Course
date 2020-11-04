//======Import info======//
//FUSE Bits: LOW  = 0x24, HIGH = 0xD9
//Clock: internal 8MHz
//BOD: 4.0V
//Startup Time: 6CK + 64ms
//-----------------------

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h> 


char digit[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	
unsigned char counter = 0;


int main(void)
{	
	DDRB = 0xFF;
	DDRD &= ~(1 << PD2); //PD2 Input
	
	
	while(1)
	{
		if(!(PIND & (1 << PD2)))
		{
			while(!(PIND & (1 << PD2)));
			_delay_ms(100);
			
			counter++;
			
			if(counter > 9)
				counter = 0;
		}
		
		PORTB = digit[counter];
	}
}