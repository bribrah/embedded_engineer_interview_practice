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

## TEST CASES

### Test Case 1: Basic Allocation and Deallocation

**Objective**: Verify that the allocator can allocate and deallocate memory blocks without errors.

- **Steps**:
    1. Allocate a block of memory using your allocator.
    2. Verify the returned pointer is not `nullptr`.
    3. Deallocate the block.
    4. Attempt to allocate another block and ensure it succeeds.

**Expected Outcome**: Both allocations should succeed, and the allocator should not return `nullptr` for any allocation that doesn't exceed the pool size.

### Test Case 2: Fill the Entire Pool

**Objective**: Test the allocator's behavior when the entire memory pool is filled.

- **Steps**:
    1. Continuously allocate blocks until the allocator returns `nullptr`, indicating the pool is exhausted.
    2. Count the number of successful allocations and compare it with the expected number based on the pool size and block size.

**Expected Outcome**: The number of successful allocations should match the total size of the pool divided by the block size.

### Test Case 3: Memory Pool Exhaustion and Release

**Objective**: Ensure the allocator correctly handles pool exhaustion and subsequent release of memory.

- **Steps**:
    1. Allocate blocks until the pool is exhausted.
    2. Deallocate at least one block.
    3. Allocate a new block.
    4. Verify that the new allocation is successful after deallocation.

**Expected Outcome**: After deallocation, new allocations should succeed even if the pool was previously exhausted.

### Test Case 4: Random Allocation and Deallocation

**Objective**: Simulate a more realistic usage pattern with random allocations and deallocations.

- **Steps**:
    1. Create a loop that randomly decides whether to allocate or deallocate a block, keeping track of allocated blocks.
    2. Ensure that deallocation requests only target previously allocated blocks.
    3. Run the loop a significant number of times (e.g., thousands of iterations).

**Expected Outcome**: The allocator should not crash, and all allocations and deallocations should be handled correctly without leaking memory.

### Test Case 5: Deallocating Non-Allocated Memory

**Objective**: Verify that the allocator behaves correctly when asked to deallocate a pointer that was not allocated by it.

- **Steps**:
    1. Pass a random pointer (not returned by the allocator) to the deallocation function.
    2. Optionally, pass a `nullptr` to the deallocation function.

**Expected Outcome**: The allocator should safely ignore the deallocation request without crashing or corrupting the memory pool. Implementing and checking for such safety features may require additional logic in your allocator.

### Test Case 6: Thread Safety (if applicable)

**Objective**: If your allocator is intended to be thread-safe, verify that it can correctly handle concurrent allocations and deallocations.

- **Steps**:
    1. Create multiple threads, where each thread performs a mix of allocations and deallocations.
    2. Join all threads and then check the integrity of the allocator's internal state (if possible).

**Expected Outcome**: The allocator should correctly manage concurrent operations without data races, deadlocks, or corruption of the memory pool.

### Writing the Tests

You can implement these tests as functions in your test suite. For tests that require randomness (like Test Case 4), you might use the `<random>` header to generate random numbers. For thread safety tests (Test Case 6), use `<thread>` and potentially `<mutex>` to manage concurrency.

Remember, thorough testing is crucial, especially for low-level components like memory allocators, as bugs can be subtle and have far-reaching effects. After implementing these tests, consider using tools like sanitizers (e.g., AddressSanitizer, ThreadSanitizer) to detect memory errors and race conditions automatically.