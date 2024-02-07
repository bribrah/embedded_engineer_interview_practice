#include <iostream>

struct structA
{
    char a;   // 1 byte
    int b;    // 4 bytes + 3 padding
    char c;   // 1byte
    double d; // 8 bytes + 7 padding
};
// // total size = 1 + 7 + 1 + 15 = 24

struct structB
{
    double a; // 8 bytes
    char b;   // 1 byte + 7 padding
    int c;    // 4 bytes
    char d;   // 1 byte + 3 padding
};
// // total size = 24;

struct structC
{
    int a;    //  4 + 4padding
    double b; // 8
    char c;   // 1
    char d;   // 1 + 6 padding
};
// total size =  8 + 8 + 8 = 24
struct structD
{
    char a;   // 1 byte
    char b;   // 1 byte + 2 padding
    int c;    // 4 bytes
    char d;   // 1 byte + 3 padding
    double e; // 8 bytes + 4 padding (multiple of 8)
};

struct structE
{
    char a;   // 1 + 7 padding
    double b; // 8
    double c; // 8
    int d;    // 4
    char e;   // 1 + 3 padding
    double f; // 8 + 2 padding
};
// 8 + 8 + 8 + 4 + 4 + 8 = 40

int main()
{

    std::cout << "start" << std::endl;

    std::cout << "A: " << sizeof(structA) << std::endl;
    std::cout << "B: " << sizeof(structB) << std::endl;
    std::cout << "C: " << sizeof(structC) << std::endl;
    std::cout << "D: " << sizeof(structD) << std::endl;
    std::cout << "E: " << sizeof(structE) << std::endl;

    return 0;
}