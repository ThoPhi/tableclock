/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#ifndef _SENSOR_H_
#define _SENSOR_H_

#define 	SENSOR_PIN		0X04
#define 	BUTTON_PIN		0x08
//extern variable
extern volatile unsigned char SensorFlag;
extern volatile unsigned char ButtonFlag;


//declare function   
void init_sensor();
void update_input();
#endif
