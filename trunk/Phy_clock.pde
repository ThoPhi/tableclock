 
/********************Variable********************/

byte t = 0;
byte nSetTimeFlag = 0;
byte cSetTimeFlag = 0;



/********************Function********************/

void transData(unsigned char Hour,unsigned char Minute)
{
  digitalWrite(LAT,LOW);
  SPI.transfer(C[Hour/10]);
  SPI.transfer(C[Hour%10]);
  SPI.transfer(C[Minute/10]);
  SPI.transfer(C[Minute%10]);
  digitalWrite(LAT,HIGH);
}
void transData4(unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
  digitalWrite(LAT,LOW);
  SPI.transfer(a);
  SPI.transfer(b);
  SPI.transfer(c);
  SPI.transfer(d);
  digitalWrite(LAT,HIGH);
}
/**********************FUNCTION********************/
//parameter:  
//return  :    
//Description:  
/****************************************************/
void timerIsr()
{
  Test = 1; 
  Tick++;
  if(Tick>99){
    Tick=0;
    Second++;
    if(Second > 59){
      Second = 0;
      Minute++;
      if(Minute > 59){
        Minute = 0;
        Hour++;
        if(Hour > 23){
          Hour = 0;
        }
      }
    }
  }

}

/**********************FUNCTION********************/
//parameter:  
//return  :    
//Description:  
/****************************************************/
byte getKey(){
  for(byte i=0;i<3;i++){
    KeyReg0[i] = KeyReg1[i];
    KeyReg1[i] = CurrentKey[i];
    CurrentKey[i] = digitalRead(SETBUT+i);  
    if((KeyReg1[i] == KeyReg0[i])&&(KeyReg1[i] == CurrentKey[i])){
      if((CurrentKey[i] != PreKey[i]) && (CurrentKey[i] == 0)) {
        PreKey[i] = CurrentKey[i];
        return i+1;
      }
      PreKey[i] = CurrentKey[i];
    }
  }
  return 0;
}

/**********************NOMALMODE_PROCESS********************/
//parameter:  
//return  :    
//Description:  
/****************************************************/
void nomalModeProcess(){
  if(Button == 2){
    Mode = (Mode+1)%2;
    //Button = 0;
  }
  else if(Button == 3){
    nSetTimeFlag = (nSetTimeFlag+1)%3;
    //Button = 0;
  }
  else if(Button == 1){
    if(nSetTimeFlag == 1){
      Minute++;
    }
    else if(nSetTimeFlag == 2){
      Hour++;
    }
    //Button = 0;
  }
  else{
    switch(nSetTimeFlag){
    case 1: 
      if(Tick<50){
        transData4(C[Hour/10],C[Hour%10],255,255);
      }
      else{
        transData(Hour,Minute);
      }
      break;
    case 2:
      if(Tick>50){
        transData4(255,255,C[Minute/10],C[Minute%10]);
      }
      else{
        transData(Hour,Minute);
      }
      break;
    default:
      transData(Hour,Minute);
      break;

    }
  }
}
/**********************SPORT_PROCESS********************/
//parameter:  
//return  :    
//Description:  
/****************************************************/
void sportModeProcess(){
  if(Button == 2){
    Mode = (Mode+1)%3;
    //Button = 0;
    //    Serial.println("BUTTON 1");
  }
  else if(Button == 3){
    //    Serial.println("BUTTON 2");
    TATOP = (TATOP+1)%2;
    //Button = 0;
  }
  else if(Button == 1){
    //    Serial.println("BUTTON 3");
    if(TATOP == 1)
    {
      sSecond = 0;
      sTick = 0;
      //Button = 0;
    }
  }
  else{
    Serial.println("in sport mode");
    transData(sSecond,sTick);
  }
}
/**********************COUNTDOWN_MODE_PROCESS********************/
//parameter:  
//return  :    
//Description:  
/****************************************************/
void countDownModeProcess(){
  if(Button == 2){
    Mode = (Mode+1)%3;
    //Button = 0;
  }
  else if(Button == 3){
    //Button = 0;
    cSetTimeFlag = (cSetTimeFlag+1)%3;
  }
  else if(Button == 1){
    if(cSetTimeFlag == 1){
      cSecond++;
      CountDownFlag = 0;
    }else if(cSetTimeFlag == 2){
      cMinute++;
      CountDownFlag = 0;
    }else if(cSetTimeFlag == 0){
      CountDownFlag = 1;
    }
  }
  else{
    switch(cSetTimeFlag){
    case 1: 
      if(Tick<50){
        transData4(C[cMinute/10],C[cMinute%10],255,255);
      }
      else{
        transData(cMinute,cSecond);
      }
      break;
    case 2:
      if(Tick>50){
        transData4(255,255,C[cSecond/10],C[cSecond%10]);
      }
      else{
        transData(cMinute,cSecond);
      }
      break;
    default:
      transData(cMinute,cSecond);
      break;

    }
  }
}













