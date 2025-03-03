//
// Created by os on 9/2/22.
//

#include "../h/Riscv.h"
#include "../lib/console.h"
#include "../h/Semafor.h"
#include "../lib/console.h"
#include "../lib/mem.h"
#include "../h/syscall_c.h"
#include "../h/printing.hpp"
#include "../h/Memory_allocator.h"

void Riscv::popSppSpie() {
    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

void Riscv::handleSupervisortrap() {
    uint64 scause = Riscv::r_scause();
    if(scause == 0x8000000000000001UL){
        //timer
        mc_sip(SIP_SSIP);
    }else if(scause == 0x8000000000000009UL){
        //spoljasnji prekid
        console_handler();
    }else{

    }

    uint64 x;
    uint64 arg1;
    uint64 arg2;
    uint64 arg3;
    uint64 arg4;

    __asm__ volatile ("ld %0, 10*8(fp)":"=r" (x));
    __asm__ volatile ("ld %0, 11*8(fp)":"=r" (arg1));
    __asm__ volatile ("ld %0, 12*8(fp)":"=r" (arg2));
    __asm__ volatile ("ld %0, 13*8(fp)":"=r" (arg3));
    __asm__ volatile ("ld %0, 14*8(fp)":"=r" (arg4));


    if(scause == 0x0000000000000008UL){
        uint64 volatile sepc = r_sepc() + 4;
        uint64 volatile sstatus = r_sstatus();


        if(x == 0x01){
            uint64 y;
            y = (uint64) Memory_allocator::mem_alloc(arg1);
            //__asm__ volatile ("mv a0, %0": :"r"(y));
            __asm__ volatile("sd %0,10*8(fp)" : : "r" (y));
        }else if(x == 0x02){
            int x;
            x = Memory_allocator::mem_free((void*)arg1);
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (x));
        }else if(x == 0x11){
            int x = CCB::createCCB((CCB**)arg1,(void (*)(void*))arg2, (void*) arg3, (void*) arg4);
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (x));
        }else if(x == 0x12){
            CCB::running->exit();
        }else if(x == 0x13){
            CCB::dispatch();
        }else if(x == 0x21){
            int x  = Semafor::otvori((Semafor**)arg1, (unsigned int)arg2);
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (x));
        }else if(x == 0x22){
            int x = ((Semafor*)arg1)->close();
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (x));
        }else if(x == 0x23){
            int x = ((Semafor*)arg1)->wait();
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (x));
        }else if(x == 0x24){
            int x = ((Semafor*)arg1)->signal();
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (x));
        }else if(x == 0x31){
            // sleep
        }else if(x == 0x41){
            char s;
            s = __getc();
            __asm__ volatile("sd %0, 10*8(fp)" : : "r" (s));
        }else if(x == 0x42){
            __putc((char)arg1);
        }

        w_sepc(sepc);
        w_sstatus(sstatus);
    }else if(scause == 0x0000000000000009UL){
        uint64  sepc = r_sepc() + 4;
        mc_sstatus(SSTATUS_SPP);
        w_sepc(sepc);

    }

}
