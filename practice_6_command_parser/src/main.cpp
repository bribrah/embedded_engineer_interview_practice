#include <iostream>
#include <string>
#include "SoftwareUart.h"
#include "CommandParser.h"

int main()
{
    SoftwareUART uart(9600);
    CommandParser cmdParser;

    uart.sendByte(5);

    std::cout << "hello world\n";
    return 0;
}