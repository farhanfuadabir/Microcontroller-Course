/*
 * EEPROM_Read___Write.c
 *
 * Created: 30-Jun-15 4:05:25 PM
 *  Author: Shakran
 */ 



#include <avr/io.h>
#define F_CPU 8000000L			/* crystal define */
#include <util/delay.h>			/* delay header file define */
#include <avr/eeprom.h>			/* eeprom header file define */



int main(void){
	/*	input/output define	*/
	DDRA = 0b00000000;
	DDRC = 0b11111111;
	
	
	/*	input/output define	*/
	PORTA = 0b00000000;
	PORTC = 0b00000000;
	
	
	/*	constant define	*/

	
	/*	variable define	*/
	int i=0;
	int j=0;
	int DelayValue = 10;
	
	
	PORTC = eeprom_read_byte (( uint8_t *) 46) ;
	
	while(1){
		//TODO:: Please write your application code
		if (PINA & 0x01){			//PINA0 == 1
			PORTC^= (1 << PC0);
			while(PINA & 0x01);
			eeprom_update_byte((uint8_t*)46,PORTC);
			_delay_ms(DelayValue);
		}


		if (PINA & 0x02){
			PORTC^= (1 << PC1);
			while(PINA & 0x02);
			eeprom_update_byte((uint8_t*)46,PORTC);
			_delay_ms(DelayValue);
		}
		

		if (PINA & 0x04){
			PORTC^= (1 << PC2);
			while(PINA & 0x04);
			eeprom_update_byte((uint8_t*)46,PORTC);
			_delay_ms(DelayValue);
		}
		
		
		if (PINA & 0x08){
			PORTC^= (1 << PC3);
			while(PINA & 0x08);
			eeprom_update_byte((uint8_t*)46,PORTC);
			_delay_ms(DelayValue);
		}
		
		
		if (PINA & 0x10){
			PORTC^= (1 << PC4);
			while(PINA & 0x10);
			eeprom_update_byte((uint8_t*)46,PORTC);
			_delay_ms(DelayValue);
		}
		
		
		if (PINA & 0x20){
			PORTC = 0x00;
			while(PINA & 0x20);
			eeprom_update_byte((uint8_t*)46,PORTC);
			_delay_ms(DelayValue);
		}
		
	}
}