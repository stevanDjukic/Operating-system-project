#ifndef PROJECT_BASE_LIST_HPP
#define PROJECT_BASE_LIST_HPP
#include "printing.hpp"
#include "Memory_allocator.h"

template<typename T>
class List{
private:
    struct Elem{
        T *data;
        Elem * next;
        Elem(T* s, Elem *sled= nullptr):data(s),next(sled){};
        void* operator new(size_t size){return Memory_allocator::mem_alloc(size);}
        void operator delete(void* point){ Memory_allocator::mem_free(point);}
    };
    Elem *head, *tail;
    int number = 0;
public:
    List():head(nullptr),tail(nullptr){}
    List(const List<T> &) = delete;
    List<T> & operator = (const List<T> &) = delete;

    void addFirst(T* data){
        Elem * elem = new Elem(data, head);
        head = elem;
        if(!tail){tail = elem;}
        number++;
    }

    void addLast(T* data){
        Elem* elem = new Elem(data);
        if(tail){
            tail->next = elem;
            tail = elem;
        }else{
            head=tail=elem;
        }
        number++;
    }

    T* removeFirst(){
        if(!head){return 0;}

        Elem* elem = head;
        head = head->next;

        if(!head){tail = 0;}

        T* ret = elem->data;

        number--;

        return ret;
    }


    int get_number(){
        return number;
    }

    void printing(){
        Elem* cur = head;
        while(cur){
            printInt(*cur->data);
            cur = cur->next;
        }
        putc('\n');
    }

};
#endif //PROJECT_BASE_LIST_HPP
