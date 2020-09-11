#ifndef _C_CHAYANVEHICLEINFO_QUCHONG_H
#define _C_CHAYANVEHICLEINFO_QUCHONG_H

#include "base/_c_chaYanVehicle.h"
#include "../common/_c_commonExtra.h"

class _c_chaYanVehicleInfo {
public:
    _c_chaYanVehicleInfo(_c_chaYanVehicle *pVehicle);
    bool checkDate(uint16_t checkKey);
    uint16_t getCheckKey();
    void setDisposeEnd(_c_chaYanVehicle *pVehicle);
    std::vector<std::string> getKeyName();
    void setGuid(const std::string &_guid);
    std::string getGuid();
    void setVehiclePhotoInfo(_c_chaYanVehicle *pVehicle);
    bool getVehiclePhotoInfo(_c_chaYanVehicle *pVehicle);

private:
    void setCheckKey(_c_chaYanVehicle *pVehicle);

private:
    bool _disposeEnd;
    uint16_t _checkKey;
    std::vector<std::string> _keyName={"lsh","hphm","clsbdh","cllx","fdjh"};
    std::string __guid;
    std::string __isPass;
    std::vector<PHOTOINFO> __vehiclePhotoInfo;
};

#endif // _C_CHAYANVEHICLEINFO_QUCHONG_H
