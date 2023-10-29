#include "Encoders.h"

volatile long int position1=0;
volatile long int position2=0;
void ISR_encoder1();
void ISR_encoder2();

int getPosition1()
{
  noInterrupts();
  int temp = position1;
  interrupts();
  return temp;
}

int getPosition2()
{
  noInterrupts();
  int temp = position2;
  interrupts();
  return temp;
}

void initEncoders()
{ 
  pinMode(PORT1_NE2,INPUT_PULLUP);
  pinMode(PORT1_NE1,INPUT_PULLUP);
  pinMode(PORT2_NE2,INPUT_PULLUP);
  pinMode(PORT2_NE1,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PORT1_NE2),ISR_encoder1,RISING);
  attachInterrupt(digitalPinToInterrupt(PORT2_NE2),ISR_encoder2,RISING);
}


// fonction appelée lors des interruptions 'front montant'
void ISR_encoder1(){
  if(digitalRead(PORT1_NE1)) // detection du sens de rotation
    position1++;
  else
    position1--;
}

void ISR_encoder2(){
  if(digitalRead(PORT2_NE1)) // detection du sens de rotation
    position2++;
  else
    position2--;
}
