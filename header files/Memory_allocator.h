#ifndef PROJECT_BASE_MEMORY_ALLOCATOR_H
#define PROJECT_BASE_MEMORY_ALLOCATOR_H

#include "../lib/hw.h"

struct FreeMem {
    FreeMem* next = nullptr; // sledeci u listi
    FreeMem* prev = nullptr; // prethodni u listi
    size_t size; // velicina slobodnog segmenta
    FreeMem(size_t x =((uint64)HEAP_END_ADDR - (uint64)HEAP_START_ADDR)/ 8,FreeMem* next = nullptr, FreeMem* prev = nullptr):next(next),prev(prev),size(x){}
};

class Memory_allocator {
private:

    static int merge(FreeMem* cur);

public:
    static FreeMem* lista;

    static void inicijalizacija();

    static void* mem_alloc(size_t size);

    static int mem_free(void* mem);

};


#endif //PROJECT_BASE_MEMORY_ALLOCATOR_H
