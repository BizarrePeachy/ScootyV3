#include "EspNowHandler.h"
#include "Screen.h"
#include <Arduino.h>
#include "MpuHandler.h"

#define FLEX_TRIGGER 3000
#define FLEX_PIN_1 32
#define FLEX_PIN_2 33

// Buttons
#define blueButtonPin 19
#define redButtonPin 18

// LED Pins (Moved from 34/35 to valid output pins 4/16)
int Flex1Led = 4;
int Flex2Led = 13;

// MPU6050 readings X and Y
float pitch = 0.0;
float roll = 0.0;

// variables for sensor states
bool flex1_status = false;
bool flex2_status = false;
bool blueButtonPressed = false;
bool redButtonPressed = false;
 
void setup() {
  
  // Set up Serial Monitor
  Serial.begin(9600);

  // Start ESP-NOW
  espNowInit();

  pinMode(Flex1Led, OUTPUT);
  pinMode(Flex2Led, OUTPUT);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(redButtonPin, INPUT_PULLUP);


  // Start Screen
  screenInit();

  // Initialize the MPU6050 sensor
  if (!mpuInit()) {
    // If MPU fails, display an error message on the OLED and halt
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("MPU INIT FAIL!");
    display.display();
    while(true);
  }
}

void CheckFlexValues(int flex1_value, int flex2_value) {
  if (flex1_value <= FLEX_TRIGGER) {
    digitalWrite(Flex1Led, LOW);
    flex1_status = false;
  } else {
    digitalWrite(Flex1Led, HIGH);
    flex1_status = true;
  }

  if (flex2_value <= FLEX_TRIGGER) {
    flex2_status = false;
    digitalWrite(Flex2Led, LOW);
  } else {
    digitalWrite(Flex2Led, HIGH);
    flex2_status = true;
  }
}

void checkButtonStates(bool buttonState1, bool buttonState2) {
  if (buttonState1 == LOW) {
    blueButtonPressed = true;
  } else {
    blueButtonPressed = false;
  }

  if (buttonState2 == LOW) {
    redButtonPressed = true;
  } else {
    redButtonPressed = false;
  }

}
 
void loop() {

  int flex1_value = analogRead(FLEX_PIN_1);
  int flex2_value = analogRead(FLEX_PIN_2);
  int blueButtonState = digitalRead(blueButtonPin);
  int redButtonState = digitalRead(redButtonPin);

  // MPU Data
  mpuReadAndCalculate(&pitch, &roll);

  // Process Flex Sensors
  CheckFlexValues(flex1_value, flex2_value);

  // Prepare esp-now packets
  myData.flex1Status = flex1_status;
  myData.flex2Status = flex2_status;
  myData.blueButton = blueButtonPressed;
  myData.redButton = redButtonPressed;
  myData.pitch = pitch;
  myData.roll = roll;

  espNowSend();

  // Update OLED Display
  displayLoop(flex1_status, flex2_status, pitch, roll, packetstatus);

  // 5. Debug Output
  Serial.print("Flex 1 Value: ");
  Serial.print(flex1_value);
  Serial.print(" | Flex 2: ");
  Serial.print(flex2_value);
  Serial.print(" | Pitch/Roll: ");
  Serial.print(pitch, 1);
  Serial.print("/");
  Serial.print(roll, 1);
  Serial.print(" | TX Status: ");
  Serial.println(packetstatus);

  delay(100);
}