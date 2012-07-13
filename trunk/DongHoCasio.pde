#include <SPI.h>
#include <TimerOne.h>
#define LAT 10
#define BLINK 8
#define MODEBUT  5
#define CHANGEBUT 6
#define SETBUT 4

#define NOMAL_MODE 0
#define SPORT_MODE 1
#define COUNT_DOWN_MODE 2

#define SETUP  3
/********************Variable********************/
unsigned char C[11] ={
  192,249,164,176,153,146,130,248,128,144,164}; 
unsigned char Hour = 0;
unsigned char Minute = 0;
unsigned char Second = 0;
unsigned char Tick =0;
unsigned char Mode =0;
unsigned char TATOP =1;
unsigned char RESET =0;
byte Button;
//sport clock variable
unsigned char sTick;
unsigned char sSecond;
//count down variable
byte CountDownFlag = 0;
unsigned char cTick;
unsigned char cSecond;
unsigned char cMinute;
unsigned char cHour;
//getkey variable
byte KeyReg0[3];
byte KeyReg1[3];
byte KeyReg2[3];
byte CurrentKey[3];
byte PreKey[3];
//
byte Test = 0;
//
/********************Function********************/

void setup()
{
  Serial.begin(9600);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(timerIsr);

  pinMode(BLINK,OUTPUT);
  //digitalWrite(BLINK,LOW);
  pinMode(LAT,OUTPUT);
  pinMode(MODEBUT, INPUT);
  pinMode(CHANGEBUT,INPUT);
  pinMode(SETBUT,INPUT);
  SPI.begin();
}


void loop()
{
  if(Test == 1){
    Button = getKey();
    //  Serial.print("Timer_ Button: ");
    //  Serial.println(Button,DEC);
    
    

    //process for sport
    switch(Mode){
    case NOMAL_MODE:

      break;
    case SPORT_MODE:
      if(TATOP != 1){
        sTick++;
        if(sTick>=99){
          sTick=0;
          sSecond++;
          if(sSecond >= 99){
            sSecond = 0;
          }
        }
      }
      break;
    case COUNT_DOWN_MODE:
      if(CountDownFlag != 0){
        cTick--;
        if(cTick==0){
          cTick = 99;
          cSecond--;
          if(cSecond == 0){
            cSecond = 59;
            cMinute--;
            if(cMinute == 0){
              CountDownFlag = 0;  
            }
          }
        }
      }
      break;
    default: 
      Mode = NOMAL_MODE ;
      break;
    }
  }
  Test = 0;
  ////////////////////////////////////////////////// 
  //display
  switch(Mode){
  case NOMAL_MODE:
    nomalModeProcess();
    break;
  case SPORT_MODE:
    sportModeProcess();

    break;
  case COUNT_DOWN_MODE:
    countDownModeProcess();
    break;
  default: 
    Mode = NOMAL_MODE;
  }
  delay(10);
}






