#include "Automata.h"

void automataInit(){
  current_state = WaitPush;
}

states_t getCurrentState(){
  return current_state;
}

void updateState(event_t event){
  states_t state = automata[event][current_state];
  if (state != current_state) {
    current_state = state;
#ifdef DEBUG 
    // TODO: Add a sound with a buzzer
#endif // DEBUG
  }
}
