#include "db_passper.h"

std::string db_passPer::getSql(std::vector<std::string> *pWhereVector,std::string table)
{
    UNUSED(table);
    std::string sql = "select ";
    for (unsigned int i = 0; i< memberVector.size(); i++) {
        sql += " " + memberVector[i].dbtype + ",";
    }
    sql.pop_back();
    sql += " from ";
    sql += " (";
    sql += " select  zhaoPianLeiXing, count(*) as allcount from photo_info  ";
    sql += " where 1=1  ";
    for (unsigned int i = 1; i< pWhereVector->size(); i++) {
        sql += " " + (*pWhereVector)[i];
    }
    sql += " and jieGuo in (1,5)  ";
    sql += " group by zhaoPianLeiXing  ";
    sql += ") as a";
    sql += " left join ";
    sql += " (";
    sql += " select  zhaoPianLeiXing, shuoMing, count(*) as passcount ";
    sql += " from photo_info ";
    sql += " where 1=1 ";
    for (unsigned int i = 0; i< pWhereVector->size(); i++) {
        sql += " " + (*pWhereVector)[i];
    }
    sql += " group by zhaoPianLeiXing,shuoMing ";
    sql += ") as b";
    sql += " on a.zhaoPianLeiXing = b.zhaoPianLeiXing ";
    sql += " order by b.zhaoPianLeiXing,b.passcount ";
    return sql;
}
