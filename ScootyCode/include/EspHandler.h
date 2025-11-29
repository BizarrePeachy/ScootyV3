#ifndef ESPHANDLER_H
#define ESPHANDLER_H

#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>

typedef struct struct_message {
    bool flex1Status;
    bool flex2Status;
    float pitch;
    float roll;
} struct_message;

extern struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
void espNowInit();


#endif