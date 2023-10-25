#include "Automata.h"
#include "Arduino.h"

void automataInit(){
  current_state = WaitPush;
}

enum states getCurrentSate(){
  return current_state;
}

void updateState(int event){
  enum states state = automata[event][current_state];
  if (state != current_state) {
    current_state = state;
#ifdef DEBUG 
    // TODO: Add a sound with a buzzer
#endif // DEBUG
  }
}
