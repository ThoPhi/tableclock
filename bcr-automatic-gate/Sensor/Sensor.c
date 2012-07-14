/*//////////////////////////*/
//
//
//
//
//
/*///////////////////////////*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Sensor.h"
#include "../Race.h"
#include "../RF/RF.h"

volatile unsigned char SensorFlag, ButtonFlag;

unsigned char Input0,Input1,Input2,Input3,OldInput;


void init_sensor()
{
	SensorFlag=0;

}
void update_input()//call from isr timer0
{
	//Input0 = Input1;
	Input1 = Input3;
	Input2 = Input3;
	Input3 = (PIND & 0x0c);
	if(/*(Input0 == Input1)&&*/(Input1 == Input2) && (Input2 == Input3) ){
		if(OldInput!= Input1){				
			
			if(((Input1& SENSOR_PIN)!=(OldInput & SENSOR_PIN))&&((Input1 & SENSOR_PIN)==0)){//tin hieu sensor
				SensorFlag = 1;
			}			
			if((Input1 & BUTTON_PIN)==0){//tin hieu nut  nhan
				ButtonFlag =1;
			}
			OldInput= Input1;
		}			
	}
}
