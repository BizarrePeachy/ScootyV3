#include <esp_now.h>
#include <WiFi.h>
#include <Arduino.h>
#include <ESP32Servo.h>

// --- Configuration ---
// Define a data structure that must match the sender's structure
typedef struct struct_message {
  bool flex1Status;
  bool flex2Status;
  float pitch;
  float roll;
} struct_message;

// Pin variables
#define LED_PIN 13
#define MOTOR_PIN 33 // Use GPIO 33 for the servo signal pin (Good PWM pin)

// Create a structured object to hold received data
struct_message myData;

// Servo object initialization
Servo myServo;

// Callback function executed when data is received
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
    // Write 180 degrees (e.g., servo fully extended)
    myServo.write(180);
    digitalWrite(LED_PIN, HIGH);
    // Removed delay(15) as delays are bad practice in callbacks
  } else {
    // Write 0 degrees (e.g., servo home position)
    myServo.write(0);
    digitalWrite(LED_PIN, LOW);
  }
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(9600);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  pinMode(LED_PIN, OUTPUT);

  // --- FIX 1: ATTACH THE SERVO TO THE PIN ---
  // The attach() function connects the servo object to the GPIO pin.
  // We use the defined MOTOR_PIN (GPIO 33)
  myServo.attach(MOTOR_PIN);
  
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
  
  Serial.println("ESP32 ESP-NOW Receiver with Servo Control Initialized.");
}

void loop() {
  // The logic is handled entirely by the ESP-NOW callback, so loop remains empty.
}