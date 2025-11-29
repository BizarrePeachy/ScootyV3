#ifndef MPUHANDLER_H
#define MPUHANDLER_H

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define MPU_SDA 21
#define MPU_SCL 22

extern Adafruit_MPU6050 mpu;

bool mpuInit();
void mpuReadAndCalculate(float* pitch, float* roll);

#endif 