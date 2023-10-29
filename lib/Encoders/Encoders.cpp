#include "Encoders.h"
#include "Arduino.h"

volatile long int position1=0;
volatile long int position2=0;
volatile float velocity1=0;
volatile float velocity2=0;
volatile long prevT1 = 0;
volatile long prevT2 = 0;

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

float getVelocity1(){
  noInterrupts();
  float temp = velocity1;
  interrupts();
  return temp;
}

float getVelocity2(){
  noInterrupts();
  float temp = velocity2;
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
  long currT = micros();
  float deltaT = ((float)(currT - prevT1))/1.0e6;
  prevT1 = currT;
  velocity1 = 1/deltaT; // Only return absolute speed

  if(digitalRead(PORT1_NE1)) // detection du sens de rotation
    position1--;
  else
    position1++;
}

void ISR_encoder2(){
  long currT = micros();
  float deltaT = ((float)(currT - prevT2))/1.0e6;
  prevT2 = currT;
  velocity2 = 1/deltaT; // Only return absolute speed

  if(digitalRead(PORT2_NE1)) // detection du sens de rotation
    position2++;
  else
    position2--;
}
