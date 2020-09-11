#ifndef _c_yingXiangLshInfo_QUCHONG_H
#define _c_yingXiangLshInfo_QUCHONG_H

#include "_c_yingXiangVehicle.h"
#include "../common/_c_commonExtra.h"

class _c_yingXiangLshInfo {
public:
    _c_yingXiangLshInfo(_c_yingXiangVehicle *pVehicle);
    bool checkDate(uint16_t checkKey);
    uint16_t getCheckKey();
    void setDisposeEnd(_c_yingXiangVehicle *pVehicle);
    std::vector<std::string> getKeyName();
    void setGuid(const std::string &_guid);
    std::string getGuid();
    void setVehiclePhotoInfo(_c_yingXiangVehicle *pVehicle);
    bool getVehiclePhotoInfo(_c_yingXiangVehicle *pVehicle);

private:
    void setCheckKey(_c_yingXiangVehicle *pVehicle);

private:
    bool _disposeEnd;
    uint16_t _checkKey;
    std::vector<std::string> _keyName={"lsh","hphm","clsbdh","cllx","fdjh"};
    std::string __guid;
    std::string __isPass;
    std::vector<PHOTOINFO> __vehiclePhotoInfo;
};

#endif // _c_yingXiangLshInfo_QUCHONG_H
