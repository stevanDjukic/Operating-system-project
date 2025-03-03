//
// Created by os on 9/2/22.
//
#include "../lib/mem.h"
#include "../h/syscall_cpp.hpp"
#include "../h/Memory_allocator.h"

//using size_t = decltype(sizeof(0));

void *operator new(size_t n)
{
    return mem_alloc(n);
}

void *operator new[](size_t n)
{
    return mem_alloc(n);
}

void operator delete(void *p) noexcept
{
    mem_free(p);
}

void operator delete[](void *p) noexcept
{
    mem_free(p);
}


