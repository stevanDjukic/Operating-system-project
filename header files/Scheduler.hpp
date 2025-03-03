#ifndef PROJECT_BASE_SCHEDULER_HPP
#define PROJECT_BASE_SCHEDULER_HPP

class CCB;
#include "List.hpp"

class Scheduler {
private:
    static List<CCB> readyThreadQueue;
public:

    static CCB* get();

    static void put(CCB* thread);
};


#endif //PROJECT_BASE_SCHEDULER_HPP
