#include "DB_tools.h"
#include <iostream>

DB_tools::DB_tools() {
    init();
}

bool DB_tools::init() {
    static bool init_flag = false;

    if (init_flag) {
        printf("initialize_MySQL_library() has been called successfully, do not "
               "need to be call again! \n");
        return false;
    }

    if (!(init_flag = !mysql_library_init(0, NULL, NULL))) {
        printf("initialize_MySQL_library() failed! \n");
    }

    return init_flag;
}

DB_tools::~DB_tools() = default;

bool DB_tools::DB_conn(const DB_PARAM &dbParam, bool statrMents) {
    if (dbParam.strHost.empty()) {
        printf("please input correct param !");
    } else {
        printf("dbParam !\n");
    }

    if (mysql_thread_init() != 0) {
        printf("mysql_thread_init() failed! \n");
        return false;
    }

    if (mysql_init(&mMysql) == nullptr) {
        printf("mysql_init() failed! \n");
        return false;
    }

    /*
        ָ���������ӵı��뷽ʽ��ȡ���ڱ��������ַ����ı���洢��ʽ��
        VS:gbk
        gcc:utf8
    */
    if (mysql_options(&mMysql, MYSQL_SET_CHARSET_NAME, "utf8") != 0) {
        printf("mysql_options(MYSQL_SET_CHARSET_NAME) failed! \n");
        return false;
    }

    unsigned long floatClient = 0;

    if (statrMents) {
        floatClient = CLIENT_MULTI_STATEMENTS;
    }

    if (mysql_real_connect(&mMysql, dbParam.strHost.c_str(),
                           dbParam.strUserName.c_str(),
                           dbParam.strPassword.c_str(), dbParam.strDbName.c_str(),
                           dbParam.port, NULL, floatClient) == NULL) {
        printf("mysql_real_connect() failed! \n");
        printf("Reason: %s \n", mysql_error(&mMysql));
        return false;
    }
    mIsConn = true;
    printf("Database connection is successful. \n");
    return true;
}

bool DB_tools::DB_query(string sql, vector<vector<string>> &resultSet) {
    if (!isConn()) {
        cout << "please connect DB !" << endl;

        return false;
    }

    if (mysql_query(&mMysql, sql.c_str()) != 0) {
        cout << "mysql_query getResult failed, Reason: " << mysql_error(&mMysql)
             << " sql: " << sql << endl;

        return false;
    } else {
        MYSQL_RES *result = nullptr;
        result = mysql_store_result(&mMysql);

        if (result != NULL) {
            MYSQL_ROW row = NULL;
            unsigned int cols = mysql_num_fields(result);
            while ((row = mysql_fetch_row(result)) != NULL) {
                vector<string> rowData;
                for (int i = 0; i < cols; ++i) {
                    rowData.emplace_back(row[i]);
                }
                resultSet.push_back(rowData);
            }

            mysql_free_result(result);
        }
    }

    return true;
}

bool DB_tools::DB_execSql(string sql) {
    if (mysql_query(&mMysql, sql.c_str()) != 0) {
        cout << "mysql_query getResult failed, Reason: " << mysql_error(&mMysql)
             << " sql : " << sql << endl;

        return false;
    }

    return true;
}

bool DB_tools::isConn() { return mIsConn; }

bool DB_tools::returnExecSql(string sql) {
    printf("sql is %s\n", sql.c_str());
    if (mysql_query(&mMysql, sql.c_str()) != 0) {
        printf("getResult() failed! \n");
        printf("Reason: %s \n", mysql_error(&mMysql));
        printf("Statements: %s \n", sql.c_str());

        return false;
    } else {
        MYSQL_RES *result = NULL;
        result = mysql_store_result(&mMysql);

        if (result != NULL) {
            printf("It is ok !\n");
            mysql_free_result(result);

            return true;
        }

        printf("no ok !\n");

        return false;
    }

}

bool DB_tools::getResult() {
    MYSQL_RES *result = NULL;
    result = mysql_store_result(&mMysql);

    printf("get result\n");

    if (result != NULL) {
        printf("It is ok !\n");
        mysql_free_result(result);

        return true;
    }

    printf("no ok !\n");

    return false;
}

void DB_tools::data_dispatcher_init() {
    string query_tbl_str;
    string tbl_name;
    string query_str;
    MYSQL_ROW row;
    MYSQL_RES *res;
    unsigned char has_the_tbl = 0;
    int ret;
    string select_str;

    query_str = "call proc_get_newest_yc\(\@yc_ia\)";
    ret = mysql_real_query(&mMysql, query_str.c_str(), (unsigned long) query_str.length());
    //ret = mysql_query(&(this->mysql), query_str);
    res = mysql_store_result(&mMysql);
    if (res == NULL) return;
    while ((row = mysql_fetch_row(res))) {
        printf("[%s]\n", row[0]);
    }
}
