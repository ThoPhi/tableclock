/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#include "EEPROM.h"
#include <avr/io.h>

void EEPROM_write(unsigned int uiAdress, unsigned char ucData)
{
	/*wait for completion of previous write*/
	while(EECR & (1<<EEWE));
	/*Set up adress and data registers*/
	EEAR = uiAdress;
	EEDR = ucData;
	/*Write logical one to EEMWE*/
	EECR |= (1<<EEMWE);
	/*Start eeprom write by setting EEWE*/
	EECR |= (1<<EEWE);
}
unsigned char EEPROM_read(unsigned int uiAdress)
{
	/* Wait for completion of previous write*/
	while(EECR & (1<<EEWE));
	/*Set up adress register*/
	EEAR = uiAdress;
	/*Start eeprom read by writing EERE*/
	EECR |= (1<<EERE);
	/*Return data from fata register*/
	return EEDR;
}

