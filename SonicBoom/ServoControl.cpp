#include "ServoControl.h"

ServoControl::ServoControl(uint8_t servoPin) : _servoPin(servoPin) {}

void ServoControl::init() {
  _servo.attach(_servoPin);
  _servo.write(0); // Initialize in release position
}

void ServoControl::triggerAction() {
  _servo.write(90);
  delay(500);
  _servo.write(0);
}

void ServoControl::holdCube() {
  _servo.write(90); // Adjust to your desired "hold" angle
}

void ServoControl::releaseCube() {
  _servo.write(0); // Adjust to your desired "release" angle
}
