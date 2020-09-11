#ifndef DB_VEHICLEINFO_H
#define DB_VEHICLEINFO_H
#include "dbbaseclass.h"

class db_vehicleInfo:public dbBaseClass{
public:

    std::string id;
    std::string hphm;
    std::string syr;
    std::string cllx;
    std::string syxz;
    std::string is_pass;
    std::string isPassReason;
    std::string clsbdh;
    std::string deviceid;
    std::string created_at;

    dbBaseClass *getDbClass(){
        return new db_vehicleInfo();
    }

    db_vehicleInfo(){
        memberVector.push_back({"uuid", "uuid","ID", &id,true});//??
        memberVector.push_back({"hphm", "CONCAT(left(faZhengJiGuan,1),chePaiHao) as chePaiHao","车牌号", &hphm,true});
        memberVector.push_back({"syr", "shiYongRen","所有人", &syr,true});
        memberVector.push_back({"clsbdh", "cheJiaHao","车架号", &clsbdh,true});
        memberVector.push_back({"cllx", "cheLiangLeiXing","车辆类型", &cllx,true});
        memberVector.push_back({"syxz", "shiYongXingZhi","使用性质", &syxz,true});
        memberVector.push_back({"isPass", "isPass","是否通过", &is_pass,true});
        memberVector.push_back({"isPassReason", "isPassReason","原因", &isPassReason,true});
//        memberVector.push_back({"device_id", "device_id","运行机器", &deviceid,true});//??
        memberVector.push_back({"inDbTime", "inDbTime","分析时间", &created_at,true});//??

    }
};


#endif // DB_VEHICLEINFO_H
