#include <stdint.h>

class SoftwareUART
{
public:
    SoftwareUART(); // Constructor to initialize UART settings
    void sendByte(uint8_t byte);
    uint8_t receiveByte();

private:
    void outputBit(bool bit); // Simulate outputting a bit (TX)
    bool inputBit();          // Simulate reading a bit (RX)
    void simulateBitDelay();  // Simulate the delay between bits based on the baud rate
};

int main()
{
    SoftwareUART uart;

    return 0;
}