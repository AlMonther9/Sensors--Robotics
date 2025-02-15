#include "StateManager.h"

StateManager::StateManager() : currentState(IDLE) {}

void StateManager::setState(RobotState state) {
  currentState = state;
}

RobotState StateManager::getState() {
  return currentState;
}

String StateManager::getStateString() {
  switch (currentState) {
    case IDLE: return "IDLE";
    case MOVING: return "MOVING";
    case SERVO_ACTION: return "SERVO_ACTION";
    default: return "UNKNOWN";
  }
}
