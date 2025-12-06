#include <Arduino.h>

#ifndef LEDLOGIC_H
#define LEDLOGIC_H

#define LED_PIN 5 // Status light diode on top of robot

// Functions
void LED_OFF();
void LED_ON();
void LED_BLINK(int delayTime);


#endif