#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int count = 0;


ISR(TIMER0_OVF_vect)
{
	count++;
	if (count == 3921)				//F_CPU/255
	{
		PORTC = ~PORTC;				//toggle PORTC
		count = 0;					//reset count
	}
}

void timer0_init()
{
	TCCR0 = 0x00;				//reset timer register
	TCNT0 = 0x00;				//reset timer0
	TIMSK |= (1<<TOIE0);		//Overflow interrupt enable
	TCCR0 |= (1<<CS00);			//Prescaler = Fcpu/1
}

int main(void)
{
	//disable Jtag on PORTC
	MCUCSR |= 1<<JTD;
	MCUCSR |= 1<<JTD;
	
	//PORTC as Output
	DDRC = 0xFF;
	
	//initialize timer0
	timer0_init();
	
	//enable global interrupt
	sei();
	
	while (1)
	{
		
	
	}
}
