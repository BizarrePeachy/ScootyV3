#include "Screen.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGH, &Wire, OLED_RESET);

void screenInit() {
    Wire.begin(SCREEN_SDA, SCREEN_SCL);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed. Check wiring and address."));
        // Don't proceed if the display fails to initialize
        for (;;); 
    }

    // Display basic setup information
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("OLED Init Success!"));
    display.display(); // Commit the buffer to the actual display
    
    // Add a small delay so the message is visible on startup
    delay(1000); 
}

/**
 * @brief Main loop function for updating the display content.
 * * This function should be called repeatedly in the Arduino loop() function.
 * It demonstrates how to clear the screen, set text properties, draw, 
 * and display a running counter based on milliseconds.
 */
void displayLoop(bool flex1, bool flex2, float pitch, float roll, const char* packetStatus) {
    // 1. Clear the buffer from previous content
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);

    // --- ROW 1: HEADER ---
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(F("SCOOTY V3 STATUS"));
    
    // --- ROW 2 & 3: FLEX SENSORS (Two lines per sensor for clarity) ---
    
    // Flex Sensor 1 Label
    display.setCursor(0, 10);
    display.setTextSize(1);
    display.print(F("FLEX 1:"));
    
    // Flex Sensor 1 Status (Size 2 for prominence)
    display.setCursor(0, 20);
    display.setTextSize(2);
    display.print(flex1 ? F("BENT") : F("OPEN"));

    // Flex Sensor 2 Label
    display.setCursor(64, 10);
    display.setTextSize(1);
    display.print(F("FLEX 2:"));
    
    // Flex Sensor 2 Status (Size 2 for prominence)
    display.setCursor(64, 20);
    display.setTextSize(2);
    display.print(flex2 ? F("BENT") : F("OPEN"));

    // --- ROW 4: MPU6050 READINGS (Compact) ---
    display.setTextSize(1);
    display.setCursor(0, 40); // Moved down from 30
    display.print(F("MPU: "));
    
    // Pitch
    display.print(F("P:"));
    display.print(pitch, 1); // 1 decimal place
    
    // Separator
    display.print(F(" | "));

    // Roll
    display.print(F("R:"));
    display.print(roll, 1); // 1 decimal place


    // --- ROW 5 & 6: ESP-NOW STATUS ---
    display.setCursor(0, 50);
    display.println(F("-----------------"));
    
    display.setCursor(0, 58); // Last line
    display.print(F("TX Status: "));
    // Status text (SENT, FAIL, etc.)
    display.print(packetStatus);

    // 4. Update the actual display hardware
    display.display();

    // Small delay for smooth updates
    delay(10); 
}