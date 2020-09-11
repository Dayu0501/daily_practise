#ifndef _C_VEHICLEINFO_QUCHONG_H
#define _C_VEHICLEINFO_QUCHONG_H

#include "../common/_c_commonExtra.h"
#include "base/_c_vehicle.h"

#define RET_RECHECK 2
#define RET_REPEAT 1
#define RET_NORMAL 0

class _c_vehicleInfo{
public:
    _c_vehicleInfo(_c_vehicle *pVehicle);
    bool checkDate(uint16_t checkKey);
//    uint16_t getCheckKey();
//    uint16_t getCheckKeyReCheck();
    void setDisposeEnd(_c_vehicle *pVehicle);
    std::vector<std::string> getKeyName();
    void setGuid(const std::string &_guid);
    std::string getGuid();
    void setVehiclePhotoInfo(_c_vehicle *pVehicle);
    bool getVehiclePhotoInfo(_c_vehicle *pVehicle);
    std::string getCheckMd5();
    std::string getReCheckMd5();

private:
    void setCheckKey(_c_vehicle *pVehicle);

private:
    bool _disposeEnd;
    uint16_t _checkKey;  //整车的key，包括图片
    uint16_t _checkKeyReCheck;  //仅仅包含_keyName的key
    std::string _md5;
    std::string _md5ReCheck;
    std::vector<std::string> _keyName={"lsh","hphm","clsbdh","cllx","fdjh"};
    std::string __guid;
    std::string __isPass;
    std::vector<PHOTOINFO> __vehiclePhotoInfo;
};

#endif // _C_VEHICLEINFO_QUCHONG_H
