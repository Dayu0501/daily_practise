#ifndef _C_OBJECT_H
#define _C_OBJECT_H
#include "baseInc.h"

class _c_object{
public:
    std::string uuid;
    std::vector<objectMember> memberVector; //存放最开始从车辆所数据库中拿到的每一项的数据。

    virtual ~_c_object(){} //用于释放内存（必须）
    std::string loadUuid();
    bool checkUuid(std::string id);
    void analyseJson(Json::Value &root);

    virtual void close(){}
};
#endif // _C_OBJECT_H
