#ifndef _C_DBTASK_SQLOPER_H
#define _C_DBTASK_SQLOPER_H
#include <iostream>
#include "base/baseInc.h"
#define UNUSED(x) (void)x

enum DB_TYPE
{
    DB_ORACLE = 0,
    DB_MYSQL = 1,
};

class _c_dbTaskSqlOper{
public:
    static _c_dbTaskSqlOper& getInstance();

    bool executeCreatDb(DB_TYPE databaseType, PDB_PARAM pParam);
    bool executeSql(DB_TYPE databaseType, PDB_PARAM pParam, const std::string& strSql, bool statrments);
    std::vector<bool> executeSql(DB_TYPE databaseType, PDB_PARAM pParam, std::vector<std::string> sqlVector, bool statrments);
    void executeQuery(DB_TYPE databaseType, PDB_PARAM pParam, const std::string& strSql);

private:
    bool executeOracleCreatDb(PDB_PARAM pParam);
    bool executeMysqlCreatDb(PDB_PARAM pParam);

    bool executeOracleSql(PDB_PARAM pParam, const std::string& strSql, bool statrments);
    bool executeMysqlSql(PDB_PARAM pParam, const std::string& strSql, bool statrments);

    bool executeOracleQuery(PDB_PARAM pParam, const std::string& strSql);
    bool executeMysqlQuery(PDB_PARAM pParam, const std::string& strSql);
};

#endif
