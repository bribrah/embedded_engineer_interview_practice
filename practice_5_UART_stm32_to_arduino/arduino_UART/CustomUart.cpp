/*
 * CustomUart.cpp
 *
 *  Created on: Feb 7, 2024
 *      Author: bespinosa
 */

#include "./CustomUart.h"

#define INPUT_PIN 10
#define OUTPUT_PIN 11

CustomUart::CustomUart(uint32_t baudRate)
{
    pinMode(OUTPUT_PIN, OUTPUT);

    outputBit(1);
    pinMode(INPUT_PIN, INPUT);
    this->baudRate = baudRate;
    waitTime = 1000000 / baudRate;
}

void CustomUart::sendByte(uint8_t byte)
{
    // first bit always low
    outputBit(0);
    for (int i = 0; i < 8; i++)
    {
        outputBit((byte >> i) & 1);
    }

    // stop bit;
    outputBit(1);
}

uint8_t CustomUart::receiveByte(int &status)
{
    bool bitRecv;
    uint8_t recvdByte = 0;
    status = 0;

    while (inputBit())
    {
    }
    // get the data
    for (int i = 0; i < 8; i++)
    {
        bitRecv = inputBit();
        recvdByte = (recvdByte) | (bitRecv << i);
    }

    // make sure stop bit
    bitRecv = inputBit();
    if (!bitRecv)
    {
        // this isnt an end bit!
        status = -1;

        return 0;
    }
    return recvdByte;
}

void CustomUart::outputBit(bool bit)
{
    digitalWrite(OUTPUT_PIN, bit);
    bitDelay();
}

bool CustomUart::inputBit()
{
    bool ret = digitalRead(INPUT_PIN);
    bitDelay();
    return ret;
}

void CustomUart::bitDelay()
{
    delayMicroseconds(waitTime);
    return;
}
