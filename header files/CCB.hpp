#ifndef PROJECT_BASE_THREAD_H
#define PROJECT_BASE_THREAD_H

#include "../lib/hw.h"
#include "Scheduler.hpp"
#include "Riscv.h"

class CCB {
public:
    ~CCB(){ delete[]stack;};
    using Arg = void *;
    using Body = void(*)(Arg);

    static int createCCB(CCB** ccb,Body body, Arg arg, void* stack);

    bool isFinished() const{
        return finished;
    }

    void setFinished(bool finished){
        CCB::finished = finished;
    }

    static int inden;

    bool isBlocked() const;

    void setBlocked(bool blocked);

    int getId() const;

    static void exit();

    static void yield();

    static CCB * running;

    static void dispatch();
    void* operator new(size_t size){return Memory_allocator::mem_alloc(size);}
    void operator delete(void* point){ Memory_allocator::mem_free(point);}
private:
    explicit CCB(Body body, Arg arg, void* stack_mem);
    struct Context{
        uint64 ra;
        uint64 sp;
    };
    Body body;
    uint64* stack;
    Context context;
    bool finished;
    bool blocked = false;
    Arg arg;
    static void threadWrapper();
    static void contextSwitch(Context* oldContext,  Context* runningContext);

    int id;
};


#endif //PROJECT_BASE_THREAD_H
