#define F_CPU 8000000UL 

#include <avr/io.h> 
#include <avr/pgmspace.h> 
#include <util/delay.h> 
#include <inttypes.h> 
#include "lcd_lib.h" 
#include "i2c_lib.h" 
#include "ds1307_lib.h" 

#define clock		(PIND & 0x01) 
#define start		(PIND & 0x02) 
#define stop		(PIND & 0x04) 
#define plus		(PIND & 0x08) 
#define minus		(PIND & 0x10) 
#define set			(PIND & 0x20) 
#define load_off	(PORTD |= 0x40) 
#define load_on		(PORTD &= 0xBF) 

void LCD_RTC_Init(void);
void RTC_Enable(void); 
void _12H_24H_Setup(void);
void delay1s(void); 
void fixed_text(void); 
void RTC_Read(void); 
void RTC_Write(void); 
void Read_Data_Conversion(void); 
void Show_Date_Time(void); 
void Button_Press_Detection(void);

unsigned char EEPROM_Read_Byte(unsigned int EeAddress); 
void EEPROM_Read_String(unsigned int EeAddress, unsigned char *StrAddress); 
void EEPROM_Write_Byte(unsigned int EepAddress, unsigned char DataByte); 
void EEPROM_Write_String(unsigned int EepAddress, unsigned char *StrAddress); 

signed char Seconds, Minutes, Hours, Date, Day, Month, Year; 
const char Day_name[8][4] = {"NUL", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}; 

signed char menu = 0; 

signed char start_hour, start_min, stop_hour, stop_min; 
signed int current_time, start_time, stop_time; 

int main(void)
{
	LCD_RTC_Init(); 
	RTC_Enable(); 
	_12H_24H_Setup(); 

	fixed_text(); 
	
	DDRD = (DDRD & 0x00) | 0x40; 
	PORTD = 0x7F; 
	
	start_hour = EEPROM_Read_Byte(0); 
	start_min  = EEPROM_Read_Byte(1); 
	stop_hour  = EEPROM_Read_Byte(2); 
	stop_min   = EEPROM_Read_Byte(3); 
	
	while(1) 
	{
		//======================================= Regular Loop 
		if(menu == 0) 
		{
			RTC_Read();
			Read_Data_Conversion();
			Show_Date_Time();
			
			_delay_ms(800); 
			
			Button_Press_Detection(); 
		} 
		//======================================= DATE Setting Loop 
		else if(menu == 1) 
		{
			if(plus == 0) 
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Date;	
				
				if(Date >= 31)
				{
					Date = 31;
				}
				
				LCDWriteIntXY(1, 0, Date, 2);
				LCDcursorLeft(1);
			} 
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
					
				--Date;
				
				if(Date <= 1)
				{
					Date = 1;
				}
				
				LCDWriteIntXY(1, 0, Date, 2);
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80); 
				
				menu = 2; 
				
				LCDcursorRight(3);
			}				
		}
		//======================================= MONTH Setting Loop 
		else if(menu == 2) 
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Month;
				
				if(Month >= 12)
				{
					Month = 12;
				}
				
				LCDWriteIntXY(4, 0, Month, 2);
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--Month;
				
				if(Month <= 1)
				{
					Month = 1;
				}
				
				LCDWriteIntXY(4, 0, Month, 2);
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 3;
				
				LCDcursorRight(5);
			}
		}
		//======================================= YEAR Setting Loop 
		else if(menu == 3)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Year;
				
				if(Year >= 99)
				{
					Year = 99;
				}
				
				LCDWriteIntXY(9, 0, Year, 2);
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--Year;
				
				if(Year < 0)
				{
					Year = 0;
				}
				
				LCDWriteIntXY(9, 0, Year, 2);
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 4; 
				
				LCDcursorRight(4);
			}
		}
		//======================================= DAY Setting Loop 
		else if(menu == 4)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Day;
				
				if(Day > 7)
				{
					Day = 1;
				}
				
				LCDWriteStringXY(12, 0, Day_name[Day]) 
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--Day;
				
				if(Day < 1)
				{
					Day = 7;
				}
				
				LCDWriteStringXY(12, 0, Day_name[Day]) 
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 5;
				
				LCDGotoXY(5, 1);
			}
		}
		//======================================= HOUR Setting Loop 
		else if(menu == 5)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Hours;
				
				if(Hours >= 23)
				{
					Hours = 23;
				}
				
				LCDWriteIntXY(4, 1, Hours, 2); 
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--Hours;
				
				if(Hours <= 0)
				{
					Hours = 0;
				}
				
				LCDWriteIntXY(4, 1, Hours, 2); 
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 6;
				
				LCDGotoXY(8, 1);
			}
		}
		//======================================= MINUTE Setting Loop 
		else if(menu == 6)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Minutes;
				
				if(Minutes >= 59)
				{
					Minutes = 59;
				}
				
				LCDWriteIntXY(7, 1, Minutes, 2); 
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--Minutes;
				
				if(Minutes <= 0)
				{
					Minutes = 0;
				}
				
				LCDWriteIntXY(7, 1, Minutes, 2); 
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 7;
				
				LCDGotoXY(11, 1);
			}
		}
		//======================================= SECOND Setting Loop
		else if(menu == 7)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++Seconds;
				
				if(Seconds >= 59)
				{
					Seconds = 59;
				}
				
				LCDWriteIntXY(10, 1, Seconds, 2); 
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--Seconds;
				
				if(Seconds <= 0)
				{
					Seconds = 0;
				}
				
				LCDWriteIntXY(10, 1, Seconds, 2); 
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80); 
								
				RTC_Write(); 
				_delay_ms(100); 
				LCDcursorOFF(); 
				
				menu = 0; 				
			}
		}
		//======================================= START HOUR Setting Loop 
		else if(menu == 11)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++start_hour;
				
				if(start_hour >= 23)
				{
					start_hour = 23;
				}
				
				LCDWriteIntXY(5, 1, start_hour, 2); 
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--start_hour;
				
				if(start_hour <= 0)
				{
					start_hour = 0;
				}
				
				LCDWriteIntXY(5, 1, start_hour, 2); 
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 12;
				
				LCDGotoXY(9, 1);
			}
		}		
		//======================================= START MINUTE Setting Loop 
		else if(menu == 12)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++start_min;
				
				if(start_min >= 59)
				{
					start_min = 59;
				}
				
				LCDWriteIntXY(8, 1, start_min, 2); 
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--start_min;
				
				if(start_min <= 0)
				{
					start_min = 0;
				}
				
				LCDWriteIntXY(8, 1, start_min, 2); 
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				EEPROM_Write_Byte(0, start_hour);
				EEPROM_Write_Byte(1, start_min); 			
				
				_delay_ms(100);
				LCDclr(); 
				LCDcursorOFF();
				fixed_text(); 
								
				menu = 0;
			}
		}		
		//======================================= STOP HOUR Setting Loop 
		else if(menu == 21)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++stop_hour;
				
				if(stop_hour >= 23)
				{
					stop_hour = 23;
				}
				
				LCDWriteIntXY(5, 1, stop_hour, 2);
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--stop_hour;
				
				if(stop_hour <= 0)
				{
					stop_hour = 0;
				}
				
				LCDWriteIntXY(5, 1, stop_hour, 2);
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				menu = 22;
				
				LCDGotoXY(9, 1);
			}
		}
		//======================================= STOP MINUTE Setting Loop
		else if(menu == 22)
		{
			if(plus == 0)
			{
				while(plus == 0);
				_delay_ms(80);
				
				++stop_min;
				
				if(stop_min >= 59)
				{
					stop_min = 59;
				}
				
				LCDWriteIntXY(8, 1, stop_min, 2);
				LCDcursorLeft(1);
			}
			else if(minus == 0)
			{
				while(minus == 0);
				_delay_ms(80);
				
				--stop_min;
				
				if(stop_min <= 0)
				{
					stop_min = 0;
				}
				
				LCDWriteIntXY(8, 1, stop_min, 2);
				LCDcursorLeft(1);
			}
			else if(set == 0)
			{
				while(set == 0);
				_delay_ms(80);
				
				EEPROM_Write_Byte(2, stop_hour);
				EEPROM_Write_Byte(3, stop_min);
				
				_delay_ms(100);
				LCDclr();
				LCDcursorOFF();
				fixed_text();
				
				menu = 0;
			}
		}
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

