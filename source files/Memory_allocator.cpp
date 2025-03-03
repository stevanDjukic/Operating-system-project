#include "../h/Memory_allocator.h"

FreeMem* Memory_allocator::lista = nullptr;

void *Memory_allocator::mem_alloc(size_t size) {
    uint64 brblok;
    if((size+sizeof(FreeMem))%MEM_BLOCK_SIZE!=0){
        brblok = (size+sizeof(FreeMem))/MEM_BLOCK_SIZE + 1;
    }else{brblok = (size+sizeof(FreeMem))/MEM_BLOCK_SIZE;}

    size_t velicina = brblok * MEM_BLOCK_SIZE;

    FreeMem* blk = Memory_allocator::lista;
    for (; blk!=nullptr; blk=blk->next)
        if (blk->size>=velicina){
            break;
        }
//If not found, allocate a new memory segment and add it to the list:
    if (blk == nullptr) {
        return nullptr;
    }
    uint8* ret=(uint8*)blk + (uint8)sizeof(FreeMem);
// Allocate the requested block:
    size_t remainingSize = blk->size - velicina;
    //blk->size = velicina;
    size_t offset = velicina;
    FreeMem* newBlk = (FreeMem*)((uint8*)blk + offset);
    if (blk->prev) {
        blk->prev->next = newBlk;
        newBlk->prev=blk->prev;
    }
    else {
        lista = newBlk;
        newBlk->prev=nullptr;
    }
    newBlk->next = blk->next;
    newBlk->size = remainingSize;

   return ret;
}

int Memory_allocator::mem_free(void *mem) {
    // Find the place where to insert the new free segment (just after cur):

    uint8* addr = (uint8*)mem - (uint8)sizeof(FreeMem);
    if(addr<(uint8*)HEAP_START_ADDR || addr>(uint8*)HEAP_END_ADDR-1){return -1;}
    FreeMem* cur;

    for (cur=lista; cur->next!= nullptr && addr>(uint8*)(cur->next); cur=cur->next);

    FreeMem* newSeg = (FreeMem*)addr;
    if(cur != lista){
        if(cur->next){newSeg->size = (uint8*)cur->next-(uint8*)cur; }
        else{
            newSeg->size = (uint8*)HEAP_END_ADDR-(uint8*)cur;
        }
        newSeg->prev = cur;
        if (cur) newSeg->next = cur->next;
        else newSeg->next = lista;
        if (newSeg->next) newSeg->next->prev = newSeg;
        if (cur) cur->next = newSeg;
        else lista = newSeg;
    }else{
        newSeg->next = lista;
        newSeg->prev = nullptr;
        lista = newSeg;
        merge(lista);
        return 0;
    }
// Try to merge with the previous and next segments:
    merge(newSeg);
    merge(cur);
    return 0;
}

int Memory_allocator::merge(FreeMem *cur) {
    if (!cur) return 0;
    if (cur->next && (uint8 *)cur+cur->size == (uint8 *)(cur->next)) {
// Remove the cur->next segment:
        cur->size += cur->next->size;
        cur->next = cur->next->next;
        if (cur->next) cur->next->prev = cur;
        return 1;
    } else
        return 0;
}

void Memory_allocator::inicijalizacija() {
    lista =  (FreeMem*) HEAP_START_ADDR;
    lista->next= nullptr;
    lista->prev = nullptr;
    lista->size = ((uint8*)HEAP_END_ADDR - (uint8*)HEAP_START_ADDR - (uint8)sizeof(FreeMem));

}

