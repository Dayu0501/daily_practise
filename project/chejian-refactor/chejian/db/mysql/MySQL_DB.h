#pragma once

#include <string>
#include <mutex>
#include <mysqld_error.h>
#include <mysql.h>
#include <mysqld_error.h>

class MySQL_DB
{
public:
	MySQL_DB();
	~MySQL_DB();

    static bool initialize_MySQL_library();
    static void terminate_MySQL_library();

    bool connect(const char *host, unsigned int port, const char *user, const char *passwd, const char *db, bool statrments=false);	/* host可以为NULL，表示本机；其他参数不能为NULL */
	void disconnect();
	bool createTable(const char *name, const char *format);	/* 创建Table，如果已存在则不会创建 */
	bool dropTable(const char *name);
	bool insert(const char *tableName, const char *valueFormat);
	bool select(const char *tableName, const char *format);	/* 将SELECT结果输出到终端(需要根据实际需求修改) */
    bool noReturnWork(const char *sql);
	unsigned long getLastID();		/* 返回0说明出错。仅限于执行insert之后，返回具有AUTO_INCREMENT属性的值。 */
	bool createDB(const char *name);	/* 创建database，如果已存在则不会创建。（使用默认字符编码） */
	bool selectDB(const char *name);	/* 指定某个数据库为默认数据库，之后的所有操作均在这个数据库上 */
	MYSQL_RES *getResult(const char *SqlStatement);	
	void freeResult(MYSQL_RES *result);
	unsigned int getErrorNumber();

private:
	MYSQL mysql;
};
