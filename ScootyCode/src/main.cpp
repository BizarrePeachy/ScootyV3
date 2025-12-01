#include "MotorControl.h"
#include "EspHandler.h"
#include <Arduino.h>

// variables
#define LED_PIN 5 // Status light diode on top of robot

void setup() {
    Serial.begin(115200);
    Serial.println("ScootyV3");

    pinMode(LED_PIN, OUTPUT);
    espNowInit();

    MotorInit(); // Initialize motor control

    esp_now_register_recv_cb(OnDataRecv); // Register callback function for receiving data from esp-now
}

void loop() {
    processMotorControl(myData); // Takes in data coming in from esp-now and processes it through motor control functions
}
