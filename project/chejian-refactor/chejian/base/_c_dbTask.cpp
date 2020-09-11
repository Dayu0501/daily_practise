#include "_c_dbTask.h"
#include <cstring>
#include"dataCenter.h"

std::string _c_dbTask::getTableName()
{
    //如果使用动态表在此处动态生成表
    if(tableName.empty())
    {
        printf("error _c_dbTask tableName is empty\n");
    }
    return tableName;
}

std::string _c_dbTask::getSql()
{
    std::string sqlStr = "";
    if(memberVector.size() > 0)
    {
        sqlStr += "INSERT INTO ";
        sqlStr += getTableName();
        std::string valueName = " (";
        std::string valueList = " (";
        for (unsigned int i = 0; i < memberVector.size(); i++) {
            if(memberVector[i].dbOption.dbLink)
            {
                valueName += memberVector[i].codeName + ",";
                valueList += "'" + *memberVector[i].value + "',";
            }
        }
        valueName.pop_back();
        valueList.pop_back();
        valueName += ") ";
        valueList += ") ";
        sqlStr += valueName;
        sqlStr += "value";
        sqlStr += valueList;
    }
    //printf("sqlStr:%s\n",sqlStr.c_str());
    return sqlStr;
}

std::string _c_dbTask::getCreatTableSql()
{
    //表格创建语句
    std::string strTableName =  getTableName();
    std::string strCreateTableSql = "create table if not exists " + strTableName + " (";
    for (unsigned int i = 0; i < memberVector.size(); i++) {
        if(memberVector[i].dbOption.dbLink)
        {
            strCreateTableSql += memberVector[i].codeName + " " +memberVector[i].dbOption.dbtype + " COMMENT '" + memberVector[i].desc + "',";
        }
    }
    strCreateTableSql += "inDbTime DATETIME NOT NULL DEFAULT NOW() COMMENT '本行数据记录时间'";
    strCreateTableSql += " ) ENGINE=InnoDB DEFAULT CHARSET=utf8;";
    return strCreateTableSql;
}

std::string getAddColumn(std::string dbName, std::string tableName, std::string columnName, std::string columnType, std::string comment)
{
    std::string str = " IF NOT EXISTS (SELECT 1 FROM information_schema.columns WHERE TABLE_NAME='"+tableName+"' AND TABLE_SCHEMA = '"+dbName+"' AND COLUMN_NAME='"+columnName+"') THEN ";
    str += " ALTER TABLE "+tableName+" ADD "+columnName+" "+columnType+" COMMENT '"+comment+"'; ";
    str += " END IF; ";
    return str;
}

std::string _c_dbTask::getUpdateTableSql()
{
    //表格同步语句
    std::string strTableName =  getTableName();
    std::string strIsDataExist = " DROP PROCEDURE IF EXISTS pro_AddColumn; CREATE PROCEDURE pro_AddColumn() BEGIN ";

    for (unsigned int i = 0; i < memberVector.size(); i++) {
        if(memberVector[i].dbOption.dbLink)
        {

            strIsDataExist += getAddColumn(DBSCHEMANAME,strTableName, memberVector[i].codeName, memberVector[i].dbOption.dbtype, memberVector[i].desc);
        }
    }

    strIsDataExist += " END; CALL pro_AddColumn; DROP PROCEDURE pro_AddColumn; ";

    //printf("strIsDataExist:%s\n",strIsDataExist.c_str());
    return strIsDataExist;
}

void _c_dbTask::dbWork()
{
    pushDbTaskQueue(this);
}
