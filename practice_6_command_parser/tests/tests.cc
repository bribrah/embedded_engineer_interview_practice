#include <gtest/gtest.h>
#include <SoftwareUart.h>
#include <vector>
#include <string>
#include <util.h>

SoftwareUART getUart()
{
    return SoftwareUART(9600, LOG_INFO);
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
    SoftwareUART myUart = getUart();
    testing::internal::CaptureStdout();
    myUart.sendByte(1);
    std::string output = testing::internal::GetCapturedStdout();
    std::vector<std::string> split = splitString(output, '\n');

    EXPECT_GE(split.size(), 1);
    EXPECT_EQ(split[1], "0100000001");
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
