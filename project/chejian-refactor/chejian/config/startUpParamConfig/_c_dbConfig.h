#ifndef _C_DBCONFIG_H
#define _C_DBCONFIG_H
#include "base/_c_dbTask.h"
#include "base/baseTool.h"

class _c_dbConfig:public _c_dbTask{
public:
    std::string dbName = DBSCHEMANAME;
    std::string dbHostIp = "127.0.0.1";
    std::string dbUserName = "root";
    std::string dbPassword = "em-data-9527";
    std::string dbPort = "3306";

    DB_PARAM dbParam;

    _c_dbConfig(){
        tableName = "db_config";
        memberVector.push_back({"dbName", "dbName", &dbName, "数据库名称", DBOPTION_DEFAULT});
        memberVector.push_back({"dbHostIp", "dbHostIp", &dbHostIp, "数据库ip地址", DBOPTION_DEFAULT});
        memberVector.push_back({"dbUserName", "dbUserName", &dbUserName, "数据库用户名称", DBOPTION_DEFAULT});
        memberVector.push_back({"dbPassword", "dbPassword", &dbPassword, "数据库用户密码", DBOPTION_DEFAULT});
        memberVector.push_back({"dbPort", "dbPort", &dbPort, "数据库端口", DBOPTION_DEFAULT});
    }

    PDB_PARAM getStructDbParam() {
        dbParam.strDbName = dbName;
        dbParam.strHost = dbHostIp;
        dbParam.strUserName = dbUserName;
        dbParam.strPassword = dbPassword;
        dbParam.port = (unsigned int)baseTool::str2Int(dbPort);

        return &dbParam;
    }

    bool needFree(){return false;}
};
#endif // _C_DBCONFIG_H
