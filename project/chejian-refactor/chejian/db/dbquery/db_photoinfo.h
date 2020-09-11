#ifndef DB_PHOTOINFO_H
#define DB_PHOTOINFO_H
#include "dbbaseclass.h"

class db_photoInfo:public dbBaseClass{
public:

    std::string category;
    std::string result;
    std::string reason;
    std::string zhaoPianXiaZaiShiJian;
    std::string suanFaFenXiShiJian;
    std::string suanfaYunXingShiJian;
    std::string jiSuanShiJian;
    std::string createdTime;
    std::string zhaoPianXiaZaiDiZhi;

    dbBaseClass *getDbClass(){
        return new db_photoInfo();
    }

    db_photoInfo(){
        memberVector.push_back({"zhaoPianLeiXing", "zhaoPianLeiXing","照片类型", &category,true});
        memberVector.push_back({"jieGuo", "jieGuo","结果", &result,true});
        memberVector.push_back({"shuoMing", "shuoMing","说明", &reason,true});
        memberVector.push_back({"zhaoPianXiaZaiShiJian", "zhaoPianXiaZaiShiJian","图片下载时间", &zhaoPianXiaZaiShiJian,true});
        memberVector.push_back({"suanFaFenXiShiJian", "suanFaFenXiShiJian","算法分析时间", &suanFaFenXiShiJian,true});
        memberVector.push_back({"suanfaYunXingShiJian", "suanfaYunXingShiJian","算法运行时间", &suanfaYunXingShiJian,true});
        memberVector.push_back({"jiSuanShiJian", "jiSuanShiJian","总时长", &jiSuanShiJian,true});
        memberVector.push_back({"inDbTime", "inDbTime","分析时间", &createdTime,true});
        memberVector.push_back({"zhaoPianXiaZaiDiZhi", "zhaoPianXiaZaiDiZhi","下载地址", &zhaoPianXiaZaiDiZhi,true});
    }
};

#endif // DB_PHOTOINFO_H
