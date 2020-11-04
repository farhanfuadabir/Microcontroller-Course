/*
 * Timer_0.c
 *
 * Created: 10/28/2015 1:43:13 PM
 * Author : Shakran
 */ 

/************************************************************************/
/* Calculation Process Of Timer0
	Clock frequency = 8000000 so, clock per second is 8000000 
	Now time length for one clock cycle is = (1/8000000) second
							               = 0.000000125 second  
										   = 0.000125 mil-seconds
										   = 0.125 u seconds
	That is after every 0.125 u seconds the Timer counter Register will 
	increase (If there is no Prescaler).	
	
	Now come to the Prescaler issue-
	If there is no prescaler then the Timer counter Register will increase 
	at every clock of CPU.
	
	If there is any prescaler then the CPU clock frequency will divided 
	by the prescaler value and the resulted time is the duration for
	increment of the Timer counter Register. 
	
	Let, Prescaler is 64. and CPU clock is 8 MHz
	now time for the increment is-	(1/8000000)*64 Second
									= 0.000008 second 
									= 0.008 ms
									= 8 us		
														   
	Now calculate the time for Timer0 Interrupt-
	we all know that Timer0 is a 8 bit timer 
	so this timer register is capable of counting from 0-255
	if increment duration is 8 us (64 prescaler) then the 
	Timer register will overflow after - 256 x 8us	
									   = 2048 us
									   =2.048 ms
	That is Timer0 interrupt will generate every 2.048 ms
	
	Now if we want to generate Interrupt as per our requirement
	i.e 1ms, 2ms, 5ms, 10ms, ... 1 sec etc. or any desired time
	then we should do some basic calculation within the Timer counter
	Register.
	Now from the discussion above we can calculate the time for 
	one step increment of timer register. so now, we have to find out
	how many step is required to get our desired time.
	
	Let, we want Interrupt every 1ms i.e 0.001 second
	If clock = 8MHz and Prescaler 64
	then the step required to fulfill our time is -
	 
						 (Time in second x MCU Frequency in Hz)
	Desired Value  = 	---------------------------------------
									(Prescaler)
								
							(0.001 second x 80000000 Hz)
				   = 	---------------------------------------
									    64
				   = 125
	That is 125 step increment is required for 1 ms. but !!
	we have 0-255 step for overflow ... !!!
	If we initially load some value to the Timer counter Register
	i.e if we load	255-125 = 130 to the register, so that the counting 
	start from 130 and overflow at 255. Now we got 125 step to overflow
	interrupt.		 			   			   
	                                                                    */
/************************************************************************/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



ISR(TIMER0_OVF_vect)
{
	PORTB = ~PORTB;
	TCNT0 = 0;				// Reset Timer Counter Register after every Interrupt
	//TIFR |= 1 << TOV0;	//Clear Timer0 Overflow Flag
}



int main(void)
{
    
	DDRB = 0xFF;
	PORTB = 0xFF;
	
	TCCR0 |= (1<<CS00);			//Timer0, Normal mode, No prescaller
	TIMSK |= (1<<TOIE0);		//Enable Timer0 overflow interrupt
	TCNT0 = 0;					//Clear Timer Counter Register
	sei();
	
    while (1) 
    {
		
    }
}
