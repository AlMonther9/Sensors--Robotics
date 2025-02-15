#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

class MotorControl {
public:
  MotorControl(uint8_t motor1A, uint8_t motor1B,
               uint8_t motor2A, uint8_t motor2B,
               uint8_t motor3A, uint8_t motor3B,
               uint8_t motor4A, uint8_t motor4B);
  void init();
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stopMotors();
  
private:
  uint8_t _motor1A, _motor1B;
  uint8_t _motor2A, _motor2B;
  uint8_t _motor3A, _motor3B;
  uint8_t _motor4A, _motor4B;
};

#endif
