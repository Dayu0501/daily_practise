#ifndef _DB_TOOLS_H
#define _DB_TOOLS_H

#include "common.h"
#include <mutex>
#include <mysql.h>
#include <mysqld_error.h>
#include <stdio.h>
#include <string>

using namespace std;

class DB_tools {
public:
    DB_tools();

    ~DB_tools();

    bool init();

    bool isConn();

    bool DB_conn(const DB_PARAM &dbParam, bool statrMents);

    bool DB_query(string sql, vector<vector<string>> &resultSet);

    bool DB_execSql(string sql);

    bool returnExecSql(string sql);

    void data_dispatcher_init();

    bool getResult();

private:
    MYSQL mMysql{};
    bool mIsConn = false;
};

#endif
