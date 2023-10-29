#include <Arduino.h>
#include "MeRGBLineFollower.h"
#include "Motors.h"

#include "Automata.h"
states_t current_state;

#define DEBUG 1

void waitPush(); // wait until a button is pressed
void follow(float speed); // default state of the automata: follow line at a given speed
void avoid(); // Avoid obstacle
void stop(); // Stop the robot to mark the priority
void end(); // Ending function


void setup(){
  automataInit(); 

  // attach interrupt for radar (update event)
  // attach interrupt for ultrasonic sensor (update event)
}

void loop(){

  // Update as frequently as possible data given by RGB sensor in order to have good response time for the PID

  // Update Robot position with the encoder

  // Adjust the speed according to the position of the robot 

  switch (getCurrentState()) {
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
