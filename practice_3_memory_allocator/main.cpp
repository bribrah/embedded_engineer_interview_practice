#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <mutex>
#include <thread>

#define POOL_SIZE 1024
#define BLOCK_SIZE 32

class SimpleAllocator
{
public:
    size_t numAllocated = 0;

    SimpleAllocator()
    {
        for (size_t i = 0; i < numBlocks; i++)
        {
            blockFree[i] = 1;
        }
    }
    ~SimpleAllocator()
    {
    }

    void *allocate()
    {
        lock.lock();
        if (numAllocated == POOL_SIZE / BLOCK_SIZE)
        {
            lock.unlock();
            return nullptr;
        }
        for (size_t i = 0; i < numBlocks; i++)
        {
            if (blockFree[i])
            {
                blockFree[i] = 0;
                numAllocated++;
                lock.unlock();
                return &memPool[i * BLOCK_SIZE];
            }
        }

        std::cerr << "SOME ALLOCATION ERROR HAS OCCURED" << std::endl;
        lock.unlock();
        return nullptr;
    }
    void deallocate(void *block)
    {
        lock.lock();
        uintptr_t blockPtr = reinterpret_cast<uintptr_t>(block);
        uintptr_t poolPtr = reinterpret_cast<uintptr_t>(memPool);

        if (blockPtr < poolPtr || blockPtr >= poolPtr + POOL_SIZE)
        {
            std::cerr << "INVALID DEALLOCATE" << std::endl;
            lock.unlock();
            return;
        }
        size_t blockIndex = (blockPtr - poolPtr) / BLOCK_SIZE;
        // check if this actually was already allocated...
        if (blockFree[blockIndex] == 0)
        {
            blockFree[blockIndex] = 1;
            numAllocated--;
        }
        lock.unlock();
    }

private:
    uint8_t memPool[POOL_SIZE];
    uint8_t blockFree[POOL_SIZE / BLOCK_SIZE];
    size_t numBlocks = POOL_SIZE / BLOCK_SIZE;
    std::mutex lock;
    // Internal data structures and functions
};

void testWrapper(std::string testname, std::string description, void (*func)())
{
    std::cout << "\n***************** " << testname << " **********************\n";
    std::cout << "Description : " << description << std::endl;
    func();
}

std::vector<void *> fillMemory(SimpleAllocator &allocator, int &count)
{
    std::vector<void *> memoryLocs;
    count = 0;
    void *newLoc = allocator.allocate();
    while (newLoc != nullptr)
    {
        memoryLocs.push_back(newLoc);
        newLoc = allocator.allocate();
        count++;
    }
    return memoryLocs;
}

void test1()
{
    SimpleAllocator allocator;
    void *alocationLoc = allocator.allocate();
    if (alocationLoc != nullptr)
    {
        std::cout << "allocation succ\n";
    }
    else
    {
        std::cerr << "allocation failed\n";
        return;
    }

    allocator.deallocate(alocationLoc);
    std::cout << '\n';
}

void test2()
{
    SimpleAllocator allocator;
    int count;
    fillMemory(allocator, count);
    std::cout << "Allocations: " << count << ";Expected: " << POOL_SIZE / BLOCK_SIZE << std::endl;
}

void test3()
{
    SimpleAllocator allocator;
    int count;

    std::vector<void *> memoryLocs = fillMemory(allocator, count);
    allocator.deallocate(memoryLocs[10]);
    void *reallocTry = allocator.allocate();
    if (reallocTry != nullptr)
    {
        std::cout << "success!\n";
    }
    else
    {
        std::cerr << "fail!\n";
    }
}

void test4()
{
    SimpleAllocator allocator;
    std::stack<void *> memoryLocStack;
    for (int i = 0; i < 10000; i++)
    {
        int random = rand() % 100;
        if (random > 50 && !memoryLocStack.empty())
        {
            void *toDealloc = memoryLocStack.top();
            memoryLocStack.pop();
            allocator.deallocate(toDealloc);
        }
        else
        {
            void *alloced = allocator.allocate();
            if (alloced != nullptr)
            {
                memoryLocStack.push(alloced);
            }
            else if (memoryLocStack.size() != POOL_SIZE / BLOCK_SIZE)
            {
                std::cerr << "Couldnt allocated despite only having" << memoryLocStack.size() << " allocations...\n";
            }
        }
    }
}

void test5()
{
    SimpleAllocator allocator;

    void *badPtr;
    int count;
    std::vector<void *> memoryLocs = fillMemory(allocator, count);

    uintptr_t uintBadPtr = reinterpret_cast<uintptr_t>(memoryLocs[memoryLocs.size() - 1]);
    uintBadPtr += 1024;
    badPtr = reinterpret_cast<void *>(uintBadPtr);

    std::cout << "filled memory; n entries: " << count << std::endl;

    std::cout << "Expect 2 invalid deallocates here...\n";
    allocator.deallocate(badPtr);

    allocator.deallocate(nullptr);
}

void test6RandomReadWrites(SimpleAllocator *allocator)
{
    std::stack<void *> memoryLocStack;
    for (int i = 0; i < 10000; i++)
    {
        int random = rand() % 100;
        if (random > 50 && !memoryLocStack.empty())
        {
            void *toDealloc = memoryLocStack.top();
            memoryLocStack.pop();
            allocator->deallocate(toDealloc);
        }
        else
        {
            void *alloced = allocator->allocate();
            if (alloced != nullptr)
            {
                memoryLocStack.push(alloced);
            }
        }
    }
}

void test6()
{
    SimpleAllocator allocator;
    std::thread t1(test6RandomReadWrites, &allocator);
    std::thread t2(test6RandomReadWrites, &allocator);
    std::thread t3(test6RandomReadWrites, &allocator);
    std::thread t4(test6RandomReadWrites, &allocator);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
}

int main()
{
    testWrapper("test1", "simple allocate and deallocate", test1);
    testWrapper("test2", "fill to make sure that the number of allocations is correct", test2);
    testWrapper("test3", "fill , deallocate, then allocate again to test release", test3);
    testWrapper("test4", "test 10000 random allocations and deallocations", test4);
    testWrapper("test5", "Test invalid deallocates", test5);
    testWrapper("test6", "Same as test 5 except distributed over 4 threads", test6);
    return 0;
}