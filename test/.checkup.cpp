#include <Arduino.h>
#include <MeMegaPi.h>

#include "Wire.h"
#include "MeRGBLineFollower.h"

MeRGBLineFollower RGBLineFollower(PORT8, ADDRESS1);

void setup(){
  pinMode(13, OUTPUT);
  Serial.begin(9600);

  for (int i=0; i<4; i++) {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }

  Serial.println("La led blue devrait avoir clignote 4 fois");
}

void loop(){
  int16_t position = RGBLineFollower.getPositionOffset();
}
