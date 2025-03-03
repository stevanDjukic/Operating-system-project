//
// Created by os on 8/10/22.
//

#include "../h/CCB.hpp"
#include "../h/Riscv.h"
#include "../lib/hw.h"

CCB *CCB::running = nullptr;

int CCB::inden = 0;

CCB::CCB(Body body, Arg arg, void* stack_mem) : body(body),
                                              stack(body != nullptr ? (uint64*) stack_mem: nullptr),
                                              context({(uint64)&threadWrapper,stack != nullptr ? (uint64)&stack[DEFAULT_STACK_SIZE]:0})
, finished(false),
                                              arg(body!= nullptr ? arg : nullptr)
{
    if (body != nullptr) { Scheduler::put(this);
    }

}
int CCB::createCCB(CCB** ccb, CCB::Body body, CCB::Arg arg, void* stack) {
    *ccb = new CCB(body, arg,stack);
    return 0;
}


void CCB::dispatch() {
    CCB * old = running;
    if(!old->isBlocked() && !old->isFinished()){Scheduler::put(old);}
    running = Scheduler::get();

    CCB::contextSwitch(&old->context, &running->context);
}

void CCB::threadWrapper() {
    Riscv::popSppSpie();
    running->body(CCB::running->arg);
    running->setFinished(true);
    __asm__ volatile ("li a0, 0x13");
    __asm__ volatile ("ecall");

    //running->dispatch();
}

void CCB::exit() {
    running->setFinished(true);
    dispatch();
}

bool CCB::isBlocked() const {
    return blocked;
}

void CCB::setBlocked(bool blocked) {
    CCB::blocked = blocked;
}

int CCB::getId() const {
    return id;
}





