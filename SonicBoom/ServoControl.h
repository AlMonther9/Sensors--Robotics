#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Arduino.h>
#include <ESP32Servo.h>

class ServoControl {
public:
  ServoControl(uint8_t servoPin);
  void init();
  void triggerAction();  // Optional swing action
  void holdCube();       // Set servo to hold position
  void releaseCube();    // Set servo to release position
  
private:
  uint8_t _servoPin;
  Servo _servo;
};

#endif
