#include <esp_now.h>
#include <WiFi.h>
 
// Define a data structure
typedef struct struct_message {
  bool flex1Status;
  bool flex2Status;
} struct_message;
 
// Create a structured object
struct_message myData;
 
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Data received: ");
  Serial.println(len);
  Serial.print("Flex 1 Value: ");
  Serial.println(myData.flex1Status);
  Serial.print("Flex 2 Value: ");
  Serial.println(myData.flex2Status);
  Serial.println();
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(9600);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
}