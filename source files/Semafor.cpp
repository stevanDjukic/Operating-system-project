#include "../h/Semafor.h"

int Semafor::wait() {
    if(closed!=1){
        if(--val<0){
            block();
        }
        return 0;
    }else{
        return -1;
    }
}

int Semafor::signal() {
    if(closed!=1){
        if(++val <= 0){
            unblock();
        }
        return 0;
    }

    return -1;
}

void Semafor::block() {
    CCB::running->setBlocked(true);
    blocked.addLast(CCB::running);
    CCB::dispatch();
}

void Semafor::unblock() {
    CCB* thread = blocked.removeFirst();
    thread->setBlocked(false);
    Scheduler::put(thread);
}

int Semafor::close() {
    for (int i =0;i<blocked.get_number();i++){
        CCB* thread = blocked.removeFirst();
        thread->setBlocked(false);
        Scheduler::put(thread);
    }
    closed =1;
    return 0;
}

Semafor::Semafor(int init) {
    val = init;
}

int Semafor::otvori(Semafor **sem, unsigned init) {
    *sem = new Semafor(init);
    return 0;
}
