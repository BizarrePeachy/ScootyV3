#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "EspHandler.h"

#define DEFAULT_SPEED 200
#define TURN_ADJUST 100

const float MAX_STEERING_ROLL_ANGLE = 25.0f;

const int MOTOR_1_IN1 = 33;   // L298N_1 IN1 for Motor 1 direction
const int MOTOR_1_IN2 = 32;   // L298N_1 IN2 for Motor 1 direction
const int MOTOR_1_ENABLE = 13; // L298N_1 ENA for Motor 1 speed (PWM pin)

const int MOTOR_2_IN3 = 27;   // L298N_1 IN3 for Motor 2 direction
const int MOTOR_2_IN4 = 26;   // L298N_1 IN4 for Motor 2 direction
const int MOTOR_2_ENABLE = 14; // L298N_1 ENB for Motor 2 speed (PWM pin)

// Module 2 (Motor 3 & Motor 4)
const int MOTOR_3_IN1 = 25;   // L298N_2 IN1 for Motor 3 direction
const int MOTOR_3_IN2 = 23;   // L298N_2 IN2 for Motor 3 direction
const int MOTOR_3_ENABLE = 18; // L298N_2 ENA for Motor 3 speed (PWM pin)

const int MOTOR_4_IN3 = 22;   // L298N_2 IN3 for Motor 4 direction (Example pin)
const int MOTOR_4_IN4 = 21;   // L298N_2 IN4 for Motor 4 direction (Example pin)
const int MOTOR_4_ENABLE = 19; // L298N_2 ENB for Motor 4 speed (PWM pin)

// PWM Settings for ESP32
// ESP32 has 16 independent PWM channels (0-15).
// Assign a unique channel to each motor's enable pin.
const int PWM_FREQ = 5000;    // PWM frequency in Hz (e.g., 5000 Hz)
const int PWM_RESOLUTION = 8; // PWM resolution in bits (8-bit = 0-255 values)

const int PWM_CHANNEL_1 = 0;  // PWM channel for Motor 1
const int PWM_CHANNEL_2 = 1;  // PWM channel for Motor 2
const int PWM_CHANNEL_3 = 2;  // PWM channel for Motor 3
const int PWM_CHANNEL_4 = 3;  // PWM channel for Motor 4


// Fuctions
void setMotor1(int dir1, int dir2, int speed);
void setMotor2(int dir1, int dir2, int speed);
void setMotor3(int dir1, int dir2, int speed);
void setMotor4(int dir1, int dir2, int speed);
void MotorInit();
void stopAllMotors();
void processMotorControl(const struct_message& data);

#endif