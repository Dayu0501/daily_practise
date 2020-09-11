#ifndef _C_FU_JIAN_H
#define _C_FU_JIAN_H
#include "base/_c_dbTask.h"
#include "db/dbquery/dbbaseclass.h"


class _c_fuJian:public _c_dbTask{
public:
    virtual ~_c_fuJian(){} //用于释放内存（必须）
    std::string cheJiaHao;
    _c_fuJian(){
        loadUuid();
        tableName = "fuJian_info";
        memberVector.push_back({"uuid", "UUID", &uuid, "UUID", DBOPTION_DEFAULT});
        memberVector.push_back({"chejiahao", "cheJiaHao", &cheJiaHao, "cheJiaHao", DBOPTION_DEFAULT});
    }
};

class _c_fuJian_clearTable:public _c_dbTask{
public:
	virtual ~_c_fuJian_clearTable(){}
	_c_fuJian_clearTable(){
		this->tableName = "fuJian_info" ; 
	}

	virtual std::string getSql(){
        std::string startTime = baseTool::getDangTianRiQi(-6);
        std::string sqlstr= "delete from " + this->tableName + " where inDbTime < '" + startTime + "'";
		return sqlstr ;
	}
};

class db_fujian:public dbBaseClass{
public:
    std::string id;
    std::string cheJiaHao;

    dbBaseClass *getDbClass(){
        return new db_fujian();
    }

    db_fujian(){
        memberVector.push_back({"uuid", "uuid","ID", &id,true});
        memberVector.push_back({"chejiahao", "cheJiaHao", "cheJiaHao", &cheJiaHao,true});
    }
};

#endif // _C_FU_JIAN_H
