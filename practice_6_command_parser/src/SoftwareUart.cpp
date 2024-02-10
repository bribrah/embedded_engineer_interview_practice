#include "SoftwareUart.h"

SoftwareUART::SoftwareUART(uint32_t baudRate, LOGLEVEL logLevel)
{
    this->baudRate = baudRate;
    waitTime = 1000000. / baudRate;
    log.setLogLevel(logLevel);
}

void SoftwareUART::sendByte(uint8_t byte)
{
    // first bit always low
    log.info("in send byte");
    outputBit(0);
    for (int i = 0; i < 8; i++)
    {
        outputBit((byte >> i) & 1);
    }

    // stop bit;
    outputBit(1);
    log.info("done with send byte");
}

uint8_t SoftwareUART::receiveByte(int &status)
{
    log.info("in recv bytes");
    bool bitRecv;
    inputBufPointer = 0;
    uint8_t recvdByte = 0;
    status = 0;

    bitRecv = inputBit();
    if (bitRecv)
    {
        // this isnt a start bit!
        std::cerr << "No start bit in recv!\n";
        status = -1;
        return 0;
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
        std::cerr << "No stop bit in recv!\n";

        return 0;
    }
    log.info("Recieved %d", (int)recvdByte);
    log.info("Done with recv byte");
    return recvdByte;
}

std::string SoftwareUART::recieveUntil(char delim, int &status)
{
    std::string ret;

    status = 0;
    uint8_t revcd = 0;
    int length = 0;
    inputStrPointer = 0;

    // making it so max string length is 100 here, maybe add a param for this
    while (status == 0 && (char)revcd != delim && length < 100)
    {
        setSimulatedInputBuffer(simulatedInputStrBuf[length]);
        revcd = receiveByte(status);
        ret += (char)revcd;
        inputStrPointer++;
        length++;
    }

    return ret;
}

void SoftwareUART::setSimulatedInputBuffer(uint8_t byte)
{
    for (int i = 0; i < 8; i++)
    {
        simulatedInputBuf[i + 1] = (byte >> i) & 1;
    }
    // set start and stop bits
    simulatedInputBuf[0] = 0;
    simulatedInputBuf[9] = 1;
}

void SoftwareUART::outputBit(bool bit)
{
    std::cout << bit;
    simulateBitDelay();
}

bool SoftwareUART::inputBit()
{
    bool bit = simulatedInputBuf[inputBufPointer];
    log.info("%d", bit);
    inputBufPointer++;
    simulateBitDelay();
    return bit;
}

void SoftwareUART::simulateBitDelay()
{
    std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(waitTime)));
    return;
}

void SoftwareUART::setSimuatedInputString(std::string str)
{
    memcpy(simulatedInputStrBuf, str.c_str(), 100);
}