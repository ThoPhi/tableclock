/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#ifndef _EEPROM_H_
#define _EEPROM_H_

void EEPROM_write(unsigned int uiAdress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAdress);


#endif
