#ifndef _C_COMMONLSHQUCHONG_H
#define _C_COMMONLSHQUCHONG_H

#include "base/baseInc.h"

class lshVectorMember {
public:

    lshVectorMember(std::string lsh_new){
        this->__lsh = lsh_new;
        this->__inTime = std::chrono::system_clock::now();
    }

    void updateInSystemTime(){
        __inTime = std::chrono::system_clock::now();
    }

    bool check(std::string lsh){
        return  (lsh==__lsh);
    }

    unsigned int getInSystemTime(){
        std::chrono::time_point<std::chrono::system_clock> nowTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> milliseconds = nowTime - __inTime;
        return (unsigned int)milliseconds.count();
    }
private:
    std::chrono::time_point<std::chrono::system_clock> __inTime;
    std::string __lsh;
};

#endif // _C_COMMONLSHQUCHONG_H
