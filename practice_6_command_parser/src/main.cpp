#include <iostream>
#include <string>
#include "SoftwareUart.h"
#include "CommandParser.h"

int helloWorld(char *argv[], int argc)
{
    std::cout << "HELLO WORLD" << std::endl;
    return 0;
}

int main()
{
    SoftwareUART uart(9600, LOG_ERROR);
    CommandParser cmdParser;
    DebugLogger log;
    log.setLogLevel(LOG_INFO);

    std::string inputFromCLI, recvdUART;
    int status;

    cmdParser.registerNewCommand("hello", helloWorld);

    while (inputFromCLI != "exit")
    {
        log.debug("In get command");
        std::getline(std::cin, inputFromCLI);
        inputFromCLI += "\n";

        uart.setSimuatedInputString(inputFromCLI);
        recvdUART = uart.recieveUntil('\n', status);
        if (status == -1)
        {
            log.error("ERROR DOING SIMULATED UART RECV...");
            return -1;
        }
        cmdParser.parseCommandString(recvdUART);
    }
    return 0;
}