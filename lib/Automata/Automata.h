#ifndef AUTOMATA_H
#define AUTOMATA_H

#define N_STATE 5
#define N_TRANS 6


enum Event{ButtonPush, ObstacleDetected, ObstacleAvoided, RobotRight, RobotLeft, EndEvent}; // Transition of the automata

enum states{Follow, Avoid, Stop, WaitPush, End};
extern enum states current_state;

extern enum states automata[N_TRANS][N_STATE] = {
  // Follow, Avoid, Stop, WaitPush, End
  {Follow, Avoid, Stop, Follow, End},
  {Avoid, Avoid, Stop, WaitPush, End},
  {Follow, Follow, Stop, WaitPush, End},
  {Stop, Avoid, Stop, WaitPush, End},
  {Follow, Avoid, Follow, WaitPush, End},
  {End, Avoid, Stop, WaitPush, End}
};



void automataInit();
enum states getCurrentState();
void updateState(Event event);

#endif // !AUTOMATA_H

