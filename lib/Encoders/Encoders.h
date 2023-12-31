#ifndef ENCODERS_H_
#define ENCODERS_H_

#include <Arduino.h>

// PIN utilisées pour l'encodeur incrémental
#define PORT1_NE1 31
#define PORT1_NE2 18

#define PORT2_NE1 38
#define PORT2_NE2 19

void initEncoders(); // setup encoder position detection

int getPosition1(); // get the actual position of the incremental encoder in pulse.
int getPosition2(); // get the actual position of the incremental encoder in pulse.

float getVelocity1();
float getVelocity2();

#endif // !ENCODERS_H_
