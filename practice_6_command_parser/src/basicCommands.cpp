#include "basicCommands.h"

int helloWorld(char *argv[], int argc)
{
    std::cout << "HELLO WORLD" << std::endl;
    return 0;
}

int doSum(char *argv[], int argc)
{
    float sum = 0;
    for (int i = 0; i < argc; i++)
    {
        sum += std::atof(argv[i]);
    }
    std::cout << "Sum is : " << sum << std::endl;
    return 0;
}