unsigned char EEPROM_Read_Byte(unsigned int EeAddress) 
{
	while(EECR & (1 << EEWE)); 
	
	EEAR = EeAddress; 
	EECR |= (1 << EERE); 
	
	return EEDR; 
}

void EEPROM_Read_String(unsigned int EeAddress,unsigned char *StrAddress) 
{
	while(EEPROM_Read_Byte(EeAddress) != '#') 
	
	*StrAddress++ = EEPROM_Read_Byte(EeAddress++); 
	*StrAddress = '\0'; 
}

void EEPROM_Write_Byte(unsigned int EepAddress, unsigned char DataByte) 
{
	while(EECR & (1 << EEWE));	//Wait for completion of previous write 
	
	EEAR = EepAddress;			//Set up address and data registers 
	EEDR = DataByte;			//Write logical one to EEMWE 
	EECR |= (1 << EEMWE);		//Start eeprom write by setting EEWE 
	EECR |= (1 << EEWE); 
}

void EEPROM_Write_String(unsigned int EepAddress, unsigned char *StrAddress) 
{
	while(*StrAddress)
	{
		EEPROM_Write_Byte(EepAddress++, *StrAddress); 
		StrAddress++; 
	} 
	
	EEPROM_Write_Byte(EepAddress,'#'); 
}

void Button_Press_Detection(void)
{
	if(clock == 0)
	{
		while(clock == 0);
		_delay_ms(80);
		
		menu = 1; 
		
		LCDGotoXY(2, 0); 
		LCDcursorOnBlink(); 
	}
	else if(start == 0)
	{
		while(start == 0);
		_delay_ms(80);
		
		menu = 11; 
		
		LCDclr(); 
		LCDWriteStringXY(3, 0, "START TIME"); 
		LCDWriteStringXY(7, 1, ":"); 		
		LCDWriteIntXY(5, 1, start_hour, 2); 
		LCDWriteIntXY(8, 1, start_min, 2); 
		
		LCDcursorLeft(4); 
		LCDcursorOnBlink();	
	}
	else if(stop == 0)
	{
		while(stop == 0);
		_delay_ms(80);
		
		menu = 21;
		
		LCDclr();
		LCDWriteStringXY(3, 0, "STOP TIME");
		LCDWriteStringXY(7, 1, ":");
		LCDWriteIntXY(5, 1, stop_hour, 2);
		LCDWriteIntXY(8, 1, stop_min, 2);
		
		LCDcursorLeft(4);
		LCDcursorOnBlink();
	}
}