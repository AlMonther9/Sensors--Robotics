#include "MotorControl.h"

MotorControl::MotorControl(uint8_t motor1A, uint8_t motor1B,
                           uint8_t motor2A, uint8_t motor2B,
                           uint8_t motor3A, uint8_t motor3B,
                           uint8_t motor4A, uint8_t motor4B)
  : _motor1A(motor1A), _motor1B(motor1B),
    _motor2A(motor2A), _motor2B(motor2B),
    _motor3A(motor3A), _motor3B(motor3B),
    _motor4A(motor4A), _motor4B(motor4B) {}

void MotorControl::init() {
  pinMode(_motor1A, OUTPUT);
  pinMode(_motor1B, OUTPUT);
  pinMode(_motor2A, OUTPUT);
  pinMode(_motor2B, OUTPUT);
  pinMode(_motor3A, OUTPUT);
  pinMode(_motor3B, OUTPUT);
  pinMode(_motor4A, OUTPUT);
  pinMode(_motor4B, OUTPUT);
}

void MotorControl::moveForward() {
  digitalWrite(_motor1A, HIGH);
  digitalWrite(_motor1B, LOW);
  digitalWrite(_motor2A, HIGH);
  digitalWrite(_motor2B, LOW);
  digitalWrite(_motor3A, HIGH);
  digitalWrite(_motor3B, LOW);
  digitalWrite(_motor4A, HIGH);
  digitalWrite(_motor4B, LOW);
}

void MotorControl::moveBackward() {
  digitalWrite(_motor1A, LOW);
  digitalWrite(_motor1B, HIGH);
  digitalWrite(_motor2A, LOW);
  digitalWrite(_motor2B, HIGH);
  digitalWrite(_motor3A, LOW);
  digitalWrite(_motor3B, HIGH);
  digitalWrite(_motor4A, LOW);
  digitalWrite(_motor4B, HIGH);
}

void MotorControl::turnLeft() {
  // Left side motors go backward; right side motors go forward.
  digitalWrite(_motor1A, LOW);
  digitalWrite(_motor1B, HIGH);
  digitalWrite(_motor3A, LOW);
  digitalWrite(_motor3B, HIGH);
  digitalWrite(_motor2A, HIGH);
  digitalWrite(_motor2B, LOW);
  digitalWrite(_motor4A, HIGH);
  digitalWrite(_motor4B, LOW);
}

void MotorControl::turnRight() {
  // Left side motors go forward; right side motors go backward.
  digitalWrite(_motor1A, HIGH);
  digitalWrite(_motor1B, LOW);
  digitalWrite(_motor3A, HIGH);
  digitalWrite(_motor3B, LOW);
  digitalWrite(_motor2A, LOW);
  digitalWrite(_motor2B, HIGH);
  digitalWrite(_motor4A, LOW);
  digitalWrite(_motor4B, HIGH);
}

void MotorControl::stopMotors() {
  digitalWrite(_motor1A, LOW);
  digitalWrite(_motor1B, LOW);
  digitalWrite(_motor2A, LOW);
  digitalWrite(_motor2B, LOW);
  digitalWrite(_motor3A, LOW);
  digitalWrite(_motor3B, LOW);
  digitalWrite(_motor4A, LOW);
  digitalWrite(_motor4B, LOW);
}
