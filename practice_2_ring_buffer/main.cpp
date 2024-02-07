#include <iostream>
#include <stdint.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

class RingBuffer
{

private:
    int *bufArray;
    size_t writePointer;
    size_t readPointer;
    size_t size;
    size_t currentEntries;

    std::mutex mut;

    void incrementReadPointer();
    void incrementWritePointer();

public:
    RingBuffer(size_t size);
    ~RingBuffer();
    void write(int val);
    int read(int *val);
};

RingBuffer::RingBuffer(size_t size)
{
    bufArray = new int[size];
    this->size = size;
    writePointer = 0;
    readPointer = 0;
    currentEntries = 0;
}

RingBuffer::~RingBuffer()
{
    delete[] bufArray;
}

void RingBuffer::incrementWritePointer()
{
    writePointer++;
    if (writePointer == size)
    {
        writePointer = 0;
    }
}
void RingBuffer::incrementReadPointer()
{
    readPointer++;
    if (readPointer == size)
    {
        readPointer = 0;
    }
}

void RingBuffer::write(int byte)
{
    mut.lock();
    bufArray[writePointer] = byte;
    currentEntries++;
    if (currentEntries > size)
    {
        currentEntries = size;
        incrementReadPointer();
    }
    incrementWritePointer();
    mut.unlock();
}

int RingBuffer::read(int *val)
{
    mut.lock();
    if (currentEntries > 0)
    {
        *val = bufArray[readPointer];
        currentEntries--;
        incrementReadPointer();
        mut.unlock();
        return 0;
    }
    else
    {
        mut.unlock();
        return -1;
    }
}

void test1()
{
    RingBuffer myBuffer(10);

    int val;
    myBuffer.write(10);
    myBuffer.read(&val);

    std::cout << "test1 : " << val << std::endl;
}

void test2()
{
    RingBuffer myBuffer(256);
    int val;
    std::cout << "test2 : ";
    for (uint16_t i = 0; i < 256; i++)
    {
        myBuffer.write(i);
    }
    while (myBuffer.read(&val) == 0)
    {
        std::cout << val << ", ";
    }
    std::cout << std::endl;
}

void test3()
{
    RingBuffer myBuffer(256);
    int val;

    for (int i = 0; i < 257; i++)
    {
        myBuffer.write(i);
    }

    // should get 1
    myBuffer.read(&val);
    std::cout << "test 3: " << val << std::endl;
}

void test4()
{
    RingBuffer myBuffer(10);
    int val = -1;
    int status = myBuffer.read(&val);

    std::cout << "Test 4: " << status << std::endl;
}

void test5()
{
    RingBuffer myBuffer(10);
    int val;
    std::cout << "Test 5: ";
    for (int i = 0; i < 10; i++)
    {
        myBuffer.write(i);
    }
    for (int i = 0; i < 3; i++)
    {
        myBuffer.read(&val);
    }

    myBuffer.write(10);
    myBuffer.write(11);

    while (myBuffer.read(&val) == 0)
    {
        std::cout << val << ", ";
    }
    std::cout << std::endl;
}

// Test writer function attempts to fill the buffer with sequential values
void concurrencyWriteTest(RingBuffer *myBuffer)
{
    std::this_thread::sleep_for(std::chrono::microseconds(100000));

    for (int i = 0; i < 200; ++i)
    {
        myBuffer->write(i);
        // Optionally, introduce a tiny sleep to increase the chance of context switching
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}
bool checkInOrder(std::vector<int> arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        if (arr[i + 1] < arr[i])
        {
            return false;
        }
    }
    return true;
}
// Test reader function attempts to read values from the buffer
void concurrencyReadTest(RingBuffer *myBuffer, std::atomic<int> &readCount)
{
    std::vector<int> valArr;
    int val;
    while (readCount.fetch_add(1) < 100)
    {
        while (myBuffer->read(&val) == -1)
        {
            // If the buffer is empty, yield the current thread's time slice
            std::this_thread::yield();
        }
        // std::cout << val << ", ";
        valArr.push_back(val);
        // Optionally, introduce a tiny sleep to increase the chance of context switching
        std::this_thread::sleep_for(std::chrono::microseconds(50));
    }
    if (!checkInOrder(valArr))
    {
        std::cout << "FAIL ";
    }
}

void test6()
{
    RingBuffer myBuffer(100);      // Assuming the buffer size is sufficient
    std::atomic<int> readCount(0); // Tracks the number of successful reads

    // Create and start writer and reader threads
    std::thread writer(concurrencyWriteTest, &myBuffer);
    std::thread reader(concurrencyReadTest, &myBuffer, std::ref(readCount));

    // Wait for both threads to complete
    writer.join();
    reader.join();

    // std::cout << "\nFinished test 6." << std::endl;
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    std::cout << "Test 6: ";

    for (int i = 0; i < 100; i++)
    {
        test6();
    }
    std::cout << "done...";
    return 0;
}