#include "Automata.h"
#include "Arduino.h"

void automataInit(){
  current_state = WaitPush;
}

enum states getCurrentSate(){
  return current_state;
}

void updateState(int event){
  current_state = automata[event][current_state];
}
