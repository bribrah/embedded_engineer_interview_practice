#pragma once

#include <stdint.h>
#include <thread>
#include <iostream>
#include <vector>

#include "DebugLogger.h"

class SoftwareUART
{
public:
    bool simulatedInputBuf[10];
    char simulatedInputStrBuf[100];

    SoftwareUART(uint32_t baudRate, LOGLEVEL logLevel);
    void sendByte(uint8_t byte);

    uint8_t receiveByte(int &status);
    std::string recieveUntil(char delim, int &status);

    void setSimulatedInputBuffer(uint8_t byte);
    void setSimuatedInputString(std::string str);

private:
    uint32_t baudRate;
    double waitTime;

    size_t inputBufPointer = 0;
    size_t inputStrPointer = 0;
    DebugLogger log;

    void outputBit(bool bit);
    bool inputBit();
    void simulateBitDelay();
};