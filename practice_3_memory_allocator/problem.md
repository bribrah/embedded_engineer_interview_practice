### Exercise: Implement a Simple Memory Allocator

**Background**: Efficient memory management is crucial in embedded systems, which often operate under strict memory constraints. Writing a custom memory allocator is a common task for embedded systems engineers, especially when working with real-time operating systems (RTOS) or bare-metal applications where dynamic memory allocation from the standard library (like `malloc` and `free`) is either unavailable or not recommended due to its unpredictability and overhead.

**Objective**: Implement a simple memory allocator for fixed-size blocks in C++. The allocator should be designed to allocate and free blocks of memory from a predefined memory pool, ensuring efficient utilization of a limited memory resource.

**Requirements**:

1. **Memory Pool**: Define a static memory pool with a fixed size at compile time. You can use an array of bytes (e.g., `uint8_t`) to represent the memory pool.

2. **Block Size**: The allocator should work with fixed-size blocks. The size of each block can be defined at compile time or passed to the allocator at initialization.

3. **Allocation and Deallocation**: Implement functions to allocate and deallocate memory blocks. The allocation function should return a pointer to a free block if available, or `nullptr` if the memory pool is exhausted. The deallocation function should mark a previously allocated block as free, making it available for future allocations.

4. **Efficiency**: Aim for efficient use of memory and time. The allocator should minimize fragmentation and strive for constant-time allocation and deallocation operations.

5. **Thread Safety**: Optionally, make your allocator thread-safe so that it can be used in a multi-threaded environment without external synchronization.

### Example API

```cpp
class SimpleAllocator {
public:
    SimpleAllocator(size_t blockSize, size_t totalSize);
    ~SimpleAllocator();

    void* allocate();
    void deallocate(void* block);

private:
    // Internal data structures and functions
};
```

### Bonus Challenges

- **Coalescing**: Implement a mechanism to coalesce adjacent free blocks into a larger block, helping to mitigate fragmentation over time.
- **Memory Usage Statistics**: Provide functions to query the allocator for statistics like the total number of free blocks, the largest contiguous free block, and total memory usage.
- **Customization**: Allow the allocator to work with different strategies for selecting which free block to allocate (e.g., first-fit, best-fit, worst-fit).

### Deliverables

- Source code for your memory allocator, including any necessary data structures.
- A set of test cases that demonstrate the allocator's functionality, including allocation, deallocation, and handling of memory exhaustion.
- (Optional) A brief explanation of your design choices, especially regarding how you addressed efficiency and fragmentation.

This exercise tests your ability to manage low-level resources efficiently, a critical skill in embedded systems development. It also offers an opportunity to demonstrate your understanding of memory management principles, data structures, and possibly concurrency, depending on how advanced you make your solution.