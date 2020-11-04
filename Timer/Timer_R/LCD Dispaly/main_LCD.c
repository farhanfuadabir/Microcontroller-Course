#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "lcd.h"

char buffer[7];
volatile int count = 0;
volatile int second = 0;

ISR(TIMER0_OVF_vect)
{
	count++;
	if(count >= 4 ) 
	{
		second++;
		count = 0;
	}
}

int main(void)
{
	lcd_init(LCD_DISP_ON);
	
	TCCR0 |= (1<<CS00) | (1<<CS02);		// prescaler 1024
	TIMSK |= (1<<TOIE0);				// overflow interrupt enable
	sei();								// enable global interrupt			
	
	while(1)
    {
		itoa(second, buffer, 10);
		lcd_gotoxy(0,0);
		lcd_puts(buffer);
		
		_delay_ms(100);
    }
}