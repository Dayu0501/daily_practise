#ifndef _C_RUNTIME_H
#define _C_RUNTIME_H
#include "_c_dbTask.h"

class _c_runTime:public _c_dbTask{
public:
    std::string cheLiangUid;
    std::string inSystemTime;

    std::string pushSessionQueueTime;
    std::string getSessionQueueTime;

    std::string pushAlgSessionQueueTime;
    std::string getAlgSessionQueueTime;

    std::string pushReponseQueueTime;
    std::string getReponseQueueTime;

    std::string pushDbTaskQueueTime;

    virtual ~_c_runTime(){} //用于释放内存（必须）
    _c_runTime(){
        tableName = "time_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"cheLiangUid", "cheLiangUid", &cheLiangUid, "会话UID", DBOPTION_DEFAULT});
        memberVector.push_back({"inSystemTime", "inSystemTime", &inSystemTime, "进入系统时间", DBOPTION_DEFAULT});

        memberVector.push_back({"pushSessionQueueTime", "pushSessionQueueTime", &pushSessionQueueTime, "插入等待会话模块处理队列时间", DBOPTION_DEFAULT});
        memberVector.push_back({"getSessionQueueTime", "getSessionQueueTime", &getSessionQueueTime, "会话模块拿到数据时间", DBOPTION_DEFAULT});

        memberVector.push_back({"pushAlgSessionQueueTime", "pushAlgSessionQueueTime", &pushAlgSessionQueueTime, "插入到等待算法模块处理队列时间", DBOPTION_DEFAULT});
        memberVector.push_back({"getAlgSessionQueueTime", "getAlgSessionQueueTime", &getAlgSessionQueueTime, "算法模块拿到数据时间", DBOPTION_DEFAULT});

        memberVector.push_back({"pushReponseQueueTime", "pushReponseQueueTime", &pushReponseQueueTime, "插入等待回复队列时间", DBOPTION_DEFAULT});
        memberVector.push_back({"getReponseQueueTime", "getReponseQueueTime", &getReponseQueueTime, "从等待回复队列拿到数据时间", DBOPTION_DEFAULT});

        memberVector.push_back({"pushDbTaskQueueTime", "pushDbTaskQueueTime", &pushDbTaskQueueTime, "插入等待写入数据库队列时间", DBOPTION_DEFAULT});


    }
};
#endif // _C_RUNTIME_H
