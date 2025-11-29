#ifndef SCREEN_H
#define SCREEN_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Oled display parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGH 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

#define SCREEN_SDA 21
#define SCREEN_SCL 22

extern Adafruit_SSD1306 display;

void screenInit();
void displayLoop(bool flex1, bool flex2, float pitch, float roll, const char* packetStatus);

#endif