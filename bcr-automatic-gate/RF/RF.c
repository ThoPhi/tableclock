/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#include "RF.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void uart_init(){
	// USART initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 9600
	UCSRA=0x00;
	UCSRB=0x18;
	UCSRC=0x86;
	UBRRH=0x00;
	UBRRL=0x33;

	
/*	// USART initialization
	// Communication Parameters: 8 Data, 1 Stop, No Parity
	// USART Receiver: On
	// USART Transmitter: On
	// USART Mode: Asynchronous
	// USART Baud Rate: 38400
	UCSRA=0x00;
	UCSRB=0x18;
	UCSRC=0x86;
	UBRRH=0x00;
	UBRRL=0x0C;*/
}
void uart_put(unsigned char c){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )	;
	/* Copy ninth bit to TXB8 */
	//UCSRB &= ~(1<<TXB8);
	//if ( data & 0x0100 )
	//UCSRB |= (1<<TXB8);
	/* Put data into buffer, sends the data */
	UDR = c;
}
unsigned char uart_get(){
	/* Wait for data to be received */
//	while ( !(UCSRA & (1<<RXC)) )	;
	//UCSRA &=(~(1<<RXC));
	/* Get and return received data from buffer */
	return UDR;
}
