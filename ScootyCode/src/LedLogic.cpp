#include "LedLogic.h"

void LED_OFF() {
    digitalWrite(LED_PIN, LOW);
}

void LED_ON() {
    digitalWrite(LED_PIN, HIGH);
}

void LED_BLINK(int delayTime) {
    digitalWrite(LED_PIN, HIGH);
    delay(delayTime);
    digitalWrite(LED_PIN, LOW);
    delay(delayTime);
}