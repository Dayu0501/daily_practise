#include "_c_chaYanYuan.h"
#include "base/baseTool.h"

std::string _c_chaYanYuan::getSql()
{
    std::string sqlStr = "";
    std::string dangTianRiQi = baseTool::getDangTianRiQi();
    if(memberVector.size() > 0)
    {
        std::string insertSqlStr = "";
        insertSqlStr += "INSERT INTO ";
        insertSqlStr += getTableName();
        std::string valueName = " (";
        std::string valueList = " (";
        std::string setStr = "";
        for (unsigned int i = 0; i < memberVector.size(); i++) {
            if(memberVector[i].dbOption.dbLink)
            {
                valueName += memberVector[i].codeName + ",";
                valueList += "'" + *memberVector[i].value + "',";
                setStr += memberVector[i].codeName + "='" + *memberVector[i].value + "',";
            }
        }
        valueName.pop_back();
        valueList.pop_back();
        setStr.pop_back();
        valueName += ") ";
        valueList += ") ";
        insertSqlStr += valueName;
        insertSqlStr += "value";
        insertSqlStr += valueList+";";

        sqlStr +=" DROP PROCEDURE IF EXISTS pro_AddColumn; CREATE PROCEDURE pro_AddColumn() BEGIN ";
        sqlStr +=" IF NOT EXISTS (SELECT 1 FROM "+getTableName()+" where shenFenZheng='"+shenFenZheng+"' and inDbTime > '"+dangTianRiQi+"') THEN ";
        sqlStr += insertSqlStr;
        sqlStr +=" ELSE";
        sqlStr +=" update chaYanYuan_info set "+setStr+" where shenFenZheng='"+shenFenZheng+"' and inDbTime > '"+dangTianRiQi+"';";
        sqlStr +=" END IF;";
        sqlStr +=" END; CALL pro_AddColumn; DROP PROCEDURE pro_AddColumn; ";
        printf("sqlStr:%s\n",sqlStr.c_str());
    }


    return sqlStr;
}
