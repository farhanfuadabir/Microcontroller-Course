/*
 * Full_Step.c
 *
 * Created: 30-Jun-15 12:30:30 PM
 *  Author: Shakran
 */ 






#include <avr/io.h>
#define F_CPU 8000000L			/* crystal define */
#include <util/delay.h>			/* delay header file define */



int main(void){
	/*	input/output define	*/
	DDRB = 0b11111111;
	DDRC = 0b11111111;
	
	
	/*	input/output define	*/
	PORTB = 0b00000000;
	PORTC = 0b00000000;
	
	
	/*	constant define	*/
	
	
	/*	variable define	*/
	int i=0;
	int DelayValue = 200;
	
	
	
	
	
    while(1){
        //TODO:: Please write your application code 
		
       for(i=0;i<5;i++){
	       PORTB=0b00000001;
	       _delay_ms(DelayValue);

	       PORTB=0b00000010;
	       _delay_ms(DelayValue);

	       PORTB=0b00000100;
	      _delay_ms(DelayValue);

	       PORTB=0b00001000;
	       _delay_ms(DelayValue);
       }

       for(i=0;i<5;i++){
	       PORTB=0b00001000;
	       _delay_ms(DelayValue);

	       PORTB=0b00000100;
	       _delay_ms(DelayValue);

	       PORTB=0b00000010;
	       _delay_ms(DelayValue);

	       PORTB=0b00000001;
	       _delay_ms(DelayValue);
       }
		
    }
}