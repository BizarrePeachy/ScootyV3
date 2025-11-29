#include "MpuHandler.h"

Adafruit_MPU6050 mpu;

bool mpuInit() {
    Wire.begin(MPU_SDA, MPU_SCL);
    Serial.print("Attempting to find MPU6050...");
    if (!mpu.begin()) {
        Serial.println("Failed! Check wiring or I2C address");
        return false;
    }
    Serial.println("Success.");

    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    
    return true;
}

void mpuReadAndCalculate(float* pitch, float* roll) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Simplified Pitch and Roll Calculation (Accelerometer-only)
  // This uses the ATAN2 function to find the angle relative to gravity (the z-axis).
  
  // Roll (rotation around X-axis, depends on Y and Z acceleration)
  *roll = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / PI;

  // Pitch (rotation around Y-axis, depends on X and Z acceleration)
  // Note: We use -a.acceleration.x because positive pitch should usually be nose-up.
  *pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / PI;
}