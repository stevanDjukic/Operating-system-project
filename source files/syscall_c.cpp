//
// Created by os on 9/4/22.
//
#include "../h/syscall_c.h"
#include "../h/CCB.hpp"

uint64 spakuj(uint64, ...){
    __asm__ volatile ("ecall");
    uint64 povratna;
    __asm__ volatile("mv %0, a0" : "=r" (povratna));
    return povratna;
}


int thread_create(thread_t* handle, void (*start_routine)(void *), void *arg) {
    void* stack = mem_alloc(DEFAULT_STACK_SIZE * sizeof (uint64));
    int pov = (int)spakuj(0x11, handle, start_routine, arg,stack);
    return pov;
}

void *mem_alloc(size_t size) {
    void* pov = (void*)spakuj(0x01, size);
    return pov;
}

int mem_free(void * vrij) {
    int pov = (int)spakuj(0x02,vrij);
    return pov;
}

int thread_exit() {
    int x = (int)spakuj(0x012);
    return x;
}

void thread_dispatch() {
    spakuj(0x13);
}

int sem_open(sem_t* handle, unsigned int init) {
    int x = (int)spakuj(0x21,handle,init);
    return x;
}

int sem_close(sem_t handle) {
    int x = (int)spakuj(0x22, handle);
    return x;
}

int sem_wait(sem_t id) {
    int x = (int)spakuj(0x23, id);
    return x;
}

int sem_signal(sem_t id) {
    int x = (int)spakuj(0x24, id);
    return x;
}
/*
int time_sleep(time_t slice) {
    int x  = spakuj ()
    __asm__ volatile("mv %0, a0" : "=r" (x));
    return x;
}
*/

void putc(char s){
    spakuj(0x42,s);
}

char getc(){
    char c = (char)spakuj(0x41);
    return c;
}
/*
int get_id() {
    int x;
    __asm__ volatile ("mv a0, %0" : : "r" (0x51));
    __asm__ volatile ("ecall");
    __asm__ volatile("mv %0, a0" : "=r" (x));
    thread_dispatch();
    return x;
}

void join_thread(thread_t handle) {
    __asm__ volatile ("mv a1, %0" : : "r" (handle));
    __asm__ volatile ("mv a0, %0" : : "r" (0x52));
    __asm__ volatile ("ecall");
}
*/