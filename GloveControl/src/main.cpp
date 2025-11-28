#include <esp_now.h>
#include <WiFi.h>

#define FLEX_TRIGGER 3000
#define FLEX_PIN_1 32
#define FLEX_PIN_2 33

// LED Pins (Moved from 34/35 to valid output pins 4/16)
int Flex1Led = 4;
int Flex2Led = 13;

// Variables for test data
bool flex1 = false;
bool flex2 = false;

// Mac Address
uint8_t broadcastAddress[] = {0x6C, 0xC8, 0x40, 0x4D, 0xC4, 0xAC};

// Define a data structure
typedef struct struct_message {
  bool flex1Status;
  bool flex2Status;
} struct_message;
 
// Create a structured object
struct_message myData;
 
// Peer info
esp_now_peer_info_t peerInfo;
 
// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success | " : "Delivery Fail | ");
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
 
  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(Flex1Led, OUTPUT);
  pinMode(Flex2Led, OUTPUT);
}

void CheckFlexValues(int flex1_value, int flex2_value) {
  if (flex1_value <= FLEX_TRIGGER) {
    digitalWrite(Flex1Led, LOW);
    flex1 = false;
  } else {
    digitalWrite(Flex1Led, HIGH);
    flex1 = true;
  }

  if (flex2_value <= FLEX_TRIGGER) {
    flex2 = false;
    digitalWrite(Flex2Led, LOW);
  } else {
    digitalWrite(Flex2Led, HIGH);
    flex2 = true;
  }
}
 
void loop() {

  int flex1_value = analogRead(FLEX_PIN_1);
  int flex2_value = analogRead(FLEX_PIN_2);

  Serial.print(" | Flex 2 Value ");
  Serial.print(flex2_value);
  Serial.print(" | Flex 1 Value ");
  Serial.print(flex1_value);
  Serial.print(" | ");

  // Data Getting Send
  myData.flex1Status = flex1_value;
  myData.flex2Status = flex2_value;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(100);
}