#ifndef DB_PASSPER_H
#define DB_PASSPER_H

#include "dbbaseclass.h"

class db_passPer:public dbBaseClass{
public:

    std::string category;
    std::string reason;
    std::string passCount;
    std::string allCount;
    std::string per;

    dbBaseClass *getDbClass(){
        return new db_passPer();
    }

    db_passPer(){
        memberVector.push_back({"zhaoPianLeiXing", "a.zhaoPianLeiXing","照片类型", &category,true});
        memberVector.push_back({"shuoMing", "ifnull(b.shuoMing,'通过') as shuoMing","结果说明", &reason,true});
        memberVector.push_back({"passcount", "ifnull(b.passcount,0) as passcount","数量", &passCount,true});
        memberVector.push_back({"allCount", "a.allcount","总数量", &allCount,true});
        memberVector.push_back({"per", "CONCAT(ROUND(ifnull(b.passcount,0)/a.allcount*100,2),'%') as per","百分比", &per,true});
    }

    std::string getSql(std::vector<std::string> *pWhereVector,std::string table);

};

#endif // DB_PASSPER_H
