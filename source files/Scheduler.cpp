//
// Created by os on 8/11/22.
//

#include "../h/Scheduler.hpp"

List<CCB> Scheduler::readyThreadQueue;

void Scheduler::put(CCB *thread) {
    readyThreadQueue.addLast(thread);
}

CCB *Scheduler::get() {
    return readyThreadQueue.removeFirst();
}
