#include "MotorControl.h"
#include "EspHandler.h"
#include <Arduino.h>

// variables
#define LED_PIN 5

void setup() {
    Serial.begin(115200);
    Serial.println("ScootyV3");

    pinMode(LED_PIN, OUTPUT);
    espNowInit();

    MotorInit();

    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    processMotorControl(myData);
}