/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#ifndef _LED7_H_
#define _LED7_H_

//macro
#define LATCH_READY	(PORTB &= ~(1<<0))
#define LATCH_OUT	(PORTB |= (1<<0))
#define SELECT_NON	(PORTD &= 0x0f);
#define SELECT1		(PORTD &= 0x0f);\
					(PORTD |= (1<<7));
#define SELECT2		(PORTD &= 0x0f);\
					(PORTD |= (1<<6));
#define SELECT3		(PORTD &= 0x0f);\
					(PORTD |= (1<<5));


//variable

extern volatile unsigned char Tick;
extern volatile unsigned int Second;

extern volatile unsigned char ScanBuffer[6];
extern unsigned char led7_data[10];

//function
void init_LED7();
void init_timer();
void scan_led(unsigned char LedIndex);
void clear_led();
void clock_tick();
void update_buffer();
unsigned char SPI_write(unsigned char WriteData);


#endif
