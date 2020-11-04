//======Import info======//
//FUSE Bits: LOW  = 0x24, HIGH = 0xD9
//Clock: internal 8MHz
//BOD: 4.0V
//Startup Time: 6CK + 64ms
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c_lib.h"
#include "ds1307_lib.h"
//----------------------------------------------------------------------------
unsigned char digitNormalNoDot [15] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
unsigned char digitNormalDotted[15] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};

unsigned char digitMirrorNoDot [15] = {0x3F, 0x30, 0x5B, 0x79, 0x74, 0x6D, 0x6F, 0x38, 0x7F, 0x7D};
unsigned char digitMirrorDotted[15] = {0xBF, 0xB0, 0xDB, 0xF9, 0xF4, 0xED, 0xEF, 0xB8, 0xFF, 0xFD};
//----------------------------------------------------------------------------
unsigned char show[5];
unsigned char anodeSelect = 0;
unsigned char blinkFlag = 0;
unsigned char Seconds, Minutes, Hours, Date, Day, Month, Year;	//Variables declare
//----------------------------------------------------------------------------
void RTC_Enable(void);											//Function prototype declare
void _12H_24H_Setup(void);
void RTC_Read(void);
void RTC_Write(void);
void Convert_Data(void);
void show_hours(void);
void show_minutes(void);
//----------------------------------------------------------------------------

int main(void)
{
	//----------------------------------------------------------------------------
	DDRB  |= 0b11111111;
	PORTB |= 0b00000000;
	
	DDRD  |= 0b00001111;
	PORTD |= 0b00000000;
	//----------------------------------------------------------------------------
	TCCR0 |= (1 << CS02);		//Timer0, Normal mode, 256 prescaler
	TIMSK |= (1 << TOIE0);		//Enable Timer0 overflow interrupt
	TCNT0 = 100;				//Clear TCNT0	
	//----------------------------------------------------------------------------
	RTC_Enable();				//Enable RTC
	_12H_24H_Setup();			//Select 12H / 24H mode
	_delay_ms(50);				//Delay for stabilization
	I2CInit();					//Initialize I2C Bus
	
	
	
	Seconds = 0, Minutes = 5, Hours = 13, Date = 12, Day = 7, Month = 12, Year = 14;
	RTC_Write();
	
	
	
	//----------------------------------------------------------------------------
	sei();						//Enable Global interrupt
	//----------------------------------------------------------------------------	
	
	while(1)
	{
		//----------------------------------------------------------------------------
		_delay_ms(1000);
		blinkFlag = ~blinkFlag;		
		//----------------------------------------------------------------------------		
		RTC_Read();
		Convert_Data();		
		show_hours();
		show_minutes();
		//----------------------------------------------------------------------------
	}
}

void RTC_Enable(void)
{
	uint8_t temp;
	
	DS1307Read(0x00, &temp);	//Reads 0th byte and keeps in temp
	temp &= (~(1 << 7));		//Make the 7th bit to 0
	DS1307Write(0x00, temp);	//Clear CH (7th) bit of RTC to enable DS1307
}

void _12H_24H_Setup(void)
{
	uint8_t temp;
	
	DS1307Read(0x02, &temp);	//Reads 2th byte and keeps in temp
	temp &= (0b10111111);		//Make the 6th bit to 0 for 24-hour mode
	DS1307Write(0x02, temp);	//Write 0 to 6th bit for 24-hour mode
}

void RTC_Read(void)
{
	DS1307Read(0x00, &Seconds);
	DS1307Read(0x01, &Minutes);
	DS1307Read(0x02, &Hours);
	DS1307Read(0x03, &Day);
	DS1307Read(0x04, &Date);
	DS1307Read(0x05, &Month);
	DS1307Read(0x06, &Year);
}

void Convert_Data(void)
{
	Seconds = ((Seconds & 0b11110000) >> 4) * 10 + (Seconds & 0b00001111);
	Minutes = ((Minutes & 0b11110000) >> 4) * 10 + (Minutes & 0b00001111);
	Hours   = ((Hours   & 0b11110000) >> 4) * 10 + (Hours   & 0b00001111);
	Day     = Day;
	Year    = ((Year    & 0b11110000) >> 4) * 10 + (Year    & 0b00001111);
	Date    = ((Date    & 0b11110000) >> 4) * 10 + (Date    & 0b00001111);
	Month   = ((Month   & 0b11110000) >> 4) * 10 + (Month   & 0b00001111);
}

void RTC_Write(void)
{
	uint8_t temp;
	
	temp = ((Seconds / 10) << 4) | (Seconds % 10);
	DS1307Write(0x00, temp);

	temp = ((Minutes / 10) << 4) | (Minutes % 10);
	DS1307Write(0x01, temp);

	temp = ((Hours / 10)   << 4) | (Hours % 10);
	DS1307Write(0x02, temp);
	
	temp = Day;
	DS1307Write(0x03, temp);
	
	temp = ((Date / 10)   << 4) | (Date % 10);
	DS1307Write(0x04, temp);
	
	temp = ((Month / 10)   << 4) | (Month % 10);
	DS1307Write(0x05, temp);
	
	temp = ((Year / 10)   << 4) | (Year % 10);
	DS1307Write(0x06, temp);
	
	_delay_ms(100);
}

void show_hours(void)
{
	show[0] = (Hours / 10);
	show[1] = (Hours % 10);
}

void show_minutes(void)
{
	show[2] = (Minutes / 10);
	show[3] = (Minutes % 10);
}

ISR(TIMER0_OVF_vect)
{
	anodeSelect++;
	
	if(anodeSelect == 1)
	{
		PORTD = 0x10;		
		PORTB = digitNormalNoDot[show[0]];
	}
	else if(anodeSelect == 2)
	{
		if(blinkFlag)
		{
			PORTD = 0x20;
			PORTB = digitNormalDotted[show[1]];
		}
		else
		{
			PORTD = 0x20;
			PORTB = digitNormalNoDot[show[1]];
		}
	}
	else if(anodeSelect == 3)
	{
		if(blinkFlag)
		{
			PORTD = 0x40;
			PORTB = digitMirrorDotted[show[2]];
		}
		else
		{
			PORTD = 0x40;
			PORTB = digitMirrorNoDot[show[2]];
		}
	}
	else if(anodeSelect == 4)
	{
		PORTD = 0x80;		
		PORTB = digitNormalNoDot[show[3]];
		
		anodeSelect = 0;
	}

	TCNT0 = 100;		//Clear TCNT0
	TIFR |= 1 << TOV0;	//Clear Timer0 Overflow Flag
}

//void RTC_Write(void)
//{
	//uint8_t temp;
	//
	//temp = ((Seconds / 10) << 4) | (Seconds % 10);
	//DS1307Write(0x00, temp);
//
	//temp = ((Minutes / 10) << 4) | (Minutes % 10);
	//DS1307Write(0x01, temp);
//
	//temp = ((Hours / 10)   << 4) | (Hours % 10);
	//DS1307Write(0x02, temp);
	//
	//temp = Day;
	//DS1307Write(0x03, temp);
	//
	//temp = ((Date / 10)   << 4) | (Date % 10);
	//DS1307Write(0x04, temp);
	//
	//temp = ((Month / 10)   << 4) | (Month % 10);
	//DS1307Write(0x05, temp);
	//
	//temp = ((Year / 10)   << 4) | (Year % 10);
	//DS1307Write(0x06, temp);
	//
	//_delay_ms(100);
//}