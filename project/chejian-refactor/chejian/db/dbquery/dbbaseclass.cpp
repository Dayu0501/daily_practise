#include "dbbaseclass.h"
#include "../mysql/MySQL_DB.h"

Json::Value dbBaseClass::getJson()
{
    Json::Value  root;
    for (unsigned int i = 0; i < memberVector.size(); i++) {
        if(memberVector[i].isOpen)
            root[memberVector[i].desc] = *(memberVector[i].value);
    }
    return root;
}

std::string dbBaseClass::getSql(std::vector<std::string> *pWhereVector,std::string table)
{

    std::string sql = "select ";
    for (unsigned int i = 0; i< memberVector.size(); i++) {
        sql += " " + memberVector[i].dbtype + ",";
    }
    sql.pop_back();
    sql += " from " + table + " where 1=1";
    for (unsigned int i = 0; i< pWhereVector->size(); i++) {
        sql += " " + (*pWhereVector)[i];
    }
    return sql;

}

unsigned int dbBaseClass::query(std::string table,std::vector<std::string> *pWhereVector,const char *host, unsigned int port, const char *user, const char *passwd, const char *db)
{
    MySQL_DB mysqldb;
    if (mysqldb.connect(host, port, user, passwd, db, false)) {
        std::string sql = getSql(pWhereVector, table);
        printf("++++ sql:%s\n", sql.c_str());
        MYSQL_RES *result = mysqldb.getResult(sql.c_str());
        if (result != NULL) {

            MYSQL_ROW row = NULL;
            while ((row = mysql_fetch_row(result)) != NULL) {
                dbBaseClass *pDbClass = getDbClass();
                for (unsigned int i = 0; i< pDbClass->memberVector.size(); i++) {
                    if(row[i] != 0)
                        (*(pDbClass->memberVector[i].value)) = row[i];
                }
                queryVector.push_back(pDbClass);
            }
            mysqldb.freeResult(result);
        }
    }
    mysqldb.disconnect();
    return queryVector.size();
}

Json::Value dbBaseClass::getVectorJson()
{
    Json::Value root;
    for(unsigned int i = 0; i < queryVector.size(); i++)
    {
        Json::Value subRoot = queryVector[i]->getJson();
        root.append(subRoot);
    }
    return root;
}

Json::Value dbBaseClass::getOrderJson()
{
    Json::Value  root;
    for (unsigned int i = 0; i < memberVector.size(); i++) {
        if(memberVector[i].isOpen)
        {
            Json::Value  subRoot;
            subRoot["name"] = memberVector[i].desc;
            root.append(subRoot);
        }
    }
    return root;
}
