/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "Led7.h"
#include "../Sensor/sensor.h"
#include "../Race.h"
#include "../RF/RF.h"

//macro

//variable
unsigned char led7_data[10] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
volatile unsigned char ScanBuffer[6] = {0x00, 0x00, 0x00, 0x00,0x00,0x00};

volatile unsigned char Tick;
volatile unsigned int Second;



//Physical function
void init_SPI()
{
	// SPI initialization
	// SPI Type: Master
	// SPI Clock Rate: 2000.000 kHz
	// SPI Clock Phase: Cycle Half
	// SPI Clock Polarity: Low
	// SPI Data Order: MSB First
	SPCR=0x50;
	SPSR=0x00;
}
void init_LED7()
{
	Second = 0;
	Tick = 0;
	init_SPI();
}
unsigned char SPI_read()
{
	unsigned char SPIData;
	SPIData = SPDR;
	return SPIData;
}
unsigned char SPI_write(unsigned char WriteData)
{
	SPDR = WriteData;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void scan_led(unsigned char LedIndex)
{
	LATCH_READY;
	SPI_write(ScanBuffer[5]);
	SPI_write(ScanBuffer[4]);
	SPI_write(ScanBuffer[3]);
	SPI_write(ScanBuffer[2]);
	SPI_write(ScanBuffer[1]);
	SPI_write(ScanBuffer[0]);
	LATCH_OUT;
}
void clock_tick()
{
	Tick++;
	if(Tick>=100){
		Tick = 0;
		Second ++;
		if(Second >=1000)
			Second = 0;			
	}	
	//update_buffer();
}
void update_buffer()
{
	ScanBuffer[5] = led7_data[Lap%10];
	ScanBuffer[4] = led7_data[Second/100];
	ScanBuffer[3] = led7_data[(Second/10)%10];
	ScanBuffer[2] = led7_data[Second%10] & 0x7f;//dot;
	ScanBuffer[1] = led7_data[Tick/10];
	ScanBuffer[0] = led7_data[Tick%10];
}
void clear_led()
{
	LATCH_READY;
	ScanBuffer[5] = 0xff;
	ScanBuffer[4] = 0xff;
	ScanBuffer[3] = 0xff;
	ScanBuffer[2] = 0xff;
	ScanBuffer[1] = 0xff;
	ScanBuffer[0] = 0xff;
	LATCH_OUT;
}

