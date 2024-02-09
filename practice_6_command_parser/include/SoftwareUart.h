#pragma once

#include <stdint.h>
#include <thread>
#include <iostream>

class SoftwareUART
{
public:
    bool simulatedInputBuf[10];

    SoftwareUART(uint32_t baudRate);
    void sendByte(uint8_t byte);
    uint8_t receiveByte(int &status);
    void setSimulatedInputBuffer(uint8_t byte);

private:
    uint32_t baudRate;
    double waitTime;
    size_t inputBufPointer = 0;

    void outputBit(bool bit);
    bool inputBit();
    void simulateBitDelay();
};