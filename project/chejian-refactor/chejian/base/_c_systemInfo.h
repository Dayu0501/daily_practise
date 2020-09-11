#ifndef _C_SYSTEMINFO_H
#define _C_SYSTEMINFO_H
#include "_c_dbTask.h"

class _c_systemInfo:public _c_dbTask{
public:
    virtual ~_c_systemInfo(){} //用于释放内存（必须）
    std::string lshNum;
    std::string sessionDisponseNum;
    std::string soapQueryNum;
    std::string soapNewNum;
    std::string sessionQueueNum;
    std::string sessionVectorNum;
    std::string sessionAlgQueueNum;
    std::string reponseQueueNum;
    std::string dbTaskQueueNum;
    _c_systemInfo(){
        loadUuid();
        tableName = "system_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"lshNum", "lshNum", &lshNum, "lsh处理数量", DBOPTION_DEFAULT});
        memberVector.push_back({"sessionDisponseNum", "sessionDisponseNum", &sessionDisponseNum, "已处理车辆数量", DBOPTION_DEFAULT});
        memberVector.push_back({"soapQueryNum", "soapQueryNum", &soapQueryNum, "soap查询数量", DBOPTION_DEFAULT});
        memberVector.push_back({"soapNewNum", "soapNewNum", &soapNewNum, "soap新增数量", DBOPTION_DEFAULT});
        memberVector.push_back({"sessionQueueNum", "sessionQueueNum", &sessionQueueNum, "session数量", DBOPTION_DEFAULT});
        memberVector.push_back({"sessionVectorNum", "sessionVectorNum", &sessionVectorNum, "session待处理数量", DBOPTION_DEFAULT});
        memberVector.push_back({"sessionAlgQueueNum", "sessionAlgQueueNum", &sessionAlgQueueNum, "算法任务待处理session数量", DBOPTION_DEFAULT});
        memberVector.push_back({"reponseQueueNum", "reponseQueueNum", &reponseQueueNum, "待回复数量", DBOPTION_DEFAULT});
        memberVector.push_back({"dbTaskQueueNum", "dbTaskQueueNum", &dbTaskQueueNum, "数据库待处理数量", DBOPTION_DEFAULT});
    }
};
#endif // _C_SYSTEMINFO_H
