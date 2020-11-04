/*
 * DS3232M_lib.h
 *
 * Created: 9/18/2015 1:31:26 AM
 *  Author: Shakran
 */ 


#ifndef DS3232M_LIB_H_
#define DS3232M_LIB_H_

#define DS3232M_ADDRESS_WRITE_COMMAND	0xD0		//0b11010000
#define DS3232M_ADDRESS_READ_COMMAND	0xD1		//0b11010001

#include <avr/io.h>

uint8_t DS3232M_Read(uint8_t address, uint8_t *data);
uint8_t DS3232M_Write(uint8_t address, uint8_t data);

#endif /* DS3232M_LIB_H_ */