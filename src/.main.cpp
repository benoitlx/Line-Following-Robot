#include <Arduino.h>
#include <MeMegaPi.h>
#include "Motors.h"

#include "MePort.h"
#include "Wire.h"
#include "MeRGBLineFollower.h"

#define MOTOR1_REGULAR_SPEED 54
#define MOTOR2_REGULAR_SPEED 50

#define KP 0.1

MeRGBLineFollower RGBLineFollower(PORT_8, ADDRESS1);

Motors motor1(12, 35, 34); // PORT 1
Motors motor2(8, 36, 37); // PORT 2

void followLine(float speed){
  int decalage = RGBLineFollower.getPositionOffset();
  float localSpeed = speed;
  uint8_t detector = ~RGBLineFollower.getPositionState();

  Serial.print(detector, BIN);
  Serial.print("    ");

if (detector != 0b11110110 && detector != 0b11110100 && detector != 0b11110010){
  // On ralentit dans les virages
    localSpeed = 0.5;
    RGBLineFollower.setKp(0.17);
  // ces paramètres sont bons pour les virages
}

  Serial.print("dec: ");
  Serial.print(decalage);
  Serial.print("      ");
  Serial.print("speed: ");
  Serial.println(localSpeed);

  motor1.setMotorSpeed(-((int)(localSpeed*MOTOR1_REGULAR_SPEED)-decalage));
  motor2.setMotorSpeed((int)(localSpeed*MOTOR2_REGULAR_SPEED)+decalage);
    
  RGBLineFollower.setKp(KP);
}


void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  for (int i=0; i<4; i++) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }

  Serial.println(F("La led blue devrait avoir clignote 4 fois"));


  // RGB Line FOllower
  RGBLineFollower.begin();
  RGBLineFollower.setKp(KP);
  RGBLineFollower.setRGBColour(1);
  delay(100);
  RGBLineFollower.setRGBColour(2);
  delay(100);
  RGBLineFollower.setRGBColour(3);
  delay(100);
}

void loop(){
  RGBLineFollower.loop();

  followLine(2);
}
