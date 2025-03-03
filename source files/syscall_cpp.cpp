//
// Created by os on 8/10/22.
//
#ifndef syscall_cpp
#define syscall_cpp
#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.h"
#include "../h/CCB.hpp"

int Thread::start() {
    if(type){
        thread_create(&myHandle, &thread_Wrapper, this);
    }
    return 0;
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    return 0;
}

Thread::Thread() {
    type = true;
}

Thread::~Thread() {
}

Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle, body,arg);
    type = false;
}

void Thread::thread_Wrapper(void* arg) {
    Thread* t = (Thread*)arg;
    t->run();
}



Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);

}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}


#endif //syscall_cpp