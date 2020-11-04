#define F_CPU 8000000UL 

#include <avr/io.h> 
#include <avr/pgmspace.h> 
#include <util/delay.h> 
#include <inttypes.h> 
#include "lcd_lib.h" 
#include "i2c_lib.h" 
#include "ds1307_lib.h" 

void LCD_RTC_Init(void);
void RTC_Enable(void); 
void _12H_24H_Setup(void);
void delay1s(void); 
void fixed_text(void); 
void RTC_Read(void); 
void RTC_Write(void); 
void Read_Data_Conversion(void); 
void Show_Date_Time(void); 

unsigned char Seconds, Minutes, Hours, Date, Day, Month, Year; 
const char Day_name[8][4] = {"NUL", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}; 


int main(void)
{
	LCD_RTC_Init(); 
	RTC_Enable(); 
	_12H_24H_Setup(); 

	fixed_text(); 
	
	DDRD = (DDRD & 0x00) | 0x40; 
	PORTD = 0x7F; 
	
	
	while(1) 
	{
		RTC_Read();
		Read_Data_Conversion();
		Show_Date_Time();
			
		_delay_ms(800);
	}
	
	return 0;
}

void LCD_RTC_Init(void)
{
	LCDinit();			//Initialize the LCD
	LCDclr();			//Clears LCD
	_delay_ms(50);		//Delay for stabilization
	LCDcursorOFF();		//Cursor OFF
	_delay_ms(50);		//Delay for stabilization
	I2CInit();			//Initialize I2C Bus
	_delay_ms(50);		//Delay for stabilization
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

void delay1s(void) 
{
	uint8_t i;
	
	for(i = 0; i < 100; i++)
	{
		_delay_ms(10);
	}
}

void fixed_text(void) 
{
	LCDWriteString("   /  /20"); 
	LCDGotoXY(0, 1);
	LCDWriteString("      :  :  "); 
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

void Read_Data_Conversion(void) 
{			
	Seconds = ((Seconds & 0b11110000) >> 4) * 10 + (Seconds & 0b00001111); 
	Minutes = ((Minutes & 0b11110000) >> 4) * 10 + (Minutes & 0b00001111); 
	Hours   = ((Hours   & 0b11110000) >> 4) * 10 + (Hours   & 0b00001111); 
	Day     = Day; 
	Year    = ((Year    & 0b11110000) >> 4) * 10 + (Year    & 0b00001111); 
	Date    = ((Date    & 0b11110000) >> 4) * 10 + (Date    & 0b00001111); 
	Month   = ((Month   & 0b11110000) >> 4) * 10 + (Month   & 0b00001111); 
}

void Show_Date_Time(void) 
{
	LCDWriteIntXY(1, 0, Date, 2); 
	LCDWriteIntXY(4, 0, Month, 2); 
	LCDWriteIntXY(9, 0, Year, 2); 
	LCDWriteStringXY(12, 0, Day_name[Day]) 
	LCDWriteIntXY(4, 1, Hours, 2); 
	LCDWriteIntXY(7, 1, Minutes, 2); 
	LCDWriteIntXY(10, 1, Seconds, 2); 
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