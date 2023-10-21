#include "Motors.h"
#include "Arduino.h"

Motors::Motors(int pinSpeed, int pin1, int pin2){
  speedPin = pinSpeed;
  dir1Pin = pin1;
  dir2Pin = pin2;

  pinMode(speedPin, OUTPUT);
  pinMode(dir1Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
}

void Motors::setMotorSpeed(int speed){
  // La direction du moteur est initie par un pont en H
  digitalWrite(dir1Pin, (speed >= 0));
  digitalWrite(dir2Pin, (speed <= 0));

  analogWrite(speedPin, constrain(abs(speed), 0, MAXPWM));
}
