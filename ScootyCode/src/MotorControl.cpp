#include "MotorControl.h"

void MotorInit() {
  // --- Configure Motor Driver Pins ---
  pinMode(MOTOR_1_IN1, OUTPUT);
  pinMode(MOTOR_1_IN2, OUTPUT);
  pinMode(MOTOR_2_IN3, OUTPUT);
  pinMode(MOTOR_2_IN4, OUTPUT);
  pinMode(MOTOR_3_IN1, OUTPUT);
  pinMode(MOTOR_3_IN2, OUTPUT);
  pinMode(MOTOR_4_IN3, OUTPUT);
  pinMode(MOTOR_4_IN4, OUTPUT);

  // --- Configure ESP32 PWM Channels ---
  ledcSetup(PWM_CHANNEL_1, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(MOTOR_1_ENABLE, PWM_CHANNEL_1);

  ledcSetup(PWM_CHANNEL_2, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(MOTOR_2_ENABLE, PWM_CHANNEL_2);

  ledcSetup(PWM_CHANNEL_3, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(MOTOR_3_ENABLE, PWM_CHANNEL_3);

  ledcSetup(PWM_CHANNEL_4, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(MOTOR_4_ENABLE, PWM_CHANNEL_4);

  stopAllMotors(); // Ensure all motors are stopped when the robot starts.

  delay(100);
}

// --- Motor Control Functions (Definitions) ---
void setMotor1(int dir1, int dir2, int speed) {
  // If left side is going backwards, swap dir1 and dir2 here
  digitalWrite(MOTOR_1_IN1, dir2); // Swapped
  digitalWrite(MOTOR_1_IN2, dir1); // Swapped
  ledcWrite(PWM_CHANNEL_1, speed);  
}

void setMotor2(int dir1, int dir2, int speed) {
  // If left side is going backwards, swap dir1 and dir2 here
  digitalWrite(MOTOR_2_IN3, dir2); // Swapped
  digitalWrite(MOTOR_2_IN4, dir1); // Swapped
  ledcWrite(PWM_CHANNEL_2, speed);
}

void setMotor3(int dir1, int dir2, int speed) {
  digitalWrite(MOTOR_3_IN1, dir1);
  digitalWrite(MOTOR_3_IN2, dir2);
  ledcWrite(PWM_CHANNEL_3, speed);
}

void setMotor4(int dir1, int dir2, int speed) {
  digitalWrite(MOTOR_4_IN3, dir1);
  digitalWrite(MOTOR_4_IN4, dir2);
  ledcWrite(PWM_CHANNEL_4, speed);
}

void stopAllMotors() {
  setMotor1(LOW, LOW, 0);
  setMotor2(LOW, LOW, 0);
  setMotor3(LOW, LOW, 0);
  setMotor4(LOW, LOW, 0);
}

void processMotorControl(const struct_message& data) {
    int masterSpeed = 0;
    int steerAmount = 0;

    if (data.flex1Status == true && data.flex2Status == false) {
        masterSpeed = DEFAULT_SPEED;
    } else if (data.flex2Status == true && data.flex1Status == false) {
        masterSpeed = -DEFAULT_SPEED;
    }

    if (data.flex1Status == true || data.flex2Status == true) {
        steerAmount = map(data.roll, -MAX_STEERING_ROLL_ANGLE, MAX_STEERING_ROLL_ANGLE, -255, 255);
        
        steerAmount = constrain(steerAmount, -255, 255);
    } else {
        steerAmount = 0;
    }

    int leftMotorSpeed = masterSpeed - steerAmount;
    int rightMotorSpeed = masterSpeed + steerAmount;

    int absLeftSpeed = abs(leftMotorSpeed);
    int absRightSpeed = abs(rightMotorSpeed);

      // Left Side Motors (1 and 2)
  if (leftMotorSpeed > 0) { // Forward
    setMotor1(HIGH, LOW, absLeftSpeed);
    setMotor2(HIGH, LOW, absLeftSpeed);
  } else if (leftMotorSpeed < 0) { // Backward
    setMotor1(LOW, HIGH, absLeftSpeed);
    setMotor2(LOW, HIGH, absLeftSpeed);
  } else { // Stop
    setMotor1(LOW, LOW, 0);
    setMotor2(LOW, LOW, 0);
  }

  // Right Side Motors (3 and 4)
  if (rightMotorSpeed > 0) { // Forward
    setMotor3(HIGH, LOW, absRightSpeed);
    setMotor4(HIGH, LOW, absRightSpeed);
  } else if (rightMotorSpeed < 0) { // Backward
    setMotor3(LOW, HIGH, absRightSpeed);
    setMotor4(LOW, HIGH, absRightSpeed);
  } else { // Stop
    setMotor3(LOW, LOW, 0);
    setMotor4(LOW, LOW, 0);
  }
}