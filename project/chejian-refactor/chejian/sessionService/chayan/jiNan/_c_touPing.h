#ifndef _C_TOUPING_H
#define _C_TOUPING_H
#include "base/_c_dbTask.h"


class _c_touPing:public _c_dbTask{
public:
    virtual ~_c_touPing(){} //用于释放内存（必须）
    std::string shenFenZheng;
    std::string jsonMsg;
    std::string isSend;
    _c_touPing(){
        loadUuid();
        tableName = "jiNanTouPing_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"shenFenZheng", "shenFenZheng", &shenFenZheng, "shenFenZheng", DBOPTION_DEFAULT});
        memberVector.push_back({"isSend", "isSend", &isSend, "isSend", DBOPTION_DEFAULT});
        memberVector.push_back({"jsonMsg", "jsonMsg", &jsonMsg, "jsonMsg", DBOPTION_TEXT});
    }
};

class _c_touPing_clearTable:public _c_dbTask{
public:
	virtual ~_c_touPing_clearTable(){}
	_c_touPing_clearTable(){
		this->tableName = "jiNanTouPing_info" ; 
	}

	virtual std::string getSql(){
        std::string sqlstr= "truncate table " + this->tableName ;
		return sqlstr ;
	}
};
#endif // _C_TOUPING_H
