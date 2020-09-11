#ifndef OCCI_DB_WRAPPER_H
#define OCCI_DB_WRAPPER_H

/*
occi_warp:
由于Oracle官方的occi库只能用g++-4.8编译运行，因此将其封装成库。
封装后的库可以用g++-5编译运行。
版本更新时间：2018-06-14

返回值为bool的函数需要判定为true时，才能进行下一步操作，否则可能引起exception!

以下函数必须成对使用:
initialize()和finish()
connect()和disconnect()
createStatement()和terminateStatement()
executeQuery()和closeQuery（）

initialize()和finish()作用是初始化环境和终止环境，整个进程中只需要调用一次。

伪代码:
initialize();
connect();
createStatement("SELECT * FROM TEST_TABLE");
executeQuery();

while (NotEndFetch()) {
    getString(1, out1);
    getDate(2, out2);
    getInt(3, out3);
}

closeQuery();
terminateStatement();
disconnect();
finish();

*/

#include "occi.h"

using namespace oracle::occi;

struct date_t {
    int year;
    unsigned int month;
    unsigned int day;
    unsigned int hour;
    unsigned int min;
    unsigned int sec;
};

class Occi_db_wrapper
{
public:
    Occi_db_wrapper(const char* user, const char* pwd, const char* dbUrl);
    ~Occi_db_wrapper();

    bool connect();
    bool disconnect();
    bool createStatement(const char *sql);
    bool terminateStatement();
    bool executeQuery();
    bool closeQuery();
    bool NotEndFetch();
    bool getInt(unsigned int colIndex, int &out);

    /*
    返回值为NULL：表示读取数据失败。
    返回值不为NULL：表示读取数据成功，数据已保存在该地址，有字符串终止符，需要调用free()。
    */
    char *getString(unsigned int colIndex);

    /*
    传出的月份为0：表示数据库中该字段为NULL
    传出的月份不为0：表示数据库中该字段为普通日期时间
    */
    bool getDate(unsigned int colIndex, date_t &out);

    /*
    返回值为NULL：表示读取数据失败。
    返回值不为NULL：表示读取数据成功，数据已保存在该地址，长度为length，需要调用free()。
    */
    unsigned char *getBlob(unsigned int colIndex, unsigned int &length);

    bool updateBlob(const char *sql, unsigned char *data, unsigned long size);

    /*
    charset和ncharset用户指定建立连接的编码格式。
    如果都为NULL表示采用默认编码。
    Linux下一般需要传入AL32UTF8
    */
    static bool initialize(bool MultiThread, const char *charset, const char *ncharset);
    static bool finish();

private:
    Connection *conn;
    Statement *stmt;
    ResultSet *rs;

    static Environment *env;

    std::string m_user;
    std::string m_pwd;
    std::string m_dbUrl;
};


#endif // OCCI_DB_WRAPPER_H
