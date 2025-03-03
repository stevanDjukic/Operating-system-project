#ifndef PROJECT_BASE_SEMAFOR_H
#define PROJECT_BASE_SEMAFOR_H
#include "../lib/hw.h"
#include "../h/List.hpp"
#include "../h/CCB.hpp"
#include "../h/Scheduler.hpp"


class Semafor {
public:
    Semafor(int init = 1);
    int wait();
    int signal();
    int close();
    static int otvori(Semafor** sem, unsigned init);
    void* operator new(size_t size){return Memory_allocator::mem_alloc(size);}
    void operator delete(void* point){ Memory_allocator::mem_free(point);}
private:
    int val = 0;
    List<CCB> blocked;
    void block();
    void unblock();
    ushort closed = 0;
};
//int lock = 0;

#endif //PROJECT_BASE_SEMAFOR_H
