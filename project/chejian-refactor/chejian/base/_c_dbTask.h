#ifndef _C_DBOBJECT_H
#define _C_DBOBJECT_H
#include "_c_object.h"

class _c_dbTask:public _c_object{
public:
    std::string tableName;

    virtual ~_c_dbTask(){} //用于释放内存（必须）
    virtual std::string getTableName();
    virtual std::string getSql();
    virtual std::string getCreatTableSql();
    virtual std::string getUpdateTableSql();
    virtual void extraDbWork(){}
    virtual void beforDbWork(){}
    virtual void dbWork();
    virtual bool needFree(){return true;}
    virtual bool statrments(){return false;}
    virtual void close(){}
};
#endif // _C_DBOBJECT_H
