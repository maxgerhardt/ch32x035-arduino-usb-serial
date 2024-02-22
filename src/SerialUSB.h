#pragma once
#include <Arduino.h>

class SerialUSBBase : public Stream {
public:
    void begin(int baud);
    int available() { return 0; }
    int read() { return -1; }
    int peek() { return -1; }
    size_t readBytes(char *buffer, size_t length) {
        (void) buffer;
        (void) length;
        return 0;
    }
    size_t write(const uint8_t *buffer, size_t size);
    size_t write(uint8_t data) {return this->write(&data, sizeof(data)); } 
    void flush() {}
    void maintain();
};

extern SerialUSBBase SerialUSB;