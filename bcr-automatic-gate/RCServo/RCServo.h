/*/////////////////////////////////*/
//Project		:	BCRGate
//MCU		:	Atmega8L
//Config		:	Int RC 8MHz
//
//
//
/*/////////////////////////////////*/
#ifndef _RCSERVO_H_
#define _RCSERVO_H_

#define RC_ANGLE 			OCR1A
#define HANDLE_STEP			5
#define HANDLE_CENTER 		750
#define OPEN_POSITION		8
#define CLOSE_POSITION		94

void handle(int _angle);
//void init_RCServo();
#endif
