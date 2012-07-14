/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//File Name	:	Main.c
//
//
/*/////////////////////////////////*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "Race.h"
#include "Led7/Led7.h"
#include "RF/RF.h"
#include "Sensor/sensor.h"
#include "RCServo/RCServo.h"
#include "EEPROM/EEPROM.h"
#include "Timer/Timer.h"
//define macro
#define 	READ_RESULT		'1'
#define 	START_RACE		'2'
#define 	CLOSE_GATE		'3'
#define 	OPEN_GATE		'4'

//variable declaration
unsigned char GetCommand;
unsigned char tmp,tmp1;



//functional declaration


void init_Atmega8();
int main(void)
{
	unsigned char i,j;	
	init_Atmega8();
	init_timer();
	uart_init();
	init_LED7();	
	//init_RCServo();
	init_sensor();
	handle(CLOSE_POSITION);	
	GetCommand = 0;	
	sei();
	while(1){
		ButtonFlag =0;
		while ( !(UCSRA & (1<<RXC)) ){			
			if(ButtonFlag >0){
				break;
			}
			_delay_ms(1);
		}
		if(ButtonFlag >0 ){
			ButtonFlag =0;
			GetCommand = START_RACE;
		}
		else GetCommand = uart_get();			
		
		switch(GetCommand){
		case  READ_RESULT:{
			for(i=0;i<MAX_PLAYER;i++){
				for(j=0;j<STORAGE_BYTE;j++){
					tmp = i * STORAGE_BYTE + j ;
					// co the break ra neu khong con du lieu
					StorageResult[i][j]= eeprom_read_byte(tmp);//EEPROM_read(i*STORAGE_BYTE + j);
					// co the xoa eeprom sau khi doc de sau nay khong bi nham lan
					_delay_ms(1);
				}
			}	
			////////////////////uart_put 5b byte de bao hieu se xuat eeprom
			for(i=0;i<MAX_PLAYER;i++){
				for(j=0;j<STORAGE_BYTE;j++){
					uart_put(StorageResult[i][j]);
				}
			}			
		}break;
		case START_RACE:{
			init_race();
			racing();
		}break;		
		case(CLOSE_GATE):{
			handle(CLOSE_POSITION);
		}break;
		case (OPEN_GATE) :{
			handle(OPEN_POSITION);
		}break;
		case('5') :{
			clock_tick();
			scan_led(5);
		}break;
		case('6') :{
			
		}break;
		case('7') :{
			
		}break;
		case('8'): {
			
		}break;
		case('9'):{
			
		}break;
		default:{

		}break;
		}
		_delay_ms(1);			
	}	
}
void init_Atmega8()
{
	// Input/Output Ports initialization
	// Port B initialization
	// Func7=In Func6=In Func5=Out Func4=In Func3=Out Func2=Out Func1=Out Func0=Out 
	// State7=T State6=T State5=0 State4=T State3=0 State2=0 State1=0 State0=1 
	PORTB=0x01;
	DDRB=0x2F;
	
	// Port C initialization
	// Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
	// State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
	PORTC=0x00;
	DDRC=0x00;
	
	// Port D initialization
	// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=In Func1=Out Func0=In 
	// State7=0 State6=0 State5=0 State4=0 State3=T State2=T State1=0 State0=T 
	PORTD=0x00;
	DDRD=0xF2;
	

	// External Interrupt(s) initialization
	// INT0: Off
	// INT1: Off
	MCUCR=0x00;

	// Global enable interrupts
	//#asm("sei")

}

