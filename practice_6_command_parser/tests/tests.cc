#include <gtest/gtest.h>
#include <SoftwareUart.h>
#include <vector>
#include <string>
#include <util.h>
#include <CommandParser.h>
#include "basicCommands.h"

class CommandParserTest : public testing::Test
{
protected:
    CommandParser parser;
    void SetUp() override
    {
        parser.registerNewCommand("hello", helloWorld);
        parser.registerNewCommand("sum", doSum);
    }
};

SoftwareUART getUart()
{
    return SoftwareUART(9600, LOG_ERROR);
}

std::string runCommandAndGetStdout(CommandParser *parser, std::string command)
{
    testing::internal::CaptureStdout();
    parser->parseCommandString(command);
    return testing::internal::GetCapturedStdout();
}

static inline bool contains(std::string s, std::string substr)
{
    return s.find(substr) != std::string::npos;
}

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(SoftwareUart, Send1Byte)
{
    SoftwareUART myUart = SoftwareUART(9600, LOG_DEBUG);
    testing::internal::CaptureStdout();
    myUart.sendByte(1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(contains(output, "0100000001"));
}

TEST(SoftwareUart, Recv1Byte)
{
    SoftwareUART myUart = getUart();
    uint8_t recvd;
    int status;

    myUart.setSimulatedInputBuffer(10);
    recvd = myUart.receiveByte(status);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(recvd, 10);
}

TEST(SoftwareUart, BadRevc)
{
    SoftwareUART myUart = getUart();
    uint8_t recvd;
    int status;

    myUart.setSimulatedInputBuffer(10);
    myUart.simulatedInputBuf[0] = 1;

    recvd = myUart.receiveByte(status);

    EXPECT_EQ(status, -1);
}

TEST(SoftwareUart, recvString)
{
    SoftwareUART myUart = getUart();
    std::string recvd;
    int status;

    char delim = '\n';
    std::string toSend = "blargin flargin\n";

    myUart.setSimuatedInputString(toSend);

    recvd = myUart.recieveUntil('\n', status);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(recvd, toSend);
}

TEST(SoftwareUart, recvStringNoDelim)
{
    SoftwareUART myUart = getUart();
    std::string recvd;
    int status;

    char delim = '\n';
    std::string toSend = "blargin flargin";

    myUart.setSimuatedInputString(toSend);

    recvd = myUart.recieveUntil('\n', status);

    EXPECT_EQ(status, 0);
    EXPECT_EQ(recvd.size(), 100);
}

TEST_F(CommandParserTest, HelloWorld)
{
    std::string captured;

    captured = runCommandAndGetStdout(&parser, "hello");
    EXPECT_TRUE(captured.find("HELLO WORLD") != std::string::npos);

    captured = runCommandAndGetStdout(&parser, "hEllO");
    EXPECT_TRUE(captured.find("HELLO WORLD") != std::string::npos);

    captured = runCommandAndGetStdout(&parser, "HELLO");
    EXPECT_TRUE(captured.find("HELLO WORLD") != std::string::npos);

    captured = runCommandAndGetStdout(&parser, "              hello            ");
    EXPECT_TRUE(contains(captured, "HELLO WORLD"));
}

TEST_F(CommandParserTest, Sum)
{
    std::string captured;
    captured = runCommandAndGetStdout(&parser, "sum 1 2 3 4");
    EXPECT_TRUE(contains(captured, "10"));
}