#include <Arduino.h>
//#include "MeRGBLineFollower.h"
#include "Motors.h"
#include "Encoders.h"

#include "Automata.h"
states_t current_state;

#define DEBUG 1

void waitPush(); // wait until a button is pressed
void follow(float speed); // default state of the automata: follow line at a given speed
void avoid(); // Avoid obstacle
void stop(); // Stop the robot to mark the priority
void end(); // Ending function


long prevT = 0;
int posPrev1 = 0;
int posPrev2 = 0;



void setup(){
  automataInit(); 
  initEncoders();

  Serial.begin(9600);

  delay(10);

  // attach interrupt for radar (update event)
  // attach interrupt for ultrasonic sensor (update event)
}

void loop(){

  /* Update the speed */
  long currT = micros();
  float deltaT = ((float)(currT - prevT)/1.0e6);
  int pos_1 = getPosition1();
  float velo_1 = ((float)(pos_1 - posPrev1)/deltaT);
  int pos_2 = getPosition1();
  float velo_2 = ((float)(pos_2 - posPrev2)/deltaT);
  prevT = currT;
  posPrev2 = pos_2;
  posPrev1 = pos_1;

  velo_1 = (abs(velo_1) < 0.5) ? velo_1 : getVelocity1();
  velo_2 = (abs(velo_2) < 0.5) ? velo_2 : getVelocity2();




  // Update as frequently as possible data given by RGB sensor in order to have good response time for the PID

  // Update Robot position with the encoder

  // Adjust the speed according to the position of the robot 

  // à remplacer par getCurrentState()
  switch (Follow) {
    case WaitPush:
      waitPush();
      break;
    case Follow:
      follow(0.5);
      break;
    case Avoid:
      avoid();
      break;
    case Stop:
      stop();
      break;
    case End:
      end();
      break;
  }
   Serial.print(velo_1);
   Serial.print("\n");
}


// Follow Line =====================================================
void follow(float speed){
  // TODO: Create a PID controller independent on each motors (so that the robot can follow a straight line)
}
// End Follow Line =================================================


// Avoid Obstacle ==================================================
void avoid(){
  // TODO
}
// End Avoid Obstacle ==============================================


// Stop ============================================================
void stop(){
  // TODO
}
// End Stop ========================================================

// End =============================================================
void end(){
  // TODO
}
// End End =========================================================

// WaitPush ========================================================
void waitPush(){
  // TODO
}
// End WaitPush ====================================================
