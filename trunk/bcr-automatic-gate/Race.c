/*/////////////////////////////////////////*/
//
//
//
//
//
/*/////////////////////////////////////////*/
#include "Race.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Led7/Led7.h"
#include "RCServo/RCServo.h"
#include "Sensor/Sensor.h"
#include "RF/RF.h"
//#include "EEPROM/EEPROM.h"
#include <avr/eeprom.h>
//Declare variable
volatile unsigned char RaceStatus;
volatile unsigned int DelayTime;

unsigned char StorageResult[MAX_PLAYER][STORAGE_BYTE] ;
unsigned char Player=0;
volatile unsigned char Lap;
unsigned char tmp;
unsigned char FlagFirstTimeGetSensor;
//Declare function
void init_race()
{
	init_sensor();
	RaceStatus = READY;
	Lap = 0;
	Second =0;
	Tick = 0;	
	DelayTime=0;
	SensorFlag = 0;
}
void count_down()
{
	RaceStatus = COUNT_DOWN;
	clear_led();
	cli();
	ScanBuffer[2] = led7_data[5];
	ScanBuffer[5] = led7_data[5];
	sei();
	//scan_led(5);
	_delay_ms(1000);
	cli();
	ScanBuffer[2] = led7_data[4];
	ScanBuffer[5] = led7_data[4];
	sei();
	//scan_led(5);
	_delay_ms(1000);
	cli();
	ScanBuffer[2] = led7_data[3];
	ScanBuffer[5] = led7_data[3];
	sei();
	//scan_led(5);
	_delay_ms(1000);
	cli();
	ScanBuffer[2] = led7_data[2];
	ScanBuffer[5] = led7_data[2];
	sei();
	//scan_led(5);
	_delay_ms(1000);
	cli();
	ScanBuffer[2] = led7_data[1];
	ScanBuffer[5] = led7_data[1];
	sei();
	//scan_led(5);
	_delay_ms(1000);
}
void start_racing()
{
	//enable timer
	RaceStatus = RUNNING;	
	//mo cong duong dua
	handle(OPEN_POSITION);
	SensorFlag = 0;
	//DelayTime = 5000;
	FlagFirstTimeGetSensor = 1;
}
void racing()
{	
	unsigned char StopFlag;
	StopFlag =0;
	handle(CLOSE_POSITION);
	count_down();
	start_racing();

	while((Lap < MAX_ROUND) &&(Second <1000)){	
		_delay_us(100);
		if(SensorFlag > 0){
			DelayTime = 3000;//thoi gian de khong nhan nut nhan= 2ms *delaytime; 2000=2s, max =65536 = 65s		
			SensorFlag =0;
			if(FlagFirstTimeGetSensor == 1)
				FlagFirstTimeGetSensor  = 0;
			else 
				Lap ++;	
			//if(Lap >= MAX_ROUND) RaceStatus = FINISH;
			uart_put(Player);
			_delay_us(10);
			uart_put(Lap);
			_delay_us(10);
			uart_put(Second/256);
			_delay_us(10);
			uart_put(Second%256);
			_delay_us(10);
			uart_put(Tick);					
		}		
		if(UCSRA & (1<<RXC)) {			
				StopFlag =  uart_get();
				if(StopFlag == '0') break;
				else if(StopFlag == '9') Lap--;
		}
	}	
	RaceStatus = FINISH;
	StorageResult[Player][0] = (Player<<2)|(Second>>8);
	StorageResult[Player][1] = (Second%256);
	StorageResult[Player][2] = Tick;
	
	
	tmp = (Player*STORAGE_BYTE+0 );
	eeprom_write_byte(tmp,StorageResult[Player][0]);
	_delay_ms(1);

	tmp = (Player*STORAGE_BYTE+1 );
	eeprom_write_byte(tmp,StorageResult[Player][1]);
	_delay_ms(1);

	tmp = (Player*STORAGE_BYTE+2 );
	eeprom_write_byte(tmp,StorageResult[Player][2]);

	Player++;

}

