#include "_c_chaYanVehicleQuChong.h"
#include "base/soapApi/soapApi.h"
#include "base/baseTool.h"

_c_chaYanVehicleInfo::_c_chaYanVehicleInfo(_c_chaYanVehicle *pVehicle)
{
    _disposeEnd = false;
    setCheckKey(pVehicle);
}

//根指定信息_keyName及相关照片信息生成字符串，用来后续生成校验码
std::string getVehicleCompareStr(_c_chaYanVehicle *pVehicle, std::vector<std::string> *keyName)
{
    std::string tmpsStr = "#!#123";
    for (unsigned int i = 0; i < keyName->size(); i++) {
        for (unsigned int j=0; j < pVehicle->memberVector.size(); j++) {
            if(keyName->at(i) == pVehicle->memberVector[j].soapName)
            {
                tmpsStr += "_";
                tmpsStr += *(std::string *)(pVehicle->memberVector[j].value);
            }
        }
    }

    if(pVehicle->zhaoPianClassVector.size() > 0)
    {
        for (unsigned int i = 0; i < pVehicle->zhaoPianClassVector.size(); i++) {
             tmpsStr += "_";
             tmpsStr += pVehicle->zhaoPianClassVector[i]->algCode;
        }
    }

    return tmpsStr;
}

void _c_chaYanVehicleInfo::setCheckKey(_c_chaYanVehicle *pVehicle)
{
    uint16_t crc16;
    std::string tmpsStr = getVehicleCompareStr(pVehicle, &_keyName);
    baseTool::Crc16((uint8_t*)tmpsStr.c_str(), tmpsStr.size(), &crc16);
    _checkKey = crc16;
}

uint16_t _c_chaYanVehicleInfo::getCheckKey()
{
    return _checkKey;
}

bool _c_chaYanVehicleInfo::checkDate(uint16_t checkKey)
{
    if(_checkKey == checkKey)
    {
        return true;
    }
    return false;
}

void _c_chaYanVehicleInfo::setDisposeEnd(_c_chaYanVehicle *pVehicle)
{
    setVehiclePhotoInfo(pVehicle);
    __isPass = pVehicle->sessionResult;
    _disposeEnd = true;
    LOG(COMMON,INFO,"vehicle %s[%s] set disposed end\n", pVehicle->liuShuiHao.c_str(), pVehicle->uuid.c_str());
}

std::vector<std::string> _c_chaYanVehicleInfo::getKeyName()
{
    return _keyName;
}

void _c_chaYanVehicleInfo::setGuid(const std::string &guid)
{
    __guid = guid;
}

std::string _c_chaYanVehicleInfo::getGuid()
{
    return __guid;
}

//把车辆检测后的结果信息写入相应的__vehiclePhotoInfo中
void _c_chaYanVehicleInfo::setVehiclePhotoInfo(_c_chaYanVehicle *pVehicle)
{
    __vehiclePhotoInfo.clear();
    for (unsigned int i = 0; i < pVehicle->zhaoPianClassVector.size(); i++)
    {
        _c_photo *pPhoto = pVehicle->zhaoPianClassVector[i];
        PHOTOINFO photoInfo = {pPhoto->algCode, pPhoto->result, pPhoto->reason, pPhoto->photoUrl, pPhoto->localPath};
        __vehiclePhotoInfo.push_back(photoInfo);
    }
}

//从__vehiclePhotoInfo中获取相应的车辆检测结果信息
bool _c_chaYanVehicleInfo::getVehiclePhotoInfo(_c_chaYanVehicle *pVehicle)
{
    _c_photo *pPhoto = NULL;
    //先把原来的照片相关信息释放掉
    for (unsigned int i = 0; i < pVehicle->zhaoPianClassVector.size(); i++)
    {
        pPhoto = pVehicle->zhaoPianClassVector[i];
        if (pPhoto != NULL)
        {
            delete pPhoto;
            pPhoto = NULL;
        }
    }
    pVehicle->zhaoPianClassVector.clear();
    pVehicle->sessionResult = __isPass;

    for (unsigned int i = 0; i < __vehiclePhotoInfo.size(); i++)
    {
        pPhoto = new _c_photo();
        pPhoto->loadUuid();
        pPhoto->cheLiangUid = pVehicle->uuid;
        pPhoto->algCode = __vehiclePhotoInfo[i].algCode;
        pPhoto->result = __vehiclePhotoInfo[i].result;
        pPhoto->reason = __vehiclePhotoInfo[i].reason;
        pPhoto->photoUrl = __vehiclePhotoInfo[i].photoUrl;
        pPhoto->localPath = __vehiclePhotoInfo[i].localPath;
        pVehicle->zhaoPianClassVector.push_back(pPhoto);
    }

    if(pVehicle->zhaoPianClassVector.size() > 0)
    {
        return true;
    }

    return false;
}
