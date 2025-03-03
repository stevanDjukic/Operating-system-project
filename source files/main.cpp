#include "../h/CCB.hpp"
#include "../h/Workers.h"
#include "../h/userMain.hpp"
#include "../lib/console.h"
#include "../h/syscall_c.h"
#include "../h/Memory_allocator.h"
#include "../h/Riscv.h"
int main() {
    Memory_allocator::inicijalizacija();
    Riscv::w_stvec((uint64) &Riscv::superVisortrap);
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    CCB* glavna;
    void* stack =  Memory_allocator::mem_alloc(DEFAULT_STACK_SIZE*sizeof (uint64));
    CCB::createCCB(&glavna, nullptr, nullptr, stack);
    CCB::running = glavna;

     __asm__ volatile ("ecall");

     userMain();

    return 0;
}