#ifndef UTILSCPP_CHECK_MALLOC_HPP
#define UTILSCPP_CHECK_MALLOC_HPP

#include <iostream>

struct AllocationMetrics {
    uint32_t TotalAllocated = 0;
    uint32_t TotalFreed = 0;

    uint32_t CurrentUsage() { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics s_AllocationMetrics;

void* operator new(size_t size)
{
    // std::cout << "Allocating " << size << " bytes\n";
    s_AllocationMetrics.TotalAllocated += size;

    return malloc(size);
}

void operator delete(void* memory, size_t size)
{
    // std::cout << "Freeing " << size << " bytes\n";
    s_AllocationMetrics.TotalFreed += size;

    free(memory);
}

static void PrintMemoryUsage()
{
    std::cout << "Memory Usage: " << s_AllocationMetrics.CurrentUsage() << " bytes\n";
}

#endif // UTILSCPP_CHECK_MALLOC_HPP