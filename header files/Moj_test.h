#ifndef PROJECT_BASE_MOJ_TEST_H
#define PROJECT_BASE_MOJ_TEST_H

#include "syscall_cpp.hpp"
#include "syscall_c.h"

bool finishedA = false;
bool finishedB = false;
bool finishedC = false;

void workerBodyA(void* arg) {
    for (uint64 i = 0; i < 10; i++) {
        printString("A");
        printInt(get_id());
        printString("\n");
        for (uint64 j = 0; j < 10000; j++) {
            for (uint64 k = 0; k < 30000; k++) { /* busy wait */ }
        }

    }
    printString("A finished!\n");
    finishedA = true;
}

void workerBodyB(void* arg) {
    for (uint64 i = 0; i < 10; i++) {
        printString("B");
        printInt(get_id());
        printString("\n");
        for (uint64 j = 0; j < 10000; j++) {
            for (uint64 k = 0; k < 30000; k++) { /* busy wait */ }
        }
    }
    printString("B finished!\n");
    finishedB = true;
    thread_dispatch();
}

void workerBodyC(void* arg) {
    for (uint64 i = 0; i < 10; i++) {
        printString("C");
        printInt(get_id());
        printString("\n");
        for (uint64 j = 0; j < 10000; j++) {
            for (uint64 k = 0; k < 30000; k++) { /* busy wait */ }
        }
    }
    printString("C finished!\n");
    finishedB = true;
    thread_dispatch();
}


void Test() {
    thread_t threads[3];
    thread_create(&threads[0], workerBodyA, nullptr);
    printString("ThreadA created\n");

    thread_create(&threads[1], workerBodyB, nullptr);
    printString("ThreadB created\n");

    thread_create(&threads[2], workerBodyC, nullptr);
    printString("ThreadC created\n");

    /*while (!(finishedA && finishedB && finishedC)) {
        thread_dispatch();
    }*/
    Thread* t1 = threads[2];
    Thread* t2 = threads[3];
    Thread* t3 = threads[1];

}



#endif //PROJECT_BASE_MOJ_TEST_H
