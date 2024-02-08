### Exercise: Software UART Communication Protocol

**Background**: UART communication is fundamental in embedded systems for serial communication between devices. In scenarios where hardware UART is not available or already in use, a software-based approach (bit-banging) can be utilized. This exercise focuses on simulating UART communication in software, emphasizing bit timing and protocol adherence.

**Objective**: Implement a class in C++ that simulates UART communication. Your implementation should include methods for sending and receiving bytes using UART protocol standards (start bit, data bits, optional parity bit, and stop bits) at a specified baud rate.

### Requirements:

1. **Data Format**: Assume the following UART settings for simplicity:
   - Baud rate: 9600 bps
   - Data bits: 8
   - Parity: None
   - Stop bits: 1

2. **Transmitter (TX)**: Implement a method to send a byte. The method should simulate UART transmission by "outputting" bits in the correct order, adhering to timing based on the baud rate. For simulation purposes, you can output bits to the console or call a mock function that represents a GPIO pin output.

3. **Receiver (RX)**: Implement a method to receive a byte. This method will "read" bits that form a UART frame and reconstruct the byte. Input can be simulated from a predefined array of bits or through mock function calls representing GPIO pin input.

4. **Timing**: Implement a mechanism to simulate the timing of UART communication based on the baud rate. This can be as simple as using sleep functions to represent the time it takes to transmit each bit.

5. **Test Suite**: Develop a set of tests to validate your UART implementation, ensuring that bytes can be correctly transmitted and received under various conditions.

### Example API

```cpp
class SoftwareUART {
public:
    SoftwareUART(); // Constructor to initialize UART settings
    void sendByte(uint8_t byte);
    uint8_t receiveByte();

private:
    void outputBit(bool bit); // Simulate outputting a bit (TX)
    bool inputBit(); // Simulate reading a bit (RX)
    void simulateBitDelay(); // Simulate the delay between bits based on the baud rate
};
```

### Bonus Challenges:

- **Error Handling**: Add support for detecting framing errors in the receiver method.
- **Parity Bit**: Extend the protocol to support parity bit calculation and verification.
- **Higher Baud Rates**: Test your implementation with higher baud rates and assess its reliability.

### Deliverables:

- Source code for the `SoftwareUART` class, including TX and RX methods.
- A test suite demonstrating the functionality of your UART implementation, including edge cases.
- (Optional) A brief discussion on potential improvements or optimizations for real-world applications.