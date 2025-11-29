#ifndef ESP_NOW_H
#define ESP_NOW_H
#include <esp_now.h>
#include <WiFi.h>

// Define a data structure
typedef struct struct_message {
  bool flex1Status;
  bool flex2Status;
  float pitch;
  float roll;
} struct_message;

// Create a structured object
extern struct_message myData;

// Packet Status
extern const char* packetstatus;

void espNowInit();
void espNowSend();

#endif 