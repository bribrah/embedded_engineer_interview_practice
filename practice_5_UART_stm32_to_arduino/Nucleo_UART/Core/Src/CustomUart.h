/*
 * CustomUart.h
 *
 *  Created on: Feb 7, 2024
 *      Author: bespinosa
 */

#ifndef SRC_CUSTOMUART_H_
#define SRC_CUSTOMUART_H_
#include <stdint.h>
#include "main.h"


#ifdef __cplusplus
extern "C"{
#endif





class CustomUart
{

public:
    CustomUart(uint32_t baudRate);

    void sendByte(uint8_t byte);

    uint8_t receiveByte(int &status);

    void setSimulatedInputBuffer(uint8_t byte);

private:
    uint32_t baudRate;
    size_t waitTime;

    void outputBit(bool bit);
    void bitDelay();
    bool inputBit();
};


void recvSendLoop();

#ifdef __cplusplus
}
#endif

#endif /* SRC_CUSTOMUART_H_ */
