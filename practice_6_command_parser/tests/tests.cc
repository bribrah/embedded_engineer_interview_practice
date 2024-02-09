#include <gtest/gtest.h>
#include <SoftwareUart.h>
#include <sstream>
#include <iostream>
#include <vector>

std::vector<std::string> splitString(std::string, char delim)
{
    using namespace std;
    vector<string> strings;
    istringstream f("denmark;sweden;india;us");
    string s;
    while (getline(f, s, ';'))
    {
        cout << s << endl;
        strings.push_back(s);
    }
    return strings;
}

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(SoftwareUart, SendTests)
{
    SoftwareUART myUart(9600);
    testing::internal::CaptureStdout();
    myUart.sendByte(1);
    std::string output = testing::internal::GetCapturedStdout();
    std::vector<std::string> split = splitString(output, '\n');

    EXPECT_GE(split.size(), 1);
    EXPECT_STREQ(split[1].c_str(), "00000001");
}