#include "EspNowHandler.h"
#include <Arduino.h>

// Mac Address
uint8_t broadcastAddress[] = {0x78, 0x1C, 0x3C, 0xB7, 0xA3, 0xE4};
const char* packetstatus = "INIT";

struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success | " : "Delivery Fail | ");

  if (status == ESP_NOW_SEND_SUCCESS) {
    packetstatus = "SENT";
  } else {
    packetstatus = "FAILED";
  }
}

void espNowInit() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent);

    // Register Peer
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add Peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
    Serial.println("ESP-NOW Initialized and Peer Added.");
}

void espNowSend() {
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  
  if (result == ESP_OK) {
    // Serial.println("Sending confirmed");
    // Note: The actual 'packetstatus' update happens in the OnDataSent callback,
    // which fires asynchronously.
  }
  else {
    // This is for local failure to even put the packet into the queue
    packetstatus = "ERROR"; 
    Serial.println("Sending error: Could not queue packet.");
  }
}