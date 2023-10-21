#include <Arduino.h>
#include <MeMegaPi.h>
#include "HardwareSerial.h"
#include "Wire.h"
#include <HCSR04.h>
#include "OPT3101.h"
#include "Motors.h"
// #include "MePort.h"
#include "MeRGBLineFollower.h"

#define BUTTON 14
#define LED 13

MeRGBLineFollower lineSensor(PORT_8, ADDRESS1);

UltraSonicDistanceSensor distanceSensor(13, 12);

Motors motor1(12, 35, 34); // PORT 1
Motors motor2(8, 36, 37); // PORT 2
                          
OPT3101 radar;
uint16_t amplitudes[3];
int16_t distances[3];

int8_t speed = 100;
uint8_t tourne = 0;
uint8_t obj_detecte = 0;


void followLine(int regularSpeed){
  int decalage = lineSensor.getPositionOffset();
  int localSpeed = regularSpeed;

  // On ralentit dans les virages
  if (abs(decalage) > 50)
    localSpeed *= 0.5;

  motor1.setMotorSpeed(localSpeed);
  motor2.setMotorSpeed(localSpeed);
}

void prio(int16_t *distances){
  
  if (distances[2] > 300) 
    return;  // rien n'est detecte à droite

  speed = 0;
  motor1.setMotorSpeed(speed);
  motor2.setMotorSpeed(speed);

  // On attend tant que quelque chose est detecte à droite ou rien à gauche
  while (distances[2] < 300 || distances[0] > 400);
}

void quart_tour(){
  // TODO
}

void setup(){
  Serial.begin(9600);

  pinMode(BUTTON, INPUT_PULLUP); // launch button setup
  pinMode(LED, OUTPUT); // led setup

  // line sensor setup
  lineSensor.begin();
  lineSensor.setKp(0.2);

  for (int i=1; i<=3; i++){
    delay(100);
    lineSensor.setRGBColour(i);
  } // make sure leds are running

  // ultrasonic sensor setup
  
  // radar setup
  Wire.begin();
  radar.init();
  if (radar.getLastError()) {
    Serial.print(F("radar initialization failed: "));
    Serial.println(radar.getLastError());
    while(1);
  }
  radar.setFrameTiming(256);
  radar.setChannel(0);
  radar.setBrightness(OPT3101Brightness::Adaptive);
  radar.startSample();


  // wait until button release
  while (!digitalRead(BUTTON)) {
    digitalWrite(LED, HIGH);
  }
  digitalWrite(LED, LOW);
}

void loop(){

  // Updates sensors information ------------
  lineSensor.loop();

  if (radar.isSampleDone()) {
    radar.readOutputRegs();

    amplitudes[radar.channelUsed] = radar.amplitude;
    distances[radar.channelUsed] = radar.distanceMillimeters;

    if (radar.channelUsed >= 2) {
      radar.nextChannel();
      radar.startSample();
    }
  }
  // ---------------------------------------

  if (tourne >= 2) {
    obj_detecte = 0;
    tourne = 0;
  } // On reinitialise les variables une fois qu'on a fait la procedure d'evitement d'obstacle

  prio(distances);

  // avoid obstacle
  if (distanceSensor.measureDistanceCm() <= 25 || obj_detecte == 1) {
    obj_detecte = 1;
    
    uint8_t detector = lineSensor.getPositionState();
    if ((detector & 0b1000) > 0) {
      // on detecte une ligne à gauche 
      quart_tour();
      tourne++;
    } else {
      followLine(speed);
    }
  } else {
    followLine(speed);
  }
   
}
