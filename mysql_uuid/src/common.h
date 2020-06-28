#ifndef _COMMON_H
#define _COMMON_H

#include <string>
#include <vector>

typedef struct _DB_PARAM {
    std::string strDbName;   //数据库名称
    std::string strHost;     //数据库所在主机ip
    std::string strUserName; //数据库用户名
    std::string strPassword; //数据库密码
    unsigned int port;
} DB_PARAM, *PDB_PARAM;


#endif