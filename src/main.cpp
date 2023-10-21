#include <Arduino.h>
#include <MeMegaPi.h>
#include "Motors.h"

#include "MePort.h"
#include "Wire.h"
#include "MeRGBLineFollower.h"

#define MOTOR1_REGULAR_SPEED 53
#define MOTOR2_REGULAR_SPEED 50

#define KP 0.1 // 0.13
#define KD 0.09 
#define KI 0
#define SPEED_REDUCTION_FACTOR 6 // slower will reduce the forward speed when the Robot is experiencing steep turn

MeRGBLineFollower RGBLineFollower(PORT_8, ADDRESS1);

Motors motor1(12, 35, 34); // PORT 1
Motors motor2(8, 36, 37); // PORT 2

int p_correction;
int i_correction;
int d_correction;
int last_p_correction = 0;

void followLine(float speed){
  p_correction = RGBLineFollower.getPositionOffset();
  i_correction += p_correction;
  d_correction = p_correction - last_p_correction;
  last_p_correction = p_correction;
  
  int decalage = p_correction + KI * i_correction + KD * d_correction;
  int8_t decalage_avant = digitalRead(A10) + digitalRead(A11);

  float corrected_speed = speed / (1+decalage_avant);
  // float corrected_speed = speed * 0.33;

  // Cette partie est à refaire en utilisant un capteur fixée à l'avant du robot pour anticiper les virages
  // float corrected_speed;
  // if (p_correction != 0)
  //  corrected_speed = speed * SPEED_REDUCTION_FACTOR / (abs(p_correction) * (1+decalage_avant));
  // else
  //  corrected_speed = speed / (1+decalage_avant);



  int speed1 = -((int)(corrected_speed*MOTOR1_REGULAR_SPEED)-decalage);
  int speed2 = (int)(corrected_speed*MOTOR2_REGULAR_SPEED)+decalage;

  Serial.print("speed1: ");
  Serial.print(-speed1);
  Serial.print("   dec: ");
  Serial.print(decalage);
  Serial.print("   cor_speed: ");
  Serial.print(corrected_speed);
  Serial.print("   dec_avant: ");
  Serial.print(decalage_avant);
  Serial.print("   speed2: ");
  Serial.println(speed2);

  motor1.setMotorSpeed(speed1);
  motor2.setMotorSpeed(speed2);
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

  // RGB Line Follower
  RGBLineFollower.begin();
  RGBLineFollower.setKp(KP);
  for (int i=1; i<=3; i++) {
    RGBLineFollower.setRGBColour(i);
    delay(100);
  }
}

void loop(){
  RGBLineFollower.loop();

  followLine(3); // 1.4
}
