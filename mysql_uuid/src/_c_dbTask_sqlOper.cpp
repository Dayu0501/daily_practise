#include "_c_dbTask_sqlOper.h"
#include "MySQL_DB.h"

_c_dbTaskSqlOper& _c_dbTaskSqlOper::getInstance()
{
	static _c_dbTaskSqlOper dbSqlHandle;
	return dbSqlHandle;
}
bool _c_dbTaskSqlOper::executeCreatDb(DB_TYPE databaseType, PDB_PARAM pParam)
{
	UNUSED(databaseType);
	switch (databaseType)
	{
	case DB_ORACLE:
		return executeOracleCreatDb(pParam);
	case DB_MYSQL:
		return executeMysqlCreatDb(pParam);
	default:
		break;
	}
	return false;
	return true;
}

bool _c_dbTaskSqlOper::executeMysqlCreatDb(PDB_PARAM pParam)
{
	MySQL_DB::initialize_MySQL_library();
	MySQL_DB db;
	if (db.connect(pParam->strHost.c_str(), pParam->port, pParam->strUserName.c_str(), pParam->strPassword.c_str(), NULL, false))
	{
		if (!db.selectDB(pParam->strDbName.c_str()))
		{
			db.createDB(pParam->strDbName.c_str());
		}
	}
	db.disconnect();
	return true;
}

bool _c_dbTaskSqlOper::executeOracleCreatDb(PDB_PARAM pParam)
{
	UNUSED(pParam);
	//接口尚未开发，等待后续完善
	return true;
}

bool _c_dbTaskSqlOper::executeSql(DB_TYPE databaseType, PDB_PARAM pParam, const std::string& strSql, bool statrments)
{
	switch (databaseType)
	{
	case DB_ORACLE:
		return executeOracleSql(pParam, strSql, statrments);
	case DB_MYSQL:
		return executeMysqlSql(pParam, strSql, statrments);
	default:
		break;
	}
	return false;
}

std::vector<bool> _c_dbTaskSqlOper::executeSql(DB_TYPE databaseType, PDB_PARAM pParam, std::vector<std::string> sqlVector, bool statrments)
{
	std::vector<bool> boolRet;
	boolRet.clear();
	if (databaseType == DB_MYSQL)
	{
		MySQL_DB db;
		if (db.connect(pParam->strHost.c_str(), pParam->port, pParam->strUserName.c_str(), pParam->strPassword.c_str(), pParam->strDbName.c_str(), statrments)) {
			for (unsigned int i = 0; i < sqlVector.size(); i++) {
				bool ret = db.noReturnWork(sqlVector[i].c_str());

				boolRet.push_back(ret);
			}
		}
		db.disconnect();
	}
	return boolRet;
}

bool _c_dbTaskSqlOper::executeMysqlSql(PDB_PARAM pParam, const std::string& strSql, bool statrments)
{
	bool bFalse;
	MySQL_DB db;
	if (db.connect(pParam->strHost.c_str(), pParam->port, pParam->strUserName.c_str(), pParam->strPassword.c_str(), pParam->strDbName.c_str(), statrments)) {
		bFalse = db.noReturnWork(strSql.c_str());
	}
	db.disconnect();
	return bFalse;
}

bool _c_dbTaskSqlOper::executeOracleSql(PDB_PARAM pParam, const std::string& strSql, bool statrments)
{
	UNUSED(pParam);
	UNUSED(strSql);
	UNUSED(statrments);
	//接口尚未开发，等待后续完善
	return true;
}

void _c_dbTaskSqlOper::executeQuery(DB_TYPE  databaseType, PDB_PARAM pParam, const std::string& strSql, std::string& result)
{
	switch (databaseType)
	{
	case DB_ORACLE:
		executeOracleQuery(pParam, strSql, result);
		break;
	case DB_MYSQL:
		executeMysqlQuery(pParam, strSql, result);
		break;
	default:
		break;
	}
}

bool _c_dbTaskSqlOper::executeMysqlQuery(PDB_PARAM pParam, const std::string strSql, std::string& result)
{
	bool bFalse;
	MySQL_DB db;
	/*if (db.connect(pParam->strHost.c_str(), pParam->port, pParam->strUserName.c_str(), pParam->strPassword.c_str(), pParam->strDbName.c_str(), false)) */{
		MYSQL_RES* result = db.getResult(strSql.c_str());
		if (result != NULL) {
			MYSQL_ROW row = NULL;
			int cols = mysql_num_fields(result);
			while ((row = mysql_fetch_row(result)) != NULL) {
				std::string data;
				for (int i = 0; i < cols; ++i) {
					data += row[i];
				}

				printf("%%%%%%%%%%%%data = %s\n", data.c_str());
			}
			db.freeResult(result);
		}
	}
	//db.disconnect();

	return true;
}

bool _c_dbTaskSqlOper::executeOracleQuery(PDB_PARAM pParam, const std::string& strSql, std::string& result)
{
	UNUSED(pParam);
	UNUSED(strSql);
	//接口尚未开发，等待后续完善
	return true;
}

bool _c_dbTaskSqlOper::conDB(PDB_PARAM pParam) {
	MySQL_DB db;
	if (db.connect(pParam->strHost.c_str(), pParam->port, pParam->strUserName.c_str(), pParam->strPassword.c_str(), pParam->strDbName.c_str(), false))
		return true;

	return false;
}
