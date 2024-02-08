#include <stdint.h>
#include <chrono>
#include <iostream>
#include <thread>

class SoftwareUART
{
public:
    bool simulatedInputBuf[10];

    SoftwareUART(uint32_t baudRate)
    {
        this->baudRate = baudRate;
        waitTime = 1000000. / baudRate;
    }
    void sendByte(uint8_t byte)
    {
        // first bit always low
        std::cout << "in send byte\n";
        outputBit(0);
        simulateBitDelay();
        for (int i = 0; i < 8; i++)
        {
            outputBit((byte >> i) & 1);
            simulateBitDelay();
        }

        // stop bit;
        outputBit(1);
        std::cout << "\ndone with send byte\n";
    }
    uint8_t receiveByte(int &status)
    {
        std::cout << "in recv byte\n";
        bool bitRecv;
        inputBufPointer = 0;
        uint8_t recvdByte = 0;
        status = 0;

        bitRecv = inputBit();
        if (bitRecv)
        {
            // this isnt a start bit!
            std::cerr << "No start bit in recv!\n";
            inputBufPointer = 0;
            status = -1;
            return 0;
        }
        simulateBitDelay();

        // get the data
        for (int i = 0; i < 8; i++)
        {
            bitRecv = inputBit();
            recvdByte = (recvdByte) | (bitRecv << i);
            simulateBitDelay();
        }

        // make sure stop bit
        bitRecv = inputBit();
        if (!bitRecv)
        {
            // this isnt an end bit!
            inputBufPointer = 0;
            status = -1;
            std::cerr << "No stop bit in recv!\n";

            return 0;
        }
        std::cout << "\nRecieved: " << (int)recvdByte << std::endl;
        std::cout << "\ndone with recv byte\n";
        return recvdByte;
    }

    void setSimulatedInputBuffer(uint8_t byte)
    {
        for (int i = 0; i < 8; i++)
        {
            simulatedInputBuf[i + 1] = (byte >> i) & 1;
        }
        // set start and stop bits
        simulatedInputBuf[0] = 0;
        simulatedInputBuf[9] = 1;
    }

private:
    uint32_t baudRate;
    double waitTime;
    size_t inputBufPointer = 0;

    void outputBit(bool bit)
    {
        std::cout << bit;
    }

    bool inputBit()
    {
        bool bit = simulatedInputBuf[inputBufPointer];
        std::cout << bit;
        inputBufPointer++;
        return bit;

    } // Simulate reading a bit (RX)

    void simulateBitDelay()
    {
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(waitTime)));
        return;
    }
};

int main()
{
    SoftwareUART uart(9600);
    uint8_t recvd;
    int status;

    uart.sendByte(8);

    uart.setSimulatedInputBuffer(55);
    recvd = uart.receiveByte(status);

    uart.simulatedInputBuf[0] = 1;
    recvd = uart.receiveByte(status);

    uart.simulatedInputBuf[0] = 0;
    uart.simulatedInputBuf[9] = 0;
    recvd = uart.receiveByte(status);

    return 0;
}