#ifndef AUTOMATA_H_
#define AUTOMATA_H_

#include <Arduino.h>

#define DEBUG 1

// TODO: commit debug mode

#define N_STATE 5
#define N_TRANS 6


enum event{ButtonPush, ObstacleDetected, ObstacleAvoided, RobotRight, RobotLeft, EndEvent}; // Transition of the automata
typedef enum event event_t ;

enum states{Follow, Avoid, Stop, WaitPush, End};
typedef enum states states_t;
extern states_t current_state;

const states_t automata[N_TRANS][N_STATE] = {
  // Follow, Avoid, Stop, WaitPush, End
  {Follow, Avoid, Stop, Follow, End},
  {Avoid, Avoid, Stop, WaitPush, End},
  {Follow, Follow, Stop, WaitPush, End},
  {Stop, Avoid, Stop, WaitPush, End},
  {Follow, Avoid, Follow, WaitPush, End},
  {End, Avoid, Stop, WaitPush, End}
};



void automataInit();
states_t getCurrentState();
void updateState(event event);

#endif // !AUTOMATA_H_

