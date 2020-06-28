#include "MySQL_DB.h"

MySQL_DB::~MySQL_DB() {
    terminate_MySQL_library();
}

bool MySQL_DB::initialize_MySQL_library() {
    static bool init_flag = false;

    if (init_flag) {
        printf("initialize_MySQL_library() has been called successfully, do not "
               "need to be call again! \n");
        return false;
    }

    if (!(init_flag = !mysql_library_init(0, nullptr, nullptr))) {
        printf("initialize_MySQL_library() failed! \n");
    }

    return init_flag;
}

void MySQL_DB::terminate_MySQL_library() { mysql_library_end(); }

bool MySQL_DB::connect(const char *host, unsigned int port, const char *user,
                       const char *passwd, const char *db, bool statrments) {

    if (mysql_thread_init() != 0) {
        printf("mysql_thread_init() failed! \n");
        return false;
    }

    if (mysql_init(&mysql) == nullptr) {
        printf("mysql_init() failed! \n");
        return false;
    }

    /*
        指定本次连接的编码方式（取决于编译器对字符串的编码存储方式）
        VS:gbk
        gcc:utf8
    */
    if (mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8") != 0) {
        printf("mysql_options(MYSQL_SET_CHARSET_NAME) failed! \n");
        return false;
    }

    unsigned long floatClient = 0;

    if (statrments) {
        floatClient = CLIENT_MULTI_STATEMENTS;
    }

    if (mysql_real_connect(&mysql, host, user, passwd, db, port, nullptr,
                           floatClient) == nullptr) {
        printf("mysql_real_connect() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        return false;
    }

    printf("Database connection is successful. \n");
    return true;
}

void MySQL_DB::disconnect() {
    mysql_close(&mysql);
    mysql_thread_end();

    // printf("Disconnected with the database. \n");
}

bool MySQL_DB::createTable(const char *name, const char *format) {
    std::string sqlString = "CREATE TABLE IF NOT EXISTS";

    sqlString = sqlString + " " + name + " " + format;
    if (mysql_query(&mysql, sqlString.c_str()) != 0) {
        printf("createTable() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        printf("Statements: %s \n", sqlString.c_str());
        return false;
    }

    return true;
}

bool MySQL_DB::dropTable(const char *name) {
    std::string sqlString = "DROP TABLE";

    sqlString = sqlString + " " + name;
    if (mysql_query(&mysql, sqlString.c_str()) != 0) {
        printf("dropTable() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        printf("Statements: %s \n", sqlString.c_str());
        return false;
    }

    return true;
}

bool MySQL_DB::insert(const char *tableName, const char *valueFormat) {
    std::string sqlString = "INSERT INTO";

    sqlString = sqlString + " " + tableName + " " + valueFormat;
    if (mysql_query(&mysql, sqlString.c_str()) != 0) {
        printf("insert() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        printf("Statements: %s \n", sqlString.c_str());
        return false;
    }

    return true;
}

bool MySQL_DB::noReturnWork(const char *sql) {
    if (mysql_query(&mysql, sql) != 0) {
        printf("%s \n", sql);
        printf("noReturnWork()  \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        return false;
    }
    return true;
}

bool MySQL_DB::select(const char *tableName, const char *format) {
    std::string sqlString = "SELECT";

    sqlString = sqlString + " " + format + " " + "FROM" + " " + tableName;
    if (mysql_query(&mysql, sqlString.c_str()) != 0) {
        printf("mysql_query() select failed! \n");
        return false;
    } else {
        MYSQL_RES *result = NULL;
        result = mysql_store_result(&mysql);

        /* 打印表头 */
        unsigned int fieldCount = mysql_num_fields(result);
        MYSQL_FIELD *field = NULL;
        for (unsigned int i = 0; i < fieldCount; i++) {
            field = mysql_fetch_field_direct(result, i);
            printf("%s \t\t", field->name);
        }
        printf("\n");

        /* 打印所有行 */
        MYSQL_ROW row = NULL;
        while ((row = mysql_fetch_row(result)) != NULL) {
            for (unsigned int i = 0; i < fieldCount; i++) {
                printf("%s \t\t", (row[i] ? row[i] : NULL));
            }
            printf("\n");
        }

        mysql_free_result(result);
    }

    return true;
}

unsigned long MySQL_DB::getLastID() {
    if (mysql_query(&mysql, "SELECT LAST_INSERT_ID()") != 0) {
        printf("getLastID() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        return 0;
    }

    MYSQL_RES *result = NULL;
    result = mysql_store_result(&mysql);
    if (result == NULL) {
        printf("getLastID() failed! \n");
        printf("Reason: mysql_store_result() failed! \n");
        return 0;
    }

    MYSQL_ROW row = NULL;
    row = mysql_fetch_row(result);
    if (row == NULL) {
        printf("getLastID() failed! \n");
        printf("Reason: mysql_fetch_row() failed! \n");
        mysql_free_result(result);
        return 0;
    }

    if (row[0] == NULL) {
        printf("getLastID() failed! \n");
        printf("Reason: no data! \n");
        mysql_free_result(result);
        return 0;
    }

    std::string tmp;
    tmp = row[0];
    unsigned long ret = std::stol(tmp);
    mysql_free_result(result);
    return ret;
}

bool MySQL_DB::createDB(const char *name) {
    std::string sqlString = "CREATE DATABASE IF NOT EXISTS ";
    sqlString += name;
    if (0 != mysql_query(&mysql, sqlString.c_str())) {
        printf("createDB() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        printf("Statements: %s \n", sqlString.c_str());
        return false;
    }

    return true;
}

bool MySQL_DB::selectDB(const char *name) {
    if (mysql_select_db(&mysql, name) != 0) {
        printf("selectDB() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        return false;
    }

    return true;
}

MYSQL_RES *MySQL_DB::getResult(const char *SqlStatement) {
    if (mysql_query(&mysql, SqlStatement) != 0) {
        printf("getResult() failed! \n");
        printf("Reason: %s \n", mysql_error(&mysql));
        printf("Statements: %s \n", SqlStatement);
        return NULL;
    } else {
        MYSQL_RES *result = NULL;
        result = mysql_store_result(&mysql);
        return result;
    }
}

void MySQL_DB::freeResult(MYSQL_RES *result) { mysql_free_result(result); }

unsigned int MySQL_DB::getErrorNumber() { return mysql_errno(&mysql); }
