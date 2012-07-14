/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#ifndef _RF_H_
#define _RF_H_

void uart_init();
void uart_put(unsigned char c);
unsigned char uart_get();
#endif
