#ifndef DBBASECLASS_H
#define DBBASECLASS_H
#include "../base/baseInc.h"

class dbItem {
public:
    std::string name;   //名称
    std::string dbtype; //数据库查询列
    std::string desc;   //描述用于web列描述
    std::string *value; //值地址
    bool isOpen;        //是否使用
};

class dbBaseClass{
public:

    std::vector<dbItem> memberVector = {};
    std::vector<dbBaseClass *> queryVector={};

    dbBaseClass(){}
    virtual ~dbBaseClass(){
        for (unsigned int i = 0; i < queryVector.size(); i++) {
            delete queryVector[i];
        }
    }

    dbBaseClass(const dbBaseClass &other)
    {
        for (unsigned int i = 0; i < memberVector.size(); i++) {
            *(memberVector[i].value) = *(other.memberVector[i].value);
        }
    }

    dbBaseClass& operator=(const dbBaseClass &other)
    {
        for (unsigned int i = 0; i < memberVector.size(); i++) {
            *(memberVector[i].value) = *(other.memberVector[i].value);
        }

        return *this;
    }

    Json::Value getJson();
    virtual dbBaseClass *getDbClass(){
        return new dbBaseClass();
    }

    virtual std::string getSql(std::vector<std::string> *pWhereVector,std::string table);
    unsigned int query(std::string table,std::vector<std::string> *pWhereVector,const char *host, unsigned int port, const char *user, const char *passwd, const char *db);
    Json::Value getVectorJson();
    Json::Value getOrderJson();

};
#endif // DBBASECLASS_H
