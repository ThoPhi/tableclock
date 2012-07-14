/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#include <avr/io.h>
#include "RCServo.h"

/*

void init_PWM()
{

}
void PWM_write(unsigned int speed)
{
	OCR1A = speed;
}
void init_RCServo()
{
	init_PWM();
	PWM_write(0);
}*/
void handle(int _angle){
	RC_ANGLE = HANDLE_CENTER - HANDLE_STEP * _angle;
}
