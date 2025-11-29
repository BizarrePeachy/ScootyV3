#include "EspHandler.h"

struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  // Copy the incoming data into the local structure
  memcpy(&myData, incomingData, sizeof(myData));

  // Value printing (for debugging)
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("Flex 1 Value: ");
  Serial.println(myData.flex1Status);
  Serial.print("Pitch Value: ");
  Serial.println(myData.pitch);
  Serial.println();

  // Control the servo based on the received flex status
  if (myData.flex1Status == true) {
    Serial.println("Finger Flexed");
  }
}

void espNowInit() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv);
}