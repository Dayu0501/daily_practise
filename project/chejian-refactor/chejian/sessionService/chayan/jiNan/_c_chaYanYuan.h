#ifndef _C_CHAYANYUAN_H
#define _C_CHAYANYUAN_H
#include "base/_c_dbTask.h"

class _c_chaYanYuan:public _c_dbTask{
public:
    virtual ~_c_chaYanYuan(){} //用于释放内存（必须）
    std::string xingMing;
    std::string shenFenZheng;
    std::string chanYanQuXuHao;
    std::string sheBeiId;
    _c_chaYanYuan(){
        loadUuid();
        tableName = "chaYanYuan_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"sheBeiId", "sheBeiId", &sheBeiId, "设备ID", DBOPTION_DEFAULT});
        memberVector.push_back({"chanYanQuXuHao", "chanYanQuXuHao", &chanYanQuXuHao, "查验区序号", DBOPTION_DEFAULT});
        memberVector.push_back({"xingMing", "xingMing", &xingMing, "姓名", DBOPTION_DEFAULT});
        memberVector.push_back({"shenFenZheng", "shenFenZheng", &shenFenZheng, "身份证号", DBOPTION_DEFAULT});
    }
    virtual std::string getSql();
    virtual bool statrments(){return true;}
};
#endif // _C_CHAYANYUAN_H

