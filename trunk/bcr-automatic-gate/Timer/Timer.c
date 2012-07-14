
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer.h"
#include "../SENSOR/sensor.h"
#include "../LED7/LED7.h"
#include "../Race.h"
unsigned char CountTimer;
unsigned char IndexScanLed;



void init_timer()
{
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 1000.000 kHz
	//TCCR0=0x02;
	//TCNT0=0x00;
	
	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: 125.000 kHz
	TCCR0=0x03;
	TCNT0=0x00;
	
	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: 1000.000 kHz
	// Mode: Ph. & fr. cor. PWM top=ICR1
	// OC1A output: Non-Inv.
	// OC1B output: Non-Inv.
	// Noise Canceler: Off
	// Input Capture on Falling Edge
	// Timer 1 Overflow Interrupt: Off
	// Input Capture Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	TCCR1A=0xA0;
	TCCR1B=0x12;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x1f;
	ICR1L=0x40;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;

	
	// Timer/Counter 2 initialization
	// Clock source: System Clock
	// Clock value: Timer 2 Stopped
	// Mode: Phase correct PWM top=FFh
	// OC2 output: Non-Inverted PWM
	ASSR=0x00;
	TCCR2=0x60;
	TCNT2=0x00;
	OCR2=0x00;
	
	// Timer(s)/Counter(s) Interrupt(s) initialization
	//TIMSK=0x44;
	TIMSK = 0x01;
	
	CountTimer = 0;
	IndexScanLed = 0;	
	Second = 0;
	Tick = 0;
}


ISR(TIMER0_OVF_vect)//ngat timer sau moi 2ms
{
	TCNT0 = 39;
	CountTimer++;		
	if(CountTimer >=6){//10ms
		CountTimer = 0;		
		if(RaceStatus == RUNNING ){
			clock_tick();
		}
		if(RaceStatus != COUNT_DOWN)
			update_buffer();
	}	
	if(DelayTime >0){
			DelayTime --;
		}
		else{			
			update_input();	
		}
	IndexScanLed = (IndexScanLed+1)%6;
	scan_led(IndexScanLed);
}


