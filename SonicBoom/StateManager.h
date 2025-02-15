#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <Arduino.h>

enum RobotState {
  IDLE,
  MOVING,
  SERVO_ACTION
};

class StateManager {
public:
  StateManager();
  void setState(RobotState state);
  RobotState getState();
  String getStateString();
  
private:
  RobotState currentState;
};

#endif
