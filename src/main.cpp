#include <Arduino.h>
#include <SerialUSB.h>

#define LED PB1

static unsigned long lastTime = 0;
static uint8_t led = 0;

void setup() {
    pinMode(LED, OUTPUT);
    SerialUSB.begin(115200);
}

void loop() {
    if (millis() - lastTime >= 1000) {        
        led ^= 1;
        digitalWrite(LED, led);
        lastTime = millis();
        SerialUSB.println("Hello from USB!");
    }
    SerialUSB.maintain(); // hack for now, must be called as fast as possible
    // otherwise we're missing the 30us CDC packets that *we* must send 
}